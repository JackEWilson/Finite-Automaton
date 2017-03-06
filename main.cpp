#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <istream>

using namespace std;

int main(int argc, char *argv[]){
	vector<int> states;//Q, set of states
	vector<char> alphabet;//E, Alphabet
	int qZero;//q0, Starting state
	vector<int> accepting;//T, accepting states
//	string line5;// where transitiosn will be stored

	ifstream file (argv[1]);
	
	bool check = true;;
	int x = 0;
	while(check){                    
		file >> x;
		states.push_back(x); //first line
		if(file.peek() == '\n'){
			check = false;
		}
	}
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
		accepting.push_back(x); //fourth line
		if(file.peek() == '\n'){
			check = false;
		}
	}

	vector<int> p1;
	vector<char> p2;
	vector<int> p3;
	
	check = true;
	while(check){                   
		file >> x;         
		p1.push_back(x);
		file >> y;
		p2.push_back(y);
		file >> x;
		p3.push_back(x);
		if(file.peek() == EOF){
			check = false;
		}
	}

	for(int i = 0; i<p1.size(); i++){
		cout << p1[i];
		cout << p2[i];
		cout << p3[i] << endl;
	}
	
	int st = qZero;
	int iter = 0;
//	cout << alphabet.size() << endl;
	for(int i = 0; i<alphabet.size(); i++){
		for(int j = 0; j<p1.size(); j++){
			if(st == p1[j]){
				if(alphabet[i] == p2[j]){
					cout << alphabet[i] << endl;
					iter++;
					cout << iter << endl;
					st = p3[j];
					break;
				}
			}		 
		}
	}
	bool ace = false;
	for(int i = 0; i<accepting.size(); i++){
		if(st == accepting[i]){
			ace = true;
		}
	}
//	cout << iter << endl;
//	cout << alphabet.size() << endl;
	
	if(iter == alphabet.size() && ace){
		cout << "accepted" << endl;
	}

	return 0;
}





