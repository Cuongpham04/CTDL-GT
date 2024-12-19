#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string name;
    int pages;
    vector<Node*> subNodes;

    Node(const string& name, int pages = 0) : name(name), pages(pages) {}

    void appendChild(Node* child) {
        subNodes.push_back(child);
    }

    ~Node() {
        for (auto subNode : subNodes) {
            delete subNode;
        }
    }
};

class Tree {
private:
    Node* rootNode;

    bool deleteNode(Node* current, const string& targetName, int& reducedPages) {
        for (auto it = current->subNodes.begin(); it != current->subNodes.end(); ++it) {
            if ((*it)->name == targetName) {
                reducedPages = (*it)->pages;
                delete *it;
                current->subNodes.erase(it);
                return true;
            }
            if (deleteNode(*it, targetName, reducedPages)) {
                current->pages -= reducedPages;
                return true;
            }
        }
        return false;
    }

    void displayTree(Node* current, int depth) const {
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << current->name << " (" << current->pages << " pages)" << endl;
        for (auto subNode : current->subNodes) {
            displayTree(subNode, depth + 1);
        }
    }

public:
    Tree() : rootNode(nullptr) {}

    ~Tree() {
        delete rootNode;
    }

    void assignRoot(Node* root) {
        rootNode = root;
    }

    int countMainNodes() const {
        return rootNode ? rootNode->subNodes.size() : 0;
    }

    Node* locateLargestNode() const {
        if (!rootNode || rootNode->subNodes.empty()) return nullptr;
        return *max_element(rootNode->subNodes.begin(), rootNode->subNodes.end(), [](Node* a, Node* b) {
            return a->pages < b->pages;
        });
    }

    bool locateAndRemove(const string& targetName) {
        if (!rootNode) return false;
        int reducedPages = 0;
        return deleteNode(rootNode, targetName, reducedPages);
    }

    void displayTree() const {
        if (rootNode) displayTree(rootNode, 0);
    }
};

int main() {
    Tree bookTree;
    Node* root = new Node("Main Title", 0);
    bookTree.assignRoot(root);

    // Add main sections
    Node* sec1 = new Node("Part 1", 50);
    Node* sec2 = new Node("Part 2", 40);
    Node* sec3 = new Node("Part 3", 60);

    root->appendChild(sec1);
    root->appendChild(sec2);
    root->appendChild(sec3);

    // Add subsections
    Node* subsec1 = new Node("Subpart 1.1", 20);
    Node* subsec2 = new Node("Subpart 1.2", 30);
    sec1->appendChild(subsec1);
    sec1->appendChild(subsec2);

    // Perform operations
    cout << "Total main sections: " << bookTree.countMainNodes() << endl;
    Node* largest = bookTree.locateLargestNode();
    if (largest) {
        cout << "Largest section: " << largest->name << " (" << largest->pages << " pages)" << endl;
    }

    cout << "\nStructure before removal:" << endl;
    bookTree.displayTree();

    bookTree.locateAndRemove("Subpart 1.1");

    cout << "\nStructure after removal:" << endl;
    bookTree.displayTree();

    return 0;
}
