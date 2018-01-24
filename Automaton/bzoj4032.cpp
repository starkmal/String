#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2005;
#define NULL 0

struct Sam{
	struct Node{
		Node *Son[26],*Par;
		int Max,Size,id;
	}pool[N];
	typedef Node* Iterator;
	Iterator Root,null,tl;
	int Totn=0;
	void Sec(const Iterator& p){
		for(int i=0;i<26;i++)p->Son[i]=null;
		p->Par=null;
		p->id=Totn++;
	}
	void Init(){
		null=tl=pool;
		Root=++tl;
		Sec(null),Sec(Root);
	}
	void Build(char *c){
		int i,t;
		Init();
		Iterator np,p,q,nq,last=Root;
		for(i=0;i<strlen(c);i++){
			t=c[i]-'a';
			np=++tl,Sec(np);
			np->Max=last->Max+1;
			np->Size=1;
			for(p=last;p!=null&&p->Son[i]==null;p=p->Par)
				p->Son[t]=np;
			if(p==null)np->Par=Root;
			else{
				nq=++tl,Sec(nq);
				nq->Max=p->Max+1;
				nq->Par=q->Par;
				memcpy(nq->Son,q->Son,sizeof(q->Son));
				q->Par=np->Par=nq;
				for(;p!=null&&p->Son[t]==q;p=p->Par)p->Son[t]=nq;
			}
			last=np;
		}
	}
	Iterator begin(){return Root;}
	Iterator end(){return null;}
}SA,SB;

struct Pam{
	struct Node{
		Node* Son[26];
		int id;
	}pool[N];
	typedef Node* Iterator;
	Iterator Root,null,tl;
	int Totn=0;
	void Sec(const Iterator& p){
		for(int i=0;i<26;i++)p->Son[i]=null;
		p->id=Totn++;
	}
	void Init(){
		null=tl=pool;
		Root=++tl;
		Sec(null),Sec(Root);
	}
	void Build(char* c){
		Init();
		Iterator Last[26];
		for(int i=0;i<26;i++)Last[i]=null;
		for(int i=0;i<strlen(c);i++)Sec(&pool[i+2]);
		for(int i=strlen(c)-1;i>=0;i--){
			memcpy(pool[i+2].Son,Last,sizeof(Last));
			Last[c[i]]=&pool[i+2];
		}
		memcpy(Root->Son,Last,sizeof(Last));
	}
	Iterator begin(){return Root;}
	Iterator end(){return null;}
}PA,PB;

int n,m;
char A[N],B[N];
void Solve1(){
	int ans=1e9,i,j,k,t;
	for(i=1;i<=n;i++){
		j=i,k=0,t=A[i];
		for(Sam::Iterator it=SB.begin();it!=SB.end();it=it->Son[t])
			k++,t=A[++j];
		ans=min(ans,k);
	}
	printf("%d\n",ans);
}
void Solve2(){
	int ans=1e9,i,j,k,t;
	for(i=1;i<=n;i++){
		j=i,k=0,t=A[i];
		for(Pam::Iterator it=PB.begin();it!=PB.end();it=it->Son[t])
			k++,t=A[++j];
		ans=min(ans,k);
	}
	printf("%d\n",ans);
}
struct Data{
	Pam::Iterator a;
	Sam::Iterator b;
	int len;
};
void Solve3(){
	queue<Data>q;
	q.push((Data){PA.begin(),SB.begin(),0});
	Data x;
	Pam::Iterator a;
	Sam::Iterator b;
	while(!q.empty()){
		x=q.front();q.pop();
		a=x.a,b=x.b;
		for(int i=0;i<26;i++){
			if(a->Son[i]!=PA.end()&&b->Son[i]==SB.end()){
				printf("%d\n",x.len+1);
				return;
			}
			if(a->Son[i]!=PA.end()&&b->Son[i]!=SB.end())
				q.push((Data){a->Son[i],b->Son[i],x.len+1});
		}
	}
}
struct Data2{
	Pam::Iterator a;
	Pam::Iterator b;
	int len;
};
void Solve4(){
	queue<Data2>q;
	q.push((Data2){PA.begin(),PB.begin(),0});
	Data2 x;
	Pam::Iterator a,b;
	while(!q.empty()){
		x=q.front(),q.pop();
		a=x.a,b=x.b;
		for(int i=0;i<26;i++){
			if(a->Son[i]!=PA.end()&&b->Son[i]==PB.end()){
				printf("%d\n",x.len+1);
				return;
			}
			if(a->Son[i]!=PA.end()&&b->Son[i]!=PB.end())
				q.push((Data2){a->Son[i],b->Son[i],x.len+1});
		}
	}
}
int main(){
	scanf("%s%s",A+1,B+1);
	n=strlen(A+1),m=strlen(B+1);
	SA.Build(A),SB.Build(B);
	PA.Build(A),PB.Build(B);
	Solve1();Solve2();
	Solve3();Solve4();
}
