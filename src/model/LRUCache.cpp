#include "LRUCache.hpp"

std::vector<std::string> LRUCache::get(const std::string &key)
 {
    if (cacheMap.find(key) == cacheMap.end()) {
        return {};
    }
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    return cacheMap[key]->second;
}

void LRUCache::put(const std::string &key, const std::vector<std::string> &value)
{
    if (cacheMap.find(key) != cacheMap.end()) {
        cacheList.erase(cacheMap[key]);
    }
    cacheList.push_front({key, value});
    cacheMap[key] = cacheList.begin();
    if (cacheList.size() > capacity) {
        cacheMap.erase(cacheList.back().first);
        cacheList.pop_back();
    }
}

void LRUCache::clear()
{
    cacheList.clear();
    cacheMap.clear();
}
