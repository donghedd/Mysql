#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#include<cstdio>
#include<string>
#include<stack>
#include<queue>
#include<set>
#include<fstream> 
using namespace std;
void ShowDatabases() {
	FILE* fp = fopen("C:/mysql/files/all.txt", "r");
	if (fp == NULL) {
		perror("");
		return;
	}
	char text;
	int cnt = 0;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|                                        Databases                                       |" << endl;
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