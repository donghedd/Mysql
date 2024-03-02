#include<iostream>
using namespace std;
extern string Database;
void ShowTables() {
	if (Database == "\0") {
		cout << "Error, please select database";
		return;
	}
	string file = "C:/mysql/files/" + Database + "/tables.txt";
	FILE* fp = fopen(file.c_str(), "r");
	if (fp == NULL) {
		perror("");
		return;
	}
	char text;
	int cnt = 0;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|                                         Tables                                         |" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl << '|';
	while (text = fgetc(fp)) {
		if (text == '\n') {
			while (cnt != 88) {
				cout << ' ';
				cnt++;
			}
			cnt = 0;
			cout << '|' << endl << "------------------------------------------------------------------------------------------" << endl << '|';
		}
		else if (text == EOF)
		{
			while (cnt != 88) {
				cout << ' ';
				cnt++;
			}
			cout << '|' << endl << "------------------------------------------------------------------------------------------";
			break;
		}
		else
		{
			cnt++;
			cout << text;
		}
	}

	fclose(fp);
}