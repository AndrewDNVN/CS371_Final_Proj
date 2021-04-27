//Used to make main smaller

//download_S.cpp


int download_file(int sockfd, struct log_server server_int[]){ // itermittent issues

	char buf [BUFSIZE];
	bzero(buf, BUFSIZE);

	int remaining_data = 0;
	char file_size[256]; // done to hold more info in a managable format

	//take in name
	recv(sockfd, buf, BUFSIZE, 0);

	//Check if file exsists

	string file_name(buf);

	cout << file_name;

	//printing file name for records

	for(int i = 0; i < number_of_files; i++){

		//checking if file exsists in this session

		if(file_name == server_int[i].file_name){

			//means that the file is in the log struct

			int fd = open(file_name.c_str(), O_RDONLY);

				// Success msg sent
			string cp_g = "0";

			//cout << cp_g << endl;

			write(sockfd, cp_g.c_str(), 10);

			cout << " sent good\n";

			// Prep sending size of file

			struct stat stat_buf;

			// Define the stats of the file

			fstat(fd, &stat_buf);

			
			//bzero(file_size, BUFSIZE);

			sprintf(file_size, "%ld", stat_buf.st_size); // not the cleanist

	   		//Sending size of file

	   		send(sockfd, file_size, sizeof(file_size), 0);

	   		cout << file_size << " sent file_size\n";

	   		//Error found here 
	   		

	   		//Prep for sending rest of file

	   		remaining_data = stat_buf.st_size;

	  		// read in file size erros msg

	  		recv(sockfd, buf, BUFSIZE, 0);

	  		string tempA(buf);

	  		cout << tempA << " ack \n" <<  endl;

	  		if(buf == "failure"){
	  			cout << "Failure in sending file size.\n";

	  			bzero(buf, BUFSIZE);

	  			close(fd);
	  			return -1;

	  		}

	  		else{

		  		off_t offset = 0;
		  		int bytes_sent = 0;

		   		while(((bytes_sent = sendfile(sockfd, fd, &offset, BUFSIZE)) > 0) && (remaining_data > 0))
		   		{

		   			//cout << "Data sent " << bytes_sent << ". Still sending " << remaining_data << ".\n";
		   			remaining_data -= bytes_sent;

		   			//keeping log for debugging and detail

		   		}

		   		server_int[i].num_downloads = server_int[i].num_downloads +1;
		   		//updating download info

				cout << " :file sent\n";

				close(fd);

				bzero(buf, BUFSIZE);

				return 1;

				//break out of the loop

	  		}

		}
	}
		//setting up error messge to return failure
		// in this case the file was not in the log

		string cp_b = "failure";

		cout << cp_b << endl;

		send(sockfd, cp_b.c_str(), cp_b.size(), 0);

		bzero(buf, BUFSIZE);
		return -1;

		

}
