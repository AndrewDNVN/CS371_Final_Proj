//this is the del function for the client side it is split out to make debugging easier 
// and to make each file smaller and easier to work with

int delete_file_remote(int sockfd){ //working

		int bytes_sent = 0, bytes_recevied = 0;

		string file_name;

		cout << "Please enter the name of the file you would like to delete.\n";

		cin >> file_name;

		bytes_sent = send(sockfd, file_name.c_str(), file_name.size(), 0);

		char buf[BUFSIZE];

		read(sockfd, buf, BUFSIZE);


		return 1;
	}