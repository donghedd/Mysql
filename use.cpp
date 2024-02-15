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
int use(char* NewDatabase) {
	char all[10][100];
	FILE* fp = fopen("C:/Users/86166/Desktop/mysql/files/all.txt", "r");
	if (fp == NULL) {
		perror("");
		return 4;
	}
	char text;
	int i = 0, j = 0, flag = 0;
	while (text = fgetc(fp)) {
		if ((flag == 0 || flag == 2) && NewDatabase[0] == text) {
			for (int i = 1; i < strlen(NewDatabase); i++) {
				text = fgetc(fp);
				if (text == '\n')
				{
					flag = 2;
					break;
				}
				if (NewDatabase[i] != text) {
					flag = 1;
					break;
				}
			}
			text = fgetc(fp);
			if (flag == 0 && (text == '\n' || text == -1 || text == EOF)) {
				flag = 3;
				break;
			}
		}
		else flag = 1;
		if (text == '\n')flag = 0;
		if (text == EOF) {
			flag = 0;
			break;
		}
	}
	fclose(fp);
	return flag;
}
//3  已存在
//4  未打开文件