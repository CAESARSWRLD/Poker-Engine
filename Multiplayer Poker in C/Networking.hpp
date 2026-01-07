#pragma once
#include <string>


std::string facingBetProcessAnswer(double& betSize);
std::string facingCheckProcessAnswer(double& betSize);

//updates betSize and returns the name of the player action
std::string facingBetProcessAnswer(double& betSize)
{

	//here is where networking should be handled between server and client

	int input = 0;
	while (input != 1 && input != 2 && input != 3)
	{
		std::cout << "Options\n(1)fold\n(2)call $" << betSize << "\n(3)raise\n>";
		std::cin >> input;

	}
	//after the message is recieved from client, process it and validate it

	double raised = 0.00;

	if (input == 1)
	{
		return "fold";

	}
	else if (input == 2)
	{
		return "call";
	}


	


	
	
	while (raised < 2 * betSize)
	{

		//system("cls");
		std::cout << "Raise to how much?\n(must be at least " << 2 * betSize << ")" << "\n>";
		std::cin >> raised;


	}

	return "raise";
	
}

std::string facingCheckProcessAnswer(double& betSize)
{

	//here is where networking should be handled between server and client



	double input = 0;
	while (input != 1 && input != 2)
	{
		std::cout << "Options\n(1)check\n(2)bet\n>";
		std::cin >> input;
	}

	if (input == 2)
	{
		std::cout << "Enter bet size\n>";
		std::cin >> input;
		betSize += input;
		return "bet";
	}

	return "check";

	
}
