#include <iostream>
#include <string>
#include <stack>
using namespace std;

//--------------------------------------------
// STRUCTURE FOR ACCOUNT
//--------------------------------------------
struct Account {
    int accountNumber;
    string name;
    double balance;
};

//--------------------------------------------
// NODE FOR LINKED LIST (MAIN STORAGE)
//--------------------------------------------
struct Node {
    Account data;
    Node* next;
};

//--------------------------------------------
// BST NODE
//--------------------------------------------
struct BSTNode {
    Account acc;
    BSTNode* left;
    BSTNode* right;
};

//--------------------------------------------
// GLOBALS
//--------------------------------------------
Node* head = NULL;          // Linked list head
BSTNode* root = NULL;       // BST root
stack<string> history;      // Transaction history (Stack)

//--------------------------------------------
// INSERT ACCOUNT INTO LINKED LIST
//--------------------------------------------
void addAccount() {
    Node* newNode = new Node;
    cout << "\nEnter Account Number: ";
    cin >> newNode->data.accountNumber;
    cout << "Enter Name: ";
    cin >> newNode->data.name;
    cout << "Enter Initial Balance: ";
    cin >> newNode->data.balance;

    newNode->next = head;
    head = newNode;

    history.push("Account Created: " + newNode->data.name);
    cout << "\nAccount Added Successfully!\n";
}

//--------------------------------------------
// LINEAR SEARCH
//--------------------------------------------
Node* linearSearch(int accNum) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.accountNumber == accNum)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

//--------------------------------------------
// DEPOSIT
//--------------------------------------------
void deposit() {
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    Node* customer = linearSearch(acc);
    if (customer == NULL) {
        cout << "Account Not Found!\n";
        return;
    }

    double amt;
    cout << "Enter Amount: ";
    cin >> amt;

    customer->data.balance += amt;
    history.push("Deposited " + to_string(amt) + " to " + customer->data.name);
    cout << "Deposit Successful!\n";
}

//--------------------------------------------
// WITHDRAW
//--------------------------------------------
void withdraw() {
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    Node* customer = linearSearch(acc);
    if (!customer) {
        cout << "Account Not Found!\n";
        return;
    }

    double amt;
    cout << "Enter Amount: ";
    cin >> amt;

    if (customer->data.balance < amt) {
        cout << "Insufficient Balance!\n";
        return;
    }

    customer->data.balance -= amt;
    history.push("Withdraw " + to_string(amt) + " from " + customer->data.name);
    cout << "Withdraw Successful!\n";
}

//--------------------------------------------
// DISPLAY TRANSACTION HISTORY (STACK)
//--------------------------------------------
void showHistory() {
    stack<string> temp = history;

    cout << "\n----- Transaction History -----\n";
    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}

//--------------------------------------------
// BST INSERT (RECURSIVE)
//--------------------------------------------
BSTNode* insertBST(BSTNode* root, Account acc) {
    if (root == NULL) {
        BSTNode* newNode = new BSTNode;
        newNode->acc = acc;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (acc.accountNumber < root->acc.accountNumber)
        root->left = insertBST(root->left, acc);
    else
        root->right = insertBST(root->right, acc);

    return root;
}

//--------------------------------------------
// BUILD BST FROM LINKED LIST
//--------------------------------------------
void buildBST() {
    root = NULL;
    Node* temp = head;
    while (temp != NULL) {
        root = insertBST(root, temp->data);
        temp = temp->next;
    }
    cout << "\nBST Built Successfully!\n";
}

//--------------------------------------------
// INORDER TRAVERSAL (RECURSION)
//--------------------------------------------
void inorder(BSTNode* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->acc.accountNumber << " - " << root->acc.name << endl;
    inorder(root->right);
}

//--------------------------------------------
// PRINT COMPLEXITY ANALYSIS
//--------------------------------------------
void showComplexity() {
    cout << "\n----- COMPLEXITY ANALYSIS -----\n";
    cout << "Linear Search     ? O(n)\n";
    cout << "Bubble Sort       ? O(n^2)\n";
    cout << "Quick Sort        ? O(n log n)\n";
    cout << "BST Search        ? Best: O(log n), Worst: O(n)\n";
}

//--------------------------------------------
// MAIN MENU
//--------------------------------------------
int main() {
    int choice;

    do {
        cout << "\n=========== BANKING SYSTEM ===========\n";
        cout << "1. Add Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Build BST\n";
        cout << "5. Display BST (Inorder)\n";
        cout << "6. Transaction History\n";
        cout << "7. Complexity Analysis\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addAccount(); break;
        case 2: deposit(); break;
        case 3: withdraw(); break;
        case 4: buildBST(); break;
        case 5: inorder(root); break;
        case 6: showHistory(); break;
        case 7: showComplexity(); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid Choice!\n";
        }
    } while (choice != 0);

    return 0;
}
