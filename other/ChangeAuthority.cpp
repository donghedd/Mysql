#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdio>
using namespace std;
void ChangeAuthority() {
	string op, name, tofrom, f, text, fe;
	cin >> op;
	if (op == "view") {
		cin >> name;
		if (name == "information") {
			cin >> name;
			name = name.substr(0, name.size() - 1);
			string pi = "C:/mysql/files/authority/information/" + name + ".txt";
			ifstream fr(pi, ios::in);
			if (!fr.is_open()) {
				perror("");
				return;
			}
			while (getline(fr, text)) {
				cout << text << endl;
			}
			fr.close();
		}
		else if (name == "database") {
			cin >> name;
			name = name.substr(0, name.size() - 1);
			string pi = "C:/mysql/files/" + name + "/authority.txt";
			ifstream fr(pi, ios::in);
			if (!fr.is_open()) {
				perror("");
				return;
			}
			while (getline(fr, text)) cout << text << endl;
			fr.close();
		}
		else if(name == "operator;" || name == "user;" || name == "part;") {
			name = name.substr(0, name.size() - 1);
			string pi = "C:/mysql/files/authority/" + name + ".txt";
			ifstream fr(pi, ios::in);
			if (!fr.is_open()) {
				perror("");
				return;
			}
			while (getline(fr, text)) cout << text << endl;
			fr.close();
		}
		else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
	}
	else {
		cin >> name >> tofrom;
		if (op == "insert" && tofrom == "to") {//添加
			cin >> f;
			f = f.substr(0, f.size() - 1);
			//检查
			string p = "C:/mysql/files/authority/information/" + name + ".txt";
			ifstream fp(p, ios::in);
			if (fp.is_open()) {
				cout << "Error, The user already has some permissions";
				fp.close();
				return;
			}

			//输入
			string pi = "C:/mysql/files/authority/" + f + ".txt";
			ofstream fiw(pi, ios::app);
			if (!fiw.is_open()) {
				perror("");
				return;
			}
			fiw << endl << name;
			fiw.close();

			ofstream fpw(p);
			if (!fpw.is_open()) {
				perror("");
				return;
			}
			if (f != "part") {
				fpw << f;
				fpw.close();
			}
			else {
				cout << endl << "Please select the database" << endl;
				cin >> text;
				if (text == ";")fpw.close();
				else {
					text = text.substr(0, text.size() - 1);
					string ttext;
					stringstream st(text);
					while (getline(st, ttext, ',')) {
						string dpo = "C:/mysql/files/" + ttext + "/authority.txt";
						ofstream df(dpo, ios::app);
						if (!df.is_open()) {
							perror("");
							return;
						}
						df << endl << name;
						df.close();

						fpw << ttext << endl;;
					}
					fpw.close();
				}
			}
			cout << "Added successfully";
		}
		else if (op == "delete" and tofrom == "from") {//删除
			vector<string>Name, a;
			cin >> f;
			f = f.substr(0, f.size() - 1);

			//检查
			string p = "C:/mysql/files/authority/information/" + name + ".txt";
			ifstream fp(p, ios::in);
			if (!fp.is_open()) {
				cout << "Error, The user was not found";
				return;
			}
			else {
				while (getline(fp, text)) {
					Name.push_back(text);
				}
				fp.close();
				if (f == "operator" || f == "user") {
					if (Name.front() != f) {
						cout << "Error, The user does not have this permission";
					}
					else {
						string d = "C:/mysql/files/authority/information/" + name + ".txt";
						remove(d.c_str());//删除信息
						//删除authority
						string pi = "C:/mysql/files/authority/" + f + ".txt";
						ifstream fpi(pi, ios::in);
						if (!fpi.is_open()) {
							perror("");
							return;
						}
						while (getline(fpi, text)) {
							if (text != name)a.push_back(text);
						}
						fpi.close();
						ofstream fpiw(pi);
						if (!fpiw.is_open()) {
							perror("");
							return;
						}
						fpiw << a.front();
						for (int i = 1; i < a.size(); i++) {
							fpiw << endl << a[i];
						}
					}
				}
				else if (f == "part") {
					string d = "C:/mysql/files/authority/information/" + name + ".txt";
					remove(d.c_str());//删除信息
					//删除authority
					{
						string pi = "C:/mysql/files/authority/" + f + ".txt";
						ifstream fpi(pi, ios::in);
						if (!fpi.is_open()) {
							perror("");
							return;
						}
						while (getline(fpi, text)) {
							if (text != name)a.push_back(text);
						}
						fpi.close();
						ofstream fpiw(pi);
						if (!fpiw.is_open()) {
							perror("");
							return;
						}
						fpiw << a.front();
						for (int i = 1; i < a.size(); i++) {
							fpiw << endl << a[i];
						}
					}

					//各数据库中的信息
					while (Name.size()) {
						a.clear();
						auto h = Name.back();
						Name.pop_back();
						string dp = "C:/mysql/files/" + h + "/authority.txt";
						ifstream dpr(dp, ios::in);
						if (!dpr.is_open()) {
							perror("");
							return;
						}
						while (getline(dpr, text)) {
							if (text != name)a.push_back(text);
						}
						dpr.close();
						ofstream dpw(dp);
						if (!dpw.is_open()) {
							perror("");
							return;
						}
						dpw << a.front();
						for (int i = 1; i < a.size(); i++) {
							dpw << endl << a[i];
						}
						dpw.close();
					}
				}
				else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
			}
			cout << "Deleted successfully";
		}
		else if (op == "up" && tofrom == "from") {//
			string p = "C:/mysql/files/authority/information/" + name + ".txt";
			ifstream fp(p, ios::in);
			if (!fp.is_open()) {
				cout << "Error, The user was not found";
				return;
			}
			fp.close();
			vector<string>Name, h;
			cin >> f >> tofrom >> fe;
			bool flag = false;
			fe = fe.substr(0, fe.size() - 1);


			if (f == "user" && fe == "part") {
				string pa = "C:/mysql/files/authority/user.txt";
				ifstream fpar(pa, ios::in);
				if (!fpar.is_open()) {
					perror("");
					return;
				}
				while (getline(fpar, text)) {
					if (text == name)flag = true;
					else Name.push_back(text);
				}
				fpar.close();
				if (flag == false){
					cout << "Error, the user does not have this permission";
					return;
				}
				ofstream fpaw(pa);
				if (!fpaw.is_open()) {
					perror("");
					return;
				}
				fpaw << Name[0];
				for (int i = 1; i < Name.size(); i++) {
					fpaw << endl << Name[i];
				}
				fpaw.close();
				string pp = "C:/mysql/files/authority/part.txt";
				ofstream fpp(pp, ios::app);
				if (!fpp.is_open()) {
					perror("");
					return;
				}
				fpp << endl << name;
				fpp.close();
				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				cout << endl << "Please select the database" << endl;
				cin >> text;
				text = text.substr(0, text.size() - 1);
				string ttext;
				stringstream st(text);
				while (getline(st, ttext, ',')) {
					string dpo = "C:/mysql/files/" + ttext + "/authority.txt";
					ofstream df(dpo, ios::app);
					if (!df.is_open()) {
						perror("");
						return;
					}
					df << endl << name;
					df.close();

					fpw << ttext << endl;
				}
				fpw.close();
			}
			else if (f == "user" && fe == "operator") {
				string pa = "C:/mysql/files/authority/user.txt";
				ifstream fpar(pa, ios::in);
				if (!fpar.is_open()) {
					perror("");
					return;
				}
				while (getline(fpar, text)) {
					if (text == name)flag = true;
					else Name.push_back(text);
				}
				fpar.close();
				if (flag == false) {
					cout << "Error, the user does not have this permission";
					return;
				}
				ofstream fpaw(pa);
				if (!fpaw.is_open()) {
					perror("");
					return;
				}
				fpaw << Name[0];
				for (int i = 1; i < Name.size(); i++) {
					fpaw << endl << Name[i];
				}
				fpaw.close();

				string pp = "C:/mysql/files/authority/operator.txt";
				ofstream fpp(pp, ios::app);
				if (!fpp.is_open()) {
					perror("");
					return;
				}
				fpp << endl << name;
				fpp.close();

				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				fpw << "operator";
				fpw.close();
			}
			else if (f == "part" && fe == "part") {
				string pp = "C:/mysql/files/authority/part.txt";
				ifstream fppr(pp, ios::in);
				if (!fppr.is_open()) {
					perror("");
					return;
				}
				bool flag = 0;
				while (getline(fppr, text)) {
					if (text == name)flag = true;
				}
				if (flag == false) {
					cout << "Error, the user does not have this permission";
					return;
				}
				fppr.close();


				ifstream fpr(p, ios::in);
				ofstream fpw(p, ios::app);
				if (!fpr.is_open()) {
					perror("");
					return;
				}
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				cout << endl << "Please select the database" << endl;
				cin >> text;
				text = text.substr(0, text.size() - 1);
				string ttext;
				stringstream st(text);
				vector<string>a;
				fpr.seekg(0, ios::beg);
				while (getline(st, ttext, ',')) {
					a.push_back(ttext);
					while (getline(fpr, text)) {
						if (text == ttext) {
							cout << "Error, the user does not have this permission";
							return;
						}
					}
				}
				string ff;
				for (int i = 0; i < a.size(); i++) {
					string dpo = "C:/mysql/files/" + a[i] + "/authority.txt";
					ofstream df(dpo, ios::app);
					if (!df.is_open()) {
						perror("");
						return;
					}
					df << endl << name;
					df.close();

					fpw << ttext << endl  ;
				}
				fpw.close();
			}
			else if (f == "part" && fe == "operator") {
				vector<string>Name, a;
				//检查
				ifstream fp(p, ios::in);
				if (!fp.is_open()) {
					cout << "Error, The user was not found";
					return;
				}
				while (getline(fp, text)) {//information
					Name.push_back(text);
				}
				fp.close();
				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				fpw << "operator";

				string pop = "C:/mysql/files/authority/operator.txt";
				ofstream fpop(pop, ios::app);
				fpop << endl << name;
				//删除authority
				string pi = "C:/mysql/files/authority/part.txt";
				ifstream fpi(pi, ios::in);
				if (!fpi.is_open()) {
					perror("");
					return;
				}
				while (getline(fpi, text)) {
					if (text != name)a.push_back(text);
				}
				fpi.close();
				ofstream fpiw(pi);
				if (!fpiw.is_open()) {
					perror("");
					return;
				}
				fpiw << a.front();
				for (int i = 1; i < a.size(); i++) {
					fpiw << endl << a[i];
				}

				//各数据库中的信息
				while (Name.size()) {
					a.clear();
					auto h = Name.back();
					Name.pop_back();
					string dp = "C:/mysql/files/" + h + "/authority.txt";
					ifstream dpr(dp, ios::in);
					if (!dpr.is_open()) {
						perror("");
						return;
					}
					while (getline(dpr, text)) {
						if (text != name)a.push_back(text);
					}
					dpr.close();
					ofstream dpw(dp);
					if (!dpw.is_open()) {
						perror("");
						return;
					}
					dpw << a.front();
					for (int i = 1; i < a.size(); i++) {
						dpw << endl << a[i];
					}
					dpw.close();
				}
			}
			else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
		}
		else if (op == "down") {
			vector<string>Name, a;
			string p = "C:/mysql/files/authority/information/" + name + ".txt";
			ifstream fp(p, ios::in);
			if (!fp.is_open()) {
				cout << "Error, The user was not found";
				return;
			}
			cin >> f >> tofrom >> fe;
			fe = fe.substr(0, fe.size() - 1);
			if (f == "operator" && fe == "part") {//完成
				string po = "C:/mysql/files/authority/operator.txt";
				//检查并删除
				ifstream fpor(po, ios::in);
				if (!fpor.is_open()) {
					perror("");
					return;
				}
				bool flag = 0;
				while (getline(fpor, text)) {
					if (text == name)flag = true;
					else Name.push_back(text);
				}
				fpor.close();
				if (flag == false) {
					cout << "Error, the user does not have this permission";
					return;
				}
				//重新读入
				ofstream fpow(po);
				if (!fpow.is_open()) {
					perror("");
					return;
				}
				fpow << Name[0];
				for (int i = 1; i < Name.size(); i++) {
					fpow << endl << Name[i];
				}
				fpow.close();

				//读入
				string pp = "C:/mysql/files/authority/part.txt";
				ofstream fppr(pp, ios::app);
				if (!fppr.is_open()) {
					perror("");
					return;
				}
				fppr << endl << name;
				fppr.close();
				//读入information和对应数据库
				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				cout << endl << "Please select the database" << endl;
				cin >> text;
				text = text.substr(0, text.size() - 1);
				string ttext;
				stringstream st(text);
				while (getline(st, ttext, ',')) {
					string dpo = "C:/mysql/files/" + ttext + "/authority.txt";
					ofstream df(dpo, ios::app);
					if (!df.is_open()) {
						perror("");
						return;
					}
					df << endl << name;
					df.close();

					fpw << ttext << endl;
				}
				fpw.close();
			}
			else if (f == "operator" && fe == "user") {
				string pu = "C:/mysql/files/authority/operator.txt";
				//读入
				ifstream fpur(pu, ios::in);
				if (!fpur.is_open()) {
					perror("");
					return;
				}
				bool flag = 0;
				while (getline(fpur, text)) {
					if (text == name)flag = true;
					else Name.push_back(text);
				}
				fpur.close();
				if (flag == false) {
					cout << "Error, the user does not have this permission";
					return;
				}
				ofstream fpuw(pu);
				if (!fpuw.is_open()) {
					perror("");
					return;
				}
				if(Name.size())fpuw << Name[0];
				for (int i = 1; i < Name.size(); i++) {
					fpuw << endl << Name[i];
				}
				fpuw.close();
				//输入
				string po = "C:/mysql/files/authority/user.txt";
				ofstream fpow(po, ios::app);
				if (!fpow.is_open()) {
					perror("");
					return;
				}
				fpow << endl << name;
				fpow.close();

				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				fpw << "operator";
				fpw.close();
			}
			else if (f == "part" && fe == "part") {
				//检查
				string pp = "C:/mysql/files/authority/part.txt";
				ifstream fppr(pp, ios::in);
				if (!fppr.is_open()) {
					perror("");
					return;
				}
				bool flag = 0;
				while (getline(fppr, text)) {
					if (text == name)flag = true;
				}
				if (flag == false) {
					cout << "Error, the user does not have this permission";
					return;
				}
				fppr.close();

				//读入需要删除的数据库
				int cnt = 0, ccnt = 0;
				cout << endl << "Please select the database" << endl;
				cin >> text;
				text = text.substr(0, text.size() - 1);
				string ttext;
				stringstream st(text);
				while (getline(st, text,',')) {
					a.push_back(text);
				}
				ifstream fpr(p, ios::in);
				if (!fpr.is_open()) {
					perror("");
					return;
				}
				while (getline(fpr, text)) {
					bool f = 0;
					for (int i = 0; i < a.size(); i++) {
						if (a[i] == text)f = 1;
					}
					if (f == 1){
						cnt++;
						f = 0;
					}
					else Name.push_back(text);
				}
				if (cnt != a.size()) {
					cout << "Error, the user does not have this permission";
					return;
				}
				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				if (Name.size())fpw << Name[0];
				for (int i = 1; i < Name.size(); i++) {
					fpw << endl << Name[i];
				}
				fpw.close();
				fpr.close();

				//在各个库中删除
				for (int i = 0; i < a.size(); i++) {
					Name.clear();
					string pa = "C:/mysql/files/" + a[i] + "/authority.txt";
					ifstream re(pa, ios::in);
					if (!re.is_open()) {
						perror("");
						return;
					}
					while (getline(re, text)) {
						if (text != name)Name.push_back(text);
					}
					ofstream wr(pa);
					if (!wr.is_open()) {
						perror("");
						return;
					}
					wr << Name[0];
					for (int i = 1; i < Name.size(); i++) {
						wr << endl <<Name[i];
					}
					wr.close();
					re.close();
				}
			}
			else if (f == "part" && fe == "user") {
				ifstream fp(p, ios::in);
				if (!fp.is_open()) {
					cout << "Error, The user was not found";
					return;
				}
				while (getline(fp, text)) {//information
					Name.push_back(text);
				}
				fp.close();
				ofstream fpw(p);
				if (!fpw.is_open()) {
					perror("");
					return;
				}
				fpw << "user";

				string pop = "C:/mysql/files/authority/user.txt";
				ofstream fpop(pop, ios::app);
				fpop << endl << name;

				//删除authority
				string pi = "C:/mysql/files/authority/part.txt";
				ifstream fpi(pi, ios::in);
				if (!fpi.is_open()) {
					perror("");
					return;
				}
				while (getline(fpi, text)) {
					if (text != name)a.push_back(text);
				}
				fpi.close();
				ofstream fpiw(pi);
				if (!fpiw.is_open()) {
					perror("");
					return;
				}
				fpiw << a.front();
				for (int i = 1; i < a.size(); i++) {
					fpiw << endl << a[i];
				}

				//各数据库中的信息
				while (Name.size()) {
					a.clear();
					auto h = Name.back();
					Name.pop_back();
					string dp = "C:/mysql/files/" + h + "/authority.txt";
					ifstream dpr(dp, ios::in);
					if (!dpr.is_open()) {
						perror("");
						return;
					}
					while (getline(dpr, text)) {
						if (text != name)a.push_back(text);
					}
					ofstream dpw(dp);
					if (!dpw.is_open()) {
						perror("");
						return;
					}
					dpw << a.front();
					for (int i = 1; i < a.size(); i++) {
						dpw << endl << a[i];
					}
					dpr.close();
					dpw.close();
				}
			}
			else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
		}
		else cout << "Unrecognized operation or instruction or you do not have permission to perform this operation";
	}
}