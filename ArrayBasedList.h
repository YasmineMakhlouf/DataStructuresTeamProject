#ifndef ARRAYBASEDLIST_H
#define ARRAYBASEDLIST_H

/**--ArrayBasedList.h-----------------------------------------------------------------------------
    This template class is responsible for a singly linked list, storing its nodes in a
    fixed-size array list. Also, multiple basic linked list operations are conducted
    through this class which we will view later.

    Basic Operations:
    Constructor: Creates an empty list
    Copy Constructor: Creates a deep copy of an existing list
    Assignment Operator: Assigns one List object to another, performing
                         a deep copy.
    Destructor : Cleans up memory used by the list
    Getters: Gives access to private data fields such as size, first....


    **Insertion Operations**
    insertFirst: insert an element at the head of the list
    insertLast: insert an element at the tail of the list
    insertAtPos: insert an element at a given valid position
    insertAfter: insert an element after a given element in the list

    **Deletion Operations**
    deleteFirst: removes the head from the list
    deleteLast: removes the tail from the list
    deleteAtPos: removes an element at a given valid position
    deleteElement: delete a given element from the list

    **Other**
    search : search the list for a node containing a given element
    and returns its position
    reverse: reverse the current list; (head become tail) and each node points to
    its predecessor (this is an exercise in the book chapter 6)
    display: outputs the list from head to tail

    Overloaded Operator: Sends the elements of the list to the output stream

    Class Invariants:
    1. Size is the number of nodes in the list
    2. Position of the first element is 0, of the second 1 and etc...
    3. first == NULL_VALUE means the list is empty
    4. No invalid indices can be found in the list: we make sure that were always
    respecting the list boundaries
    5. The insertion after an element means inserting after the first occurrence of it


-------------------------------------------------------------------------------------------*/
#include "NodePool.h"
#include <iostream>
using namespace std;

template <typename ElementType> // A template class where a type is selected by the user
                                // to all variables of type ElementType
class ArrayBasedList
{ // Forward Declaration
private:
    NodePool<ElementType> storagePool; // Fixed size of nodes used to store elemets
    NodePtr first;                     // index of the first node of the list
    int size;                          // keeps track of number of elements in the list

public:
    /***** Constructor *****/
    /*------------------------------------------------------
        Creates an empty linked list by setting size to 0, first to NULL_VALUE,
        Meanwhile, storagePool is calling its copy constructor to initialize
        a storage pool for the nodes forming the linked list

        Precondition: None
        Post-condition: Empty linked list, size is 0 and an initialized storage pool
    -------------------------------------------------------*/
    ArrayBasedList() : first(NULL_VALUE), size(0) {}

    /***** Copy Constructor *****/
    /*--------------------------------------------------------------------
    Creates a deep copy of another linked list (new storage pool too).

    Precondition: origList is a valid List object of the same ElementType.
    Post-condition: This list will contain an identical sequence of elements,
    using a separate storage pool,
    -----------------------------------------------------------------*/
    ArrayBasedList(const ArrayBasedList<ElementType> &origList)
    {
        // If the original list is empty, initialize this list as empty too
        if (origList.first == NULL_VALUE)
        {
            first = NULL_VALUE; // No head node
            size = 0;           // Size is zero
            return;
        }
        size = origList.size;         // Copy the size value from the original list
        NodePtr ptr = origList.first; // Start at the head of the original list
        NodePtr last = NULL_VALUE;    // To keep track of the last copied node
        // Traversal of list till the end
        while (ptr != NULL_VALUE)
        {
            // Allocate a new node from this list's pool
            NodePtr nextIndex = storagePool.newNode();
            // Copy the data from the original node into the new node
            storagePool.getNode(nextIndex).data = origList.storagePool.getNode(ptr).data;
            // Set the new node's next to NULL_VALUE (will be fixed if another node follows)
            storagePool.getNode(nextIndex).next = NULL_VALUE;

            if (last == NULL_VALUE)
            {                      // To make sure it is the first node
                first = nextIndex; // This is the first node being added to this list
            }
            else
            {
                // Link the previous node's next to the new node
                storagePool.getNode(last).next = nextIndex;
            }

            last = nextIndex;                             // update the last node index
            ptr = origList.storagePool.getNode(ptr).next; // move ptr to the next node
                                                          // to be copied
        }
    }

