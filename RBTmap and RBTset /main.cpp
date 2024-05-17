#include <iostream>
#include "BST.cpp"

using namespace std;

template <typename  T , typename K>
class TreeMap{
private:
    class Node{
    public:
        T data;
        K key;
        char color;
        Node* left;
        Node* right;
        Node* parent;

        Node(K key , T data): key(key) , data(data){
            left = right = parent = nullptr;
            color = 'R';
        }


    };
    Node* root;
    bool RR = false;
    bool lrRotation = false;
    bool rlRotation = false;
    bool lRotation = false;
    bool rRotation = false;


    Node* leftRotation(Node* node){
        Node* y = node->right;
        Node* betta = y->left;


        y->left = node;
        node->right = betta;
        if(betta)
            betta->parent = node;

        node->parent = y;

        return y;
    }

    Node* rightRotation(Node* node) {
        Node* y = node->left;
        Node* betta = y->right;


        y->right = node;
        node->left = betta;
        if(betta)
            betta->parent = node;

        node->parent = y;

        return y;
    }

    Node* insert(K key , T data, Node* node){
        if(node == nullptr)
            return new Node(key,data);

        if(key < node->key){
            node->left = insert(key,data,node->left);
            node->left->parent = node;
            if(node != root){
                if(node->left && node->left->color == 'R' && node->color == 'R')
                    RR = true;
            }
        }
        else {
            node->right = insert(key,data ,node->right);
            node->right->parent = node;
            if(node != root ){
                if(node->right && node->right->color == 'R' && node->color == 'R')
                    RR = true;
            }
        }

        if(lrRotation){ /// work

            node->left = leftRotation(node->left);
            node->left->parent = node;

            node = rightRotation(node);

//            if(node->color == 'R') {
            node->color = 'B';
//            }
//            if(node->right) {
//            node->right->color = 'R';
//            }
//            if(node->parent){
            node->parent->color = 'R';
//            }
            lrRotation = false;
        }

        if(rlRotation){  /// work
            node->right = rightRotation(node->right);
            node->right->parent = node;
            node = leftRotation(node);

//            if(node->color == 'R'){
            node->color = 'B';
//            }
//            if(node->right) {
//            node->left->color = 'R';
//            }
//            if(node->parent){
            node->parent->color = 'R';
//            }
            rlRotation = false;
        }

        if(lRotation){ /// work
            node = leftRotation(node);
            node->color = 'B';
//            node->right->color = 'R';
            node->parent->color = 'R';
            lRotation = false;
        }

        if(rRotation){

            node = rightRotation(node);

            node->color = 'B';
//            node->left->color = 'R';
            node->parent->color = 'R';
            rRotation = false;
        }

        if(RR){
            if(node->parent->right == node){
                if(node->parent->left == nullptr || node->parent->left->color == 'B'){ /// uncle = Black
                    if(node->left && node->left->color == 'R' && node->color == 'R'){
                        /// if node = Red and node left child = Red
                        rlRotation = true;
                    }
                    else if(node->right && node->right->color == 'R' && node->color == 'R'){
                        /// if node = Red and node right child = Red
                        lRotation = true;
                    }
                }
                else { ///       uncle = Red
                    //// if node = Red and node right child = Red or if node = Red and node left child = Red
                    node->color = 'B';
                    node->parent->left->color = 'B';
                    if(node->parent != root)
                        node->parent->color ='R';
                }
            }
            else{
                if(node->parent->right == nullptr || node->parent->right->color == 'B'){

                    if(node->right && node->right->color == 'R' && node->color == 'R' && node){
                        /// uncle = Black
                        /// node = Red and node right child = Red
                        lrRotation = true;
                    }
                    else if(node->left && node->left->color == 'R' && node->color == 'R' && node){

                        /// uncle = Black
                        /// node = red and node left child = Red
                        rRotation = true;
                    }
                }
                else {
                    /// uncle = Red
                    //// if node = Red and node right child = Red or if node = Red and node left child = Red
                    node->color = 'B';
                    node->parent->right->color ='B';
                    if(node->parent != root)
                        node->parent->color = 'R';
                }
            }


            RR = false;
        }



        return node;

    }


    static void inorder(Node* node) {
        if(node){
        inorder(node->left);
        if(node->key)
            cout << node->key << " " << node->data << " ";
            if (node->color)
                cout << "color:" << node->color << endl;
            inorder(node->right);
        }
        else {
            return ;
        }
    }


