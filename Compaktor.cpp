#include<bits/stdc++.h>
#define ll long long
using namespace std;
ifstream inf;
ofstream ouf;
string lokacija,bs;
string tostr(int x){
   if(x==0)
      return "0";
   string ret="";
   while(x){
      ret.push_back(x%10+'0');
      x/=10;
   }
   reverse(ret.begin(),ret.end());
   return ret;
}
string drzave[50]={
    "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut",
    "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
    "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
    "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
    "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
    "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota",
    "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
    "Wisconsin", "Wyoming"};
void procesiraj(string A,int indx){
   for(int i=0;i<10000;i++){
      if((i&1023)==0)
         cout<<indx<<" "<<i<<endl;
      if((i&3)==0)
         ouf<<indx<<"\n";
      string ime,fajl;
      ime=tostr(i>>2)+"_"+tostr(i&3)+".txt";
      fajl=lokacija+A+bs+ime;
      inf.open(fajl);
      string x;
      while(inf>>x){
         ouf<<x<<" ";
      }
      ouf<<"\n";
      inf.close();
   }
}
int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   bs="";
   bs.push_back(92);
   ouf.open("Dataset.txt");
   lokacija="Ekstraktovano"+bs;
   for(int i=0;i<50;i++)
      procesiraj(drzave[i],i);
   return 0;
}
