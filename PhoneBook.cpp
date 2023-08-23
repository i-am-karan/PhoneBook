#include <iostream>
#include <unordered_map>
#include<string>
#include<vector>
#include<algorithm>
#include <fstream>
#include "Cache.h"
#include "Trie.h"
using namespace std;

class phonebook
{   
    vector<string> name, email, contact;
    unordered_map<char, int> mp;  //for Mapping Each lower case AlphaBet plus whitespace to a Number 
    Node *Trie;
    LRUCache cache;
public:

    phonebook(int cacheLimit=5):cache(cacheLimit) 
    {
        ifstream name1("names.txt");
        ifstream email1("emails.txt");
        ifstream contact1("contacts.txt");
        string a, b, c;
        Trie=new Node();
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

    void init()
    {
        for (int i = 0; i < 1000; i++)
        {   name[i].pop_back();
            contact[i].pop_back();
            email[i].pop_back();
            Trie->insert(name[i], i,mp);
        }
    }

    vector<SearchResult> find(string &s)
    {   
        if(cache.isCached(s))
        {   cout<<"\n\n\nCache Hit!!!\n\n\n\n\n";
            return cache.get(s);
        }
        Node *curr = Trie;
        vector<SearchResult>result;
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
                result.push_back(SearchResult(name[x], contact[x], email[x]));
            }
        }
        cout<<"\n\n\nCache Miss!!!\n\n\n\n\n";
        cache.put(s,result);
        return result;
    }

    void print(string s)
    {
        
        vector<SearchResult>result=find(s);
        cout << "There are " << result.size() << " results found related to your entry "<<s<<"\n";
        cout << "\n";
        int cnt=1;
        for (auto &x : result)
        {
            cout <<"Result: "<<cnt++<<"."<<"\t"<<x;
        }
    }
};

int main()
{   phonebook final;
    final.init();
    while(true){
    string s;
    cout<<"\n\n\nEnter Name (! for exit): ";
    getline(cin, s);
    if(s=="!") return 0;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    final.print(s);
  } 
}