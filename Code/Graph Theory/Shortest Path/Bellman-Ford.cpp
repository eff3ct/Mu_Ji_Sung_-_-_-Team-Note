//have to include these headers
#include <vector>
#include <utility>
#define INF 987654321

using namespace std;

int N;
vector<int> dist(N, INF);

//O(VE) bellman ford algorithm
void bellman_ford(vector<vector<pair<int, int>>> adj, int start) {
    dist[start] = 0;

    //update dist
    for(int i = 1; i <= (N - 1); ++i) { //after repeat N - 1 times, it completes.
        for(int j = 1; j <= N; ++j) {
            for(auto& edge : adj[j]) { //edge.first = destination, edge.second = distance
                dist[edge.first] = min(dist[j] + edge.second, dist[edge.first]);
            }
        }
    }

    //check negative cycle
    for(int i = 1; i <= N; ++i) {
        for(auto& edge : adj[i]) {
            if(dist[edge.first] > dist[i] + edge.second) { //if dist changes, it means that it has negative cycle
                //cout << "YES\n";
                return;
            }
        }
    }

    //cout << "NO\n";
}