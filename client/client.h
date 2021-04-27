
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <sstream>
#include <sys/stat.h>

#include <sys/stat.h>
#include <sys/types.h>


#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

const int BUFSIZE = 25;

//Used to set size of buffer

const int NUM_OF_LOG = 100;
//used to set max number of logs being tracked


using namespace std;

struct log{

	string file_name;

	int file_size = 0;
	
	string date_time;

	int num_downloads = 0;

};