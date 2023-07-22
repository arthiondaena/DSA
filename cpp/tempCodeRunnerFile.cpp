#include <iostream>
#include <queue>
using namespace std;

class AVLTreeRecursiveOptimized {
private:
    struct Node {
        int value;
        int height;
        int bf;
        Node* left;
        Node* right;

        Node(int val) : value(val), height(0), bf(0), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    int nodeCount = 0;

    int getHeight(Node* node) {
        return (node == nullptr) ? -1 : node->height;
    }

    int getBalanceFactor(Node* node) {
        return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
    }

    Node* leftRotation(Node* node) {
        Node* newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));
        return newParent;
    }

    Node* rightRotation(Node* node) {
        Node* newParent = node->left;
        node->left = newParent->right;
        newParent->right = node;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));
        return newParent;
    }

    Node* balance(Node* node) {
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor == -2) {
            if (getBalanceFactor(node->left) <= 0)
                return rightRotation(node);
            else
                return leftRotation(node->left);
        } else if (balanceFactor == 2) {
            if (getBalanceFactor(node->right) >= 0)
                return leftRotation(node);
            else
                return rightRotation(node->right);
        }
        return node;
    }

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            nodeCount++;
            return new Node(val);
        }

        if (val < node->value)
            node->left = insert(node->left, val);
        else if (val > node->value)
            node->right = insert(node->right, val);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node = balance(node);
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (node == nullptr) return nullptr;

        if (val < node->value)
            node->left = remove(node->left, val);
        else if (val > node->value)
            node->right = remove(node->right, val);
        else {
            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                nodeCount--;
                return rightChild;
            } else if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                nodeCount--;
                return leftChild;
            } else {
                Node* minRight = findMin(node->right);
                node->value = minRight->value;
                node->right = remove(node->right, minRight->value);
            }
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node = balance(node);
        return node;
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    AVLTreeRecursiveOptimized() {}
    ~AVLTreeRecursiveOptimized() {
        deleteTree(root);
    }

    int height() {
        return getHeight(root);
    }

    int size() {
        return nodeCount;
    }

    bool isEmpty() {
        return nodeCount == 0;
    }

    bool contains(int value) {
        Node* node = root;
        while (node != nullptr) {
            if (value < node->value)
                node = node->left;
            else if (value > node->value)
                node = node->right;
            else
                return true;
        }
        return false;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    void levelOrder() {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    void rootele() {
        if (root != nullptr)
            cout << root->value;
        else
            cout << "The tree is empty.";
    }
};

int main() {
    AVLTreeRecursiveOptimized tree;
    for (int i = 1; i < 10; i++) {
        tree.insert(i);
    }
    tree.levelOrder();
    cout << "\n";

    tree.remove(5);
    tree.levelOrder();
    cout << "\n";

    cout << "Height: " << tree.height() << "\n";
    cout << "Size: " << tree.size() << "\n";
    cout << "Contains 3? " << boolalpha << tree.contains(3) << "\n";
    cout << "Contains 5? " << boolalpha << tree.contains(5) << "\n";
    cout << "Is Empty? " << boolalpha << tree.isEmpty() << "\n";

    tree.rootele();

    return 0;
}
