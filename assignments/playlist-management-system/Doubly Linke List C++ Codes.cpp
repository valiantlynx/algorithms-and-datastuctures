#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* next;
    Node* prev;

};
class DLL{
    Node* head;
    Node* tail;
public:
    DLL(){
        head = NULL;
        tail = NULL;
    }
    void addNodeAtFront(int value){
        Node* newNode = new Node();
        newNode->data = value;
        if(head == NULL){
            newNode->next = NULL;
            newNode->prev = NULL;
            head = newNode;
            tail = newNode;
        }
        else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void addNodeAtEnd(int value){
      Node* newNode = new Node();
      newNode->data = value;
      if(tail == NULL){
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        tail = newNode;
      }
      else{
        newNode->next = NULL;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
      }
    }
    void forwardDisplay(){
      Node* tmp = head;
      cout<<"Content of the list in forward direction"<<endl;
      while(tmp!=NULL){
        cout<<tmp->data<<endl;
        tmp = tmp->next;
      }
    }
    void backwardDisplay(){
      Node* tmp = tail;
      cout<<"Content of the list in backward direction"<<endl;
      while(tmp!=NULL){
        cout<<tmp->data<<endl;
        tmp = tmp->prev;
      }
    }
    void search(int key){
        Node* tmp = head;
        int position = 0;
        bool searchResult = false;
        while(tmp != NULL){
            position++;
            if(tmp->data == key){
                cout<<"The node found in the list at position "<<position<<endl;
                searchResult = true;
            }
            tmp = tmp->next;
        }
        if(!searchResult)
            cout<<"The node not exist in the list"<<endl;
    }
    void deleteNode(int key){
       Node* tmp = head;
       while(tmp != NULL){
         if(tmp->data == key && tmp == head){
            tmp->next->prev = NULL;
            head = tmp->next;
            cout<<"The head node found and deleted"<<endl;
         }
         else if(tmp->data == key && tmp == tail){
            tmp->prev->next = NULL;
            tail = tmp->prev;
            cout<<"The last node found and deleted"<<endl;
         }
         else if(tmp->data == key && tmp != head && tmp!=tail){
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            cout<<"The node found and deleted"<<endl;
         }
        tmp = tmp->next;
       }
    }

};
int main(){
    DLL dllObject;
    dllObject.addNodeAtFront(40);
    dllObject.addNodeAtFront(30);
    dllObject.addNodeAtFront(20);
    dllObject.addNodeAtEnd(30);
    dllObject.addNodeAtEnd(60);
    dllObject.forwardDisplay();
    dllObject.backwardDisplay();
    int searchKey = 50;
    dllObject.search(searchKey);
    int deleteKey = 30;
    dllObject.deleteNode(deleteKey);
    dllObject.forwardDisplay();
}

