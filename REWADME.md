# DataStructuresTeamwork

**CSIS216 Project — Array-Based Linked List Implementation**

This project is a console-based C++ application that demonstrates a **singly linked list** using a **fixed-size array storage pool**. The list supports standard linked list operations including insertion, deletion, search, and reverse.

---

## Features

- **Insertion Operations**
  - Insert at the head (`insertFirst`)
  - Insert at the tail (`insertLast`)
  - Insert at a specific position (`insertAtPos`)
  - Insert after a specific element (`insertAfter`)

- **Deletion Operations**
  - Delete first element (`deleteFirst`)
  - Delete last element (`deleteLast`)
  - Delete at a specific position (`deleteAtPos`)
  - Delete a specific element (`deleteElement`)

- **Other Utilities**
  - Search for an element (`search`)
  - Get the current size of the list (`getsize`)
  - Reverse the list (`reverse`)
  - Display the list (`display`)

- **Array-based node storage**
  - Uses a `NodePool` class to manage a fixed-size storage pool
  - Prevents dynamic memory allocation and manages free nodes efficiently

---

## Files

- `main.cpp` — Contains the console-based menu and testing of list operations
- `ArrayBasedList.h` — Template class for array-based linked list
- `NodePool.h` — Template class for managing the fixed-size node pool
- `README.md` — Project description and documentation

---

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/USERNAME/DataStructuresTeamwork.git


Authors

Yasmine Makhlouf
Rim Jiblawi
Jason Jamous