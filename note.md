### **Analysis of the Improved Trie Algorithm**

#### 1. **Time Complexity**

##### **a. Inserting a String (`addString`)**
- The insertion process iterates through the characters of the input string.
- Let `L` be the length of the string, then:
  - Each character is processed in \(O(1)\) due to the hash map used for children.
  - Total complexity: **\(O(L)\)** for one string.
- For inserting `N` strings with an average length \(L\):
  - Total complexity: **\(O(N \cdot L)\)**.

##### **b. Autocomplete Suggestions (`autoComplete`)**
- The `autoComplete` method has two main steps:
  1. Traversing the Trie to locate the node corresponding to the prefix.
     - Complexity: \(O(P)\), where \(P\) is the length of the prefix.
  2. Performing a **weighted BFS** to gather all possible completions:
     - The BFS visits all descendant nodes of the prefix node.
     - Let \(M\) be the number of descendant nodes, and \(C\) be the total characters in their paths.
     - Traversing and processing all nodes takes \(O(M + C)\).
     - Using a priority queue for ranking adds a log factor for each insertion, \(O(M \cdot \log(M))\).

  - Total complexity for `autoComplete`: **\(O(P + M \cdot \log(M) + C)\)**.

##### **c. User Selection Update (`userSelected`)**
- Traversing the Trie to update weights for the selected string.
- Let \(L\) be the length of the selected string:
  - Complexity: \(O(L)\).

##### **d. Deletion (`deleteString`)**
- Deleting a string requires traversing its path in the Trie and potentially cleaning up unused nodes.
- Let \(L\) be the length of the string:
  - Complexity: \(O(L)\) for traversal and node deletions.

##### **e. Reading Data from File (`readDataFromFile`)**
- Each line of the file is inserted into the Trie.
- Let \(N\) be the number of lines and \(L\) the average length of a line:
  - Total complexity: \(O(N \cdot L)\).

---

#### 2. **Space Complexity**

##### **a. Trie Structure**
- Each node stores:
  1. A hash map for its children, which can use \(O(|\Sigma|)\) memory, where \(|\Sigma|\) is the alphabet size.
  2. Two integers (`exist` and `cnt`) and a weight.

- For a dataset with \(N\) strings of average length \(L\):
  - The Trie may have up to \(N \cdot L\) nodes (in the worst case, each character in each string forms a unique node).
  - Each node uses \(O(|\Sigma|)\) space for the hash map.
  - Total space: **\(O(N \cdot L \cdot |\Sigma|)\)** in the worst case.

##### **b. BFS for Autocomplete**
- The BFS queue can grow up to the size of the Trie subtree corresponding to the prefix.
- Let \(M\) be the number of descendant nodes:
  - Queue memory: \(O(M)\).
  - Priority queue for weighted ranking: \(O(M)\).
  - Total space: **\(O(M)\)** for BFS.

##### **c. User Preferences (`userPreference`)**
- The map tracks weights for each string selected by the user.
- Let \(U\) be the number of unique strings selected by users:
  - Memory used: **\(O(U)\)**.

---

#### 3. **Summary**

| Operation               | Time Complexity                  | Space Complexity                 |
|-------------------------|-----------------------------------|-----------------------------------|
| **Insert (`addString`)** | \(O(L)\) per string, \(O(N \cdot L)\) for \(N\) strings | \(O(N \cdot L \cdot |\Sigma|)\)     |
| **Autocomplete**         | \(O(P + M \cdot \log(M) + C)\)   | \(O(M)\)                         |
| **User Selection Update**| \(O(L)\)                         | \(O(U)\)                         |
| **Deletion**             | \(O(L)\)                         | \(O(N \cdot L \cdot |\Sigma|)\) (after insertion) |
| **File Read**            | \(O(N \cdot L)\)                 | \(O(N \cdot L \cdot |\Sigma|)\)     |

---

### **Optimizations**

1. **Space Efficiency**
   - If the dataset uses only lowercase English letters (\(26\) characters), replacing `std::unordered_map` with `std::array` reduces memory overhead.

2. **Weighted Ranking**
   - Weights are dynamically updated, allowing adaptive performance based on user behavior.

3. **Scalability**
   - The algorithm efficiently scales for large datasets with millions of entries due to the logarithmic factor in suggestion ranking.

# The main differences between a Directed Acyclic Word Graph (DAWG) and a Trie are related to their structure, memory efficiency, and performance characteristics. Here are the key differences:

### Structure
- **Trie**: A Trie (or prefix tree) is a tree-like data structure where each node represents a single character of a word. Each path from the root to a leaf node represents a complete word. Tries can have many redundant nodes because each word is stored independently.
- **DAWG**: A DAWG is a more compact representation of a Trie. It merges equivalent subtrees, meaning that common suffixes are shared among different words. This results in a directed acyclic graph rather than a tree.

### Memory Efficiency
- **Trie**: Tries can consume a lot of memory, especially when there are many words with common prefixes but different suffixes. Each unique suffix is stored separately, leading to redundancy.
- **DAWG**: DAWGs are more memory-efficient because they merge equivalent states (nodes) and share common suffixes. This reduces the number of nodes and edges, leading to a more compact representation.

### Performance
- **Trie**: Tries provide fast insertion and search operations, typically O(m) time complexity, where m is the length of the word. However, they can be less efficient in terms of memory usage.
- **DAWG**: DAWGs also provide fast search operations, but the construction can be more complex due to the need to merge equivalent states. Once constructed, DAWGs offer efficient search and autocomplete operations with reduced memory usage.

### Construction
- **Trie**: Constructing a Trie is straightforward. You simply insert each word character by character, creating new nodes as needed.
- **DAWG**: Constructing a DAWG is more complex. It involves adding words and merging equivalent states to ensure that the graph remains acyclic and compact. This often requires additional data structures and algorithms to manage state equivalence and suffix links.

### Use Cases
- **Trie**: Tries are suitable for applications where fast insertion and search operations are required, and memory usage is not a primary concern. Examples include spell checkers, autocomplete systems, and IP routing.
- **DAWG**: DAWGs are ideal for applications where memory efficiency is crucial, and the dataset contains many words with common suffixes. They are often used in dictionary compression, text indexing, and advanced autocomplete systems.

### Example
Consider the words "cat", "cats", and "dog":
- **Trie**: Each word is stored independently, resulting in separate paths for "cat" and "cats", and another path for "dog".
- **DAWG**: The common suffix "at" is shared between "cat" and "cats", reducing redundancy. The word "dog" would have a separate path, but any common suffixes with other words would be shared.

In summary, DAWGs optimize Tries by merging equivalent states, leading to reduced memory usage and potentially faster search operations for large datasets with many common suffixes. However, they come with increased complexity in construction and maintenance.