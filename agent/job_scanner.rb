require_relative './agent_job'

class JobScanner
  def initialize(jobs_dir)
    @jobs_dir = jobs_dir
    puts @jobs_dir
  end

  def load_jobs
    directories = Dir.entries(@jobs_dir).select do |dir|
      File.directory?(File.join(@jobs_dir, dir)) && dir !~ /^\.{1,2}$/
    end

    jobs = []
    directories.each do |dir|
      path = File.join @jobs_dir, dir
      next unless Dir.entries(path).include? 'job.yml'

      job = AgentJob.new path
      jobs.push job if job.status == 'active'
    end
    jobs
  end
end