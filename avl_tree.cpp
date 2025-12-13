#include <iostream>
#include <algorithm>
using namespace std;

// AVL Node Structure
struct AVLNode {
    int key;
    AVLNode *left;
    AVLNode *right;
    int height;
    
    // Constructor
    AVLNode(int k) : key(k), left(NULL), right(NULL), height(0) {}
};

// Get height of a node
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Get balance factor of a node
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation (LL case)
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    // Return new root
    return x;
}

// Left rotation (RR case)
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    // Return new root
    return y;
}

// Insert a key into AVL tree
AVLNode* insertAVL(AVLNode* node, int key) {
    // 1. Perform normal BST insertion
    if (node == NULL) {
        return new AVLNode(key);
    }
    
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    } else {
        // Duplicate keys not allowed
        return node;
    }
    
    // 2. Update height of current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    // 3. Get balance factor
    int balance = getBalance(node);
    
    // 4. If unbalanced, there are 4 cases
    
    // Left-Left (LL) case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    
    // Right-Right (RR) case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    
    // Left-Right (LR) case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right-Left (RL) case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return unchanged node pointer
    return node;
}

// Inorder traversal of AVL tree
void inorderAVL(AVLNode* root) {
    if (root != NULL) {
        inorderAVL(root->left);
        cout << root->key << " ";
        inorderAVL(root->right);
    }
}

int main() {
    AVLNode* root = NULL;
    int n;
    
    // Read number of keys
    cin >> n;
    
    // Insert keys into AVL tree
    for (int i = 0; i < n; i++) {
        int key;
        cin >> key;
        root = insertAVL(root, key);
    }
    
    // Print inorder traversal
    cout << "AVL Inorder: ";
    inorderAVL(root);
    cout << endl;
    
    // Print height of root
    cout << "Height=" << getHeight(root) << endl;
    
    return 0;
}