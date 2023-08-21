// Minimization of a DFA
// Here input symbols are assumed to be numbered from 0 to n-1 , where n is the number of input symbols
// Here states are assumed to be numbered as q'i' , where i ranges from 0 to m-1, where m is the number of states
#include <bits/stdc++.h>
using namespace std;
set<int> start_state;
set<int> final_states;
vector<vector<int>> dfa;
set<int> all_states;

void printSet(set<int> s)
{
    cout << "[";
    int count = 0;
    for (auto val : s)
    {
        count++;
        cout << "q" << val;
        if (!(val == *(--(s.end()))))
            cout << ",";
    }
    cout << "]";
    if (count < 3)
    {
        cout << "\t";
    }
    cout << "\t";
}

void printMinimizedDFA(vector<set<int>> min_dfa_vector)
{
    cout << "\n\nThe transition table of minimized DFA is : \n"
         << endl;
    for (int i = 0; i < dfa[0].size(); i++)
    {
        cout << "\t\t" << i;
    }
    cout << endl;
    cout << "States" << endl;
    for (auto val : min_dfa_vector)
    {
        printSet(val);
        for (int i = 0; i < dfa[0].size(); i++)
        {
            int num = dfa[*(val.begin())][i];
            for (auto inside_set : min_dfa_vector)
            {
                if (inside_set.find(num) != inside_set.end())
                {
                    printSet(inside_set);
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

set<int> setDiff(set<int> s1, set<int> s2)
{
    set<int> diff;
    for (auto val1 : s1)
    {
        if (s2.find(val1) == s2.end())
        {
            diff.insert(val1);
        }
    }
    return diff;
}

bool equal_vec(vector<set<set<int>>::iterator> v1, vector<set<set<int>>::iterator> v2)
{
    for (int i = 0; i < v1.size(); i++)
    {
        auto it1 = v1[i]->begin();
        auto it2 = v2[i]->begin();
        while (it1 != v1[i]->end() || it2 != v2[i]->end())
        {
            if (*it1 != *it2)
            {
                return false;
            }
            it1++;
            it2++;
        }
    }
    return true;
}

set<set<int>> break_set(set<int> s, set<set<int>> parent_set)
{
    set<set<int>> broken_sets;
    vector<pair<int, vector<set<set<int>>::iterator>>> val_set_info;
    for (auto val : s)
    {
        int i = 0;
        vector<set<set<int>>::iterator> val_set;
        pair<int, vector<set<set<int>>::iterator>> p;
        p.first = val;
        while (i < dfa[0].size())
        {
            for (auto it = parent_set.begin(); it != parent_set.end(); it++)
            {
                if (!(it->find(dfa[val][i]) == it->end()))
                {
                    val_set.push_back(it);
                    break;
                }
            }
            i++;
        }
        p.second = val_set;
        val_set_info.push_back(p);
    }

    for (int i = 0; i < val_set_info.size(); i++)
    {
        set<int> s1;
        if (val_set_info[i].first != -1)
        {
            s1.insert(val_set_info[i].first);
        }
        for (int j = i + 1; j < val_set_info.size() && val_set_info[i].first != -1; j++)
        {
            if (equal_vec(val_set_info[i].second, val_set_info[j].second))
            {
                s1.insert(val_set_info[j].first);
                val_set_info[j].first = -1;
            }
        }
        if (s1.size() > 0)
            broken_sets.insert(s1);
    }
    return broken_sets;
}

set<set<int>> minimizedDFA()
{
    set<set<int>> parent_sets;
    parent_sets.insert(final_states);
    parent_sets.insert(setDiff(all_states, final_states));

    set<set<int>> new_sets;
    while (true)
    {
        for (auto it = parent_sets.begin(); it != parent_sets.end(); it++)
        {
            set<set<int>> brokenSets = break_set(*it, parent_sets);
            for (auto val : brokenSets)
            {
                new_sets.insert(val);
            }
        }
        if (new_sets.size() == parent_sets.size())
        {
            return new_sets;
        }
        else
        {
            parent_sets = new_sets;
            new_sets.clear();
        }
    }
}

void inputDFA()
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
        vector<int> transition;
        for (int j = 0; j < numOfInputSymbols; j++)
        {
            int x;
            cin >> x;
            transition.push_back(x);
        }
        dfa.push_back(transition);
        i++;
    }
    cout << "Enter the initial state : " << endl;
    int x;
    cin >> x;
    start_state.insert(x);
    cout << "How many final states ? : ";
    int numFinalStates;
    cin >> numFinalStates;
    cout << "Enter the final states : " << endl;
    while (numFinalStates--)
    {
        int x;
        cin >> x;
        final_states.insert(x);
    }

    for (int i = 0; i < dfa.size(); i++)
    {
        all_states.insert(i);
    }
}

int main()
{
    inputDFA();
    set<set<int>> mini_DFA = minimizedDFA();
    vector<set<int>> min_dfa_vector;
    for (auto val : mini_DFA)
    {
        min_dfa_vector.push_back(val);
    }
    cout << "\nThere are " << mini_DFA.size() << " states in the minimized DFA : ";
    cout << "{ ";
    for (auto val : mini_DFA)
    {
        cout << "[";
        int count = 0;
        for (auto g : val)
        {
            count++;
            cout << "q" << g;
            if (!(g == *(--(val.end()))))
                cout << ",";
        }
        cout << "]";
        if (!(val == *(--(mini_DFA.end()))))
            cout << ", ";
    }
    cout << " }";

    printMinimizedDFA(min_dfa_vector);
    return 0;
}