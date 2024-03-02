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

void update()
{
	string table;
	cin >> table;

	string set;
	cin >> set;

	string longziduan;
	cin >> longziduan;

	string where;
	cin >> where;
	string keyword;
	cin >> keyword;
	string denghao;
	cin >> denghao;
	string xuanxiang;
	cin >> xuanxiang;
	xuanxiang = xuanxiang.substr(1, xuanxiang.size() - 1);
	xuanxiang = xuanxiang.substr(0, xuanxiang.size() - 1);
	xuanxiang = xuanxiang.substr(0, xuanxiang.size() - 1);


	int k = 1;
	while (k)
	{
		int position = 0, start = 0, endd = 0, position2 = 0;
		for (int i = 0; i < longziduan.size(); i++)
		{
			if (longziduan[i] == '=') position = i;
			if (longziduan[i] == '\'' && start == 0)  start = i;
			if (longziduan[i] == '\'' && start)  endd = i;
			if (longziduan[i] == ',') {
				position2 = i;
				break;
			}
			if (longziduan[i] == '\'' && i == longziduan.size() - 1) {
				position2 = i;
				k = 0;
				break;
			}
		}
		string oldname = longziduan.substr(0, position);
		string neirong = longziduan.substr(start + 1, endd - start - 1);
		longziduan = longziduan.substr(position2 + 1, longziduan.size() - 1 - position2);

		string filename1 = "C:/mysql/files/" + Database + '/' + table + '/' + "header.txt";
		fstream fin1(filename1);
		if (!fin1.is_open())
		{
			perror("");
			return;
		}

		string buffer;
		int position3 = 0, position4 = 0, i = 1;
		while (getline(fin1, buffer))
		{
			if (buffer.substr(0, keyword.size()) == keyword) position3 = i;
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
		int j = 1;//行数
		while (getline(fin2, buffer2))
		{
			temp[j] = buffer2;
			j++;
		}
		fin2.close();


		int air = 0;
		for (int h = 2; h < j; h++)//找关键行
		{
			string hang = temp[h];
			int numm = 0;//找position3
			int bg = 0, ed = 0;
			for (int g = 0; g < hang.size(); g++)
			{
				if (hang[g] != ' ' && !bg) bg = g;//第一个不为空格的点
				if (hang[g] == ' ' && hang[g - 1] != ' ') {
					ed = g;
					numm++;
					if (numm == position3)//位置
					{
						string abc = hang.substr(bg, ed - bg);
						if (abc == xuanxiang) //是这一行
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

		//行在temp, air是修改行
		string temprary = temp[air];
		string zdcc[N];//存字段
		int star = 0, end = 0, k = 1, num_ziduan = 0;
		for (int i = 0; i < temprary.size(); i++)
		{
			if (i == 0) star = i;
			if (i && temprary[i] != ' ' && temprary[i - 1] == ' ') star = i;
			if (temprary[i] == ' ' && temprary[i - 1] != ' ')
			{
				num_ziduan++;
				end = i;
				zdcc[k] = temprary.substr(star, end - star);
				if (num_ziduan == position4) zdcc[k] = neirong;
				star = 0, end = 0, k++;
			}
		}


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
				for (int d = 1; d < i; d++)
				{
					fout << setw(20) << left << zdcc[d];
				}
				if (f != j - 1) fout << '\n';
			}
			else
			{
				fout << temp[f];
				if (f != j - 1) fout << '\n';
			}//一个数据结束
		}
	}
	cout << "Query OK" << endl;
}
//update table set longziduan where keyword denghao xuanxiang