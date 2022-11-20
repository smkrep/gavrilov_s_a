#include "QueueP.h"


bool QueueP::isEmpty() const
{
	return head == nullptr;
}

void QueueP::push(const int& val)
{
	if (isEmpty())
	{
		head = std::make_unique<Node>();
		head->data = val;
		return;
	}

	if (val >= head->data)
	{
		Node* ptr = head.get();


		while (ptr->next != nullptr)
		{
			if (val < ptr->next->data)
			{
				std::unique_ptr<Node> newnode = std::make_unique<Node>(val); // создаем где-то в памяти ноду

				newnode->next = std::move(ptr->next); // перекидываем указатель на след. элемент

				ptr->next = std::move(newnode); // перекидываем указатель на ноду в предыдущий элемент

				break;
			}

		    ptr = ptr->next.get();
		}

		if (ptr->next == nullptr)
		{
			ptr->next = std::make_unique<Node>(val);
		}
	}
	else
	{
		std::unique_ptr<Node> newnode = std::make_unique<Node>(val); // создаем где-то в памяти ноду

		newnode->next = std::move(head);

		head = std::move(newnode);
	}

}
	

int QueueP::pop() 
{
	int value = head->data;
	head = std::move(head->next);
	return value;
}

int QueueP::top() const
{
	return head->data;
}

QueueP::QueueP(const std::vector<int>& values)
{
	for (int i = 0; i < values.size(); i++)
	{
		push(values[i]);
	}
}

QueueP::~QueueP()
{
	while (head != nullptr)
	{
		this->pop();
	}
}

void QueueP::print() const
{
	Node* ptr = head.get();

	while (ptr != nullptr)
	{
		std::cout << ptr->data << " ";
		ptr = ptr->next.get();
	}
	std::cout << "\n";
}



