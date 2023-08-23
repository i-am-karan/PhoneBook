#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>
class Node
    {
        public:
        std::vector<int> index;
        Node *child[27];
        Node()
        {
            for (int i = 0; i < 27; i++)
                child[i] = NULL;
        }
    void insert(std:: string &s, int ind,std:: unordered_map<char, int>&mp)
    {
        Node *curr = this;
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
                curr->child[x] = new Node();
            }
            curr->child[x]->index.push_back(ind);
            curr = curr->child[x];
        }
    }
};