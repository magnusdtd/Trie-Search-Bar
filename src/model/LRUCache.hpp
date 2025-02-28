#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <unordered_map>
#include <list>
#include <string>
#include <vector>

class LRUCache {
    int capacity;
    std::list<std::pair<std::string, std::vector<std::string>>> cacheList;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::vector<std::string>>>::iterator> cacheMap;

public:
    LRUCache(int cap) : capacity(cap) {}

    std::vector<std::string> get(const std::string& key);

    void put(const std::string& key, const std::vector<std::string>& value);
    
    void clear();
};

#endif