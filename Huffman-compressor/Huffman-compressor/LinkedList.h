#pragma once
#ifndef HUFFMAN_LINKEDLIST_H
#define HUFFMAN_LINKEDLIST_H

struct Node
{
	int frequency;
	char data;
	Node* next;
};

Node* insertLast(Node* h, int frequency, char item)
{
	if (h == NULL)
	{
		h = (Node*)malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = NULL;
	}
	else
	{
		Node* it = h;
		while (it->next != NULL)
			it = it->next;

		it->next = (Node*)malloc(sizeof(Node));
		it->next->frequency = frequency;
		it->next->data = item;
		it->next->next = NULL;

	}

	return h;
}


Node* removeFirst(Node* h, int* frequency, char* item)
{
	if (h == NULL)
		return NULL;

	if (h->next == NULL)
	{
		*frequency = h->frequency;
		*item = h->data;
		free(h);
		h = NULL;
	}
	else
	{
		Node* tmp = h->next;
		free(h);
		h = tmp;
	}
	return h;
}


#endif //HUFFMAN_LINKEDLIST_H

