#include "TabuList.h"
#include <iostream>


void TabuList::pushFront(NodeTabu* node)
{
	NodeTabu* c = new NodeTabu;
	c->verA = node->verA;
	c->verB = node->verB;
	c->next = head;

	if (head)
	{
		head->previous = c;
	}
	else tail = c;
	head = c;
	tabuListSize++;

	delete node;
}

void TabuList::pushBack(NodeTabu* node)
{
	NodeTabu* c = new NodeTabu;
	c->verA = node->verA;
	c->verB = node->verB;
	c->previous = tail;

	if (tail)
	{
		tail->next = c;
	}
	else head = c;
	tail = c;
	tabuListSize++;

	delete node;
}

void TabuList::popFront()
{
	NodeTabu* c = head;
	if (!head && !tail)
		return;
	if (tabuListSize <= 1) {
		tabuListSize = 0;
		head = nullptr;
		tail = nullptr;
		delete c;
		return;
	}

	head = head->next;
	head->previous = nullptr;
	
	delete c;
	tabuListSize--;
}

TabuList::TabuList(int tabuListMaxSize)
{
	this->tabuListMaxSize = tabuListMaxSize;
}


TabuList::~TabuList()
{
}

bool TabuList::contains(int vertexA, int vertexB)
{
	NodeTabu* n = head;
	bool contains = false;

	while (n) {
		if (n->verA == vertexA && n->verB == vertexB) {
			contains = true;
			break;
		}
		n = n->next;
	}
	return contains;
}

void TabuList::insert(int vertexA, int vertexB)
{
	NodeTabu* cities = new NodeTabu;
	cities->verA = vertexA;
	cities->verB = vertexB;

	if (tabuListSize < tabuListMaxSize)
	{
		pushBack(cities);
	}
	else
	{
		popFront();
		pushBack(cities);
	}
}

void TabuList::clear()
{
	while (tail != nullptr)
		popFront();
}