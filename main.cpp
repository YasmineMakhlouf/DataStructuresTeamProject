#include <iostream>
#include "ArrayBasedList.h"
using namespace std;

/**
 * CSIS216 Project — Array-Implement Linked Lists
 *
 * This program provides a console-based menu system to test all the
 * basic operations of the List class using a fixed-size, array-based
 * implementation via NodePool.
 *
 * Features:
 * - Insert elements (at head, tail, position, after value)
 * - Delete elements (by position, first, last, or by value)
 * - View the current list
 * - Run extra operations (search, size, reverse)
 *
 * Authors: Rim Jiblawi , Yasmine Makhlouf, Jason Jamous
 */

int main()
{
    ArrayBasedList<string> csisList; // The linked list instance using string elements
    int mainChoice, subChoice;       // Menu selections
    string value, after;             // For user input of string values
    int position;                    // For inputting specific positions

    cout << "\n========== Welcome to CSIS216 Project ==========\n";

    do
    {
        // Display main menu
        cout << "\n========== Please select an option: ==========\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display List\n";
        cout << "4. Other Operations (Search, Size, Reverse)\n";
        cout << "0. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice)
        {
        // ------------------- INSERTION OPERATIONS -------------------
        case 1:
            cout << "\n--- INSERT MENU ---\n";
            cout << "1. Insert at Head\n";
            cout << "2. Insert at Tail\n";
            cout << "3. Insert at Specific Position\n";
            cout << "4. Insert After Specific Element\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice)
            {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                csisList.insertFirst(value);
                break;

            case 2:
                cout << "Enter value to insert at tail: ";
                cin >> value;
                csisList.insertLast(value);
                break;

            case 3:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Enter position: ";
                cin >> position;
                csisList.insertAtPos(value, position);
                break;

            case 4:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Insert after which element? ";
                cin >> after;
                csisList.insertAfter(value, after);
                break;

            default:
                cout << "Invalid Insert option.\n";
                break;
            }
            break;

        // ------------------- DELETION OPERATIONS -------------------
        case 2:
            cout << "\n--- DELETE MENU ---\n";
            cout << "1. Delete First Element\n";
            cout << "2. Delete Last Element\n";
            cout << "3. Delete Specific Element\n";
            cout << "4. Delete at Specific Position\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice)
            {
            case 1:
                csisList.deleteFirst();
                break;

            case 2:
                csisList.deleteLast();
                break;

            case 3:
                cout << "Enter element to delete: ";
                cin >> value;
                csisList.deleteElement(value);
                break;

            case 4:
                cout << "Enter position to delete: ";
                cin >> position;
                csisList.deleteAtPos(position);
                break;

            default:
                cout << "Invalid Delete option.\n";
                break;
            }
            break;

        // ------------------- DISPLAY CURRENT LIST -------------------
        case 3:
            cout << "\n--- CURRENT LIST ---\n";
            cout << csisList;
            break;

        // ------------------- OTHER UTILITIES -------------------
        case 4:
            cout << "\n--- OTHER OPERATIONS MENU ---\n";
            cout << "1. Search for an Element\n";
            cout << "2. Get Size of the List\n";
            cout << "3. Display List in Reverse\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice)
            {
            case 1:
                cout << "Enter element to search: ";
                cin >> value;
                position = csisList.search(value);
                if (position != -1)
                    cout << value << " found at position " << position << endl;
                else
                    cout << value << " not found.\n";
                break;

            case 2:
                cout << "Size of the list: " << csisList.getsize() << endl;
                break;

            case 3:
                cout << "List in Reverse:\n";
                csisList.reverse(); // Reverse the list
                cout << csisList;   // Print reversed list
                csisList.reverse(); // Reverse again to restore original order
                break;

            default:
                cout << "Invalid Other operation option.\n";
                break;
            }
            break;

        // ------------------- EXIT -------------------
        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;

        // ------------------- INVALID MAIN OPTION -------------------
        default:
            cout << "Invalid Main Menu option. Try again.\n";
            break;
        }

    } while (mainChoice != 0);

    return 0;
}
