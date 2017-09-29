struct Min_cost_flow {
	// 0-base
	struct Edge {
		int fr,to,flow,cap,cost;
	};
	int V,E;
	vector<Edge> edge;
	vector<int> G[MAXV+5];

	void init(int _V) {
		V=_V;
		E=0;
		for (int i=0;i<V;i++) G[i].clear();
	}
	void add_edge(int fr, int to, int cap, int cost) {
		edge.pb({fr,to,0,cap,cost});
		edge.pb({to,fr,0,0,-cost});
		G[fr].pb(E);
		G[to].pb(E^1);
		E+=2;
	}
	bool SPFA(int src, int dest, int &ans_flow, int &ans_cost) {
		queue<int> que;
		int dist[MAXV+5],pre[MAXV+5],flow[MAXV+5];
		bool inque[MAXV+5];
		for (int i=0;i<V;i++) {
			dist[i]=INF;
			pre[i]=-1;
			inque[i]=false;
			flow[i]=-1;
		}
		dist[src]=0;
		flow[src]=INF;
		inque[src]=true;
		que.push(src);
		while (!que.empty()) {
			int v=que.front(); que.pop();
			inque[v]=false;
			for (auto idx : G[v]) {
				Edge &e=edge[idx];
				if (e.flow<e.cap && dist[e.fr]+e.cost<dist[e.to]) {
					flow[e.to]=min(flow[e.fr],e.cap-e.flow);
					dist[e.to]=dist[e.fr]+e.cost;
					pre[e.to]=idx;
					if (!inque[e.to]) que.push(e.to);
					inque[e.to]=true;
				}
			}
		}
		if (dist[dest]==INF) return false;
		int v=dest;
		ans_flow+=flow[dest];
		ans_cost+=(dist[dest]*flow[dest]);
		while (v!=src) {
			static int num;
			edge[pre[v]].flow+=flow[dest];
			edge[pre[v]^1].flow-=flow[dest];
			v=edge[pre[v]].fr;
		}
		return true;
	}
	PII min_cost_flow(int src, int dest) {
		int ans_flow=0, ans_cost=0;
		while (SPFA(src,dest,ans_flow,ans_cost));
		return make_pair(ans_flow,ans_cost);
	}
};
