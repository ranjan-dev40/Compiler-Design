#include <bits/stdc++.h>
using namespace std;

set<int> start_state;
set<set<int>> final_states;
set<set<int>> all_states;

void printSetNFA(set<int> s)
{
    cout << "{";
    for (auto val : s)
    {
        cout << "q" << val;
        if (!(val == *(--(s.end()))))
            cout << ",";
    }
    cout << "}";
}

void printNFA(vector<vector<set<int>>> &nfa)
{
    cout << "The nfa is : " << endl;
    for (int i = 0; i < nfa[0].size(); i++)
    {
        cout << "\t\t" << i;
    }
    cout << "\n";
    cout << "States" << endl;
    for (int i = 0; i < nfa.size(); i++)
    {

        cout << "q" << i << "\t\t";
        for (int j = 0; j < nfa[0].size(); j++)
        {
            printSetNFA(nfa[i][j]);
            cout << "\t\t";
        }
        cout << endl;
    }
}

vector<vector<set<int>>> nfaToDfa(vector<set<int>> &dfa_states, vector<vector<set<int>>> &nfa)
{

    vector<vector<set<int>>> dfa;
    set<int> current_state = start_state;
    set<set<int>> dfa_states_check;
    dfa_states_check.insert(current_state);
    stack<set<int>> st;
    st.push(current_state);
    while (!empty(st))
    {
        current_state = st.top();
        st.pop();
        dfa_states.push_back(current_state);
        vector<set<int>> v;
        for (int i = 0; i < nfa[0].size(); i++)
        {
            set<int> new_state;
            for (auto val : current_state)
            {
                for (auto stat : nfa[val][i])
                {
                    new_state.insert(stat);
                }
            }

            v.push_back(new_state);
            if (dfa_states_check.find(new_state) == dfa_states_check.end())
            {
                st.push(new_state);
                dfa_states_check.insert(new_state);
            }
        }
        dfa.push_back(v);
    }
    return dfa;
}

void inputNFA(vector<vector<set<int>>> &nfa)
{
    int numOfStates;
    int numOfInputSymbols;
    cout << "Enter the number of States : ";
    cin >> numOfStates;
    cout << "Enter number of input symbols : ";
    cin >> numOfInputSymbols;
    cout << "Enter the transition table : ";
    int i = 0;
    while (i < numOfStates)
    {
        vector<set<int>> transition;
        for (int j = 0; j < numOfInputSymbols; j++)
        {
            int x;
            cout << "\nEnter number of transitions for (q" << i << ", " << j << ") : ";
            cin >> x;
            set<int> transitionsOnSymbol;
            while (x--)
            {
                int y;
                cin >> y;
                transitionsOnSymbol.insert(y);
            }
            transition.push_back(transitionsOnSymbol);
        }
        nfa.push_back(transition);
        i++;
    }
    cout << "Enter the initial state : " << endl;
    int x;
    cin >> x;
    start_state.insert({x});
    cout << "How many final states ? : ";
    int numFinalStates;
    cin >> numFinalStates;
    cout << "Enter the final states : " << endl;
    while (numFinalStates--)
    {
        int x;
        cin >> x;
        final_states.insert({x});
    }

    for (int i = 0; i < nfa.size(); i++)
    {
        all_states.insert({i});
    }
}

void print_stateDFA(set<int> s)
{
    int count = 0;
    cout << "[";
    for (auto state : s)
    {
        count++;
        cout << "q" << state;
        if (!(state == *(--(s.end()))))
            cout << ",";
    }
    cout << "]";
    if (count < 3)
    {
        cout << "\t";
    }
    cout << "\t";
}

void print_transitions(vector<set<int>> transition)
{
    for (auto val : transition)
    {
        print_stateDFA(val);
    }
}

void printDFA(vector<vector<set<int>>> dfa, vector<set<int>> dfa_states)
{
    for (int i = 0; i < dfa[0].size(); i++)
    {
        cout << "\t\t" << i;
    }
    cout << endl;
    cout << "States" << endl;
    for (int i = 0; i < dfa.size(); i++)
    {
        print_stateDFA(dfa_states[i]);
        print_transitions(dfa[i]);
        cout << endl;
    }
}

void printStatesOfDFA(vector<set<int>> dfa_states)
{
    cout << "{";
    for (auto val : dfa_states)
    {
        cout << "[";
        for (auto state : val)
        {
            cout << "q" << state;
            if (!(state == *(--(val.end()))))
                cout << ",";
        }
        cout << "]";

        if (!(val == *(--(dfa_states.end()))))
            cout << ", ";
    }
    cout << "}";
    cout << endl;
}

int main()
{
    vector<set<int>> dfa_states;
    vector<vector<set<int>>> nfa;
    inputNFA(nfa);
    printNFA(nfa);
    vector<vector<set<int>>> dfa = nfaToDfa(dfa_states, nfa);
    cout << "\nThere are " << dfa_states.size() << " states in the DFA : ";
    printStatesOfDFA(dfa_states);
    cout << "\nCorresponding dfa is : " << endl;
    cout << "\n\n";
    printDFA(dfa, dfa_states);
    return 0;
}