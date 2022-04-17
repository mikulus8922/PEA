#include "PriorityQueue.h"
#include <iostream>


void PriorityQueue::displayFromFront()
{
	NodePQ* c = new NodePQ;
	c = head;

	while (c)
	{
		std::cout << c->node->cost << " ";
		c = c->next;
	}
	std::cout << std::endl;
}

void PriorityQueue::pushFront(Node* node)
{
	NodePQ* c = new NodePQ;
	c->node = node;
	c->next = head;

	if (head) {
		head->previous = c;
	}
	else tail = c;
	head = c;
}

void PriorityQueue::pushBack(Node* node)
{
	NodePQ* c = new NodePQ;
	c->node = node;
	c->previous = tail;

	if (tail) {
		tail->next = c;
	}
	else head = c;
	tail = c;
}

void PriorityQueue::push(Node* node)
{

	NodePQ* c = head;
	int current_position = 0;

	if (c == nullptr || c->node->cost > node->cost) {
		pushFront(node);
		//std::cout << "nowy koszt front: " << node->cost << std::endl;
		//displayFromFront();
		return;
	}

	c = c->next;

	while (c != nullptr) {
		if (c->node->cost > node->cost) {
			NodePQ* t = new NodePQ;
			t->node = node;
			NodePQ* p = c->previous;

			t->next = c;
			t->previous = p;
			p->next = t;
			c->previous = t;
			//std::cout << "nowy koszt mid: " << node->cost << std::endl;
			//displayFromFront();
			return;
		}
		c = c->next;
	}
	pushBack(node);
	
}

//zrobione do sprawdzenia
void PriorityQueue::pop()
{
	if (!head && !tail)
		return;
	NodePQ* c = new NodePQ;
	NodePQ* n = new NodePQ;
	c = head;
	n = c->next;
	if (c->next)
		n->previous = nullptr;
	head = n;
	delete(c);
}

bool PriorityQueue::isEmpty()
{
	if (head == nullptr)
		return true;
	return false;
}

Node* PriorityQueue::top()
{
	return head->node;
}

void PriorityQueue::clearMemory(Node* node)
{
	delete node->reducedMatrix;
}
