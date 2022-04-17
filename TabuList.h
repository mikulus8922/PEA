#pragma once


struct NodeTabu
{
	int verA;
	int verB;

	NodeTabu* next;
	NodeTabu* previous;

	NodeTabu()
	{
		next = nullptr;
		previous = nullptr;
	}
};


class TabuList
{
private:
	NodeTabu* head = nullptr;
	NodeTabu* tail = nullptr;

	int tabuListMaxSize;
	int tabuListSize;

	void pushFront(NodeTabu* node);
	void pushBack(NodeTabu* node);
	void popFront();

public:
	TabuList(int tabuListMaxSize);
	~TabuList();

	bool contains(int vertexA, int vertexB);
	void insert(int vertexA, int vertexB);
	void clear();

};
