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

int main(int argc, char *argv[]){
	vector<char> alphabet;//E, Alphabet
	int qZero;//q0, Starting state

	ifstream file (argv[1]);
	map<int, stateObj*> states;	

	bool check = true;;
	int x = 0;
	while(check){                    
		file >> x;
		cout << x << endl;
		stateObj *newState = new stateObj;
		states[x] = newState;
		if(file.peek() == '\n'){
			check = false;
		}
	}

	cout << "here" << endl;
	check = true;
	char y;
	while(check){
		file >> y;
		alphabet.push_back(y); //second line
		if(file.peek() == '\n'){
			check = false;
		}
	}

	file >> qZero; 		       //third line

	check = true;
	while(check){                    
		file >> x;
		states[x]->accept = true;         
		if(file.peek() == '\n'){
			check = false;
		}
	}
	
	cout << qZero;
	if(states[qZero]->accept){
		cout << "*" << endl;
	}
	else{
		cout << endl;
	}

	int z;	
	check = true;
	while(check){                   
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
		states[x]->transition[y] = z;// << endl;//->transition[y] = z;
		if(file.peek() == EOF){
			check = false;
		}
	}
	
	cout << "Enter a stringer to check" << endl;	
	string user;
	vector<char> input;
	int st;
	while(getline(cin, user)){
		st = qZero;
		for(int i = 0; i<user.size(); i++){
			if(&user[i] != " "){
				input.push_back(user[i]);
			}
		}
		cout << st;
		if(states[st]->accept){
			cout << "*";
		}
		for(int i = 0; i<input.size(); i++){
			st = states[st]->transition[input[i]];
			cout << " -> " << st;            
        	if(states[st]->accept){
        		cout << "*";
        	}
		}
		cout << endl;
		cout << "=====================" << endl;
		if(states[st]->accept){
			cout << "Accepted" << endl;
		}
		else{
			cout << "Rejected" << endl;
		}
		input.clear();
	}

	states.clear();
	return 0;
}





