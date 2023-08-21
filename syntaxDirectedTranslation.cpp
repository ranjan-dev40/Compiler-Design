#include <bits/stdc++.h>
using namespace std;

map<char, vector<pair<string, string>>> prod;
// SLR
vector<vector<pair<int, int>>> table;

int gotot[12][3] = {1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 2, 3, -1, -1, -1,
                    -1, 9, 3, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int a[10];
char b[10];
int top = -1, btop = -1, i;

stack<pair<char, int>> cust;
stack<int> calc;

void printStack(stack<pair<char, int>> s)
{
    cout << "Current Stack State - ";
    while (!s.empty())
    {
        pair<char, int> x = s.top();
        s.pop();
        cout << x.second << " " << x.first << " ";
    }

    cout << endl;
}

void display1(string p, int m) // Displays The Present Input String
{
    int l;
    cout << "Current Input String - ";
    for (l = m; p[l] != '\0'; l++)
    {
        cout << p[l];
    }
    cout << endl;
}

void error()
{
    printf("Syntax Error");
}

void reduce(int p, char num)
{
    int len, k, ad;
    char src, *dest;

    switch (p)
    {
    case 1:
        dest = "E+T";
        src = 'E';
        break;

    case 2:
        dest = "T";
        src = 'E';
        break;

    case 3:
        dest = "T*F";
        src = 'T';
        break;

    case 4:
        dest = "F";
        src = 'T';
        break;

    case 5:
        dest = "(E)";
        src = 'F';
        break;

    case 6:
        dest = "i";
        src = 'F';
        break;

    default:
        dest = "\0";
        src = '\0';
        break;
    }

    cout << "Reduction Step :-->" << src << "->" << dest << "-->";

    for (pair<string, string> i : prod[src])
    {
        if (i.first == dest)
        {
            cout << i.first << "->" << i.second << endl;

            if (i.first == "i")
            {
                cout << "Pushed " << num << "in stack" << endl;
                calc.push(int(num - '0'));
            }
            else if (i.first.length() > 1 && i.first[1] == '*')
            {
                int x = calc.top();
                calc.pop();
                int y = calc.top();
                calc.pop();
                calc.push(x * y);
                cout << "-----------"
                     << "Calculated Mul Value: " << x * y << "------------" << endl;
            }
            else if (i.first.length() > 1 && i.first[1] == '+')
            {
                int x = calc.top();
                calc.pop();
                int y = calc.top();
                calc.pop();
                calc.push(x + y);
                cout << "-----------"
                     << "Calculated Add Value: " << x + y << "------------" << endl;
            }

            break;
        }
    }

    cout << "------------------" << endl;

    for (k = 0; k < strlen(dest); k++)
    {
        cust.pop();
    }

    switch (src)
    {
    case 'E':
        ad = 0;
        break;

    case 'T':
        ad = 1;
        break;

    case 'F':
        ad = 2;
        break;

    default:
        ad = -1;
        break;
    }

    cust.push({src, gotot[cust.top().second][ad]});
}

main()
{
    table.push_back({{'s', 5}, {-1, -1}, {-1, -1}, {'s', 4}, {-1, -1}, {-1, -1}});
    table.push_back({{-1, -1}, {'s', 6}, {-1, -1}, {-1, -1}, {-1, -1}, {'a', 'a'}});
    table.push_back({{-1, -1}, {'r', 2}, {'s', 7}, {-1, -1}, {'r', 2}, {'r', 2}});
    table.push_back({{-1, -1}, {'r', 4}, {'r', 4}, {-1, -1}, {'r', 4}, {'r', 4}});
    table.push_back({{'s', 5}, {-1, -1}, {-1, -1}, {'s', 4}, {-1, -1}, {-1, -1}});
    table.push_back({{-1, -1}, {'r', 6}, {'r', 6}, {-1, -1}, {'r', 6}, {'r', 6}});
    table.push_back({{'s', 5}, {-1, -1}, {-1, -1}, {'s', 4}, {-1, -1}, {-1, -1}});
    table.push_back({{'s', 5}, {-1, -1}, {-1, -1}, {'s', 4}, {-1, -1}, {-1, -1}});
    table.push_back({{-1, -1}, {'s', 6}, {-1, -1}, {-1, -1}, {'s', 1}, {-1, -1}});
    table.push_back({{-1, -1}, {'r', 1}, {'s', 7}, {-1, -1}, {'r', 1}, {'r', 1}});
    table.push_back({{-1, -1}, {'r', 3}, {'r', 3}, {-1, -1}, {'r', 3}, {'r', 3}});
    table.push_back({{-1, -1}, {'r', 5}, {'r', 5}, {-1, -1}, {'r', 5}, {'r', 5}});

    prod['E'] = {{"E+T", "E.val=E.val=T.val"}, {"T", "E.val=T.val"}};
    prod['T'] = {{"T*F", "T.val=T.val*F.val"}, {"F", "T.val=F.val"}};
    prod['F'] = {{"(E)", "F.val=E.val"}, {"i", "F.val=i.lexval"}};
    int j, state, ic;
    string ip;
    char an;
    cout << "Enter any string -";
    cin >> ip;
    ip += "$";
    cout << "Initial input String - " << ip << endl;
    cust.push({0, 0});
    printStack(cust);
    for (j = 0; j < ip.length();)
    {
        cout << endl;
        state = cust.top().second;
        an = ip[j];
        if (an > '0' && an <= '9')
            ic = 0;
        else if (an == '+')
            ic = 1;
        else if (an == '*')
            ic = 2;
        else if (an == '(')
            ic = 3;
        else if (an == ')')
            ic = 4;
        else if (an == '$')
            ic = 5;
        else
        {
            error() ; break;
        }
        if (table[state][ic].first == 's')
        {
            cout << "Shift step - " << endl;
            cust.push({an, table[state][ic].second});
            j++;
            display1(ip, j);
            printStack(cust);
        }
        if (table[state][ic].first == 'r')
        {
            reduce(table[state][ic].second, ip[j - 1]);
            display1(ip, j);
            printStack(cust);
        }
        if (table[state][ic].second == 'a')
        {
            cout << "Given string is accepted" << endl;
            break;
        }
    }
    return 0;
}