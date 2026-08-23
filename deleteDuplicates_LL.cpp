#include <iostream>
using namespace std; 

class Node {
public:
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = NULL;
    }
};  

class Linkedlist {
public:
    Node* head;

    Linkedlist() {
        head = NULL;
    } 

    void insertAtHead(int val) {
        Node* new_node = new Node(val);
        new_node->next = head;
        head = new_node;
    } 

    void insertAtTail(int val) {
        Node* new_node = new Node(val);

        if(head == NULL) {
            head = new_node; 
            return;
        } 

        Node* tmp = head;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    } 

    void insertAtPosition(int val, int pos) {
        if (pos < 1) {
            cout << "Invalid position! Must be 1 or greater." << endl;
            return;
        }

        if (pos == 1) {
            insertAtHead(val);
            return;
        }

        Node* tmp = head;
        Node* new_node = new Node(val);
        int current_pos = 1; 

        while(current_pos < pos - 1 && tmp != NULL) { 
            tmp = tmp->next; 
            current_pos++;
        } 

        if (tmp == NULL) {
            cout << "Position out of bounds." << endl;
            return; 
        }

        new_node->next = tmp->next; 
        tmp->next = new_node; 
    }

    void updateAtPosition(int val, int pos) {
        if (pos < 1) return;

        Node* tmp = head; 
        int curr = 1; 

        while(curr < pos && tmp != NULL) {
            tmp = tmp->next;
            curr++;
        }

        if (tmp != NULL) {
            tmp->data = val;
        } else {
            cout << "Position out of bounds." << endl;
        }
    } 

    void deleteAtHead() {
        if (head == NULL) return; 
        Node* tmp = head; 
        head = head->next; 
        delete tmp; 
    } 

    void deleteAtEnd() {
        if (head == NULL) return; 
        if (head->next == NULL) {
            deleteAtHead();
            return;
        }

        Node* second_last = head; 
        while(second_last->next->next != NULL) {
            second_last = second_last->next;
        } 

        Node* tmp = second_last->next;
        second_last->next = NULL;
        delete tmp; 
    }  

    void deleteAtPosition(int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (pos == 1) {
            deleteAtHead();
            return;
        }

        int curr = 1; 
        Node* prev = head;

        while (curr < pos - 1 && prev != NULL && prev->next != NULL) {
            curr++;
            prev = prev->next;
        } 

        if (prev == NULL || prev->next == NULL) {
            cout << "Position out of bounds." << endl;
            return; 
        }

        Node* tmp = prev->next;
        prev->next = prev->next->next;
        delete tmp; 
    } 

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    } 

    void deleteAlternate(){

        Node* curr = head ;

        while( curr!=nullptr && curr->next!=nullptr ) {
            Node* tmp = curr->next ;
            curr->next=curr->next->next ;
            delete tmp ;
            curr=curr->next ;
        }
    } 

    void deleteDuplicates(){
     Node* curr_node = head ; 
     while(curr_node!=nullptr && curr_node->next!=nullptr){
          if(curr_node->data==curr_node->next->data){
               Node* tmp = curr_node->next ;
               curr_node->next = curr_node->next->next ;
               delete tmp ;
               
          } else {
               curr_node=curr_node->next ;
          }
     }
    }
}; 

int main() {
    Linkedlist ll; 

    ll.insertAtHead(1);
    ll.insertAtTail(3);
    
    ll.insertAtPosition(2, 2); 
    
    ll.insertAtTail(4);
    ll.insertAtTail(4);
    ll.insertAtTail(4);
        ll.insertAtTail(7);
    ll.insertAtTail(8); 

    ll.display() ;
    ll.deleteDuplicates();
    ll.display();

    
   

    return 0;
}