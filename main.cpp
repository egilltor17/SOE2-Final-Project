#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;
int main(int argc, char** argv)
{
    int confidence = 65;                // Default confidence      - the range [confidence, 1] determines whether or not the bug get reported.
    int support = 0;                    // Default support         - the minimum occurrence of a function pair to be considered as a "bug".
    int index = 0;                      // Index of char in string - used to isolate function names form the callGraph data.
    string scope = "";
    string call = "";
    set<string> allFuncs;
    set<string> callScopes;
    set<string> calledInScope;
    unordered_map< string, pair< set<string>, int > > funCalls;
    pair< set<string>, int > scopeAndCount = {callScopes, 1};
    ifstream myfile("./dump.txt");
//    ifstream myfile("C:\\Users\\Egill\\Desktop\\bla\\bla.txt");
//    ifstream myfile("C:\\Users\\Egill\\Desktop\\bla\\callGraph.txt");
    set<string>::iterator it;
    set<string>::iterator it2;
    set<string>::iterator it3;
    set<string>::iterator itTmp;

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
                if(call == "") {            // call is empty string --> scope has ended
                    for(it = calledInScope.begin(); it != calledInScope.end(); it++){
                        itTmp = it;
                        for(it2 = ++itTmp; it2 != calledInScope.end(); it2++){
                            string fun = *it + *it2;
                            if(funCalls.count(fun)){
                                funCalls[fun].first.insert(scope);
                                funCalls[fun].second++;
                            } else {
                                scopeAndCount.first.clear();
                                scopeAndCount.first.insert(scope);
                                funCalls.insert({fun, scopeAndCount});
                            }
                        }
                    }
                    calledInScope.clear();
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    index = call.find('\'') + 1;
                    call = call.substr(index, call.find('\'', index) - index);
                    if(funCalls.count(call)){
                        funCalls[call].first.insert(scope);
                        funCalls[call].second++;
                    } else {
                        scopeAndCount.first.clear();
                        scopeAndCount.first.insert(scope);
                        funCalls.insert({call, scopeAndCount});
                    }
                    allFuncs.insert(call);
                    calledInScope.insert(call);
                }
            }
        }
        myfile.close();
    } else {
        cout << "Unable to open file\n";
    }

    for(it = allFuncs.begin(); it != allFuncs.end(); it++){
        itTmp = it;
        for(it2 = ++itTmp; it2 != allFuncs.end(); it2++){
            string combo = *it + *it2;
            if(support <= funCalls[combo].second) {
                double confit1 = ((double)(int)((10000*((double)funCalls[combo].second)/funCalls[*it ].second) + 0.5) / 100);
                double confit2 = ((double)(int)((10000*((double)funCalls[combo].second)/funCalls[*it2].second) + 0.5) / 100);
                if(confit1 > confidence && confit1 < 100) {
                    for(it3 = funCalls[*it ].first.begin(); it3 != funCalls[*it ].first.end(); it3++) {
                        if(!funCalls[combo].first.count(*it3)) {
                            cout << "bug: " << *it  << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].second << ", confidence: " << confit1 << "%\n";
                        }
                    }
                }
                if(confit2 > confidence && confit2 < 100) {
                    for(it3 = funCalls[*it2].first.begin(); it3 != funCalls[*it2].first.end(); it3++) {
                        if(!funCalls[combo].first.count(*it3)) {
                            cout << "bug: " << *it2 << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].second << ", confidence: " << confit2 << "%\n";
                        }
                    }
                }
            }
        }
    }
    return 0;
}
