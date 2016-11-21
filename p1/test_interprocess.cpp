///////////////////////////////////////////////////////////////////////////////////////////
///                                 Avinash Oza & Zhihao Chen
///////////////////////////////////////////////////////////////////////////////////////////
// Demonstrates the usage of boost inter process to store and retrieve and integer

#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>
using std::cout;

int main(int argc, char ** argv)
{
    // If no parameters are passed, run the parent process. If any argument is passed, run the child process.
	if (argc == 1) {//Parent Process
		boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Shared_Memory", 1024);
		int *i = managed_shm.find_or_construct<int>("Integer")(99);
		std::cout << "Parent process integer value: " << *i << std::endl;
	}
	else {
        //Child Process
		boost::interprocess::managed_shared_memory managed_shm2(boost::interprocess::open_or_create, "Shared_Memory", 1024);
		std::pair<int*, std::size_t> p = managed_shm2.find<int>("Integer");
		if (p.first) //if the shared object with name "Integer" exists
        {
            std::cout << "Child process integer value + 1: "  <<  (*p.first)+1 << std::endl; //modify and output it
            boost::interprocess::shared_memory_object::remove("Shared_Memory");//Remove shared_memory

        }
        else {
            // show a message letting the user know that nothing is stored.
            std:cout << "There appears to be no value stored " << std::endl;
        }
	}

	return 0;
}