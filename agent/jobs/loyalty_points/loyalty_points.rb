require 'json'
require 'mysql2'
require 'yaml'

class AgentJobMain
  def initialize(helper)
    @helper = helper
    @config = helper.load_yaml 'config.yml'
    helper.load_file 'database.rb'
    @database = Database.new @config['database']
  end

  def run(data)
    data = JSON.parse data

    account_id = data['account_id']
    loyalty_points = data['loyalty_points']
    source = data['source_id']

    @database.set_lp_for_account account_id, loyalty_points

    action = loyalty_points.positive? ? 'gained' : 'lost'
    puts "Account #{account_id} #{action} #{loyalty_points.abs} loyalty points for #{source}!"
  end
end