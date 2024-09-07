#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* next;
};
class CLL{
    Node* tail;
public:
    CLL(){
        tail = NULL;
    }
    void insertFront(int value){
        Node* newNode = new Node();
        newNode->data = value;
        if(tail == NULL){
            newNode->next = newNode;
            tail = newNode;
        }
        else{
            newNode->next = tail->next;
            tail->next = newNode;
        }
    }
    void insertEnd(int value){
        Node* newNode = new Node();
        newNode->data = value;
        if(tail == NULL){
            newNode->next = newNode;
            tail = newNode;
        }
        else{
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }
    void deleteNode(int key){
        Node* prev = tail;
        Node* current = tail->next;
        while(current!=tail){
            if(current->data == key){
                prev->next = current->next;
                cout<<"Node found and deleted from the list"<<endl;
                delete current;
                return;
            }
            else{
                prev = prev->next;
            }
           current = current->next;
        }
        if(current->data == key){
            prev->next = current->next;
            cout<<"Node deleted from end of the list"<<endl;
            tail = prev;
            return;
        }
    }
    void display(){
        Node* tmp = tail;
        do{
            tmp = tmp->next;
            cout<<tmp->data<<endl;
        }
        while(tmp!=tail);
    }
};
int main(){
    CLL obj;
    obj.insertFront(30);
    obj.insertFront(40);
    obj.insertEnd(100);
    obj.insertEnd(200);
    obj.deleteNode(200);
    obj.display();
}
