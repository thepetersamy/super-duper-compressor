#ifndef HUFFMAN_LINKEDLIST_H
#define HUFFMAN_LINKEDLIST_H

struct Node
{
	int frequency;
	char data;
	Node* next;
};

Node* insertSort(Node* h, int frequency, char item)
{
	if (h == NULL)
	{
		h = (Node*)malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = NULL;
	}
	else if (frequency < h->frequency)
	{
		Node* tmp = h;
		h = (Node*)malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = tmp;
	}
	else
	{
		Node* it = h, * it2 = h;
		while (it->frequency <= frequency && it->next != NULL)
		{
			it2 = it;
			it = it->next;
		}
		if (it->next == NULL && it->frequency <= frequency)
		{
			it->next = (Node*)malloc(sizeof(Node));
			it->next->frequency = frequency;
			it->next->data = item;
			it->next->next = NULL;
		}
		else
		{
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->frequency = frequency;
			tmp->data = item;
			tmp->next = it;
			it2->next = tmp;
		}
	}

	return h;
}


Node* removeFirst(Node* h, int* frequency, char* item)
{
	if (h == NULL)
		return NULL;

	else
	{
		*frequency = h->frequency;
		*item = h->data;
		Node* tmp = h->next;
		free(h);
		h = tmp;
	}
	return h;
}


#endif //HUFFMAN_LINKEDLIST_H
