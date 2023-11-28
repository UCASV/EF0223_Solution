#include <iostream>

using namespace std;

int LCS(string A, string B){ 
    int nA = A.length(), nB = B.length();

    int M[nA+1][nB+1];

    for(int i = 0; i <= nA; ++i)
        M[i][0] = 0;

    for(int j = 1; j <= nB; ++j)
        M[0][j] = 0;

    for(int i = 1; i <= nA; ++i)
        for(int j = 1; j <= nB; ++j)
            if( A[i-1] == B[j-1] )
                M[i][j] = 1 + M[i-1][j-1];
            else
                M[i][j] = max( M[i-1][j] , M[i][j-1] );

    return M[nA][nB];
}

int getposition(string* combis, string combi){
    int pos = -1;
    for(int i = 0; i < 25; ++i){
        if(combis[i]==combi){
            pos = i;
            break;
        }
    }
    return pos;
}

int main(void){
    int n;
    string p1, p2;
    string combis[] = {"SS","SA","SQ","SV","SF","AS","AA","AQ","AV","AF","QS","QA","QQ","QV","QF","VS","VA","VQ","VV","VF","FS","FA","FQ","FV","FF"};
    string sym = "abcdefghijklmnopqrstuvwxy";

    cin >> n;

    string S1 = "";
    for(int i = 0; i < n; ++i){
        cin >> p1 >> p2;
        S1 += sym[getposition(combis,p1+p2)];
    }

    cin >> n;

    string S2 = "";
    for(int i = 0; i < n; ++i){
        cin >> p1 >> p2;
        S2 += sym[getposition(combis,p1+p2)];
    }

    cout << "Ichigo should use " << LCS(S1,S2) << " power combinations against the Sternritter.\n";

    return 0;
}
