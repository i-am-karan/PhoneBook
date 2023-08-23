#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<iterator>
#include<unordered_map>
#include <cassert>
#include "Output.h"
class LRUCache{
    std::list<std:: string>order;
    std::unordered_map<std::string,std::pair<std::vector<SearchResult>,std::list<std::string>::iterator>>cache;
    int capacity;
    public:
    LRUCache(int cacheLimit=5):capacity(cacheLimit){
    }
    void update(std::string key){
        auto it=cache[key];
        order.erase(it.second);
        order.push_front(key);
        cache[key].second=order.begin();
    }
    void put(std::string key,std::vector<SearchResult>value){
        if(cache.find(key)==cache.end()){
            if(cache.size()==capacity){
                std::string to_delete=order.back();
                cache.erase(to_delete);
                order.pop_back();
            }
            order.push_front(key);
        }
        else{
            assert(true);
            update(key);
        }
        cache[key]={value,order.begin()};

    }
    std::vector<SearchResult>get(std::string key){
        std::vector<SearchResult>cacheResult;
        if(cache.find(key)!=cache.end()){
            update(key);
            cacheResult=cache[key].first;
        }
        return cacheResult;
    }
    bool isCached(std:: string key){
        if(cache.find(key)!=cache.end()){
            return true;
        }    
        return false;
    }
};