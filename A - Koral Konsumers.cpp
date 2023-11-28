#include <iostream>

using namespace std;

int knapsack(int K, int* V, int* W, int n){
    int M[n+1][K+1];

    for(int i = 0; i <= n; ++i)
        M[i][0] = 0;

    for(int j = 1; j <= K; ++j) //Se inicia en la segunda columna
        M[0][j] = 0;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= K; ++j)
            if( W[i-1] <= j )
                M[i][j] = max( V[i-1] + M[i-1][j-W[i-1]] , M[i-1][j] );
            else
                M[i][j] = M[i-1][j];

    return M[n][K];
}

int main(void){
    int P, N;

    cin >> P;
    while(P != -1){
        cin >> N;

        int* fish = (int*) malloc(sizeof(int)*N);
        int* coral = (int*) malloc(sizeof(int)*N);

        for(int i = 0; i < N; ++i){
            cin >> fish[i];
            cin >> coral[i];
        }

        cout << knapsack(P, fish, coral, N) << "\n";

        free(fish);
        free(coral);
        
        cin >> P;
    }

    return 0;
}