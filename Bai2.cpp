#include <iostream>
#include<math.h>
#include<vector>
using namespace std;

vector<int> nt;
int prime[10000000];
void sang(){
	for(int i = 0; i <= 10000000; i++){
		prime[i] = 1;
	}
	prime[0] = prime[1] = 0;
	for(int i = 2; i <= sqrt(10000000); i++){
		if(prime[i]==1){
			for(int j = i * i; j <= 10000000; j += i){
				prime[j] = 0;
			}
		}
	}
	int j=0;
	for(int i = 0; i <= 10000000; i++){
		if (prime[i]==1) 
		{
			nt.push_back(i);
		}
	}
}

void Sort(vector<int> &a, int l, int r)
{
	if (l>r) return; 
	int i=l+1,j=r;
	int c=a[l]; 
	while (a[i]<=c && i<=j) i++;
	while (a[j]>c && i<=j) j--;
	if (i<j) swap(a[i],a[j]);
	swap(a[j],a[l]);
	 Sort(a, l, j-1);
     Sort(a, j+1, r);
} 

vector<int> nnt;
void nuant(int n)
{
	int i=0;
	while (nt[i]<=sqrt(n))
	{
		int j=i;
		while (nt[i]*nt[j]<=n)
		{
			nnt.push_back(nt[i]*nt[j]);
			j++;
		}
		i++;
	}
}

int check(int x)
{
	int i=0;
	while (nt[i]<sqrt(x)) 
	{
		if (x%nt[i]==0)
		{
			if (prime[x/nt[i]]==1) return 1;
		}
		i++;
	}
	return 0;
}

int main()
{
	sang();
	int n;
	cin >> n;
	nuant(n);
	Sort(nnt,0,nnt.size()-1);
	for (int i=0; i<nnt.size(); i++) cout << nnt[i] << " ";
	cout << endl;
	cout << "cac cap so blum co tong la so blum:" << endl;
	for (int i=0; i<nnt.size(); i++)
		for (int j=i+1; j<nnt.size(); j++)
			if (check(nnt[i]+nnt[j])==1) cout << nnt[i] << "," << nnt[j] << endl; 
	int m;
	cin >> m;
	int kt=0;
	for (int i=0; i<nnt.size(); i++)
		if (nnt[i]==m) 
		{
			kt=1;
			break;
		}
	if (kt==1) cout << "m co trong day so nua nguyen to";
	else cout <<"m khong co trong day so nua nguyen to";
    return 0;
}
