//this is the download function for the client side it is split out to make debugging easier 
// and to make each file smaller and easier to work with

int download(int sockfd){ // intermittent issues

	cout << "Please enter the name of the file you wish to download." << endl;
	string file_name;

	cin >> file_name;

	//setting timer after user inputs

	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	using chrono::duration;
	using chrono::milliseconds;

	auto t1 = high_resolution_clock::now();


	// Send file name to server
	send(sockfd, file_name.c_str(), file_name.size(), 0);

	// Recv response from server

	char buf[BUFSIZE];

	read(sockfd, buf, 10);

	string temp(buf);

	//cout << temp << endl;

	bzero(buf, BUFSIZE);

	if(temp == "1"){

		cout << "File does not exist or other error. Returning." << endl;
		return -1;

	}

	else{

		// Time for file size

		//opening file on client

		FILE *fd = fopen(file_name.c_str(), "w");

		cout << "\nOpened file waiting for data\n";

		//taking in file size

		recv(sockfd, buf, BUFSIZE, 0);

		int file_size = atoi(buf);



		//bzero(buf, BUFSIZE);

		cout << file_size << " :size of file."<<endl;

		if(file_size <= 0){

			// Error

			cout << "File size is incorrect / small. Returning." << endl;
			string cp_b = "failure";

			send(sockfd, cp_b.c_str(), cp_b.size(), 0);

			fclose(fd);

			bzero(buf, BUFSIZE);

			return -1;

			}

			//Sending success
			string cp_g = "success";

			send(sockfd, cp_g.c_str(), cp_g.size(), 0);

			int remaining_Data = file_size;

			ssize_t len;

			fstream f;
         	f.open("down.csv",fstream::out);

         	auto i = 0; auto x = 0; double j = 0.0;

        	 long count = 1;

          	f << file_name << "Format: bits per second : Timeline number: "<< BUFSIZE <<"\n";

          	auto t4 = high_resolution_clock::now();

			while((remaining_Data > 0 ) && (len = read(sockfd, buf, BUFSIZE))){

				auto t5 = high_resolution_clock::now();
				
				fwrite(buf, sizeof(char), len, fd);
				
				cout << "Data read " << len << ". Still waiting for: " << remaining_Data << ".\n";
				remaining_Data -=len;
   			
	            auto t6 = high_resolution_clock::now();

	            auto micro_int_TL = duration_cast<milliseconds>(t5 - t4);

	            auto micro_int_math = duration_cast<milliseconds>(t6 - t5);

	            x = micro_int_math.count(); 

	            i = micro_int_TL.count();
           
		            if(count % 250 == 0 && (x != 0) && ((len / 8) != 0)){ // shrinks checks

		               j = ((len / 8) / x); // bytes per millisecond sent
		                  
		                // calcs amount data sent by the time in bits in 

		               if(j != 0){

			               f << (j/1000) << " " << i << ", "; //pushing items into file

			               //Format: bits per milisecond sent : bits per second sent : calc number : Timeline number

			               cout << "Data rate (BUFSIZE): " << j << endl;
		            }

		               // first item is rate and second item is the time in seconds

		            } //prints a csv with the time for sending paired with the size of the buffer that it sends
              
              count++;

			}

			auto t2 = high_resolution_clock::now();

				 /* Getting number of milliseconds as an integer. */
	    	auto ms_int = duration_cast<milliseconds>(t2 - t1);

	    	cout << ms_int.count() << " milliseconds total.\n";

	    	f.close();


			fclose(fd);

			bzero(buf, BUFSIZE);
			return 1;

		}


		//failsafe

		bzero(buf, BUFSIZE);
		return -1;

}
