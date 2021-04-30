#ifndef HUFFMAN_LINKEDLIST_H
#define HUFFMAN_LINKEDLIST_H

typedef struct Node {
	int frequency;
	char data;
	struct Node *next, *left, *right;
}Node;

Node *insertSort(Node *h, int frequency, char item) {

	// if Node is empty
	if (h == NULL) {
		h = (Node *) malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = h->left = h->right = NULL;
	}
	// if current frequency is smaller than frequency of head, insert first
	else if (frequency < h->frequency) {
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->data = item;
		tmp->frequency = frequency;
		tmp->left = tmp->right = NULL;
		tmp->next = h;
		h = tmp;
	}
	else {
		// 2 iterators to place new item in between
		Node *itAfter = h, *itBefore = h;

		while (itAfter->frequency <= frequency && itAfter->next != NULL) {
			itBefore = itAfter;
			itAfter = itAfter->next;
		}
		// insert last
		if (itAfter->next == NULL && itAfter->frequency <= frequency) {
			itAfter->next = (Node *) malloc(sizeof(Node));
			itAfter->next->frequency = frequency;
			itAfter->next->data = item;
			itAfter->next->next = itAfter->next->left = itAfter->next->right = NULL;
		}
		// insert in between
		else {
			Node *tmp = (Node *) malloc(sizeof(Node));
			tmp->left = tmp->right = NULL;
			tmp->frequency = frequency;
			tmp->data = item;
			tmp->next = itAfter;
			itBefore->next = tmp;
		}
	}

	return h;
}

Node *buildHuffmanTree(Node *h) {
	// if isEmpty
	if (h == NULL)
		return NULL;

	// stopping condition
	else if (h->next == NULL)
		return h;

	else {
		Node *p = (Node *) malloc(sizeof(Node)); // create parent node
		p->frequency = h->next->frequency + h->frequency; // init parent with sum of 2 nodes
		p->data = '\0'; // placing NULL at data bc parent it has no data
		// placing first 2 items of priority queue to tree
		p->right = h;
		p->left = h->next;

		h = h->next->next; // changing head to next of next as we just removed 2 nodes

		// if there is no head, place the parent inside it
		if (h == NULL) {
			h = p;
			p->next = NULL;
		}
		// insert first
		else if (p->frequency < h->frequency) {
			Node *tmp = h; // storing old head in tmp
			h = p; // let h point to p(new head)
			h->next = tmp; // let new head point to old head
		}
		// inserting at middle or end
		else {
			Node *itAfter = h, *itBefore = h;
			while (p->frequency > itAfter->frequency  && itAfter->next != NULL) {
				itBefore = itAfter;
				itAfter = itAfter->next;
			}
			// insert last if parent's frequency is the greatest
			if (itAfter->next == NULL && itAfter->frequency <= p->frequency) {
				itAfter->next = p;
				p->next = NULL;
			}
			// else place between the 2 iterators
			else {
				p->next = itAfter;
				itBefore->next = p;
			}
		}
		p->left->next = p->right->next = NULL;

		buildHuffmanTree(h);
	}
}


void printList(Node *head){
	Node *iterator = head;
	while(iterator != NULL){
		printf("%c:%d\t", iterator->data, iterator->frequency);
		iterator = iterator->next;
	}
	printf("\n\n");
}

#endif //HUFFMAN_LINKEDLIST_H
