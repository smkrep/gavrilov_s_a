#pragma once
#ifndef QUEUEP
#define QUEUEP

#include <iostream>
#include <memory>
#include <vector>


class QueueP
{
public:
	QueueP()=default;
	QueueP(const std::vector<int>& values);
	~QueueP();
	QueueP(const QueueP& copy);

	void push(const int& value);
	int pop(); 
	int top() const; 
	bool isEmpty() const;
	void print() const;


private:
	struct Node
	{
		Node()=default;
		Node(const int& val)
		{
			data = val;
		}
		int data = 0;
		std::unique_ptr<Node> next = nullptr;
		~Node()=default;

	};

	std::unique_ptr<Node> head = nullptr; 
};

#endif
