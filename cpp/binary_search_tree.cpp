#include <iostream>
#include <cstdlib>
#include "queue.h"

class BinarySearchTree{
    private:
        class Node{
            public:
                Node *left=NULL, *right=NULL;
                int data=0;
                
                Node(Node* l, Node* r, int val){
                    left=l;
                    right=right;
                    data=val;
                }
        };

        int nodeCount=0;
        Node *root= NULL;

        int compared(int n1, int n2){
            if(n1<n2) return -1;
            else if(n1>n2) return 1;
            else return 0;
        }

        Node* add(Node* node, int elem){
            if(node==NULL)
                node=new Node(NULL, NULL, elem);
            else{
                if(compared(elem, node->data)<0)
                    node->left=add(node->left, elem);
                else
                    node->right=add(node->right, elem);
            }
            return node;
        }

        bool contains(Node* node, int elem){
            if(node==NULL) return false;

            int cmp=compared(elem, node->data);

            if(cmp<0)
                return contains(node->left, elem);
            else if(cmp>0)
                return contains(node->right, elem);
            else
                return true;  
        }

        Node* findMin(Node* node){
            while(node->left!=NULL) node=node->left;
            return node;
        }

        Node* findMax(Node* node){
            while(node->right!=NULL) node=node->right;
            return node;
        }

        Node* remove(Node *node, int elem){
            if(node==NULL) return NULL;

            int cmp=compared(elem, node->data);

            if(cmp<0)
                node->left=remove(node->left, elem);

            else if(cmp>0)
                node->right=remove(node->right, elem);

            else{
                if(node->left==NULL)
                    return node->right;
                else if(node->right==NULL)
                    return node->left;

                else{
                    Node* tmp=findMax(node->left);
                    node->data=tmp->data;
                    node->right=remove(node->right, tmp->data);
                }
            }
            return node;
        }

        int hei(Node* node){
            if(node==NULL) return 0;
            return std::max(hei(node->left), hei(node->right))+1;
        }

        void preorder_t(Node *node){
            if (node==NULL) return;
            std::cout<<node->data<<" ";
            preorder_t(node->left);
            preorder_t(node->right);
        }

        void inorder_t(Node *node){
            if(node==NULL) return;
            inorder_t(node->left);
            std::cout<<node->data<<" ";
            inorder_t(node->right);
        }

        void postorder_t(Node *node){
            if(node==NULL) return;
            postorder_t(node->left);
            postorder_t(node->right);
            std::cout<<node->data<<" ";
        }

        void levelOrder_t(){
            Queue<Node*> q;
            q.offer(root);
            while(!q.isEmpty()){
                Node* node=q.poll();
                if(node->left!=NULL)q.offer(node->left);
                if(node->right!=NULL)q.offer(node->right);
                std::cout<<node->data<<" ";
            }
        }

    public:
        int size(){
            return nodeCount;
        }

        bool isEmpty(){
            return size()==0;
        }

        bool contain(int elem){
            return contains(root, elem);
        }

        bool append(int elem){
            if(contain(elem)) return false;
            root=add(root, elem);
            nodeCount++;
            return true;
        }

        bool remove(int elem){
            if(contain(elem)){
                Node* tmp=remove(root, elem);
                nodeCount--;
                return 1;
            }
            return -1;
        }

        int height(){
            return hei(root);
        }

        void preorder(){
            preorder_t(root);
        }

        void inorder(){
            inorder_t(root);
        }

        void postorder(){
            postorder_t(root);
        }

        void levelorder(){
            levelOrder_t();
        }

};

int main(){
    BinarySearchTree t;
    for(int i=0; i<5; i++){
        t.append(5-i);
        t.append(5+i);
    }
    std::cout<<"height: "<<t.height();
    std::cout<<"\npreorder traversal: ";
    t.preorder();
    std::cout<<"\ninorder traversal: ";
    t.inorder();
    std::cout<<"\npostorder traversal: ";
    t.postorder();
    std::cout<<"\nlevelorder traversal: ";
    t.levelorder();
    return 0;
}