    /***** Assignment Operator *****/
    /*-------------------------------------------------------------------------------------
    Performs a deep copy of the right-hand side list into this list,
    replacing any existing elements.

    Precondition: rightHandSide must be a valid List object
    Post-condition: This list will contain the same elements
    as rightHandSide.
    -------------------------------------------------------------------------------------*/
    ArrayBasedList &operator=(const ArrayBasedList<ElementType> &rightHandSide)
    {
        // If the object is being assigned to itself, do nothing
        if (this == &rightHandSide)
        {
            return *this;
        }
        // Clear the current list
        while (first != NULL_VALUE)
        {
            NodePtr temp = first;                    // store the head in a temporary variable
            first = storagePool.getNode(first).next; // move the head forward
            storagePool.returnNode(temp);            // free the node
        }

        size = 0; // reset size after clearing the list to ensure an accurate fresh start

        // If rightHandSide is empty, set this list to empty
        if (rightHandSide.first == NULL_VALUE)
        {
            first = NULL_VALUE;
            return *this;
        }

        size = rightHandSide.size;         // copy size
        NodePtr ptr = rightHandSide.first; // pointer to current node in source list
        NodePtr last = NULL_VALUE;         // pointer to last copied node in this list
        // Traversal of list till the end
        while (ptr != NULL_VALUE)
        {
            NodePtr nextIndex = storagePool.newNode(); // allocate new node in this list’s pool
            // now same operation as the copy constructor
            storagePool.getNode(nextIndex).data = rightHandSide.storagePool.getNode(ptr).data;
            storagePool.getNode(nextIndex).next = NULL_VALUE;

            if (last == NULL_VALUE)
            {
                first = nextIndex;
            }
            else
            {
                storagePool.getNode(last).next = nextIndex;
            }

            last = nextIndex;
            ptr = rightHandSide.storagePool.getNode(ptr).next;
        }

        return *this; // return reference
    }
    /***** Destructor *****/
    /*--------------------------------------------------------------------------
     Destroys and cleans up the memory taken by the list by freeing up all the nodes

    Precondition: list and storage pool must be initialized
    Post-condition: All nodes that belonged to the list are returned to the free list
    in the NodePool, first is set to NULL_VALUE and size is set to zero
    ------------------------------------------------------------------------------*/
    ~ArrayBasedList()
    {
        size = 0; // Reset size
        // Traversal of list till the end
        while (first != NULL_VALUE)
        {
            NodePtr temp = first;                    // Store current node index
            first = storagePool.getNode(first).next; // Advance to the next node
            storagePool.returnNode(temp);            // Free up the current node
        }
    }

    /***** Getters *****/
    /*------------------------------------------------------------------------
    Provides access to the data fields of List.

    Precondition:  None.
    Post-condition: Returns the requested data field value.

    NOTE: getFree() s used by the programmer to keep track of the "free" data field,
    helping him debug and search for errors if needed. The user should not use it
    as it will be commented out.
    -----------------------------------------------------------------------*/

    int getsize() const
    {
        return size;
    }

    int getFirst() const
    {
        return first;
    }

    int getFree() const
    {
        return storagePool.getFree();
    }

    bool isEmpty() const
    {
        return first == NULL_VALUE;
    }

    /***** insertFirst *****/
    /*-------------------------------------------------------------------------------
    Inserts a new element at the beginning (head) of the list.
    Precondition: The storage pool must not be full
    Post-condition: A new node is inserted at head of the list, size is incremented
    by 1, and first is updated to contain the index of the next node
    If the pool is full , a message is displayed
    ----------------------------------------------------------------------------------*/
    void insertFirst(const ElementType &element)
    {
        // Checks if storage pool is full
        if (storagePool.isFull())
        {
            cout << "Storage Pool is full; " << element << " could not be inserted" << endl;
            return;
        }
        NodePtr nextIndex = storagePool.newNode(); // Allocate a new node from this list's pool
        // Set the new node's data to the element
        storagePool.getNode(nextIndex).data = element;
        // Link the new node to point to the current first node
        storagePool.getNode(nextIndex).next = first;
        first = nextIndex; // update head
        size++;            // increment size
        // display success
        cout << element << " is inserted at the head of the list" << endl;
    }

