#include <bits/stdc++.h>
using namespace std;
class Grammar
{
private:
    vector<string> terminals;
    vector<string> nonTerminals;
    map<string, vector<string>> grammar;
    vector<vector<string>> table;
    vector<pair<string, string>> gramWithNumber;

public:
    Grammar()
    {
        grammar["A"].push_back("FF");
        grammar["F"].push_back("aF");
        grammar["F"].push_back("b");
        gramWithNumber.push_back({"A", "FF"});
        gramWithNumber.push_back({"F", "aF"});
        gramWithNumber.push_back({"F", "b"});
        terminals = {"a", "b", "$"};
        nonTerminals = {"A", "F"};
        table.push_back({"s3", "s4", "N", "1", "2"});
        table.push_back({"N", "N", "ACC", "N", "N"});
        table.push_back({"s3", "s4", "N", "N", "5"});
        table.push_back({"s3", "s4", "N", "N", "6"});
        table.push_back({"r3", "r3", "r3", "N", "N"});
        table.push_back({"r1", "r1", "r1", "N", "N"});
        table.push_back({"r2", "r2", "r2", "N", "N"});
    }
    vector<pair<string, string>> getGramWithNumber()
    {
        return gramWithNumber;
    }
    map<string, vector<string>> getGrammer()
    {
        return grammar;
    }
    vector<string> getTerms()
    {
        return terminals;
    }
    vector<string> getNonTerms()
    {
        return nonTerminals;
    }
    vector<vector<string>> getTable()
    {
        return table;
    }
};
bool checkTerm(vector<string> terminals, string x)
{
    for (auto i : terminals)
    {
        if (i == x)
            return true;
    }
    return false;
}
bool getExpTerms(string exp, vector<string> terminals, vector<string> &expTerms)
{
    for (auto i : exp)
    {
        string x(1, i);
        if (checkTerm(terminals, x))
            expTerms.push_back(x);
        else
            return false;
    }
    return true;
}
void print_error(vector<string> exp, int expPtr, stack<string> parsingStack, vector<vector<string>> table, string row, string col)
{
    cout << endl
         << endl;
    cout << "------------------Error Info--------------" << endl;
    cout << "Parsing Stack -" << endl;
    while (!parsingStack.empty())
    {
        cout << parsingStack.top() << endl;
        parsingStack.pop();
    }
    cout << "String Content -" << endl;
    for (int i = expPtr; i < exp.size(); i++)
    {
        cout << exp[i];
    }
    cout << endl;
}
int main()
{
    Grammar g;
    vector<string> terminals = g.getTerms();
    vector<string> nonTerminals = g.getNonTerms();
    map<string, vector<string>> grm = g.getGrammer();
    vector<vector<string>> table = g.getTable();
    vector<pair<string, string>> gramWithNumber = g.getGramWithNumber();
    string exp;
    vector<string> expTerm;
    cout << "Grammer-" << endl;
    for (auto prd : grm)
    {
        cout << prd.first << ">";
        for (auto i : prd.second)
        {
            cout << i << "/";
        }
        cout << endl;
    }
    cout << endl
         << endl;
    cout << "Parsing Table-" << endl;
    for (string i : terminals)
    {
        cout << "\t" << i;
    }
    for (string i : nonTerminals)
    {
        cout << "\t" << i;
    }
    for (int i = 0; i, table.size(); i++)
    {
        cout << endl
             << i << "\t";
        for (string j : table[i])
        {
            cout << (j == "N" ? " " : j) << "\t";
        }
        cout << endl;
    }
    cout << endl
         << "Enter String to be parsed - ";
    cin >> exp;
    exp += "$";
    bool canParse = getExpTerms(exp, terminals, expTerm);
    if (!canParse)
    {
        cout << "String Cannot be parsed" << endl;
        exit(0);
    }
    stack<string> parsingStack;
    parsingStack.push("$");
    parsingStack.push("0");
    int expPointer = 0;
    int flag = 1;
    while (1)
    {
        int rowInd = stoi(parsingStack.top());
        string curChar = expTerm[expPointer];
        int collnd;
        if (checkTerm(terminals, curChar))
        {
            collnd = find(terminals.begin(), terminals.end(), curChar) - terminals.begin();
        }
        else
        {
            collnd = terminals.size() + (find(nonTerminals.begin(), nonTerminals.end(), curChar) - nonTerminals.begin());
        }
        string action = table[rowInd][collnd];
        cout << "stack Top -" << parsingStack.top() << "curr Char-" << curChar << "Action - " << action << endl;
        if (action == "ACC")
        {
            flag = 1;
            break;
        }
        if (action == "N")
        {
            cout << endl;
            cout << "Error in cell -" << endl;
            cout << "Row -" << parsingStack.top() << "Column-" << curChar << endl;
            print_error(expTerm, expPointer, parsingStack, table, parsingStack.top(), curChar);
            flag = 0;
            break;
        }
        string type = string(1, action[0]);
        string indexNum = string(1, action[1]);
        if (type == "s")
        {
            parsingStack.push(indexNum);
        }
        if (type == "r")
        {
            string nonTerm = gramWithNumber[stoi(indexNum) - 1].first;
            string prd = gramWithNumber[stoi(indexNum) - 1].second;
            int prdLen = prd.length();
            for (int i = 0; i < 2 * prdLen; i++)
            {
                if (parsingStack.empty())
                {
                    flag = 0;
                    break;
                }
                parsingStack.pop();
            }
            int prevlnd = stoi(parsingStack.top());
            int newCollnd = terminals.size() + (find(nonTerminals.begin(), nonTerminals.end(), nonTerm) - nonTerminals.begin());
            string newlnd = table[prevlnd][newCollnd];
            parsingStack.push(nonTerm);
            parsingStack.push(newlnd);
        }
    }
    if (flag)
        cout << "String parsed";
    else
        cout << "string not parsed";
    return 0;
}