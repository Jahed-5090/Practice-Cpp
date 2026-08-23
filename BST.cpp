#include <iostream>

using namespace std;

// 1. Node Structure
// This represents the basic building block of any Binary Tree.
class Node
{
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// 2. Binary Search Tree Class
class BST
{
private:
    Node* root;

    // --- HELPER FUNCTIONS (Hidden from the user) ---

    // Recursive Insertion
    Node* insertHelper(Node* node, int value)
    {
        // Base case: Found the correct empty spot
        if (node == nullptr)
        {
            return new Node(value);
        }

        // BST Logic: Go left if smaller, go right if larger
        if (value < node->data)
        {
            node->left = insertHelper(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertHelper(node->right, value);
        }

        return node;
    }

    // Recursive Search
    Node* searchHelper(Node* node, int value)
    {
        // Base cases: root is null or key is present at root
        if (node == nullptr || node->data == value)
        {
            return node;
        }

        // Key is greater than root's key
        if (node->data < value)
        {
            return searchHelper(node->right, value);
        }

        // Key is smaller than root's key
        return searchHelper(node->left, value);
    }

    // Find the minimum value node (used for deletion)
    Node* findMin(Node* node)
    {
        Node* current = node;
        // The leftmost leaf will be the smallest value
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    // Recursive Deletion
    Node* deleteHelper(Node* node, int value)
    {
        if (node == nullptr) return node;

        // Traverse down the tree to find the node
        if (value < node->data)
        {
            node->left = deleteHelper(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteHelper(node->right, value);
        }
        else
        {
            // Node found! Time to delete it.

            // Case 1: No child
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            // Case 2: One child
            else if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }


            // Case 3: Node with two children
            // Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }

    // Traversals
    void inorderHelper(Node* node)
    {
        if (node != nullptr)
        {
            inorderHelper(node->left);           // Left
            cout << node->data << " ";      // Root
            inorderHelper(node->right);          // Right
        }
    }

    void preorderHelper(Node* node)
    {
        if (node != nullptr)
        {
            cout << node->data << " ";      // Root
            preorderHelper(node->left);          // Left
            preorderHelper(node->right);         // Right
        }
    }

    void postorderHelper(Node* node)
    {
        if (node != nullptr)
        {
            postorderHelper(node->left);         // Left
            postorderHelper(node->right);        // Right
            cout << node->data << " ";      // Root
        }
    }

public:
    // Constructor
    BST()
    {
        root = nullptr;
    }

    // --- PUBLIC API ---
    void insert(int value)
    {
        root = insertHelper(root, value);
    }

    bool search(int value)
    {
        return searchHelper(root, value) != nullptr;
    }

    void remove(int value)
    {
        root = deleteHelper(root, value);
    }

    void displayInorder()
    {
        cout << "Inorder Traversal: ";
        inorderHelper(root);
        cout << endl;
    }

    void displayPreorder()
    {
        cout << "Preorder Traversal: ";
        preorderHelper(root);
        cout << endl;
    }

    void displayPostorder()
    {
        cout << "Postorder Traversal: ";
        postorderHelper(root);
        cout << endl;
    }
};

// 3. Main Function to Demonstrate Operations
int main()
{
    BST tree;

    cout << "--- 1. Insertion ---" << endl;
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int v : values)
    {
        tree.insert(v);
        cout << "Inserted: " << v << endl;
    }
    cout << endl;

    cout << "--- 2. Traversals ---" << endl;
    // Inorder of a BST always yields sorted data
    tree.displayInorder();
    tree.displayPreorder();
    tree.displayPostorder();
    cout << endl;

    cout << "--- 3. Searching ---" << endl;
    int searchKey1 = 60;
    int searchKey2 = 99;
    cout << "Searching for " << searchKey1 << ": "
         << (tree.search(searchKey1) ? "Found" : "Not Found") << endl;
    cout << "Searching for " << searchKey2 << ": "
         << (tree.search(searchKey2) ? "Found" : "Not Found") << endl;
    cout << endl;

    cout << "--- 4. Deletion ---" << endl;
    cout << "Deleting 20 (Leaf Node)..." << endl;
    tree.remove(20);
    tree.displayInorder();

    cout << "Deleting 30 (Node with one child)..." << endl;
    tree.remove(30);
    tree.displayInorder();

    cout << "Deleting 50 (Node with two children)..." <<endl;
    tree.remove(50);
    tree.displayInorder();

    return 0;
}
