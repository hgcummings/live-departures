require 'socket'

server = TCPServer.new '0.0.0.0', 43134 # Server bind to port 2000

loop do
  puts 'listening...'
  client = server.accept    # Wait for a client to connect
  client.write [20,50,70].pack("C*")
  client.close
end
