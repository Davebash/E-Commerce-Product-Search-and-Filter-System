#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;

struct Product {
    string ID;        
    string name;
    string category;
    float price;
    float rating;
};

struct Node {
    Product data;
    Node* left;
    Node* right;
};

struct CartNode {
    Product data;
    CartNode* next;
};

// Global variables
Node* root = nullptr;
CartNode* cartHead = nullptr;
vector<Product> sortedProducts;

// Function prototypes
int generateProductNumber(Node* root);
string formatProductID(int number);
string normalizeID(string id);
int extractIDNumber(const string& id);
int findMaxID(Node* root);
Node* createNode(Product p);
Node* insertNode(Node* root, Product p);
Node* searchNode(Node* root, const string& targetID);
void inOrderTraversal(Node* root);
void toArray(Node* root, vector<Product>& arr);
bool isValidNameOrCategory(const string& str);
Node* addProducts(Node* root);
void displayHeader();
void mainMenu();
void productManagementMenu();
void searchFilterMenu();
void sortingMenu();
void cartMenu();
void displayAllProducts();
int binarySearchByID(const vector<Product>& arr, const string& targetID);
void searchByName();
void filterByCategory();
void filterByPriceRange();
void sortByPrice(bool ascending);
void sortByRating(bool ascending);
void sortByName(bool ascending);
void displaySortedList();
void addProductToCart();
void viewCart();
void checkout();
CartNode* createCartNode(Product p);
void addToCart(Product product);
bool isInCart(CartNode* head, const string& productID);
void validateCart(string productID);
void clearScreen();
void displayThankYou();
void saveProductsToFile(const string& filename);
void loadProductsFromFile(const string& filename);
void saveMenu();
void searchByID();
void pressEnterToContinue();




int main() {
    // Load products from file at startup
    loadProductsFromFile("products.dat");
    
    // Debug: Show startup status
    cout << "=== STARTUP DEBUG INFO ===" << endl;
    cout << "BST root: " << (root == nullptr ? "nullptr" : "exists") << endl;
    cout << "Sorted products array size: " << sortedProducts.size() << endl;
    if (!sortedProducts.empty()) {
        cout << "First product: " << sortedProducts[0].ID << endl;
        cout << "Last product: " << sortedProducts[sortedProducts.size()-1].ID << endl;
    }
    cout << "==========================\n" << endl;
    pressEnterToContinue();

    
    int choice;
    do {
        clearScreen();
        mainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                productManagementMenu();
                break;
            case 2:
                searchFilterMenu();
                break;
            case 3:
                sortingMenu();
                break;
            case 4:
                cartMenu();
                break;
            case 5:
                saveMenu();
                break;
            case 6:
                displayThankYou();
                break;
            default:
                if (choice != 6) {
                    cout << "Invalid choice! Please try again.\n";
                    pressEnterToContinue();
                    cin.get();
                }
        }
    } while (choice != 6);
    
    // Save products to file before exiting
    saveProductsToFile("products.dat");
    
    return 0;
}

void clearScreen() {
    // Portable clear screen implementation
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}

void displayHeader() {
    cout << "==================================================\n";
    cout << "        🛒 E-COMMERCE PRODUCT FINDER 🛒         \n";
    cout << "     BST & Binary Search Powered System          \n";
    cout << "==================================================\n\n";
}

void mainMenu() {
    displayHeader();
    cout << "============== MAIN MENU ==============\n";
    cout << " 1️⃣  Product Management\n";
    cout << " 2️⃣  Search & Filter Products\n";
    cout << " 3️⃣  Sorting & Display Options\n";
    cout << " 4️⃣  Cart & Checkout\n";
    cout << " 5️⃣  Save/Load Data\n";
    cout << " 6️⃣  Exit Program\n";
    cout << "=======================================\n";
    cout << "👉 Enter your choice (1-6): ";
}

void saveMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "======== SAVE/LOAD DATA ========\n";
        cout << " 1️⃣  Save Products to File\n";
        cout << " 2️⃣  Load Products from File\n";
        cout << " 3️⃣  Back to Main Menu\n";
        cout << "================================\n";
        cout << "👉 Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                saveProductsToFile("products.dat");
                cout << "\n\033[32m✅ Products saved successfully!\033[0m\n";
                pressEnterToContinue();
                break;
            case 2:
                loadProductsFromFile("products.dat");
                cout << "\n\033[32m✅ Products loaded successfully!\033[0m\n";
                pressEnterToContinue();
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        pressEnterToContinue();
                cin.get();
        }
    } while (choice != 3);
}

void saveProductsToFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    
    // First, convert BST to vector
    sortedProducts.clear();
    toArray(root, sortedProducts);
    
    // Write the number of products
    size_t numProducts = sortedProducts.size();
    outFile.write(reinterpret_cast<const char*>(&numProducts), sizeof(numProducts));
    
    // Write each product
    for (const auto& product : sortedProducts) {
        // Write ID
        size_t idSize = product.ID.size();
        outFile.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
        outFile.write(product.ID.c_str(), idSize);
        
        // Write name
        size_t nameSize = product.name.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(product.name.c_str(), nameSize);
        
        // Write category
        size_t categorySize = product.category.size();
        outFile.write(reinterpret_cast<const char*>(&categorySize), sizeof(categorySize));
        outFile.write(product.category.c_str(), categorySize);
        
        // Write price and rating
        outFile.write(reinterpret_cast<const char*>(&product.price), sizeof(product.price));
        outFile.write(reinterpret_cast<const char*>(&product.rating), sizeof(product.rating));
    }
    
    outFile.close();
}

void loadProductsFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Info: No existing data file found. Starting with empty product list." << endl;
        return;
    }
    
    // Clear existing BST
    root = nullptr;
    sortedProducts.clear();
    
    // Read the number of products
    size_t numProducts;
    inFile.read(reinterpret_cast<char*>(&numProducts), sizeof(numProducts));
    
    // Read each product
    for (size_t i = 0; i < numProducts; ++i) {
        Product product;
        
        // Read ID
        size_t idSize;
        inFile.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
        product.ID.resize(idSize);
        inFile.read(&product.ID[0], idSize);
        
        // Read name
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        product.name.resize(nameSize);
        inFile.read(&product.name[0], nameSize);
        
        // Read category
        size_t categorySize;
        inFile.read(reinterpret_cast<char*>(&categorySize), sizeof(categorySize));
        product.category.resize(categorySize);
        inFile.read(&product.category[0], categorySize);
        
        // Read price and rating
        inFile.read(reinterpret_cast<char*>(&product.price), sizeof(product.price));
        inFile.read(reinterpret_cast<char*>(&product.rating), sizeof(product.rating));
        
        // Insert into BST
        root = insertNode(root, product);
    }
    
    inFile.close();
    
    // Update the sorted products vector
    toArray(root, sortedProducts);
}

void productManagementMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "======== PRODUCT MANAGEMENT ========\n";
        cout << " 1️⃣  Add Product\n";
        cout << " 2️⃣  Display All Products\n";
        cout << " 3️⃣  Search Product in BST\n";
        cout << " 4️⃣  Check ID Status\n";
        cout << " 5️⃣  Back to Main Menu\n";
        cout << "====================================\n";
        cout << "👉 Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                ::root = addProducts(::root);
                sortedProducts.clear();
                toArray(::root, sortedProducts);
                pressEnterToContinue();
                break;
            case 2:
                displayAllProducts();
                pressEnterToContinue();
                break;
            case 3: {
                string id;
                cout << "🔍 Enter Product ID to search in BST (e.g., PID01): ";
                cin >> id;
                id = normalizeID(id);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Node* foundNode = searchNode(root, id);
                if (foundNode != nullptr) {
                    cout << "\n\033[32m✅ Product Found in BST:\033[0m\n";
                    cout << "-----------------------------------\n";
                    cout << "\033[36mID:\033[0m " << foundNode->data.ID
                         << " | \033[36mName:\033[0m " << foundNode->data.name
                         << " | \033[36mCategory:\033[0m " << foundNode->data.category
                         << " | \033[36mPrice:\033[0m $" << foundNode->data.price
                         << " | \033[36mRating:\033[0m " << foundNode->data.rating << "/5" << endl;
                    cout << "-----------------------------------\n";
                } else {
                    cout << "\n\033[31m❌ Product with ID " << id << " not found in BST.\033[0m\n";
                }
                pressEnterToContinue();
                break;
            }
            case 4: {
                clearScreen();
                displayHeader();
                cout << "======== ID STATUS ========\n";
                if (root == nullptr) {
                    cout << "\033[31m❌ No products in system.\033[0m\n";
                    cout << "\033[36mNext product will get ID: PID01\033[0m\n";
                } else {
                    int currentMaxID = findMaxID(root);
                    cout << "\033[32m✅ Current highest ID: PID\033[0m" << (currentMaxID < 10 ? "0" : "") << currentMaxID << endl;
                    cout << "\033[36mNext product will get ID: PID\033[0m" << (currentMaxID + 1 < 10 ? "0" : "") << (currentMaxID + 1) << endl;
                    cout << "\033[36mTotal products: \033[0m" << sortedProducts.size() << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        pressEnterToContinue();
                
        }
    } while (choice != 5);
}

void searchFilterMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "======== SEARCH & FILTER ========\n";
        cout << " 1️⃣  Search by ID\n";
        cout << " 2️⃣  Search by Name\n";
        cout << " 3️⃣  Filter by Category\n";
        cout << " 4️⃣  Filter by Price Range\n";
        cout << " 5️⃣  Refresh Products Array\n";
        cout << " 6️⃣  Back to Main Menu\n";
        cout << "=================================\n";
        cout << "👉 Enter your choice (1-6): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                searchByID();
                break;
            case 2:
                searchByName();
                pressEnterToContinue();
                break;
            case 3:
                filterByCategory();
                pressEnterToContinue();
                break;
            case 4:
                filterByPriceRange();
                pressEnterToContinue();
                break;
            case 5:
                sortedProducts.clear();
                toArray(root, sortedProducts);
                cout << "✅ Products array refreshed! Current size: " 
                     << sortedProducts.size() << endl;
                pressEnterToContinue();
                cin.get();
                break;
            case 6:
                break;
            default:
                cout << "❌ Invalid choice! Try again.\n";
                pressEnterToContinue();
                cin.get();
        }
    } while (choice != 6);
}

void sortingMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "======== SORTING OPTIONS ========\n";
        cout << " 1️⃣  Sort by Price (Ascending)\n";
        cout << " 2️⃣  Sort by Price (Descending)\n";
        cout << " 3️⃣  Sort by Rating (Ascending)\n";
        cout << " 4️⃣  Sort by Rating (Descending)\n";
        cout << " 5️⃣  Sort by Name (Ascending)\n";
        cout << " 6️⃣  Sort by Name (Descending)\n";
        cout << " 7️⃣  Display Sorted List\n";
        cout << " 8️⃣  Back to Main Menu\n";
        cout << "=================================\n";
        cout << "👉 Enter your choice (1-8): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                sortByPrice(true);
                cout << "\n\033[32m✅ Products sorted by price (ascending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 2:
                sortByPrice(false);
                cout << "\n\033[32m✅ Products sorted by price (descending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 3:
                sortByRating(true);
                cout << "\n\033[32m✅ Products sorted by rating (ascending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 4:
                sortByRating(false);
                cout << "\n\033[32m✅ Products sorted by rating (descending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 5:
                sortByName(true);
                cout << "\n\033[32m✅ Products sorted by name (ascending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 6:
                sortByName(false);
                cout << "\n\033[32m✅ Products sorted by name (descending).\033[0m\n";
                pressEnterToContinue();
                break;
            case 7:
                displaySortedList();
                pressEnterToContinue();
                break;
            case 8:
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        pressEnterToContinue();
                cin.get();
        }
    } while (choice != 8);
}

void cartMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "======== CART & CHECKOUT ========\n";
        cout << " 1️⃣  Add Product to Cart\n";
        cout << " 2️⃣  View Cart\n";
        cout << " 3️⃣  Checkout\n";
        cout << " 4️⃣  Back to Main Menu\n";
        cout << "=================================\n";
        cout << "👉 Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1:
                addProductToCart();
                pressEnterToContinue();
                break;
            case 2:
                viewCart();
                pressEnterToContinue();
                break;
            case 3:
                checkout();
                pressEnterToContinue();
                break;
            case 4:
                break;
            default:
                cout << "\033[31m❌ Invalid choice! Please try again.\033[0m\n";
                pressEnterToContinue();
        }
    } while (choice != 4);
}

void displayAllProducts() {
    clearScreen();
    displayHeader();
    cout << "\033[32m======== ALL PRODUCTS =========\033[0m\n";
    if (root == nullptr) {
        cout << "\n\033[31m❌ No products available.\033[0m\n";
        return;
    }
    
    // Show current highest ID for reference
    int currentMaxID = findMaxID(root);
    cout << "\033[36mCurrent highest ID: PID\033[0m" << (currentMaxID < 10 ? "0" : "") << currentMaxID << endl;
    cout << "\033[36mNext product will get ID: PID\033[0m" << (currentMaxID + 1 < 10 ? "0" : "") << (currentMaxID + 1) << endl;
    cout << "\033[36m----------------------------------------\033[0m\n";
    
    inOrderTraversal(root);
}

void searchByID() {
    clearScreen();
    displayHeader();
    cout << "🔍 Enter Product ID to search (e.g., PID01): ";
    string id;

    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    id = normalizeID(id);

    // Try BST search first
    Node* foundNode = searchNode(root, id);
    if (foundNode != nullptr) {
        cout << "\n\033[32m✅ Product Found (BST Search):\033[0m\n";
        cout << "-----------------------------------\n";
        cout << "ID: " << foundNode->data.ID
             << ", Name: " << foundNode->data.name
             << ", Category: " << foundNode->data.category
             << ", Price: $" << foundNode->data.price
             << ", Rating: " << foundNode->data.rating << "/5" << endl;
        cout << "-----------------------------------\n";
    } 
    else {
        cout << "\n\033[33m⚠️ Not found in BST, trying array search...\033[0m\n";
        int index = binarySearchByID(sortedProducts, id);
        if (index != -1) {
            cout << "\n\033[32m✅ Product Found (Array Search):\033[0m\n";
            cout << "-----------------------------------\n";
            cout << "ID: " << sortedProducts[index].ID
                 << ", Name: " << sortedProducts[index].name
                 << ", Category: " << sortedProducts[index].category
                 << ", Price: $" << sortedProducts[index].price
                 << ", Rating: " << sortedProducts[index].rating << "/5" << endl;
            cout << "-----------------------------------\n";
        } else {
            cout << "\n\033[31m❌ Product with ID " << id << " not found.\033[0m\n";
            if (!sortedProducts.empty()) {
                cout << "Available product IDs: ";
                for (const auto& p : sortedProducts) {
                    cout << p.ID << " ";
                }
                cout << endl;
            }
        }
    }
    pressEnterToContinue();
}

string normalizeID(string id) {

    if (id.substr(0, 3) != "PID") {
        id = "PID" + id.substr(3);
    }
    return id;
}

int binarySearchByID(const vector<Product>& arr, const string& targetID) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid].ID == targetID) {
            return mid;
        } 
        else if (arr[mid].ID < targetID) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }

    return -1;
}

