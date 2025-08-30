# 📚 API Documentation

## 🔧 Function Reference Guide

This document provides comprehensive documentation for all functions in the E-Commerce Product Search and Filter System, including parameters, return values, usage examples, and implementation details.

## 📋 Table of Contents

- [Data Structures](#data-structures)
- [Core Functions](#core-functions)
- [Product Management](#product-management)
- [Search & Filter Functions](#search--filter-functions)
- [Sorting Functions](#sorting-functions)
- [Cart Operations](#cart-operations)
- [File I/O Operations](#file-io-operations)
- [Utility Functions](#utility-functions)
- [Menu Functions](#menu-functions)

## 🏗️ Data Structures

### Product Structure
```cpp
struct Product {
    string ID;        // Product identifier (e.g., "PID01")
    string name;      // Product name
    string category;  // Product category
    float price;      // Product price
    float rating;     // Product rating (1.0 - 5.0)
};
```

### BST Node Structure
```cpp
struct Node {
    Product data;     // Product information
    Node* left;       // Left child pointer
    Node* right;      // Right child pointer
};
```

### Cart Node Structure
```cpp
struct CartNode {
    Product data;     // Product information
    CartNode* next;   // Pointer to next cart item
};
```

## ⚙️ Core Functions

### Node Creation and Management

#### `createNode(Product p)`
Creates a new BST node with the given product data.

**Parameters:**
- `p` (Product): Product data to store in the node

**Returns:**
- `Node*`: Pointer to the newly created node

**Usage Example:**
```cpp
Product newProduct = {"PID01", "Laptop", "Electronics", 999.99, 4.5};
Node* newNode = createNode(newProduct);
```

**Implementation:**
```cpp
Node* createNode(Product p) {
    Node* newNode = new Node();
    newNode->data = p;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
```

#### `createCartNode(Product p)`
Creates a new cart node with the given product data.

**Parameters:**
- `p` (Product): Product data to store in the cart

**Returns:**
- `CartNode*`: Pointer to the newly created cart node

**Usage Example:**
```cpp
Product product = {"PID01", "Laptop", "Electronics", 999.99, 4.5};
CartNode* cartItem = createCartNode(product);
```

## 🏪 Product Management

### Product Addition and Storage

#### `addProducts(Node* root)`
Interactive function to add multiple products to the BST.

**Parameters:**
- `root` (Node*): Root of the BST

**Returns:**
- `Node*`: Updated root of the BST

**Features:**
- Auto-generates product IDs
- Validates user input
- Supports multiple product additions
- Interactive user interface

**Usage Example:**
```cpp
Node* root = nullptr;
root = addProducts(root);
```

**Implementation Details:**
- Generates sequential product IDs (PID01, PID02, etc.)
- Validates name and category (letters and spaces only)
- Ensures price is non-negative
- Ensures rating is between 1.0 and 5.0

#### `insertNode(Node* root, Product p)`
Inserts a product into the BST based on product ID.

**Parameters:**
- `root` (Node*): Root of the BST
- `p` (Product): Product to insert

**Returns:**
- `Node*`: Updated root of the BST

**Algorithm:**
- Recursively traverses the BST
- Compares product ID numbers
- Inserts in appropriate subtree
- Handles duplicate IDs

**Usage Example:**
```cpp
Product product = {"PID01", "Laptop", "Electronics", 999.99, 4.5};
root = insertNode(root, product);
```

**Time Complexity:** O(log n) average case, O(n) worst case

### Product Search and Retrieval

#### `searchNode(Node* root, const string& targetID)`
Searches for a product in the BST by ID.

**Parameters:**
- `root` (Node*): Root of the BST
- `targetID` (string): Product ID to search for

**Returns:**
- `Node*`: Pointer to found node, or nullptr if not found

**Algorithm:**
- Recursively traverses the BST
- Compares target ID with current node ID
- Navigates left or right based on comparison
- Returns node when found or nullptr when not found

**Usage Example:**
```cpp
string searchID = "PID01";
Node* foundNode = searchNode(root, searchID);
if (foundNode != nullptr) {
    cout << "Found: " << foundNode->data.name << endl;
}
```

**Time Complexity:** O(log n) average case, O(n) worst case

### Product Display

#### `displayAllProducts()`
Displays all products in the system with current ID status.

**Features:**
- Shows current highest product ID
- Displays next available ID
- Lists all products in sorted order
- Handles empty product lists

**Usage Example:**
```cpp
displayAllProducts();
```

#### `inOrderTraversal(Node* root)`
Performs in-order traversal of the BST to display products in sorted order.

**Parameters:**
- `root` (Node*): Root of the BST

**Algorithm:**
- Traverses left subtree recursively
- Processes current node
- Traverses right subtree recursively

**Output:** Products displayed in ascending ID order

**Usage Example:**
```cpp
inOrderTraversal(root);
```

**Time Complexity:** O(n) - visits every node exactly once

## 🔍 Search & Filter Functions

### ID-Based Search

#### `searchByID()`
Comprehensive ID-based search with dual-search strategy.

**Search Strategy:**
1. **Primary Search**: BST search (O(log n))
2. **Fallback Search**: Binary search on sorted array (O(log n))

**Features:**
- Normalizes user input (converts to uppercase)
- Provides detailed search results
- Shows available product IDs if search fails
- Interactive user interface

**Usage Example:**
```cpp
searchByID();
```

#### `binarySearchByID(const vector<Product>& arr, const string& targetID)`
Performs binary search on sorted product array.

**Parameters:**
- `arr` (vector<Product>&): Sorted array of products
- `targetID` (string): Product ID to search for

**Returns:**
- `int`: Index of found product, or -1 if not found

**Prerequisites:**
- Array must be sorted by product ID
- Products must have unique IDs

**Algorithm:**
- Maintains low and high pointers
- Calculates middle index
- Compares target with middle element
- Adjusts search range accordingly

**Usage Example:**
```cpp
int index = binarySearchByID(sortedProducts, "PID01");
if (index != -1) {
    cout << "Found at index: " << index << endl;
}
```

**Time Complexity:** O(log n)

### Name and Category Search

#### `searchByName()`
Searches for products by name using substring matching.

**Features:**
- Case-sensitive substring search
- Displays all matching products
- Shows comprehensive product information
- Handles no-match scenarios

**Algorithm:**
- Linear search through product array
- Uses `string::find()` for substring matching
- Collects and displays all matches

**Usage Example:**
```cpp
searchByName();
```

**Time Complexity:** O(n)

#### `filterByCategory()`
Filters products by specific category.

**Features:**
- Exact category matching
- Displays all products in category
- Shows product details
- Handles empty categories

**Algorithm:**
- Linear search through product array
- Exact string comparison
- Collects and displays matches

**Usage Example:**
```cpp
filterByCategory();
```

**Time Complexity:** O(n)

### Price Range Filtering

#### `filterByPriceRange()`
Filters products within specified price range.

**Features:**
- User-defined minimum and maximum prices
- Input validation for price range
- Displays products within range
- Shows comprehensive product information

**Input Validation:**
- Ensures minimum price ≤ maximum price
- Handles invalid input gracefully

**Algorithm:**
- Linear search through product array
- Price range comparison
- Collects and displays matches

**Usage Example:**
```cpp
filterByPriceRange();
```

**Time Complexity:** O(n)

## 📊 Sorting Functions

### Multi-Criteria Sorting

#### `sortByPrice(bool ascending)`
Sorts products by price in specified order.

**Parameters:**
- `ascending` (bool): true for ascending, false for descending

**Algorithm:**
- Uses C++ standard library `std::sort`
- Custom comparator for price comparison
- In-place sorting for memory efficiency

**Usage Example:**
```cpp
sortByPrice(true);   // Ascending order
sortByPrice(false);  // Descending order
```

**Time Complexity:** O(n log n)

#### `sortByRating(bool ascending)`
Sorts products by rating in specified order.

**Parameters:**
- `ascending` (bool): true for ascending, false for descending

**Algorithm:**
- Uses C++ standard library `std::sort`
- Custom comparator for rating comparison
- Maintains product data integrity

**Usage Example:**
```cpp
sortByRating(true);   // Ascending order
sortByRating(false);  // Descending order
```

**Time Complexity:** O(n log n)

#### `sortByName(bool ascending)`
Sorts products by name in specified order.

**Parameters:**
- `ascending` (bool): true for ascending, false for descending

**Algorithm:**
- Uses C++ standard library `std::sort`
- Custom comparator for name comparison
- Lexicographic ordering

**Usage Example:**
```cpp
sortByName(true);   // Ascending order
sortByName(false);  // Descending order
```

**Time Complexity:** O(n log n)

### Display Sorted Results

#### `displaySortedList()`
Displays the currently sorted product list.

**Features:**
- Shows all products in current sort order
- Displays comprehensive product information
- Handles empty product lists
- Clear formatting and organization

**Usage Example:**
```cpp
displaySortedList();
```

## 🛒 Cart Operations

### Cart Management

#### `addProductToCart()`
Interactive function to add products to shopping cart.

**Features:**
- Displays available products
- User input for product selection
- Duplicate prevention
- Validation of product existence

**Algorithm:**
- Shows sorted product list
- Accepts user input for product ID
- Validates product ID
- Adds to cart if valid

**Usage Example:**
```cpp
addProductToCart();
```

#### `addToCart(Product product)`
Adds a product to the shopping cart.

**Parameters:**
- `product` (Product): Product to add to cart

**Algorithm:**
- Creates new cart node
- Appends to end of cart list
- Maintains cart structure

**Usage Example:**
```cpp
Product product = {"PID01", "Laptop", "Electronics", 999.99, 4.5};
addToCart(product);
```

**Time Complexity:** O(n) - linear search for end of list

#### `viewCart()`
Displays current shopping cart contents.

**Features:**
- Shows all cart items
- Displays product details
- Calculates total price
- Handles empty cart

**Algorithm:**
- Traverses cart linked list
- Accumulates total price
- Displays formatted output

**Usage Example:**
```cpp
viewCart();
```

**Time Complexity:** O(n) - traverses all cart items

#### `checkout()`
Processes cart checkout and clears cart.

**Features:**
- Displays final cart contents
- Shows total purchase amount
- Clears cart after checkout
- Confirmation message

**Algorithm:**
- Traverses cart linked list
- Calculates final total
- Deallocates cart memory
- Resets cart pointer

**Usage Example:**
```cpp
checkout();
```

**Time Complexity:** O(n) - traverses and clears all cart items

### Cart Validation

#### `validateCart(string productID)`
Validates product before adding to cart.

**Parameters:**
- `productID` (string): Product ID to validate

**Validation Steps:**
1. Checks if product exists in system
2. Verifies product is not already in cart
3. Adds product if validation passes

**Usage Example:**
```cpp
validateCart("PID01");
```

#### `isInCart(CartNode* head, const string& productID)`
Checks if product is already in cart.

**Parameters:**
- `head` (CartNode*): Head of cart linked list
- `productID` (string): Product ID to check

**Returns:**
- `bool`: true if product is in cart, false otherwise

**Algorithm:**
- Linear search through cart list
- String comparison for ID matching

**Usage Example:**
```cpp
bool inCart = isInCart(cartHead, "PID01");
```

**Time Complexity:** O(n) - linear search through cart

## 💾 File I/O Operations

### Data Persistence

#### `saveProductsToFile(const string& filename)`
Saves all products to binary file.

**Parameters:**
- `filename` (string): Name of file to save to

**File Format:**
- Binary format for efficiency
- Product count header
- Variable-length string storage
- Numeric data storage

**Algorithm:**
- Converts BST to sorted array
- Writes file header (product count)
- Writes each product sequentially
- Handles file I/O errors

**Usage Example:**
```cpp
saveProductsToFile("products.dat");
```

#### `loadProductsFromFile(const string& filename)`
Loads products from binary file.

**Parameters:**
- `filename` (string): Name of file to load from

**Features:**
- Automatic data restoration
- BST reconstruction
- Sorted array update
- Error handling for missing files

**Algorithm:**
- Reads file header (product count)
- Reads each product sequentially
- Reconstructs BST structure
- Updates sorted array

**Usage Example:**
```cpp
loadProductsFromFile("products.dat");
```

## 🛠️ Utility Functions

### ID Management

#### `generateProductNumber()`
Generates next available product number.

**Returns:**
- `int`: Next available product number

**Algorithm:**
- Finds maximum existing ID number
- Returns max + 1 for new product
- Handles empty system case

**Usage Example:**
```cpp
int nextID = generateProductNumber();
```

#### `formatProductID(int number)`
Formats product number into ID string.

**Parameters:**
- `number` (int): Product number

**Returns:**
- `string`: Formatted product ID (e.g., "PID01")

**Format:**
- Prefix: "PID"
- Zero-padded number
- Example: PID01, PID02, PID10

**Usage Example:**
```cpp
string id = formatProductID(1);  // Returns "PID01"
```

#### `extractIDNumber(const string& id)`
Extracts numeric part from product ID.

**Parameters:**
- `id` (string): Product ID string

**Returns:**
- `int`: Numeric part of ID

**Algorithm:**
- Substring extraction after "PID"
- String to integer conversion

**Usage Example:**
```cpp
int num = extractIDNumber("PID01");  // Returns 1
```

#### `findMaxID(Node* root)`
Finds maximum product ID in BST.

**Parameters:**
- `root` (Node*): Root of BST

**Returns:**
- `int`: Maximum product ID number

**Algorithm:**
- Recursive tree traversal
- Compares all node IDs
- Returns maximum value

**Usage Example:**
```cpp
int maxID = findMaxID(root);
```

**Time Complexity:** O(n) - visits all nodes

### Input Validation

#### `isValidNameOrCategory(const string& str)`
Validates name or category input.

**Parameters:**
- `str` (string): String to validate

**Returns:**
- `bool`: true if valid, false otherwise

**Validation Rules:**
- Non-empty string
- Contains at least one alphabetic character
- Only letters and spaces allowed

**Usage Example:**
```cpp
bool valid = isValidNameOrCategory("Laptop Computer");
```

#### `normalizeID(string id)`
Normalizes product ID input.

**Parameters:**
- `id` (string): ID string to normalize

**Returns:**
- `string`: Normalized ID string

**Normalization:**
- Converts first 3 characters to uppercase
- Maintains rest of string unchanged

**Usage Example:**
```cpp
string normalized = normalizeID("pid01");  // Returns "PID01"
```

### Array Operations

#### `toArray(Node* root, vector<Product>& arr)`
Converts BST to sorted array.

**Parameters:**
- `root` (Node*): Root of BST
- `arr` (vector<Product>&): Target array (passed by reference)

**Algorithm:**
- In-order traversal of BST
- Adds products to array in sorted order
- Maintains array sorting

**Usage Example:**
```cpp
vector<Product> products;
toArray(root, products);
```

**Time Complexity:** O(n) - visits all nodes

## 🎮 Menu Functions

### Main Menu System

#### `mainMenu()`
Displays main application menu.

**Features:**
- Clear header display
- Numbered menu options
- User input prompt
- Professional formatting

**Menu Options:**
1. Product Management
2. Search & Filter Products
3. Sorting & Display Options
4. Cart & Checkout
5. Save/Load Data
6. Exit Program

#### `productManagementMenu()`
Displays product management submenu.

**Features:**
- Product addition interface
- Product display options
- BST search functionality
- ID status information

**Menu Options:**
1. Add Product
2. Display All Products
3. Search Product in BST
4. Check ID Status
5. Back to Main Menu

#### `searchFilterMenu()`
Displays search and filter submenu.

**Features:**
- Multiple search options
- Filtering capabilities
- Array refresh functionality
- Comprehensive search tools

**Menu Options:**
1. Search by ID
2. Search by Name
3. Filter by Category
4. Filter by Price Range
5. Refresh Products Array
6. Back to Main Menu

#### `sortingMenu()`
Displays sorting options submenu.

**Features:**
- Multi-criteria sorting
- Bidirectional sorting
- Sorted list display
- Flexible sorting options

**Menu Options:**
1. Sort by Price (Ascending)
2. Sort by Price (Descending)
3. Sort by Rating (Ascending)
4. Sort by Rating (Descending)
5. Sort by Name (Ascending)
6. Sort by Name (Descending)
7. Display Sorted List
8. Back to Main Menu

#### `cartMenu()`
Displays shopping cart submenu.

**Features:**
- Cart management options
- Checkout process
- Product addition interface
- Cart viewing capabilities

**Menu Options:**
1. Add Product to Cart
2. View Cart
3. Checkout
4. Back to Main Menu

#### `saveMenu()`
Displays data persistence submenu.

**Features:**
- File save operations
- File load operations
- Data management tools
- Backup and restore

**Menu Options:**
1. Save Products to File
2. Load Products from File
3. Back to Main Menu

### Display and Interface

#### `displayHeader()`
Displays application header.

**Features:**
- Professional branding
- Clear title display
- System description
- Visual formatting

#### `clearScreen()`
Clears terminal screen.

**Features:**
- Cross-platform compatibility
- Windows and Unix support
- Clean user interface
- Professional appearance

#### `pressEnterToContinue()`
Prompts user to continue.

**Features:**
- User-friendly prompts
- Consistent interface
- Input validation
- Clear instructions

#### `displayThankYou()`
Displays exit message.

**Features:**
- Professional farewell
- Clear formatting
- User appreciation
- Clean exit

## 🔄 Main Application Flow

### `main()`
Main application entry point.

**Application Flow:**
1. **Initialization**: Load existing data from file
2. **Debug Information**: Display startup status
3. **Main Loop**: Continuous menu system
4. **Data Persistence**: Save data before exit

**Features:**
- Automatic data loading
- Comprehensive menu system
- Error handling
- Clean shutdown

**Usage Example:**
```cpp
int main() {
    // Application runs automatically
    return 0;
}
```

---

*This API documentation provides comprehensive coverage of all functions in the system. For implementation details and performance analysis, refer to the TECHNICAL_DOCUMENTATION.md file.* 