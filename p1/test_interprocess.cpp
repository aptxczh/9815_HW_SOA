#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 

int main()
{
    //if pass not arguments, run the parent process; if pass no fewer than 1 argument, run the child process
    //Run Parent Process first in order to set the interger. Then run child process to modify and output it.
    int argc =1;
	if (argc == 1) {//Parent Process
		boost::interprocess::shared_memory_object::remove("Shared_Memory");//Remove shared_memory
		boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Shared_Memory", 1024);
		int *i = managed_shm.find_or_construct<int>("Integer")(99);
		std::cout << *i << std::endl;
	}
	else {//Child Process
		boost::interprocess::managed_shared_memory managed_shm2(boost::interprocess::open_or_create, "Shared_Memory", 1024);
		std::pair<int*, std::size_t> p = managed_shm2.find<int>("Integer");
		if (p.first)//if the shared object with name "Integer" exists
			std::cout << (*p.first)+1 << std::endl;//modify and output it
	}
	return 0;
}