#include "string"
#include "iostream"
#include "Table.hpp"

class DebuggingTool
{
public:
	//const Table& table;

	DebuggingTool(){};

	//returns inputted message. No more std::cout everywhere
	void message(std::string&& message)const
	{
		std::cout << message;
		std::cin.get();
		std::cin.get();

	}

	void weMadeItHere()const
	{
		std::cout << "Made it here!\nPress enter to continue...";
		std::cin.get();
		std::cin.get();

	}

};