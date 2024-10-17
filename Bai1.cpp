#include <iostream>
#include<string>
using namespace std;

int main()
{
	string s,st="";
	int dem[3];
	dem[0]=0;
	dem[1]=0;
	dem[2]=0;
	getline(cin , s);
	for (int i=0; i<s.size(); i++)
	{
		if (s[i] == ',')
		{
			if (st=="do") dem[0]++;
			if (st=="trang") dem[1]++;
			if (st=="xanh") dem[2]++;
			st="";
		}
		else st+=s[i];
	}
	string kq="";
	for (int i=0; i<=2; i++)
	{
		for (int j=1; j<=dem[i]; j++)
		{
			if (i==0) kq+="do,";
			if (i==1) kq+="trang,";
			if (i==2) kq+="xanh,";
		}
	}
	kq.erase(kq.size()-1,kq.size()-1);
	cout << kq;
    return 0;
}
