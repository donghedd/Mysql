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

void deletee()
{
	string from;
	cin >> from;

	string table;
	cin >> table;

	string where;
	cin >> where;
	string longziduan;
	cin >> longziduan;
	string denghao;
	cin >> denghao;
	string xuanxiang;
	cin >> xuanxiang;
	xuanxiang = xuanxiang.substr(1, xuanxiang.size() - 1);
	xuanxiang = xuanxiang.substr(0, xuanxiang.size() - 1);
	xuanxiang = xuanxiang.substr(0, xuanxiang.size() - 1);

	string oldname = longziduan;
	string neirong = "NULL";

	string filename1 = "C:/mysql/files/" + Database + '/' + table + '/' + "header.txt";
	fstream fin1(filename1);
	if (!fin1.is_open())
	{
		perror("");
		return;
	}

	string buffer;
	int position4 = 0, i = 1;
	while (getline(fin1, buffer))
	{
		if (buffer.substr(0, oldname.size()) == oldname) position4 = i;
		i++;
	}
	fin1.close();

	string filename2 = "C:/mysql/files/" + Database + '/' + table + '/' + "value.txt";
	fstream fin2(filename2);
	if (!fin2.is_open())
	{
		perror("");
		return;
	}

	string buffer2;
	string temp[N];
	int j = 1;//����
	while (getline(fin2, buffer2))
	{
		temp[j] = buffer2;
		j++;
	}
	fin2.close();


	int air = 0;
	for (int h = 2; h < j; h++)//�ҹؼ���
	{
		string hang = temp[h];
		int numm = 0;//��position3
		int bg = 0, ed = 0;
		for (int g = 0; g < hang.size(); g++)
		{
			if (hang[g] != ' ' && !bg) bg = g;//��һ����Ϊ�ո�ĵ�
			if (hang[g] == ' ' && hang[g - 1] != ' ') {
				ed = g;
				numm++;
				if (numm == position4)//λ��
				{
					string abc = hang.substr(bg, ed - bg);
					if (abc == xuanxiang) //����һ��
					{
						air = h;
						break;
					}
					else {
						continue;
					}
				}
				bg = 0, ed = 0;
			}

		}
	}

	//����temp, air���޸���

	ofstream fout(filename2);
	if (!fout.is_open())
	{
		perror("");
		return;
	}
	for (int f = 1; f < j; f++)
	{
		if (f == air)
		{
			continue;
		}
		else
		{
			fout << temp[f];
			if (f != j - 1) fout << '\n';
		}//һ�����ݽ���
	}
	cout << "Query OK" << endl;
}
//delete from table where longziduan denghao xuanxiang