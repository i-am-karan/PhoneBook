#include <iostream>
#include <unordered_map>
#include<string>
#include<vector>
#include<algorithm>
#include <fstream>
using namespace std;

class phonebook
{
public:
    vector<string> name, email, contact;
    vector<vector<string>>result;
    unordered_map<char, int> mp;  //for Mapping Each lower case AlphaBet plus whitespace to a Number 
    phonebook()
    {
        ifstream name1("names.txt");
        ifstream email1("emails.txt");
        ifstream contact1("contacts.txt");

        string a, b, c;

        while (getline(name1, a))
        {
            name.push_back(a);
        }
        while (getline(email1, b))
        {
            email.push_back(b);
        }
        while (getline(contact1, c))
        {
            contact.push_back(c);
        }

        for (int i = 0; i < 26; i++)
        {
            mp['a' + i] = i;
        }
        mp[' '] = 26; //Mapping white space to 26
    }

    struct node
    {
        vector<int> index;
        node *child[27];
        node()
        {
            for (int i = 0; i < 27; i++)
                child[i] = NULL;
        }
    } root;

    void insert(string &s, int ind)
    {
        node *curr = &root;
        int size = s.size();
        for (int i = 0; i < size; i++)
        {
            char ch;
            ch = s[i];
            if (isalpha(ch))
                ch = tolower(ch);
            int x = mp[ch];
            if (curr->child[x] == NULL)
            {
                curr->child[x] = new node;
            }
            curr->child[x]->index.push_back(ind);
            curr = curr->child[x];
        }
    }

    void init()
    {
        for (int i = 0; i < 1000; i++)
        {   name[i].pop_back();
            contact[i].pop_back();
            email[i].pop_back();
            insert(name[i], i);
        }
    }

    void find(string &s)
    {
        node *curr = &root;
        int size = s.size();
        for (int i = 0; i < size; i++)
        {
            int x = mp[s[i]];
            if (curr != NULL && curr->child[x] != NULL)
            {
                curr = curr->child[x];
            }
            else
                curr = NULL;
        }

        if (curr != NULL)
        {
            for (auto x : curr->index)
            {
                result.push_back({name[x], contact[x], email[x]});
            }
        }
    }

    void print(string s)
    {
        init();
        find(s);
        cout << "There are " << result.size() << " results found related to your entry\n";
        cout << "\n";
        int cnt=1;
        for (auto &x : result)
        {
            cout <<"Result: "<<cnt++<<"."<<"\t"<<x[0] << "\t"<< x[1]<< "\t" <<x[2]<< "\n";
        }
    }
};

int main()
{
    string s;
    getline(cin, s);
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    phonebook final;
    final.print(s);
}