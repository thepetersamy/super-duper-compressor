#ifndef HUFFMAN_LINKEDLIST_H
#define HUFFMAN_LINKEDLIST_H

struct Node
{
	int frequency;
	char data;
	Node* next, * left, * right;
};

Node* insertSort(Node* h, int frequency, char item)
{
	if (h == NULL)
	{
		h = (Node*)malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = NULL;
		h->left = NULL;
		h->right = NULL;
	}
	else if (frequency < h->frequency)
	{
		Node* tmp = h;
		h = (Node*)malloc(sizeof(Node));
		h->frequency = frequency;
		h->data = item;
		h->next = tmp;
		h->left = NULL;
		h->right = NULL;
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
			it->next->left = NULL;
			it->next->right = NULL;
		}
		else
		{
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->left = NULL;
			tmp->right = NULL;
			tmp->frequency = frequency;
			tmp->data = item;
			tmp->next = it;
			it2->next = tmp;
		}
	}

	return h;
}

Node* findRoot(Node* h)
{
	if (h == NULL)
		return NULL;

	else if (h->next == NULL)
		return h;

	else
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->frequency = h->next->frequency + h->frequency;
		p->data = '\0';
		p->right = h;
		p->left = h->next;
		h = h->next->next;

		if (h == NULL)
		{
			h = p;
			p->next = NULL;
		}
		else if (p->frequency < h->frequency)
		{
			Node* tmp = h;
			h = p;
			h->next = tmp;
		}
		else
		{
			Node* it = h, * it2 = h;
			while (it->frequency <= p->frequency && it->next != NULL)
			{
				it2 = it;
				it = it->next;
			}
			if (it->next == NULL && it->frequency <= p->frequency)
			{
				it->next = p;
				p->next = NULL;
			}
			else
			{
				p->next = it;
				it2->next = p;
			}
		}
		p->left->next = NULL;
		p->right->next = NULL;
		findRoot(h);
	}
}


#endif //HUFFMAN_LINKEDLIST_H
