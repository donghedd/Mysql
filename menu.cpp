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
void help();
void ShowDatabases();
void CreateDatabase();
void CreateTable();
void ShowTables();
void insert();
void SelectAll();
int main() {
	/*cout << "Enter password: ";
	string password;
	cin >> password;
	if (password != "206908") {
		cout << "Password Error"<<endl;
		return 0;
	}
	cout << "Welcome to the database operating system. (SQL)" << endl;
	cout << "Due to the ability of the producer, the final result is inevitably not satisfactory," << endl;
	cout << "hoping you can put forward your valuable comments!" << endl<<endl;
	cout << "------------------------------------------------------------------------------------------"<<endl<<endl;
	cout << "Before using, please read the following carefully:" << endl;
	cout << "Commands end with; or \g." << endl;
	cout << "Type 'help; ' or '\\h' for help." << endl;
	cout << "Type '\c' to clear the current input statement." << endl;
	cout << "Some other content in your use process I will slowly tell you, now please start!" << endl<<endl;
	cout << "------------------------------------------------------------------------------------------" << endl;*/

	while (1) {
		cout << endl << "mysql> ";
		cin >> op;
		if (op == "\\h" || op == "help" || op == "?") {
			help();
		}
		else if (op == "create") {//创建
			string text;
			cin >> text;
			if (text == "table") {
				CreateTable();
			}
			else if (text == "database") {
				CreateDatabase();
			}
		}
		else if (op == "use") {//选择数据库
			cin >> Database;
			Database = Database.substr(0, Database.size() - 1);
			char charDatabase[100];
			strcpy(charDatabase, Database.c_str());
			int t = use(charDatabase);
			if (t == 3) {
				cout << "Database changed;";
			}
			else if (t == 4)continue;
			else cout << "Error, the database does not exist";
		}
		else if (op == "insert") {
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
			else if (text == "create") {
				cin >> text;
				if (text == "database") {

				}
				else if (text == "table") {

				}
			}
			
			else if (text == "table") {
				//scanf("status from %s", &Database);
			}
			else if (text == "varblies") {

			}
		}
		else if (op == "drop") {//删除
			string text;
			cin >> text;
		}
		else if (op == "desc") {

		}
		else if (op == "alter") {

		}
		else if (op == "rename") {

		}
		else if (op == "update") {

		}
		else if (op == "delete") {

		}
		else if (op == "exit") return 0;
		else cout << "Unrecognized operation or instruction";

	}

}