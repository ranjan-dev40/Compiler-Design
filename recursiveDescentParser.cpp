#include<bits\stdc++.h>
using namespace std;
#define vs vector<string>
bool T(int &,vector<string>);
bool T1(int &,vector<string>);
bool T2(int &,vector<string>);
bool T3(int &,vector<string>);
bool E(int &,vector<string>);
bool E1(int &,vector<string>);
bool E2(int &,vector<string>);
class Grammer{
    private:
    vector<string>nonTerminal;
    vector<string>terminals;
    string startSymbol="E";
    public:
    Grammer()
{
nonTerminal={"E","T"};
terminals={"int","*","(",")","+"};
}
vs getTerminal(){
    return terminals;
}
vs getNonTerminal(){
    return nonTerminal;
}
};
bool checkTer(string tmp,vector<string>terminals){
for(auto i:terminals){
    if(i==tmp) return true;
}
return false;
}
bool stringToArray(vs&result, string inputString,vs terminals){
    string tmp;
    int i=0;
    while(i<inputString.length()){
        while(i!=inputString.length() && inputString[i]!=' '){
            tmp+=inputString[i];
            i++;
        }
         if(checkTer(tmp,terminals)){
            result.push_back(tmp);
            tmp="";
         }
         else return false;i++;
    }
    return true;
}
bool match(string tk,int&ind,vs tokens){
    int tkSize=tk.length();
    if(tokens[ind++]==tk) return true;
    return false;
}
bool E(int &ind,vs tokens){
    int tmp=ind;
    bool e1Flag=E1(ind,tokens);
    if(e1Flag) return true;
    if(e1Flag==false){
        ind=tmp;
    }
    return E2(ind,tokens);
}
bool E1(int &ind, vs tokens){
    return T(ind,tokens);
}
bool E2(int &ind, vs tokens){
    return T(ind,tokens) && match("+",ind,tokens) &&E(ind,tokens);
}
bool T(int &ind,vs tokens){
    int tmp=ind;
    bool t1Flag=T1(ind,tokens);
    if(t1Flag) return true;
    else ind=tmp;
    bool t2Flag=T2(ind,tokens);
    if(t2Flag) return true;
    else ind=tmp;
    return T3(ind,tokens);
}
bool T1(int &ind,vs tokens){
    return match("int",ind,tokens);
}
bool T2(int &ind,vs tokens){
    return match("int",ind,tokens) && match("*",ind,tokens) && T(ind,tokens);
}
bool T3(int &ind,vs tokens){
    return match("(",ind,tokens) && E(ind,tokens) && match(")",ind,tokens);
}
int main(){
    Grammer g;
    string inputString;
    vs tokens;
    cout<<"eneter string to be checked = ";
    getline(cin,inputString);
    bool isAllTer=stringToArray(tokens,inputString,g.getTerminal());
    if(!isAllTer){
        cout<<"Language is not accepted";
        exit(0);
    }
    int ind=0;
    E(ind,tokens)?cout<<"Language is Accepted":cout<<"Language is not Accepted";
    return 0;
}