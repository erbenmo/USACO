/*
ID:sidneyl1
LANG:C++
TASK:fracdec
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
using namespace std;
    long n,d;
    long a[100010]={0};
    bool f[100010]={0};
    char s[100010];
    long len,head;
    
    int count(long x,long y)
    {
        long c2,c5;
             
             c2=c5=0;
             while(x%2==0&&y%2==0) x=x/2,y=y/2;
             while(x%5==0&&y&5==0) x=x/5,y=y/5;
             
             while(y%2==0) y=y/2,c2++;
             while(y%5==0) y=y/5,c5++;
             
             if(c2>c5) return c2;
               else return c5;

    }
        
    
    int main()
    {
        long i,j,k,tmp,r;
        
        freopen("fracdec.in","r",stdin);
        freopen("fracdec.out","w",stdout);
             
             scanf("%ld %ld",&n,&d);
             
             sprintf(s+strlen(s),"%ld.",n/d);
             
             head=count(n,d);
             
             k=n%d;
             
             if(k==0) sprintf(s+strlen(s),"0");
             
             else
             { 

               for(i=0;i<head;i++)
               {
                  k=k*10;
                  a[i]=k/d;
                  k=k%d;
                  tmp=i;
               }
             
               if(k==0)
               {
                 len=i-1;
                 for(i=0;i<=len;i++) sprintf(s+strlen(s),"%ld",a[i]);
               }
             
               else
               {
                 r=k;
                 for(i=i;;i++)
                 {
                    a[i]=k*10/d;
                    k=k*10%d;
                    if(k==r) break;
                 }
             
                 len=i;

                 for(i=0;i<head;i++) sprintf(s+strlen(s),"%ld",a[i]);
                 sprintf(s+strlen(s),"(");
                 for(i=head;i<=len;i++) sprintf(s+strlen(s),"%ld",a[i]);
                 sprintf(s+strlen(s),")");
               }
             }
             
             len=strlen(s);
             for(i=0;i<len;i+=76) printf("%.76s\n",s+i);
             
             //printf("%ld\n",head);
        
        fclose(stdin);
        fclose(stdout);
    }
