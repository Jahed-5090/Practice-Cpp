#include <iostream>
#include <stack>

using namespace std;

class QueueUsingStacks {
private:
    stack<int> inputStack;  // Used for enqueuing
    stack<int> outputStack; // Used for dequeuing

    // Helper function to transfer elements when outputStack is empty
    void transferIfNeeded() {
        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
    }

public:
    // Insert an element into the queue
    void enqueue(int x) {
        inputStack.push(x);
    }

    // Remove the front element of the queue and return it
    int dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue Underflow");
        }
        
        transferIfNeeded(); // Ensure outputStack has the FIFO elements
        
        int frontElement = outputStack.top();
        outputStack.pop();
        return frontElement;
    }

    // Get the front element without removing it
    int peek() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        
        transferIfNeeded();
        return outputStack.top();
    }

    // Check if the queue is empty
    bool isEmpty() {
        return inputStack.empty() && outputStack.empty();
    }
};