//Used to make main smaller

//Stats_S.cpp


int stats_dir(int sockfd, struct log_server server_int[]){ //not working

	if(number_of_files == 0){
		cout << " Error in number of files.\n";
		return -1;
	}

	cout << "The log currnetly contains " << number_of_files << ".\n";
	cout << "Printing out contents." << endl;
	cout << "--------------------------------------------------\n";

	string temp_num_f;

	int sent = 0, rec =0;

	temp_num_f = to_string(number_of_files);

	sent = send(sockfd, temp_num_f.c_str(), sizeof(temp_num_f), 0); // sending number of files

	char buf[BUFSIZE];
	char msg[7];
	//bzero(buf, BUFSIZE);

	read(sockfd, buf, BUFSIZE); //read in ack from number of files

	//string ack1(buf);

	//cout << ack1 << endl; //testing

	for(int i = 0; i < number_of_files; i++){

		string temp_size = to_string(server_int[i].file_size);
		string temp_down = to_string(server_int[i].num_downloads);


		string send_log = server_int[i].file_name;
		send_log += " ";
		send_log += temp_size;
		send_log += " ";
		send_log += server_int[i].date_time;
		send_log += " ";
		send_log += temp_down; // this is ugly but ....

		cout << "#" << i << ": " << send_log << endl;

		send(sockfd, send_log.c_str(), 100, 0); // send log info to client

		read(sockfd, msg, 7); // wait for ack

	}

	cout << "--------------------------------------------------\n";


	return 1;
}