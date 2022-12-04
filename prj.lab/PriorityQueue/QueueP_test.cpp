#include "QueueP.h"
#include <iostream>
#include <memory>





int main()
{
	std::cout << "QUEUEP TESTS\n\n";

	std::cout << "TESTING PUSH\n";
	QueueP test;
	std::cout << "PUSHING 1\n";
	test.push(1);
	std::cout << "PUSHING 2\n";
	test.push(2);
	std::cout << "PUSHING 3\n";
	test.push(3);
	std::cout << "RESULT:\n";
	test.print();
	std::cout << "\n\n";


	std::cout << "TESTING CONSTRUCTORS\n\n";

	std::vector<int> vec({ 1, 2, 3, 4 });

	std::cout << "CONSTRUCTING WITH VECTOR OF 1 2 3 4\n";
	QueueP test1(vec);
	std::cout << "RESULT:\n";
	test1.print();

}