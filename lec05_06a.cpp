#include <iostream>
#include <conio.h>
using namespace std;

template <typename T>
class Node
{
public:
    T value;
    Node* next;

    Node(const T& value) : value(value), next(nullptr)
    {}

    void print() const
    {
        cout << value;
    }
};

template <typename T>
class List
{
public:
    Node<T>* head;
    List() : head{ nullptr }
    {}
    void add(const T& value)
    {
        Node<T>* nodePtr = new Node<T>(value);
        nodePtr->next = head;
        head = nodePtr;
    }

    void remove()
    {
        if (head != nullptr)
        {
            Node<T>* nodePtr = head;
            head = head->next;
            delete nodePtr;
        }
    }
    Node<T>* find(const T& value) const
    {
        for (Node<T>* nodePtr = head;
            nodePtr != nullptr;
            nodePtr = nodePtr->next)
        {
            if (nodePtr->value == value)
            {
                return nodePtr;
            }
        }
        return nullptr;
    }
    Node<T>* findPrev(const T& value) const
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        
        for (Node<T>* nodePtr = head->next, *prevPtr = head;
            nodePtr != nullptr;
            nodePtr = nodePtr->next, prevPtr = prevPtr->next)
        {
            if (nodePtr->value == value)
            {
                return prevPtr;
            }
        }
        return nullptr;
    }
    Node<T>* addAfter(const T& value, Node<T>* afterPtr)
    {
        if (afterPtr == nullptr)
        {
            return nullptr;
        }
        Node<T>* nodePtr = new Node<T>(value);
        nodePtr->next = afterPtr->next;
        afterPtr->next = nodePtr;
        return afterPtr->next;
    }

    Node<T>* removeAfter(Node<T>* afterPtr)
    {
        if (afterPtr != nullptr && afterPtr->next != nullptr)
        {
            Node<T>* nodePtr = afterPtr->next;
            afterPtr->next = afterPtr->next->next;
            delete nodePtr;
        }
        return afterPtr;
    }
    void clear()
    {
        while (head != nullptr)
        {
            remove();
        }
    }
    void doForEach(void (*func)(Node<T>* nodePtr))
    {
        for (Node<T>* nodePtr = head; 
            nodePtr != nullptr; 
            nodePtr = nodePtr->next)
        {
            func(nodePtr);
        }
    }
    static void printNode(Node<T>* nodePtr)
    {
        nodePtr->print();
        cout << " > ";
    }

    void print()
    {
        cout << " > ";
        doForEach(printNode);
        cout << endl;
    }
};

int main()
{
    cout << "Linked List" << endl << endl;

    List<string> list;
    list.add("one");
    list.add("two");
    list.add("three");
    list.print();
    cout << endl;

    list.remove();
    list.remove();
    list.print();
    cout << endl;

    list.remove();
    list.remove();
    list.print();
    cout << endl;

    list.add("one");
    list.add("two");
    list.add("three");
    list.print();
    cout << endl;

    Node<string>* nodePtr = list.find("two");
    if (nodePtr != nullptr)
    {
        nodePtr->value = "two + two";
    }
    list.print();
    cout << endl;
    nodePtr = list.find("two");
    if (nodePtr != nullptr)
    {
        nodePtr->value = "new value";
    }
    list.print();
    cout << endl;

    nodePtr = list.find("three");
    list.addAfter("four", nodePtr);
    nodePtr = list.findPrev("two + two");
    list.addAfter("two", nodePtr);
    list.print();
    cout << endl;

    nodePtr = list.findPrev("two + two");
    list.removeAfter(nodePtr);
    nodePtr = list.find("three");
    list.removeAfter(nodePtr);
    list.print();
    cout << endl;

    list.clear();
    list.print();
    cout << endl;

    list.add("ten");
    list.addAfter("twelve", (list.addAfter("eleven", list.head)));
    list.print();
    cout << endl;

    cout << endl;
    return 0;
}