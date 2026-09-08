Making something like templates in c++

Function	            What It Does	                    When to Use
list_create	            Creates an empty list	            Before any operations
list_destroy	        Frees all memory	                When you're done with the list
list_push_front	        Adds element at the beginning	    When order doesn't matter, or you want LIFO behavior
list_push_back	        Adds element at the end	            When you want to maintain insertion order (FIFO)
list_pop_front	        Removes first element	            When you want LIFO behavior
list_pop_back	        Removes last element	            When you want to remove from the end
list_get	            Reads data at an index	            When you need to inspect an element
list_set	            Replaces data at an index	        When you need to update an element
list_size	            Returns number of elements	        For loops, validation, debugging
list_empty	            Checks if list is empty	            Before operations that require non-empty list
list_clear	            Removes all elements	            When you want to reuse the list
list_insert	            Inserts at any position	            When you need specific order
list_delete	            Deletes at any position	            When you need to remove a specific element
list_print_int	        Prints as integers	                Debugging integer lists
list_print_string	    Prints as strings	                Debugging string lists