#include <iostream>
using namespace std;

struct Document {
    string fileName;
    int fileSize;      // File size (KB)
    int storageDays;   // Storage time (days)

    Document(string n, int s, int t) : fileName(n), fileSize(s), storageDays(t) {}
};

struct Node {
    Document doc;
    Node* nextNode;

    Node(Document d) : doc(d), nextNode(nullptr) {}
};

class Folder {
public:
    Node* start;

    Folder() : start(nullptr) {}

    // Add a document to the list in ascending order by file size
    void addDocument(Document d) {
        Node* newNode = new Node(d);
        if (!start || start->doc.fileSize > d.fileSize) {
            newNode->nextNode = start;
            start = newNode;
        } else {
            Node* current = start;
            while (current->nextNode && current->nextNode->doc.fileSize <= d.fileSize) {
                current = current->nextNode;
            }
            newNode->nextNode = current->nextNode;
            current->nextNode = newNode;
        }
    }

    // Remove the first document in the list
    void removeFirst() {
        if (start) {
            Node* temp = start;
            start = start->nextNode;
            delete temp;
        }
    }

    // Remove the last document in the list
    void removeLast() {
        if (!start) return;
        if (!start->nextNode) {
            delete start;
            start = nullptr;
            return;
        }
        Node* current = start;
        while (current->nextNode->nextNode) {
            current = current->nextNode;
        }
        delete current->nextNode;
        current->nextNode = nullptr;
    }

    // Remove the document after a given node
    void removeAfter(Node* prevNode) {
        if (prevNode && prevNode->nextNode) {
            Node* temp = prevNode->nextNode;
            prevNode->nextNode = temp->nextNode;
            delete temp;
        }
    }

    // Remove documents with the smallest file size and the longest storage time
    void removeMinFiles() {
        if (!start) return;

        int minFileSize = start->doc.fileSize;
        Node* temp = start;

        // Traverse through documents with the smallest file size and longest storage time
        while (temp && temp->doc.fileSize == minFileSize) {
            temp = temp->nextNode;
        }

        // Remove documents with the smallest file size and longest storage time
        while (start && start->doc.fileSize == minFileSize) {
            removeFirst();
        }
    }

    // Display the list of documents in the folder
    void showDocuments() const {
        Node* temp = start;
        while (temp) {
            cout << "File: " << temp->doc.fileName << ", Size: " << temp->doc.fileSize << "KB, Storage Days: " << temp->doc.storageDays << " days\n";
            temp = temp->nextNode;
        }
    }
};

int main() {
    Folder directory;
    
    // Add documents to the folder
    directory.addDocument(Document("FileA", 450, 25));
    directory.addDocument(Document("FileB", 180, 35));
    directory.addDocument(Document("FileC", 180, 15));
    directory.addDocument(Document("FileD", 90, 5));
    directory.addDocument(Document("FileE", 90, 45));
    
    cout << "Initial documents in folder:\n";
    directory.showDocuments();

    // Remove the first document in the list
    cout << "\nRemoving first document:\n";
    directory.removeFirst();
    directory.showDocuments();

    // Remove the last document in the list
    cout << "\nRemoving last document:\n";
    directory.removeLast();
    directory.showDocuments();

    // Remove documents with the smallest file size and the longest storage time
    cout << "\nRemoving documents with minimum size and longest storage time:\n";
    directory.removeMinFiles();
    directory.showDocuments();

    return 0;
}

