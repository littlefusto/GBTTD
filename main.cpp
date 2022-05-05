#include <iostream>
#include <thread>

void thread_function()
{
	std::cout << std::this_thread::get_id() << "Goodbye, cruel world!" << std::endl;
}

int main()
{
	std::cout << "Hello, World!" << std::endl;
	std::thread thread(&thread_function);
	thread.join();
	return 0;
}
