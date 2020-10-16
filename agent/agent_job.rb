require 'yaml'

class AgentJob
  attr_reader :job_dir, :status, :name, :description, :exec, :config, :opcode

  def initialize(job_dir)
    @job_dir = job_dir
    @config = YAML.load_file File.join(job_dir, 'job.yml')
    job = @config['job']
    @name = job['name']
    @opcode = job['opcode']
    @exec = job['exec']
    @description = job['description']
    @status = job['status']
  end

  def init_path
    File.join @job_dir, @exec
  end

  def to_s
    "#{name}: #{description}"
  end
end