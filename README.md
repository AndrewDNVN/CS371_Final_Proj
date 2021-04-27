# CS371Proj
Project for CS 371
This project was designed by Andrew Donovan

Using C/C++ to build a remote file server.

There are two Main Files:

Server.cpp

Client.cpp

	Each folder contains subfiles for each function this was done to ease debugging.

	Server files:
		server.h -> used for headers in one place and for the server log strucutre
		login.cpp -> login function for the server
		upload_S.cpp -> upload function for the server
		download_S.cpp -> download function for the server
		del_S.cpp -> delete function for the server
		stats_S.cpp -> directory and file info for the server
		password.txt -> list of username and passwords for the users
		Server.cpp -> main function and connection // calls other functions described above

	Client files:
		client.h -> used for headers and for client log struct
		upload.cpp -> upload function for the client
		download.cpp -> download function for the client
		del.cpp -> delete function for the client
		dir.cpp -> directory function for the client
		Client.cpp -> main function and connection // calls other functions described above


Server.cpp and Client.cpp can be built using:

gcc -o server Server.cpp -lstdc++

gcc -o client Client.cpp -lstdc++

	Needed to use -lstdc++, to bring in the correct linker

Command Line arguments:
For server has only one the Port number to listen from; ran in form as such:
	
	./Server (SAMPLE PORT)8000

For the client it has two arguments: the IP address to connect to as well as the port number:
	
	./Client HOSTNAME (SAMPLE PORT)8000

Server will loop continously to listen for new connections after, either the client disconnects or drops the connection.

The other files included are for testing the functionality of the two programs. These are small files less than 10 MB, to generate larger files use locally:
	
	fallocate -l 1G test.img
	^this creates a file of size 1GB locally and is what I used for testing.

As well as the implementation notes/report screenshots of functionalily and this readme file.

Along with all of this is a screen recordiong of all of the commands working as intended.


