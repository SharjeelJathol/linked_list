#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// Node structure (internal)
typedef struct Node {
    void* data;              // Pointer to user data
    struct Node* next;       // Pointer to next node
} Node;

// List structure
typedef struct {
    Node* head;              // First node in the list
    Node* tail;              // Last node in the list
    size_t length;           // Number of elements
    size_t data_size;        // Size of each element (in bytes)
} LinkedList;

// Creation and Destruction

LinkedList* list_create(size_t data_size);
void list_destroy(LinkedList* list);

// Basic Operations

void list_push_front(LinkedList* list, const void* data);
void list_push_back(LinkedList* list, const void* data);
void list_pop_front(LinkedList* list);
void list_pop_back(LinkedList* list);

// Accessors

void* list_get(const LinkedList* list, size_t index);
void list_set(LinkedList* list, size_t index, const void* data);

// Utility

size_t list_size(const LinkedList* list);
int list_empty(const LinkedList* list);
void list_clear(LinkedList* list);

// Bonus: Insert / Delete at Index

void list_insert(LinkedList* list, size_t index, const void* data);
void list_delete(LinkedList* list, size_t index);

// Bonus: Print (for debugging)

void list_print_int(const LinkedList* list);      // Print as integers
void list_print_string(const LinkedList* list);   // Print as strings

#endif