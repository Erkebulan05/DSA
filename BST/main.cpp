#include <iostream>

using namespace std;

template<typename T>
class BST {
private:
    class Node {
    public:
        T data;
        Node* right;
        Node* left;
        Node(T value, Node* right, Node* left) : data(value), right(right), left(left) {}
    };

    Node* root = nullptr;
    int size = 0;

    void preorder(Node* node) { /// прямой обход
        if (node == nullptr)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) { /// симметричный обход
      if(node == nullptr)
          return;
        inorder(node->left);
        cout<<node->data<<" ";
        inorder(node->right);
    }

    void postorder(Node* node) { /// обратный обход
        if(node==nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout<<node->data<<" ";
    }

    void countNodes(Node* node,int& count) {
        if(node!= nullptr){
            countNodes(node->left,count);
            count++;
            countNodes(node->right,count);
        }
    }


    Node* insert(T data, Node* node) {
     if(node == nullptr)
         return new Node(data,nullptr,nullptr);

     if( data < node->data)
         node->left = insert(data,node->left);
     else
         node->right = insert(data,node->right);


     return node;

    }


//    8 9 3 4 5 6 2 3
//
//                          8
//            3                       9
//       2        4
//             3     5
//                      6

  Node* searchHelper( Node* node , T data){
        if(node== nullptr || data == node->data)
            return node;

        if(data > node->data)
            return searchHelper(node->right , data);
        else
            return searchHelper(node->left , data);
    }


    Node* findMin(Node* node){
        while(node->left !=nullptr){
            node = node->left;
        }
        return node;
    }


    void remove(T data, Node*& node){
        if (node == nullptr) {
            return;
        }

        if (data < node->data) {
            remove(data, node->left);
        } else if (data > node->data) {
            remove(data, node->right);
        } else {
            // Node found, handle different cases
            if (node->left == nullptr && node->right == nullptr) {
                // Case 1: No children
                delete node;
                node = nullptr;

            } else if (node->left == nullptr) {
                // Case 2: One right child
                Node* temp = node;
                node = node->right;
                delete temp;

            } else if (node->right == nullptr) {
                // Case 3: One left child
                Node* temp = node;
                node = node->left;
                delete temp;

            } else {
                // Case 4: Two children
                // Find in-order successor (min value in right subtree)
                Node* successor = findMin(node->right);
                // Replace node's value with successor's value
                node->data = successor->data;
                // Remove only one instance of successor's data
                remove(successor->data, node->right);

            }

        }
    }



public:
    BST() : root(nullptr), size(0) {}

    void preorderTraversal() {
        preorder(root);
    }

    void inorderTraversal() {
        inorder(root);
    }

    void postorderTraversal() {
        postorder(root);
    }



    void insert(T data) {
        root = insert(data,root);
    }

    Node* search(T data) {
        return searchHelper(root,data);
    }


    void remove(T data) {
        remove(data, root);
    }


    bool contains(T data, Node* node){
       if(node == nullptr)
           return false;

       if(data == node->data)
           return true;

       if(data > node->data)
           contains(data,node->right);
       else
           contains(data,node->left);

    }



    Node* getRoot()  {
        return root;
    }

    int length() {
        int count = 0;
        countNodes(root,count);
        return count;
    }

    void printAll() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST<int> tree;
    tree.insert(10);
    tree.insert(7);
    tree.insert(19);
    tree.insert(11);
    tree.insert(8);
    tree.insert(7);
    tree.insert(8);
    tree.insert(7);
    tree.insert(7);
    tree.insert(19);
    tree.insert(10);
    tree.insert(8);
    tree.insert(11);
    tree.insert(16);

    cout << "Tree contains '10': " << (tree.contains(10, tree.getRoot()) ? "true" : "false") << endl;
    cout << "Tree contains 12': " << (tree.contains(12, tree.getRoot()) ? "true" : "false") << endl;




    cout << endl;

    int searchValue = 10;
    auto  foundNode = tree.search(searchValue);
    if (foundNode != nullptr)
        cout << "Found value " << searchValue << " in the tree." << endl;
    else
        cout << "Value " << searchValue << " not found in the tree." << endl;

    searchValue = 15;
    foundNode = tree.search(searchValue);
    if (foundNode != nullptr)
        cout << "Found value " << searchValue << " in the tree." << endl;
    else
        cout << "Value " << searchValue << " not found in the tree." << endl;





//
//    tree.remove(7);
    tree.remove(16);
//    tree.remove(8);
////
//    tree.remove(7);
//    tree.remove(8);
//

    cout << "Tree elements: " << tree.length() << endl;
    cout << "All elements in the tree: ";


    tree.printAll();

    return 0;
}
