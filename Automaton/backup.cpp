#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2005;

struct Sam{
		struct Node{
					Node *Son[26],*Par;
							int Max,Size,id;
									Node(){
													for(int i=0;i<26;i++)Son[i]=NULL;
																Par=NULL;
																		}
										}pool[3*N];
			typedef Node* Iterator;
				Iterator Root,tl;
					int Totn=0;
						void Build(char *c){
									int i,t;
											Root=tl=pool;
													Iterator np,p,q,nq,last=Root;
															for(i=0;i<strlen(c);i++){
																			t=c[i]-'a';
																						np=++tl;
																									np->Max=last->Max+1;
																												np->Size=1;
																															for(p=last;p!=NULL&&p->Son[t]==NULL;p=p->Par)
																																				p->Son[t]=np;
																																		if(p==NULL)np->Par=Root;
																																					else{
																																										q=p->Son[t];
																																														if(q->Max==p->Max+1)np->Par=q;
																																																		else{
																																																								nq=++tl;
																																																													nq->Max=p->Max+1;
																																																																		nq->Par=q->Par;
																																																																							memcpy(nq->Son,q->Son,sizeof(q->Son));
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
					Node* Son[26];
							Node(){
											for(int i=0;i<26;i++)Son[i]=NULL;
													}
								}pool[N];
			typedef Node* Iterator;
				Iterator Root,tl;
					void Build(char* c){
								Iterator Last[26];
										for(int i=0;i<26;i++)Last[i]=NULL;
												Root=tl=pool;
														for(int i=strlen(c)-1;i>=0;i--){
																		for(int j=0;j<26;j++)pool[i+1].Son[j]=Last[j];
																					Last[c[i]-'a']=&pool[i+1];
																							}
																for(int j=0;j<26;j++)
																				Root->Son[j]=Last[j];
																	}
						Iterator begin(){return Root;}
							Iterator end(){return NULL;}
}PA,PB;

int n,m;
char A[N],B[N];
void Solve1(){
		int ans=1e9,i,j,k,t;
			for(i=1;i<=n;i++){
						j=i,k=0,t=A[i]-'a';
								Sam::Iterator it;
										for(it=SB.begin();
																it!=SB.end()&&j<=n;
																				it=it->Son[t],t=A[++j]-'a')
															k++;
												if(it==SB.end())ans=min(ans,k);
													}
				if(ans!=1e9)printf("%d\n",ans);
					else puts("-1");
}
void Solve2(){
		int ans=1e9,i,j,k,t;
			for(i=1;i<=n;i++){
						j=i,k=0,t=A[i]-'a';
								Pam::Iterator it;
										for(it=PB.begin();
																it!=PB.end()&&j<=n;
																				it=it->Son[t],t=A[++j]-'a')
															k++;
												if(it==PB.end())ans=min(ans,k);
													}
				if(ans!=1e9)printf("%d\n",ans);
					else puts("-1");
}
int ans;
void Solve3(Pam::Iterator ita,Sam::Iterator itb,int len){
		for(int i=0;i<26;i++)
					if(ita->Son[i]!=PA.end()&&itb->Son[i]==SB.end()){
									ans=min(ans,len+1);
												return;
														}
			for(int i=0;i<26;i++)
						if(ita->Son[i]!=PA.end()&&itb->Son[i]!=SB.end())
										Solve3(ita->Son[i],itb->Son[i],len+1);
}
void Solve4(Pam::Iterator ita,Pam::Iterator itb,int len){
		for(int i=0;i<26;i++)
					if(ita->Son[i]!=PA.end()&&itb->Son[i]==PB.end()){
									ans=min(ans,len+1);
												return;
														}
			for(int i=0;i<26;i++)
						if(ita->Son[i]!=PA.end()&&itb->Son[i]!=PB.end())
										Solve4(ita->Son[i],itb->Son[i],len+1);
}

int main(){
		scanf("%s%s",A+1,B+1);
			n=strlen(A+1),m=strlen(B+1);
				SA.Build(A+1),SB.Build(B+1);
					PA.Build(A+1),PB.Build(B+1);
						Solve1();Solve2();
							ans=1e9;
								Solve3(PA.begin(),SB.begin(),0);
									if(ans==1e9)puts("-1");
										else printf("%d\n",ans);
											ans=1e9;
												Solve4(PA.begin(),PB.begin(),0);
													if(ans==1e9)puts("-1");
														else printf("%d\n",ans);
}
