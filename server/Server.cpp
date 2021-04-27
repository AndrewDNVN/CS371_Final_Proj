//Written by Andrew Donovan

#include "server.h"

#include "login.cpp" //wprking // Extra credit

#include "upload_S.cpp"//working
#include "del_S.cpp"//working

#include "download_S.cpp" //seems to be working
#include "stats_S.cpp" // working


int main(int argc, char *argv[])
{
//   Loops to continually listen and accept
     while(true)
     {
	     int sockfd, newsockfd, portno;
	     socklen_t clilen;
	     char buffer[256];
	     struct sockaddr_in serv_addr, cli_addr;
	     int n;
	//   Checks to see if correct number of command line arguments
	     if (argc < 2) {
	        cout << "ERROR, no port provided :: Exiting with status -1\n";
	         exit(-1);
	     }
	//   Opens a socket
	     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	     if (sockfd < 0) {
		
			cout<<"ERROR opening socket:: Exiting with status -1\n";
			exit(-1);
		}
	    cout << "Socket created.\n";
	     
	     bzero((char *) &serv_addr, sizeof(serv_addr));
	     portno = atoi(argv[1]);
	     serv_addr.sin_family = AF_INET;
	     serv_addr.sin_addr.s_addr = INADDR_ANY;
	     serv_addr.sin_port = htons(portno);

	//   Binds 
	     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	            cout<< "ERROR on binding:: Exiting with status -1 \n";
	       //exit(-1);
	      }
	     cout << "Bind completed\n";

		int byte_recevied = 0, bytes_sent = 0, total_bytes_rec = 0, total_bytes_sent = 0;

		int stat = 0;

	//Listens for the client to connect
		 printf("Waiting for incoming connection from a client...\n");
	         listen(sockfd,5);
	         clilen = sizeof(cli_addr);

	//Accepts the client
	         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,  &clilen);
	         if (newsockfd < 0){
	          cout << "ERROR on accept:: closeing current socket and resuming listening. \n";
	      }

	// checking username and password


		cout << "==================================================\n";	 \
		cout << "Receciving username and password from client. \n";

		char usr_name_buf[100];
		char password_buf[100];

		byte_recevied = read(newsockfd, usr_name_buf, 100);

		byte_recevied += read(newsockfd, password_buf, 100);


		string usr_g = "good"; // meaning username and password are good
		string usr_b = "bads"; // not good

		stat = login(string(usr_name_buf),string(password_buf)); // doing the checking

		if (stat == -1){
			send(newsockfd, usr_b.c_str(), usr_b.size(), 0);

		}

	
		else{
			
			send(newsockfd, usr_g.c_str(), usr_g.size(), 0); // sending all good msg

			cout << "Login == Success.\n";

			    char buf_opt[100]; // choose something large enough to deal with errors.
			    bzero(buf_opt, 100);
			    // opt codes: u = upload; d =download; r = delete; i = diretory
			    // opt codes: x = close connection

			    byte_recevied += read(newsockfd, buf_opt, 100);

			    //cout << "Char buf Recvied: " << buf_opt << "\n"; //testing connenction

			    string opt(buf_opt); // converting back to string

			    cout << opt << " temp"<<endl;

			    //cout << "String Conversion: "<< opt << "\n"; // testing conversion

			    //hold connection until break

			  //cout << opt << "\n";

			    if(stat == -1) // not the cleanist but workable
			    	opt == "x";

			    struct log_server server_int[NUM_OF_LOG];
			    //^ building out an array of files and there data to be passed


			do{

					    
			    if(opt == "u"){
					
					cout << "==================================================\n";
			    	cout << "Uploading::\n";

			    	stat = upload_file(newsockfd, server_int);

			    	if (stat < 0)
			    		cout << "Error:: upload\n";

			    }
			    else if (opt == "d"){

			    	cout << "==================================================\n";
			    	cout << "Downloading::\n";

			    	stat = download_file(newsockfd, server_int);

			    	if (stat < 0)
			    		cout << "Error:: download\n";

			    }
			    	
			    else if (opt == "r"){
			    	cout << "==================================================\n";
			    	cout << "Removing::\n";

			    	stat = del_file(newsockfd, server_int);

			    	if (stat < 0)
			    		cout << "Error:: del\n";

			    }

			    else if (opt == "i"){
			    	cout << "==================================================\n";
			    	cout << "Indexing::\n";

			    	stat = stats_dir(newsockfd, server_int);

			    	//read(newsockfd, buf_opt, 100);

			    	if (stat < 0)
			    		cout << "Error:: dir\n";

			    }

			    else if (opt == "x"){
			    	cout << "==================================================\n";
			    	cout << "Exiting:: \n";

			    	cout << "Connection closed by client. \n";
			    }
			 

			    else{

			    	//cout << "Transmission error.\n";
			    	//break;
			    	//this is due to trash on the connection that I cannot seem to clear
			    }


			    bzero(buf_opt, 100);

			    byte_recevied = read(newsockfd, buf_opt, 100);

			    opt = buf_opt[0];

			}while (opt != "x");

		}


	//       Closes Socket
	cout << "==================================================\n";
	cout << "Current connection closed.\n";

			 close(newsockfd);
	         close(sockfd);
	}
     return 0; 
}