#include <iostream>
#include <fstream>
#include <string>
//#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
    int index = 0;
    string scope = "";
    string call = "";
    unordered_map< string, vector<string> > scopeMap;
    vector<string> callVector;

    ifstream myfile("./callGraph.out");
//    ifstream myfile("C:\\Users\\Egill\\Desktop\\bla\\callGraph.txt");

    if(myfile.is_open()) {
        getline(myfile,scope);          // Eats the "Root of the callGraph"
        while(getline(myfile,scope)) {  // Outer loop runs through the scopes
            index = scope.find('\'') + 1;
            if(index) {
                scope = scope.substr(index, scope.find('\'', index) - index);
            } else {
                scope = "unknown_name";
            }
            while(getline(myfile,call)) {   // Inner loop runs though scope's elements
                if(call == "") {
                    scopeMap.insert({scope, callVector});
                    callVector.clear();
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    index = call.find('\'') + 1;
                    callVector.push_back(call.substr(index, call.find('\'', index) - index));
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
