require 'json'
require 'net/http'
require 'socket'

raise 'STOP_POINT environment variable not specified' unless ENV['STOP_POINT']

server = TCPServer.new '0.0.0.0', ENV['PORT'] || 8080
uri = URI("https://api.tfl.gov.uk/StopPoint/#{ENV['STOP_POINT']}/Arrivals")

loop do
    puts "Listening on port #{server.addr[1]}..."
    client = server.accept

    puts client.remote_address.ip_address

    line_id = client.recv(1).ord.to_s

    puts line_id

    arrivals =
        JSON.parse(Net::HTTP.get(uri))
            .select{ |a| a['lineId'] == line_id }
            .map{ |a| a['timeToStation'] / 10 }
            .sort

    puts arrivals.join(', ')

    client.write arrivals.pack("C*")
    client.close
end
