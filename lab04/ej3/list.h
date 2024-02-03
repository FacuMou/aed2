#include <stdbool.h>

typedef int list_elem;
typedef struct node_t * list;

// Constructors

list empty();
// Returns an empty list

list addl(list l, list_elem e);
// Adds element to head of list

void destroy(list l);
// Clears memory


// Operators

bool is_empty(list l);
// Verifies if the given list is empty

list_elem head(list l);
// Returns the first element of the list

list tail(list l);
// Returns the list without the first element

list addr(list l, list_elem e);
// Adds element at the end of the list

unsigned int length(list l);
// Returns the length of the list

list concat(list l1, list l2);
// Adds all l2 elements at the end of l1

list_elem index(list l, unsigned int i);
// Returns the element in the 'i' position of the list

list take(list l, unsigned int n);
// Leaves in the list the first n elements

list drop(list l, unsigned int n);
// Removes the first n elements of the list

list copy_list(list l);
// Copies all the elements of the list l into a new list