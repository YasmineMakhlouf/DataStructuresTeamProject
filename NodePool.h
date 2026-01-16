#ifndef NODEPOOL_H
#define NODEPOOL_H

/**-- NodePool.h------------------------------------------------------------------
    This header file manages a fixed-size storage pool of nodes used in a linked list.
    Using an array of nodes, this template class manages the nodes , setting the linked
    list up for multiple operations.

    Basic Operations:
        Constructor: Initializes the storage pool and links every node to the next one,
        but the last one. This gives us a free list, a list where all nodes are free.
        newNode: Allocates and returns the index of the first free node in the pool
        while assigning a new node to the free index/list
        returnNode: Frees a node by assigning
        getNode: Provides access to the node by reference
        getFree: (this was used only for debugging): it returns the index of the free node
        isFull: Checks if the storage pool is full

----------------------------------------------------------------------------------**/

const int NULL_VALUE = -1; // Expresses that a node is last in the list or there's no free node
const int NUM_NODES = 10;   // The number of nodes available in the storage pool
typedef int NodePtr;       // an alias for the index pointers

template <typename ElementType> // A type of class where the type of data is user-defined
class NodePool
{ // Forward Declaration
private:
    /**--NodeType--------------------------------------------------
     A node struct that holds an element of user-defined data type (in our case string)
     and an index "next" that points to the next node of the list.
     It is considered private to assure encapsulation and avoid leaks, or breach by the user.
     ---------------------------------------------------------------**/
    struct NodeType
    {                     // Struct Declaration
        ElementType data; // data stored in the node
        NodePtr next;     // index of the next node

        /***** NodeType (no-argument constructor) *****/
        /*-----------------------------------------------------------
        Initializes a node by assigning the data field its default
        value and setting the next index to NULL_VALUE, indicating
        that the node has no successor.
        ------------------------------------------------------------*/
        NodeType() : data(), next(NULL_VALUE) {} 

        /***** NodeType (parameterized constructor) *****/
        /*-----------------------------------------------------------
        Initializes a node with the provided data element and sets
        the next index to the specified value. If no next value is
        provided, it defaults to NULL_VALUE, indicating no successor.
        ------------------------------------------------------------*/
        NodeType(const ElementType& item, NodePtr n = NULL_VALUE)
        {
            data = item;
            next = n;
        }

    };

    NodeType arrNode[NUM_NODES]; // Array of nodes
    NodePtr free;                // Index of the first free node

public:
    /***** Constructor *****/
    /*------------------------------------------------------
        Initializes the storage pool linking all nodes together. Each node points
        to the next one, and the last node point to NULL_VALUE indicating the end.

        Precondition: None
        Post-condition: Each node is linked to the next one, and free points to 0
        indication that the first node in the pool is available.
    -------------------------------------------------------*/
    NodePool()
    {
        for (int i = 0; i < NUM_NODES - 1; i++)
        {                            // Loops through the array
            arrNode[i].next = i + 1; // Links each node to the next one
        }

        arrNode[NUM_NODES - 1].next = NULL_VALUE; // Links the last node to NULL_VALUE
                                                  // indicating the end of the newly
                                                  // initialized linked list
        free = 0;                                 // setting the first node as free
    }

    /***** newnode *****/
    /*------------------------------------------------------------
        Returns and allocates an index of the next free available node. And moves the free
        index to the next available node. Before allocating, it checks whether the storage pool is full.
        If the pool is full, NULL_VALUE is returned.

        Precondition: None (the function internally checks if the pool is full)
        Post-condition: Returns the index of the next free node.
    ---------------------------------------------------------------*/

    int newNode()
    {
        if (isFull()) 
            return NULL_VALUE;     // Returns NULL_VALUE if no free nodes are available

        int index = free;          // Stores the index of the free node in a local variable
        free = arrNode[free].next; // Moves the free pointer/index to the next node
        return index;              // Returns the index of the newly allocated node
    }

    /***** returnNode *****/
    /*-------------------------------------------------------------------------
     Returns the index of a node and assigns it to the free index, "freeing up" the pool.

     PreCondition: index must be valid and list should not be empty
     Post-Condition: The node in question is now the first free node
     -------------------------------------------------------------------------*/

    void returnNode(NodePtr index)
    {
        arrNode[index].next = free; // the node succeeding the node we want to free
                                    // becomes the first free node
        free = index; // the index of the node want to free/delete is assigned to free
    }

    /***** getNode *****/
    /*----------------------------------------------------------------
    This function returns the node with respect to its index. This function is used to access nodes,
    then to modify them using different operations

    Precondition: index must be valid which is always the case
    Post -condition: returns a reference to the node depending in its index
    ------------------------------------------------------------------*/
    NodeType &getNode(int index)
    {
        return arrNode[index]; // Accesses the node in question and returns it
    }
    /***** getNode (const)*****/
    /*----------------------------------------------------------------
    This function returns the node with respect to its index. This function is used to ONLY
    access nodes with NO purpose of modifying them

    Precondition: index must be valid which is always the case
    Post -condition: returns a reference to the node depending in its index
    ------------------------------------------------------------------*/

    const NodeType &getNode(int index) const
    {
        return arrNode[index];
    }
    /***** getFree *****/
    /*-----------------------------------------------------------------
    This function is used by the programmer to keep track of the "free" data field,
    helping him debug and search for errors if needed. The user should not use it
    as it will be commented out.

    PreCondition: None
    Post-Condition: returns the free index/pointer or NULL_VALUE if no free nodes
    ----------------------------------------------------------------------*/
    int getFree() const
    {
        return free;
    }

    /***** isFull *****/
    /*-------------------------------------------------------
     Checks whether the pool is full and out of free nodes.

     Precondition: Nonce
     Post-Condition: Return true if free is NULL_VALUE, false otherwise
     --------------------------------------------------------*/
    bool isFull() const
    {
        return free == NULL_VALUE; // Checks if free is equal to NULL and returns the result
    }
};
#endif