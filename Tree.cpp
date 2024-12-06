#include <iostream>
#include <stack>
#include <string>

using namespace std;

// C?u tr�c c?a m?t n�t trong c�y
struct Node {
    char data;
    Node* left;
    Node* right;
};

// H�m t?o m?t n�t m?i
Node* newNode(char data) {
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// H�m ki?m tra �? �u ti�n c?a to�n t?
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// H�m chuy?n �?i bi?u th?c trung t? sang h?u t?
string infixToPostfix(string s) {
    stack<char> ops;
    string result;

    for (char c : s) {
        if (isalnum(c)) {
            result += c;
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                result += ops.top();
                ops.pop();
            }
            ops.pop();
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                result += ops.top();
                ops.pop();
            }
            ops.push(c);
        }
    }

    while (!ops.empty()) {
        result += ops.top();
        ops.pop();
    }

    return result;
}

// H�m x�y d?ng c�y bi?u th?c t? bi?u th?c h?u t?
Node* constructTree(string postfix) {
    stack<Node*> st;
    for (char c : postfix) {
        if (isalnum(c)) {
            st.push(newNode(c));
        } else {
            Node* t = newNode(c);
            t->right = st.top();
            st.pop();
            t->left = st.top();
            st.pop();
            st.push(t);
        }
    }

    return st.top();
}

// C�c h�m duy?t c�y
void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

int main() {
    string s = "a+b*(c-d)";
    string postfix = infixToPostfix(s);
    cout << "Postfix: " << postfix << endl;

    Node* root = constructTree(postfix);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    return 0;
}
