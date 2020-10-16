#!/usr/bin/ruby

current_time = Time.now.strftime '%Y%m%d%H%M%S'
template_filename = 'migration_template.sql'

unless File.exists? template_filename
	puts "#{template_filename} does not exist."
	return
end

print "Which database is the migration for? [characters, logon, logs, world]: "
database = gets.chomp

unless ['characters', 'logon', 'logs', 'world'].include? database
	puts "#{database} is not a valid choice."
	return
end

print "Enter a migration name (lowercase, underscores, numbers only): "
migration_name = gets.chomp

unless migration_name =~ /^\w+$/
	puts "#{migration_name} is not a valid migration name."
end

migration_file_name = "#{current_time}_#{migration_name}_#{database}.sql"

begin
	File.open template_filename, 'r' do |template_file|
		File.open migration_file_name, 'w' do |migration_file|
			template_file.each_line do |line|
				migration_file.puts line.gsub('##CURRENT_TIME##', current_time).gsub('##MIGRATION_NAME##', migration_name)
			end
		end
	end

	puts "#{migration_file_name} has been created. Remember to move it to the migrations folder when you are done!"
rescue Exception => e
	puts e
	puts "Could not create migration."
end
