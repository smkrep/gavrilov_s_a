#include "QueueP.h"

#include <iostream>
#include <memory>





int main()
{
	std::cout << "ok";

	std::cout << "TEST" << "\n";
	QueueP test;
	test.push(1);
	test.push(2);
	test.push(3);
	test.print();



}