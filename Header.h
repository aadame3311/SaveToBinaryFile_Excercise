#include "Car.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Pre-processor directives.
#define RESET_TEXT SetConsoleTextAttribute(hConsole, 7) // Light gray.
#define SET_ERROR_TEXT SetConsoleTextAttribute(hConsole, 4) // Red.
#define SET_SUCCESS_TEXT SetConsoleTextAttribute(hConsole, 2) // Green.
#define SET_WARNING_TEXT SetConsoleTextAttribute(hConsole, 14) // Yellow.
#define SET_NOTICE_TEXT SetConsoleTextAttribute(hConsole, 9) // Blue.


void Print_Options_List(std::list<std::string> opts) {
	for (std::list<std::string>::iterator it = opts.begin(); it != opts.end(); it++) {
		std::cout << *it << std::endl;
	}
}
void Add_Item(std::list<Car>& carList) {
	char name[50];
	int cost, id;

	bool carExists = false;

	do {
		carExists = false;

		// Ask user for car information.
		std::cout << "Enter ID: ";
		std::cin >> id;
		std::cin.ignore();

		std::cout << "Enter Car Name: ";
		std::cin.getline(name, 50);

		std::cout << "Enter Cost: ";
		std::cin >> cost;

		// Check if car ID exists.
		for (std::list<Car>::iterator car = carList.begin(); car != carList.end(); car++) {
			if (car->ID == id) {
				carExists = true;
				SET_WARNING_TEXT;
				std::cout << "Sorry, a car with ID: " << id << " already exists. Please enter another one." << std::endl;
				RESET_TEXT;
				break;
			}
		}
	} while (carExists);

	// Generate car object.
	struct Car car;
	car.ID = id;
	strcpy_s(car.name, name);
	car.price = cost;

	carList.push_back(car);

	SET_SUCCESS_TEXT;
	std::cout << "Car added succesfully!" << std::endl << std::endl;
	RESET_TEXT;


}
void Remove_Item(std::list<Car>& cars) {
	int id;

	std::cout << "Please Enter ID: ";
	std::cin >> id;

	for (std::list<Car>::iterator car = cars.begin(); car != cars.end(); car++) {
		if (car->ID == id) {
			Car& _car = *car;

			SET_SUCCESS_TEXT;
			std::cout << _car.ID << " - " << _car.name;
			SET_WARNING_TEXT;
			std::cout << " has been deleted. Save file to confirm changes. " << std::endl << std::endl;
			RESET_TEXT;

			cars.erase(car);
			return;
		}
	}

	SET_ERROR_TEXT;
	std::cout << "Car with ID: " << id << " is not on the list. " << std::endl << std::endl;
	RESET_TEXT;

	return;
}
void Edit_Item(std::list<Car>& cars) {
	int id;
	int option;
	char name[50];
	int cost;

	std::cout << "Please Enter ID: ";
	std::cin >> id;

	// Ask user which attribute they would like to edit.
	while (true) {
		std::cout << "Which attribute do you wish to edit?: " << std::endl;
		std::cout << "1. name" << std::endl;
		std::cout << "2. cost" << std::endl;
		std::cin >> option;

		if (option < 1 || option > 2) {
			SET_ERROR_TEXT;
			std::cout << "Invalid option. Try again." << std::endl;
			RESET_TEXT;
			continue;
		}
		else {

			for (std::list<Car>::iterator car = cars.begin(); car != cars.end(); car++) {
				if (car->ID == id) {
					Car& _car = *car;

					switch (option) {
					case 1:
						std::cin.ignore();
						std::cout << "Enter the new name: ";
						std::cin.getline(name, 50);
						strcpy_s(_car.name, name);
						break;
					case 2:
						std::cin.ignore();
						std::cout << "Enter the new price for the " << _car.name << ": ";
						std::cin >> cost;
						_car.price = cost;
						break;
					}
				}
			}
			return;
		}

		SET_ERROR_TEXT;
		std::cout << "Car with ID: " << id << " is not on the list. " << std::endl << std::endl;
		RESET_TEXT;

		return;
	}

}

std::list<Car> Read_List_From_File(std::string filename) {

	std::list<Car> carList;
	Car car;
	std::ifstream inFile;
	inFile.open(filename, std::ios::binary);

	if (!inFile.is_open()) {
		SET_ERROR_TEXT;
		std::cout << "Error Opening File: " << filename << " For Reading." << std::endl << std::endl;
		RESET_TEXT;
	}
	else {
		// First item in binary file will always be the amount of cars in the list.
		long int size = 0;
		inFile.read(reinterpret_cast<char*>(&size), sizeof(long int));

		if (size > 0) {
			// Read each car.
			while (inFile.read(reinterpret_cast<char*>(&car), sizeof(Car)))
				carList.push_back(car);

		}
	}
	inFile.close();
	return carList;
}

void Write_List_To_File(std::list<Car> cars, std::string filename)
{
	long int size = cars.size();
	std::ofstream outFile;

	// Open file.
	outFile.open(filename, std::ios::binary);

	// Write the size of the list first.
	outFile.write(reinterpret_cast<char*>(&size), sizeof(long int));

	// Write each list element to the file.
	for (std::list<Car>::iterator car = cars.begin(); car != cars.end(); car++) {
		outFile.write(reinterpret_cast<char*>(&(*car)), sizeof(Car));
	}

	outFile.close();
	return;
}

void Print_List(std::list<Car> _list) {

	// Don't even try to loop if list is empty.
	if (_list.empty()) {
		SET_WARNING_TEXT;
		std::cout << "No cars available. " << std::endl << std::endl;
		RESET_TEXT;
		return;
	}
	else {
		SET_NOTICE_TEXT;
		std::cout << "CarList: " << std::endl;
		RESET_TEXT;
		for (std::list<Car>::iterator it = _list.begin(); it != _list.end(); it++) {
			Car& car = *it;
			SET_SUCCESS_TEXT;
			std::cout << car.ID;
			RESET_TEXT;
			std::cout << " - " << car.name << ": " << car.price << std::endl;
		}

		std::cout << std::endl;
	}


	return;
}
