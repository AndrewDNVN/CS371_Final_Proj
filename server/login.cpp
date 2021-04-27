//working

// to make main line server smaller

int login(string username, string password ){ //working
	// used to check login info 
	/*
		This is very unsecure.
	*/

	fstream f;

	int num_usrs;

	string usr, pass;

	f.open("password.txt");

	if (f.fail()){
		cout << "Error opening password.txt\n";
		f.close();
		return -1;
	}

	f >> num_usrs;

	for (int i = 0; i < num_usrs; i++){

		f >> usr >> pass;

		if((usr == username) && (password == pass)){
		
			f.close();
			return 1;		
		}

	}

	f.close();
	return -1;
}