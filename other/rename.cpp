#include<cstring>
#include<map>
#include<algorithm>
#include<cstdio>
#include<string>
#include<stack>
#include<queue>
#include<set>
#include<fstream>
#include <iostream>
using namespace std;
extern string Database;
const int N = 100;

void renamee()
{
    string tablename;
    cin >> tablename;
    string temptablename = tablename;

    int k = 1;
    while (k)
    {
        tablename = temptablename;
        string toas;// 输入 to 或者 as
        cin >> toas;

        string ntablename;// 输入新的表名
        cin >> ntablename;

        // 判断末尾
        int leng = ntablename.size();
        int position = 0;// 记录逗号位置

        string tail = ntablename.substr(ntablename.size() - 1, 1);
        if (tail == ";") {
            k = 0;// 分号就结束
            ntablename = ntablename.substr(0, leng - 1);
            string ntablename2 = ntablename;
        }
        else {
            // 找逗号
            for (int i = 0; i < leng; i++)
            {
                if (ntablename[i] == ',') position = i;
            }
            string ntablename2 = ntablename;
            ntablename = ntablename2.substr(0, position);
            temptablename = ntablename2.substr(position + 1, leng - 1 - position);// 用来存下一个 tablename
        }


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
        string temp[N];
        string buffer;
        while (fin1 >> buffer)
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
        fout.close();
    }
    cout << "Query OK" << endl;
}