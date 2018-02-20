#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=50005,M=N<<7,ALPHA=26;
#define RG register
#define IL __inline__ __attribute__((always_inline))

IL int _R(){
	RG int d=0;RG char t;RG bool ty;
	while(t=getchar(),(t<'0'||t>'9')&&t!='-');
	ty=t=='-'?0:1;
	for(;t>='0'&&t<='9';t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return ty?d:-d;
}
IL void _S(RG char *c){
	RG char *t=c,ch;
	while(ch=getchar(),ch==' '||ch=='\n'||ch=='\r');
	*t++=ch;
	while(ch=getchar(),ch!=' '&&ch!='\n'&&ch!='\r')*t++=ch;
	*t=0;
}

namespace Seg{
	struct Node{
		Node* Son[2];
		int max;
	}pool[M],*root[N],*tl,*null;
	IL void Init(){
		null=tl=pool;
		null->Son[0]=null->Son[1]=null;
	}
	IL Node* Copy(RG Node* p){
		Node* x=++tl;
		x->Son[0]=p->Son[0];
		x->Son[1]=p->Son[1];
		x->max=p->max;
		return x;
	}
	IL void Update(RG Node* p){
		p->max=p->Son[0]->max>p->Son[1]->max?p->Son[0]->max:p->Son[1]->max;
	}
	void Merge(RG Node* &x,RG Node* y,RG int l,RG int r){
		if(x==null)return Copy(y);
		if(y==null)return Copy(x);
		x=Copy(x);
		if(l==r){
			x->max+=y->max;
			return;
		}
		RG mid=l+r>>1;
		Merge(x->Son[0],y->Son[0],l,mid);
		Merge(x->Son[1],y->Son[1],mid+1,r,);
		Update(x);
	}
	void Add(RG Node* &x,RG int l,RG int r,RG int k,RG int d){
		if(x==null)x=++tl,x->Son[0]=x->Son[1]=null;
		if(l==r){
			x->max+=d;
			return;
		}
		RG int mid=l+r>>1;
		if(l<=mid)Add(x->Son[0],l,mid,k,d);
		else Add(x->Son[1],mid+1,r,k,d);
		Update(x);
	}
}

int Son[N<<1][ALPHA],fail[N],Max[N],last,tot,root,label[N];
IL void exsam(RG char c){
	RG int t=c-'a',np=++tot,nq,p,q;
	for(p=last;p&&!Son[p][t];p=fail[p])
		Son[p][t]=np;
	if(!p)fail[np]=root;
	else{
		q=Son[p][t];
		if(Max[q]==Max[p]+1)fail[np]=q;
		else{
			nq=++tot;
			for(RG int i=0;i<ALPHA;i+=4)
				Son[nq][i]=Son[q][i],
				Son[nq][i+1]=Son[q][i+1],
				Son[nq][i+2]=Son[q][i+2],
				Son[nq][i+3]=Son[q][i+3];
			Son[nq][25]=Son[q][25];
			Max[nq]=Max[p]+1;
			fail[nq]=fail[q];
			fail[np]=fail[q]=nq;
			for(;p&&Son[p][t]==q;p=fail[p])
				Son[p][t]=nq;
		}
	}
	last=np;
}

char str[N];
int main(){
	RG int n,m,q,i,j,k;
	RG char *c;
	_S(str);
	last=root=++tot;
	for(c=str,i=0;*c;i++,c++)exsam(*c),lable[i]=last;
	m=_R();
	for(i=1;i<=m;i++){
		_S(str);
		exsam('@');
		for(c=str;*c;c++)exsam(c);
	}
	q=_R();
	for(i=1;i<=q;i++){
		
	}
}
