#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<fstream>
#include<map>
#include<iomanip>
using namespace std;
extern string Database;
void SelectSection(string text) {
	string from, table, t;
	cin >> from >> table;
	if (table[table.size() - 1] == ';') {
		vector<string>header, Name[100];//表头  数据
		header.push_back("");		
		bool match[100] = { 0 };
		if (from != "from") {
			cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
			return;
		}
		if (Database == "\0") {
			cout << "Error, please select database";
			return;
		}
		table = table.substr(0, table.size() - 1);
		string pov = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
		ifstream fin(pov, ios::in);
		if (!fin.is_open()) {
			perror("");
			return;
		}

		//读取需要查询的表头
		stringstream st(text);
		int cnt = 0;
		map<string, pair<char, double>>ch;
		map<string, string>hh;
		while (getline(st, t, ',')) {
			int f = 0;
			for (int i = 0; i < t.size(); i++) {//判断是否需要做运算
				if (t[i] != '+' and t[i] != '-' and t[i] != '*' and t[i] != '/' and t[i] != '#')continue;
				else if (t[i] == '#') {
					int j =  i + 1;
					for (; j < t.size(); j++) {
						if (t[j] != '+' and t[j] != '-' and t[j] != '*' and t[j] != '/')continue;
						ch[t.substr(0, i)] = { t[j],stod(t.substr(j + 1)) };//运算
						break;
					}
					if(j == t.size())hh[t.substr(0, i)] = t.substr(i + 1);//改名
					else hh[t.substr(0, i)] = t.substr(i + 1,j - i - 1);
				}
				else ch[t.substr(0, i)] = { t[i],stod(t.substr(i + 1)) };//运算
				t = t.substr(0, i);
				break;
			}
			header.push_back(t);
		}

		//读取文件内容
		string fname, head;
		while (getline(fin, fname)) {
			cnt = 0;
			stringstream sf(fname);
			while (getline(sf, head, ' ')) {
				if (head == "")continue;
				if (Name[cnt].size() && ch.find(Name[cnt].front()) != ch.end()) {
					auto t = ch[Name[cnt].front()];
					double k;
					try {
						k = stod(head);
					}
					catch (const exception& e) {
						Name[cnt++].push_back(head);
						continue;
					}
					if (t.first == '+')head = to_string(stod(head) + t.second);
					else if(t.first == '-')head = to_string(stod(head) - t.second);
					else if(t.first == '*')head = to_string(stod(head) * t.second);
					else if(t.first == '/')head = to_string(stod(head) / t.second);
				}
				Name[cnt++].push_back(head);
			}
		}


		//匹配文件与表头
		int flag = 0;
		for (int i = 1; i < header.size(); i++) {
			for (int j = 0; j < cnt; j++) {
				if (header[i] != Name[j].front())continue;
				match[j] = true;
				flag++;
			}
		}
		if (flag != header.size() - 1) {
			cout << "Error, table header does not exist, please check the input";
			return;
		}
		//输出表头

		for (int i = 0; i < cnt; i++) {
			if (!match[i])continue;
			if (ch.find(Name[i].front()) == ch.end() && hh.find(Name[i].front()) == hh.end())cout << setw(20) << left << Name[i][0];
			else if (hh.find(Name[i].front()) == hh.end())//没改名
				cout << setw(20) << left << Name[i][0] + ch[Name[i][0]].first + to_string(ch[Name[i][0]].second);
			else {
				if (ch.find(Name[i].front()) == ch.end())cout << setw(20) << left << hh[Name[i][0]];
				else cout << setw(20) << left << hh[Name[i][0]] + ch[Name[i][0]].first + to_string(ch[Name[i][0]].second);
			}
		}
		
		//输出内容
		for (int i = 1; i < Name[0].size(); i++) {
			cout << endl;
			for (int j = 0; j < cnt; j++) {
				if (!match[j])continue;
				cout << setw(20) << left << Name[j][i];
			}
		}


		fin.close();
	}

	//有where
	else {
		string op, where, opp, order;
		cin >> op >> where;
		if(op == "where") {
			if (where[where.size() - 1] != ';'){
				cin >> opp >> order;
				if ((opp == "order" or opp == "ordergreater") and order[order.size() - 1] == ';')
					order = order.substr(0, order.size() - 1);
			}
			else where = where.substr(0, where.size() - 1);
			vector<string>sheader, header, Name[100], NName[100];//表头  数据
			header.push_back("");
			sheader.push_back("");
			vector<double>sum;
			vector<string>rela;
			int st[100][2] = {0};
			map<int, int>match;
			if (from != "from") {
				cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
				return;
			}
			if (Database == "\0") {
				cout << "Error, please select database";
				return;
			}
			string pov = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
			ifstream fin(pov, ios::in);
			if (!fin.is_open()) {
				perror("");
				return;
			}

			//读取需要查询的表头
			stringstream stt(text);
			int cnt = 0;
			map<string, pair<char, double>>ch;
			map<string, string>hh;
			while (getline(stt, t, ',')) {
				int f = 0;
				for (int i = 0; i < t.size(); i++) {//判断是否需要做运算
					if (t[i] != '+' and t[i] != '-' and t[i] != '*' and t[i] != '/' and t[i] != '#')continue;
					else if (t[i] == '#') {
						int j = i + 1;
						for (; j < t.size(); j++) {
							if (t[j] != '+' and t[j] != '-' and t[j] != '*' and t[j] != '/')continue;
							ch[t.substr(0, i)] = { t[j],stod(t.substr(j + 1)) };//运算
							break;
						}
						if (j == t.size())hh[t.substr(0, i)] = t.substr(i + 1);//改名
						else hh[t.substr(0, i)] = t.substr(i + 1, j - i - 1);
					}
					else ch[t.substr(0, i)] = { t[i],stod(t.substr(i + 1)) };//运算
					t = t.substr(0, i);
					break;
				}
				sheader.push_back(t);
			}
			//读取文件内容
			string fname, head;
			while (getline(fin, fname)) {
				cnt = 0;
				stringstream sf(fname);
				while (getline(sf, head, ' ')) {
					if (head == "")continue;
					Name[cnt].push_back(head);
					if (Name[cnt].size() && ch.find(Name[cnt].front()) != ch.end()) {
						auto t = ch[Name[cnt].front()];
						double k;
						try {
							k = stod(head);
						}
						catch (const exception& e) {
							NName[cnt++].push_back(head);
							continue;
						}
						if (t.first == '+')head = to_string(stod(head) + t.second);
						else if (t.first == '-')head = to_string(stod(head) - t.second);
						else if (t.first == '*')head = to_string(stod(head) * t.second);
						else if (t.first == '/')head = to_string(stod(head) / t.second);
					}
					NName[cnt++].push_back(head);
					
				}
			}

			//排序
			map<double, vector<int>>sequence;
			int seq[100] = { 0 };
			vector<double>sequ;
			for (int i = 0; i < cnt; i++) {
				if (order.empty())break;
				else if (order == NName[i].front()) {
					for (int j = 1; j < NName[i].size(); j++) {
						double com;
						try {
							com = stod(Name[i][j]);
						}
						catch (const exception& e) {
							st[j][0] = 2;
							continue;
						}
						sequence[stod(NName[i][j])].push_back(j);//数据原来位置
						sequ.push_back(stod(NName[i][j]));	
					}
					if(opp =="order")sort(sequ.begin(), sequ.end());
					else if(opp == "ordergreater")sort(sequ.begin(), sequ.end(), greater<double>());
					for (int j = 0; j < sequ.size(); j++) {
						seq[j + 1] = sequence[sequ[j]].back();
						sequence[sequ[j]].pop_back();
						//seq[k] = 
					}
					break;
				}
			}
			//数据要求
			rela.push_back("");
			sum.push_back(0);
			stringstream sw(where);
			string p;
			while (getline(sw, p, ',')) {
				int i = 0, flag = 0;
				for (; i < p.size(); i++) {
					if (p[i] != '=' and p[i] != '>' and p[i] != '<' and p[i] != '!')continue;
					if (p[i] == '=')rela.push_back("=");
					else if (p[i] == '>') {
						if (p[i + 1] == '=')flag++, rela.push_back(">=");
						else rela.push_back(">");
					}
					else if (p[i] == '<') {
						if (p[i + 1] == '=')flag++, rela.push_back("<=");
						else rela.push_back("<");
					}
					else  flag++,rela.push_back("!=");
					break;
				}
				sum.push_back(stod(p.substr(i + 1 + flag)));
				header.push_back(p.substr(0, i));
			}

			//需要比较的列
			bool s[100] = { 0 };
			for (int i = 0; i < cnt; i++) {
				for (int j = 0; j < header.size(); j++) {
					if (Name[i].front() == header[j]) {
						match[i] = j;
						s[i] = true;
					}
				}
			}

			for (int i = 0; i < cnt; i++) {//第i列
				if (!s[i])continue;
				for (int j = 1; j < Name[i].size(); j++) {//逐行比较
					double com;
					try {
						com = stod(Name[i][j]);
					}
					catch (const exception& e) {
						st[j][0] = 2;
						continue;
					}
					if (rela[match[i]] == "=") {
						if (st[j][0] != 2 && com == sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
					else if (rela[match[i]] == "<") {
						if (st[j][0] != 2 && com < sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
					else if (rela[match[i]] == "<=") {
						if (st[j][0] != 2 && com <= sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
					else if (rela[match[i]] == ">") {
						if (st[j][0] != 2 && com > sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
					else if (rela[match[i]] == ">=") {
						if (st[j][0] != 2 && com >= sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
					else if (rela[match[i]] == "!=") {
						if (st[j][0] != 2 && com != sum[match[i]])st[j][0] = 1;
						else st[j][0] = 2;
					}
				}
			}

			//匹配文件与表头
			int flag = 0;
			for (int i = 1; i < sheader.size(); i++) {
				for (int j = 0; j < cnt; j++) {
					if (sheader[i] != Name[j].front())continue;
					st[j][1]++;
					flag++;
				}
			}
			if (flag != sheader.size() - 1) {
				cout << "Error, table header does not exist, please check the input";
				return;
			}

			//输出
			for (int i = 0; i < cnt; i++) {
				if (!st[i][1])continue;
				if (ch.find(Name[i].front()) == ch.end() && hh.find(Name[i].front()) == hh.end())cout << setw(20) << left << NName[i][0];
				else if (hh.find(Name[i].front()) == hh.end())//没改名
					cout << setw(20) << left << NName[i][0] + ch[NName[i][0]].first + to_string(ch[NName[i][0]].second);
				else {
					if (ch.find(Name[i].front()) == ch.end())cout << setw(20) << left << hh[NName[i][0]];//没运算
					else cout << setw(20) << left << hh[NName[i][0]] + ch[NName[i][0]].first + to_string(ch[NName[i][0]].second);
				}
			}
			for (int i = 1; i < Name[0].size(); i++) {//行
				if (order.size()) {
					if (st[seq[i]][0] != 1)continue;
				}
				else if (st[i][0] != 1)continue;	
				cout << endl;
				for (int j = 0; j < cnt; j++) {//列
					if (st[j][1] != 1)continue;
					if(order.empty())cout << setw(20) << left << NName[j][i];
					else cout << setw(20) << left << NName[j][seq[i]];
				}
			}
			fin.close();
		}
		else if (op == "order" || op == "ordergreater") {
			string order;
			if (where[where.size() - 1] == ';')order = where.substr(0, where.size() - 1);
			vector<string>sheader, Name[100], NName[100];//表头  数据
			sheader.push_back("");
			int st[100][2] = { 0 };
			if (from != "from") {
				cout << "Unrecognized operation or instruction";
				return;
			}
			if (Database == "\0") {
				cout << "Error, please select database";
				return;
			}

			string pov = "C:/mysql/files/" + Database + "/" + table + "/value.txt";
			ifstream fin(pov, ios::in);
			if (!fin.is_open()) {
				perror("");
				return;
			}

			//读取需要查询的表头
			stringstream stt(text);
			int cnt = 0;
			map<string, pair<char, double>>ch;
			map<string, string>hh;
			while (getline(stt, t, ',')) {
				int f = 0;
				for (int i = 0; i < t.size(); i++) {//判断是否需要做运算
					if (t[i] != '+' and t[i] != '-' and t[i] != '*' and t[i] != '/' and t[i] != '#')continue;
					else if (t[i] == '#') {
						int j = i + 1;
						for (; j < t.size(); j++) {
							if (t[j] != '+' and t[j] != '-' and t[j] != '*' and t[j] != '/')continue;
							ch[t.substr(0, i)] = { t[j],stod(t.substr(j + 1)) };//运算
							break;
						}
						if (j == t.size())hh[t.substr(0, i)] = t.substr(i + 1);//改名
						else hh[t.substr(0, i)] = t.substr(i + 1, j - i - 1);
					}
					else ch[t.substr(0, i)] = { t[i],stod(t.substr(i + 1)) };//运算
					t = t.substr(0, i);
					break;
				}
				sheader.push_back(t);
			}
			//读取文件内容
			string fname, head;
			while (getline(fin, fname)) {
				cnt = 0;
				stringstream sf(fname);
				while (getline(sf, head, ' ')) {
					if (head == "")continue;
					Name[cnt].push_back(head);
					if (Name[cnt].size() && ch.find(Name[cnt].front()) != ch.end()) {
						auto t = ch[Name[cnt].front()];
						double k;
						try {
							k = stod(head);
						}
						catch (const exception& e) {
							NName[cnt++].push_back(head);
							continue;
						}
						if (t.first == '+')head = to_string(stod(head) + t.second);
						else if (t.first == '-')head = to_string(stod(head) - t.second);
						else if (t.first == '*')head = to_string(stod(head) * t.second);
						else if (t.first == '/')head = to_string(stod(head) / t.second);
					}
					NName[cnt++].push_back(head);

				}
			}

			//排序
			map<double, vector<int>>sequence;
			int seq[100] = { 0 };
			vector<double>sequ;
			for (int i = 0; i < cnt; i++) {
				if (order.empty())break;
				else if (order == NName[i].front()) {
					for (int j = 1; j < NName[i].size(); j++) {
						double com;
						try {
							com = stod(Name[i][j]);
						}
						catch (const exception& e) {
							st[j][0] = 2;
							continue;
						}
						sequence[stod(NName[i][j])].push_back(j);//数据原来位置
						sequ.push_back(stod(NName[i][j]));
					}
					if (op == "order")sort(sequ.begin(), sequ.end());
					else if (op == "ordergreater")sort(sequ.begin(), sequ.end(), greater<double>());
					for (int j = 0; j < sequ.size(); j++) {
						seq[j + 1] = sequence[sequ[j]].back();
						sequence[sequ[j]].pop_back();
						//seq[k] = 
					}
					break;
				}
			}

			//匹配文件与表头
			int flag = 0;
			for (int i = 1; i < sheader.size(); i++) {
				for (int j = 0; j < cnt; j++) {
					if (sheader[i] != Name[j].front())continue;
					st[j][1]++;
					flag++;
				}
			}
			if (flag != sheader.size() - 1) {
				cout << "Error, table header does not exist, please check the input";
				return;
			}

			//输出
			for (int i = 0; i < cnt; i++) {
				if (!st[i][1])continue;
				if (ch.find(Name[i].front()) == ch.end() && hh.find(Name[i].front()) == hh.end())cout << setw(20) << left << NName[i][0];
				else if (hh.find(Name[i].front()) == hh.end())//没改名
					cout << setw(20) << left << NName[i][0] + ch[NName[i][0]].first + to_string(ch[NName[i][0]].second);
				else {
					if (ch.find(Name[i].front()) == ch.end())cout << setw(20) << left << hh[NName[i][0]];//没运算
					else cout << setw(20) << left << hh[NName[i][0]] + ch[NName[i][0]].first + to_string(ch[NName[i][0]].second);
				}
			}
			st[seq[0]][0] = 2;
			for (int i = 1; i < Name[0].size(); i++) {//行
				if (st[seq[i]][0] == 2)continue;
				cout << endl;
				for (int j = 0; j < cnt; j++) {//列
					if (st[j][1] != 1)continue;
					cout << setw(20) << left << NName[j][seq[i]];
				}
				fin.close();
			}
		}
		else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
	}
}
//select num#number,name,ch#chinses*10,ma#math*0.1,en#english/2 from 1 where ch>0;
//select num,name,ch,ma,en from 1 where ch>0 order num;
