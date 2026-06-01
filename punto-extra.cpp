#include<iostream>
#include<vector>

using namespace std;

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