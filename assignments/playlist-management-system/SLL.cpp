#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* next;
};
class SLL{
    Node* head;
public:
    SLL(){
        head = NULL;
    }
    void insertFront(int value){
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }
    void insertEnd(int value){
        Node* newNode = new Node();
        if(head == NULL){
            newNode->data = value;
            newNode->next = NULL;
            head = newNode;
        }
        else{
            Node* lastNode = head;
            while(lastNode != NULL){
                if(lastNode->next == NULL){
                    lastNode->next = newNode;
                    newNode->next = NULL;
                    newNode->data = value;
                }
                lastNode = lastNode->next;
            }
        }
    }
    void display(){
        Node* tmp;
        tmp = head;
        while(tmp != NULL){
           cout<<tmp->data<<endl;
           tmp = tmp->next;
        }
    }
    void deleteFront(){
        Node* tmp = head;
        head = tmp->next;
        cout<<"One node deleted from front of the list"<<endl;
        delete tmp;
        return;
    }
    void deleteNode(int key){
        Node* tmp = head;
        if(tmp->data == key){
            head = tmp->next;
            cout<<"A node deleted from front of the list"<<endl;
            delete tmp;
            return;
        }
        while(tmp!=NULL){
            if(tmp->next->data == key){
                Node* tmp2 = tmp->next;
                tmp->next = tmp2->next;
                cout<<"The node found and deleted from the list"<<endl;
                delete tmp2;
                return;
            }
            tmp = tmp->next;
        }
    }
    void search(int key){
        Node* tmp = head;
        while(tmp!=NULL){
            if(tmp->data == key){
                cout<<"the key found in the list"<<endl;
                return;
            }
            tmp = tmp->next;
        }
        cout<<"The key not found in the list"<<endl;
    }
};
int main(){
    SLL object;
    object.insertEnd(200);
    object.insertFront(10);
    object.insertFront(11);
    object.insertFront(12);
    object.deleteFront();
    object.deleteNode(11);
    object.deleteNode(200);
    object.insertEnd(90);
    object.insertEnd(100);
    object.display();
    object.search(19);
}
