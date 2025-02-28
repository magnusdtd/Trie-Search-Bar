#include "CompressedTrie.hpp"

bool CompressedTrie::deleteString(Node* p, const std::string& s, int i) {
    if (i == s.size()) {
        if (p->exist > 0) {
            p->exist--;
            if (p->exist == 0 && p->child.empty()) {
                delete p;
                return true;
            }
        }
        return false;
    }

    char c = s[i];
    if (p->child.find(c) == p->child.end())
        return false;

    bool shouldDeleteChild = deleteString(p->child[c], s, i + 1);
    if (shouldDeleteChild) {
        p->child.erase(c);
        if (p->child.empty() && p->exist == 0 && p != root) {
            delete p;
            return true;
        }
    }
    return false;
}

void CompressedTrie::demolish(Node* node) {
    if (node) {
        for (auto& pair : node->child)
            demolish(pair.second);
        delete node;
    }
}

std::vector<std::string> CompressedTrie::weightedBfs(Node* startNode, const std::string& prefix) {
    std::vector<std::string> result;
    if (!startNode) {
        std::cerr << "Start node is null\n";
        return result;
    }

    // Custom comparator for the priority queue
    auto comparator = [this](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
        if ((a.first == b.first))
            return (a.second.length() > b.second.length());  // Ascending order by length
        return (a.first < b.first);  // Descending order by weight
    };

    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, decltype(comparator)> pq(comparator);
    std::queue<std::pair<Node*, std::string>> q;

    q.push({startNode, prefix});
    while (!q.empty()) {
        auto [current, str] = q.front();
        q.pop();

        if (!current)
            continue;

        if (current->exist > 0) {
            int weight = current->weight;
            if (userPreference.find(str) != userPreference.end())
                weight += userPreference[str];
            pq.push({weight, str});  // Rank by weight and length
        }

        for (auto& pair : current->child)
            q.push({pair.second, str + pair.second->label});

    }

    while ((!pq.empty()) && (result.size() < limitWord)) {
        result.emplace_back(pq.top().second);
        pq.pop();
    }

    return result;
}

std::vector<std::string> CompressedTrie::weightedBfs(Node* startNode, const std::string& prefix, long long &count_comparisons) {
    std::vector<std::string> result;
    if (++count_comparisons && !startNode) {
        std::cerr << "Start node is null\n";
        return result;
    }

    // Custom comparator for the priority queue
    auto comparator = [this, &count_comparisons](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
        if (++count_comparisons && (a.first == b.first))
            return ++count_comparisons && (a.second.length() > b.second.length());  // Ascending order by length
        return ++count_comparisons && (a.first < b.first);  // Descending order by weight
    };

    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, decltype(comparator)> pq(comparator);
    std::queue<std::pair<Node*, std::string>> q;

    q.push({startNode, prefix});
    while (++count_comparisons && !q.empty()) {
        Node* current = q.front().first;
        std::string str = q.front().second;
        q.pop();

        if (++count_comparisons && !current)
            continue;

        if (++count_comparisons && current->exist > 0) {
            int weight = current->weight;
            if (++count_comparisons && userPreference.find(str) != userPreference.end())
                weight += userPreference[str];
            pq.push({weight, str});  // Rank by weight and length
        }

        for (auto& pair : current->child)
            q.push({pair.second, str + pair.second->label});

    }

    while ((++count_comparisons && !pq.empty()) && (++count_comparisons && (result.size() < limitWord))) {
        result.emplace_back(pq.top().second);
        pq.pop();
    }

    return result;
}

void CompressedTrie::setLimitWord(int limitWord)
{ 
    this->limitWord = limitWord; 
    cache.clear();
}

