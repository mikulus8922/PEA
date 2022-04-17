#pragma once
#include <iostream>

/// <summary>
/// Struktura opisujaca pojedynczy element listy
/// </summary>
struct NodeTWL
{
	int value;
	NodeTWL* next;
	NodeTWL* previous;

	NodeTWL()
	{
		next = nullptr;
		previous = nullptr;
	}
};


/// <summary>
/// Klasa opisujaca liste dwustronna
/// </summary>
class TwoWayList
{
private:
	NodeTWL* head;
	NodeTWL* tail;

public:
	TwoWayList()
	{
		head = nullptr;
		tail = nullptr;
	}

	TwoWayList(const TwoWayList& list) {

		head = nullptr;
		tail = nullptr;

		if (list.head == nullptr)
			return;

		NodeTWL* listNode = list.head;

		while (listNode != nullptr) {
			//std::cout << listNode->value << " ";
			pushBack(listNode->value);
			listNode = listNode->next;
		}
		//std::cout << std::endl;
	}

	~TwoWayList()
	{
		NodeTWL* c = head;

		while (c != nullptr)
		{
			c = head->next;
			delete head;
			head = c;

		}
		head = nullptr;
		tail = nullptr;
		c = nullptr;
	}


	void displayFromFront();

	void displayFromBack();

	void pushFront(int value);

	void pushBack(int value);

	void pushInPosition(int val, int position);

	void popFront();

	void popBack();

	void popInPosition(int position);

	NodeTWL* find(int value);

};

