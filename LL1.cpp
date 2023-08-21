#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

vector<pair<char, string>> prod;
set<char> non_terminals, terminals;
map<char, set<char>> first, follow;

bool isNonTerminal(char c)
{
    return c >= 'A' && c <= 'Z';
}

void findFirst(char non_terminal)
{
    for (auto &x : prod)
    {
        if (x.first != non_terminal)
            continue;
        int len = x.second.length();
        auto &y = x.second;
        for (int i = 0; i < len; i++)
        {
            if (!isNonTerminal(y[i]))
            {
                first[non_terminal].insert(y[i]);
                break;
            }
            else
            {
                if (first[y[i]].empty())
                {
                    findFirst(y[i]);
                }

                if (!first[y[i]].count('e'))
                {
                    first[non_terminal].insert(first[y[i]].begin(), first[y[i]].end());
                    break;
                }

                set<char> temp = first[y[i]];

                if (i != len - 1)
                {
                    temp.erase('e');
                }
                first[non_terminal].insert(temp.begin(), temp.end());
            }
        }
    }
}

void findFollow(char non_terminal)
{
    for (auto &x : prod)
    {
        bool finished = true;
        int len = x.second.length(), i = 0;
        auto &y = x.second;
        while (i < len)
        {
            if (y[i] == non_terminal)
            {
                finished = false;
                break;
            }
            i++;
        }
        i++;
        while (i < len)
        {
            if (!isNonTerminal(y[i]))
            {
                follow[non_terminal].insert(y[i]);
                finished = true;
                break;
            }

            set<char> temp = first[y[i]];

            if (!temp.count('e'))
            {
                follow[non_terminal].insert(temp.begin(), temp.end());
                finished = true;
                break;
            }

            temp.erase('e');
            follow[non_terminal].insert(temp.begin(), temp.end());

            i++;
        }

        if (i == len && !finished)
        {
            if (follow[x.first].empty())
            {
                findFollow(x.first);
            }
            follow[non_terminal].insert(follow[x.first].begin(), follow[x.first].end());
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        string s;
        cin >> s;
        prod.push_back({c, s});
        non_terminals.insert(c);
        for (auto &x : s)
            if (!isNonTerminal(x))
                terminals.insert(x);
    }

    cout << "Productions: " << nl;

    for (auto &x : prod)
    {
        cout << x.first << " -> " << x.second << nl;
    }

    cout << nl;

    cout << "Non Terminals: ";
    for (auto &x : non_terminals)
    {
        cout << x << " ";
    }
    cout << nl;

    terminals.insert('$');
    terminals.erase('e');

    cout << "Terminals: ";
    for (auto &x : terminals)
    {
        cout << x << " ";
    }
    cout << nl;

    char start_symbol = prod[0].first;
    for (auto &x : non_terminals)
    {
        if (first[x].empty())
        {
            findFirst(x);
        }
    }

    cout << "First: " << nl;
    for (auto &x : non_terminals)
    {
        cout << x << " -> ";
        for (auto &y : first[x])
        {
            cout << y << " ";
        }
        cout << nl;
    }

    cout << nl;

    follow[start_symbol].insert('$');
    findFollow(start_symbol);
    for (auto &x : non_terminals)
    {
        if (follow[x].empty())
        {
            findFollow(x);
        }
    }

    cout << "Follow: " << nl;
    for (auto &x : non_terminals)
    {
        cout << x << " -> ";
        for (auto &y : follow[x])
        {
            cout << y << " ";
        }
        cout << nl;
    }
    cout << nl;

    map<char, map<char, int>> table;

    for (int i = 0; i < n; i++)
    {
        auto &y = prod[i].second;
        set<char> next_list;
        bool finished = false;
        int len = y.length();
        for (int i = 0; i < len; i++)
        {
            if (!isNonTerminal(y[i]))
            {
                if (y[i] != 'e')
                {
                    next_list.insert(y[i]);
                    finished = true;
                    break;
                }
                continue;
            }

            set<char> temp = first[y[i]];
            if (!temp.count('e'))
            {
                next_list.insert(temp.begin(), temp.end());
                finished = true;
                break;
            }

            temp.erase('e');
            next_list.insert(temp.begin(), temp.end());
        }

        if (!finished)
        {
            next_list.insert(follow[prod[i].first].begin(), follow[prod[i].first].end());
        }

        for (auto &z : terminals)
        {
            if (!table[prod[i].first].count(z))
                table[prod[i].first][z] = -1;
            if (next_list.count(z))
            {
                if (table[prod[i].first][z] != -1)
                {
                    cout << "Error: Ambiguous Grammar" << nl;
                    return 0;
                }
                table[prod[i].first][z] = i;
            }
        }
    }

    cout << "Parsing Table: " << nl;

    cout << "  ";
    for (auto &x : terminals)
    {
        cout << x << " ";
    }
    cout << nl;
    for (auto &x : non_terminals)
    {
        cout << x << " ";
        for (auto &y : terminals)
        {
            if (table[x][y] == -1)
                cout << "- ";
            else
                cout << table[x][y] + 1 << " ";
        }
        cout << nl;
    }

    cout << nl;

    string input;
    cin >> input;
    input.push_back('$');
    stack<char> st;
    st.push('$');
    st.push(start_symbol);

    for (auto &x : input)
    {
        if (!terminals.count(x))
        {
            cout << "Error: Invalid Input" << nl;
            return 0;
        }
    }

    bool accepted = true;
    reverse(input.begin(), input.end());

    while (!st.empty() && !input.empty())
    {
        if (input.back() == st.top())
        {
            st.pop();
            input.pop_back();
        }
        else if (!isNonTerminal(st.top()))
        {
            cout << "Error: Unmatched Terminal" << nl;
            accepted = false;
            break;
        }
        else
        {
            char top = st.top();
            st.pop();
            int prod_num = table[top][input.back()];
            if (prod_num == -1)
            {
                cout << "Error: No production found in parse table" << nl;
                accepted = false;
                break;
            }

            auto &y = prod[prod_num].second;
            if (y[0] == 'e')
                continue;
            for (int i = y.length() - 1; i >= 0; i--)
                st.push(y[i]);
        }
    }

    if (accepted)
    {
        cout << "Accepted" << nl;
    }
    else
    {
        cout << "Rejected" << nl;
    }
}