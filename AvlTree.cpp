#include<iostream>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1; // New node is initially at height 1
    }
};

int getheight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getbalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getheight(node->left) - getheight(node->right);
}

Node* rightRotate(Node* root) {
    Node* child = root->left;
    Node* child_right = child->right;

    // Perform rotation
    child->right = root;
    root->left = child_right;

    // Update heights
    root->height = 1 + max(getheight(root->left), getheight(root->right));
    child->height = 1 + max(getheight(child->left), getheight(child->right));

    return child;
}


Node* leftRotate(Node* root) {
    Node* child = root->right;
    Node* child_left = child->left;

    child->left = root;
    root->right = child_left;

    root->height = 1 + max(getheight(root->left), getheight(root->right));
    child->height = 1 + max(getheight(child->left), getheight(child->right));

    return child;
}


Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    } else {
        return root; // Duplicate keys are not allowed
    }

    // Update height of the current node
    root->height = 1 + max(getheight(root->left), getheight(root->right));

    // Get balance factor
    int balance = getbalance(root);

    // Left Left Case
    if (balance > 1 && root->left != nullptr && key < root->left->data) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && root->right != nullptr && key > root->right->data) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && root->left != nullptr && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && root->right != nullptr && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root) {
    if(root == nullptr) return;
    
    preorder(root->left);
    cout<<root->data<<" ";
    preorder(root->right);
}

int main() {
    Node *root = NULL;

    //duplicate elements are not allowed
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 50);
    root = insert(root, 70);
    root = insert(root, 100);
    root = insert(root, 95);

    cout<<"Preorder Traversal of the AVL Tree is: ";
    preorder(root);
}