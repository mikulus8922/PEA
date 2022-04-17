#pragma once
#include "BBNode.h"

/// <summary>
/// Struktura opisujaca pojedynczy element
/// kolejki priorytetowej
/// </summary>
struct NodePQ
{
	Node *node;
	NodePQ* next;
	NodePQ* previous;

	NodePQ()
	{
		next = nullptr;
		previous = nullptr;
	}
};


/// <summary>
/// Klasa zawierajaca kolejke priorytetowa
/// </summary>
class PriorityQueue
{
private:
	NodePQ* head;
	NodePQ* tail;

	void pushFront(Node* node);

	void pushBack(Node* node);


public:
	PriorityQueue()
	{
		head = nullptr;
		tail = nullptr;
	}

	~PriorityQueue()
	{
		NodePQ* c = new NodePQ;
		c = head;

		while (c)
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

	/// <summary>
	/// Funkcja dodaj¹ca element w odpowiednie miejsce kolejki priorytetowej
	/// </summary>
	/// <param name="node"></param>
	void push(Node* node);

	/// <summary>
	/// Funkcja usuwajaca pierwszy element kolejki
	/// </summary>
	void pop();

	/// <summary>
	/// Funkcja sprawdzajaca czy kolejka jest pusta
	/// </summary>
	/// <returns></returns>
	bool isEmpty();

	/// <summary>
	/// Funkcja zwracajaca pierwszy element kolejki
	/// </summary>
	/// <returns></returns>
	Node* top();

	/// <summary>
	/// Usuwa z pamieci dane znajdujace sie w nodzie
	/// </summary>
	/// <param name="node"></param>
	void clearMemory(Node* node);
};