    /***** insertLast *****/
    /*-------------------------------------------------------------------------------------
     Insert a new element to the tail of the list

     Precondition: The storage pool must be not full
     Post-condition: If the list is empty, the element is inserted at the head.
     Otherwise, it is inserted at the tail. The list size is incremented
     ---------------------------------------------------------------------------------------*/
    void insertLast(const ElementType &element)
    {
        // Checks if storage pool is full
        if (storagePool.isFull())
        {
            cout << "Storage Pool is full; " << element << " could not be inserted" << endl;
            return;
        }
        // Checks if position is 0
        if (size == 0)
        {
            // inserting at head to avoid duplicate code by calling insertFirst
            insertFirst(element);
            return;
        }

        NodePtr ptr = first; // Starts from head
        // Traversal to the tail
        while (storagePool.getNode(ptr).next != NULL_VALUE)
        {
            ptr = storagePool.getNode(ptr).next; // Move to next node
        }
        // Allocate a new free node
        NodePtr nextIndex = storagePool.newNode();
        storagePool.getNode(nextIndex).data = element;                       /// Set value
        storagePool.getNode(nextIndex).next = storagePool.getNode(ptr).next; // New tail
        // Link the previous tail to the new node
        storagePool.getNode(ptr).next = nextIndex;
        size++; // Increment size
        // display success
        cout << element << " is inserted at the tail of the list" << endl;
    }

    /***** insertAtPos *****/
    /*-------------------------------------------------------------------------------
    Inserts a new element at a specific position in the list (after position - 1)

    Precondition: Position must be in the range [0, size] and pool should not be full
    Post-condition: The element is inserted at the specified position, and the size is
    incremented. If the position is invalid, the insertion is aborted with an error message
    -----------------------------------------------------------------------------------*/
    void insertAtPos(const ElementType &element, unsigned pos)
    {
        // Checks if storage pool is full
        if (storagePool.isFull())
        {
            cout << "Storage Pool is full; " << element << " could not be inserted" << endl;
            return;
        }
        // Check if the position is valid
        if (pos > size)
        {
            cout << "Invalid Position." << endl;
            return;
        }
        // Checks if position is 0
        if (pos == 0)
        {
            // inserting at head to avoid duplicate code by calling insertFirst
            insertFirst(element);
            return;
        }

        NodePtr ptr = first; // Starts from head
        unsigned count = 0;  // position counter

        // loop to advance to the node at position 'pos - 1'
        while (ptr != NULL_VALUE && count < pos - 1)
        {
            ptr = storagePool.getNode(ptr).next; // advance to next node
            count++;                             // increasing count
        }

        NodePtr nextIndex = storagePool.newNode();     // Allocate a new node from this list's pool
        storagePool.getNode(nextIndex).data = element; // Set data
        // Point to what ptr was pointing to
        storagePool.getNode(nextIndex).next = storagePool.getNode(ptr).next;
        storagePool.getNode(ptr).next = nextIndex;                     // Link ptr to new node
        size++;                                                        // update size
        cout << element << " is inserted at position " << pos << endl; // display success
    }

    /***** insertAfter *****/
    /*------------------------------------------------------------------------------------
     Inserts a new element after the first occurrence of an existing element

    Precondition: The list must not be empty, the storage pool must not be full,
    and yhe after value must exist in the list.
    Post-condition: A new node with the given element is inserted immediately after
    the first occurrence of after. If the list is empty, or after is not found, no changes
    are made. If the pool is full, the insertion is aborted with an error message.
    ---------------------------------------------------------------------------------*/
    void insertAfter(const ElementType &element, const ElementType &after)
    {
        // List is empty so no insertion possible
        if (first == NULL_VALUE)
        {
            cout << "List is empty" << endl;
            return;
        }
        // Checks if storage pool is full
        if (storagePool.isFull())
        {
            cout << "Storage Pool is full; " << element << " could not be inserted" << endl;
            return;
        }

        NodePtr ptr = first; // Start from head
        // Traversal of list till the end
        while (ptr != NULL_VALUE)
        {
            // Compare current node's data with after
            if (storagePool.getNode(ptr).data == after)
            {
                // Allocate a new node from this list's pool
                NodePtr nextIndex = storagePool.newNode();
                // Set the new node's data
                storagePool.getNode(nextIndex).data = element;
                // Link the new node to the successor of after
                storagePool.getNode(nextIndex).next = storagePool.getNode(ptr).next;
                // Link the 'after' node to the new node
                storagePool.getNode(ptr).next = nextIndex;
                // Increment size
                size++;
                // display success
                cout << element << " is inserted after " << after << "." << endl;
                return;
            }
            ptr = storagePool.getNode(ptr).next; // move forward
        }
        cout << after << " not found :(" << endl; // element not found
    }

