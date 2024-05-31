#include <minisat-master/minisat/core/Solver.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

//cnf sat ki convert cheyali next output to a file callets text.satinput
vector<vector<int>> createCNFFormula(int n, int m, map<pair<int, int>,bool> edges) {
    vector<vector<int>> clauses;
    string formula = " ";
    int count=0;

    vector<vector<Minisat::Var>> variables(n + 1, vector<Minisat::Var>(3));
    vector<vector<Minisat::Var>> variables1(n + 1, vector<Minisat::Var>(3));
    vector<vector<Minisat::Var>> variables3(n + 1, vector<Minisat::Var>(3));

    using Minisat::mkLit;
    using Minisat::lbool;

    Minisat::Solver solver;

    int k1=4 ;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 1; j++) {
            variables[i][j] = solver.newVar();
        }
    }
    int cnt = 2*n + 1;
    for (int i = 1; i <= n-1; i++) {
        for (int j = 1; j <= k1; j++) {
            variables1[i][j] = solver.newVar();
            cnt++;
        }
    }
    for (int i = 1; i <= (n-1); i++) {
        for (int j = 1; j <= n-k1; j++) {
            variables3[i][j] = solver.newVar();
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
                //clauses.push_back({-variables[i][1],-variables[j][1], 0});
                solver.addClause(~mkLit(variables[i][1]),~mkLit(variables[j][1]));
                //clauses.push_back({-variables[i][2],-variables[j][2], 0});
                count = count + 1;
            }
        }
    }

    //k1
    //clauses.push_back({-variables[1][1],variables1[1][1], 0});
    solver.addClause(~mkLit(variables[1][1]),~mkLit(variables1[1][1]));
    count =count+1;

    for(int j =2;j<=k1;j++){
        //clauses.push_back({-variables1[1][j], 0});
        solver.addClause(~mkLit(variables1[1][j]));
        count++;
    }

    for(int i=2;i<n;i++){
        //clauses.push_back({-variables[i][1],variables1[i][1], 0});
        solver.addClause(~mkLit(variables[i][1]),mkLit(variables1[i][1]));
        count++;
        //clauses.push_back({-variables1[i-1][1],variables1[i][1], 0});
        solver.addClause(~mkLit(variables1[i-1][1]),mkLit(variables1[i][1]));
        count++;
        for(int j =2;j<=k1;j++){
            //clauses.push_back({-variables[i][1],-variables1[i-1][j-1],variables1[i][j], 0});
            solver.addClause(~mkLit(variables[i][1]),~mkLit(variables1[i-1][j-1]),~mkLit(variables1[i][j]));
            //clauses.push_back({-variables1[i-1][j],variables1[i][j], 0});
            solver.addClause(~mkLit(variables1[i-1][j]),mkLit(variables1[i][j]));
            count=count+2;
        }
        //clauses.push_back({-variables[i][1],-variables1[i-1][k1], 0});
        solver.addClause(~mkLit(variables[i][1]),~mkLit(variables1[i-1][k1]));
        count++;
    }

    //clauses.push_back({-variables[n][1],-variables1[n-1][k1], 0});
    solver.addClause(~mkLit(variables[n][1]),~mkLit(variables1[n-1][k1]));
    count++;

    //n-k1
    //clauses.push_back({variables[1][1],variables3[1][1], 0});
    solver.addClause(mkLit(variables[1][1]),mkLit(variables3[1][1]));
    count =count+1;

    for(int j =2;j<=n-k1;j++){
        //clauses.push_back({-variables3[1][j], 0});
        solver.addClause(~mkLit(variables3[1][j]));
        count++;
    }

    for(int i=2;i<n;i++){
        //clauses.push_back({variables[i][1],variables3[i][1], 0});
        solver.addClause(mkLit(variables[i][1]),mkLit(variables3[i][1]));
        count++;
        //clauses.push_back({-variables3[i-1][1],variables3[i][1], 0});
        solver.addClause(~mkLit(variables3[i-1][1]),mkLit(variables3[i][1]));
        count++;
        for(int j =2;j<=n-k1;j++){
            //clauses.push_back({variables[i][1],-variables3[i-1][j-1],variables3[i][j], 0});
            solver.addClause(mkLit(variables[i][1]),~mkLit(variables3[i-1][j-1]),mkLit(variables3[i][j]));
            //clauses.push_back({-variables3[i-1][j],variables3[i][j], 0});
            solver.addClause(~mkLit(variables3[i-1][1]),mkLit(variables3[i][j]));
            count=count+2;
        }
        //clauses.push_back({variables[i][1],-variables3[i-1][n-k1], 0});
        solver.addClause(mkLit(variables[i][1]),~mkLit(variables3[i-1][n-k1]));
        count++;
    }

    //clauses.push_back({variables[n][1],-variables3[n-1][n-k1], 0});
    solver.addClause(mkLit(variables[n][1]),~mkLit(variables3[n-1][n-k1]));
    count++;

    for(int i =1;i<n+1;i++){
        //clauses.push_back({variables[i][1],-variables[i][1], 0});
        solver.addClause(mkLit(variables[i][1]),~mkLit(variables1[i][1]));
        count++;
    }

    auto sat = solver.solve();

    return clauses;
}

int main() {
    int v, e;

    map<pair<int, int>,bool> edges;

    ifstream inp("newtest.graphs");
    if (!inp) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }

    inp >> v >> e;
    for (int i = 0; i < e; i++) {
        int u, v;
        inp >> u >> v;
        edges[{u,v}]=true;
        edges[{v,u}]=true;
    }

    vector<vector<int>> cnfFormula = createCNFFormula(v, e, edges);

    ofstream output_file("newtest.satinput");
    ostream_iterator<int> output_iterator(output_file, " ");
    for ( int i = 0 ; i < cnfFormula.size() ; i++ ){
        copy(cnfFormula.at(i).begin(), cnfFormula.at(i).end(), output_iterator);
        output_file << '\n';
    }
}