void searchByName() {
    clearScreen();
    displayHeader();
    string name;
    cout << "🔍 Enter product name to search: ";
    getline(cin, name);
    
    bool found = false;
    for (const auto& product : sortedProducts) {
        if (product.name.find(name) != string::npos) {
            if (!found) {
                cout << "\n\033[32m✅ Search Results:\033[0m\n";
                cout << "-----------------------------------\n";
                found = true;
            }
            cout << "\033[36mID:\033[0m " << product.ID
                 << " | \033[36mName:\033[0m " << product.name
                 << " | \033[36mCategory:\033[0m " << product.category
                 << " | \033[36mPrice:\033[0m $" << product.price
                 << " | \033[36mRating:\033[0m " << product.rating << "/5" << endl;
        }
    }
    
    if (!found) {
        cout << "\n\033[31m❌ No products found with name containing: \033[0m" << name << endl;
    }
    cout << "-----------------------------------\n";
}

void filterByCategory() {
    clearScreen();
    displayHeader();
    string category;
    cout << "🏷️ Enter category to filter: ";
    getline(cin, category);
    
    bool found = false;
    for (const auto& product : sortedProducts) {
        if (product.category == category) {
            if (!found) {
                cout << "\n\033[32m✅ Products in category '\033[0m" << category << "\033[32m':\033[0m\n";
                cout << "-----------------------------------\n";
                found = true;
            }
            cout << "\033[36mID:\033[0m " << product.ID
                 << " | \033[36mName:\033[0m " << product.name
                 << " | \033[36mPrice:\033[0m $" << product.price
                 << " | \033[36mRating:\033[0m " << product.rating << "/5" << endl;
        }
    }
    
    if (!found) {
        cout << "\n\033[31m❌ No products found in category: \033[0m" << category << endl;
    }
    cout << "-----------------------------------\n";
}

void filterByPriceRange() {
    clearScreen();
    displayHeader();
    float minPrice, maxPrice;
    cout << "💰 Enter minimum price: $";
    cin >> minPrice;
    cout << "💰 Enter maximum price: $";
    cin >> maxPrice;
    
    if (minPrice > maxPrice) {
        cout << "\n\033[31m❌ Invalid range! Minimum price cannot be greater than maximum price.\033[0m\n";
        return;
    }
    
    bool found = false;
    for (const auto& product : sortedProducts) {
        if (product.price >= minPrice && product.price <= maxPrice) {
            if (!found) {
                cout << "\n\033[32m✅ Products in price range \033[0m$" << minPrice << " - $" << maxPrice << "\033[32m:\033[0m\n";
                cout << "-----------------------------------\n";
                found = true;
            }
            cout << "\033[36mID:\033[0m " << product.ID
                 << " | \033[36mName:\033[0m " << product.name
                 << " | \033[36mCategory:\033[0m " << product.category
                 << " | \033[36mPrice:\033[0m $" << product.price
                 << " | \033[36mRating:\033[0m " << product.rating << "/5" << endl;
        }
    }
    
    if (!found) {
        cout << "\n\033[31m❌ No products found in price range \033[0m$" << minPrice << " - $" << maxPrice << endl;
    }
    cout << "-----------------------------------\n";
}

void sortByPrice(bool ascending) {
    if (sortedProducts.empty()) {
        cout << "No products to sort.\n";
        return;
    }
    
    if (ascending) {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.price < b.price; });
    } else {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.price > b.price; });
    }
}

void sortByRating(bool ascending) {
    if (sortedProducts.empty()) {
        cout << "No products to sort.\n";
        return;
    }
    
    if (ascending) {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.rating < b.rating; });
    } else {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.rating > b.rating; });
    }
}

void sortByName(bool ascending) {
    if (sortedProducts.empty()) {
        cout << "No products to sort.\n";
        return;
    }
    
    if (ascending) {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.name < b.name; });
    } else {
        sort(sortedProducts.begin(), sortedProducts.end(), 
            [](const Product& a, const Product& b) { return a.name > b.name; });
    }
}

