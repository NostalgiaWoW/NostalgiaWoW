require 'mysql2'
require 'yaml'

class JobHelper
  def initialize(agent_job)
    @agent_job = agent_job
  end

  def load_yaml(relative_path)
    YAML.load_file File.join(@agent_job.job_dir, relative_path)
  end

  def load_file(relative_path)
    load File.join(@agent_job.job_dir, relative_path)
  end
end