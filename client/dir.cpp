//used to make main smaller

//dir.cpp

int dir_of_remote(int sockfd, struct log client_int[]){

		int num_of_file = 0, sent, rec;

		string gd_msg = "success";
		string bd_msg = "failure";

		char buf[BUFSIZE];
		//bzero(buf, BUFSIZE);

		rec = recv(sockfd, buf, BUFSIZE, 0); //num of files

		num_of_file = atoi(buf);
		//taking in number of files

		cout << num_of_file << endl;

		//bzero(buf, BUFSIZE);

		write(sockfd, gd_msg.c_str(), BUFSIZE); // sending ack

		for(int i = 0; i < num_of_file; i++){

			read(sockfd, buf, 100); // wait for ack

			string temp(buf);

			cout << "#" << i << ": " << temp << endl;	// print log

			write(sockfd, gd_msg.c_str(), 7);// send good

		}


		return 1;
}