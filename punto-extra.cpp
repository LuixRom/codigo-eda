#include<iostream>
#include<vector>
#include <algorithm>
#include <map>

using namespace std;

struct SparseTable {
    vector<vector<int>> sparse_table;

    SparseTable() {}

    SparseTable(vector<int>& a) {
        int n = a.size();
        sparse_table.clear();
        sparse_table.emplace_back(a);
        for (int k = 1; (1 << k) <= n; k++) {
            sparse_table.emplace_back(n - (1 << (k - 1)) + 1);
            sparse_table[k].resize(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                sparse_table[k][i] = min(sparse_table[k-1][i],
                                         sparse_table[k-1][i + (1 << (k-1))]);
            }
        }
    }

    int query(int l, int r) {
        int length = r - l + 1;
        int d = 31 - __builtin_clz(length);
        return min(sparse_table[d][l], sparse_table[d][r - (1 << d) + 1]);
    }
}

int main(){
    int N, R;

    cin >> N >>R;
    
    vector<int> A(R), B(R), C(R);

    for(int i=0; i<R; i++){
        cin>>A[i] >> B[i] >> C[i];
    }
    
    int Q;

    cin>>Q;

    vector<int> U(Q), V(Q);

    for(int i=0; i<Q; i++){
        cin>>U[i] >> V[i];
    }

    return 0;
}