#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <istream>
#include <map>

using namespace std;




struct stateObj{
	bool accept;
	map<char, int> transition;
};

void quit(map<int, stateObj*> states){
	states.erase(states.begin(), states.end());
	exit(1);
}

int main(int argc, char *argv[]){
	vector<char> alphabet;//E, Alphabet
	int qZero;//q0, Starting state
	ifstream file (argv[1]);
	map<int, stateObj*> states;	

	bool check = true;;
	int x = 0;
	while(check){           //Reads first line         
		file >> x;
		stateObj *newState = new stateObj;
		states[x] = newState;
		if(file.peek() == '\n'){
			check = false;
		}
	}

	check = true;
	char y;
	while(check){			//Reads second line
		file >> y;
		alphabet.push_back(y); //Keeps track of alphabet for error checking user input
		if(file.peek() == '\n'){
			check = false;
		}
	}

	file >> qZero; 		     //Reads third line

	check = true;
	while(check){           //Reads fourth line 
		file >> x;
		states[x]->accept = true;         
		if(file.peek() == '\n'){
			check = false;
		}
	}
	
	cout << "q0 = " << qZero;
	if(states[qZero]->accept){
		cout << "*" << endl;
	}
	else{
		cout << endl;
	}

	int z;	
	check = true;
	while(check){         //Reads fifth line
		file >> x;
		cout << x << ",";
		file >> y;
		cout << y << " -> ";
		file >> z;
		cout << z;
		if(states[z]->accept){
			cout << "*" << endl;
		}
		else{
			cout << endl;
		}
		states[x]->transition[y] = z; //Adds transition to the map of the struct
		if(file.peek() == EOF){
			check = false;
		}
	}
	
	cout << "Enter a stringer to check" << endl;	
	string user;
	vector<char> input;
	int st;
	while(getline(cin, user)){ //Takes user input
		st = qZero;
		for(int i = 0; i<user.size(); i++){
			if(&user[i] != " "){
				input.push_back(user[i]); //puts user input into vector. removes whitespace
			}
		}
		int error = 0;
		for(int i = 0; i<input.size(); i++){
			for(int j = 0; j<alphabet.size(); j++){ //Checks user input against alphabet.
				if(input[i]==alphabet[j]){
					error++;
				}
			}
		}
		if(error != input.size()){
			cerr << "User input contains character not in alphabet" << endl;
			quit(states);
		}
		cout << st;
		if(states[st]->accept){
			cout << "*";
		}
		for(int i = 0; i<input.size(); i++){ 
			st = states[st]->transition[input[i]]; //This line moves through the states
			cout << " -> " << st;            
        	if(states[st]->accept){
        		cout << "*";
        	}
		}
		cout << endl;
		if(states[st]->accept){ //If the ending state is accepting it is accepted.
			cout << "Accepted" << endl;
		}
		else{
			cout << "Rejected" << endl;
		}
		cout << "=====================" << endl;
		input.clear();
	}

	quit(states);//Frees memory
	return 0;
}





