#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
string password;
int authority() {
	cin >> password;
	string position = "C:/mysql/files/authority/operator.txt";
	ifstream fp(position, ios::in);
	string text;
	if (password == "206908") return 1;//���Ȩ��
	if (!fp.is_open()) {
		return 0;
	}
	while (getline(fp, text)) {//�����
		if (password == text) {
			return 2;
		}
	}
	fp.close();

	string p = "C:/mysql/files/authority/part.txt";
	ifstream fo(p, ios::in);
	if (!fo.is_open()) {
		return 0;
	}
	while (getline(fo, text)) {//ר��
		if (password == text) {
			return 3;
		}
	}
	fo.close();

	string po = "C:/mysql/files/authority/user.txt";
	ifstream fin(po, ios::in);
	if (!fin.is_open()) {
		return 0;
	}
	while (getline(fin, text)) {//��ͨ
		if (password == text) {
			return 4;
		}
	}
	fin.close();
	return 0;
}