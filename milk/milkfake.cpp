/*
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
struct farmer
{
       int p;
       int a;
};
main()
{
       ofstream fout ("milk.out");
       ifstream fin ("milk.in");
       int n,m,i,j,t,sum_n=0,place=0;
       farmer f[5000];
       fin>>n>>m;
       for(i=0;i<m;i++)
       fin>>f[i].p>>f[i].a;
       for(i=0;i<m;i++)
        for(j=i+1;j<m;j++)
           if(f[j].p<f[i].p)
           {
               t=f[i].p;f[i].p=f[j].p;f[j].p=t;
               t=f[i].a;f[i].a=f[j].a;f[j].a=t;
           }
       i=0;
       while(sum_n<n)
       {
           if(sum_n+f[i].a<=n)
           {
               place+=f[i].a*f[i].p;
               sum_n+=f[i].a;
           }
           else
           {
               place+=(n-sum_n)*f[i].p;
               sum_n+=(n-sum_n);
           }
           i++;
       }
       fout<<place<<endl;
       return 0;
} 
