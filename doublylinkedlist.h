/**
* @file doublylinkedlist.h
*
* @brief
*    Template for doubly linked list class.
*
* @author Judy Challinger and Troy Jones
* @date 1/1/16
*/

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T* data);
    bool empty() const { return (head == nullptr); }
    T* remove();
    T* first();
    T* next();

private:
    class Node {
        public:
            Node();
            Node(T* data);
            Node* next;
            Node* prev;
            T* data;
    };
    Node* head;
    Node* tail;
    Node* current;
};


/****************
** Definitions **
****************/

/**
* @brief  Node deconstructor
*/
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    while (head)
    {
        Node* temp = head;
        head = head->next;
        temp->data = NULL;
        temp->next = NULL;
        temp->prev = NULL;
        temp = NULL;
        delete temp;        
    }   
}

/**
* @brief   Node constructor.
*/
template <class T>
DoublyLinkedList<T>::Node::Node()
{
    data = NULL;
    next = NULL;
    prev = NULL;
}

/**
* @brief    Node constructor with class argument
*/
template <class T>
DoublyLinkedList<T>::Node::Node(T* data)
{
    next = NULL;
    prev = NULL;
    this->data = data;
}


/**
* @brief   DoublyLinkedList constructor.
*/
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() 
{
    head = NULL;
    tail = NULL;
    current = NULL;
}


/**
* @brief   Appends a new Node at the end of the DoublyLinkedList.
* @param   data A pointer to the data to be stored in the new Node.
* @return  Nothing.
*
* Creates a new Node to hold the data and appends the Node at the end
* of the list. The current Node pointer is set to point to the newly
* appended Node.
*/
template <class T>
void DoublyLinkedList<T>::append(T* data) 
{
    if(empty())
    {
        head = new Node(data);
        tail = head;
    }
    else
    {
        tail->next = new Node(data);
        tail->next->prev = tail;
        tail = tail->next;
    }
}


/**
* @brief   Get the first thing on the list.
* @return  A pointer to the data stored in the first Node on the list,
*          or nullptr if the list is empty.
*
* The current pointer is set to point to the first Node in the list,
* or nullptr if the list is empty.
*/
template <class T>
T* DoublyLinkedList<T>::first() 
{
    if(head == NULL)
        return NULL;
    else
    {
        current = head;
        return current->data;
    }
}


/**
* @brief   Get the next thing on the list.
* @return  A pointer to the data stored in the next Node on the list. The next
*          Node is the one following whatever the current pointer is pointing
*          to. If there is no next Node then nullptr is returned.
*
* The current pointer is set to point to the next Node in the list,
* or nullptr if there is no next Node.
*/
template <class T>
T* DoublyLinkedList<T>::next()
{
    if(current == NULL)
        return NULL;
    else
    {
        current = current->next;
        if(current != NULL)
            return current->data;
        return NULL;
    }
}


/**
* @brief   Remove the Node pointed to by the current pointer.
* @return  A pointer to the data stored in the next Node on the list. The next
*          Node is the one following the Node that was removed. If there is
*          no next Node then nullptr is returned.
*
* The current pointer is set to point to the next Node in the list, following
* the Node that was removed, or nullptr if there is no next Node.
*/
template <class T>
T* DoublyLinkedList<T>::remove() 
{
    if(current == NULL)
        return NULL;
    else
    {
        Node* temp = current;
        // if only item in list
        if (current == head && current->next == NULL)
        {
            head = NULL;
            tail = NULL;
            temp = NULL;
            delete temp;
            return NULL;
        }
        // if item is at beginning of list
        else if (current == head)
        {
            head = current->next;
            current = current->next;
            current->prev = NULL;
            temp = NULL;
            delete temp;
            return head->data;
        }
        // if item is the last item in the list
        else if (current->next == NULL)
        {
            tail = current->prev;
            current->prev->next = NULL;
            current = NULL;
            if (temp->prev == NULL)
                head = current;
            temp = NULL;
            delete temp;
            return NULL;
        }
        // anywhere else in list
        else
        {
            current = current->next;
            current->prev = temp->prev;
            if (temp->prev != NULL)
                temp->prev->next = current;
            else
                head = current;
            temp = NULL;
            delete temp;
            return current->data;
        }
    }
}


#endif // CSCI_311_DOUBLYLINKEDLIST_H