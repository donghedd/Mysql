#include<iostream>
#include<fstream>
#include<string>
using namespace std;
extern string password;
extern string Database;
int judge() {
	string p = "C:/mysql/files/authority/information/" + password + ".txt";
	ifstream fp(p, ios::in);
	if (!fp.is_open()) {
		perror("");
		return 0;
	}
	string text;
	while (getline(fp, text)) {
		if (text == Database)return 1;
	}
	cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
	return 0;
}