/**
 * @file hash_table.cpp
 * @author Nabiha Khalid Sheikh
 * @brief Implementation of the hash table.
 *
 * 03/14/2026 - the file was made for milestone3
 * 04/25/2026 - file was altered to fit milestone5 requirements
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
* @brief Returns the internal hash table array.
* @return Pointer to the hash table array.
*/
HashNode** HashTable::getTable() {
    return table;
}

/**
     * @brief Returns the total number of buckets in the hash table.
     * @return The number of buckets.
*/
int HashTable::getSize() {
    return numberOfBuckets;
}

/**
* @brief Calculates a hash code for the given key.
* @param currentKey The key to hash.
* @return The hash code (bucket index).
*/
int HashTable::calculateHashCode(int currentKey) {
    int bucketIndex = currentKey % numberOfBuckets; 
    return bucketIndex;
}

/**
* @brief Checks if the hash table is empty.
* @return true if the table has no items; false otherwise.
*/
bool HashTable::isEmpty() {
    return numberOfItems == 0;
}

/**
* @brief Returns the number of items in the hash table.
* @return The number of items.
*/
int HashTable::getNumberOfItems() {
    return numberOfItems;
}

/**
* @brief Adds a HashNode to the table using a specified key.
* @param curKey The key associated with the node.
* @param myNode Pointer to the node to add.
* @return true if successfully added; false otherwise.
*/
bool HashTable::add(int curKey, HashNode* myNode) {
    int bucketIndex = curKey % numberOfBuckets; 
    if (table [bucketIndex] == nullptr) { 
        myNode-> prev = nullptr;
        myNode-> next = nullptr;
        numberOfItems++;
        table[bucketIndex] = myNode; 
        
        return true;
    } else { 
        myNode-> prev = nullptr;
        myNode-> next = table [bucketIndex];
        table[bucketIndex]-> prev = myNode; 
        table[bucketIndex] = myNode;
        numberOfItems++;
        return true;

    }
}

/**
* @brief Removes a node from the table using a specified key.
* @param curKey The key of the node to remove.
* @return true if successfully removed; false otherwise.
*/
bool HashTable::remove(int curKey) {
    int bucketIndex = calculateHashCode(curKey);
    HashNode* current = table[bucketIndex];

    while (current != nullptr) {
        if (current->key == curKey) {
            if (current->prev == nullptr) { //remove head node 
                table[bucketIndex] = current->next; 
                if (current->next != nullptr)                
                    current->next->prev = nullptr;
            } else if (current->next == nullptr) { //remove tail node
                current->prev->next = nullptr;
            } else { //remove middle node
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;               
            numberOfItems--; // update count
            return true;                  
        }

        current = current->next;          
    }

    return false;                        
}

/**
* @brief Removes all entries from the hash table.
*/
void HashTable::clear() {
    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;  
            delete temp;
        }

        table[i] = nullptr; //bucket is now empty
    }

    numberOfItems = 0;
}

/**
* @brief Retrieves a node from the table based on key.
* @param curKey The key to search for.
* @return Pointer to the corresponding HashNode if found; nullptr otherwise.
*/
HashNode* HashTable::getItem(int curKey) {
    int bucketIndex = calculateHashCode(curKey);
    HashNode* current = table[bucketIndex];

    while (current != nullptr) { 
        if (current->key == curKey) {   
            return current;             
        }
        current = current->next;        
    }

    return nullptr;      
}

/**
* @brief Checks if a key exists in the table.
* @param curKey The key to check.
* @return true if found; false otherwise.
*/
bool HashTable::contains(int curKey) {
    return getItem(curKey) != nullptr;
}

/**
     * @brief Prints the contents of the hash table to the console and output file.
*/
void HashTable::printTable() {
    logToFileAndConsole("Here are the Hash Table contents (" + std::to_string(numberOfItems) + " entries):");

    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* current = table[i];

        if (current == nullptr) {
            logToFileAndConsole("Bucket " + to_string(i) + ": Empty");
        } else {
            logToFileAndConsole("Bucket " + to_string(i) + ": ");
            while (current != nullptr) {
                current->fifoNode-> printNode(); //from the dll_node.cpp
                current = current->next;
            }
        }
    }

    logToFileAndConsole("End of table");
    logToFileAndConsole("");
}