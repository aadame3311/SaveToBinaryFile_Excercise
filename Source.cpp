#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>   // WinApi header
#include "Header.h"

/////////////////////////////////////////////////////////////////////////////////////
// GOAL:
//	Write a program that presents a list of options to the user.
//	add, remove or edit items from the list based on that option.
//	save data in a binary file.
/////////////////////////////////////////////////////////////////////////////////////

int main() {
	/////////////////////////////////////////////////////////////////
	// open cars.bin for writing to ensure the file always exists.
	std::ofstream file;
	file.open("cars.bin", std::ios::binary|std::ios::app);
	file.close();
	/////////////////////////////////////////////////////////////////

	// Read from file and into our local list<Car> variable.
	std::list<Car> carList = Read_List_From_File("cars.bin");

	// Generate options list.
	unsigned int option = 0;
	std::list<std::string> options;
	options.push_back("1. Add Item");
	options.push_back("2. Delete Item");
	options.push_back("3. Edit Item");
	options.push_back("4. See Items");
	options.push_back("5. Save Items");
	options.push_back("6. Exit");

	// Loop options.
	while (true) {
		//carList = Read_List_From_File("cars.bin");

		// Tell user how many cars are currently in inventory.
		long int size = carList.size();
		std::cout << "Cars in inventory: ";
		SET_SUCCESS_TEXT; 
		std::cout << size << std::endl;
		RESET_TEXT;

		Print_Options_List(options); // Display options.

		std::cout << "Please Enter Your Choice: " << std::flush; 
		std::cin >> option; // Take user input.
		std::cout << std::endl;

		// Do something with input.
		if (option < 1 || option > options.size()) {
			SET_ERROR_TEXT;	
			std::cout << "Invalid Option. Please Try Again." << std::endl << std::endl;
			RESET_TEXT;

			continue;
		}
		else {
			// Process the option selected.
			switch (option) {
			case 1:
				Add_Item(carList); // Add.
				break;
			case 2:
				Remove_Item(carList); // Remove.
				break;
			case 3:
				Edit_Item(carList); // Edit.
				break;
			case 4:
				Print_List(carList);
				break;
			case 5: 
				Write_List_To_File(carList, "cars.bin");
				SET_SUCCESS_TEXT;
				std::cout << "List saved succesfully!" << std::endl << std::endl;
				RESET_TEXT;
				break;
			case 6:
				char saveAns;
				std::cin.ignore();

				SET_NOTICE_TEXT;
				std::cout << "Do you want to save changes made to CarList? (Y/N): ";
				RESET_TEXT;
				std::cin >> saveAns;

				if (saveAns == 'y' || saveAns == 'Y') {
					Write_List_To_File(carList, "cars.bin");
				}

				return 0;
			}
		}
	}


	Write_List_To_File(carList, "cars.bin");
	return 0;
}
