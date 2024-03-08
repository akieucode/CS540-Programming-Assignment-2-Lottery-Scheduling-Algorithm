// Lottery Scheduling Algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <random>

// Process class
class Process {
private:
	int processID; // process identifier (unique identifier) 
	int numTickets;	// lottery tickets

public: 
	// constructor, int id and int num_tickets hold values, and passed as parameters in the member variables
	Process(int id, int tickets) : processID(id), numTickets(tickets) {} 
	int getPID() const { // getter function to get process ID
		return processID; // return the processID value  
	}
	int getTickets() const { // getter function to get num of tickets
		return numTickets;
	}
};

// Scheduler class
class Scheduler {
private:
	std::vector<Process> processes; // vector of processes holding instances from Process class
	int systemTotal_tickets = 0; // initialize total of tickets to 0

public:
	// function to add process to the system
	void addProcess(const Process& process) { // takes a constant reference from the Process object as the parameter
		processes.push_back(process); // add new process to the back of vector of existing processes
		int addProcessTickets = process.getTickets(); // get the total number of tickets for a process
		systemTotal_tickets += addProcessTickets; // update the total_tickets in the system
	}

	const std::vector<Process>& getProcesses() const {
		return processes;
	}

	const Process& chooseWinner() { // function that returns the winning process
		int random_num = rand(); // random ticket generator
		int win_ticket = random_num % systemTotal_tickets; // choose ticket from range 0 - total_tickets
		int overall_tickets = 0; //initialize all tickets to 0

		for (const Process& process : processes) { // loop through Process instances in the processes vector
			overall_tickets += process.getTickets(); // get total number of tickets of the process
			if (win_ticket < overall_tickets) {	// conditional statement to check if winning ticket is within the limit
				return process;
			}
		}
	}

	void deleteFront_process() {
		if (!processes.empty()) { // check if the vector is not empty
			int front_process_tickets = processes.front().getTickets(); // get tickets from the front
			systemTotal_tickets -= front_process_tickets; // update total tickets in the system
			processes.erase(processes.begin()); // remove the first element from the vector (front process)
		}
	}
};

	void menu() {
		std::cout << "MENU: " << std::endl;
		std::cout << "1 - Display Current Schedule" << std::endl;
		std::cout << "2 - Add Sample Processes to the Schedule" << std::endl;
		std::cout << "3 - Run the Lottery" << std::endl;
		std::cout << "4 - Remove Front Process" << std::endl;
		std::cout << "5 - Exit" << std::endl;
		std::cout << std::endl;
	}


int main() {

	// implement a random number generator
	srand(time(nullptr)); // seed generator with current time

	// create the process scheduler
	Scheduler process_scheduler;

	menu();

	int select;
	while (true) { // while loop to allow user to continuously make an input
		std::cout << std::endl;
		std::cout << "Please select an option: ";

		std::cin >> select;
		std::cout << std::endl;

		if (select == 1) {
			std::cout << "Current Schedule" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;

			for (const auto& process : process_scheduler.getProcesses()) {
				std::cout << "Process ID: " << process.getPID() << ", Tickets: " << process.getTickets() << std::endl;
				std::cout << std::endl;
			}
		}
		else if (select == 2) {
			// create the processes with process ID, and number of tickets as parameters
			Process process1(1, 2);
			Process process2(2, 5);
			Process process3(3, 3);
			Process process4(4, 1);

			// call the process_scheduler, and add processes to it
			process_scheduler.addProcess(process1);
			process_scheduler.addProcess(process2);
			process_scheduler.addProcess(process3);
			process_scheduler.addProcess(process4);

			std::cout << "Processes Added." << std::endl;
			std::cout << std::endl;
		}
		else if (select == 3) {
			// call function to choose a winner within the process scheduler
			const Process& winner = process_scheduler.chooseWinner();

			// print out winner statement, grab the process ID with getter function and print
			std::cout << "The winner is: Process " << winner.getPID();
			std::cout << std::endl;
			std::cout << std::endl;
		}
		else if (select == 4) {
			process_scheduler.deleteFront_process();
			std::cout << "Front Process Removed." << std::endl;
			std::cout << std::endl;
		}
		else if (select == 5) {
			break;
		}
		else {		// case for when the user enters values that are not available
			std::cin.clear();	// clear the error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the invalid input
			std::cout << "Invalid input. Try again." << std::endl;
			std::cout << std::endl;
		}
		// loop until user selects 5
	}
}