#include<iostream>
#include "stack.h"
#include "queue.h"

class BinarySearchTree{
    private:
        class Node{
            public:
                Node *left=NULL;
                Node *right=NULL;
                int data=0;
                Node(Node *l, Node *r, int val){
                    left=l;
                    right=r;
                    data=val;
                }
        };

        int nodeCount=0;
        Node *root=NULL;

        int compared(int n1, int n2){
            if(n1<n2) return -1;
            if(n1>n2) return 1;
            return 0;
        }

        bool contains(Node* node, int elem){
            while(node!=NULL){
                int cmp=compared(elem, node->data);
                if(cmp<0)
                    node=node->left;
                else if(cmp>0)
                    node=node->right;
                else
                    return true;
            }
            return false;
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
                    Node *tmp= findMin(node->right);
                    node->data=tmp->data;
                    node->right=remove(node->right, tmp->data);
                }
            }
            return node;
        }

        void preorder_t(Node *node){
            if (node==NULL) return;
            std::cout<<node->data<<" ";
            preorder_t(node->left);
            preorder_t(node->right);
        }

    public:
        int size(){ return nodeCount;}

        bool isEmpty(){ return nodeCount==0;}

        bool contains(int elem){
            return contains(root, elem);
        }

        void add(int elem){
            if(contains(elem)) return;
            root=add(root, elem);
            nodeCount++;
        }

        void remove(int elem){
            remove(root, elem);
        }

        void preorder(){
            Stack<Node*> s;
            s.push(root);
            while(!s.isEmpty()){
                Node *tmp=s.pop();
                std::cout<<tmp->data<<" ";
                if(tmp->right!=NULL) s.push(tmp->right);
                if(tmp->left!=NULL) s.push(tmp->left);
            }
        }

        void inorder(){
            Stack<Node*> stack;
            Node *s=root;
            stack.push(root);
            while(!stack.isEmpty()){
                while(s!=NULL&&s->left!=NULL){
                    stack.push(s->left);
                    s=s->left;
                }
                Node *tmp=stack.pop();
                std::cout<<tmp->data<<" ";
                if(tmp->right!=NULL){
                    stack.push(tmp->right);
                    s=tmp->right;
                }
            }
        }

        void postorder(){
            Stack<Node*> stack1, stack2;
            stack1.push(root);
            while(!stack1.isEmpty()){
                Node *node=stack1.pop();
                if(node!=NULL){
                    stack2.push(node);
                    if(node->left!=NULL) stack1.push(node->left);
                    if(node->right!=NULL) stack1.push(node->right);
                }
            }
            while(!stack2.isEmpty()){
                std::cout<<stack2.pop()->data<<" ";
            }
        }

        void levelorder(){
            Queue<Node*> q;
            q.offer(root);
            while(!q.isEmpty()){
                Node *tmp=q.poll();
                if(tmp->left!=NULL) q.offer(tmp->left);
                if(tmp->right!=NULL) q.offer(tmp->right);
                std::cout<<tmp->data<<" ";
            }
        }
};

int main(){
    BinarySearchTree t;
    for(int i=0; i<5; i++){
        t.add(5-i);
        t.add(5+i);
    }
    std::cout<<"size: "<<t.size();
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