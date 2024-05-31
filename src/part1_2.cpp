#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

int main(int argc, char* argv[]) {
    int v, e, k1, k2;

    string ss = argv[1];
    string s;
    vector<int> var;
    vector<int> G1;
    vector<int> G2;
    ifstream inp(ss+".graph");

    if (!inp) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }

    inp >> v >> e >> k1 >> k2;

    ifstream inp1(ss+".satoutput");

    if (!inp1) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }
    
    inp1>>s;
    if(s == "SAT"){
        for(int i=0;i<2*v;i++){
            int p;
            inp1 >> p;
            var.push_back(p);
        }
        for (int i=0;i<v;i++){
            if (var[i]>0){
                int c = var[i];
                G1.push_back(c);
            }
        }

        for (int i=v;i<2*v;i++){
            if (var[i]>0){
                int c = var[i]-v;
                G2.push_back(c);
            }
        }
        ofstream output_file(ss+".mapping");

        output_file<<"#"<<1<<endl;

        for (int i=0; i<G1.size()-1; ++i){  
            output_file << G1[i] << ' ';
        }
        output_file << G1[k1-1] <<endl;
        output_file<<"#"<<2<<endl;
        for (int i=0; i<G2.size()-1; ++i){  
            output_file << G2[i] << ' ';
        }
        output_file << G2[k2-1];
    }
    else{
        ofstream output_file(ss+".mapping");
        output_file<<0<<endl;
    }
    
}
