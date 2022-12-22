#include <vector>
#include <priority_queue>

vector<int> taken;
priority_queue<pair<int, int>> pq;

void process(int vtx) {
    taken[vtx] = 1;
    for (int j = 0; j < (int) AdjList[vtx].size(); j++) {
        pair<int, int> v = AdjList[vtx][j];
        if (!taken[v].first) {
            pq.push(pair<int, int>(-v.second, -v.first));
        }
    }
}

int prim(int V) {
    int mst_cost = 0;
    taken.assign(V, 0);
    process(0);
    while (!pq.empty()) {
        pair<int, int> front = pq.top(); pq.pop();
        int u = -front.second, w = -front.first;
        if (!taken[u]) {
            mst_cost += w, process(u);
        }
    }
}
