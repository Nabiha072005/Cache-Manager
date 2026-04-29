/**
* @author - Nabiha Khalid Sheikh
* @file binary_search_tree.cpp -  This file implements the binary search tree using the binary_search_tree.h
* 04/14/2026 - Made the file for milestone4 
* 04/28/2026 - Finished the assignment by adding more functions and their comments for milestone5
*/


 #include "binary_search_tree.h"
 #include "cache_manager.h"
 #include "dll_node.h"
 #include "doubly_linked_list.h"
 #include "hash_node.h"
 #include "hash_table.h"
 #include "milestone5.h"
 #include "tree_node.h"

#include <algorithm> //for the max function in insert
#include <queue> //for the breadth traversal


using namespace std;


/**
     * @brief Default constructor for BinarySearchTree.
     *
     * Initializes an empty binary search tree.
*/
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}


/**
     * @brief Destructor for BinarySearchTree.
     *
     * Frees the dynamically allocated memory by deleting all nodes in the tree.
*/
BinarySearchTree::~BinarySearchTree() {
    clear();
}


//helper function for insertion. This function allows for recursion to take place to allow insertion. This is a free function which means that it does not need to be in class (they are not part of the BinarySearchTree class)
TreeNode* insert(TreeNode* node, int key) { //inserting the chosen node from the tree
    if (node == nullptr) { //reached an empty spot in the tree
        return new TreeNode(key); //constructor from the tree_node.h that has all the default values
    } else if (key < node-> key ) { //insert at the left side of the tree
        node-> left = insert (node->left, key);
    } else if (key > node-> key) { //insert at the right side of the tree
        node-> right = insert (node->right, key);
    } else { // key = node-> key we are making a left biased tree
        node-> left = insert (node->left, key);
    }

    //activily updating the height and the number of nodes in each time recursion is returned 

    int leftSubTreeNodes = (node->left == nullptr) ? 0 : node->left->numberOfNodes;
    int rightSubTreeNodes = (node->right == nullptr) ? 0 : node->right->numberOfNodes;

     // changed to fit the output but height = 0 when number of nodes = 1, in this defintion return should be -1. However, there are other definitions of height
    int leftSubTreeHeight = (node->left == nullptr) ? 0 : node->left->height;
    int rightSubTreeHeight = (node->right == nullptr) ? 0 : node->right->height;

    node->numberOfNodes = 1 + leftSubTreeNodes + rightSubTreeNodes;
    node->height = 1 + max(leftSubTreeHeight, rightSubTreeHeight);
    
    return node;

}

/**
     * @brief Adds a node with the specified key to the tree.
     *
     * @param key The key to be added to the tree.
*/
void BinarySearchTree:: addToTree(int key, DllNode* dllNode) {
    root = insert (root, key);
}

