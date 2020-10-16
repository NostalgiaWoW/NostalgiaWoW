# frozen_string_literal: true

require 'mysql2'
require 'securerandom'
require 'yaml'
require_relative './job_definition.rb'
require_relative './job_helper.rb'
require_relative './job_scanner.rb'

# noinspection RubyUnusedLocalVariable
def run_job(mysql, agent_job, data, job)
  puts "Executing #{agent_job.name} (#{agent_job.description})..."
  load agent_job.init_path
  main = AgentJobMain.new JobHelper.new(agent_job)
  main.run data
  true
rescue StandardError => ex
  puts 'Failed to run job due to the following error:'
  puts ex
  job.status = 'failed'
  job.status_reason = ex.to_s
  job.save mysql
  false
end

def get_job(client, agent_id)
  # Check for existing jobs
  get_job_stmt = client.prepare 'SELECT * FROM agent_queue WHERE agent_id = ? AND status = ? LIMIT 1'
  get_job_query = get_job_stmt.execute agent_id, 'pending'
  get_job_query.each do |row|
    return JobDefinition.new row
  end

  set_job_stmt = client.prepare 'UPDATE IGNORE agent_queue t SET t.agent_id = ?, t.status = ? WHERE t.status = ? LIMIT 1'
  set_job_stmt.execute agent_id, 'running', 'pending'

  get_marked_job_stmt = client.prepare 'SELECT * FROM agent_queue t WHERE t.agent_id = ? AND t.status = ? LIMIT 1'
  get_marked_job_stmt.execute(agent_id, 'running').each do |row|
    return JobDefinition.new row
  end
  nil
end

config = YAML.load_file './config/agent.yml'
agent_config = config['agent']
db_config = config['database']

agent_id = agent_config['id']

scanner = JobScanner.new "#{Dir.pwd}/jobs"

mysql = Mysql2::Client.new(
    host: db_config['host'],
    port: db_config['port'],
    username: db_config['username'],
    password: db_config['password'],
    database: db_config['agentdb']
)

# Fail any crashed jobs
reset_crashed_jobs_stmt = mysql.prepare 'UPDATE IGNORE agent_queue t SET t.status = ?, t.status_reason = ? WHERE t.agent_id = ? AND t.status = ?'
reset_crashed_jobs_stmt.execute 'crashed', 'Job was marked as running when the agent booted up. Make sure each agent has its own ID!', agent_id, 'running'

loop do
  # Small sleep before running another job
  sleep 0.5

  job = get_job mysql, agent_id
  if job.nil?
    puts "No jobs available! Waiting #{agent_config['delay']} seconds before trying again."
    sleep agent_config['delay']
    next
  end

  puts "Attempting to run job: #{job.opcode}, [#{job.data}]"

  puts 'Scanning for job...'
  jobs = scanner.load_jobs
  found = false
  jobs.each do |agent_job|
    next unless agent_job.opcode == job.opcode

    found = true
    if run_job mysql, agent_job, job.data, job
      puts "Job '#{agent_job.name}' completed without error."
      job.erase mysql
    end
  end

  next if found

  puts "Could not find jobfile for job #{job.opcode}!"
  job.status = 'jobfile_missing'
  job.status_reason = 'Could not execute this job as the jobfile is missing. Please ensure the jobfile is registered with the agent.'
  job.save mysql
end
