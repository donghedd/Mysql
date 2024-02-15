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
#include <iomanip>
#include <Windows.h>
using namespace std;
int use(char* NewDatabase);
extern string Database;
map < string,pair< string,string >  > dictionary = {
	{"int,", {"yes","int"}}, 
	{"char,", {"yes","char"}},
	{"float,", {"yes","float"}},
	{"primary", {"primary"," "}}
};
map<string, int>match;
struct Header{
	string type, name;
}header[100];

void CreateTable() {
	string table;
	cin >> table;
	table = table.substr(0, table.size() - 1);
	scanf("(\n");
	string ch, primary;
	char name[20], type[30];
	int flag = 0, idx, cnt = 0;

	
	//建表
	while (cnt++ <100) {
		cin >> name >> type;
		if (dictionary[type].first == "yes") {
			match[name] = cnt;
			header[cnt].name = name;
			strcpy(type, dictionary[type].second.c_str());
			header[cnt].type = type;
		}
		else if (name == dictionary[name].first) {
			char pr[20];
			for (int i = 4; ; i++) {
				if (type[i] == ')') {
					pr[i - 4] = '\0';
					break;
				}
				pr[i - 4] = type[i];
			}
			primary = string(pr);
			break;
		}
		else flag = 2;
	}

	//检查
	{
		if (flag == 2 || cnt == 100) {
			cout << "Error, please check the input";
			return;
		}
		if (Database == "\0") {
			cout << "Error, please select database";
			return;
		}

		if (match[primary] == 0) {
			cout << "Error, the name referred to by primary was not found in the table header";
			return;
		}
	}

	//创建文件夹
	//string file = "C:/Users/86166/Desktop/mysql/files/ kk/dd";
	string file = "C:/Users/86166/Desktop/mysql/files/"+Database +'/' + table;
	if (_mkdir(file.c_str())) {
		perror("Error creating directory");
		return;
	}
	//string command;
	//command = "mkdir -p " + file;
	//system(command.c_str());

	//创建文件， 存放表头
	string position = "C:/Users/86166/Desktop/mysql/files/" + Database + '/' + table +"/" + "header.txt";
	const char* charposition = position.c_str();
	//FILE* fp = fopen(charposition, "w");
	ofstream fp(charposition);
	if (!fp.is_open()) {
		perror("");
		return;
	}

	//写入表头
	const char* charPrimary = primary.c_str();
	//fprintf(fp, "%-20s\t%-6s", primary, header[match[primary]].type);
	fp << setw(20) << left << primary << header[match[primary]].type;
	for (int i = 1; i < cnt; i++) {
		if (i == match[primary])continue;
		//fprintf(fp, "\n%-20s\t%-6s", header[i].name, header[i].type);
		fp << endl << setw(20) << left << header[i].name << header[i].type;
	}
	fp.close();

	//创建文件， 存放数据
	string p = "C:/Users/86166/Desktop/mysql/files/" + Database + '/' + table + "/" + "value.txt";
	//FILE* fout = fopen(p.c_str(), "w");
	ofstream fout(p.c_str());
	if (!fout.is_open()) {
		perror("");
		return;
	}

	//写入首行
	//fprintf(fout, "%-20s\t%-6s", primary, header[match[primary]].type);
	fout << setw(20) << left << primary;
	for (int i = 1; i < cnt; i++) {
		if (i == match[primary])continue;
		//fprintf(fout, "\n%-20s\t%-6s", header[i].name, header[i].type);
		fout << setw(20) << left << header[i].name ;
	}
	fout.close();

	//表目录
	string tfile = "C:/Users/86166/Desktop/mysql/files/" + Database + "/" + "tables.txt";

	flag = 0;
	//如果原来不存在
	{
		FILE* fin = fopen(tfile.c_str(), "r");
		if (fin != NULL) {
			flag = 0;
			fclose(fin);
		}
		else flag = 1;
		
	}

	FILE* fin = fopen(tfile.c_str(), "a");
	if (fin == NULL) {
		perror("");
		return;
	}
	if (flag == 1)fputs(table.c_str(), fin);
	else fprintf(fin, "\n%s", table.c_str());
	fclose(fin);
	cout << "Successfully created " << table;
	return;
}
//create table aa(
//	name char,
//	num int,
//	score float,
//	primary key(num));

