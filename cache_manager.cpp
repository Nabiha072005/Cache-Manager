/**
 * @file cache_manager.cpp
 * @author Nabiha Khalid Sheikh, 
 * @brief Coordinated the hash table and the doubly linked list.
 *
 * 04/14/2026 - the file was made for milestone3
 * 04/28/2026 - file was altered to fit milestone 5 requirements. This file had to be changed the most 
 * to incoporate the binary search tree part to the cache manager which milestone3 did not
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
     * @brief Returns a pointer to the internal hash table.
     * @return Pointer to the HashTable object.
*/
 HashTable* CacheManager::getTable() {
    return hashTable; 
}

/**
     * @brief Returns a pointer to the internal FIFO list.
     * @return Pointer to the DoublyLinkedList object.
*/
DoublyLinkedList* CacheManager::getList() {
    return doublyLinkedList;
}

/**
	*
	* getBst
	*
	* Method to return the BST
	*
	* @param    none
	*
	* @return	the BST
*/
BinarySearchTree* CacheManager::getBst() {
    return binarySearchTree;
}


/**
     * @brief Gets the current number of items in the cache.
     * @return Number of items in the cache.
*/
int CacheManager::getSize() { //not referring to the capacity but rather the number of items
    //get the size either from the hash table or the list as they both will have the same size
    return hashTable->getNumberOfItems(); //Call the getNumberOfItems() function from the HashTable object that hashTable points to.
    
}

/**
     * @brief Checks whether the cache is empty.
     * @return True if the cache has no entries, false otherwise.
*/
bool CacheManager::isEmpty() {
    /** if (getSize() == 0) {
        return true;
     } else {
        return false;
    } or
    */  
   return (getSize() == 0);  
}

/**
     * @brief Adds a node to the cache, evicting the oldest entry if >= Max Cache Size
     * @param curKey Key associated with the node.
     * @param myNode Pointer to the node to be added.
     * @return True if the operation succeeds, false otherwise.
*/
bool CacheManager::add(int curKey, DllNode* myNode) {
    HashNode* newNode = new HashNode(curKey, myNode); 
    if (getSize() < maxCacheSize) {
        //add to the list
        //add to the head (because newest entries are the head)
        doublyLinkedList->insertAtHead(curKey, myNode);

        //add to the hash table
        hashTable->add(curKey, newNode); //the newNode has to be of the type HashNode* according to the structure  

        //add to the binary search tree
        binarySearchTree -> addToTree(curKey, myNode);
        
        return true;
        
    } else { 
        //remove the oldest entry (tail) from list, hash table, and binary search tree
        hashTable->remove(doublyLinkedList->tail->key);

        doublyLinkedList->removeTailNode();

        binarySearchTree->removeNode(doublyLinkedList->tail->key);
    
        //add the myNode to the head of the list
        doublyLinkedList->insertAtHead(curKey, myNode);

        //add to the hash table
        hashTable->add(curKey, newNode);

        //add to the binary search tree
        binarySearchTree -> addToTree(curKey, myNode);

        return true;
    }

}

/**
     * @brief Removes a node from the cache based on the key.
     * @param curKey Key of the node to be removed.
     * @return True if the operation succeeds, false otherwise.
*/
bool CacheManager::remove(int curKey) {
    if (contains(curKey)) {

    //remove from the list
    doublyLinkedList-> remove(curKey); 

    //remove from hash table
    hashTable-> remove(curKey);

    //remove from the binary search tree
    binarySearchTree -> removeNode(curKey);


    return true;

    } else {
        return false;

    }
    
}

/**
     * @brief Clears all entries from the cache.
*/
void CacheManager::clear() {
    doublyLinkedList-> clear();
    hashTable-> clear();
    binarySearchTree -> clear();
}

/**
     * @brief Retrieves a node from the cache.
     * @param curKey Key of the node to retrieve.
     * @return Pointer to the DllNode if found, nullptr otherwise.
*/

DllNode* CacheManager::getItem(int curKey) {
    if (contains(curKey)) {
        HashNode* node = hashTable->getItem(curKey);
        return node->fifoNode;  //accessing the fifoNode field inside the HashNode, and that field already is a DllNode* which is what we want as the return type is DllNode*
    } else {
        return nullptr; 
    }
    
}

/**
     * @brief Gets the maximum cache size.
     * @return Maximum number of entries the cache can hold.
*/
int CacheManager::getMaxCacheSize() {
    return maxCacheSize;
}

/**
     * @brief Checks if a specific key exists in the cache.
     * @param curKey Key to check.
     * @return True if the key exists in the cache, false otherwise.
*/
bool CacheManager::contains(int curKey) {
    return hashTable-> contains(curKey);
}

/**
     * @brief Prints the current contents of the cache to console and output file.
*/
void CacheManager::printCache() {
    logToFileAndConsole("");
    logToFileAndConsole("");
    logToFileAndConsole("Printing out the cache contents");

    doublyLinkedList-> printList();

    logToFileAndConsole("");

    hashTable-> printTable();

    binarySearchTree-> printInOrder();

    binarySearchTree-> printReverseOrder();

    logToFileAndConsole("");
    logToFileAndConsole("End of cache contents");
    logToFileAndConsole("");

}
/**
	*
	* range
	*
	* Method to traverse and print out the cache information given a low and high value.
	*
	* @param    low			the lower bound (inclusive) of the range to print
	* @param	high		the higher bound (inclusive) of the range to print
	*
	* @return   nothing, but prints out the keys for the cache between low and high
*/
void CacheManager::printRange(int low, int high) {
    binarySearchTree -> printRange(low, high);
}


/**
	*
	* printSort
	*
	* Method to print out the cache information in sorted order
	*
	* @param    ascending	true, if output is to be in ascending order, false for descending order
	*
	* @return   nothing, but prints out the keys for the cache in sorted order
*/
void CacheManager::printSort(bool ascending) {
    if (ascending == true) {
        binarySearchTree -> printInOrder();

    } else { //ascending == false aka descending 
        binarySearchTree -> printReverseOrder(); 
    }
    
    

}

