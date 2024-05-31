#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

//cnf sat ki convert cheyali next output to a file callets text.satinput
vector<vector<int>> CNFconv(int n, int m, int k1, int k2, map<pair<int, int>,bool> edges) {
    vector<vector<int>> clauses;
    int count=0;

    vector<vector<int>> variables(n + 1, vector<int>(n+1));
    vector<vector<int>> variables1(n + 1, vector<int>(n+1));
    vector<vector<int>> variables2(n + 1, vector<int>(n+1));
    vector<vector<int>> variables3(n + 1, vector<int>(n+1));
    vector<vector<int>> variables4(n + 1, vector<int>(n+1));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2; j++) {
            variables[i][j] = i + (j - 1) * n;
        }
    }
    int cnt = 2*n + 1;
    for (int i = 1; i <= n-1; i++) {
        for (int j = 1; j <= k1; j++) {
            variables1[i][j] = cnt;
            cnt++;
        }
    }
    for (int i = 1; i <= (n-1); i++) {
        for (int j = 1; j <= k2; j++) {
            variables2[i][j] = cnt;
            cnt++;
        }
    }
    for (int i = 1; i <= (n-1); i++) {
        for (int j = 1; j <= n-k1; j++) {
            variables3[i][j] = cnt;
            cnt++;
        }
    }
    for (int i = 1; i <= (n-1); i++) {
        for (int j = 1; j <= n-k2; j++) {
            variables4[i][j] = cnt;
            cnt++;
        }
    }

    // for(int i =1;i<n+1;i++){
    //     clauses.push_back({variables[i][1],variables[i][2],-variables[i][1], 0});
    //     count++;
    // }
    //  for(int i =1;i<n+1;i++){
    //     clauses.push_back({variables[i][1],variables[i][2],-variables[i][2], 0});
    //     count++;
    // }
    for(int i =1;i<n+1;i++){
        for(int j=i+1;j<n+1;j++){
            if(!edges.count({i,j})){
                clauses.push_back({-variables[i][1],-variables[j][1], 0});
                clauses.push_back({-variables[i][2],-variables[j][2], 0});
                count = count + 2;
            }
        }
    }
    for(int i =1;i<n+1;i++){
        clauses.push_back({-variables[i][1],-variables[i][2], 0});
        count++;
    }
    
    //k1
    clauses.push_back({-variables[1][1],variables1[1][1], 0});
    count =count+1;

    for(int j =2;j<=k1;j++){
        clauses.push_back({-variables1[1][j], 0});
        count++;
    }

    for(int i=2;i<n;i++){
        clauses.push_back({-variables[i][1],variables1[i][1], 0});
        count++;
        clauses.push_back({-variables1[i-1][1],variables1[i][1], 0});
        count++;
        for(int j =2;j<=k1;j++){
            clauses.push_back({-variables[i][1],-variables1[i-1][j-1],variables1[i][j], 0});
            clauses.push_back({-variables1[i-1][j],variables1[i][j], 0});
            count=count+2;
        }
        clauses.push_back({-variables[i][1],-variables1[i-1][k1], 0});
        count++;
    }

    clauses.push_back({-variables[n][1],-variables1[n-1][k1], 0});
    count++;

    //k2
    clauses.push_back({-variables[1][2],variables2[1][1], 0});
    count =count+1;

    for(int j =2;j<=k2;j++){
        clauses.push_back({-variables2[1][j], 0});
        count++;
    }

    for(int i=2;i<n;i++){
        clauses.push_back({-variables[i][2],variables2[i][1], 0});
        count++;
        clauses.push_back({-variables2[i-1][1],variables2[i][1], 0});
        count++;
        for(int j =2;j<=k2;j++){
            clauses.push_back({-variables[i][2],-variables2[i-1][j-1],variables2[i][j], 0});
            clauses.push_back({-variables2[i-1][j],variables2[i][j], 0});
            count=count+2;
        }
        clauses.push_back({-variables[i][2],-variables2[i-1][k2], 0});
        count++;
    }

    clauses.push_back({-variables[n][2],-variables2[n-1][k2], 0});
    count++;

    //n-k1
    clauses.push_back({variables[1][1],variables3[1][1], 0});
    count =count+1;

    for(int j =2;j<=n-k1;j++){
        clauses.push_back({-variables3[1][j], 0});
        count++;
    }

    for(int i=2;i<n;i++){
        clauses.push_back({variables[i][1],variables3[i][1], 0});
        count++;
        clauses.push_back({-variables3[i-1][1],variables3[i][1], 0});
        count++;
        for(int j =2;j<=n-k1;j++){
            clauses.push_back({variables[i][1],-variables3[i-1][j-1],variables3[i][j], 0});
            clauses.push_back({-variables3[i-1][j],variables3[i][j], 0});
            count=count+2;
        }
        clauses.push_back({variables[i][1],-variables3[i-1][n-k1], 0});
        count++;
    }

    clauses.push_back({variables[n][1],-variables3[n-1][n-k1], 0});
    count++;

    //n-k2
    clauses.push_back({variables[1][2],variables4[1][1], 0});
    count =count+1;

    for(int j =2;j<=n-k2;j++){
        clauses.push_back({-variables4[1][j], 0});
        count++;
    }

    for(int i=2;i<n;i++){
        clauses.push_back({variables[i][2],variables4[i][1], 0});
        count++;
        clauses.push_back({-variables4[i-1][1],variables4[i][1], 0});
        count++;
        for(int j =2;j<=n-k2;j++){
            clauses.push_back({variables[i][2],-variables4[i-1][j-1],variables4[i][j], 0});
            clauses.push_back({-variables4[i-1][j],variables4[i][j], 0});
            count=count+2;
        }
        clauses.push_back({variables[i][2],-variables4[i-1][n-k2], 0});
        count++;
    }

    clauses.push_back({variables[n][2],-variables4[n-1][n-k2], 0});
    count++;

    return clauses;
}

int main(int argc, char* argv[]) {
    int v, e, k1, k2;

    map<pair<int, int>,bool> edges;
    
    string ss = argv[1];

    ifstream inp(ss+".graph");
    if (!inp) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }

    inp >> v >> e >> k1 >> k2;
    for (int i = 0; i < e; i++) {
        int u, v;
        inp >> u >> v;
        edges[{u,v}]=true;
        edges[{v,u}]=true;
    }


    //cout<<edges[{1,7}]<<endl;
    vector<vector<int>> cnfFormula = CNFconv(v, e, k1, k2, edges);

    ofstream output_file(ss+".satinput");
    ostream_iterator<int> output_iterator(output_file, " ");
    for ( int i = 0 ; i < cnfFormula.size() ; i++ ){
        copy(cnfFormula.at(i).begin(), cnfFormula.at(i).end(), output_iterator);
        output_file << '\n';
    }
}
