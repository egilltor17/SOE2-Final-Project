#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    int confidence = 65;
    int support = 0;
    int index = 0;
    string scope = "";
    string call = "";
    unordered_map< string, set<string> > scopeMap;
    unordered_map< string, int> funcalls;
    set<string> callSet;
    set<string> allFuncs;
    ifstream myfile("./dump.txt");
//    ifstream myfile("C:\\Users\\Egill\\Desktop\\bla\\bla.txt");

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
                    set<string>::iterator it;
                    set<string>::iterator it2;
                    for(it = callSet.begin(); it != callSet.end(); ++it){
                        set<string>::iterator itTmp = it;
                        for(it2 = ++itTmp; it2 != callSet.end(); it2++){
                            string fun = *it + *it2;
                            if(funcalls.count(fun)){
                                funcalls[fun]++;
                            } else {
                                funcalls.insert({fun,1});
                            }
                        }
                    }
                    callSet.clear();
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    index = call.find('\'') + 1;
                    call = call.substr(index, call.find('\'', index) - index);
                    if(funcalls.count(call)){
                        funcalls[call]++;
                    } else {
                        funcalls.insert({call,1});
                    }
                    callSet.insert(call);
                    allFuncs.insert(call);
                }
            }
        }
        myfile.close();
    } else {
        cout << "Unable to open file\n";
    }
    set<string>::iterator it;
    set<string>::iterator it2;
    for(it = allFuncs.begin(); it != allFuncs.end(); ++it){
        set<string>::iterator itTmp = it;
        for(it2 = ++itTmp; it2 != allFuncs.end(); it2++){
            string combo = *it + *it2;
            double confit1 = ((double)(int)((10000*((double)funcalls[combo])/funcalls[*it] ) + 0.5) / 100);
            double confit2 = ((double)(int)((10000*((double)funcalls[combo])/funcalls[*it2]) + 0.5) / 100);
            if(confit1 > confidence && confit1 < 100){cout << "bug: " << *it  << " in " << "TODO:scope" << ", pair: (" << *it << ", " << *it2 << "), support: " << support << ", confidence: " << confit1 << "%\n";}
            if(confit2 > confidence && confit2 < 100){cout << "bug: " << *it2 << " in " << "TODO:scope" << ", pair: (" << *it << ", " << *it2 << "), support: " << support << ", confidence: " << confit2 << "%\n";}
        }
    }
    return 0;
}
