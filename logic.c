

int popCorn(int* time){

	time[0] = 0;
	time[1] = 0;
	time[2] = 1;
	time[3] = 0;

	return 	0;
}

int timeDecrement(int* time){
	if(time[0] != 0){
      time[0]--;
      return 1;
	}
	else if(time[1] != 0){
		time[1]--;
		time[0] = 9;
		return 1;
	}
	else if(time [2] != 0){
		time[2]--;
		time[1] = 5;
		time[0] = 9;
		return 1;
	}
	else if(time [3] != 0){
		time[3]--;
		time[2] = 9;
		time[1] = 5;
		time[0] = 9;
        return 1;
	}
	return 0;
}

void timeToAscii(char* time){
	time[0] = time[0] + 48;
	time[1] = time[1] + 48;
	time[3] = time[3] + 48;
	time[4] = time[4] + 48;
}

