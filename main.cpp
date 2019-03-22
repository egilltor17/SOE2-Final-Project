#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;
int main()
{
    int index = 0;
    string scope = "";
    string call = "";
    unordered_map< string, set<string> > scopeMap;
    unordered_map< string ,int> funcalls;
    set<string> callVector;
    set<string> allFuncs;
    ifstream myfile("./dump.txt");
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
                    //scopeMap.insert({scope, callVector});
	            set<string>::iterator it;
		    set<string>::iterator it2;
		    for(it = callVector.begin(); it != callVector.end(); ++it){
			set<string>::iterator itTmp = it;
		    	for(it2 = ++itTmp; it2 != callVector.end(); it2++){
		            string fun = *it + *it2;
			    if(funcalls.count(fun)){funcalls[fun]++;}
                    	    else{funcalls.insert({fun,1});}
               		}
		    }
		    callVector.clear();
                    break;
                } else if(call[call.size() - 1] == '\'') {
                    index = call.find('\'') + 1;
                    string fun = call.substr(index, call.find('\'', index) - index);
		    if(funcalls.count(fun)){funcalls[fun]++;}
		    else{funcalls.insert({fun,1});}
                    callVector.insert(fun);
		    allFuncs.insert(fun);
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
		double confit1 = ((double)funcalls[combo])/funcalls[*it];
		double confit2 = ((double)funcalls[combo])/funcalls[*it2];
		if(confit1 > 0.65 && confit1 != 1){cout << combo << "is under threshold: " << confit1 << endl;}
		if(confit2 > 0.65 && confit2 != 1){cout << combo << "is under threshold: " << confit2 << endl;}
	}
    }
    return 0;
}
