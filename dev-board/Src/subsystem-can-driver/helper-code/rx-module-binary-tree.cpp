//File Name: rx-module-binary-tree.cpp
//Description: This implements the binary tree functions of being able to add and search the tree.

//Include Files
#include "rx-module-binary-tree.hpp"
#include "../subsystem-data-module.hpp"
//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes
RX_BINARY_TREE::RX_BINARY_TREE():
root{nullptr}, currentTreeSize{0}
{}

bool RX_BINARY_TREE::AddNode(SUBSYSTEM_DATA_MODULE* new_element)
{
    //Only insert a node if there is room and we have a valid message id
    if(currentTreeSize < subsystem_info::NUM_MESSAGES && new_element != nullptr)
    {
        root = insert(root,new_element);
        return true;
    }
    return false;
}

SUBSYSTEM_DATA_MODULE* RX_BINARY_TREE::FindElement(uint32_t message_id_key)
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
//Private Function Definitions
Node* RX_BINARY_TREE::find(Node* node, int32_t key)
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

Node* RX_BINARY_TREE::newNode(SUBSYSTEM_DATA_MODULE* new_element)
{
    treeArray[currentTreeSize].datum = new_element;
    treeArray[currentTreeSize].left = nullptr;
    treeArray[currentTreeSize].right = nullptr;
    treeArray[currentTreeSize].height = 1;
    return &treeArray[currentTreeSize++];
}

uint32_t RX_BINARY_TREE::max(uint32_t a, uint32_t b)  
{  
    return (a > b)? a : b;  
}  

bool RX_BINARY_TREE::isValid(int32_t message_id)
{
    return (message_id == RX_BINARY_TREE::INVALID_MESSAGE_ID ? false : true);
}

uint8_t RX_BINARY_TREE::height(Node *N)  
{  
    if (N == nullptr)  
        return 0;  
    return N->height;  
}

int32_t RX_BINARY_TREE::node_key(Node* N)
{
    if(N == nullptr)
        return RX_BINARY_TREE::INVALID_MESSAGE_ID;
    if(N->datum == nullptr)
        return RX_BINARY_TREE::INVALID_MESSAGE_ID;
    return N->datum->messageIdentifier;
}

int32_t RX_BINARY_TREE::element_key(SUBSYSTEM_DATA_MODULE* E)
{
    if(E == nullptr)
        return RX_BINARY_TREE::INVALID_MESSAGE_ID;
    return E->messageIdentifier;  
}
  
Node* RX_BINARY_TREE::rightRotate(Node *y)  
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

Node* RX_BINARY_TREE::leftRotate(Node *x)  
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
 
int RX_BINARY_TREE::getBalance(Node *N)  
{  
    if (N == nullptr)  
        return 0;  
    return height(N->left) - height(N->right);  
}  

Node* RX_BINARY_TREE::insert(Node* node, SUBSYSTEM_DATA_MODULE* new_element)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)  
        return(newNode(new_element));  

    
    if (element_key(new_element) < node_key(node))  
        node->left = insert(node->left, new_element);  
    else if (element_key(new_element) > node_key(node))  
        node->right = insert(node->right, new_element);  
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
//Public Function Definitions
