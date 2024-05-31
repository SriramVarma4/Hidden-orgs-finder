#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

//cnf sat ki convert cheyali next output to a file callets text.satinput
vector<vector<int>> CNFconv(int n, int m, map<pair<int, int>,bool> edges,int p) {
    vector<vector<int>> clauses;
    string formula = " ";
    int count=0;

    vector<vector<int>> variables(n + 1, vector<int>(3));
    vector<vector<int>> variables1(n + 1, vector<int>(n+1));
    vector<vector<int>> variables3(n + 1, vector<int>(n+1));

    int k1=p ;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 1; j++) {
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
        for (int j = 1; j <= n-k1; j++) {
            variables3[i][j] = cnt;
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
                //clauses.push_back({-variables[i][2],-variables[j][2], 0});
                count = count + 1;
            }
        }
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

    for(int i =1;i<n+1;i++){
        clauses.push_back({variables[i][1],-variables[i][1], 0});
        count++;
    }
    return clauses;
}

int main(int argc, char* argv[]) {
    int v, e;

    map<pair<int, int>,bool> edges;

    string ss=argv[1];

    ifstream inp(ss+".graph");
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

    int z = v;
    int l =0;
    int h =v;

    vector<vector<int>> cnfFormula = CNFconv(v, e, edges,z);

    ofstream output_file(ss+".satinput");
    ostream_iterator<int> output_iterator(output_file, " ");
    for ( int i = 0 ; i < cnfFormula.size() ; i++ ){
        copy(cnfFormula.at(i).begin(), cnfFormula.at(i).end(), output_iterator);
        output_file << '\n';
    }
    output_file.close();
    
    string aa = ss + ".satinput";
    string bb = ss + ".satoutput";
    string cc = "./minisat";
    string str = cc +" "+aa+" "+ bb; 
    const char* command = str.c_str();

    system(command);

    string s;
    ifstream inp1(bb);
    if (!inp1) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }
    inp1>>s;

    if(s=="SAT"){
        z=v;
    }
    else{
        string check;
        while(l<=h ){
            int t= l + (h-l)/2;
            vector<vector<int>> cnfFormula1 = CNFconv(v, e, edges,t);

            ofstream output_file(ss+".satinput");
            ostream_iterator<int> output_iterator(output_file, " ");
            for ( int i = 0 ; i < cnfFormula1.size() ; i++ ){
                copy(cnfFormula1.at(i).begin(), cnfFormula1.at(i).end(), output_iterator);
                output_file << '\n';
            }
            output_file.close();

            string aa = ss + ".satinput";
            string bb = ss + ".satoutput";
            string cc = "./minisat";
            string str = cc +" "+aa+" "+ bb; 
            const char* command = str.c_str();

            system(command);

            string check;
            ifstream inp1(ss+".satoutput");
            if (!inp1) {
                cout << "Error: Cannot open input file." << endl;
                return 1;
            }
            inp1>>check;
            
            if(l==h && check =="SAT"){
                break;
            }
            else if(l==h && check =="UNSAT"){
                vector<vector<int>> cnfFormula1 = CNFconv(v, e, edges,l-1);
                ofstream output_file(ss+".satinput");
                ostream_iterator<int> output_iterator(output_file, " ");
                for ( int i = 0 ; i < cnfFormula1.size() ; i++ ){
                    copy(cnfFormula1.at(i).begin(), cnfFormula1.at(i).end(), output_iterator);
                    output_file << '\n';
                }
                output_file.close();
                string aa = ss + ".satinput";
                string bb = ss + ".satoutput";
                string cc = "./minisat";
                string str = cc +" "+aa+" "+ bb; 
                const char* command = str.c_str();
                system(command);
                break;
            }
            else if(check=="SAT"){
                l=t+1;
            }
            else{
                h=t-1;
            }
        }
    }

    string sss;

    ifstream inp3(ss+".satoutput");

    if (!inp3) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }
    
    inp3>>sss;
    if(sss=="SAT"){
        vector<int> var;
        for(int i=0;i<v;i++){
            int p;
            inp3 >> p;
            if(p>0){
                var.push_back(p);
            }
        }

        ofstream output_file1(ss+".mapping");

        output_file1<<"#"<<1<<endl;

        for (int i=0; i<var.size()-1; ++i){  
            output_file1 << var[i] << ' ';
        }
        int tt = var.size();
        output_file1<<var[tt-1];
    }
    else{
        ofstream output_file1(ss+".mapping");
        output_file1<<0<<endl;
    }
}
