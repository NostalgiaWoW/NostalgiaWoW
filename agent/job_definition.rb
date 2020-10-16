class JobDefinition
  attr_accessor :opcode, :created_at, :id, :data, :agent_id, :status, :status_reason

  def initialize(row)
    @id = row['id']
    @opcode = row['opcode']
    @data = row['data']
    @created_at = row['created_at']
    @agent_id = row['agent_id']
    @status = row['status']
    @status_reason = row['status_reason']
  end

  def save(mysql)
    statement = mysql.prepare('UPDATE IGNORE agent_queue t SET t.opcode = ?, t.data = ?, t.created_at = ?, t.agent_id = ?, t.status = ?, t.status_reason = ? WHERE t.id = ?')
    statement.execute opcode, data, created_at, agent_id, status, status_reason, id
  end

  def erase(mysql)
    statement = mysql.prepare('DELETE FROM `agent_queue` WHERE `id` = ?')
    statement.execute id
  end
end