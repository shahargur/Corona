#include <iostream>
#include "../Include/Session.h"
#include "../Include/json.hpp"
#include <fstream>
#include <vector>
using json=nlohmann:: json;

using namespace std;

int main(int argc, char** argv){
  /*  if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }*/

    json readInput;
    ifstream readInput_file("/home/spl211/CLionProjects/208482216-315741454/config1.json", std::ifstream::binary);
    readInput_file >> readInput;
/*    vector<vector<int>> check;
    vector<int> temp;
    for(int i=0; i < readInput["graph"].size();i++){
        for(int j=0;j<readInput["graph"][i].size();j++){
            temp.push_back(readInput["graph"][i][j]);
        }
        check.push_back(temp);
        temp.clear();
    }
    for(int i=0; i < check.size();i++){
        for(int j = 0; j < check[i].size();j++){
            cout<<check[i][j]<<" ";
        }
        cout<< endl;
    }
*/
   /* Session sess(argv[1]);
    sess.simulate();
    return 0;*/
}
