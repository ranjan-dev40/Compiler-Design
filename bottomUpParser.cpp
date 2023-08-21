#include<bits/stdc++.h>
using namespace std;

class  Grammer{
    private:
    vector<string> terminals;
    vector<string> nonTerminals;
    unordered_map<string, vector<string>> grammar;
    vector<vector<string>> precedenceTable;
    public:
    Grammer(){
        grammar["E"].push_back("E+E");
        grammar["E"].push_back("E*E");
        grammar["E"].push_back("i");

        terminals = {"i","+","*","$"};
        nonTerminals = {"E"};
        precedenceTable.push_back({"=",">",">",">"});
        precedenceTable.push_back({"<",">","<",">"});
        precedenceTable.push_back({"<",">",">",">"});
        precedenceTable.push_back({"<","<","<","="});
    }

    unordered_map<string, vector<string>> getGrammer(){
        return grammar;
    }

    vector<string>getTerms(){
        return terminals;
    }
    vector<string>getNonTerms(){
        return nonTerminals;
    }
    vector<vector<string>>getTable(){
        return precedenceTable;
    }
};

bool checkTerm(vector<string>terminals, string x){
    for(auto i:terminals){
        if(i==x){
            return true;
        }
    }
        return false;
}

bool getExpTerms(string exp, vector<string>terminals, vector<string> &expTerm){
    for(auto i: exp){
        string  x(1,i);
        if(checkTerm(terminals, x)) expTerm.push_back(x);
        else return false;
    }

    return true;
}

bool parseString(vector<string> expTerm, vector<string>terminals, vector<vector<string>> table, stack<string> parsingStack){
    int expPointer =0;
    while(true){
        int colInd = find(terminals.begin(),terminals.end(), expTerm[expPointer]) - terminals.begin();
        int rowInd = find(terminals.begin(),terminals.end(), parsingStack.top()) - terminals.begin();
        string precedence = table[rowInd][colInd];
        if(table[rowInd][colInd] =="<" || table[rowInd][colInd] =="="  ){
            cout<<"IF-";
            cout<<rowInd<<" "<<colInd<<" "<< precedence<<endl;
            parsingStack.push(expTerm[expPointer++]);

            if(expPointer >= expTerm.size()) return false;
        }
            else{
                do{
                    cout<<"Else -"<<endl;
                    cout<<"Top -"<<parsingStack.top()<<endl;
                    parsingStack.pop();

                    colInd = find(terminals.begin(),terminals.end(), expTerm[expPointer]) - terminals.begin();
                    rowInd = find(terminals.begin(),terminals.end(), parsingStack.top()) - terminals.begin();
                    precedence = table[rowInd][colInd];

                    cout<<rowInd<<" "<<colInd<<" "<<precedence<<endl;

                }while(precedence==">");

        }

                if(parsingStack.top()=="$" && expTerm[expPointer] == "$") return true;
    }

  
}

int main(){
    Grammer g;
    vector<string> terminals = g.getTerms();
    vector<string> nonTerminals = g.getNonTerms();
    unordered_map<string, vector<string>> grm = g.getGrammer();
    vector<vector<string>> table = g.getTable();

    string exp;
    vector<string> expTerm;
    cout<<"Grammar-"<<endl;

    for(auto prd:grm){
        cout<<prd.first<<"->";
        for(auto i:prd.second){
            cout<<i<<"/";
        }
        cout<<endl;
    }

    cout<<endl<<endl;

    cout<<"Operator Precedence Table- "<<endl;
    for(string i: terminals){
        cout<<"\t"<<i;
    }

    for(int i=0; i<table.size(); i++){
        cout<<endl<<terminals[i]<<"\t";
        for(string j:table[i]){
            cout<<(j == "="?" " : j)<<"\t";
        }
        cout<<endl;
    }

    cout<<endl;


    cout<<"Enter String to be parsed - ";
    cin>>exp;

    exp +="$";

    bool canParse = getExpTerms(exp, terminals, expTerm);

    if(!canParse){
        cout<<"String Cannot be parsed"<<endl;
        exit(0);
    }

    stack<string> parsingStack;
    parsingStack.push("$");

    bool isParsed = parseString(expTerm, terminals, table, parsingStack);

    if(isParsed){
        cout<<"String Parsed Successfully"<<endl;
    }
    else{
        cout<<"String is not parsed";
    }






    return 0;
}