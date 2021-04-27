//used to make smaller 

//upload_s


int upload_file(int sockfd, struct log_server server_int[]){ //working

	char buf[BUFSIZE];

	int file_size, remaingData;

	bzero(buf, BUFSIZE);

	//Reading File name

	read(sockfd, buf, BUFSIZE); 
	
	string new_file_name(buf);

	FILE *fd = fopen(buf, "w");

	if(fd == NULL){

		string cp_b = new_file_name + " file failed to create.\n"; // error messge back to client


	    cout << cp_b; //local output for debugging

	    // sending fail messege

	    int bytes_sent = send(sockfd, cp_b.c_str(), cp_b.size(), 0);

	    return -1;

	}

	else{

		string cp_g = new_file_name + " file created.\n"; //updating the client

		cout << cp_g;
		
		// sending success messege

		int bytes_sent = send(sockfd, cp_g.c_str(), cp_g.size(), 0);

		/// File receiving time

		// File size

		recv(sockfd, buf, BUFSIZE, 0);

		file_size  = atoi(buf);

		//cout << "File size : %d\n", file_size; // for debugging

		if(file_size == 0){

			string fs_b = "failure";

			send(sockfd, fs_b.c_str(), fs_b.size(), 0);

			fclose(fd);

			return -1;
		}


		string fs_g = "success";

		send(sockfd, fs_g.c_str(), fs_g.size(), 0);

		remaingData = file_size;

		//Updating the log structure

		server_int[number_of_files].file_name = new_file_name;
		//taking in the file name
		server_int[number_of_files].file_size = remaingData;
		//taking in remaing data

		time_t t = time(NULL);
	  	struct tm tm = *localtime(&t);
	  	char time[256];
	  	sprintf(time, "now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	  	string temp(time);

		server_int[number_of_files].date_time = temp;

		//cout << temp << endl;

		//time is hard

		server_int[number_of_files].num_downloads = 0;
		//new file not downloaded yet: set to zero

		number_of_files = number_of_files + 1;
		//setting to next file

		//done updating the log

		// Looping to take in data

		ssize_t len;

		while((remaingData > 0 ) && (len = read(sockfd, buf, BUFSIZE))){

			fwrite(buf, sizeof(char), len, fd);
			remaingData -=len;

	}

	fclose(fd);

	bzero(buf, BUFSIZE);

	return 1;

	}
	
}