#!/usr/bin/ruby

%i[characters logon logs world].each do |database|
	scan_regex = Regexp.new "#{database}\.sql$"
	migrations = Dir.entries('.').select do |e|
		e =~ scan_regex
	end.sort
	File.open "#{database}_db_updates.sql", 'w' do |updates_file|
		migrations.each do |migration|
			updates_file.puts '/*'
			updates_file.puts " * #{migration}"
			updates_file.puts ' */'
			File.open migration, 'r' do |migration_file|
				migration_file.each_line do |line|
					updates_file.puts line
				end
			end
		end
		puts "Written #{migrations.count} #{database} migrations."
	end unless migrations.count == 0
end
