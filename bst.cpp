//
//  main.cpp
//  Trees
//
//  Created by Jett Sturges on 12/3/20.
//

#include <iostream>
#include <vector>

using namespace std;

// Make Node class

class Node {

private:
    
    int data = 0;
    Node* lc = nullptr;
    Node* rc = nullptr;
    
public:
    
    Node() {}
    
    Node(int c) {
        data = c;
        lc = nullptr;
        rc = nullptr;
    }
    
    int getData()
    { return data; }
    
    Node* getLC()
    { return this->lc; }
    
    Node* getRC()
    { return this->rc; }
    
    void setData(int x)
    { data = x; }
    
    void setLC(Node* ptr)
    { this->lc = ptr; }
    
    void setRC(Node* ptr)
    { this->rc = ptr; }
    
};

// Make Stack class

class Stack {

private:
    
public:
    
    vector<Node*> s;
    
    bool empty()
    { return s.empty(); }
    
    void add(Node* node)
    { s.push_back(node); }
    
    void remove_top()
    { s.pop_back(); }
    
    Node* get_top()
    { return s.back(); }
    
};

// Function prototypes

void postOrder(Node*);
Node* findMin(Node*);
Node* order66(int, Node*);

// Global variables

Node* head = new Node;
Stack* stack = new Stack;

int main() {
    
    int input, number, key;
    int i = 0;
    
    // While reading in input, create binary search tree
    
    while (cin >> input) {
        if (i == 0) {
            head->setData(input);
            i+=1;
        }
        else if (i == 1) {
            Node* temp = head;
            Node* newNode = new Node(input);
            bool spotFound = false;
            while (!spotFound) {
                if (newNode->getData() < temp->getData()) {
                    if (temp->getLC() != nullptr) {
                        temp = temp->getLC();
                    }
                    else {
                        temp->setLC(newNode);
                        spotFound = true;
                    }
                }
                else if (newNode->getData() > temp->getData()) {
                    if (temp->getRC() != nullptr) {
                        temp = temp->getRC();
                    }
                    else {
                        temp->setRC(newNode);
                        spotFound = true;
                    }
                }
            }
        }
    }
    
    cin.clear();
    
    cin.ignore(2, '\n');
    
    // Read in number and key
    
    cin >> number >> key;
    
    switch(number) {
            
        // if number is 1, we perform search
            
        case 1: {
            Node* temp = head;
            bool found = false;
            while (temp && found == false) {
                // if key is found, we print out the postorder
                if (temp->getData() == key) {
                    found = true;
                    postOrder(head);
                }
                else if (key < temp->getData()) {
                    // if we go left and it's null, the key is not found and we print -1
                    if (temp->getLC() == nullptr) {
                        cout << -1;
                        found = true;
                    }
                    // if key is less than data, we go left
                    else {
                        temp = temp->getLC();
                    }
                }
                else {
                    // if we go right and it's null, the key is not found and we print -1
                    if (temp->getRC() == nullptr) {
                        cout << -1;
                        found = true;
                    }
                    else {
                        // if key is greater than data, we go right
                        temp = temp->getRC();
                    }
                }
            }
            break;
        }
            
        // if number is 2, we perform insert
            
        case 2: {
            
            Node* temp = head;
            Node* newNode = new Node(key);
            bool found = false;
            while (temp && found == false) {
                
                // if key is already in the tree, print -1
                if (key == temp->getData()) {
                    cout << -1;
                    found = true;
                }
                
                // if key is less than data, go left. If left is null, insert the new node and print out the postorder. Else, go to the next left child.
                
                else if (key < temp->getData()) {
                    if (temp->getLC() == nullptr) {
                        temp->setLC(newNode);
                        postOrder(head);
                        found = true;
                    }
                    else {
                        temp = temp->getLC();
                    }
                }
                
                // if key is greater than data, go right. If right is null, insert the new node and print out the postorder. Else, go to the next right child.
                
                else if (key > temp->getData()) {
                    if (temp->getRC() == nullptr) {
                        temp->setRC(newNode);
                        postOrder(head);
                        found = true;
                    }
                    else {
                        temp = temp->getRC();
                    }
                }
            }
            
            break;
        }
            
        // if number is 3, we perform delete
            
          case 3: {
            Node* node = head;
            while (key != node->getData()) {
                
                // if key we want to delete is less than the data of the current node in our traversal, look at the left child. If the left child is empty, there is no key to be deleted, so we print out -1. Otherwise, we go left.
                if (key < node->getData()) {
                    if (node->getLC() == nullptr) {
                        cout << -1;
                        break;
                    }
                    else {
                        node = node->getLC();
                    }
                }
                
                // if key we want to delete is greater than the data of the current node in our traversal, look at the right child. If the right child is empty, there is no key to be deleted, so we print out -1. Otherwise, we go right.

                else {
                    if (node->getRC() == nullptr) {
                        cout << -1;
                        break;
                    }
                    else {
                        node = node->getRC();
                    }
                }
            }
              
            // if we find the key we want to delete in the tree, we invoke order 66 to delete the node. Then, we print out the postorder traversal.
              
            if (key == node->getData()) {
                order66(key, head);
                postOrder(head);
            }
            break;
          }
            
            
    }
    
    return 0;
}

// Function to print out the postorder traversal

void postOrder(Node* node) {
    if (node == NULL) {
        return;
    }
    
    // Create 2 stacks

    Stack stack1, stack2;
    
    // Push root node to the first stack

    stack1.add(node);
    
    // create temp node

    Node* node1;
    
    // while stack 1 is not empty, take the last element of the vector, assign that to node1. Then, pop the last element of the vector, and then add node1 to stack 2.

    while(!stack1.empty()) {
        node1 = stack1.get_top();
        stack1.remove_top();
        stack2.add(node1);
        
        // if node1 has a left child, add it to stack1

        if (node1->getLC()) {
            stack1.add(node1->getLC());
        }
        
        // if node1 has a right child, add it to stack1, on top of the last added node.
        
        if (node1->getRC()) {
            stack1.add(node1->getRC());
        }
    }
    
    // start from the top and print the values out all the way down theh stack2 vector.
    
    while (!stack2.empty()) {
        node1 = stack2.get_top();
        stack2.remove_top();
        cout << node1->getData() << " ";
    }
}

// Function to find the minimum node of a right subtree.

Node* findMin(Node* node) {
    if (node->getLC() == nullptr) {
        return node;
    }
    else {
        return findMin(node->getLC());
    }
}

// Function to delete a node from a tree

Node* order66(int key, Node* node) {
    if (node == NULL) {
        return node;
    }
    
    // if key is less than the data of the current node, go left and perform recursion
    
    if (key < node->getData()) {
        node->setLC(order66(key, node->getLC()));
    }
    
    // if key is greater than the data of the current node, go right and perform recursion
    
    else if (key > node->getData()) {
        node->setRC(order66(key, node->getRC()));
    }
    
    // if key equals the data of the current node, then we check if the node has 0 or 1 child first
    
    else {
        if (node->getLC() == nullptr) {
            Node* temp = node->getRC();
            return temp;
        }
        
        else if (node->getRC() == nullptr) {
            Node* temp = node->getLC();
            return temp;
        }
        
        // if the node we want to delete has 2 children, we first find the minimum value node in the right subtree
        
        Node* temp = findMin(node->getRC());
        
        // then, we replace the delted node's data with the data from the node with the smallest value of the right subtree
        
        node->setData(temp->getData());
        
        // delete the successor node we just swapped the deleted node with
        
        node->setRC(order66(temp->getData(), node->getRC()));
    }
    return node;
}
