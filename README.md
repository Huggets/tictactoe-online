# Tic Tac Toe Online

This is a tic tac toe game with a server and clients.

It is just a project where I try to use the linux sockets to make an online.

# How does it works?

You execute the server executable. This server will wait until two clients are connected. To stop the server, you need
to do a CTRL-C.

After you started the server, you need to execute two instances of the clients. This is done via the command:  
```client <hostname> <port>``` (note: the server only accept 10678 as a valid port)  
So you can for example run ```./client localhost 10678``` if the client is executed on the same machine as the server.