void CompressedTrie::addString(const std::string &s) {
    cache.clear();  // Clear cache when adding a string
    Node* p = root;
    int i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (!p->child[c]) {
            p->child[c] = new Node(s.substr(i));
            p->child[c]->exist++;
            p->child[c]->cnt++;
            return;
        }
        Node* child = p->child[c];
        std::string label = child->label;
        int j = 0;
        while (j < label.size() && i < s.size() && label[j] == s[i]) {
            j++;
            i++;
        }
        if (j == label.size()) {
            p = child;
        } else {
            Node* newNode = new Node(label.substr(j));
            newNode->child = std::move(child->child);
            newNode->exist = child->exist;
            newNode->cnt = child->cnt;
            child->label = label.substr(0, j);
            child->child.clear();
            child->child[newNode->label[0]] = newNode;
            if (i < s.size()) {
                Node* newChild = new Node(s.substr(i));
                newChild->exist++;
                newChild->cnt++;
                child->child[newChild->label[0]] = newChild;
            } else {
                child->exist++;
            }
            return;
        }
    }
    p->exist++;
}

void CompressedTrie::deleteString(const std::string& s) {
    cache.clear();  // Clear cache when deleting a string
    if (!findString(s))
        return;
    deleteString(root, s, 0);
}

bool CompressedTrie::findString(const std::string& s) {
    Node* p = root;
    int i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (!p->child[c])
            return false;
        Node* child = p->child[c];
        std::string label = child->label;
        int j = 0;
        while (j < label.size() && i < s.size() && label[j] == s[i]) {
            j++;
            i++;
        }
        if (j != label.size())
            return false;
        p = child;
    }
    return (p->exist != 0);
}

std::vector<std::string> CompressedTrie::search(const std::string& prefix) {
    // Check if the result is already in the cache
    std::vector<std::string> cachedResult = cache.get(prefix);
    if (!cachedResult.empty()) {
        return cachedResult;
    }

    Node* current = root;
    int i = 0;
    while (i < prefix.size()) {
        char c = prefix[i];
        if (!current->child[c])
            return {};
        Node* child = current->child[c];
        std::string label = child->label;
        int j = 0;
        while (j < label.size() && i < prefix.size() && label[j] == prefix[i]) {
            j++;
            i++;
        }
        if (j != label.size())
            return {};
        current = child;
    }
    std::vector<std::string> result = weightedBfs(current, prefix);
    cache.put(prefix, result);  // Store the result in the cache
    return result;
}

std::vector<std::string> CompressedTrie::search(const std::string& prefix, long long &count_comparisons) {
    // Check if the result is already in the cache
    std::vector<std::string> cachedResult = cache.get(prefix);
    if (!cachedResult.empty()) {
        return cachedResult;
    }

    Node* current = root;
    int i = 0;
    while (++count_comparisons && i < prefix.size()) {
        char c = prefix[i];
        if (++count_comparisons && !current->child[c])
            return {};
        Node* child = current->child[c];
        std::string label = child->label;
        int j = 0;
        while (++count_comparisons && j < label.size() && ++count_comparisons && i < prefix.size() && ++count_comparisons && label[j] == prefix[i]) {
            j++;
            i++;
        }
        if (++count_comparisons && j != label.size())
            return {};
        current = child;
    }
    std::vector<std::string> result = weightedBfs(current, prefix, count_comparisons);
    cache.put(prefix, result);  // Store the result in the cache
    return result;
}

void CompressedTrie::readDataFromFile(const std::string &filePath) {
    std::fstream readBuffer(filePath, std::ios::in);
    if (!readBuffer.is_open()) {
        std::cout << "Can not open file at path: " << filePath << '\n';
        exit(1);
    }
    std::string line;

    while (getline(readBuffer, line)) {
        if (line.empty())
            continue;
        this->addString(line);            
    }
    
    readBuffer.close();
}

void CompressedTrie::userSelected(const std::string& word) {
    userPreference[word]++;
    Node* p = root;
    int i = 0;
    while (i < word.size()) {
        char c = word[i];
        if (!p->child[c])
            return;
        Node* child = p->child[c];
        std::string label = child->label;
        int j = 0;
        while (j < label.size() && i < word.size() && label[j] == word[i]) {
            j++;
            i++;
        }
        if (j != label.size())
            return;
        p = child;
        p->weight++;
    }
}