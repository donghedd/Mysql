#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>
#include<map>
#include<iomanip>
using namespace std;
extern string Database;
void SelectAll() {
	string text, table, op;
	cin >> text >> table;
	if(table[table.size() - 1] == ';'){
		if (text != "from") {
			 cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
			return;
		}
		if (Database == "\0") {
			cout << "Error, please select database";
			return;
		}
		table = table.substr(0, table.size() - 1);
		string position = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
		ifstream fin(position, ios::in);
		if (!fin.is_open()) {
			perror("");
			return;
		}
		string sen;
		int n = 0;
		while (getline(fin, sen)) {
			cout  << sen << endl;
		}
		fin.close();	
	}
	else {//有where
		vector<string>Name[100];//数据
		vector<double>sum;//比较
		vector<string>rela;//比较符
		bool st[100] = {0};
		int h[100] = {0};
		//for (int i = 0; i < 100; i++)Name[i].clear();
		//sum.clear();
		//rela.clear();
		//memset(st, false, sizeof st);
		//memset(h, 0, sizeof h);
		string where, p, t, opp, order;
		vector<string>header;//筛选对象
		header.push_back(" ");
		cin >> op >> where;
		if (text != "from") {
			cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
			return;
		}
		if (Database == "\0") {
			cout << "Error, please select database";
			return;
		}

		//要求
		rela.push_back("");
		sum.push_back(0);
		if (op == "where") {
			if (where[where.size() - 1] != ';') {
				cin >> opp >> order;
				if ((opp == "order" or opp == "ordergreater") and order[order.size() - 1] == ';')
					order = order.substr(0, order.size() - 1);
			}
			else where = where.substr(0, where.size() - 1);
			stringstream ss(where);
			while (getline(ss, p, ',')) {
				int i = 0, flag = 0;
				//筛选条件
				for (; i < p.size(); i++) {
					if (p[i] != '=' and p[i] != '>' and p[i] != '<' and p[i] !=  '!')continue;
					if (p[i] == '=')rela.push_back("=");
					else if (p[i] == '>') {
						if (p[i + 1] == '=')flag++,rela.push_back(">=");
						else rela.push_back(">");
					}
					else if (p[i] == '<') {
						if (p[i + 1] == '=')flag++, rela.push_back("<=");
						else rela.push_back("<");
					}
					else i++, rela.push_back("!=");
					break;
				}
				header.push_back(p.substr(0, i));
				sum.push_back(stod(p.substr(i + 1 + flag)));
			}

			string type,tt; int cnt = 0;
			string poh = "C:/mysql/files/" + Database + "/" + table + "/header.txt";
			string pov = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
			ifstream fh(poh, ios::in);
			if (!fh.is_open()) {
				perror("");
				return;
			}
			ifstream fv(pov, ios::in);
			if (!fv.is_open()) {
				perror("");
				return;
			}
			while (getline(fh, type)) cnt++;//列数

			//将数据放入表中
			while (getline(fv, type)) {
				stringstream ss(type);
				int i = 0;
				while (getline(ss, tt, ' ')) {
					if (tt == "")continue;
					Name[i++].push_back(tt);
				}
			}

			//排序
			map<double, vector<int>>sequence;
			int seq[100] = { 0 };
			vector<double>sequ;
			for (int i = 0; i < cnt; i++) {
				if (order.empty())break;
				else if (order == Name[i].front()) {
					for (int j = 1; j < Name[i].size(); j++) {
						double com;
						try {
							com = stod(Name[i][j]);
						}
						catch (const exception& e) {
							h[j] = 2;
							continue;
						}
						sequence[stod(Name[i][j])].push_back(j);//数据原来位置
						sequ.push_back(stod(Name[i][j]));
					}
					if (opp == "order")sort(sequ.begin(), sequ.end());
					else if (opp == "ordergreater")sort(sequ.begin(), sequ.end(), greater<double>());
					for (int j = 0; j < sequ.size(); j++) {
						seq[j + 1] = sequence[sequ[j]].back();
						sequence[sequ[j]].pop_back();
					}
					break;
				}
			}
			int n = 0;
			map<int, int>match;//Name对应的header
			for (int i = 0; i < cnt; i++) {
				for (int j = 0; j < header.size(); j++) {
					if (Name[i].front() == header[j]) {
						st[i] = true;
						match[i] = j;
						n++;
					}
				}
			}
			if (n != header.size() - 1) {
				cout << "Error, table header does not exist, please check the input";
				return;
			}
			//判断哪行符合要求
			//0 ： 未检测
			//1 ： 全部通过
			//2 ： 不通过
			//逐行比较
			for (int i = 0; i < cnt; i++) {
				if (!st[i])continue;
				for (int j = 1; j < Name[i].size(); j++) {
					double com;
					try{
						com = stod(Name[i][j]);
					}
					catch (const exception& e) {
						h[j] = 2;
						continue;
					}
					if (rela[match[i]] == "=") {
						if (h[j] != 2 && com == sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
					else if (rela[match[i]] == "<") {
						if (h[j] != 2 && com < sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
					else if (rela[match[i]] == "<=") {
						if (h[j] != 2 && com <= sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
					else if (rela[match[i]] == ">") {
						if (h[j] != 2 && com > sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
					else if (rela[match[i]] == ">=") {
						if (h[j] != 2 && com >= sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
					else if (rela[match[i]] == "!=") {
						if (h[j] != 2 && com != sum[match[i]])h[j] = 1;
						else h[j] = 2;
					}
				}
			}

			//输出表头
			for (int i = 0; i < cnt; i++) {
				cout << setw(20) << left << Name[i][0];
			}
			for (int i = 1; i < Name[0].size(); i++) {
				if (order.size()) {
					if (h[seq[i]] != 1)continue;
				}
				else if (h[i] != 1)continue;
				cout << endl;
				for (int j = 0; j < cnt; j++) {
					if (order.empty())cout << setw(20) << left << Name[j][i];
					else cout << setw(20) << left << Name[j][seq[i]];
				}
			}
			fh.close();
			fv.close();
		}
		else if (op == "order" || op == "ordergreater") {
			order = where.substr(0, where.size() - 1);
			string type, tt; int cnt = 0;
			string poh = "C:/mysql/files/" + Database + "/" + table + "/header.txt";
			string pov = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
			ifstream fh(poh, ios::in);
			if (!fh.is_open()) {
				perror("");
				return;
			}
			ifstream fv(pov, ios::in);
			if (!fv.is_open()) {
				perror("");
				return;
			}
			while (getline(fh, type)) cnt++;//列数

			//将数据放入表中
			while (getline(fv, type)) {
				stringstream ss(type);
				int i = 0;
				while (getline(ss, tt, ' ')) {
					if (tt == "")continue;
					Name[i++].push_back(tt);
				}
			}

			//排序
			map<double, vector<int>>sequence;
			int seq[100] = { 0 };
			vector<double>sequ;
			for (int i = 0; i < cnt; i++) {
				if (order.empty())break;
				else if (order == Name[i].front()) {
					for (int j = 1; j < Name[i].size(); j++) {
						double com;
						try {
							com = stod(Name[i][j]);
						}
						catch (const exception& e) {
							h[j] = 2;
							continue;
						}
						sequence[stod(Name[i][j])].push_back(j);//数据原来位置
						sequ.push_back(stod(Name[i][j]));
					}
					if (op == "order")sort(sequ.begin(), sequ.end());
					else if (op == "ordergreater")sort(sequ.begin(), sequ.end(), greater<double>());
					for (int j = 0; j < sequ.size(); j++) {
						seq[j + 1] = sequence[sequ[j]].back();
						sequence[sequ[j]].pop_back();
					}
					break;
				}
			}
			//判断哪行符合要求
			//0 ： 未检测
			//1 ： 全部通过
			//2 ： 不通过
			//逐行比较
			//输出表头
			h[0] = 2;
			for (int i = 0; i < cnt; i++) {
				cout << setw(20) << left << Name[i][0];
			}
			for (int i = 1; i < Name[0].size(); i++) {
				if (h[seq[i]] == 2)continue;
				cout << endl;
				for (int j = 0; j < cnt; j++) {
					cout << setw(20) << left << Name[j][seq[i]];
				}
			}
			fh.close();
			fv.close();
		}
		else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
	}
}
//select * from 1 where num>1 order ma;