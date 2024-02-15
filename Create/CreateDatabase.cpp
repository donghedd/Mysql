#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#include<cstdio>
#include<string>
#include<stack>
#include<queue>
#include<set>
#include<direct.h>
#include<fstream>
using namespace std;
void CreateDatabase() {
	char NewDatabase[90] = { '\0' };
	scanf("%[^;];", NewDatabase);

	//ofstream fin("C: / Users / 86166 / Desktop / mysql / files / all.txt", ios::app);

	FILE* fin = fopen("C:/Users/86166/Desktop/mysql/files/all.txt", "a");
	if (fin == NULL) {
		perror("");
		return;
	}

	//char text;
	//int i = 0, j = 0, flag = 0;
	//while (text = fgetc(fin)) {
	//	if ((flag == 0 || flag == 2) && NewDatabase[0] == text) {
	//		for (int i = 1; i < strlen(NewDatabase); i++) {
	//			text = fgetc(fin);
	//			if (text == '\n')
	//			{
	//				flag = 2;
	//				break;
	//			}
	//			if (NewDatabase[i] != text) {
	//				flag = 1;
	//				break;
	//			}
	//		}
	//		text = fgetc(fin);
	//		if (flag == 0 && (text == '\n' || text == -1 || text == EOF)) {
	//			flag = 3;
	//			break;
	//		}
	//	}
	//	else flag = 1;
	//	if (text == '\n')flag = 0;
	//	if (text == EOF) {
	//		flag = 0;
	//		break;
	//	}
	//}
	//if (flag == 3) {
	//	cout <<
	//}

	string file = "C:/Users/86166/Desktop/mysql/files/" + string(NewDatabase).substr(1);
	if (_mkdir(file.c_str()) != 0) {
		perror("Error creating directory");
		return;
	}
	cout << "Successfully created" << NewDatabase;
	NewDatabase[0] = '\n';
	fputs(NewDatabase, fin);
	fclose(fin);
	return;
}