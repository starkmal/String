#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=400005,M=20000005,ALPHA=27;
#define RG register
#define IL __inline__ __attribute__((always_inline))

IL int _R(){
	RG int d=0;RG bool ty;RG char t;
	while(t=getchar(),(t<'0'||t>'9')&&t!='-');
	ty=t=='-'?0:1;d=t-'0';
	while(t=getchar(),t>='0'&&t<='9')d=(d<<3)+(d<<1)+t-'0';
	return ty?d:-d;
}
IL int _S(RG char *c){
	RG char *t=c,ch;
	while(ch=getchar(),ch==' '||ch=='\n'||ch=='\r');
	*t++=ch;
	while(ch=getchar(),ch!=' '&&ch!='\n'&&ch!='\r')*t++=ch;
	*t=0;
	return t-c;
}

struct Node{
	Node *Son[2];
	int val;
}pool[M],*root[N],*tl,*null;
IL void Init(){
	null=tl=pool;
	null->Son[0]=null->Son[1]=null;
	for(RG int i=0;i<N-5;i++)root[i]=null;
}
IL void Update(RG Node* p){
	p->val=p->Son[0]->val+p->Son[1]->val;
}
void Modify(RG Node* &p,RG int l,RG int r,RG int k,RG int d){
	if(p==null)p=++tl,p->Son[0]=p->Son[1]=null;
	if(l==r){
		p->val=d;
		return;
	}
	RG int mid=l+r>>1;
	if(k<=mid)Modify(p->Son[0],l,mid,k,d);
	else Modify(p->Son[1],mid+1,r,k,d);
	Update(p);
}
int Query(RG Node* p,RG int l,RG int r,RG int x,RG int y){
	if(p==null)return 0;
	if(x<=l&&r<=y)return p->val;
	RG int mid=l+r>>1,sum=0;
	sum+=x<=mid?Query(p->Son[0],l,mid,x,y):0;
	sum+=mid<y?Query(p->Son[1],mid+1,r,x,y):0;
	return sum;
}


int Son[N][ALPHA],Max[N],Par[N],last,tot;
IL void exsam(RG char c){
	RG int t=c-'a',np=++tot,nq,p,q;
	Max[np]=Max[last]+1;
	for(p=last;p&&!Son[p][t];p=Par[p])
		Son[p][t]=np;
	if(!p)Par[np]=1;
	else{
		q=Son[p][t];
		if(Max[q]==Max[p]+1)Par[np]=q;
		else{
			nq=++tot;
			memcpy(Son[nq],Son[q],sizeof(Son[q]));
			Max[nq]=Max[p]+1;
			Par[nq]=Par[q];

			Par[q]=Par[np]=nq;
			for(;p&&Son[p][t]==q;p=Par[p])
				Son[p][t]=nq;
		}
	}
	last=np;
}


int Tote,Last[N],Next[N<<1],End[N<<1];
IL void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int Ref[N],Ref2[N],Fa[N][20],In[N],Out[N],vtt;
void Dfs(int x){
	In[x]=++vtt;
	for(RG int i=1,y=Fa[x][0];i<=18;i++)y=Fa[x][i]=Fa[y][i-1];
	for(RG int i=Last[x];i;i=Next[i])Fa[End[i]][0]=x,Dfs(End[i]);
	Out[x]=vtt;
}


int n,m,q;
IL int GetSum(RG int x,RG int l,RG int r){
	if(!x)return 0;
	RG int rt=0;
	for(RG int i=x;i;i^=i&-i)rt+=Query(root[i],1,m,l,r);
	return rt;
}
IL void Change(RG int x,RG int y){
	for(RG int i=In[Ref2[x]];i<=tot;i+=i&-i)Modify(root[i],1,m,x,y);
}
 int GetAns(RG int l,RG int r,RG int pl,RG int pr){
	RG int i,j,k=Ref[r],x=r-l+1;
	for(i=18;i>=0;i--)
		if(Max[Fa[k][i]]>=x)k=Fa[k][i];
	return GetSum(Out[k],pl+x-1,pr)-GetSum(In[k]-1,pl+x-1,pr);
}
char S[N],T[N];
void Solve(){
	RG int i,j,k,opt,l,r,pl,pr,ans=0;
	RG char *c;
	m=_S(T),n=_S(S);
	last=++tot;
	for(c=S,i=1;i<=n;c++,i++)exsam(*c),Ref[i]=last;
	exsam('z'+1);
	for(c=T,i=1;i<=m;c++,i++)exsam(*c),Ref2[i]=last;
	for(i=2;i<=tot;i++)
		Ins(Par[i],i);
	Dfs(1);
	for(i=1;i<=m;i++)Change(i,_R());

	q=_R();
	for(i=1;i<=q;i++){
		opt=_R();
		if(opt==1)l=_R()^ans,r=_R()^ans,Change(l+1,r);
		else{
			l=_R(),r=_R(),pl=_R(),pr=_R();
			ans=GetAns((l^ans)+1,(r^ans)+1,(pl^ans)+1,(pr^ans)+1);
			printf("%d\n",ans);
		}
	}

	for(i=1;i<=tot;i++){
		for(j=0;j<ALPHA;j++)
			Son[i][j]=0;
		Par[i]=0;
		Last[i]=0;
		root[i]=null;
	}
	Tote=tot=vtt=0;
}
int main(){
	RG int T=_R();
	Init();
	while(T--)Solve();
}
