/**
 * @file doubly_linked_list.cpp
 * @author Nabiha Khalid Sheikh
 * @brief Implementation of the doubly linked list using the rest of the files.
 *
 * Contains logic to create a doubly linked list. This file was created from scratch.
 *
 * 03/14/2026 - the file was made for milestone3
 * 04/28/2026 - the file was altered to fit milestone 5 requirements
 */




 #include "binary_search_tree.h"
 #include "cache_manager.h"
 #include "dll_node.h"
 #include "doubly_linked_list.h"
 #include "hash_node.h"
 #include "hash_table.h"
 #include "milestone5.h"
 #include "tree_node.h"

using namespace std;


/**
     * @brief Constructs an empty doubly linked list.
*/
DoublyLinkedList::DoublyLinkedList() { 
    head = nullptr; 
    tail = nullptr; 
    size = 0;

}

/**
     * @brief Destroys the list and releases all memory.
*/
DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

/**
     * @brief Returns the number of entries in the list.
     * @return Number of nodes in the list.
*/
int DoublyLinkedList::getSize() {
    return size;
}

/**
     * @brief Checks whether the list is empty.
     * @return True if the list is empty, false otherwise.
*/
bool DoublyLinkedList::isEmpty() {
    return head == nullptr;
}

/**
     * @brief Inserts a new node at the head of the list.
     * @param key Integer key for the new node.
     * @param newNode Pointer to the node to insert.
*/
void DoublyLinkedList::insertAtHead(int key, DllNode* newNode) {
    if (isEmpty()) { 
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr; 
        size++;
    } else { 
        newNode->next = head; 
        head->prev = newNode; 
        head = newNode; 
        newNode->prev = nullptr;
        size++;
    }
}

/**
     * @brief Inserts a new node at the tail of the list.
     * @param key Integer key for the new node.
     * @param newNode Pointer to the node to insert.
*/
void DoublyLinkedList::insertAtTail(int key, DllNode* newNode) {
    if (isEmpty()) { 
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr; 
        size++;
    } else { 
        newNode->prev = tail; 
        tail->next = newNode; 
        tail = newNode; 
        newNode->next = nullptr;
        size++;
    }
}

/**
     * @brief Removes the node with the given key from the list.
     * @param key The key of the node to remove.
*/
void DoublyLinkedList::remove(int key) {
    if (isEmpty()) { 
        return; 
    }
    DllNode* current = head; 
    while (current != nullptr) { 
        if (current->key == key) { 
            if (current == head) { 
                removeHeaderNode(); 
            } else if (current == tail) { 
                removeTailNode(); 
            } else { 
                current->prev->next = current->next; 
                current->next->prev = current->prev; 
                size--;
                delete current; 
            }
            return; 
        }
        current = current->next; 
    }
}

/**
     * @brief Removes the first node (head) of the list.
*/
void DoublyLinkedList::removeHeaderNode() {
    if (isEmpty()) { 
        return; 
    }
    DllNode* temp = head; 
    if (head == tail) { 
        head = nullptr; 
        tail = nullptr; 
        size--;
    } else { 
        head = head->next; 
        head->prev = nullptr; 
        size--;
    }
    delete temp;

}

/**
     * @brief Removes the last node (tail) of the list.
*/
void DoublyLinkedList::removeTailNode() {
    if (isEmpty()) { 
        return; 
    }
    DllNode* temp = tail; 
    if (head == tail) { 
        head = nullptr; 
        tail = nullptr; 
        size--;
    } else { 
        tail = tail->prev; 
        tail->next = nullptr; 
        size--;
    }
    delete temp;

}

/**
     * @brief Moves the node with the given key to the head of the list.
     * @param key Key of the node to move.
*/
void DoublyLinkedList::moveNodeToHead(int key) {
    if (isEmpty()) { 
        return; 
    }
    DllNode* current = head; 
    while (current != nullptr) { 
        if (current->key == key) { 
            if (current == head) { 
                return; 
            } else if (current == tail) { 
                //disconnect
                tail = current->prev;
                tail->next = nullptr;

                //connect
                current->prev = nullptr;
                current->next = head;
                head->prev = current;
                head = current;
            } else { 
                current->prev->next = current->next; 
                current->next->prev = current->prev; 

                current->prev = nullptr; 
                current->next = head; 
                head->prev = current; 
                head = current; 
            }
            return; 
        }
        current = current->next; 
    }
}

/**
     * @brief Moves the node with the given key to the tail of the list.
     * @param key Key of the node to move.
*/
void DoublyLinkedList::moveNodeToTail(int key) {
    if (isEmpty()) { 
        return; 
    }
    DllNode* current = head; 
    while (current != nullptr) { 
        if (current->key == key) { 
            if (current == tail) { 
                return; 
            } else if (current == head) { 
                head = current->next;
                head->prev = nullptr;

                current->next = nullptr;
                current->prev = tail;
                tail->next = current;
                tail = current;
            } else { 
                current->prev->next = current->next; 
                current->next->prev = current->prev; 
                
                current->next = nullptr; 
                current->prev = tail; 
                tail->next = current; 
                tail = current; 
            }
            return; 
        }
        current = current->next; 
    }
}

 /**
     * @brief Clears the list by deleting all nodes.
*/
void DoublyLinkedList::clear() {
    DllNode* current = head; 
    while (current != nullptr) { 
        DllNode* temp = current; 
        current = current->next; 
        delete temp; 
    }
    head = nullptr; 
    tail = nullptr; 
    size = 0;
}   

 /**
     * @brief Prints the list from head to tail to the console and output file.
*/
void DoublyLinkedList::printList() {
    logToFileAndConsole("");
    logToFileAndConsole("Here are the FIFO List contents:");
    DllNode* current = head; 
    while (current != nullptr) {
        logToFileAndConsole("FIFO Node key: " + to_string(current->key) + ", fullName: " + current-> fullName + ", address: " + current-> address + ", city: " + current-> city + ", state: " + current-> state + ", zip: " + current-> zip);
        current = current->next; 
    }

    logToFileAndConsole("End of FIFO List");


}

/**
     * @brief Prints the list from tail to head to the console and output file.
*/
void DoublyLinkedList::reversePrintList() {
    logToFileAndConsole("");
    logToFileAndConsole("Here are the List contents reversed:");
    DllNode* current = tail; 
    while (current != nullptr) { 
        logToFileAndConsole("FIFO Node key: " + to_string(current->key));
        current = current->prev; 
    }
    logToFileAndConsole("End of List");

}