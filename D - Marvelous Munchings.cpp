#include <iostream>

using namespace std;

int minimum_coin_change(int V, int* C, int n){
    int M[n+1][V+1];

    for(int i = 0; i <= n; ++i)
        M[i][0] = 0;

    for(int j = 1; j <= V; ++j)
        M[0][j] = 9999;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= V; ++j)
            if( C[i-1] <= j )
                M[i][j] = min( 1 + M[i][j-C[i-1]] , M[i-1][j] );
            else
                M[i][j] = M[i-1][j];
    
    return M[n][V];
}

int main(void){
    int W, N;

    cin >> W;
    while(W != -99){
        W *= 1000;

        cin >> N;

        int* ingredients = (int*) malloc(sizeof(int)*N);

        for(int i = 0; i < N; ++i) cin >> ingredients[i];

        cout << minimum_coin_change(W, ingredients, N)*5 << " minutes\n";

        free(ingredients);
        
        cin >> W;
    }

    return 0;
}