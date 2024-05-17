#include <iostream>
#include <algorithm>

using namespace std;

template <typename T> class AVL{
private:
    class Node{
    public:
        T data;
        int h;
        Node* left;
        Node* right;
        Node(T data):data(data){
            h = 1;
            right = left = nullptr;
        }
    };
    Node *root ;

    int getH(Node* node){
        if(node==nullptr)
            return 0;
        return node->h;
    }
    int getBalanceFactor(Node* node){
        if(node == nullptr)
            return 0 ;
        return getH(node->left) - getH(node->right);
    }
//
//    1
//        2
//            3
    Node* lRotation(Node* node){
        Node* y = node->right;
        Node* betta = y->left;


        y->left = node;
        node->right = betta;


        node->h = 1 + max(getH(node->left), getH(node->right));
        y->h = 1 + max(getH(y->left),getH(y->right));

        return y;
    }
//            6
//        5
//    4
    Node* rRotation(Node* node){
        Node* y = node->left;
        Node* betta = y->right;


        y->right = node;
        node->left = betta;


        node->h = 1 + max(getH(node->left), getH(node->right));
        y->h = 1 + max(getH(y->left),getH(y->right));

        return y;
    }
    Node* insert(T data , Node* node){
        if(node == nullptr)
            return new Node(data);

        if(data > node->data)
            node->right = insert(data,node->right);
        else if(data < node->data)
            node->left = insert(data,node->left);
        else if(node->data == data)
            node->right = insert(data , node->right);


        node->h = 1 + max(getH(node->left),getH(node->left));

        int bf = getBalanceFactor(node);

        if(bf > 1 && data < node->left->data)
            return rRotation(node);
        else if(bf < -1 && data > node->right->data)
            return lRotation(node);
        else if(bf > 1 && data > node->left->data){
            node->left = lRotation(node->left);
            return rRotation(node);
        }
        else if(bf < -1 && data < node->right->data){
            node->right = rRotation(node->right);
            return lRotation(node);
        }

        return node;
    }
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
    void destroy(Node *node) {
        if (node == nullptr)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* remove(T data, Node* node) {
        if (node == nullptr)
            return nullptr;

        if (data < node->data)
            node->left = remove(data, node->left);
        else if (data > node->data)
            node->right = remove(data, node->right);
        else {
            // Node to be deleted found
           if(node->right == nullptr && node->left == nullptr){
               delete node;
               node = nullptr;
            }else if(node->right == nullptr){
               Node* temp = node;
               node =node->left;
               delete temp;
           } else if(node->left == nullptr){
               Node* temp = node;
               node =node->right;
               delete temp;
           }
           else {
                // Node with two children: Get the inorder successor (smallest
                // in the right subtree)
                Node* temp = minValueNode(node->right);

                // Copy the inorder successor's data to this node
                node->data = temp->data;

                // Delete the inorder successor
                node->right = remove(temp->data, node->right);
            }
        }

        // If the tree had only one node, then return
        if (node == nullptr)
            return nullptr;

        // Update height of the current node
        node->h = 1 + max(getH(node->left), getH(node->right));

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int bf = getBalanceFactor(node);

        // If this node becomes unbalanced, there are 4 cases to consider

        // Left Left Case
        if(bf > 1 && data < node->left->data)
            return rRotation(node);

        // Left Right Case
        if(bf > 1 && data > node->left->data){
            node->left = lRotation(node->left);
            return rRotation(node);
        }

        // Right Right Case
        else if(bf < - 1 && data > node->right->data)
            return lRotation(node);

        // Right Left Case
        if(bf < -1 && data < node->right->data){
            node->right = rRotation(node->right);
            return lRotation(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        // loop down to find the leftmost leaf
        while (current->left != nullptr)
            current = current->left;

        return current;
    }


    bool search(T data , Node* node){
        if(node == nullptr)
            return false;

        if(data == node->data)
            return true;
        else if(data> node->data)
            return search(data ,  node->right);
        else if (data < node->data)
            return search(data , node->left);
    }
    Node* searchHelper(T data , Node* node){
        if(node == nullptr)
            return nullptr;

        if(data == node->data)
            return node;
        else if(data> node->data)
            return searchHelper(data ,  node->right);
        else if (data < node->data)
            return searchHelper(data , node->left);
    }
public:
    AVL():root(nullptr){}

    void insert(T data){
        root = insert(data ,root);
    }

    void remove(T data){
        root = remove(data,root);
    }

    bool contains(T data){
        search(data,root);
    }

    Node* search(T data){
        return searchHelper(data,root);
    }

    void printAll(){
        inorder(root);
        cout<<endl;

    }
    Node* getRoot(){
        return root;
    }
    ~AVL() {
        destroy(root);
    }

};

int main() {
    AVL<int> tree;

    // Insert elements into the AVL tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(12);
    tree.insert(15);
    tree.insert(21);
    tree.insert(14);
    tree.insert(10);
    tree.insert(15);
    tree.insert(-1);
    tree.insert(90);
    tree.insert(0);
    tree.insert(-90);

//     Remove elements from the AVL tree
    tree.remove(10);
    tree.remove(20);
    tree.remove(15);
    tree.remove(15);
    tree.remove(10);
    tree.remove(12);
    tree.remove(14);
    tree.remove(21);
    tree.remove(-1);

//
//
//    // Print all elements in the AVL tree (inorder traversal)
    cout << "Elements in the AVL tree after removal: ";
    tree.printAll();

    // Check if the AVL tree contains a specific element
    cout << "Tree contains '10': " << (tree.contains(10) ? "true" : "false") << endl;
    cout << "Tree contains '12': " << (tree.contains(12) ? "true" : "false") << endl;

    // Search for a specific element in the AVL tree
    int numToSearch = 0;
    auto foundNode = tree.search(numToSearch);
    if (foundNode != nullptr) {
        cout << "Found element: " << foundNode->data << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}




 //        1
//            2
//                3
//                    4
//                        5
//
//                     1
//                        2
//                            4
//                        3       5
//
//9
//                        2
//                    1      4
//                        3     5
//                                 9(append)
//
//                             4
//                          2     5
//                       1    3        9

