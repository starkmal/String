#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int N=2005;

struct Sam{
	struct Node{
		map<char,Node*>Son;
		Node* Par;
		int Max,Size,id;
		Node(){Par=NULL;}
	}pool[2*N];
	typedef Node* Iterator;
	Iterator Root,tl;
	int Totn=0;
	void Build(char *c){
		Root=tl=pool;
		Iterator np,p,q,nq,last=Root;
		for(int i=0;i<strlen(c);i++){
			char t=c[i];
			np=++tl;
			np->Max=last->Max+1;
			np->Size=1;
			for(p=last;p!=NULL&&!p->Son.count(t);p=p->Par)
				p->Son[t]=np;
			if(p==NULL)np->Par=Root;
			else{
				q=p->Son[t];
				if(q->Max==p->Max+1)np->Par=q;
				else{
					nq=++tl;
					nq->Max=p->Max+1;
					nq->Par=q->Par;
					nq->Son=q->Son;
					q->Par=np->Par=nq;
					for(;p!=NULL&&p->Son[t]==q;p=p->Par)p->Son[t]=nq;
				}
			}
			last=np;
		}
	}
	Iterator begin(){return Root;}
	Iterator end(){return NULL;}
}SA,SB;

struct Pam{
	struct Node{
		map<char,Node*>Son;	}pool[N];
	typedef Node* Iterator;
	Iterator Root,tl;
	void Build(char* c){
		map<char,Iterator>Last;
		Root=tl=pool;
		for(int i=strlen(c)-1;i>=0;i--){
			pool[i+1].Son=Last;
			Last[c[i]]=&pool[i+1];
		}
		Root->Son=Last;
	}
	Iterator begin(){return Root;}
	Iterator end(){return NULL;}
}PA,PB;

int n,m;
char A[N],B[N];
void Solve1(){
	int ans=1e9,i,j,k;
	for(i=1;i<=n;i++){
		j=i,k=1;
		Sam::Iterator it;
		for(it=SB.begin();
			j<=n&&it->Son.count(A[j]);
			it=it->Son[A[j]],k++,j++);
		if(j<=n&&!it->Son.count(A[j]))ans=min(ans,k);
	}
	if(ans!=1e9)printf("%d\n",ans);
	else puts("-1");
}
void Solve2(){
	int ans=1e9,i,j,k;
	for(i=1;i<=n;i++){
		j=i,k=1;
		Pam::Iterator it;
		for(it=PB.begin();
			j<=n&&it->Son.count(A[j]);
			it=it->Son[A[j]],k++,j++);
		if(j<=n&&!it->Son.count(A[j]))ans=min(ans,k);
	}
	if(ans!=1e9)printf("%d\n",ans);
	else puts("-1");
}
int f[N][N];
int Solve3(Pam::Iterator ita,Sam::Iterator itb,int len){
	int i=ita-PA.begin(),j=itb-SB.begin();
	if(f[i][j])return f[i][j];
	f[i][j]=1e9;
	for(map<char,Pam::Iterator>::iterator it=ita->Son.begin();
		it!=ita->Son.end();it++)
			if(!itb->Son.count(it->first))
				return f[i][j]=len+1;
	for(map<char,Pam::Iterator>::iterator it=ita->Son.begin();
		it!=ita->Son.end();it++)
			if(itb->Son.count(it->first))
				f[i][j]=min(f[i][j],Solve3(it->second,itb->Son[it->first],len+1));
}
int Solve4(Pam::Iterator ita,Pam::Iterator itb,int len){
	int i=ita-PA.begin(),j=itb-PB.begin();
	if(f[i][j])return f[i][j];
	f[i][j]=1e9;
	for(map<char,Pam::Iterator>::iterator it=ita->Son.begin();
		it!=ita->Son.end();it++)
			if(!itb->Son.count(it->first))
				return f[i][j]=len+1;
	for(map<char,Pam::Iterator>::iterator it=ita->Son.begin();
		it!=ita->Son.end();it++)
			if(itb->Son.count(it->first))
				f[i][j]=min(f[i][j],Solve4(it->second,itb->Son[it->first],len+1));
}
int main(){
	scanf("%s%s",A+1,B+1);
	n=strlen(A+1),m=strlen(B+1);
	SA.Build(A+1),SB.Build(B+1);
	PA.Build(A+1),PB.Build(B+1);
	Solve1();Solve2();

	Solve3(PA.begin(),SB.begin(),0);
	if(f[0][0]!=1e9)printf("%d\n",f[0][0]);
	else puts("-1");

	memset(f,0,sizeof(f));
	Solve4(PA.begin(),PB.begin(),0);
	if(f[0][0]!=1e9)printf("%d\n",f[0][0]);
	else puts("-1");
}
