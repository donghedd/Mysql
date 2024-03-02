#include<iomanip>
#include <iostream>
#include<cstring>
#include<map>
#include<algorithm>
#include<cstdio>
#include<string>
#include<stack>
#include<queue>
#include<set>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<direct.h>
#include<io.h>
using namespace std;
extern string Database;
const int N = 100;

void drop()
{
	string fuction;
	cin >> fuction;
	if (fuction == "database")
	{
		string oldname;
		cin >> oldname;
		oldname = oldname.substr(0, oldname.size() - 1);

		string filename1 = "C:/mysql/files/" + oldname;
		fstream fin1(filename1);

		string filename2 = "C:/mysql/files/" + oldname + '/' + "tables.txt";
		fstream fin2(filename2);

		string buffer2;
		while (getline(fin2, buffer2))
		{
			string filename3 = "C:/mysql/files/" + oldname + '/' + buffer2;
			fstream fin3(filename3);
			string filename4 = "C:/mysql/files/" + oldname + '/' + buffer2 + '/' + "header.txt";
			string filename5 = "C:/mysql/files/" + oldname + '/' + buffer2 + '/' + "value.txt";
			remove(filename4.c_str());
			remove(filename5.c_str());
			fin3.close();
			if (_rmdir(filename3.c_str())) {
				perror("Error creating directory");
				return;
			}
		}
		fin2.close();
		remove(filename2.c_str());
		if (_rmdir(filename1.c_str())) {
			perror("Error creating directory");
			return;
		}
		fin1.close();

		string address = "/all.txt";
		string filename = "C:/mysql/files" + address;
		ifstream fin(filename);
		if (!fin.is_open())
		{
			perror("");
			return;
		}

		int i = 1, position = 0;;
		string temp[N];
		string buffer;
		while (getline(fin, buffer))
		{
			temp[i] = buffer;
			if (buffer.substr(0, oldname.size()) == oldname)
			{
				position = i;
			}
			i++;
		}
		fin.close();

		ofstream fout(filename);
		if (!fout.is_open())
		{
			perror("");
			return;
		}

		for (int j = 1; j < i; j++)
		{
			if (j == position) continue;
			fout << temp[j];
			fout << '\n';
		}
		fout.close();


		cout << "Query OK" << endl;
	}

	if (fuction == "table")
	{
		string longziduan;
		cin >> longziduan;


		int k = 1;
		while (k)
		{
			int position1;
			for (int i = 0; i < longziduan.size(); i++)
			{
				if (longziduan[i] == ',')
				{
					position1 = i;
					break;
				}
				if (longziduan[i] == ';')
				{
					position1 = i;
					k = 0;
					break;
				}
			}
			string oldname = longziduan.substr(0, position1);
			longziduan = longziduan.substr(position1 + 1, longziduan.size() - 1 - position1);
			if (Database == "\0") {
				cout << "Error, please select database";
				return;
			}

			string filename1 = "C:/mysql/files/" + Database + '/' + oldname;
			fstream fin1(filename1);

			string filename4 = "C:/mysql/files/" + Database + '/' + oldname + '/' + "header.txt";
			string filename5 = "C:/mysql/files/" + Database + '/' + oldname + '/' + "value.txt";
			remove(filename4.c_str());
			remove(filename5.c_str());

			fin1.close();
			if (_rmdir(filename1.c_str()))
			{
				perror("Error creating directory");
				return;
			}

			string address = "/tables.txt";
			string filename = "C:/mysql/files/" + Database + '/' + address;
			ifstream fin(filename);
			if (!fin.is_open())
			{
				perror("");
				return;
			}

			int i = 1, position = 0;;
			string temp[N];
			string buffer;
			while (getline(fin, buffer))
			{
				temp[i] = buffer;
				if (buffer.substr(0, oldname.size()) == oldname)
				{
					position = i;
				}
				i++;
			}
			fin.close();

			ofstream fout(filename);
			if (!fout.is_open())
			{
				perror("");
				return;
			}

			for (int j = 1; j < i; j++)
			{
				if (j == position) continue;
				fout << temp[j];
				fout << '\n';
			}
			fout.close();
		}


		cout << "Query OK" << endl;
	}
}