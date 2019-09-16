//File Name: rx-module-binary-tree.hpp
//Description: This is a module that implements the receive binary tree where the sorting value is the message identifier

//Header Guards
#ifndef RX_MODULE_BINARY_TREE_H_
#define RX_MODULE_BINARY_TREE_H_

//Include Files
#include "subsystem-data-module.hpp"
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
//Class Definitions
// An AVL tree node   

template <uint8_t MAX_MESSAGES>
class RX_BINARY_TREE
{
public:
    //Constructors
    RX_BINARY_TREE():
    currentTreeSize{0}, root{nullptr}
    {}
    //Public Function Prototypes
    /**
     * @brief This adds a new node of element new_element to the binary tree if there is room left
     * @param new_element: the element to add
     */
    void AddNode(SUBSYSTEM_DATA_MODULE* new_element)
    {
        //Only insert a node if there is room
        if(currentTreeSize < MAX_MESSAGES)
        {
            root = insert(root,new_element);
        }
    }
    /**
     * @brief This finds and returns an element that matches the key
     * @param message_id_key: the key to match
     * @return nullptr if can't find element, otherwise a pointer to the element
     */
    SUBSYSTEM_DATA_MODULE* FindElement(uint32_t message_id_key)
    {
        Node* foundNode = find(root, message_id_key);
        if(foundNode == nullptr)
        {
            return nullptr;
        }else
        {
            return foundNode->datum;
        }
        
    }
    //Public Constants

    //Public Variable
private:
    //Private Structs
    struct Node  
    {  
        SUBSYSTEM_DATA_MODULE* datum;  
        Node *left;  
        Node *right;
        uint8_t height;
    }; 
    //Private Variables
    Node treeArray[MAX_MESSAGES];
    Node* root;
    uint16_t currentTreeSize;
    //Private Function Prototypes
    Node* find(Node* node, uint32_t key)
    {
        //Can't find node return nullptr
        if(node == nullptr)
        {
            return node;
        }

        if(key < node_key(node))
        {
            return find(node->left,key);
        }else if(key > node_key(node))
        {
            return find(node->right,key);
        }else
        {
            //If key == node_key then return the node
            return node;
        }
        
    }
    Node* newNode(SUBSYSTEM_DATA_MODULE* new_element)
    {
        treeArray[currentTreeSize].datum = new_element;
        treeArray[currentTreeSize].left = nullptr;
        treeArray[currentTreeSize].right = nullptr;
        treeArray[currentTreeSize].height = 1;
        currentTreeSize++;
        return &treeArray[currentTreeSize];
    }
    // A utility function to get maximum 
    // of two integers  
    uint32_t max(uint32_t a, uint32_t b)  
    {  
        return (a > b)? a : b;  
    }  
    // A utility function to get the  
    // height of the tree  
    uint8_t height(Node *N)  
    {  
        if (N == NULL)  
            return 0;  
        return N->height;  
    }
    // A utility function to get the  
    // key of a node on the tree  
    uint32_t node_key(Node* N)
    {
        if(N == nullptr)
            return 0;
        if(N->datum == nullptr)
            return 0;
        return N->datum->messageIdentifier;
    }
    // A utility function to get the  
    // key of a element of the tree 
    uint32_t element_key(SUBSYSTEM_DATA_MODULE* E)
    {
        if(E == nullptr)
            return 0;
        return E->messageIdentifier;  
    }
    // A utility function to right 
    // rotate subtree rooted with y  
    // See the diagram given above.  
    Node *rightRotate(Node *y)  
    {  
        Node *x = y->left;  
        Node *T2 = x->right;  
    
        // Perform rotation  
        x->right = y;  
        y->left = T2;  
    
        // Update heights  
        y->height = max(height(y->left), 
                        height(y->right)) + 1;  
        x->height = max(height(x->left), 
                        height(x->right)) + 1;  
    
        // Return new root  
        return x;  
    } 
    // A utility function to left  
    // rotate subtree rooted with x  
    // See the diagram given above.  
    Node *leftRotate(Node *x)  
    {  
        Node *y = x->right;  
        Node *T2 = y->left;  
    
        // Perform rotation  
        y->left = x;  
        x->right = T2;  
    
        // Update heights  
        x->height = max(height(x->left),     
                        height(x->right)) + 1;  
        y->height = max(height(y->left),  
                        height(y->right)) + 1;  
    
        // Return new root  
        return y;  
    }  
    
    // Get Balance factor of node N  
    int getBalance(Node *N)  
    {  
        if (N == NULL)  
            return 0;  
        return height(N->left) - height(N->right);  
    }  
    
    // Recursive function to insert a key 
    // in the subtree rooted with node and 
    // returns the new root of the subtree.  
    Node* insert(Node* node, SUBSYSTEM_DATA_MODULE* new_element)  
    {  
        /* 1. Perform the normal BST insertion */
        if (node == NULL)  
            return(newNode(key));  
    
        if (element_key(new_element) < node_key(node))  
            node->left = insert(node->left, new_element);  
        else if (element_key(new_element) > node_key(node))  
            node->right = insert(node->right, key);  
        else // Equal keys are not allowed in BST  
            return node;  
    
        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),  
                            height(node->right));  
    
        /* 3. Get the balance factor of this ancestor  
            node to check whether this node became  
            unbalanced */
        int balance = getBalance(node);  
    
        // If this node becomes unbalanced, then  
        // there are 4 cases  
    
        // Left Left Case  
        if (balance > 1 && element_key(new_element) < node_key(node->left))  
            return rightRotate(node);  
    
        // Right Right Case  
        if (balance < -1 && element_key(new_element) > node_key(node->right))  
            return leftRotate(node);  
    
        // Left Right Case  
        if (balance > 1 && element_key(new_element) > node_key(node->left))  
        {  
            node->left = leftRotate(node->left);  
            return rightRotate(node);  
        }  
    
        // Right Left Case  
        if (balance < -1 && element_key(new_element) < node_key(node->right))  
        {  
            node->right = rightRotate(node->right);  
            return leftRotate(node);  
        }  
    
        /* return the (unchanged) node pointer */
        return node;  
    }  
};
     

   
  
#endif //End Header Guard