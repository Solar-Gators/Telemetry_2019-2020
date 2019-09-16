//File Name: rx-module-binary-tree.hpp
//Description: This is a module that implements the receive binary tree where the sorting value is the message identifier

//Header Guards
#ifndef RX_MODULE_BINARY_TREE_H_
#define RX_MODULE_BINARY_TREE_H_

//Include Files
#include "subsystem-info.hpp"
#include "stdint.h" //REMOVE THIS
//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */

//C Public Variables

//C Public Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Forward Declarations
class SUBSYSTEM_DATA_MODULE;
//Class Definitions
// An AVL tree node   
struct Node  
{  
    SUBSYSTEM_DATA_MODULE* datum;  
    Node *left;  
    Node *right;
    uint8_t height;
}; 

class RX_BINARY_TREE
{
public:
    //Constructors
    RX_BINARY_TREE();
    //Public Function Prototypes
    /**
     * @brief This adds a new node of element new_element to the binary tree if there is room left
     * @param new_element: the element to add
     */
    void AddNode(SUBSYSTEM_DATA_MODULE* new_element);
    /**
     * @brief This finds and returns an element that matches the key
     * @param message_id_key: the key to match
     * @return nullptr if can't find element, otherwise a pointer to the element
     */
    SUBSYSTEM_DATA_MODULE* FindElement(uint32_t message_id_key);
    //Public Constants

    //Public Variable
private:
    //Private Variables
    Node treeArray[subsystem_info::NUM_MESSAGES];
    Node* root;
    uint16_t currentTreeSize;

    //Private Function Prototypes

    // This is a recursive method to find the node corresponding to @key
    Node* find(Node* node, uint32_t key);
    // This creates a new node using one of the elements in treeArray
    Node* newNode(SUBSYSTEM_DATA_MODULE* new_element);
    // A utility function to get maximum 
    // of two integers  
    uint32_t max(uint32_t a, uint32_t b);
    // A utility function to get the  
    // height of the tree  
    uint8_t height(Node *N);
    // A utility function to get the  
    // key of a node on the tree  
    uint32_t node_key(Node* N);
    // A utility function to get the  
    // key of a element of the tree 
    uint32_t element_key(SUBSYSTEM_DATA_MODULE* E);
    // A utility function to right 
    // rotate subtree rooted with y  
    // See the diagram given above.  
    Node *rightRotate(Node *y);
    // A utility function to left  
    // rotate subtree rooted with x  
    // See the diagram given above.  
    Node *leftRotate(Node *x); 
    // Get Balance factor of node N  
    int getBalance(Node *N);
    // Recursive function to insert a key 
    // in the subtree rooted with node and 
    // returns the new root of the subtree.  
    Node* insert(Node* node, SUBSYSTEM_DATA_MODULE* new_element);
};
     

   
  
#endif //End Header Guard