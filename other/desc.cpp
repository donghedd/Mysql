#include<iostream>
#include<string>
#include<fstream>
using namespace std;
extern string Database;
void desc() {
	string table;
	cin >> table;
	table = table.substr(0, table.size() - 1);
	string position = "C:/mysql/files/" + Database + '/' + table + "/header.txt";
	ifstream fp(position, ios::in);
	if (!fp.is_open()) {
		perror("");
		return;
	}
	string text;
	int cnt = 0;
	while (getline(fp, text)) {
		if (cnt++ == 0)cout << text;
		else cout << endl << text;
	}
	fp.close();
}