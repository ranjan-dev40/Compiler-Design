#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> dfa = {{3,1}, {2,0}, {1,3}, {0,2}};

int start_state =0;
int final_state =0;

bool isAccepted(string s){

    int i = 0;
    int current_state = start_state;

    while(i< s.size()){

        if(s[i] == '0') current_state = dfa[current_state] [0];

        else  current_state = dfa[current_state] [1];

        i++;


    }

    if(current_state == final_state) return true;
    else return false;


}

int main(){
    string s;
    cout<<"Enter the string over alphabet (0, 1) : "<<endl;
    cin>> s;

    if(isAccepted(s)) cout<<"string is accepted by dfa"<<endl;
    else cout<<"string is not  accepted by dfa"<<endl;




    return 0;
}