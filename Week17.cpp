#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;

    Node(int val) : value(val), left(NULL), right(NULL), height(1) {}
};

class BalancedTree {
public:
    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateToRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* rotateToLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* addNode(Node* root, int key) {
        if (!root) return new Node(key);

        if (key < root->value)
            root->left = addNode(root->left, key);
        else if (key > root->value)
            root->right = addNode(root->right, key);
        else
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = balanceFactor(root);

        if (balance > 1 && key < root->left->value)
            return rotateToRight(root);

        if (balance < -1 && key > root->right->value)
            return rotateToLeft(root);

        if (balance > 1 && key > root->left->value) {
            root->left = rotateToLeft(root->left);
            return rotateToRight(root);
        }

        if (balance < -1 && key < root->right->value) {
            root->right = rotateToRight(root->right);
            return rotateToLeft(root);
        }

        return root;
    }

    void displayTraversal(Node* root, string order) {
        if (order == "pre") {
            if (root) {
                cout << root->value << " ";
                displayTraversal(root->left, order);
                displayTraversal(root->right, order);
            }
        } else if (order == "in") {
            if (root) {
                displayTraversal(root->left, order);
                cout << root->value << " ";
                displayTraversal(root->right, order);
            }
        } else if (order == "post") {
            if (root) {
                displayTraversal(root->left, order);
                displayTraversal(root->right, order);
                cout << root->value << " ";
            }
        }
    }
};

int main() {
    BalancedTree tree;
    Node* root = NULL;
    int count, data;

    cout << "Enter number of elements: ";
    cin >> count;

    for (int i = 0; i < count; ++i) {
        cout << "Enter element " << (i + 1) << ": ";
        cin >> data;
        root = tree.addNode(root, data);

        cout << "\nPre-order traversal: ";
        tree.displayTraversal(root, "pre");
        cout << "\nIn-order traversal: ";
        tree.displayTraversal(root, "in");
        cout << "\nPost-order traversal: ";
        tree.displayTraversal(root, "post");
        cout << endl;
    }

    return 0;
}