//helper function for deletion(TreeNode* node, int key). This function helps us find the smallest element in the right subtree
TreeNode* getSuccessor(TreeNode* curr) { 
    curr = curr->right;
    while (curr!=nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

//helper function for removeNode(int key). This function allows recursion to take place to allow deletion
TreeNode* deletion(TreeNode* node, int key) { //deleting the chosen node from the tree
    if (node == nullptr) { //the tree is empty
        return node;
    } 

    
    if (key < node-> key) { //remove the left node
        node-> left = deletion(node-> left, key);
    } else if (key > node-> key) { //remove the right node
        node-> right = deletion(node-> right, key);
    } else { //key == node-> key
        //Case 1: leaf node (node with no child)
        if (node-> left == nullptr && node-> right == nullptr) {
            delete node; 
            return nullptr; //node = nullptr to prevent dangling pointer
        }
        //Case 2: node with 1 child
        else if (node-> left == nullptr) { //no left child
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node-> right == nullptr) { //no right child
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } 
        //Case 3: node with 2 children
        else { 
            TreeNode* succ = getSuccessor(node);
            node->key = succ->key;
            node->right = deletion(node->right, succ->key);
        }
    }

    int leftSubTreeNodes = (node->left == nullptr) ? 0 : node->left->numberOfNodes;
    int rightSubTreeNodes = (node->right == nullptr) ? 0 : node->right->numberOfNodes;

   
    int leftSubTreeHeight = (node->left == nullptr) ? 0 : node->left->height; 
    int rightSubTreeHeight = (node->right == nullptr) ? 0 : node->right->height;

    node->numberOfNodes = 1 + leftSubTreeNodes + rightSubTreeNodes;
    node->height = 1 + max(leftSubTreeHeight, rightSubTreeHeight);

    return node;
}

/**
     * @brief Removes a node with the specified key from the tree.
     *
     * @param key The key of the node to remove.
     * @return True if the node was removed, false if the key wasn't found.
*/
bool BinarySearchTree:: removeNode(int key) {
    if (!contains(key)) {
        return false;
    }

    root = deletion(root, key);
    return true;
}

/**
     * @brief Helper function to calculate the height of a node.
     *
     * This function is used by `getHeightOfTree` to calculate the height of the tree.
     *
     * @param node A pointer to the node whose height is to be calculated.
     * @return The height of the given node.
*/
//const functions mean that they this function will not modify the object like do height++ etc. 
int BinarySearchTree:: getHeight(TreeNode* node) const {
    if (node == nullptr) { //base case
        return 0;  //changed to fit the output but usually height of a leaf node = 0 and later we add 1 so -1+1=0
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + max(leftHeight, rightHeight);
}

/**
     * @brief Gets the height of the tree.
     *
     * The height of the tree is defined as the length of the longest path from
     * the root to a leaf node.
     *
     * @return The height of the tree.
*/
int BinarySearchTree:: getHeightOfTree() const {
    return getHeight(root);
}


/**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The number of nodes in the tree.
*/
int BinarySearchTree:: getNumberOfTreeNodes() const {
    return (root == nullptr) ? 0 : root->numberOfNodes; //root is a private datafield in BinarySearchTree header file 
    //root is a TreeNode* so it gives us access to TreeNode class 
}

//helper function for contain. This function searches for the key
bool search(TreeNode* node, int key) {
    //root is null aka the tree is empty and the key we are searching for doesn't exist
    if (node == nullptr) {
        return false;
    }

    if (node-> key == key) { //base case
        return true;
    } else if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }

}

/**
     * @brief Checks if the tree contains a node with the specified key.
     *
     * @param key The key to search for in the tree.
     * @return True if the key exists in the tree, false otherwise.
*/
bool BinarySearchTree:: contains(int key) const {
    return search(root, key);
}

/**
     * @brief Gets the root node of the tree.
     *
     * @return A pointer to the root node of the tree.
*/
TreeNode* BinarySearchTree:: getRoot() const {
    return root; 
}

/**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
*/
bool BinarySearchTree:: isEmpty() const {
    return root == nullptr;
}

/**
     * @brief Deletes the tree starting from the specified node. Helper function for clear()
     *
     * Recursively deletes all nodes in the tree.
     *
     * @param node The starting node to begin deleting the tree.
*/
void BinarySearchTree:: deleteTree(TreeNode* node) {
    if (node == nullptr) { //base case
        return; //used to end the function prematurely cause recursion needs that
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

/**
     * @brief Clears the entire tree.
     *
     * Deletes all the nodes in the tree, freeing up memory.
*/
void BinarySearchTree:: clear() {
    deleteTree(root);
    root = nullptr; //prevent dangling pointers

}


/**
     * @brief Prints the data of a specific node.
     *
     * This function prints the key, number of nodes in the subtree, and height of the given node.
     *
     * @param node A pointer to the node whose data is to be printed.
*/
void BinarySearchTree:: printNodeFromTree(TreeNode* node) const {
    if (node != nullptr) {
        logToFileAndConsole("Node key: " + to_string(node->key));
    }
}

/**
     * @brief Helper function for recursive in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
*/
void BinarySearchTree:: printInOrderHelper(TreeNode* node) const {
    if (node == nullptr) { //base case
        return;
    }
    
    printInOrderHelper(node-> left);
    logToFileAndConsole("Node key: " + to_string(node->key));
    printInOrderHelper(node-> right);

}

/**
     * @brief Performs an in-order traversal of the tree and prints the nodes.
     *
     * In-order traversal visits the left subtree, the node, and then the right subtree.
*/
void BinarySearchTree:: printInOrder() const { //left, node,right
    logToFileAndConsole("");
    logToFileAndConsole("Performing in-order traversal");
    printInOrderHelper(root);

    logToFileAndConsole("End of binary search tree");
}

/**
     * @brief Helper function for recursive reverse in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
*/
void BinarySearchTree:: printReverseOrderHelper(TreeNode* node) const { 
     if (node == nullptr) { //base case
        return;
    }
    
    printReverseOrderHelper(node-> right);
    logToFileAndConsole("Node key: " + to_string(node->key));
    printReverseOrderHelper(node-> left);


}

/**
     * @brief Performs an reverse traversal of the tree and prints the nodes.
     *
     * Reverse traversal visits the right subtree, the node, and then the left subtree.
*/
void BinarySearchTree:: printReverseOrder() const { //right, node, left
    logToFileAndConsole("");
    logToFileAndConsole("Performing reverse-order traversal");
    printReverseOrderHelper(root);

    logToFileAndConsole("End of binary search tree");
}

/**
     * @brief Helper function for recursive pre-order traversal.
     *
     * This function is called recursively to perform a pre-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the pre-order traversal.
*/
void BinarySearchTree:: printPreOrderHelper(TreeNode* node) const {
    if (node == nullptr) { //base case
        return;
    }
    logToFileAndConsole("Node key: " + to_string(node->key));
    printPreOrderHelper(node-> left);
    printPreOrderHelper(node-> right);


}

/**
     * @brief Performs a pre-order traversal of the tree and prints the nodes.
     *
     * Pre-order traversal visits the node, the left subtree, and then the right subtree.
*/
void BinarySearchTree:: printPreOrder() const { //node, left, right
    logToFileAndConsole("Performing Pre-order traversal");
    printPreOrderHelper(root);
}

/**
     * @brief Helper function for recursive post-order traversal.
     *
     * This function is called recursively to perform a post-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the post-order traversal.
*/
void BinarySearchTree:: printPostOrderHelper(TreeNode* node) const {
    if (node == nullptr) { //base case
        return;
    }
    
    printPostOrderHelper(node-> left);
    printPostOrderHelper(node-> right);
    logToFileAndConsole("Node key: " + to_string(node->key));

}

/**
     * @brief Performs a post-order traversal of the tree and prints the nodes.
     *
     * Post-order traversal visits the left subtree, the right subtree, and then the node.
*/
void BinarySearchTree:: printPostOrder() const { //left, right, node
    logToFileAndConsole("Performing Post-order traversal");
    printPostOrderHelper(root);

}

//helper function for printDepthFirst()
void printDepthHelper(TreeNode* node) {
    if (node == nullptr) { //base case
        return;
    }
    logToFileAndConsole("Node key: " + to_string(node->key));
    printDepthHelper(node-> left);
    printDepthHelper(node-> right);

}

/**
     * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
     *
     * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
*/
void BinarySearchTree:: printDepthFirst() const {
    logToFileAndConsole("Performing Depth First via PreOrder traversal");
    logToFileAndConsole("Performing Pre-order traversal");
    printDepthHelper(root);
}


// We create a queue in order to keep track of the memory addresses so that we can use that to go to both the left and right of the same node to complete one level 
void printBreadthFirstHelper(TreeNode* node) {
    if (node == nullptr) { //empty tree case
        return;
    } 
    queue<TreeNode*> Q;
    Q.push(node);
    while(!Q.empty()) {
        TreeNode* current = Q.front();
        logToFileAndConsole("Node key: " + to_string(current->key));
        if (current-> left != NULL) {
            Q.push(current-> left);
        }

        if (current-> right != NULL) {
            Q.push(current-> right);
        }

        Q.pop(); //removing the front element as queue is FIFO (first in, first out)

    }


}


/**
     * @brief Performs a breadth-first traversal of the tree and prints the nodes.
     *
     * Breadth-first traversal visits nodes level by level, from left to right.
*/
void BinarySearchTree:: printBreadthFirst() const {
    logToFileAndConsole("Performing Breadth First traversal");
    printBreadthFirstHelper(root);

}


/**
    *
    * printRangeHelper
    *
    * @brief Helper function to traverse and print out the cache information given a low and high value.
    *
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
*/
void BinarySearchTree:: printRangeHelper(TreeNode* node, int low, int high) {
    if (node == nullptr) { //base case
        return;
    }

    // Only check left subtree if it might contain values >= low
    if (node->key > low) {
        printRangeHelper(node->left, low, high);
    }

    // Print current node if it is in range
    if (node->key >= low && node->key <= high) {
        logToFileAndConsole("Node key: " + to_string(node->key));
    }

    // Only check right subtree if it might contain values <= high
    if (node->key < high) {
        printRangeHelper(node->right, low, high);
    }

}

/**
    *
    * printRange
    *
    * Method to traverse and print out the cache information given a low and high value.
    *
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
*/
void BinarySearchTree:: printRange(int low, int high) {
    logToFileAndConsole("Printing nodes in range [" + to_string(low) + ", " + to_string(high) + "]");
    printRangeHelper(root, low, high);

}







