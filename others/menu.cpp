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
string op, Table;
string Database;
int use(char* NewDatabase);
void ShowDatabases();
void CreateDatabase();
void CreateTable();
void ShowTables();
void insert();
void SelectAll();
void alter();
void SelectSection(string text);
void desc();
int authority();
void ChangeAuthority();
void alter();
void renamee();
void drop();
void update();
void deletee();
int judge();
int main() {
	cout << "Enter password: ";
	int t = authority();
	if (t == 1) {
		cout << "Welcome to the database operating system. (SQL)" << endl;
		cout << "The level of access you possess is the highest." << endl << endl;
	}
	else if (t == 2) {
		cout << "Welcome to the database operating system. (SQL)" << endl;
		cout << "You are authorized to modify and view the database." << endl << endl;
	}
	else if (t == 3) {
		cout << "Welcome to the database operating system. (SQL)" << endl;
		cout << "You can modify only some databases" << endl << endl;
	}
	else if (t == 4) {
		cout << "Welcome to the database operating system. (SQL)" << endl;
		cout << "You only have the right to view the database." << endl << endl;
	}
	else {
		cout << "Sorry, you are not authorized to access";
		return 0;
	}
	
	cout << "Due to the ability of the producer, the final result is inevitably not satisfactory," << endl;
	cout << "hoping you can put forward your valuable comments!" << endl<<endl;
	cout << "------------------------------------------------------------------------------------------"<<endl<<endl;
	cout << "Before using, please read the following carefully:" << endl;
	cout << "Commands end with; " << endl;
	//cout << "Type 'help; ' or '\\h' for help." << endl;
	cout << "Some other content in your use process I will slowly tell you, now please start!" << endl<<endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	while (1) {
		cout << endl << endl << "mysql> ";
		cin >> op;
		if (t <= 2 and op == "create") {//创建
			string text;
			cin >> text;
			if (text == "table") {
				CreateTable();
			}
			else if (text == "database") {
				CreateDatabase();
			}
			else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
		}
		else if (op == "use") {//选择数据库
			cin >> Database;
			Database = Database.substr(0, Database.size() - 1);
			char charDatabase[100];
			strcpy(charDatabase, Database.c_str());
			int k = use(charDatabase);
			if (k == 3) {
				cout << "Database changed;";
			}
			else if (k == 4) {
				Database.clear();
				continue;
			}
			else {
				Database.clear();
				cout << "Error, the database does not exist";
			}
		}
		else if (t <= 3 and op == "insert") {
			if (t == 3 && judge() == 0) {
				continue;
			}
			string text;
			cin >> text;
			insert();
		}
		else if (op == "select") {
			string text;
			cin >> text;
			if (text == "*") {
				SelectAll();
			}
			else SelectSection(text);
		}
		else if (op == "show") {//查看
			string text;
			cin >> text;
			if (text == "tables;") {
				ShowTables();
			}
			else if (text == "databases;") {
				ShowDatabases();
			}
			else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
		}
		else if (t <= 3 and op == "drop") {//删除
			if (t == 3 && judge() == 0) {
				continue;
			}
			drop();
		}
		else if (op == "desc") {
			desc();
		}
		else if (t <= 3 and op == "alter") {
			if (t == 3 && judge() == 0) {
				continue;
			}
			string table;
			cin >> table;
			alter();
		}
		else if (t <= 3 and op == "rename") {
			if (t == 3 && judge() == 0) {
				continue;
			}
			string table;
			cin >> table;
			renamee();
		}
		else if (t <= 3 and op == "update") {
			if (t == 3 && judge() == 0) {
				continue;
			}
			update();
		}
		else if (t <= 3 and op == "delete") {
			if (t == 3 && judge() == 0) {
				continue;
			}
			deletee();
		}
		else if (t == 1 and op == "authority") {
			ChangeAuthority();
		}
		else if (op == "exit") return 0;
		else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";

	}

}