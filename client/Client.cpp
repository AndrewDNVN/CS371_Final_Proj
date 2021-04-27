// Written by Andrew Donovan

#include "client.h"

#include "upload.cpp" // working
#include "del.cpp" // working

#include "download.cpp" // seems to be working
#include "dir.cpp" // working

/*
	Using a mix of c and c++, mostly due to myslef having a better understanding of c socket design. 
	But liking c++ for some of its more creature comforts.

*/	

int main(int argc, char *argv[]) //working
{
    

    int sockfd, portnum, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
//  Condition to see if right number of command line arguments
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       close(sockfd);
       exit(0);
    }

//  Connects to port number
    portnum = atoi(argv[2]);

//  Opens a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "ERROR opening socket:: Exiting with status -1\n";
        close(sockfd);
        exit(-1);
    }
    cout<< "Socket created\n";

//  Checks for host to exist and connects to it
    server = gethostbyname(argv[1]);
    if (server == NULL) {
       cout << "ERROR, no such host:: Exiting with status -1\n";
       close(sockfd);
      exit(-1);
    }
    

    // cleans out memory in place of the new serv address

    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    // defines the family of connection

    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    
	// converts port

    serv_addr.sin_port = htons(portnum);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
     	 cout << "ERROR connecting:: Exiting with status -1\n";
        close(sockfd);
        exit(-1);
    }
    
    cout << "Connected.\n";

    //create client side mirror of the server log file
    struct log client_int[NUM_OF_LOG];

// Send user name / password to server

    int stat = 0, bytes_sent = 0;

   	string usr_name_S, password_S;

    cout << "==============================================\n";  

    cout << "Please enter your username. (Server side update only)\n";
    cin >> usr_name_S;
    cout << "And now your password.\n";
    cin >> password_S;
	char buf[BUFSIZE];

    bytes_sent = send(sockfd, usr_name_S.c_str(), 100, 0); // both hardcoded to make simpler
    bytes_sent += send(sockfd, password_S.c_str(), 100, 0);

	recv(sockfd, buf, BUFSIZE, 0); // checking return msg

	string checks(buf);
	
	string cut;

	if (checks == "bads"){
		cut = "close";

		cout << "Error in username or password. Closeing connection.\n";
	}

	else{


		cout << "==============================================\n";  

		cout << "What would you like to do now?\n";
		cout << "The options are: Upload, Download, Delete, and Dir. ";
		cout << "Or enter 'exit' to exit.\n";

		cout << "File names with spaces are not currently supported. \n"; // work in progres

		cout << "Please enter one option at this time, further guidence on format will be provided later.\n";

		string opt;

		cin >> opt;
		
		do{ // loop until exit given


				if (opt == "exit" || opt == "Exit"){

					opt = "x";

					bytes_sent += send(sockfd, opt.c_str(), opt.size(), 0);
					
					// close connection

					break;

				}

				else if (opt == "Upload" || opt == "upload" || opt == "u" || opt == "U"){

					cout << "Upload selected. \n";

				

					opt = "u";

					bytes_sent = send(sockfd, opt.c_str(), opt.size(), 0);

					stat = upload(sockfd);

					if(stat < 0 || (bytes_sent != opt.size())){
						cout << "Error. \n";
					}


				}

				else if (opt == "Download" || opt == "download" || opt == "d" || opt == "D"){

					cout << "Download selected. \n";

					
					opt = "d";

					bytes_sent = send(sockfd, opt.c_str(), opt.size(), 0);

					stat = download(sockfd);

					

					if(stat < 0 || (bytes_sent != opt.size())){
						cout << "Error. \n";
					}
				}

				else if (opt == "Delete" || opt == "delete" || opt == "del" || opt == "Del"){
					cout << "Delete selected. \n";

					opt = "r";

					bytes_sent = send(sockfd, opt.c_str(), opt.size(), 0);

					stat = delete_file_remote(sockfd);

					if(stat < 0|| (bytes_sent != opt.size())){
						cout << "Error. \n";
					}

				}

				else if (opt == "Dir"|| opt == "dir"){
					cout << "Dir selected. \n";

					opt = "i";

					bytes_sent = send(sockfd, opt.c_str(), opt.size(), 0);

					stat = dir_of_remote(sockfd, client_int);

					if(stat < 0|| (bytes_sent != opt.size())){
						cout << "Error. \n";
					}

				}

				else if (opt == "C")
				{
					cout << "Error in username or password. Closeing connection.\n";
					cut = "close";
				}

				else {

					cout << "Please enter a correct option. Thank you.\n";
				}



			// loop for user input
			cout << "==============================================\n";  

			cout << "What would you like to do now?\n";
			cout << "The options are: Upload, Download, Delete, and Dir. ";
			cout << "Or enter h for more guidence.\n";

			cout << "Please enter one option at this time, further guidence on format will be provided later.\n";

			cin >> opt;

		}while(opt != "x" || opt != "exit" || opt != "Exit" || cut != "close");

	}
    
    close(sockfd);
    return 0;
}
