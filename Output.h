#include<iostream>
#include<vector>
#include<string>
#include <unordered_map>
class SearchResult{
    std::string name;
    std::string email;
    std::string contact;
    public:
    SearchResult(std::string a="",std:: string b="",std::string c=""):name(a),email(b),contact(c) {
        
    }
    friend std::ostream &operator<<(std:: ostream &os,const SearchResult &searchResult);
};

std::ostream& operator<<(std::ostream& os, const SearchResult& searchResult) {
    os << searchResult.name << " " << searchResult.email << " " << searchResult.contact << "\n";
    return os;
}