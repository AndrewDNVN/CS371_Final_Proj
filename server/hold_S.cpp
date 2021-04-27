
		cout << server_int[i].file_name << " ";
		// send name
		send(sockfd, server_int[i].file_name.c_str(), sizeof(server_int[i].file_name.c_str()), 0); //sizeof(server_int[i].file_name.c_str())
		
		//cout << "file name sent \n";

		recv(sockfd, buf, 100, 0); //waiting for msg

		//cout << "file name ack recv\n";

		//cout << buf << endl; //error catching
		//zero(buf, BUFSIZE);

		cout << server_int[i].file_size << " ";

		//send size

		string temp_FS = to_string(server_int[i].file_size);

		send(sockfd, temp_FS.c_str(), sizeof(temp_FS) , 0);

		//cout << "sent file size\n";

		recv(sockfd, buf, 32, 0);

		//cout << "file size ack recv\n";
		//cout << buf << endl; //error catching

		//bzero(buf, BUFSIZE);

		//send date and time
		send(sockfd, server_int[i].date_time.c_str(), 24, 0); // hardcoded due to known format and size

		//cout << "sent file date and time\n";		

		recv(sockfd, buf, 8, 0);

		//cout << "file size ack recv\n";

		//bzero(buf, BUFSIZE);

		cout << server_int[i].date_time << " ";


		// send number of downloads

		string temp_num = to_string(server_int[i].num_downloads);

		send(sockfd, temp_num.c_str(), sizeof(temp_num) , 0);

		//cout << "sent file num downloads\n";	


		recv(sockfd, buf, 32, 0);

		//cout << "file num downloads ack \n";
		//cout << buf << endl; //error catching

		//bzero(buf, BUFSIZE);

		cout << server_int[i].num_downloads << " " << endl;

		//recv(sockfd, buf, BUFSIZE, 0);
		//take in all good msg
