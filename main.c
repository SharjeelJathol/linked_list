#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "singly_linked_list.h"

// ============================================================
// Helper: Print a list of integers
// ============================================================
void print_int_list(LinkedList* list, const char* label) {
    printf("%s: [", label);
    for (size_t i = 0; i < list_size(list); i++) {
        int* val = (int*)list_get(list, i);
        printf("%d", *val);
        if (i < list_size(list) - 1) printf(", ");
    }
    printf("] (size: %zu)\n", list_size(list));
}

// ============================================================
// Helper: Print a list of strings
// ============================================================
void print_string_list(LinkedList* list, const char* label) {
    printf("%s: [", label);
    for (size_t i = 0; i < list_size(list); i++) {
        char** val = (char**)list_get(list, i);
        printf("\"%s\"", *val);
        if (i < list_size(list) - 1) printf(", ");
    }
    printf("] (size: %zu)\n", list_size(list));
}

// ============================================================
// Test 1: Creation and Destruction
// ============================================================
int test_creation_destruction() {
    printf("\n=== Test 1: Creation and Destruction ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    assert(list != NULL);
    assert(list_size(list) == 0);
    assert(list_empty(list) == 1);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    
    list_destroy(list);
    printf("✅ Creation and destruction test passed\n");
    return 1;
}

// ============================================================
// Test 2: Push Front and Pop Front
// ============================================================
int test_push_pop_front() {
    printf("\n=== Test 2: Push Front and Pop Front ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Push front
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        list_push_front(list, &values[i]);
    }
    print_int_list(list, "After push front 50,40,30,20,10");
    printf("Verified");
    assert(list_size(list) == 5);
    
    // Verify order (should be reverse: 50,40,30,20,10)
    int expected[] = {50, 40, 30, 20, 10};
    for (int i = 0; i < 5; i++) {
        int* val = (int*)list_get(list, i);
        assert(*val == expected[i]);
    }
    
    // Pop front
    list_pop_front(list);
    print_int_list(list, "After pop front");
    assert(list_size(list) == 4);
    
    int* first = (int*)list_get(list, 0);
    assert(*first == 40);
    
    // Pop all
    list_pop_front(list);
    list_pop_front(list);
    list_pop_front(list);
    list_pop_front(list);
    print_int_list(list, "After popping all");
    assert(list_size(list) == 0);
    assert(list_empty(list) == 1);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    
    // Pop from empty list (should not crash)
    list_pop_front(list);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Push front and pop front test passed\n");
    return 1;
}

// ============================================================
// Test 3: Push Back and Pop Back
// ============================================================
int test_push_pop_back() {
    printf("\n=== Test 3: Push Back and Pop Back ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Push back
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        list_push_back(list, &values[i]);
    }
    print_int_list(list, "After push back 10,20,30,40,50");
    assert(list_size(list) == 5);
    
    // Verify order
    for (int i = 0; i < 5; i++) {
        int* val = (int*)list_get(list, i);
        assert(*val == values[i]);
    }
    
    // Pop back
    list_pop_back(list);
    print_int_list(list, "After pop back");
    assert(list_size(list) == 4);
    
    int* last = (int*)list_get(list, 3);
    assert(*last == 40);
    
    // Pop all
    list_pop_back(list);
    list_pop_back(list);
    list_pop_back(list);
    list_pop_back(list);
    print_int_list(list, "After popping all");
    assert(list_size(list) == 0);
    assert(list_empty(list) == 1);
    
    // Pop from empty list (should not crash)
    list_pop_back(list);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Push back and pop back test passed\n");
    return 1;
}

// ============================================================
// Test 4: Mixed Push/Pop Operations
// ============================================================
int test_mixed_operations() {
    printf("\n=== Test 4: Mixed Operations ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Push back 10, 20, 30
    int v1 = 10, v2 = 20, v3 = 30;
    list_push_back(list, &v1);
    list_push_back(list, &v2);
    list_push_back(list, &v3);
    print_int_list(list, "After push back 10,20,30");
    
    // Push front 5
    int v4 = 5;
    list_push_front(list, &v4);
    print_int_list(list, "After push front 5");
    assert(list_size(list) == 4);
    
    // Verify: 5,10,20,30
    int expected[] = {5, 10, 20, 30};
    for (int i = 0; i < 4; i++) {
        int* val = (int*)list_get(list, i);
        assert(*val == expected[i]);
    }
    
    // Pop back (should remove 30)
    list_pop_back(list);
    print_int_list(list, "After pop back");
    assert(list_size(list) == 3);
    
    // Pop front (should remove 5)
    list_pop_front(list);
    print_int_list(list, "After pop front");
    assert(list_size(list) == 2);
    
    // Should have 10,20
    int* first = (int*)list_get(list, 0);
    int* last = (int*)list_get(list, 1);
    assert(*first == 10);
    assert(*last == 20);
    
    list_destroy(list);
    printf("✅ Mixed operations test passed\n");
    return 1;
}

// ============================================================
// Test 5: Insert at Index
// ============================================================
int test_insert() {
    printf("\n=== Test 5: Insert at Index ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Insert at beginning when empty
    int val = 10;
    list_insert(list, 0, &val);
    print_int_list(list, "After insert at index 0 (empty list)");
    assert(list_size(list) == 1);
    int* first = (int*)list_get(list, 0);
    assert(*first == 10);
    
    // Insert at beginning (index 0)
    int val2 = 5;
    list_insert(list, 0, &val2);
    print_int_list(list, "After insert at index 0 (beginning)");
    assert(list_size(list) == 2);
    int* new_first = (int*)list_get(list, 0);
    assert(*new_first == 5);
    
    // Insert at end (index = size)
    int val3 = 20;
    list_insert(list, list_size(list), &val3);
    print_int_list(list, "After insert at end");
    assert(list_size(list) == 3);
    int* last = (int*)list_get(list, 2);
    assert(*last == 20);
    
    // Insert in middle
    int val4 = 15;
    list_insert(list, 2, &val4);
    print_int_list(list, "After insert in middle (index 2)");
    assert(list_size(list) == 4);
    
    // Verify: 5,10,15,20
    int expected[] = {5, 10, 15, 20};
    for (int i = 0; i < 4; i++) {
        int* val_ptr = (int*)list_get(list, i);
        assert(*val_ptr == expected[i]);
    }
    
    // Insert at invalid index (should do nothing)
    list_insert(list, 99, &val);
    print_int_list(list, "After invalid insert (index 99) - should not change");
    assert(list_size(list) == 4);
    
    list_destroy(list);
    printf("✅ Insert test passed\n");
    return 1;
}

// ============================================================
// Test 6: Delete at Index
// ============================================================
int test_delete() {
    printf("\n=== Test 6: Delete at Index ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Prepare list: 10,20,30,40,50
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        list_push_back(list, &values[i]);
    }
    print_int_list(list, "Initial list");
    assert(list_size(list) == 5);
    
    // Delete from beginning
    list_delete(list, 0);
    print_int_list(list, "After delete index 0 (beginning)");
    assert(list_size(list) == 4);
    int* first = (int*)list_get(list, 0);
    assert(*first == 20);
    
    // Delete from end
    list_delete(list, list_size(list) - 1);
    print_int_list(list, "After delete end");
    assert(list_size(list) == 3);
    int* last = (int*)list_get(list, 2);
    assert(*last == 40);
    
    // Delete from middle
    list_delete(list, 1);
    print_int_list(list, "After delete middle (index 1)");
    assert(list_size(list) == 2);
    
    // Should have 20,40
    int* first2 = (int*)list_get(list, 0);
    int* last2 = (int*)list_get(list, 1);
    assert(*first2 == 20);
    assert(*last2 == 40);
    
    // Delete invalid index (should do nothing)
    list_delete(list, 99);
    assert(list_size(list) == 2);
    
    // Delete all
    list_delete(list, 0);
    list_delete(list, 0);
    print_int_list(list, "After deleting all");
    assert(list_size(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    
    // Delete from empty list (should not crash)
    list_delete(list, 0);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Delete test passed\n");
    return 1;
}

// ============================================================
// Test 7: Get and Set
// ============================================================
int test_get_set() {
    printf("\n=== Test 7: Get and Set ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Prepare list: 10,20,30,40,50
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        list_push_back(list, &values[i]);
    }
    print_int_list(list, "Initial list");
    
    // Test get
    for (int i = 0; i < 5; i++) {
        int* val = (int*)list_get(list, i);
        assert(*val == values[i]);
    }
    
    // Test get invalid (should return NULL)
    int* invalid = (int*)list_get(list, 99);
    assert(invalid == NULL);
    invalid = (int*)list_get(list, 5);
    assert(invalid == NULL);
    
    // Test set
    int new_val = 99;
    list_set(list, 2, &new_val);
    print_int_list(list, "After set index 2 to 99");
    int* val = (int*)list_get(list, 2);
    assert(*val == 99);
    
    // Set at beginning
    int new_val2 = 5;
    list_set(list, 0, &new_val2);
    print_int_list(list, "After set index 0 to 5");
    int* first = (int*)list_get(list, 0);
    assert(*first == 5);
    
    // Set at end
    int new_val3 = 100;
    list_set(list, 4, &new_val3);
    print_int_list(list, "After set index 4 to 100");
    int* last = (int*)list_get(list, 4);
    assert(*last == 100);
    
    // Set invalid index (should do nothing)
    list_set(list, 99, &new_val);
    assert(list_size(list) == 5);
    
    list_destroy(list);
    printf("✅ Get and set test passed\n");
    return 1;
}

// ============================================================
// Test 8: Clear
// ============================================================
int test_clear() {
    printf("\n=== Test 8: Clear ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Add some elements
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        list_push_back(list, &values[i]);
    }
    print_int_list(list, "Before clear");
    assert(list_size(list) == 3);
    
    // Clear
    list_clear(list);
    print_int_list(list, "After clear");
    assert(list_size(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    
    // Clear empty list (should not crash)
    list_clear(list);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Clear test passed\n");
    return 1;
}

// ============================================================
// Test 9: Strings (Different Data Type)
// ============================================================
int test_strings() {
    printf("\n=== Test 9: Strings ===\n");
    
    LinkedList* list = list_create(sizeof(char*));
    
    char* strings[] = {"Hello", "World", "Linked", "List", "Test"};
    for (int i = 0; i < 5; i++) {
        list_push_back(list, &strings[i]);
    }
    print_string_list(list, "String list");
    assert(list_size(list) == 5);
    
    // Verify
    for (int i = 0; i < 5; i++) {
        char** val = (char**)list_get(list, i);
        assert(strcmp(*val, strings[i]) == 0);
    }
    
    // Insert string
    char* new_str = "Inserted";
    list_insert(list, 2, &new_str);
    print_string_list(list, "After insert at index 2");
    assert(list_size(list) == 6);
    char** val = (char**)list_get(list, 2);
    assert(strcmp(*val, "Inserted") == 0);
    
    // Delete string
    list_delete(list, 3);
    print_string_list(list, "After delete index 3");
    assert(list_size(list) == 5);
    
    // Pop front
    list_pop_front(list);
    print_string_list(list, "After pop front");
    assert(list_size(list) == 4);
    char** first = (char**)list_get(list, 0);
    assert(strcmp(*first, "World") == 0);
    
    // Pop back
    list_pop_back(list);
    print_string_list(list, "After pop back");
    assert(list_size(list) == 3);
    
    list_destroy(list);
    printf("✅ Strings test passed\n");
    return 1;
}

// ============================================================
// Test 10: Stress Test (Large List)
// ============================================================
int test_stress() {
    printf("\n=== Test 10: Stress Test (1000 elements) ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // Push 1000 elements
    for (int i = 0; i < 1000; i++) {
        list_push_back(list, &i);
    }
    assert(list_size(list) == 1000);
    
    // Verify some values
    int* first = (int*)list_get(list, 0);
    assert(*first == 0);
    int* middle = (int*)list_get(list, 500);
    assert(*middle == 500);
    int* last = (int*)list_get(list, 999);
    assert(*last == 999);
    
    // Pop 500 from front
    for (int i = 0; i < 500; i++) {
        list_pop_front(list);
    }
    assert(list_size(list) == 500);
    
    // Verify remaining values
    int* val = (int*)list_get(list, 0);
    assert(*val == 500);
    val = (int*)list_get(list, 499);
    assert(*val == 999);
    
    // Clear rest
    list_clear(list);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Stress test passed\n");
    return 1;
}

// ============================================================
// Test 11: Edge Cases - Empty List Operations
// ============================================================
int test_edge_cases() {
    printf("\n=== Test 11: Edge Cases ===\n");
    
    LinkedList* list = list_create(sizeof(int));
    
    // All operations on empty list should not crash
    list_pop_front(list);
    list_pop_back(list);
    list_insert(list, 0, &(int){10});
    list_delete(list, 0);
    list_clear(list);
    assert(list_size(list) == 0);
    assert(list_get(list, 0) == NULL);
    assert(list_empty(list) == 1);
    
    // Push then delete all
    int val = 42;
    list_push_back(list, &val);
    assert(list_size(list) == 1);
    list_delete(list, 0);
    assert(list_size(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    
    // Push, pop, push again (should work)
    list_push_back(list, &val);
    assert(list_size(list) == 1);
    list_pop_front(list);
    assert(list_size(list) == 0);
    list_push_back(list, &val);
    assert(list_size(list) == 1);
    int* val_ptr = (int*)list_get(list, 0);
    assert(*val_ptr == 42);
    
    list_destroy(list);
    printf("✅ Edge cases test passed\n");
    return 1;
}

// ============================================================
// Test 12: Custom Struct Data Type
// ============================================================
typedef struct {
    int id;
    char name[32];
    float score;
} Student;

int test_structs() {
    printf("\n=== Test 12: Custom Struct Data Type ===\n");
    
    LinkedList* list = list_create(sizeof(Student));
    
    Student students[] = {
        {1, "Alice", 95.5},
        {2, "Bob", 87.3},
        {3, "Charlie", 92.1}
    };
    
    for (int i = 0; i < 3; i++) {
        list_push_back(list, &students[i]);
    }
    assert(list_size(list) == 3);
    
    // Verify
    Student* s = (Student*)list_get(list, 0);
    assert(s->id == 1);
    assert(strcmp(s->name, "Alice") == 0);
    assert(s->score == 95.5);
    
    // Insert
    Student new_student = {4, "Diana", 98.7};
    list_insert(list, 1, &new_student);
    assert(list_size(list) == 4);
    Student* s2 = (Student*)list_get(list, 1);
    assert(s2->id == 4);
    assert(strcmp(s2->name, "Diana") == 0);
    
    // Delete
    list_delete(list, 2);
    assert(list_size(list) == 3);
    Student* s3 = (Student*)list_get(list, 2);
    assert(s3->id == 3);
    assert(strcmp(s3->name, "Charlie") == 0);
    
    // Clear
    list_clear(list);
    assert(list_size(list) == 0);
    
    list_destroy(list);
    printf("✅ Custom struct test passed\n");
    return 1;
}

// ============================================================
// Main - Run All Tests
// ============================================================
int main() {
    printf("===================================================\n");
    printf("      LINKED LIST LIBRARY - COMPREHENSIVE TESTS\n");
    printf("===================================================\n");
    
    int passed = 0;
    int total = 12;
    
    passed += test_creation_destruction();
    passed += test_push_pop_front();
    // passed += test_push_pop_back();
    // passed += test_mixed_operations();
    // passed += test_insert();
    // passed += test_delete();
    // passed += test_get_set();
    // passed += test_clear();
    // passed += test_strings();
    // passed += test_stress();
    // passed += test_edge_cases();
    // passed += test_structs();
    
    printf("\n===================================================\n");
    printf("             TEST RESULTS\n");
    printf("===================================================\n");
    printf("Passed: %d / %d\n", passed, total);
    
    if (passed == total) {
        printf("\n🎉 ALL TESTS PASSED! 🎉\n");
        return 0;
    } else {
        printf("\n❌ SOME TESTS FAILED ❌\n");
        return 1;
    }
}