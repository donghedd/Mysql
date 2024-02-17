#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include <iomanip>
using namespace std;
extern string Database;

void insert() {
	string table ,value, text, tt;
	cin >> table >> value;
	value = value.substr(6, value.size() - 7);
	if (Database == "\0") {
		cout << "Error, please select database";
		return;
	}
	string position = "C:/mysql/files/" + Database + '/' + table + "/value.txt";
	ofstream fp(position, ios::app);
	//FILE* fp = fopen(position.c_str(), "a");
	if (!fp.is_open()) {
		perror("");
		return;
	}

	value.erase(remove(value.begin(), value.end(), '('), value.end());
	stringstream ss(value);
	char delimiter = ')';
	while (getline(ss, text, delimiter)) {
		//text = text.substr(1, text.size());
		text.erase(remove(text.begin(), text.end(), '\''), text.end());
		fp << endl;
		stringstream st(text);
		while (getline(st, tt, ',')) {
			if (tt == "")continue;
			fp << setw(20) << left << tt;
			//fprintf(fp, "%-20s", tt);
		}
	}
	fp.close();
	cout << "Add successfully";
}
//insert into aa values(1,'qiang',100.0),(2,'xioaqiang',99.9); 
//1,qiang,100.0),2,xioaqiang,99.9)