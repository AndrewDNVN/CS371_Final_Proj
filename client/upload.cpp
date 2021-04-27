int upload(int sockfd){ // working

		
		int bytes_sent = 0, bytes_recevied = 0;
		int remaingdata = 0;

		char file_size[256];

		string file_name;

		cout << "Please enter the name of the file you would like to upload.\n";

		cin >> file_name;

		//Sending file name

		bytes_sent = send(sockfd, file_name.c_str(), file_name.size(), 0);

		char buf[BUFSIZE];

      using chrono::high_resolution_clock;
   using chrono::duration_cast;
   using chrono::duration;
   using chrono::milliseconds;

   auto t1 = high_resolution_clock::now();

		//Reading out error messge / success

		read(sockfd, buf, BUFSIZE);

		string temp(buf);

		//cout << temp; // catching failures

		int fd = open(file_name.c_str(), O_RDONLY);

   		struct stat stat_buf;

   		// Getting stats about the file

   		fstat(fd, &stat_buf);

   		sprintf(file_size, "%ld", stat_buf.st_size);

   		//Sending size of file

   		size_t len = send(sockfd, file_size, sizeof(file_size), 0);

   		remaingdata = stat_buf.st_size;

   		// Receive go ahead

   		read(sockfd, buf, BUFSIZE);

   		string tempA(buf);

   		//cout << tempA <<"\n";

   		if(tempA == "File size incorrect"){
   			cout << "Error in sending file size\n";
   			return -1;
   		}


   		// looping to send file

   		off_t offset = 0;

         fstream f;
         f.open("up.csv",fstream::out);

         // f << file_name << "\n";

         

         auto i = 0; auto x = 0; double j = 0.0;

         long count = 1;

         f << file_name << "Format: bits per second : Timeline number: "<< " "<< BUFSIZE <<"\n";

         auto t4 = high_resolution_clock::now();

   		while(((bytes_sent = sendfile(sockfd, fd, &offset, BUFSIZE)) > 0) && (remaingdata > 0))
   		{
            auto t5 = high_resolution_clock::now();
   			cout << "Data sent " << bytes_sent << ". Still sending " << remaingdata << ".\n";
   			remaingdata -= bytes_sent;

            auto t6 = high_resolution_clock::now();

            auto micro_int_TL = duration_cast<milliseconds>(t5 - t4);

            auto micro_int_math = duration_cast<milliseconds>(t6 - t5);

            x = micro_int_math.count(); 

            i = micro_int_TL.count();
           
            if(count % 250 == 0 && (x != 0) && ((bytes_sent / 8) != 0)){ // shrinks checks

               j = ((bytes_sent / 8) / x); // bytes per millisecond sent
                  
                // calcs amount data sent by the time in bits in 

               if(j != 0){

               f << (j/1000) << " " << i << ", "; //pushing items into file

               //Format: bits per second : Timeline number

               cout << "Data rate (BUFSIZE): " << j << endl;
            }

               // first item is rate and second item is the time in seconds

            } //prints a csv with the time for sending paired with the size of the buffer that it sends
              
              count++;

   		}

		 cout << "bytes sent "<< stat_buf.st_size << ": file sent\n";

         auto t3 = high_resolution_clock::now();

             /* Getting number of milliseconds as an integer. */
         auto ms_int = duration_cast<milliseconds>(t3 - t1);

         cout << ms_int.count() << " milliseconds total\n";

         f.close();

		close(fd);

		return 1;
	}
