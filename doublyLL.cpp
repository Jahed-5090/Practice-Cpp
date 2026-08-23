#include <iostream>
using namespace std;

class Node
{
public:
  int val;
  Node *prev;
  Node *next;

  Node(int data)
  {
    val = data;
    prev = nullptr;
    next = nullptr;
  }
};

class DoublyLinkedlist
{
public:
  Node *head;

  DoublyLinkedlist()
  {
    head = nullptr;
  }

  ~DoublyLinkedlist()
  {
    Node *curr = head;
    while (curr != nullptr)
    {
      Node *next_node = curr->next;
      delete curr;
      curr = next_node;
    }
  }

  void insertAtStart(int val)
  {
    Node *new_node = new Node(val);

    if (head == nullptr)
    {
      head = new_node;
      return;
    }

    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }

  void insertAtEnd(int val)
  {
    Node *new_node = new Node(val);

    if (head == nullptr)
    {
      head = new_node;
      return;
    }

    // Traverse to the last node
    Node *tmp = head;
    while (tmp->next != nullptr)
    {
      tmp = tmp->next;
    }

    tmp->next = new_node;
    new_node->prev = tmp;
  }

  void insertAtPosition(int val, int pos)
  {
    if (pos <= 1)
    {
      this->insertAtStart(val);
      return;
    }

    int count = 1;
    Node *tmp = head;

    // Traverse to the node JUST BEFORE the insertion point
    while (count < (pos - 1) && tmp != nullptr)
    {
      tmp = tmp->next;
      count++;
    }

    // Edge case: Position is out of bounds
    if (tmp == nullptr)
      return;

    Node *new_node = new Node(val);

    new_node->next = tmp->next;
    new_node->prev = tmp;

    // Safety check: if inserting at the very end, tmp->next is null
    if (tmp->next != nullptr)
    {
      tmp->next->prev = new_node;
    }

    tmp->next = new_node;
  }

  void deleteAtFirst()
  {
    if (head == nullptr)
    {
      return;
    }

    Node *tmp = head;
    head = head->next;

    // Safety check: if the list had only 1 node, head is now null
    if (head != nullptr)
    {
      head->prev = nullptr;
    }

    delete tmp;
  }

  void deleteAtLast()
  {
    if (head == nullptr)
      return;

    // If there is only one node
    if (head->next == nullptr)
    {
      delete head;
      head = nullptr;
      return;
    }

    // Traverse to the last node
    Node *tmp = head;
    while (tmp->next != nullptr)
    {
      tmp = tmp->next;
    }

    tmp->prev->next = nullptr;
    delete tmp;
  }

  void deleteAfterValue(int val)
  {
    Node *tmp = head;

    // Find the node with the value
    while (tmp != nullptr && tmp->val != val)
    {
      tmp = tmp->next;
    }

    // If value not found, or it's the last node (nothing to delete after)
    if (tmp == nullptr || tmp->next == nullptr)
      return;

    Node *deln = tmp->next; // The node to delete

    // Link the current node to the node AFTER the deleted one
    tmp->next = deln->next;

    // If the node we are deleting wasn't the last node in the list
    if (deln->next != nullptr)
    {
      deln->next->prev = tmp;
    }

    delete deln;
  }

  void deletebeforeValue(int data)
  {
    Node *tmp = head;

    // Find the node with the value
    while (tmp != nullptr && tmp->val != data)
    {
      tmp = tmp->next;
    }

    // If value not found, or it's the head node (nothing to delete before)
    if (tmp == nullptr || tmp->prev == nullptr)
      return;

    Node *deln = tmp->prev; // The node to delete

    // If we are deleting the head node
    if (deln->prev == nullptr)
    {
      head = tmp;
      tmp->prev = nullptr;
    }
    else
    {
      // Standard deletion in the middle
      deln->prev->next = tmp;
      tmp->prev = deln->prev;
    }

    delete deln;
  }

  void display()
  {
    Node *tmp = head;
    while (tmp != nullptr)
    {
      cout << tmp->val << "->";
      tmp = tmp->next;
    }
    cout << "NULL" << endl;
  }

  void displayReverse()
  {
    if (head == nullptr)
      return;

    // 1. Traverse to the very end
    Node *tmp = head;
    while (tmp->next != nullptr)
    {
      tmp = tmp->next;
    }

    // 2. Traverse backwards using the prev pointer
    while (tmp != nullptr)
    {
      cout << tmp->val << "<-";
      tmp = tmp->prev;
    }
    cout << "HEAD" << endl;
  }
};

int main()
{
  DoublyLinkedlist doubly;

  doubly.insertAtEnd(1);
  doubly.insertAtEnd(2);
  doubly.insertAtEnd(3);
  doubly.insertAtEnd(4);
  doubly.insertAtEnd(5);
  doubly.insertAtEnd(6);
  doubly.insertAtEnd(7);
  doubly.insertAtEnd(8);
  doubly.insertAtEnd(9);
  doubly.insertAtEnd(10);

  cout << "Original List: ";
  doubly.display();

  cout << "\nAfter deleteAtFirst: ";
  doubly.deleteAtFirst();
  doubly.display();

  cout << "\nAfter deleteAtLast: ";
  doubly.deleteAtLast();
  doubly.display();

  cout << "\nAfter deleteAfterValue(5) [Deletes 6]: ";
  doubly.deleteAfterValue(5);
  doubly.display();

  cout << "\nAfter deletebeforeValue(3) [Deletes 2]: ";
  doubly.deletebeforeValue(3);
  doubly.display();

  cout << "\nAfter deletebeforeValue(4) [Deletes 3]: ";
  doubly.deletebeforeValue(4);
  doubly.display();

  cout << "\nReverse Display: ";
  doubly.displayReverse();

  return 0;
}