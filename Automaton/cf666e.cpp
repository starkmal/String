#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=1200005,M=40000005,ALPHA=27;
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

struct Node{
	Node* Son[2];
	int max,val;
}pool[M],*root[N],*tl,*null;
IL void Init(){
	null=tl=pool;
	null->Son[0]=null->Son[1]=null;
	for(RG int i=1;i<=N-5;i+=4)
		root[i]=null,
		root[i+1]=null,
		root[i+2]=null,
		root[i+3]=null;
}
IL Node* Copy(RG Node* p){
	Node* x=++tl;
	x->Son[0]=p->Son[0];
	x->Son[1]=p->Son[1];
	x->max=p->max;
	x->val=p->val;
	return x;
}

IL void Update(RG Node* p){
	p->max=p->Son[0]->max>p->Son[1]->max?p->Son[0]->max:p->Son[1]->max;
	p->val=p->Son[0]->max>=p->Son[1]->max?p->Son[0]->val:p->Son[1]->val;
}
void Merge(RG Node* &x,RG Node* y,RG int l,RG int r){
	if(x==null){x=Copy(y);return;}
	if(y==null)return;
	x=Copy(x);
	if(l==r){
		x->max+=y->max;
		x->val=l;
		return;
	}
	RG int mid=l+r>>1;
	Merge(x->Son[0],y->Son[0],l,mid);
	Merge(x->Son[1],y->Son[1],mid+1,r);
	Update(x);
}
void Add(RG Node* &x,RG int l,RG int r,RG int k){
	if(x==null)x=++tl,x->Son[0]=x->Son[1]=null;
	if(l==r){
		x->max++;
		x->val=l;
		return;
	}
	RG int mid=l+r>>1;
	if(k<=mid)Add(x->Son[0],l,mid,k);
	else Add(x->Son[1],mid+1,r,k);
	Update(x);
}
typedef pair<int,int> pii;
pii Query(RG Node* p,RG int l,RG int r,RG int x,RG int y){
	if(x<=l&&r<=y)return pii(p->val,p->max);
	RG int mid=l+r>>1;
	RG pii lm=pii(0,0),rm=pii(0,0);
	if(x<=mid)lm=Query(p->Son[0],l,mid,x,y);
	if(mid<y)rm=Query(p->Son[1],mid+1,r,x,y);
	return lm.second>=rm.second?lm:rm;
}

int Son[N][ALPHA],fail[N],Max[N],last,tot,lable[N];
IL void exsam(RG char c){
	RG int t=c-'a',np=++tot,nq,p,q;
	Max[np]=Max[last]+1;
	for(p=last;p&&!Son[p][t];p=fail[p])
		Son[p][t]=np;
	if(!p)fail[np]=1;
	else{
		q=Son[p][t];
		if(Max[q]==Max[p]+1)fail[np]=q;
		else{
			nq=++tot;
			for(RG int i=0;i<ALPHA;i++)
				Son[nq][i]=Son[q][i];
			Max[nq]=Max[p]+1;
			fail[nq]=fail[q];

			fail[np]=fail[q]=nq;
			for(;p&&Son[p][t]==q;p=fail[p])
				Son[p][t]=nq;
		}
	}
	last=np;
}

int n,m,q;
int Tote,Last[N],Next[N<<1],End[N<<1];
IL void Ins(RG int x,RG int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int Fa[N][20];
void Dfs(int x){
	for(RG int i=1,y=Fa[x][0];i<=18;i++)y=Fa[x][i]=Fa[y][i-1];
	for(RG int u,i=Last[x];i;i=Next[i])
		if((u=End[i])!=Fa[x][0]){
			Fa[u][0]=x;
			Dfs(u);
			Merge(root[x],root[u],1,m);
		}
}
char str[N];
int main(){
	RG int i,j,k;
	RG char *c;
	_S(str);
	last=++tot;
	for(c=str,i=0;*c;i++,c++){
		exsam(*c);
		lable[i]=last;
	}
	m=_R();
	Init();
	for(i=1;i<=m;i++){
		_S(str);
		exsam('z'+1);
		for(c=str;*c;c++){
			exsam(*c);
			Add(root[last],1,m,i);
		}
	}
	for(i=2;i<=tot;i++)
		Ins(fail[i],i),Ins(i,fail[i]);
	Dfs(1);
	q=_R();
	for(i=1;i<=q;i++){
		int l=_R(),r=_R(),pl=_R()-1,pr=_R()-1,x=pr-pl+1;
		k=lable[pr];
		for(j=18;j>=0;j--)
			if(Max[Fa[k][j]]>=x)k=Fa[k][j];
		RG pii ans=Query(root[k],1,m,l,r);
		if(ans.second==0)printf("%d 0\n",l);
		else printf("%d %d\n",ans.first,ans.second);
	}
}
