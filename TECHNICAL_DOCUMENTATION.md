# 🔬 Technical Documentation

## 📚 Deep Dive into Implementation

This document provides comprehensive technical details about the E-Commerce Product Search and Filter System implementation, including algorithm analysis, data structure operations, and performance characteristics.

## 🏗️ Data Structure Implementation Details

### 1. Binary Search Tree (BST) Implementation

#### Node Structure
```cpp
struct Node {
    Product data;        // Product information
    Node* left;         // Left child pointer
    Node* right;        // Right child pointer
};
```

#### BST Insertion Algorithm
```cpp
Node* insertNode(Node* root, Product p) {
    if (root == nullptr) {
        return createNode(p);  // Create new leaf node
    }
    
    int newIDNum = extractIDNumber(p.ID);
    int rootIDNum = extractIDNumber(root->data.ID);

    if (newIDNum < rootIDNum) {
        root->left = insertNode(root->left, p);  // Recursive left insertion
    } else if (newIDNum > rootIDNum) {
        root->right = insertNode(root->right, p); // Recursive right insertion
    } else {
        cout << "Product with ID " << p.ID << " already exists.\n";
    }
    return root;
}
```

**Algorithm Analysis**:
- **Time Complexity**: O(log n) average case, O(n) worst case (unbalanced tree)
- **Space Complexity**: O(h) where h is tree height
- **Balancing**: Currently unbalanced; could be enhanced with AVL or Red-Black trees

#### BST Search Algorithm
```cpp
Node* searchNode(Node* root, const string& targetID) {
    if (root == nullptr || root->data.ID == targetID) {
        return root;  // Found or end of path
    }
    
    int targetIDNum = extractIDNumber(targetID);
    int rootIDNum = extractIDNumber(root->data.ID);
    
    if (targetIDNum < rootIDNum) {
        return searchNode(root->left, targetID);  // Search left subtree
    } else {
        return searchNode(root->right, targetID); // Search right subtree
    }
}
```

**Search Performance**:
- **Best Case**: O(1) - target is root
- **Average Case**: O(log n) - balanced tree
- **Worst Case**: O(n) - linear tree (unbalanced)

#### In-Order Traversal
```cpp
void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);   // Visit left subtree
        // Process current node
        cout << "ID: " << root->data.ID << ", Name: " << root->data.name << endl;
        inOrderTraversal(root->right);  // Visit right subtree
    }
}
```

**Traversal Characteristics**:
- **Order**: Left → Root → Right
- **Result**: Sorted output (ascending by ID)
- **Time Complexity**: O(n) - visits every node exactly once

### 2. Binary Search Algorithm Implementation

#### Array Conversion
```cpp
void toArray(Node* root, vector<Product>& arr) {
    if (root != nullptr) {
        toArray(root->left, arr);   // Convert left subtree
        arr.push_back(root->data);  // Add current node
        toArray(root->right, arr);  // Convert right subtree
    }
}
```

#### Binary Search Implementation
```cpp
int binarySearchByID(const vector<Product>& arr, const string& targetID) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;  // Calculate middle index
        
        if (arr[mid].ID == targetID) {
            return mid;  // Found target
        } 
        else if (arr[mid].ID < targetID) {
            low = mid + 1;   // Search right half
        } 
        else {
            high = mid - 1;  // Search left half
        }
    }
    return -1;  // Target not found
}
```

**Binary Search Analysis**:
- **Prerequisite**: Array must be sorted
- **Time Complexity**: O(log n)
- **Space Complexity**: O(1) - iterative implementation
- **Efficiency**: Optimal for large datasets

### 3. Linked List Shopping Cart

#### Cart Node Structure
```cpp
struct CartNode {
    Product data;        // Product information
    CartNode* next;     // Pointer to next item
};
```

#### Cart Operations

**Adding to Cart**:
```cpp
void addToCart(Product product) {
    if (cartHead == nullptr) {
        cartHead = createCartNode(product);  // First item
        return;
    }

    CartNode* temp = cartHead;
    while (temp->next != nullptr) {
        temp = temp->next;  // Find last node
    }
    temp->next = createCartNode(product);  // Append to end
}
```

