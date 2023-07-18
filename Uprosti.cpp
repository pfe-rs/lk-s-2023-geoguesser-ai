#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define LIMIT 630000000
using namespace std;
char buffer[LIMIT+5];
int dsize=1564,ipok=0;
int osize=50;
int es=2500;
int ts=0;
int eN,tN;
mt19937_64 rng;
int getint(){
   int ret=0;
   while(!(buffer[ipok]>='0' and buffer[ipok]<='9'))
      ipok++;
   while(buffer[ipok]>='0' and buffer[ipok]<='9'){
      ret*=10;
      ret+=buffer[ipok]-'0';
      ipok++;
   }
   return ret;
}
struct primer{
   vector<int> input,output;
}example[130005],tests[130005];
void unesitest(){
   FILE *fp;
   fp = fopen("Dataset.txt","r");
   fread(buffer,LIMIT,1,fp);
   int klasa,pk=-1;
   int cnt;
   int k=0;
   for(int it=1;it<=(es+ts)*osize;it++){
      klasa=getint();
      cout<<klasa<<"\n";
      k++;
    //  if((k&1023)==0)
     //    cout<<k<<endl;
     //cout<<"AAA"<<endl;
     // cout<<eN<<" "<<tN<<endl;
      if(klasa!=pk)
         cnt=0;
      pk=klasa;
      cnt++;
      primer pp;
      for(int i=0;i<dsize;i++){
         int x;
         x=getint();
         pp.input.push_back(x);
      }
      if(cnt<=es){
         eN++;
         example[eN]=pp;
      }
      else{
         tN++;
         tests[tN]=pp;
      }
      for(int a=0;a<dsize;a+=391){
         for(int i=0;i<7;i++)
            cout<<pp.input[a+i]<<" ";
         cout<<"\n";
      }
   }
   cout<<"TESTOVI UNETI"<<endl;
}
int main(){
   freopen("UproscenDataset.txt","w",stdout);
   unesitest();
   return 0;
}
