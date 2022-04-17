#include "TwoWayList.h"
#include <iostream>

//zrobione
void TwoWayList::displayFromFront()
{
	NodeTWL* c = new NodeTWL;
	c = head;

	while (c->next)
	{
		std::cout << c->value << " -> ";
		c = c->next;
	}
	std::cout << c->value;
	std::cout << std::endl;
}

//zrobione
void TwoWayList::displayFromBack()
{
	NodeTWL* c = new NodeTWL;
	c = tail;

	while (c)
	{
		std::cout << c->value << " ";
		c = c->previous;
	}
	std::cout << std::endl;
}

//zrobione
void TwoWayList::pushFront(int value)
{
	NodeTWL* c = new NodeTWL;
	c->value = value;
	c->next = head;

	if (head)
	{
		head->previous = c;
	}
	else tail = c;
	head = c;
}

//zrobione
void TwoWayList::pushBack(int value)
{
	NodeTWL* c = new NodeTWL;
	c->value = value;
	c->previous = tail;

	if (tail)
	{
		tail->next = c;
	}
	else head = c;
	tail = c;
}

//zrobione
void TwoWayList::pushInPosition(int value, int position)
{
	NodeTWL* c = new NodeTWL;
	NodeTWL* p = new NodeTWL;
	NodeTWL* n = new NodeTWL;
	NodeTWL* t = new NodeTWL;
	int current_position = 0;
	t = head;

	if (position == 0)
	{
		pushFront(value);
		return;
	}

	while (current_position < position && t->next)
	{
		t = t->next;
		current_position++;
	}

	if (!t->next)
	{
		pushBack(value);
		return;
	}

	n = t;
	p = t->previous;

	n->previous = c;
	c->next = n;
	c->previous = p;
	p->next = c;
	c->value = value;
}

//zrobione do sprawdzenia
void TwoWayList::popFront()
{
	if (!head && !tail)
		return;
	NodeTWL* c = new NodeTWL;
	NodeTWL* n = new NodeTWL;
	c = head;
	n = c->next;
	if (c->next)
		n->previous = nullptr;
	head = n;
	delete(c);
}

//zrobione do sprawdzenia
void TwoWayList::popBack()
{
	if (!head && !tail)
		return;
	NodeTWL* c = new NodeTWL;
	NodeTWL* p = new NodeTWL;
	c = tail;
	p = c->previous;
	if (c->previous)
		p->next = nullptr;
	tail = p;
	delete(c);
}

//zrobione
void TwoWayList::popInPosition(int position)
{
	if (!head && !tail)
		return;
	NodeTWL* p = new NodeTWL;
	NodeTWL* n = new NodeTWL;
	NodeTWL* t = new NodeTWL;
	int current_position = 0;
	t = head;

	if (position == 0)
	{
		popFront();
		return;
	}

	while (current_position < position && t->next)
	{
		t = t->next;
		current_position++;
	}

	if (!t->next)
	{
		popBack();
		return;
	}

	p = t->previous;
	n = t->next;

	p->next = n;
	n->previous = p;
	delete(t);
}

//zrobione
NodeTWL* TwoWayList::find(int value)
{
	NodeTWL* c = new NodeTWL;
	int current_position = 0;
	c = head;

	while (c)
	{
		if (c->value == value)
		{
			//std::cout << "Znaleziono wartoœæ " << value << " na pozycji: " << current_position << std::endl;
			return c;
		}
		current_position++;
		c = c->next;
	}
	std::cout << "Wartoœæ " << value << " nie istnieje w tej liœcie" << std::endl;
	return nullptr;
}