**Cart Traversal**:
```cpp
void viewCart() {
    CartNode* temp = cartHead;
    float total = 0;
    
    while (temp != nullptr) {
        cout << "ID: " << temp->data.ID << ", Price: $" << temp->data.price << endl;
        total += temp->data.price;
        temp = temp->next;  // Move to next item
    }
    cout << "Total: $" << total << endl;
}
```

**Cart Performance**:
- **Insertion**: O(n) - linear search for end
- **Display**: O(n) - traverse all items
- **Memory**: Dynamic allocation per item

## 🔍 Search and Filter Implementation

### 1. ID-Based Search Strategy

The system implements a **dual-search approach**:

1. **Primary Search**: BST search (O(log n))
2. **Fallback Search**: Binary search on sorted array (O(log n))

```cpp
void searchByID() {
    string id = normalizeID(userInput);
    
    // Try BST search first
    Node* foundNode = searchNode(root, id);
    if (foundNode != nullptr) {
        displayProduct(foundNode->data);
        return;
    }
    
    // Fallback to array search
    int index = binarySearchByID(sortedProducts, id);
    if (index != -1) {
        displayProduct(sortedProducts[index]);
    } else {
        cout << "Product not found" << endl;
    }
}
```

### 2. Name-Based Search

**Linear Search Implementation**:
```cpp
void searchByName() {
    string name = getUserInput();
    bool found = false;
    
    for (const auto& product : sortedProducts) {
        if (product.name.find(name) != string::npos) {
            displayProduct(product);
            found = true;
        }
    }
    
    if (!found) {
        cout << "No products found" << endl;
    }
}
```

**Performance Characteristics**:
- **Time Complexity**: O(n) - linear search
- **Search Type**: Substring matching (case-sensitive)
- **Optimization Potential**: Could use trie data structure

### 3. Category and Price Filtering

**Category Filtering**:
```cpp
void filterByCategory() {
    string category = getUserInput();
    
    for (const auto& product : sortedProducts) {
        if (product.category == category) {
            displayProduct(product);
        }
    }
}
```

**Price Range Filtering**:
```cpp
void filterByPriceRange() {
    float minPrice, maxPrice;
    cin >> minPrice >> maxPrice;
    
    for (const auto& product : sortedProducts) {
        if (product.price >= minPrice && product.price <= maxPrice) {
            displayProduct(product);
        }
    }
}
```

## 📊 Sorting Algorithm Implementation

### 1. Standard Library Sort

The system uses C++'s built-in `std::sort` algorithm:

```cpp
void sortByPrice(bool ascending) {
    if (ascending) {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { 
                return a.price < b.price; 
            });
    } else {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { 
                return a.price > b.price; 
            });
    }
}
```

**Sorting Performance**:
- **Algorithm**: Introsort (hybrid of quicksort, heapsort, and insertion sort)
- **Time Complexity**: O(n log n) average and worst case
- **Space Complexity**: O(log n)
- **Stability**: Not guaranteed

### 2. Custom Comparator Functions

**Lambda-based Comparators**:
```cpp
// Price comparison
[](const Product& a, const Product& b) { return a.price < b.price; }

// Rating comparison
[](const Product& a, const Product& b) { return a.rating < b.rating; }

// Name comparison
[](const Product& a, const Product& b) { return a.name < b.name; }
```

## 💾 Data Persistence Implementation

### 1. Binary File Format

**File Structure**:
```
[Number of Products (size_t)]
[Product 1]
  ├── ID Length (size_t)
  ├── ID String (char[])
  ├── Name Length (size_t)
  ├── Name String (char[])
  ├── Category Length (size_t)
  ├── Category String (char[])
  ├── Price (float)
  └── Rating (float)
[Product 2]
...
```

**Save Operation**:
```cpp
void saveProductsToFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    
    // Convert BST to vector first
    sortedProducts.clear();
    toArray(root, sortedProducts);
    
    // Write product count
    size_t numProducts = sortedProducts.size();
    outFile.write(reinterpret_cast<const char*>(&numProducts), sizeof(numProducts));
    
    // Write each product
    for (const auto& product : sortedProducts) {
        writeString(outFile, product.ID);
        writeString(outFile, product.name);
        writeString(outFile, product.category);
        outFile.write(reinterpret_cast<const char*>(&product.price), sizeof(float));
        outFile.write(reinterpret_cast<const char*>(&product.rating), sizeof(float));
    }
}
```

