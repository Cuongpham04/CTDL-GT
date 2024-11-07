#include <iostream>
using namespace std;

// L?p Term �? l�u th�ng tin c?a t?ng h?ng t? trong �a th?c
class Term {
public:
    int coefficient;   // H? s? c?a h?ng t?
    int exponent;      // B?c c?a h?ng t?
    Term* nextTerm;    // Con tr? �?n h?ng t? ti?p theo
    
    Term(int coef, int exp) : coefficient(coef), exponent(exp), nextTerm(nullptr) {}
};

// L?p PolynomialList �? bi?u di?n �a th?c d�?i d?ng danh s�ch li�n k?t
class PolynomialList {
public:
    Term* head;  // Con tr? �?n �?u danh s�ch li�n k?t
    
    PolynomialList() : head(nullptr) {}

    // H�m �? th�m m?t h?ng t? m?i v�o �a th?c
    void addElement(int coef, int exp) {
        if (coef == 0) return; // B? qua c�c h? s? 0 �? gi?m b? nh?
        Term* newTerm = new Term(coef, exp);

        if (!head || head->exponent < exp) {
            newTerm->nextTerm = head;
            head = newTerm;
        } else {
            Term* current = head;
            while (current->nextTerm && current->nextTerm->exponent > exp) {
                current = current->nextTerm;
            }
            if (current->exponent == exp) {
                current->coefficient += coef;  // C?ng h? s? n?u c�ng b?c
                delete newTerm;                // X�a newTerm v? kh�ng d�ng
            } else if (current->nextTerm && current->nextTerm->exponent == exp) {
                current->nextTerm->coefficient += coef;
                delete newTerm;
            } else {
                newTerm->nextTerm = current->nextTerm;
                current->nextTerm = newTerm;
            }
        }
    }

    // H�m �? hi?n th? �a th?c
    void displayPoly() const {
        Term* current = head;
        while (current) {
            if (current->coefficient) {
                if (current != head && current->coefficient > 0) cout << " + ";
                if (current->exponent == 0) cout << current->coefficient;
                else if (current->exponent == 1) cout << current->coefficient << ".x";
                else cout << current->coefficient << ".x^" << current->exponent;
            }
            current = current->nextTerm;
        }
        cout << ";" << endl;
    }

    // H�m �? c?ng hai �a th?c v� tr? v? k?t qu? l� m?t �a th?c m?i
    PolynomialList sumPolynomials(const PolynomialList& otherPoly) const {
        PolynomialList result;
        Term* ptr1 = head;
        Term* ptr2 = otherPoly.head;
        
        while (ptr1 || ptr2) {
            if (ptr1 && (!ptr2 || ptr1->exponent > ptr2->exponent)) {
                result.addElement(ptr1->coefficient, ptr1->exponent);
                // Debug: In th�ng tin c?a ph?n t?
                cout << "f(x) Term: coef = " << ptr1->coefficient 
                     << ", exp = " << ptr1->exponent << ", address = " << ptr1 << endl;
                ptr1 = ptr1->nextTerm;
            } else if (ptr2 && (!ptr1 || ptr2->exponent > ptr1->exponent)) {
                result.addElement(ptr2->coefficient, ptr2->exponent);
                // Debug: In th�ng tin c?a ph?n t?
                cout << "g(x) Term: coef = " << ptr2->coefficient 
                     << ", exp = " << ptr2->exponent << ", address = " << ptr2 << endl;
                ptr2 = ptr2->nextTerm;
            } else {  // ptr1->exponent == ptr2->exponent
                result.addElement(ptr1->coefficient + ptr2->coefficient, ptr1->exponent);
                // Debug: In th�ng tin c?a ph?n t?
                cout << "Combined Term: coef = " << ptr1->coefficient + ptr2->coefficient
                     << ", exp = " << ptr1->exponent << ", f(x) address = " << ptr1 
                     << ", g(x) address = " << ptr2 << endl;
                ptr1 = ptr1->nextTerm;
                ptr2 = ptr2->nextTerm;
            }
        }
        return result;
    }

    // Gi?i ph�ng b? nh? khi �a th?c kh�ng c?n s? d?ng
    ~PolynomialList() {
        while (head) {
            Term* temp = head;
            head = head->nextTerm;
            delete temp;
        }
    }
};

int main() {
    // T?o v� nh?p hai �a th?c f(x) v� g(x)
    PolynomialList polyF;
    polyF.addElement(5, 10);
    polyF.addElement(1, 0);

    PolynomialList polyG;
    polyG.addElement(10, 15);
    polyG.addElement(-2, 7);
    polyG.addElement(3, 2);
    polyG.addElement(-7, 0);

    // In ra f(x) v� g(x)
    cout << "f(x) = ";
    polyF.displayPoly();
    cout << "g(x) = ";
    polyG.displayPoly();

    // T�nh t?ng h(x) = f(x) + g(x) v� in ra k?t qu?
    PolynomialList polyH = polyF.sumPolynomials(polyG);
    cout << "h(x) = f(x) + g(x) = ";
    polyH.displayPoly();

    return 0;
}

