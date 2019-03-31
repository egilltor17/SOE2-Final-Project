#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
<<<<<<< HEAD
#include<stdlib.h>

using namespace std;
int main(int argc, char* argv[])
{
    cout << argc << endl;
//    cout << argv[0] << endl;
//    cout << argv[1] << endl;
//    cout << argv[2] << endl;
//    cout << argv[3] << endl;

    string fileDir = (argc > 1) ? (string)argv[1] : "./dump.txt";
    int confidence = (argc == 4) ? atoi(argv[2]) : 65; // Default confidence is 65     - the range [confidence, 1] determines whether or not the bug get reported.
    int support =    (argc == 4) ? atoi(argv[3]) : 3;  // Default support         - the minimum occurrence of a function pair to be considered as a "bug".
    int index = 0;
    cout << "Confidence: " << confidence << endl;
    cout << "Support: " << support << endl;
    cout << "Number of args: " << argc << endl;                            // Index of char in string - used to isolate function names form the callGraph data.
=======
#include <stdlib.h>
using namespace std;
int main(int argc, char* argv[])
{
    string fileDir = (argc > 1) ? (string)argv[1] : "./dump.txt";
    int confidence = (argc == 4) ? atoi(argv[2]) : 65; // Default confidence is 65     - the range [confidence, 1] determines whether or not the bug get reported.
    int support =    (argc == 4) ? atoi(argv[3]) : 3;  // Default support         - the minimum occurrence of a function pair to be considered as a "bug".
    int index = 0;                                    // Index of char in string - used to isolate function names form the callGraph data.
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
    ifstream myfile(fileDir);
    string scope = "";
    string call = "";
    set<string> allFuncs;
<<<<<<< HEAD
    set<string> calledInScope;
    unordered_map< string, set<string> > funCalls;
    set<string> scopeAndCount;
=======
    set<string> callScopes;
    set<string> calledInScope;
    unordered_map< string, pair< set<string>, int > > funCalls;
    pair< set<string>, int > scopeAndCount = {callScopes, 1};
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
    set<string>::iterator it;
    set<string>::iterator it2;
    set<string>::iterator it3;
    set<string>::iterator itTmp;
<<<<<<< HEAD
    cout << fileDir << endl;
=======
    cout << fileDir;
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
    if(myfile.is_open()) {

        getline(myfile,scope);          // Eats the "Root of the callGraph"
        while(getline(myfile,scope)) {  // Outer loop runs through the scopes

        //cout << fileDir << endl;
            index = scope.find('\'') + 1;
            if(index) {
                scope = scope.substr(index, scope.find('\'', index) - index);
            } else {
                // scope is null function and we skip it
                while(getline(myfile,call) && call != "") {}
            }
            while(getline(myfile,call)) {   // Inner loop runs though scope's elements
<<<<<<< HEAD
               // cout << fileDir;
=======
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
                if(call == "") {            // call is empty string --> scope has ended
                    for(it = calledInScope.begin(); it != calledInScope.end(); it++){
                        itTmp = it;
                        for(it2 = ++itTmp; it2 != calledInScope.end(); it2++){
                            string fun = *it + *it2;
                            if(funCalls.count(fun)){
<<<<<<< HEAD
                                funCalls[fun].insert(scope);
                            } else {
                                scopeAndCount.clear();
                                scopeAndCount.insert(scope);
                                funCalls[fun] = scopeAndCount;
=======
                                funCalls[fun].first.insert(scope);
                                funCalls[fun].second++;
                            } else {
                                scopeAndCount.first.clear();
                                scopeAndCount.first.insert(scope);
                                funCalls.insert({fun, scopeAndCount});
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
                            }
                        }
                    }
                    calledInScope.clear();
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    index = call.find('\'') + 1;
                    call = call.substr(index, call.find('\'', index) - index);
                    if(funCalls.count(call)){
<<<<<<< HEAD
                        funCalls[call].insert(scope);
                    } else {
                        scopeAndCount.clear();
                        scopeAndCount.insert(scope);
                        funCalls[call] = scopeAndCount;
=======
                        funCalls[call].first.insert(scope);
                        funCalls[call].second++;
                    } else {
                        scopeAndCount.first.clear();
                        scopeAndCount.first.insert(scope);
                        funCalls.insert({call, scopeAndCount});
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
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
<<<<<<< HEAD
            if(support <= funCalls[combo].size()) {
                double confit1 = ((double)(int)((10000*((double)funCalls[combo].size())/funCalls[*it ].size()) + 0.5) / 100);
                double confit2 = ((double)(int)((10000*((double)funCalls[combo].size())/funCalls[*it2].size()) + 0.5) / 100);
                if(confit1 > confidence && confit1 < 100) {
                    for(it3 = funCalls[*it ].begin(); it3 != funCalls[*it ].end(); it3++) {
                        if(!funCalls[combo].count(*it3)) {
                            cout << "bug: " << *it  << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].size() << ", confidence: " << confit1 << "%\n";
=======
            if(support <= funCalls[combo].second) {
                double confit1 = ((double)(int)((10000*((double)funCalls[combo].second)/funCalls[*it ].second) + 0.5) / 100);
                double confit2 = ((double)(int)((10000*((double)funCalls[combo].second)/funCalls[*it2].second) + 0.5) / 100);
                if(confit1 > confidence && confit1 < 100) {
                    for(it3 = funCalls[*it ].first.begin(); it3 != funCalls[*it ].first.end(); it3++) {
                        if(!funCalls[combo].first.count(*it3)) {
                            cout << "bug: " << *it  << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].second << ", confidence: " << confit1 << "%\n";
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
                        }
                    }
                }
                if(confit2 > confidence && confit2 < 100) {
<<<<<<< HEAD
                    for(it3 = funCalls[*it2].begin(); it3 != funCalls[*it2].end(); it3++) {
                        if(!funCalls[combo].count(*it3)) {
                            cout << "bug: " << *it2 << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].size() << ", confidence: " << confit2 << "%\n";
=======
                    for(it3 = funCalls[*it2].first.begin(); it3 != funCalls[*it2].first.end(); it3++) {
                        if(!funCalls[combo].first.count(*it3)) {
                            cout << "bug: " << *it2 << " in " << *it3 << ", pair: (" << *it << ", " << *it2 << "), support: " << funCalls[combo].second << ", confidence: " << confit2 << "%\n";
>>>>>>> 51f7eefbd10cee47e2ac97f475439c9d3939cfe7
                        }
                    }
                }
            }
        }
    }
    return 0;
}
