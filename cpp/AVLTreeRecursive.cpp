#include <iostream>
#include "queue.h"

/*height, size, isempty, contains, insert(2), update, balance, leftleftcase, leftrightcase
  rightrightcase, rightleftcase, leftrotation, rightrotation, remove(2), findMin, findMax*/

class AVLTreeRecursive{
    private:
        int compared(int i, int j){
            if(i<j) return -1;
            else if(i>j) return 1;
            return 0;
        }

        class Node{
            public:
            Node *left=nullptr;
            Node *right=nullptr;
            int value;
            int bf;
            //balance factor
            int height=0;
            Node(int val){
                value=val;
            }
        };

        Node* TOKEN=new Node(0);

        int nodeCount=0;

        Node *insert(Node* node, int val){
            if(node==nullptr)  return new Node(val);
            int cmp=1;
            cmp = compared(val, node->value);
            if(cmp<0){
                Node* newleftnode=insert(node->left, val);
                if(newleftnode==NULL) return NULL;
                node->left=newleftnode;
            }
            else if(cmp>0){
                Node *newrightnode=insert(node->right, val);
                if(newrightnode==NULL) return NULL;
                node->right=newrightnode;
            }
            else return NULL;

            update(node);
            return balance(node);
        }

        void update(Node* node){
            int leftNodeHeight=(node->left==NULL)?-1: node->left->height;
            int rightNodeHeight=(node->right==NULL)?-1: node->right->height;
            node->height=1+(std::max(leftNodeHeight, rightNodeHeight));
            node->bf=rightNodeHeight-leftNodeHeight;
        }

        Node* balance(Node* node){
            if(node->bf==-2){
                if(node->left->bf<=0)
                    return leftLeftCase(node);
                else
                    return leftRightCase(node);
            }
            else if(node->bf==2){
                if(node->right->bf>=0)
                    return rightRightCase(node);
                else
                    return rightLeftCase(node);
            }
            return node;
        }

        Node *leftLeftCase(Node *node){
            return rightRotation(node);
        }

        Node *leftRightCase(Node* node){
            node->left=leftRotation(node->left);
            return rightRotation(node);
        }

        Node *rightRightCase(Node* node){
            return leftRotation(node);
        }
        
        Node *rightLeftCase(Node* node){
            node->right=rightRotation(node->right);
            return leftRotation(node);
        }
        
        Node *leftRotation(Node *node){
            Node *newParent=node->right;
            node->right=newParent->left;
            newParent->left=node;
            update(node);
            update(newParent);
            return newParent;
        }

        Node *rightRotation(Node *node){
            Node* newParent=node->left;
            node->left=newParent->right;
            newParent->right=node;
            update(node);
            update(newParent);
            return newParent;
        }

        int findMin(Node* node){
            while(node->left!=NULL) node=node->left;
            return node->value;
        }

        int findMax(Node* node){
            while(node->right!=NULL) node=node->right;
            return node->value;
        }
    
        Node *remove(Node *node, int val){
            if(node==NULL) return TOKEN;
            int cmp=compared(val, node->value);

            if(cmp<0){
                Node *node1=remove(node->left, val);
                if(node1==TOKEN) return TOKEN;
                node->left=node1;
            }
            else if(cmp>0){
                Node *node1=remove(node->right, val);
                if(node1==TOKEN) return TOKEN;
                node->right=node1;
            }

            else{
                if(node->left==NULL)
                    return node->right;
                else if(node->right==NULL)
                    return node->left;
                else{
                    int temp=findMin(node->right);
                    node->value=temp;
                    Node* replacement=remove(node->right, temp);
                    if(replacement==TOKEN) return TOKEN;
                    node->right=replacement;
                }
            }
            update(node);
            return balance(node);
        }
    
    public:
        Node *root=NULL;

        int height(){
            if(root==NULL) return 0;
            return root->height;
        }

        int size(){
            return nodeCount;
        }

        bool isEmpty(){
            return size()==0;
        }

        bool contains(int value){
            Node *node=root;
            while(node!=NULL){
                int cmp=compared(value, node->value);
                if(cmp<0)
                    node=node->left;
                else if(cmp>0)
                    node=node->right;
                else
                    return true;
            }
            return false;
        }

        bool insert(int value){
            Node* contain=insert(root, value);
            if(contain!=NULL){
                nodeCount++;
                root=contain;
            }
            return contain!=NULL;
        }

        bool remove(int value){
            Node* Newroot=remove(root, value);
            if(Newroot==NULL) return false;
            root=Newroot;
            nodeCount--;
            return true;
        }

        void levelOrder(){
            Queue<Node*> q;
            q.offer(root);
            while(!(q.isEmpty())){
                Node *temp=q.poll();
                std::cout<<temp->value<<" ";
                if(temp->left!=NULL) q.offer(temp->left);
                if(temp->right!=NULL) q.offer(temp->right);
            }
        }

};

int main(){
    AVLTreeRecursive tree;
    for(int i=1; i<17; i++){
        tree.insert(i);
    }
    tree.remove(4);
    tree.levelOrder();
    return 0;
}