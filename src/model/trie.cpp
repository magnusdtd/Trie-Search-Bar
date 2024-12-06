#include "trie.hpp"

bool Trie::deleteString(Node* p, const std::string& s, int i) {
    if (i != (int)s.size()) {
        char c = s[i];
        bool isChildDeleted = deleteString(p->child[c], s, i + 1);
        if (isChildDeleted) 
            p->child.erase(c);
    } else
        p->exist--;

    if (p != root) {
        p->cnt--;
        if (p->cnt == 0) {
            delete p;
            return true;
        }
    }
    return false;
}

void Trie::demolish(Node* node) {
    if (node) {
        for (auto& pair : node->child)
            demolish(pair.second);
        delete node;
    }
}

std::vector<std::string> Trie::weightedBfs(Node* startNode, const std::string& prefix) {
    std::vector<std::string> result;
    if (!startNode) {
        std::cerr << "Start node is null" << std::endl;
        return result;
    }

    // Custom comparator for the priority queue
    auto comparator = [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
        if (a.second.length() == b.second.length()) {
            return a.first < b.first;  // Descending order by weight
        }
        return a.second.length() > b.second.length();  // Ascending order by length
    };

    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, decltype(comparator)> pq(comparator);
    std::queue<std::pair<Node*, std::string>> q;

    q.push({startNode, prefix});
    while (!q.empty()) {
        Node* current = q.front().first;
        std::string str = q.front().second;
        q.pop();

        if (!current)
            continue;

        if (current->exist > 0) {
            int weight = current->weight;
            if (userPreference.find(str) != userPreference.end()) {
                weight += userPreference[str];
            }
            pq.push({weight, str});  // Rank by weight and length
        }

        for (auto& pair : current->child) {
            q.push({pair.second, str + pair.first});
        }
    }

    while (!pq.empty() && result.size() < limitWord) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    return result;
}

void Trie::addString(const std::string& s) {
    Node* p = root;
    for (char c : s) {
        if (!p->child[c]) {
            p->child[c] = new Node();
            if (!p->child[c]) {
                std::cerr << "Can not allocate new memory for this trie\n";
                exit(1);
            }
        }
        p = p->child[c];
        p->cnt++;
    }
    p->exist++;
    p->weight++;
}

void Trie::deleteString(const std::string& s) {
    if (!findString(s))
        return;
    deleteString(root, s, 0);
}

bool Trie::findString(const std::string& s) {
    Node* p = root;
    for (char c : s) {
        if (!p->child[c])
            return false;
        p = p->child[c];
    }
    return (p->exist != 0);
}

std::vector<std::string> Trie::autoComplete(const std::string& s) {
    Node* current = root;
    for (char c : s) {
        if (!current->child[c])
            return {};
        current = current->child[c];
    }
    return weightedBfs(current, s);
}

void Trie::readDataFromFile(const std::string &filePath) {
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

void Trie::userSelected(const std::string& word) {
    userPreference[word]++;
    Node* p = root;
    for (char c : word) {
        p = p->child[c];
        if (p)
            p->weight++;
    }
}

