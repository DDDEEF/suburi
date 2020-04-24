require 'mysql2'

client = Mysql2::Client.new(
	host: "localhost",       #例として書いています。
	database: "sampledb",    #例として書いています。
	username: "root",        #例として書いています。
	password: "Abcdef01."    #例として書いています。
)

results = client.query("select * from user")

results.each do |row|
  puts row
end
