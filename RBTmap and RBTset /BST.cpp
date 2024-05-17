//
// Created by Еркебулан Шопангали on 04.05.2024.
//
#include "ostream"
#include "iostream"
template <typename T>
class BST {
private:
    class Node{
    public:
        T data;
        Node* left;
        Node* right;
        Node(T data) : data(data){
            left = right = nullptr;
        }
    };
    Node* root;


    Node* insert(T data , Node* node){
        if(node == nullptr)
            return new Node(data);
        if(data < node->data){
            node->left = insert(data,node->left);
        }
        else {
            node->right = insert(data,node->right);
        }

        return node;
    }

    static void inorder(Node* node){
        if(node){
            inorder(node->left);
            std:: cout << node->data << " ";
            inorder(node->right);
        }
        else{
            return ;
        }
    }


public:

    BST(){
        root = nullptr;
    }
    void insert(T data){
        root = insert(data,root);
    }

    void printAll(){
        std:: cout <<"root data:"<<" "<<root->data<<std::endl;
        inorder(root);
        std::cout<<std::endl;
    }
    friend std::ostream& operator<<(std :: ostream& os, const BST& tree) {
        os<<"root data:" <<" "<<tree.root->data<<" "<<std :: endl;
        inorder(tree.root);
        os << std:: endl;
    }
 };