    Node*  search(const K& key) const {
        Node* current = root;
        while (current) {
            if (key == current->key) {
                return current;
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void transplant(Node* k, Node* t) {
        if (k->parent == nullptr)
            root = t;
        else if (k == k->parent->left)
            k->parent->left = t;
        else
            k->parent->right = t;
        if (t != nullptr)
            t->parent = k->parent;
    }

    void delete_fixup(Node* node) {
        while (node != root && node->color == 'B') {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;
                if (sibling->color == 'R') {
                    sibling->color = 'B';
                    node->parent->color = 'R';
                    leftRotation(node->parent);
                    sibling = node->parent->right;
                }
                if (sibling->left->color == 'B' && sibling->right->color == 'B') {
                    sibling->color = 'R';
                    node = node->parent;
                } else {
                    if (sibling->right->color == 'B') {
                        sibling->left->color = 'B';
                        sibling->color = 'R';
                        rightRotation(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = 'B';
                    sibling->right->color = 'B';
                    leftRotation(node->parent);
                    node = root;
                }
            } else {
                // Symmetric case
                Node* sibling = node->parent->left;
                if (sibling->color == 'R') {
                    sibling->color = 'B';
                    node->parent->color = 'R';
                    rightRotation(node->parent);
                    sibling = node->parent->left;
                }
                if (sibling->right->color == 'B' && sibling->left->color == 'B') {
                    sibling->color = 'R';
                    node = node->parent;
                } else {
                    if (sibling->left->color == 'B') {
                        sibling->right->color = 'B';
                        sibling->color = 'R';
                        leftRotation(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = 'B';
                    sibling->left->color = 'B';
                    rightRotation(node->parent);
                    node = root;
                }
            }
        }
        node->color = 'B';
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void remove(K key, Node* node) {
        if (node == nullptr)
            return;

        if (key < node->key)
            remove(key, node->left);
        else if (key > node->key)
            remove(key, node->right);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                if (node->parent == nullptr)
                    root = nullptr;
                else if (node == node->parent->left)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
                delete node;
                delete_fixup(node);
            } else if (node->left && node->right == nullptr) {
                Node* temp = node->left;
                transplant(node, temp);
                temp->color = node->color;
                delete node;
                delete_fixup(temp);
            } else if (node->right && node->left == nullptr) {
                Node* temp = node->right;
                transplant(node, temp);
                temp->color = node->color;
                delete node;
                delete_fixup(temp);
            } else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                remove(temp->key, temp);
            }
        }
    }



public:

    TreeMap() {
        root = nullptr;
    }

    Node * getRoot() const {
        cout<<"root data:"<<root->data;
        cout<<" ";
        cout<<"root color:"<<root->color;
    }
    void insert(K key , T data){
        root = insert(key,data,root);
        root->color = 'B';
    }

    T get(const K& key) const {
        auto node = search(key);
        if (node)
            return node->data;
        else
            return T();
    }

    void remove(K key){
        remove(key,root);
    }

    friend ostream &operator<<(ostream &os, const TreeMap &map) {
        os << "root: " << map.root->key <<" " << map.root->data<<endl;
        os << "items:" << endl;
        inorder(map.root);
        return os;
    }

    T& operator[](const K& key) {
        Node* currentNode = root;
        Node* parentNode = nullptr;

        while (currentNode != nullptr) {
            parentNode = currentNode;
            if (key < currentNode->key) {
                currentNode = currentNode->left;
            } else if (key > currentNode->key) {
                currentNode = currentNode->right;
            } else {
                return currentNode->data;
            }
        }

        Node* newNode = new Node(key, T());
        newNode->parent = parentNode;

        if (parentNode == nullptr) {
            root = newNode;
        } else if (key < parentNode->key) {
            parentNode->left = newNode;
        } else {
            parentNode->right = newNode;
        }


        return newNode->data;
    }



};


template <typename K>
class TreeSet{
private:
    TreeMap<char, K> treeMap;

public:

    void add(const K& key) {
        treeMap.insert(key, ' ');
    }


    void remove(const K& key){
        treeMap.remove(key);
    }

    bool get(const K& key) const {
        return treeMap.get(key) != ' ';
    }


    bool operator[](const K& key) const {
        return get(key);
    }


    friend ostream& operator<<(ostream& os, const TreeSet& set) {
        os<<"root:"<<set.treeMap.getRoot();
        os <<"items:"<<endl;
        os << set.treeMap;
        return os;
    }
};




int main(){
//    TreeMap <string , int> map;
//
//    map.insert(100 , "Erkebulan");
//    map.insert(90 , "Olzhas");
//    map.insert(95,"Zhanarys");
//    map.insert(87,"Damir");
//    map.insert(86 , "Erzhan");
//    map.insert(103,"Islam");
//    map.insert(102,"Ardak");
//    map.insert(109,"Serikbolsyn");
//    map.insert(104,"Albert");
//    map.insert(110,"Damir");
//
//    cout<<endl;
//
//    map.remove(110);
//    map.remove(104);
//    map.remove(109);
//    map.remove(103);
//
//
//
//
//
//
////    map.remove(5);
//
////    cout<<"The method get,we get key = 110: "<<map.get(110)<<endl;
////    cout<<"The method get,we get key = 111: "<<map.get(111)<<endl;
////
////    map[107] = "Didar";
////
////
////    cout << "Value for key 100: " << map[100] << endl;
//
//
//
//    cout << map <<endl;
//
//
//    cout<<" ____________________"<<endl;
//
//
//
//    TreeSet<int> set;
//
//    set.add(5);
//    set.add(3);
//    set.add(8);
//    set.add(19);
//    set.add(12);
//
////
//    set.remove(5);
//////
////    set.remove(8);
//    cout << "Set contains 5: " << set[5] << endl;
//    cout << "Set contains 4: " << set[4] << endl;
//
//    cout << "Set elements: " << set << endl;



    cout <<"____________________________________________________________"<<endl;
    BST <int> tree;


    tree.insert(10);
    tree.insert(8);
    tree.insert(12);
    tree.insert(18);
    tree.insert(7);
    tree.insert(9);

    tree.printAll();


    return 0;



}
