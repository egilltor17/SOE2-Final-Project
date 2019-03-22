#include <iostream>
#include <fstream>
#include <string>
//#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
//    int scopeCalls = 0;
    string scope = "";
    string call = "";
    unordered_map< string, vector<string> > scopeMap;
    vector<string> callVector;
    ifstream myfile ("C:\\Users\\Egill\\Documents\\HR\\Önn 4\\Hugbúnaðarfræði II\\Assingments\\Project\\dump.txt");
    if (myfile.is_open()) {
        while(getline(myfile,scope)) {
//            scopeCalls = atoi(scope.substr(scope.find('=', 31), scope.size() - 1));
//            scopeCalls = atoi("12");
            scope = scope.substr(31, scope.find('\'', 31) - 31);
//            cout << scope << "\n";

            while(getline(myfile,call)) {
                if(call == "") {
                    scopeMap.insert({scope, callVector});
                    callVector.clear();
//                    cout << '\n';
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    callVector.push_back(call.substr(32, call.find('\'', 32) - 32));
//                    cout << '\t' << call.substr(32, call.find('\'', 32) - 32) << "\n";
                }
            }
        }
        myfile.close();
    } else {
        cout << "Unable to open file\n";
    }

    for(auto& p: scopeMap) {
        cout << p.first << '\n';
        for(string& q: p.second) {
            cout << '\t' << q << '\n';
        }
    }

    return 0;
}