**Load Operation**:
```cpp
void loadProductsFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    
    // Clear existing data
    root = nullptr;
    sortedProducts.clear();
    
    // Read product count
    size_t numProducts;
    inFile.read(reinterpret_cast<char*>(&numProducts), sizeof(numProducts));
    
    // Read each product
    for (size_t i = 0; i < numProducts; ++i) {
        Product product = readProduct(inFile);
        root = insertNode(root, product);
    }
    
    // Update sorted array
    toArray(root, sortedProducts);
}
```

## 🚀 Performance Optimization Strategies

### 1. Memory Management

**Dynamic Allocation**:
- BST nodes allocated dynamically
- Cart items allocated as needed
- Automatic cleanup on program exit

**Memory Efficiency**:
- Minimal overhead per node
- Efficient string storage
- Smart pointer usage (could be enhanced)

### 2. Algorithm Optimization

**Search Optimization**:
- Dual-search strategy reduces worst-case scenarios
- BST maintains sorted order automatically
- Binary search provides O(log n) fallback

**Sorting Optimization**:
- Use of efficient standard library algorithms
- In-place sorting to minimize memory usage
- Lazy sorting (only when needed)

### 3. Data Structure Trade-offs

**BST vs Array**:
- **BST**: Fast insertion/deletion, maintains order
- **Array**: Fast random access, efficient sorting
- **Hybrid Approach**: Best of both worlds

**Linked List vs Array for Cart**:
- **Linked List**: Dynamic size, easy insertion
- **Array**: Better cache locality, random access
- **Current Choice**: Linked list for simplicity

## 🔧 Error Handling and Validation

### 1. Input Validation

**Product ID Validation**:
```cpp
string normalizeID(string id) {
    // Ensure first 3 characters are uppercase
    for (int i = 0; i < 3 && i < id.size(); i++) {
        id[i] = toupper(id[i]);
    }
    return id;
}
```

**Name/Category Validation**:
```cpp
bool isValidNameOrCategory(const string& str) {
    if (str.empty()) return false;
    
    bool hasAlpha = false;
    for (char c : str) {
        if (isalpha(c)) hasAlpha = true;
        else if (!isspace(c)) return false;
    }
    return hasAlpha;
}
```

### 2. File I/O Error Handling

**Safe File Operations**:
```cpp
ifstream inFile(filename, ios::binary);
if (!inFile) {
    cerr << "Error: Could not open file for reading: " << filename << endl;
    return;
}
```

## 📈 Scalability Considerations

### 1. Current Limitations

**Memory Constraints**:
- All data stored in memory
- No pagination for large datasets
- Limited by available RAM

**Performance Bottlenecks**:
- Linear search for name/category
- Unbalanced BST could degrade performance
- No caching mechanism

### 2. Scalability Improvements

**Data Structure Enhancements**:
- **Balanced BST**: AVL or Red-Black trees
- **Hash Tables**: For O(1) name/category lookup
- **B-Trees**: For disk-based storage

**Algorithm Improvements**:
- **Indexing**: Create secondary indexes
- **Caching**: LRU cache for frequent searches
- **Parallelization**: Multi-threaded operations

## 🧪 Testing and Validation

### 1. Test Scenarios

**BST Operations**:
- Insert products in random order
- Verify in-order traversal produces sorted output
- Test search with existing and non-existing IDs

**Search Operations**:
- Test binary search on sorted arrays
- Verify fallback search mechanisms
- Test edge cases (empty arrays, single elements)

**Cart Operations**:
- Add multiple items to cart
- Verify total calculation
- Test checkout and cart clearing

### 2. Performance Testing

**Load Testing**:
- Test with large numbers of products
- Measure search and sort performance
- Monitor memory usage patterns

**Stress Testing**:
- Rapid insertions and deletions
- Concurrent operations (future enhancement)
- Memory pressure scenarios

---

*This technical documentation provides comprehensive insights into the system's implementation details. For additional information, refer to the main README.md file.* 