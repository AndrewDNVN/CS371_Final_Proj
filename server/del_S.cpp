//Used to make smaller

int del_file(int sockfd, struct log_server server_int[]){ //working
//need to update server log

	char buf[BUFSIZE];

	bzero(buf, BUFSIZE);

	read(sockfd, buf, BUFSIZE);

	string new_file_name(buf);


	if (remove(new_file_name.c_str()) == 0) {

		string cp_g = new_file_name + " was deleted. \n";

		int bytes_sent = send(sockfd, cp_g.c_str(), cp_g.size(), 0);

		cout << cp_g; 

		bzero(buf, BUFSIZE);

		for(int i = 0; i < number_of_files; i++){

			if(new_file_name == server_int[i].file_name){

					server_int[i].file_name = "removed";

				}

			}

		  number_of_files = number_of_files -1;

		  return 1;
	}

   else{

	   	string cp_b = new_file_name + " was not deleted. \n";
	   		
	   	int bytes_sent = send(sockfd, cp_b.c_str(), cp_b.size(), 0);
		
	    cout << cp_b; 

	    bzero(buf, BUFSIZE);

	    return -1;
   }

   return -1; // incase of weird

}