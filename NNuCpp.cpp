#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define LIMIT 630000000
using namespace std;
char buffer[LIMIT+5];
int N,koliko[105],ipok=0;
int tN,eN;///broj validacionih i treniranih
ld eta=0.1;
clock_t poc;
int dsize=1564;
int osize=50;
int es=2250;
int ts=250;
mt19937_64 rng;
int getint(){/// OVA FUNKCIJA NIJE GOTOVA
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
ld random(ld lb,ld ub){
   if(lb>ub)
      swap(lb,ub);
   ld x=((ld)(rng()))/(INT64_MAX)/2;
   return lb+(ub-lb)*x;
}
struct matrica{
   vector<vector<ld>> mat;
   int N,M;
   void mresize(int n,int m){
      N=n;
      M=m;
      vector<ld> tmp;
      tmp.resize(m,0);
      mat.resize(n,tmp);
      return;
   };
   void popuni(ld a){
      for(int i=0;i<N;i++)
         for(int j=0;j<M;j++)
            mat[i][j]=a;
   }
   void mrandom(ld lb,ld ub){
      for(int i=0;i<N;i++)
         for(int j=0;j<M;j++)
            mat[i][j]=random(lb,ub);
      return;
   }
   matrica ufunkciju(ld f(ld)){
      matrica mat2;
      mat2.mresize(N,M);
      mat2.mat=mat;
      for(int i=0;i<N;i++)
         for(int j=0;j<M;j++)
            mat2.mat[i][j]=f(mat[i][j]);
      return mat2;
   }
   void izvektora(vector<ld> vek){
      N=vek.size();
      M=1;
      vector<ld> tmp;
      tmp.resize(M,0);
      mat.resize(N,tmp);
      for(int i=0;i<N;i++)
         mat[i][0]=vek[i];
      return;
   }
   matrica operator + (const matrica &m2){
      matrica m1;
      m1.N=N;
      m1.M=M;
      m1.mat=mat;
      if(m2.N!=N or m2.M!=M){
         cout<<"ATTEMPTED TO ADD MATRICES OF NON EQUAL SIZES"<<endl;
         return m1;
      }
      for(int i=0;i<m1.N;i++)
         for(int j=0;j<m1.M;j++)
            m1.mat[i][j]+=m2.mat[i][j];
      return m1;
   };
   matrica negiraj(){
      matrica m1;
      m1.N=N;
      m1.M=M;
      m1.mat=mat;
      for(int i=0;i<m1.N;i++)
         for(int j=0;j<m1.M;j++)
            m1.mat[i][j]=-m1.mat[i][j];
      return m1;
   };
   matrica operator * (const ll &a){
      matrica r;
      r.mresize(N,M);
      for(int i=0;i<N;i++)
         for(int j=0;j<M;j++)
            r.mat[i][j]=mat[i][j]*a;
      return r;
   }
   matrica operator * (const matrica &m2){ /// Obicno mnozenje
      matrica m1;
      m1.N=N;
      m1.M=M;
      m1.mat=mat;
      if(m2.N!=m1.M){
         cout<<"ATTEMPTED TO MULTIPLY MATRICES OF WRONG SIZES"<<endl;
         cout<<m1.N<<" "<<m1.M<<" "<<m2.N<<" "<<m2.M<<endl;
         return m1;
      }
      matrica m3;
      m3.mresize(m1.N,m2.M);
      for(int i=0;i<m1.N;i++)
         for(int j=0;j<m2.M;j++){
            m3.mat[i][j]=0;
            for(int k=0;k<m2.N;k++){
               m3.mat[i][j]+=m1.mat[i][k]*m2.mat[k][j];
            }
         }
      return m3;
   };
   matrica operator / (const matrica &m2){ /// Mnozenje istog reda i kolone
      matrica m1;
      m1.N=N;
      m1.M=M;
      m1.mat=mat;
      if(m2.N!=m1.N and m2.M!=m1.M){
         cout<<"ATTEMPTED TO DO HAMARD PRODUCT ON MATRICES THAT ARE NOT THE SAME SIZE"<<endl;
         return m1;
      }
      for(int i=0;i<m1.N;i++)
         for(int j=0;j<m2.M;j++)
            m1.mat[i][j]*=m2.mat[i][j];
      return m1;
   };
   void unesi(int n,int m){
      if(n<=0)
         cin>>n;
      if(m<=0)
         cin>>m;
      N=n;
      M=m;
      vector<ld> tmp;
      tmp.resize(m,0);
      mat.resize(n,tmp);
      for(int i=0;i<n;i++)
         for(int j=0;j<m;j++)
            cin>>mat[i][j];
      return;
   };
   void ispisi(bool NM){
      if(NM)
         cout<<N<<" "<<M<<"\n";
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++)
            cout<<mat[i][j]<<" ";
         cout<<"\n";
      }
      return;
   };
   matrica transpozicija(){
      matrica mat2;
      mat2.mresize(M,N);
      for(int i=0;i<N;i++)
         for(int j=0;j<M;j++)
            mat2.mat[j][i]=mat[i][j];
      return mat2;
   }
};
struct primer{
   vector<ld> input,output;
}example[130005],tests[130005];
void unesitest(){
   FILE *fp;
   fp = fopen("Dataset.txt","r");
   fread(buffer,LIMIT,1,fp);

   int klasa,pk=-1;
   int cnt;
   vector<ld> maks;
   maks.resize(dsize,0);
   int k=0;
   for(int it=1;it<=(es+ts)*osize;it++){
      klasa=getint();
      k++;
      if((k&1023)==0)
         cout<<k<<endl;
     //cout<<"AAA"<<endl;
     // cout<<eN<<" "<<tN<<endl;
      if(klasa!=pk)
         cnt=0;
      pk=klasa;
      cnt++;
      primer pp;
      pp.output.resize(osize,0);
      pp.output[klasa]=1;
      for(int i=0;i<dsize;i++){
         ld x;
         x=getint();
         maks[i]=max(maks[i],x);
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
   }/*
   for(int i=0;i<maks.size();i++)
      cout<<maks[i]<<" ";
   cout<<endl;*/
   for(int i=1;i<=eN;i++)
      for(int j=0;j<dsize;j++)
         example[i].input[j]/=maks[j];
   for(int i=1;i<=tN;i++)
      for(int j=0;j<dsize;j++)
         tests[i].input[j]/=maks[j];
   cout<<"TESTOVI UNETI"<<endl;
}
matrica slojevi[105],z[105],bias[105],grane[105],C,C2,greska[105];
ld euler=2.71828182845904523536;
ld squash(ld x){
   return 1/(1+pow(euler,-x));
}
ld dsquash(ld x){
   ld a=pow(euler,-x);
   return a/((a+1)*(a+1));
}
bool testiraj(primer x){
   slojevi[1].izvektora(x.input);
   for(int i=2;i<=N;i++){
      z[i]=grane[i]*slojevi[i-1];
      z[i]=z[i]+bias[i];
      slojevi[i]=z[i].ufunkciju(squash);
   }
   C.izvektora(x.output);
   C=slojevi[N]+C.negiraj();
   int guess=0;
   for(int i=1;i<osize;i++)
      if(slojevi[N].mat[i][0]>slojevi[N].mat[guess][0])
         guess=i;
   C2=C2+C;
   return (abs(x.output[guess]-1)<=0.01);
}
void backprop(){
   greska[N]=(C2*2)/z[N].ufunkciju(dsquash);
   for(int i=N-1;i>=2;i--){
      greska[i]=(grane[i+1].transpozicija()*greska[i+1])/z[i].ufunkciju(dsquash);
   }
   for(int i=2;i<=N;i++){
      //cout<<i<<endl;
      //cout<<grane[i].M<<" "<<grane[i].N<<endl;
      bias[i]=bias[i]+greska[i].negiraj()*eta;
      for(int i2=0;i2<grane[i].M;i2++)
         for(int j2=0;j2<grane[i].N;j2++){
            //cout<<i2<<" "<<j2<<endl;
            grane[i].mat[j2][i2]-=slojevi[i-1].mat[i2][0]*greska[i].mat[j2][0]*eta;
         }
   }
   return;
}
void epoha(int br){
   for(int it=1;it<=5*eN;it++)
      swap(example[rng()%eN+1],example[rng()%eN+1]);

   for(int i=1;i<=eN;i++){
      if((i&1023)==0)
         cout<<i<<" od "<<eN<<" "<<(clock()-poc)/1000.0<<endl;
      C2.popuni(0);
      testiraj(example[i]);
      backprop();
   }
   int kol=0;
   ld ugreska=0;
   for(int i=1;i<=tN;i++){
      kol+=testiraj(tests[i]);
      for(int j=0;j<C.N;j++)
         ugreska+=C.mat[j][0];
   }
   cout<<"EPOHA "<<br<<endl;
   cout<<"VREME "<<(clock()-poc)/1000.0<<endl;
   cout<<kol<<" "<<tN<<" "<<ugreska<<endl;
/*
   ofstream ouf;
   ouf.open("Mreza.txt");
   ouf<<N<<"\n";
   for(int i=1;i<=N;i++)
      ouf<<koliko[i]<<" ";
   ouf<<"\n";
   for(int i=2;i<=N;i++){
      bias[i].ispisi(ouf,true);
      grane[i].ispisi(ouf,true);
   }
   ouf.close();*/
}
int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   cin>>N>>eta;
   for(int i=2;i<=N+1;i++)
      cin>>koliko[i];
   unesitest();
   //return 0;
   poc=clock();
   int v1=0,v2=0;
   koliko[1]=dsize;
   koliko[N+2]=osize;
   N+=2;
   C2.mresize(koliko[N],1);
   slojevi[1].mresize(koliko[1],1);
   for(int i=2;i<=N;i++){
      slojevi[i].mresize(koliko[i],1);
      grane[i].mresize(koliko[i],koliko[i-1]);
      bias[i].mresize(koliko[i],1);
   }
   slojevi[N].mresize(koliko[N],1);
   for(int i=1;i<N;i++){
      grane[i].mrandom(-1,1);
      bias[i+1].mrandom(-1,1);
   }
   for(int i=1;i<=10;i++)
      epoha(i);
   return 0;
}
