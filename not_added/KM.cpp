#include <bits/stdc++.h>
#define LL long long
using namespace std;

template<class T>
struct KM { //O(V^3), 1-based
	#define INF 0x3f3f3f3f
	// # of vertices in both side must be the same
	// Non-exist edge weight=0
	// g: weight, n: # of vertices
	#define MAXN 1005 // Must add 5 !!
	T g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
	int n,match_y[MAXN],match_x[MAXN],pa[MAXN];
	bool vx[MAXN],vy[MAXN];
	void init(int _n) {
		n=_n;
		memset(g,0,sizeof(g));
	}
	void augment(int y){
		for(int x,z;y;y=z){
			x=pa[y],z=match_x[x];
			match_y[y]=x,match_x[x]=y;
		}
	}
	void bfs(int st){
		for(int i=1;i<=n;++i)slack_y[i]=INF,vx[i]=vy[i]=0;
		queue<int> q;q.push(st);
		for(;;){
			while(q.size()){
				int x=q.front();q.pop();
				vx[x]=1;
				for(int y=1;y<=n;++y)if(!vy[y]){
					int t=lx[x]+ly[y]-g[x][y];
					if(t==0){
						pa[y]=x;
						if(!match_y[y]){augment(y);return;}
						vy[y]=1,q.push(match_y[y]);
					}else if(slack_y[y]>t)pa[y]=x,slack_y[y]=t;
				}
			}
			int cut=INF;
			for(int y=1;y<=n;++y){
				if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
			}
			for(int j=1;j<=n;++j){
				if(vx[j])lx[j]-=cut;
				if(vy[j])ly[j]+=cut;
				else slack_y[j]-=cut;
			}
			for(int y=1;y<=n;++y){
				if(!vy[y]&&slack_y[y]==0){
					if(!match_y[y]){augment(y);return;}
					vy[y]=1,q.push(match_y[y]);
				}
			}
		}
	}
	T km() {
		memset(match_y,0,sizeof(int)*(n+1));
		memset(ly,0,sizeof(int)*(n+1));
		for(int x=1;x<=n;++x){
			lx[x]=-INF;
			for(int y=1;y<=n;++y)
				lx[x]=max(lx[x],g[x][y]);
		}
		for(int x=1;x<=n;++x)bfs(x);
		T ans=0;
		for(int y=1;y<=n;++y)ans+=g[match_y[y]][y];
		return ans;
	}
};

KM<LL> algo;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int m,n,k,N;
	cin>>m>>n>>k;
	N=max(m,n);
	algo.init(N);
	for (int i=0;i<k;i++) {
		int f,t;
		cin>>f>>t;
		cin>>algo.g[f][t];
	}
	cout<<algo.km()<<endl;
	vector<pair<int,int>> ans;
	for (int i=1;i<=n;i++) {
		if (algo.match_x[i]<=m) {
			ans.push_back({i,algo.match_x[i]});
		}
	}
	cout<<ans.size()<<endl;
	for (int i=0;i<ans.size();i++) {
		cout<<ans[i].first<<' '<<ans[i].second<<endl;
	}
}
