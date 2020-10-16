require 'mysql2'

class Database
  def initialize(config)
    @client = Mysql2::Client.new(
      host: config['host'],
      port: config['port'],
      username: config['username'],
      password: config['password']
    )
    @lp_database = config['lp_database']
    @lp_real_table = config['lp_real_table']
    @lp_logs_table = config['lp_logs_table']
  end

  def set_lp_for_account(account_id, loyalty_points)
    statement = @client.prepare "INSERT INTO #{@lp_database}.#{@lp_real_table} (account_id, loyalty_points) VALUES (?, ?) ON DUPLICATE KEY UPDATE loyalty_points = loyalty_points + ?"
    statement.execute account_id, loyalty_points, loyalty_points
  end
end