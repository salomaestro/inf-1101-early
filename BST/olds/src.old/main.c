#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "binarysearch.h"

int main(int argc, char **argv)
{
	list_t *list = list_create(compare_char);
	
	for (int arg=1; arg < argc; arg++){
		list_addlast(list, argv[arg]);
	}

	list_print(list, 1, ", ");

	list_node_t *h = list_node_create("hello");
	printf("%s", (char *)h->elem);

	return 0;
	// list_node_t *head = list->head;

	// tree_node_t *root = tree_createnode(head->elem);

	// tree_t *tree = tree_create(compare_char, root);

	// list_iter_t *iter = list_createiter(list);

	// while (list_hasnext(iter)) {
	// 	char *elem = list_next(iter);
	// 	tree_insert(tree, elem);
	// }

	// tree_print(tree);

	return 0;
}