void displaySortedList() {
    clearScreen();
    displayHeader();
    if (sortedProducts.empty()) {
        cout << "\n\033[31m❌ No products to display.\033[0m\n";
        return;
    }
    
    cout << "\n\033[32m📋 SORTED PRODUCT LIST:\033[0m\n";
    cout << "==========================================\n";
    for (const auto& product : sortedProducts) {
        cout << "\033[36mID:\033[0m " << product.ID
             << " | \033[36mName:\033[0m " << product.name
             << " | \033[36mCategory:\033[0m " << product.category
             << " | \033[36mPrice:\033[0m $" << product.price
             << " | \033[36mRating:\033[0m " << product.rating << "/5" << endl;
    }
    cout << "==========================================\n";
}

void addProductToCart() {
    clearScreen();
    displayHeader();
    if (sortedProducts.empty()) {
        cout << "No products available to add to cart.\n";
        return;
    }
    
    displaySortedList();
    string productID;
    cout << "\nEnter Product ID to add to cart: ";
    cin >> productID;
    
    validateCart(productID);
}

void viewCart() {
    clearScreen();
    displayHeader();
    if (cartHead == nullptr) {
        cout << "Cart is empty.\n";
        return;
    }
    
    cout << "🛒 YOUR SHOPPING CART 🛒\n";
    float total = 0;
    CartNode* temp = cartHead;
    int itemCount = 1;
    
    while (temp != nullptr) {
        cout << itemCount << ". ID: " << temp->data.ID
             << ", Name: " << temp->data.name
             << ", Price: $" << temp->data.price << endl;
        total += temp->data.price;
        temp = temp->next;
        itemCount++;
    }
    
    cout << "----------------------------\n";
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
}

void checkout() {
    clearScreen();
    displayHeader();
    if (cartHead == nullptr) {
        cout << "Cart is empty. Nothing to checkout.\n";
        return;
    }
    
    cout << "💳 CHECKOUT 💳\n";
    cout << "==============================\n";
    
    float total = 0;
    CartNode* temp = cartHead;
    int itemCount = 1;
    
    while (temp != nullptr) {
        cout << itemCount << ". " << temp->data.name 
             << " - $" << temp->data.price << endl;
        total += temp->data.price;
        temp = temp->next;
        itemCount++;
    }
    
    cout << "==============================\n";
    cout << "TOTAL: $" << fixed << setprecision(2) << total << endl;
    cout << "Thank you for your purchase!\n";
    
    // Clear cart
    while (cartHead != nullptr) {
        CartNode* del = cartHead;
        cartHead = cartHead->next;
        delete del;
    }
}

CartNode* createCartNode(Product p) {
    CartNode* newNode = new CartNode();
    newNode->data = p;
    newNode->next = nullptr;
    return newNode;
}

void addToCart(Product product) {
    if (cartHead == nullptr) {
        cartHead = createCartNode(product);
        cout << "Added To Cart Successfully\n";
        return;
    }

    CartNode* temp = cartHead;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = createCartNode(product);
    cout << "Added To Cart Successfully\n";
}

