#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define RG register
#define ll long long
#define IL __inline__ __attribute__((always_inline))
const int N=300005,ALPHA=26;

IL int _R(){
	RG int d=0;RG bool ty;RG char t=getchar();
	while((t<'0'||t>'9')&&t!='-')t=getchar();
	ty=t=='-'?0:1;
	for(;t>='0'&&t<='9';t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return ty?d:-d;
}
IL void _S(RG char *s){
	RG char *t=s,ch;
	while(ch=getchar(),ch==' '||ch=='\n'||ch=='\r');
	*t++=ch;
	while(ch=getchar(),ch!=' '&&ch!='\n'&&ch!='\r')*t++=ch;
	*t=0;
}

struct Node{
	Node *Son[ALPHA],*fail,*fa;
	int flag,dep,sz;
}pool[N],*root,*null,*tl;
IL void Init(){
	null=root=tl=pool;
	for(RG int i=0;i<ALPHA;i+=4){
		null->Son[i]=null;
		null->Son[i+1]=null;
		null->Son[i+2]=null;
		null->Son[i+3]=null;
	}
	null->Son[25]=null;
	null->fail=null;
	null->fa=null;
	null->dep=-1;
	tl++;
}
IL Node* newp(RG Node* p){
	Node *x=tl++;
	x->dep=p->dep+1;
	for(RG int i=0;i<ALPHA;i+=4){
		x->Son[i]=null;
		x->Son[i+1]=null;
		x->Son[i+2]=null;
		x->Son[i+3]=null;
	}
	x->Son[25]=null;
	x->fail=null;
	x->sz=1;
	return x;
}
IL void Insert(RG char* str){
	Node *p=root;
	RG int t;
	for(RG int i=0;i<strlen(str);i++){
		t=str[i]-'a';
		if(p->Son[t]==null)p->Son[t]=newp(p),p->Son[t]->fa=p;
		p=p->Son[t];
	}
	p->flag=1;
}
Node *q[N],**tail,**head;
IL void BuildAC(){
	head=q+1,tail=q;
	root->fail=root;
	for(RG int i=0;i<ALPHA;i++)
		if(root->Son[i]==null)root->Son[i]=root;
		else root->Son[i]->fail=root,++tail,*tail=root->Son[i];
	while(tail-head>=0){
		Node *x=*head;
		head++;
		for(RG int i=0;i<ALPHA;i++)
			if(x->Son[i]==null)x->Son[i]=x->fail->Son[i];
			else x->Son[i]->fail=x->fail->Son[i],++tail,*tail=x->Son[i];
	}
	for(RG Node** x=head-1;x!=q;x--)
		(*x)->fail->sz+=(*x)->sz;
}
IL int GeT(RG Node* p){
	RG Node* x=p;
	p=p->fail;
	if(p==root)return 0;
	for(RG int i=1;i<=p->dep;i++)x=x->fa;
	return x->sz-1;
}
char str[10005][31];
int main(){
	RG int n,i,j,k;
	RG ll cnt,ans;
	while(n=_R()){
		Init();
		root=newp(null);
		for(i=1;i<=n;i++){
			_S(str[i]);
			Insert(str[i]);
		}
		BuildAC();
		cnt=(int)(tl-root)-1;
		ans=cnt*cnt;
		for(RG Node* p=root;p!=tl;p++)ans-=GeT(p);
		printf("%lld\n",ans);
	}
}
