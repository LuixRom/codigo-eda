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
            sparse_table.emplace_back(n - (1 << (k-1)) + 1);
            sparse_table[k].resize(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                sparse_table[k][i] = min(sparse_table[k-1][i], sparse_table[k-1][i + (1 << (k-1))]);
            }
        }
    }

    int query(int l, int r) {
        int length = r - l + 1;
        int d = 31 - __builtin_clz(length);
        return min(sparse_table[d][l], sparse_table[d][r - (1 << d) + 1]);
    }
};


struct SparseTableMax {
    vector<vector<int>> tbl;

    SparseTableMax() {}

    SparseTableMax(vector<int>& a) {
        int n = a.size();
        tbl.clear();
        tbl.emplace_back(a);
        for (int k = 1; (1 << k) <= n; k++) {
            tbl.emplace_back(n - (1 << (k-1)) + 1);
            tbl[k].resize(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                tbl[k][i] = max(tbl[k-1][i],tbl[k-1][i + (1 << (k-1))]);
            }
        }
    }

    int query(int l, int r) {
        int length = r - l + 1;
        int d = 31 - __builtin_clz(length);
        return max(tbl[d][l], tbl[d][r - (1 << d) + 1]);
    }
};

struct SparseTableIdx{
    vector<vector<int>> tbl;
    vector<int>* depRef;

    SparseTableIdx() : depRef(nullptr) {}

    SparseTableIdx(vector<int>& dep) : depRef(&dep) {
        int n = dep.size();
        tbl.assign(1, vector<int>(n));
        for (int i = 0; i < n; i++) tbl[0][i] = i;

        for (int k = 1; (1 << k) <= n; k++) {
            int sz = n - (1 << k) + 1;
            tbl.push_back(vector<int>(sz));
            for (int i = 0; i < sz; i++) {
                int x = tbl[k-1][i];
                int y = tbl[k-1][i + (1 << (k-1))];
                tbl[k][i] = ((*depRef)[x] <= (*depRef)[y]) ? x : y;
            }
        }
    }

    int queryIdx(int l, int r) {
        int length = r - l + 1;
        int d = 31 - __builtin_clz(length);
        int x = tbl[d][l];
        int y = tbl[d][r - (1 << d) + 1];
        return ((*depRef)[x] <= (*depRef)[y]) ? x : y;
    }
}


int main(){

    ios::sync_with_stdio(false);

    cin.tie(0);

    int N, R;

    cin >> N >>R;
    
    vector<int> ciudadA(R), ciudadB(R), costoC(R);

    for(int i=0; i<R; i++){
        cin >> ciudadA[i] >> ciudadB[i] >> costoC[i];
    }



    int Q;

    cin>>Q;

    while (Q--) {
        int u, v;
        cin >> u >> v;
        int pesoConsulta = pesoArista[{u, v}];

        if (estaEnMST.count({u, v})) {
            cout << costoMST << "\n";
        } else {
            int maxEnCamino = arbol.consultarMaxArista(u, v);
            cout << costoMST - maxEnCamino + pesoConsulta << "\n";
        }
    }

    return 0;
}