bool isInCart(CartNode* head, const string& productID) {
    CartNode* current = head;
    while (current != nullptr) {
        if (current->data.ID == productID) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void validateCart(string productID) {
    int productLocation = binarySearchByID(sortedProducts, productID);

    if (productLocation == -1) {
        cout << "Invalid Product ID\n";
        return;
    }

    if (isInCart(cartHead, productID)) {
        cout << "This product is already in the cart.\n";
        return;
    }

    addToCart(sortedProducts[productLocation]);
}

void displayThankYou() {
    clearScreen();
    cout << "\n\n";
    cout << "=============================================\n";
    cout << "   Thank you for using our E-Commerce System!\n";
    cout << "=============================================\n";
    cout << "            See you again soon! 👋\n";
    cout << "=============================================\n\n";
}

// Function definitions
int generateProductNumber(Node* root) {
    // Find the highest existing ID number and continue from there
    int maxID = 0;
    
    // Traverse the BST to find the highest ID
    if (root != nullptr) {
        // Use a helper function to find max ID
        maxID = findMaxID(root);
    }
    
    // If no products exist, start from 1, otherwise continue from max + 1
    return maxID + 1;
}

int findMaxID(Node* root) {
    if (root == nullptr) return 0;
    
    int currentID = extractIDNumber(root->data.ID);
    int leftMax = findMaxID(root->left);
    int rightMax = findMaxID(root->right);
    
    return max({currentID, leftMax, rightMax});
}

string formatProductID(int number) {
    return "PID" + (number < 10 ? "0" + to_string(number) : to_string(number));
}

int extractIDNumber(const string& id) {
    return stoi(id.substr(3));
}

Node* createNode(Product p) {
    Node* newNode = new Node();
    newNode->data = p;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, Product p) {
    if (root == nullptr) {
        return createNode(p);
    }
    int newIDNum = extractIDNumber(p.ID);
    int rootIDNum = extractIDNumber(root->data.ID);

    if (newIDNum < rootIDNum) {
        root->left = insertNode(root->left, p);
    } else if (newIDNum > rootIDNum) {
        root->right = insertNode(root->right, p);
    } else {
        cout << "Product with ID " << p.ID << " already exists.\n";
    }
    return root;
}

Node* searchNode(Node* root, const string& targetID) {
    if (root == nullptr || root->data.ID == targetID) {
        return root;
    }
    
    int targetIDNum = extractIDNumber(targetID);
    int rootIDNum = extractIDNumber(root->data.ID);
    
    if (targetIDNum < rootIDNum) {
        return searchNode(root->left, targetID);
    } else {
        return searchNode(root->right, targetID);
    }
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "\033[36mID:\033[0m " << root->data.ID
             << " | \033[36mName:\033[0m " << root->data.name
             << " | \033[36mCategory:\033[0m " << root->data.category
             << " | \033[36mPrice:\033[0m $" << root->data.price
             << " | \033[36mRating:\033[0m " << root->data.rating << "/5" << endl;
        inOrderTraversal(root->right);
    }
}

void toArray(Node* root, vector<Product>& arr) {
    if (root != nullptr) {
        toArray(root->left, arr);
        arr.push_back(root->data);
        toArray(root->right, arr);
    }
}

bool isValidNameOrCategory(const string& str) {
    if (str.empty()) return false;
    bool hasAlpha = false;
    for (char c : str) {
        if (isalpha(c)) hasAlpha = true;
        else if (!isspace(c)) return false;
    }
    return hasAlpha;
}

Node* addProducts(Node* root) {
    char choice;

    do {
        clearScreen();
        displayHeader();
        Product p;
        cout << "\nEnter product details:\n";

        int autoID = generateProductNumber(root);
        p.ID = formatProductID(autoID);
        cout << "Assigned ID: " << p.ID << endl;

        do {
            cout << "Name: ";
            getline(cin, p.name);
            if (!isValidNameOrCategory(p.name))
                cout << "Invalid name! Only letters and spaces are allowed.\n";
        } while (!isValidNameOrCategory(p.name));

        do {
            cout << "Category: ";
            getline(cin, p.category);
            if (!isValidNameOrCategory(p.category))
                cout << "Invalid category! Only letters and spaces are allowed.\n";
        } while (!isValidNameOrCategory(p.category));

        cout << "Price: $";
        while (!(cin >> p.price) || p.price < 0) {
            cout << "Invalid price! Enter a non-negative number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Rating (1-5): ";
        while (!(cin >> p.rating) || p.rating < 1.0 || p.rating > 5.0) {
            cout << "Invalid rating! Enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        root = insertNode(root, p);

        cout << "\nDo you want to add another product? (y/n): ";
        string input;
        getline(cin, input);
        if (input.empty()) choice = 'n';
        else choice = tolower(input[0]);

    } while (choice == 'y');

    return root;
}
void pressEnterToContinue() {
    cout << "\n\033[36mPress Enter to continue...\033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
}