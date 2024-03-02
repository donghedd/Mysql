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
#include<iomanip>
using namespace std;
extern string Database;
const int N = 100;

void alter()
{
	string tablename;
	cin >> tablename;
	string function;
	cin >> function;//输入功能选项
	if (function == "rename")
	{
		string toas;//输入to或者as
		cin >> toas;

		string ntablename;//输入新的表名
		cin >> ntablename;
		ntablename = ntablename.substr(0, ntablename.size() - 1);
		string newname = ntablename;
		ntablename = "C:/mysql/files/" + Database + "/" + ntablename;

		string filename = "C:/mysql/files/" + Database + "/" + tablename;
		ifstream fin(filename);

		fin.close();

		rename(filename.c_str(), ntablename.c_str());

		string filename1 = "C:/mysql/files/" + Database + '/' + "tables.txt";
		ifstream fin1(filename1);
		if (!fin1.is_open())
		{
			perror("");
			return;
		}

		int i = 1;
		string buffer;
		string temp[N];
		while (getline(fin1, buffer))
		{
			temp[i] = buffer;
			if (buffer == tablename)
			{
				temp[i] = newname;
			}
			i++;
		}
		fin1.close();

		string filename2 = "C:/mysql/files/" + Database + '/' + "tables.txt";
		ofstream fout(filename2);
		if (!fout.is_open())
		{
			perror("");
			return;
		}
		for (int j = 1; j < i; j++)
		{
			fout << temp[j];
			if (j != i - 1) fout << '\n';
		}
		cout << "Query OK" << endl;
	}

	if (function == "change")
	{
		string oldziduan;
		cin >> oldziduan;
		string newziduan;
		cin >> newziduan;
		string ziduantype;
		cin >> ziduantype;
		ziduantype = ziduantype.substr(0, ziduantype.size() - 1);

		string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";
		ifstream fin(filename);

		if (!fin.is_open())
		{
			perror("");
			return;
		}

		int i = 1;
		int leng = oldziduan.size();
		string temp[N];
		string buffer;
		while (getline(fin, buffer))
		{
			string jianyan = buffer.substr(0, leng);
			temp[i] = buffer;
			if (jianyan == oldziduan)
				temp[i] = newziduan;
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
			if (temp[j] == newziduan)
			{
				fout << setw(20) << left << newziduan << setw(20) << left << ziduantype;
			}
			else fout << temp[j];
			if (j != i - 1) fout << '\n';
		}
		fout.close();

		string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
		ifstream fin1(filename1);
		if (!fin1.is_open())
		{
			perror("");
			return;
		}

		int g = 1;
		string buffer1;
		string temp1[N];
		string temprary;
		while (getline(fin1, buffer1))
		{
			if (g == 1) temprary = buffer1;
			else temp1[g] = buffer1;//存每一行内容
			g++;
		}

		int num_ziduan = 0;
		string zdcc[N];//存字段
		int star = 0, end = 0, k = 1;
		for (int i = 0; i < temprary.size(); i++)
		{
			if (i == 0) star = i;
			if (i && temprary[i] != ' ' && temprary[i - 1] == ' ') star = i;
			if (temprary[i] != ' ' && temprary[i + 1] == ' ')
			{
				num_ziduan++;//记录字段个数
				//当前i是末尾
				end = i;
				zdcc[k] = temprary.substr(star, end - star + 1);
				if (zdcc[k] == oldziduan) zdcc[k] = newziduan;
				star = 0, end = 0, k++;
			}
		}
		fin1.close();

		ofstream fout1(filename1);
		if (!fout1.is_open())
		{
			perror("");
			return;
		}

		for (int j = 1; j < g; j++)
		{
			if (j == 1)
			{
				for (int jj = 1; jj <= num_ziduan; jj++)
				{
					fout1 << setw(20) << left << zdcc[jj];
				}
				if (j != g - 1) fout1 << '\n';
			}
			else
			{
				fout1 << temp1[j];
				if (j != g - 1) fout1 << '\n';
			}
		}
		fout1.close();

		cout << "Query OK" << endl;
	}

	if (function == "modify")
	{
		string oldname;
		cin >> oldname;
		string typedd;
		cin >> typedd;
		string function1;
		cin >> function1;
		if (function1 == "first;")
		{
			string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";
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
				if (buffer.substr(0, oldname.size()) == oldname) position = i;
				i++;
			}
			//swap(temp[1], temp[position]);
			fin.close();

			ofstream fout(filename);
			if (!fout.is_open())
			{
				perror("");
				return;
			}

			fout << temp[position];
			fout << '\n';
			for (int j = 1; j < i; j++)
			{
				if (j == position) continue;
				fout << temp[j];
				if (j != i - 1) fout << '\n';
			}
			fout.close();

			string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
			ifstream fin1(filename1);
			if (!fin1.is_open())
			{
				perror("");
				return;
			}

			//i是种类数，j是行数, position是oldname序号
			int j = 1;
			string temp1[N];
			string buffer1;
			while (getline(fin1, buffer1))
			{
				temp1[j] = buffer1;
				j++;
			}
			j--;

			string zdcc[N];//存字段
			string spzdcc[N];//存特殊字段
			int k = 1, kk = 1;
			for (int h = 1; h <= j; h++)//行数
			{
				int star = 0, end = 0;
				int nummm = 0;//计数
				string temprary = temp1[h];
				for (int u = 0; u < temprary.size(); u++)
				{
					if (u == 0) star = u;
					if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
					if (temprary[u] != ' ' && temprary[u + 1] == ' ')
					{
						nummm++;
						//当前i是末尾
						end = u;
						string abc;
						abc = temprary.substr(star, end - star + 1);
						if (nummm == position)
						{
							spzdcc[kk] = abc;
							kk++;
							star = 0, end = 0;
						}
						else
						{
							zdcc[k] = abc;
							k++;
							star = 0, end = 0;
						}
					}
				}

			}
			fin1.close();

			ofstream fout1(filename1);
			if (!fout1.is_open())
			{
				perror("");
				return;
			}

			int seq = 1, seqq = 1;
			for (int h = 1; h <= j; h++)
			{
				for (int u = 0; u < i - 1; u++)
				{
					if (u == 0) fout1 << setw(20) << left << spzdcc[seqq++];
					else fout1 << setw(20) << left << zdcc[seq++];
				}
				if (h != j) fout1 << '\n';
			}
			fout1.close();

			cout << "Query OK" << endl;
		}
		if (function1 == "after")
		{
			string newname;
			cin >> newname;
			newname = newname.substr(0, newname.size() - 1);
			string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";
			ifstream fin(filename);
			if (!fin.is_open())
			{
				perror("");
				return;
			}

			int i = 1, position = 0, position1 = 0;
			string temp[N];
			string buffer;
			string oldziduan;
			while (getline(fin, buffer))
			{
				if (buffer.substr(0, oldname.size()) == oldname)
				{
					position = i;
					oldziduan = buffer;
					continue;
				}
				if (buffer.substr(0, newname.size()) == newname)
				{
					position1 = i;
				}
				temp[i] = buffer;
				i++;
			}
			fin.close();

			ofstream fout(filename);
			if (!fout.is_open())
			{
				perror("");
				return;
			}

			for (int j = 1; j <= i - 1; j++)
			{
				if (temp[j].substr(0, newname.size()) == newname)
				{
					fout << temp[j];
					fout << '\n';
					fout << oldziduan;
					if (j != i - 1) fout << '\n';
					continue;
				}

				fout << temp[j];
				if (j != i - 1) fout << '\n';
			}
			fout.close();

			string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
			ifstream fin1(filename1);
			if (!fin1.is_open())
			{
				perror("");
				return;
			}

			//i是种类数，j是行数, position是oldname序号
			int j = 1;
			string temp1[N];
			string buffer1;
			while (getline(fin1, buffer1))
			{
				temp1[j] = buffer1;
				j++;
			}
			j--;

			string zdcc[N];//存字段
			string spzdcc[N];//存特殊字段
			int k = 1, kk = 1;
			for (int h = 1; h <= j; h++)//行数
			{
				int star = 0, end = 0;
				int nummm = 0;//计数
				string temprary = temp1[h];
				for (int u = 0; u < temprary.size(); u++)
				{
					if (u == 0) star = u;
					if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
					if (temprary[u] != ' ' && temprary[u + 1] == ' ')
					{
						nummm++;
						//当前i是末尾
						end = u;
						string abc;
						abc = temprary.substr(star, end - star + 1);
						if (nummm == position)
						{
							spzdcc[kk] = abc;
							kk++;
							star = 0, end = 0;
						}
						else
						{
							zdcc[k] = abc;
							k++;
							star = 0, end = 0;
						}
					}
				}

			}
			fin1.close();

			ofstream fout1(filename1);
			if (!fout1.is_open())
			{
				perror("");
				return;
			}

			int seq = 1, seqq = 1;
			for (int h = 1; h <= j; h++)
			{
				for (int u = 0; u < i; u++)
				{
					if (u == position1) fout1 << setw(20) << left << spzdcc[seqq++];
					else fout1 << setw(20) << left << zdcc[seq++];
				}
				if (h != j) fout1 << '\n';
			}
			fout1.close();

			cout << "Query OK" << endl;
		}
	}

	if (function == "add")
	{
		string newname;
		cin >> newname;
		string jianyan1 = newname.substr(0, 1);
		if (jianyan1 == "(")
		{
			newname = newname.substr(1, newname.size() - 1);
			string addname = newname;

			int k = 1;
			string temptablename = addname;
			while (k)
			{
				addname = temptablename;
				string whole;
				string addtype;
				cin >> whole;
				if (whole.substr(whole.size() - 1, 1) == ";")
				{
					k = 0;
					whole = whole.substr(0, whole.size() - 1);
					whole = whole.substr(0, whole.size() - 1);
					addtype = whole;
				}
				else {
					int leng = whole.size();
					int position = 0, position1 = 0;
					for (int i = 0; i < whole.size(); i++)
					{
						if (whole[i] == ',') position = i;//逗号位置
					}

					addtype = whole.substr(0, position);
					temptablename = whole.substr(position + 1, leng - 1 - position);
				}

				string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";

				ifstream fin(filename);
				if (!fin.is_open())
				{
					perror("");
					return;
				}

				int i = 1;
				string buffer;
				while (getline(fin, buffer))
				{
					i++;
				}
				fin.close();

				ofstream fout(filename, ios::app);
				if (!fout.is_open())
				{
					perror("");
					return;
				}
				fout << '\n';
				fout << setw(20) << left << addname << setw(20) << left << addtype;
				fout.close();

				string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
				ifstream fin1(filename1);
				if (!fin1.is_open())
				{
					perror("");
					return;
				}

				//i-1是种类数，j是行数, position是oldname序号
				int j = 1;
				string temp1[N];
				string buffer1;
				while (getline(fin1, buffer1))
				{
					temp1[j] = buffer1;
					j++;
				}
				j--;

				string zdcc[N];//存字段
				string spzdcc[N];//存特殊字段
				int k = 1, kk = 1;
				for (int h = 1; h <= j; h++)//行数
				{
					int star = 0, end = 0;
					int nummm = 0;//计数
					string temprary = temp1[h];
					for (int u = 0; u < temprary.size(); u++)
					{
						if (u == 0) star = u;
						if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
						if (temprary[u] != ' ' && temprary[u + 1] == ' ')
						{
							nummm++;
							//当前i是末尾
							end = u;
							string abc;
							abc = temprary.substr(star, end - star + 1);
							zdcc[k] = abc;
							k++;
							star = 0, end = 0;
						}
					}

				}
				fin1.close();

				ofstream fout1(filename1);
				if (!fout1.is_open())
				{
					perror("");
					return;
				}

				int seq = 1, seqq = 1;
				for (int h = 1; h <= j; h++)
				{
					if (h == 1) {
						for (int u = 0; u < i; u++)
						{
							if (u == i - 1) fout1 << setw(20) << left << addname;
							else fout1 << setw(20) << left << zdcc[seq++];
						}
						if (h != j) fout1 << '\n';
					}
					else
					{
						for (int u = 0; u < i; u++)
						{
							if (u == i - 1) fout1 << setw(20) << left << "NULL";
							else fout1 << setw(20) << left << zdcc[seq++];
						}
						if (h != j) fout1 << '\n';
					}
				}
				fout1.close();

			}
			cout << "Query OK" << endl;
		}
		else {
			string typeziduan;
			cin >> typeziduan;

			string jianyan = typeziduan.substr(typeziduan.size() - 1, 1);
			if (jianyan == ";")
			{
				string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";

				ifstream fin(filename);
				if (!fin.is_open())
				{
					perror("");
					return;
				}

				int i = 1;
				string buffer;
				while (getline(fin, buffer))
				{
					i++;
				}
				fin.close();

				ofstream fout(filename, ios::app);
				if (!fout.is_open())
				{
					perror("");
					return;
				}
				fout << '\n';
				fout << setw(20) << left << newname << setw(20) << left << typeziduan.substr(0, typeziduan.size() - 1);
				fout.close();

				string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
				ifstream fin1(filename1);
				if (!fin1.is_open())
				{
					perror("");
					return;
				}

				//i-1是种类数，j是行数, position是oldname序号
				int j = 1;
				string temp1[N];
				string buffer1;
				while (getline(fin1, buffer1))
				{
					temp1[j] = buffer1;
					j++;
				}
				j--;

				string zdcc[N];//存字段
				string spzdcc[N];//存特殊字段
				int k = 1, kk = 1;
				for (int h = 1; h <= j; h++)//行数
				{
					int star = 0, end = 0;
					int nummm = 0;//计数
					string temprary = temp1[h];
					for (int u = 0; u < temprary.size(); u++)
					{
						if (u == 0) star = u;
						if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
						if (temprary[u] != ' ' && temprary[u + 1] == ' ')
						{
							nummm++;
							//当前i是末尾
							end = u;
							string abc;
							abc = temprary.substr(star, end - star + 1);
							zdcc[k] = abc;
							k++;
							star = 0, end = 0;
						}
					}

				}
				fin1.close();

				ofstream fout1(filename1);
				if (!fout1.is_open())
				{
					perror("");
					return;
				}

				int seq = 1, seqq = 1;
				for (int h = 1; h <= j; h++)
				{
					if (h == 1) {
						for (int u = 0; u < i; u++)
						{
							if (u == i - 1) fout1 << setw(20) << left << newname;
							else fout1 << setw(20) << left << zdcc[seq++];
						}
						if (h != j) fout1 << '\n';
					}
					else
					{
						for (int u = 0; u < i; u++)
						{
							if (u == i - 1) fout1 << setw(20) << left << "NULL";
							else fout1 << setw(20) << left << zdcc[seq++];
						}
						if (h != j) fout1 << '\n';
					}
				}
				fout1.close();

				cout << "Query OK" << endl;
			}
			if (jianyan != ";")
			{
				string function2;
				cin >> function2;
				if (function2.substr(0, function2.size() - 1) == "first")
				{

					string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";

					ifstream fin(filename);
					if (!fin.is_open())
					{
						perror("");
						return;
					}

					int i = 1;
					string buffer;
					string temp[N];
					while (getline(fin, buffer))
					{
						temp[i] = buffer;
						i++;
					}
					fin.close();

					ofstream fout(filename);
					if (!fout.is_open())
					{
						perror("");
						return;
					}
					fout << setw(20) << left << newname << setw(20) << left << typeziduan;
					fout << '\n';
					for (int j = 1; j < i; j++)
					{
						fout << temp[j];
						if (j != i - 1) fout << '\n';
					}
					fout.close();

					string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
					ifstream fin1(filename1);
					if (!fin1.is_open())
					{
						perror("");
						return;
					}

					//i-1是种类数，j是行数, position是oldname序号
					int j = 1;
					string temp1[N];
					string buffer1;
					while (getline(fin1, buffer1))
					{
						temp1[j] = buffer1;
						j++;
					}
					j--;

					string zdcc[N];//存字段
					string spzdcc[N];//存特殊字段
					int k = 1, kk = 1;
					for (int h = 1; h <= j; h++)//行数
					{
						int star = 0, end = 0;
						int nummm = 0;//计数
						string temprary = temp1[h];
						for (int u = 0; u < temprary.size(); u++)
						{
							if (u == 0) star = u;
							if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
							if (temprary[u] != ' ' && temprary[u + 1] == ' ')
							{
								nummm++;
								//当前i是末尾
								end = u;
								string abc;
								abc = temprary.substr(star, end - star + 1);
								zdcc[k] = abc;
								k++;
								star = 0, end = 0;
							}
						}

					}
					fin1.close();

					ofstream fout1(filename1);
					if (!fout1.is_open())
					{
						perror("");
						return;
					}

					int seq = 1, seqq = 1;
					for (int h = 1; h <= j; h++)
					{
						if (h == 1) {
							for (int u = 0; u < i; u++)
							{
								if (u == 0) fout1 << setw(20) << left << newname;
								else fout1 << setw(20) << left << zdcc[seq++];
							}
							if (h != j) fout1 << '\n';
						}
						else
						{
							for (int u = 0; u < i; u++)
							{
								if (u == 0) fout1 << setw(20) << left << "NULL";
								else fout1 << setw(20) << left << zdcc[seq++];
							}
							if (h != j) fout1 << '\n';
						}
					}
					fout1.close();

					cout << "Query OK" << endl;
				}
				else
				{
					string oldname;
					cin >> oldname;
					oldname = oldname.substr(0, oldname.size() - 1);
					string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";

					ifstream fin(filename);
					if (!fin.is_open())
					{
						perror("");
						return;
					}

					int i = 1, position = 0;
					string buffer;
					string temp[N];
					while (getline(fin, buffer))
					{
						if (buffer.substr(0, oldname.size()) == oldname)
							position = i;
						temp[i] = buffer;
						i++;
					}
					fin.close();

					ofstream fout(filename);
					if (!fout.is_open())
					{
						perror("");
						return;
					}
					for (int j = 1; j <= i - 1; j++)
					{
						if (j == position)
						{
							fout << temp[j];
							fout << '\n';
							fout << setw(20) << left << newname << setw(20) << left << typeziduan;
							if (j != i - 1)fout << '\n';
							continue;
						}
						fout << temp[j];
						if (j != i - 1) fout << '\n';
					}
					fout.close();


					string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
					ifstream fin1(filename1);
					if (!fin1.is_open())
					{
						perror("");
						return;
					}

					//i-1是种类数，j是行数, position是oldname序号
					int j = 1;
					string temp1[N];
					string buffer1;
					while (getline(fin1, buffer1))
					{
						temp1[j] = buffer1;
						j++;
					}
					j--;

					string zdcc[N];//存字段
					string spzdcc[N];//存特殊字段
					int k = 1, kk = 1;
					for (int h = 1; h <= j; h++)//行数
					{
						int star = 0, end = 0;
						int nummm = 0;//计数
						string temprary = temp1[h];
						for (int u = 0; u < temprary.size(); u++)
						{
							if (u == 0) star = u;
							if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
							if (temprary[u] != ' ' && temprary[u + 1] == ' ')
							{
								nummm++;
								//当前i是末尾
								end = u;
								string abc;
								abc = temprary.substr(star, end - star + 1);
								zdcc[k] = abc;
								k++;
								star = 0, end = 0;
							}
						}

					}
					fin1.close();

					ofstream fout1(filename1);
					if (!fout1.is_open())
					{
						perror("");
						return;
					}

					int seq = 1, seqq = 1;
					for (int h = 1; h <= j; h++)
					{
						if (h == 1) {
							for (int u = 0; u < i; u++)
							{
								if (u == position) fout1 << setw(20) << left << newname;
								else fout1 << setw(20) << left << zdcc[seq++];
							}
							if (h != j) fout1 << '\n';
						}
						else
						{
							for (int u = 0; u < i; u++)
							{
								if (u == position) fout1 << setw(20) << left << "NULL";
								else fout1 << setw(20) << left << zdcc[seq++];
							}
							if (h != j) fout1 << '\n';
						}
					}
					fout1.close();

					cout << "Query OK" << endl;
				}
			}
		}
	}

	if (function == "drop")
	{
		string oldname;
		cin >> oldname;
		oldname = oldname.substr(0, oldname.size() - 1);
		string filename = "C:/mysql/files/" + Database + "/" + tablename + "/" + "header.txt";
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
			if (j == i - 2 && position == i - 1)
			{
				fout << temp[j];
				continue;
			}
			fout << temp[j];
			if (j != i - 1) fout << '\n';
		}
		fout.close();

		string filename1 = "C:/mysql/files/" + Database + "/" + tablename + "/" + "value.txt";
		ifstream fin1(filename1);
		if (!fin1.is_open())
		{
			perror("");
			return;
		}

		//i是种类数，j是行数, position是oldname序号
		int j = 1;
		string temp1[N];
		string buffer1;
		while (getline(fin1, buffer1))
		{
			temp1[j] = buffer1;
			j++;
		}
		j--;

		string zdcc[N];//存字段
		string spzdcc[N];//存特殊字段
		int k = 1;
		for (int h = 1; h <= j; h++)//行数
		{
			int star = 0, end = 0;
			string temprary = temp1[h];
			for (int u = 0; u < temprary.size(); u++)
			{
				if (u == 0) star = u;
				if (u && temprary[u] != ' ' && temprary[u - 1] == ' ') star = u;
				if (temprary[u] != ' ' && temprary[u + 1] == ' ')
				{
					end = u;
					string abc;
					abc = temprary.substr(star, end - star + 1);
					zdcc[k] = abc;
					k++;
					star = 0, end = 0;
				}
			}

		}
		fin1.close();

		ofstream fout1(filename1);
		if (!fout1.is_open())
		{
			perror("");
			return;
		}

		int seq = 1, seqq = 1;
		for (int h = 1; h <= j; h++)
		{
			for (int u = 0; u < i - 1; u++)
			{
				if (u == position - 1)
				{
					zdcc[seq++];
					continue;
				}
				else fout1 << setw(20) << left << zdcc[seq++];
			}
			if (h != j) fout1 << '\n';
		}
		fout1.close();

		cout << "Query OK" << endl;
	}
}