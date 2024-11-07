#include <iostream>
using namespace std;


class Term {
public:
    int coefficient;  
    int exponent;      
    Term* nextTerm;    
    
    Term(int coef, int exp) : coefficient(coef), exponent(exp), nextTerm(nullptr) {}
};


class PolynomialList {
public:
    Term* head;  
    
    PolynomialList() : head(nullptr) {}

    
    void addElement(int coef, int exp) {
        if (coef == 0) return; 
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
                current->coefficient += coef;  
                delete newTerm;                
            } else if (current->nextTerm && current->nextTerm->exponent == exp) {
                current->nextTerm->coefficient += coef;
                delete newTerm;
            } else {
                newTerm->nextTerm = current->nextTerm;
                current->nextTerm = newTerm;
            }
        }
    }

    
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

    
    PolynomialList sumPolynomials(const PolynomialList& otherPoly) const {
        PolynomialList result;
        Term* ptr1 = head;
        Term* ptr2 = otherPoly.head;
        
        while (ptr1 || ptr2) {
            if (ptr1 && (!ptr2 || ptr1->exponent > ptr2->exponent)) {
                result.addElement(ptr1->coefficient, ptr1->exponent);
                
                cout << "f(x) Term: coef = " << ptr1->coefficient 
                     << ", exp = " << ptr1->exponent << ", address = " << ptr1 << endl;
                ptr1 = ptr1->nextTerm;
            } else if (ptr2 && (!ptr1 || ptr2->exponent > ptr1->exponent)) {
                result.addElement(ptr2->coefficient, ptr2->exponent);
                
                cout << "g(x) Term: coef = " << ptr2->coefficient 
                     << ", exp = " << ptr2->exponent << ", address = " << ptr2 << endl;
                ptr2 = ptr2->nextTerm;
            } else {  // ptr1->exponent == ptr2->exponent
                result.addElement(ptr1->coefficient + ptr2->coefficient, ptr1->exponent);
        
                cout << "Combined Term: coef = " << ptr1->coefficient + ptr2->coefficient
                     << ", exp = " << ptr1->exponent << ", f(x) address = " << ptr1 
                     << ", g(x) address = " << ptr2 << endl;
                ptr1 = ptr1->nextTerm;
                ptr2 = ptr2->nextTerm;
            }
        }
        return result;
    }

    
    ~PolynomialList() {
        while (head) {
            Term* temp = head;
            head = head->nextTerm;
            delete temp;
        }
    }
};

int main() {
    
    PolynomialList polyF;
    polyF.addElement(5, 10);
    polyF.addElement(1, 0);

    PolynomialList polyG;
    polyG.addElement(10, 15);
    polyG.addElement(-2, 7);
    polyG.addElement(3, 2);
    polyG.addElement(-7, 0);

    
    cout << "f(x) = ";
    polyF.displayPoly();
    cout << "g(x) = ";
    polyG.displayPoly();

    
    PolynomialList polyH = polyF.sumPolynomials(polyG);
    cout << "h(x) = f(x) + g(x) = ";
    polyH.displayPoly();

    return 0;
}

