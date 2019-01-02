#include <bits/stdc++.h>
#define REP(i,n) for (long i=0;i<(n);i++)
#define FOR(i,a,b) for (long i=(a);i<(b);i++)
#define RREP(i,n) for(long i=n;i>=0;i--)
#define RFOR(i,a,b) for(long i=(a);i>(b);i--)
#define dump1d_arr(array) REP(i,array.size()) cerr << #array << "[" << (i) << "] ==> " << (array[i]) << endl;
#define dump2d_arr(array) REP(i,array.size()) REP(j,array[i].size()) cerr << #array << "[" << (i) << "]" << "[" << (j) << "] ==> " << (array[i][j]) << endl;
#define dump(x)  cerr << #x << " => " << (x) << endl;
#define CLR(vec) { REP(i,vec.size()) vec[i] = 0; } 
#define llINF (long long) 9223372036854775807
#define loINF (long) 2147483647
#define shINF (short) 32767
#define SORT(c) sort((c).begin(),(c).end())
 
using namespace std;
typedef vector<long> VI;
typedef vector<VI> VVI;
 
// グラフのdfs
VI sorted_ver;
VI used;
VVI edge;
 
long dfs(long node){
    if (used[node] == 1) return (-1);
    if (used[node] == 2) return 0;
    used[node] = 1;
    REP(i,edge[node].size()) {
        if(dfs(edge[node][i]) == (-1)) return (-1);
    }
    used[node] = 2;
    sorted_ver.push_back(node);
    return 0;
}
 
int main(void){
    long V,E;
    cin >> V >> E;
    sorted_ver = VI(0);
    used = VI(V,0);
    edge = VVI(V,VI(0));
 
    REP(i,E){
        long s,t;
        cin >> s >> t;
        edge[s].push_back(t);
    }
 
    REP(i,V){
        if (used[i] != 2) {
            if (dfs(i) == (-1)) {
                cout << "CYCLE EXIST" << endl;
                exit(0);
            }
        }
    }
     
    #ifdef DEBUG
        dump2d_arr(edge);
        dump1d_arr(sorted_ver);
    #endif
    RREP(i,sorted_ver.size()-1) cout << sorted_ver[i] << endl;
 
    return 0;
}