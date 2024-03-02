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


	FILE* fin = fopen("C:/mysql/files/all.txt", "a");
	if (fin == NULL) {
		perror("");
		return;
	}

	string file = "C:/mysql/files/" + string(NewDatabase).substr(1);
	if (_mkdir(file.c_str()) != 0) {
		perror("Error creating directory");
		return;
	}
	

	string p = "C:/mysql/files/" + string(NewDatabase).substr(1) + "/authority.txt";
	ofstream fp(p, ios::out);
	if (!fp.is_open()) {
		perror("");
		return;
	}
	fp << "206908";
	fp.close();
	cout << "Successfully created" << NewDatabase;
	NewDatabase[0] = '\n';
	fputs(NewDatabase, fin);
	fclose(fin);
	return;
}