    /***** deleteFirst *****/
    /*------------------------------------------------------------------------
     Removes the head from the list and updated first

     Precondition: The list must not be empty.
     Post-condition: The node at head is removed from the list and set to the
     first free node. The size is decremented by1 and the deletion is aborted with
     an error message. First is updated
    -----------------------------------------------------------------------------*/

    void deleteFirst()
    {
        // Checks whether list is empty
        if (first == NULL_VALUE)
        {
            cout << "The list is empty. Nothing can be deleted." << endl;
            return;
        }
        NodePtr ptr = first;                     // Starts from head
        first = storagePool.getNode(first).next; // Sets first to next node
        storagePool.returnNode(ptr);             // returns the node to the free list
        size--;                                  // decrement size
        cout << " The head of the list is successfully deleted from the list." << endl;
    }

    /***** deleteLast *****/
    /*--------------------------------------------------------------------------
    Removes the tail from the list.

    Precondition: The list may not be empty
    Post-condition: The last node is removed and set as free. The size is decremented
    by 1. And, if the list becomes empty first is updated to NULL_VALUE.
    The deletion is aborted with an error message.
    ------------------------------------------------------------------------------*/

    void deleteLast()
    {
        // Checks whether the list is empty
        if (first == NULL_VALUE)
        {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }

        NodePtr ptr = first;       // start from beginning
        NodePtr pred = NULL_VALUE; // this is to check the previous node
        // Traverse to the end of the list
        while (storagePool.getNode(ptr).next != NULL_VALUE)
        {
            pred = ptr;                          // move pred forward
            ptr = storagePool.getNode(ptr).next; // move ptr forward
        }
        // this means that the element we want to delete is the only element in the list
        if (pred == NULL_VALUE)
        {
            first = NULL_VALUE; // we set first to NULL_VALUE (list is empty)
        }
        else
        {
            storagePool.getNode(pred).next = NULL_VALUE; // the previous node is linked
                                                         // to NULL_VALUE
        }

        storagePool.returnNode(ptr); // the deleted node is set as free
        size--;                      // size is decremented
        cout << "The tail of the list was successfully deleted." << endl;
    }

    /***** deleteAtPos *****/
    /*-------------------------------------------------------------------------------
    Deletes the element at a specified position from the list.

    Precondition: The list must not be empty and position must be
    in the range [0, size - 1].
    Post-condition: The node at position is removed from the list and set to the
    first free node. The size is decremented by 1.The deletion is aborted with
    an error message.
    -------------------------------------------------------------------------------*/
    void deleteAtPos(unsigned int pos)
    {
        // Check is list is empty
        if (first == NULL_VALUE)
        {
            cout << "The list is empty. Nothing can be deleted" << endl;
            return;
        }
        // Checks if position out of bounds
        if (pos >= size)
        {
            cout << "Invalid Position." << endl;
            return;
        }

        NodePtr ptr = first; // Starts from head
        // Delete the first element
        if (pos == 0)
        {
            first = storagePool.getNode(ptr).next; // update first
            storagePool.returnNode(ptr);           // return the first node to the free list
        }
        else
        {
            NodePtr pred = NULL_VALUE; // to store the precedent node
            int count = 0;             // position counter

            // Traverse to node at position 'pos'
            while (ptr != NULL_VALUE && count < pos)
            {
                pred = ptr;                          // move pred forward
                ptr = storagePool.getNode(ptr).next; // move ptr forward
                count++;                             // increment count
            }
            // linking he previous node to the next node (in relation to the node
            // we want to delete)
            storagePool.getNode(pred).next = storagePool.getNode(ptr).next;
            storagePool.returnNode(ptr); // set the deleted node to free
        }
        size--; // decrement size
        cout << "Element at position " << pos << " is deleted." << endl;
    }

