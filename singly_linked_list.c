#include "singly_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>      // remove

// constructor
LinkedList* list_create(size_t data_size){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;  // Allocation failed

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->data_size = data_size;

    return list;
}

// destructor
void list_destroy(LinkedList* list){
    if(list) free(list);
    return;
}

// Basic Operations
// add the element to the front of the list
void list_push_front(LinkedList* list, const void* data){
    // check if the list even exists
    if(!list) return;

    // creating new node
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (!new_node) return;  // Allocation failed

    // add new data
    new_node->data = malloc(list->data_size);       // memory allocation
    if (!new_node->data) {
        free(new_node);
        return;  // Allocation failed
    }
    memcpy(new_node->data, data, list->data_size);  // copy data to node memory
    new_node->next = NULL;
    
    if(!list->head){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        new_node->next = list->head;
        list->head = new_node;
    }
    
    list->length+=1;
    new_node = NULL;

    return;
}

// add the element to the end of the list
void list_push_back(LinkedList* list, const void* data){
    // check whether the lists even exists
    if(!list) return;

    // creating new Node
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (!new_node) return;  // Allocation failed

    // add new data
    new_node->data = malloc(list->data_size);   // allocate memory for data   
        if (!new_node->data) {
        return;  // Allocation failed
    }
    memcpy(new_node->data, data, list->data_size);  // copy data to memory
    new_node->next = NULL;

    if(!list->head){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->length+=1;
    new_node = NULL;

    return;
}

// remove the first element
void list_pop_front(LinkedList* list){
    // check whether the list even exists
    if(!list) return;

    // check whether list list is initialized
    if(!list->head) return;

    // TODO: free memory?

    // if only one element, needs to update both head and tail
    if(list->length == 1){
        list->head = NULL;
        list->tail = NULL;
    }
    else{
        // otherwise just move the head one step forward
        list->head = list->head->next;
    }

    // update the length
    list->length--;

    return;
}

// remove the last element
void list_pop_back(LinkedList* list){
    // check whether the list even exists
    if(!list) return;

    // check whether list list is initialized
    if(!list->head) return;

    // reference the head for parsing
    Node* current = list->head;
    Node* prev = NULL;

    // parse until the last element in the list
    while(current->next){
        prev = current;
        current = current->next;
    }

    if(prev == NULL){
        // there was only one element in the list
        list->head = NULL;
        list->tail = NULL;
    }    
    else{
        list->tail = prev;
        prev->next = NULL;
    }

    prev = NULL;
    current = NULL;
    list->length--;

    return;
}

// // Accessors

// get nth element in the linked list
void* list_get(const LinkedList* list, size_t index){
    // check whether the list even exists
    if(!list) return NULL;
    
    // reference the list head for parsing
    Node* temp = list->head;
    
    // check whether list list is initialized
    if(!temp) return NULL;

    // check if the index is within the length range
    if(index >= list->length) return NULL;

    // parse to the target index
    for(size_t i = 0; i < index; i++){
        if(temp->next == NULL) return NULL;
        temp = temp->next;
    }

    return temp->data;
}

// set the nth element in the linked list
void list_set(LinkedList* list, size_t index, const void* data){
    // check whether the list even exists
    if(!list) return;

    // refrence to the head of the list
    Node* temp = list->head;

    // check whether list list is initialized
    if(!temp) return;

    // check if the index is within the length range
    if(index >= list->length - 1) return;

    // parse to the target index
    for(size_t i = 0; i < index; i++){
        if(temp->next == NULL) return;
        temp = temp->next;
    }

    // copying data to the memory
    memcpy(temp->data, data, list->data_size);

    return;
}

// Utility
// return the linked list length
size_t list_size(const LinkedList* list){
    return list->length;
}

// check if the list is empty
int list_empty(const LinkedList* list){
    // check if the list is even initialized
    if(!list) return 1;

    // check if the list has no node
    if(list->length == 0) return 1;

    return 0;
}

// clear the list
void list_clear(LinkedList* list){
    if(!list) return;

    if(!list->head) return;

    list->head = NULL;
    list->tail = NULL;

    return;
}

// Bonus: Insert / Delete at Index

// insert the new element in between the list
void list_insert(LinkedList* list, size_t index, const void* data){
    if(!list) return;

    // pointer to header
    Node* current = list->head;
    Node* prev = NULL;

    if(!current) return;

    // get the pointer of the certain indexed element in the linked list
    for(size_t i = 0; i < index; i++){
        if(index == 0) break;
        if(current->next == NULL) return;
        prev = current;
        current = current->next;   
    }

    // create new node
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (!new_node) return;  // Allocation failed

    // add new data
    new_node->data = malloc(list->data_size);
    if (!new_node->data) {
        free(new_node);
        return;  // Allocation failed
    }
    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;

    // insert the node inbetween
    if(!prev){
        new_node->next = list->head;
        list->head = new_node;
    }
    else{
        prev->next = new_node;
        new_node->next = current;
    }

    current = NULL;
    prev = NULL;
    list->length++;

    return;
}

void list_delete(LinkedList* list, size_t index){
    if(!list) return;

    // pointer to header
    Node* current = list->head;
    Node* prev = NULL;

    if(!current) return;

    // get the pointer of the certain indexed element in the linked list
    for(size_t i = 0; i < index; i++){
        if(index == 0) break;
        if(current->next == NULL) return;
        prev = current;
        current = current->next;   
    }

    // delete the node inbetween
    if(!prev){
        list->head = list->head->next;
    }
    else
        prev->next = current->next;

    current = NULL;
    prev = NULL;
    list->length--;

    return;
}

// // Bonus: Print (for debugging)

// void list_print_int(const LinkedList* list);      // Print as integers
// void list_print_string(const LinkedList* list);   // Print as strings
