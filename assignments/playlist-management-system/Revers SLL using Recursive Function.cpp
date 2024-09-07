#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* next;
};
class SLL{
public:
    Node* head;
    SLL(){
       head = NULL;
    }
    void addNodeAtFront(int value){
      Node* newNode = new Node();
      newNode->data = value;
      newNode->next = head;
      head = newNode;
    }
    void addNodeAtEnd(int value){
      Node* newNode = new Node();
      newNode->data = value;
      newNode->next = NULL;
      Node* tmp;
      if(head == NULL){
        head = newNode;
        tmp = newNode;
      }
      else{
        tmp = head;
        while(tmp != NULL){
            if(tmp->next == NULL){
                tmp->next = newNode;
                tmp = newNode;
                return;
            }
            tmp = tmp->next;
        }
      }
    }
    void display(){
        Node* tmp = head;
        while(tmp != NULL){
           cout<<tmp->data<<endl;
           tmp = tmp->next;
        }
    }
    void search(int key){
       Node* tmp = head;
       while(tmp!=NULL){
        if(tmp->data == key){
            cout<<"The key found in the list"<<endl;
            return;
        }
        tmp = tmp->next;

       }
       cout<<"The key not found in the list"<<endl;
       return;
    }
    void deleteNode(int key){
      if(head->data == key){
        Node* tmp = head;
        head = tmp->next;
        delete tmp;
        cout<<"The head node deleted from the list"<<endl;
        return;
      }
      else{
        Node* tmp = head;
        while(tmp != NULL){
            if(tmp->next->data == key){
                //If you want to delete the node from the memory, you can add the following lines
                Node* nodeToDelete = tmp->next;
                //tmp->next = tmp->next->next;
                tmp->next = nodeToDelete->next;
                delete nodeToDelete;
                cout<<"The node deleted from the list"<<endl;
                return;
            }
            tmp = tmp->next;
        }
        cout<<"The key not found in the list to be deleted"<<endl;
        return;
      }
    }
    void deleteNodes(int key){
        Node* tmp = head;
        Node* prev = head;
        while(tmp != NULL){
              if(head->data == key){
                head = tmp->next;
                cout<<"The head node deleted from the list"<<endl;
              }
              else{
                    if(tmp->data == key){
                        prev->next = tmp->next;
                        cout<<"The node deleted from the list"<<endl;
                    }
                }
          prev = tmp;
          tmp = tmp->next;
      }
    }
    Node* reversLinkList(Node* tmp){
       if(tmp==NULL){
        return NULL;
       }
       if(tmp->next == NULL){
          head = tmp;
          return tmp;
       }
       Node* node1 = reversLinkList(tmp->next);
       node1->next = tmp;
       tmp->next = NULL;
       return tmp;
    }
};
int main(){
   SLL sllObject;
   sllObject.addNodeAtFront(60);
   sllObject.addNodeAtFront(60);
   sllObject.addNodeAtFront(60);
   sllObject.addNodeAtFront(60);
   sllObject.addNodeAtEnd(80);
   sllObject.display();
   cout<<"After revers"<<endl;
   sllObject.reversLinkList(sllObject.head);
   sllObject.display();
}