    /***** deleteElement ****/
    /*--------------------------------------------------------------------------------
    Deletes the first node in the list that contains a specific value

    Precondition: The list need contain the element and cannot be empty.
    Post-condition: The element's node is removed from the list and set to the
    first free node. The size is decremented by 1 and the deletion is aborted with
    an error message.
    ----------------------------------------------------------------------------------*/
    void deleteElement(const ElementType &element)
    {
        // Checks if list is empty
        if (first == NULL_VALUE)
        {
            cout << "The list is empty." << endl;
            return;
        }
        NodePtr ptr = first;       // Start from head of the list
        NodePtr pred = NULL_VALUE; // Pointer to previous node(null at first)
        // Traverse till the eend
        while (ptr != NULL_VALUE)
        {
            // Compare the node data to the element
            if (storagePool.getNode(ptr).data == element)
            {
                // if pred is null, it means that the element is at head
                if (pred == NULL_VALUE)
                {
                    // so we set first to the next node
                    first = storagePool.getNode(ptr).next;
                }
                else
                {
                    // else, we link the previous with the next
                    storagePool.getNode(pred).next = storagePool.getNode(ptr).next;
                }

                storagePool.returnNode(ptr); // the node is set as the first free node
                size--;                      // size is decremented
                cout << element << " is deleted." << endl;
                return;
            }
            pred = ptr;                          // pred is moved forward
            ptr = storagePool.getNode(ptr).next; // ptr is moved forward
        }
        cout << element << " is not found" << endl;
    }

    /***** Search *****/
    /*----------------------------------------------------------------------------
     Searches for the first occurrence of an element and returns its position.

     Precondition: None
     Post-condition: If the element is found, returns its position.
     If not, returns -1
     ------------------------------------------------------------------------*/
    int search(const ElementType &element) const
    {
        NodePtr ptr = first; // start from head
        int pos = 0;         // position counter set to 0
        // Traversal of list till the end
        while (ptr != NULL_VALUE)
        {
            // Compare current node's data with the search target
            if (storagePool.getNode(ptr).data == element)
            {
                return pos; // if matches, return position
            }
            ptr = storagePool.getNode(ptr).next; // move forward to next node
            pos++;                               // increment position
        }
        return -1; // element not found
    }

    /***** reverse *****/
    /*----------------------------------------------------------------
     The list is reversed.

     Precondition: None
     Post-condition: Head becomes tails and evey node is now linked to is predecessor.
     --------------------------------------------------------------------------------*/
    void reverse()
    {
        NodePtr pred = NULL_VALUE; // previous node
        NodePtr current = first;   // current node
        NodePtr next = NULL_VALUE; // to store next (to keep track of current)
        // Traverse the list
        while (current != NULL_VALUE)
        {
            next = storagePool.getNode(current).next; // save next node
            storagePool.getNode(current).next = pred; // link current to previous
            pred = current;                           // move previous forward
            current = next;                           // move current forward
        }

        first = pred; // set first to the last previous node (tail)
    }

    /***** display *****/
    /*-------------------------------------------------------------------------
     Provide the outputs of the element of the linked list to the the output stream.

     Precondition: ostream out must be valid
     Post-condition: If list is empty, "NULL" is printed,
     else, elements are printed separated by " -> ", without ending with "NULL"
     -----------------------------------------------------------------------------*/
    void display(ostream &out) const
    {
        if (first == NULL_VALUE)
        {
            // List is empty
            out << "NULL" << endl;
            return;
        }
        NodePtr ptr = first; // Start from head
        // Traverse to print nodes
        while (ptr != NULL_VALUE)
        {
            out << storagePool.getNode(ptr).data; // print data
            // Only print " -> " if this is not the last node
            if (storagePool.getNode(ptr).next != NULL_VALUE)
            {
                out << " -> ";
            }
            ptr = storagePool.getNode(ptr).next; // Move forward
        }
        out << endl; // End line
    }

    /***** Overloaded Output Operator *****/
    /*---------------------------------------------------------------
    Allows the list to be output directly using the << stream operator,
    for example: cout << myList

    Precondition: The output stream out must be valid
    List must be properly initialized
    Post-condition: The elements of the list are sent to the output stream
    using the display() method.
    -----------------------------------------------------------------------*/
    friend ostream &operator<<(ostream &out, const ArrayBasedList<ElementType> &list)
    {
        list.display(out); // call the display method
        return out;        // Return the output stream to allow 'cout<<list)'
    }
};

#endif
