#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "Clear.h" // Holding clear function
#include <array>
#include <conio.h>
#include <math.h>
#include <vector>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int unlocks = 2;

int prices[5]{5, 10, 500, 10000, 1000000}; // per 1 unit

string NewGame() {
	string file; // input for file selection
	string line;
	fstream File_Names("File_Names.txt"); // opening file names file

	bool check = true;

	do {
		check = true;
		cout << "What should the file be saved as: ";
		cin >> file; // getting the name of the new file

		while (getline(File_Names, line)) { // loop over each file name
			if (line == file) { // check if the name already exists
				check = false;
			}
		}
		File_Names.close();

		if (check == true) {
			fstream File_Names("File_Names.txt", ios::out | ios::app); // opening file names file
			File_Names << endl << file; // writing the name of the new file in the file names file for future use
			File_Names.close();

			/* file layout
			Current$
			Picklvl
			Miners
			Trucks
			Dinamite
			Nukes
			FullPower
			*/

			ofstream New_File(file); // creating file with inputed name
			New_File << "0\n1\n1\n0\n0\n0\n0";

			cout << "Welcome to Mining Mania!\n\n" << "This game requires no skill, just patience and CPU power.\n" << "The aim of the game is to mine the most gold as you possibly can.\n";
			cout << "Have fun and just let it run.";
			Sleep(10000); // wait ten seconds to read
		}
		else { cout << "File already exists\n"; }
	} while (check == false);
	return file;
}
string LoadGame() {

	clear();

	string file;
	string line;
	vector<string> fileList;

	fstream File_Names("File_Names.txt"); // oppening the file Names file

	if (File_Names.is_open()) { // Checking if the file is open
		while (getline(File_Names, line)) { // looping over the lines
			fileList.push_back(line); // create vector of the file names
		}
	}
	else { cout << "Could not access saves\n"; } // if the file couldn't be found

	bool LoadGameLoop = true;
	int select = 0;

	while (LoadGameLoop == true) {
		
		for (int i = 0; i < fileList.size(); i++) { // looping over the lines
			if (i == select) {
				SetConsoleTextAttribute(console, 112);
			}
			cout << fileList[i] << endl; // output current line
			SetConsoleTextAttribute(console, 15);
		}
		
		if (_kbhit()) {

			int keyPressed = _getch();

			if (keyPressed == 13) {
				file = line;
				LoadGameLoop = false;
			}
			else if (keyPressed == 72) {
				if (select == 0) {
					select = (fileList.size());
				}
				select--;
			}
			else if (keyPressed == 80) {
				select++;
				if (select == (fileList.size())) {
					select = 0;
				}
					
			}
		}
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(console, cursorPos);
		File_Names.seekg(0);
	}
	File_Names.close();
	return file;
}
void Print(string OpenFile, int upgradeSelect) {
	array<double, 7>info; // fancy array to pass into another function
	string line;

	fstream File(OpenFile);

	for (int i = 0; i <= 7; i++) { // transfering characters from the file into numbers
		getline(File, line);
		if (i == 0) { info[i] = stod(line); }
		if (i == 1) { info[i] = stod(line); }
		if (i == 2) { info[i] = stod(line); }
		if (i == 3) { info[i] = stod(line); }
		if (i == 4) { info[i] = stod(line); }
		if (i == 5) { info[i] = stod(line); }
		if (i == 6) { info[i] = stod(line); }
	}
	File.close();

	// printing current info

	cout << "Current $: " << info[0] << "\n\n";
	if (upgradeSelect == 1) { SetConsoleTextAttribute(console, 112); }
	cout << "Picklvl: " << info[1] << endl << "Cost: $" << prices[0] << "\n\n";
	SetConsoleTextAttribute(console, 15);

	if (upgradeSelect == 2) { SetConsoleTextAttribute(console, 112); }
	cout << "Miners: " << info[2] << endl << "Cost: $" << prices[1] << "\n\n";
	SetConsoleTextAttribute(console, 15);

	if (upgradeSelect == 3) { SetConsoleTextAttribute(console, 112); }
	if (info[1] < 10) {
		cout << "Trucks: " << "Locked until picklvl 10\n\n";
	}
	else {
		cout << "Trucks: " << info[3] << endl << "Cost: $" << prices[2] << "\n\n";
		unlocks = 3;
	}
	SetConsoleTextAttribute(console, 15);

	if (upgradeSelect == 4) { SetConsoleTextAttribute(console, 112); }
	if (info[1] < 50) {
		cout << "Dynamite: " << "Locked until picklvl 50\n\n";
	}
	else {
		cout << "Dynamite: " << info[4] << endl << "Cost: $" << prices[3] << "\n\n";
		unlocks = 4;
	}
	SetConsoleTextAttribute(console, 15);

	if (upgradeSelect == 5) { SetConsoleTextAttribute(console, 112); }
	if (info[1] < 100) {
		cout << "Nukes: " << "Locked until picklvl 100\n\n";
	}
	else {
		cout << "Nukes: " << info[5] << endl << "Cost: $" << prices[4] << "\n\n";
		unlocks = 5;
	}
	SetConsoleTextAttribute(console, 15);

	if (upgradeSelect == 6) { SetConsoleTextAttribute(console, 112); }
	if (info[1] < 1000) {
		cout << "FullPower: " << "Locked until picklvl 1000\n\n";
	}
	else {
		cout << "FullPower: " << info[6] << endl << "Cost: $" << prices[5] << "\n\n";
		unlocks = 6;
	}
	SetConsoleTextAttribute(console, 15);

}
void Write(string OpenFile, array<double, 7>info) { // function to save to external save file
	fstream File;
	File.open(OpenFile, fstream::trunc);

	for (int i = 0; i < 7; i++) {
		File << info[i] << endl;
	}
	File.close();
}
void Shop(string OpenFile) {
	array<double, 7>info; // {Current$, Picklvl, Miners, Trucks, Dinamite, Nukes, FullPower}
	string input;
	string upgrade;
	int amount;
	string line;
	bool shop_loop = true;

	while (shop_loop == true) {
		clear();
		fstream File(OpenFile);
		int upgradeSelect = 0;

		for (int i = 0; i < 7; i++) {
			getline(File, line);
			if (i == 0) { info[i] = stod(line); } // Current$
			if (i == 1) { info[i] = stod(line); } // Picklvl
			if (i == 2) { info[i] = stod(line); } // Miners
			if (i == 3) { info[i] = stod(line); } // Trucks
			if (i == 4) { info[i] = stod(line); } // Dinamite
			if (i == 5) { info[i] = stod(line); } // Nukes
			if (i == 6) { info[i] = stod(line); } // FullPower
		}
		File.close();

		Print(OpenFile, upgradeSelect);

		bool mainMenuLoop = true;
		int select = 0;
		while (mainMenuLoop == true) {

			COORD cursorPos = { 0, 19 };

			if (select == 0) {
				SetConsoleCursorPosition(console, cursorPos);
				cout << "Would you like to ";
				SetConsoleTextAttribute(console, 112);
				cout << "UPGRADE";
				SetConsoleTextAttribute(console, 15);
				cout << " or go MINE";
			}
			else if (select == 1) {
				SetConsoleCursorPosition(console, cursorPos);
				cout << "Would you like to UPGRADE or go ";
				SetConsoleTextAttribute(console, 112);
				cout << "MINE";
				SetConsoleTextAttribute(console, 15);
			}

			if (_kbhit()) {

				int keyPressed = _getch();
				// cout << endl << keyPressed;

				if (keyPressed == 13) {
					mainMenuLoop = false;
				}
				else if (keyPressed == 75 || keyPressed == 77) {
					if (select == 0) {
						select = 1;
					}
					else if (select == 1) {
						select = 0;
					}
				}
			}
		}

		if (select == 0) { // upgrade screen
			bool upgrade_loop = true;

			clear();

			bool upgradeChoiceLoop = true;
			int upgradeSelect = 1;
			while (upgradeChoiceLoop == true) {
				Print(OpenFile, upgradeSelect);

				if (_kbhit()) {

					int keyPressed = _getch();
					// cout << keyPressed;

					if (keyPressed == 13) {
						upgradeChoiceLoop = false;
					}
					else if (keyPressed == 72) {
						if (upgradeSelect == 1) {
							upgradeSelect = (unlocks + 1);
						}
						upgradeSelect--;
					}
					else if (keyPressed == 80) {
						upgradeSelect++;
						if (upgradeSelect == (unlocks + 1)) {
							upgradeSelect = 1;
						}

					}
				}

				cout << "What would you like to upgrade? ";
				COORD cursorPos = { 0, 0 };
				SetConsoleCursorPosition(console, cursorPos);
			}

			clear();
			int maxUpgrade;
			int upgradeAmountLoop = true;
			select = 0;

			prices[0] = (5 * pow(info[1], 2)); // picklvl
			prices[1] = (10 * pow(info[2], 2)); // miners
			prices[2] = (500 * pow(info[3] + 1, 2.5)); // trucks
			prices[3] = (10000 * pow(info[4] + 1, 2.5)); // dynamite
			prices[4] = (1000000 * pow(info[5] + 1, 2.5)); // nukes
			prices[5] = 1000000000; // full power

			while (upgradeAmountLoop == true) {
				maxUpgrade = (info[0] / prices[upgradeSelect - 1]);
				if (select == 0) {
					cout << "How much do you want to upgrade by?\n\n\t\t\t";
					SetConsoleTextAttribute(console, 112);
					cout << "Max Amout:" << maxUpgrade;
					SetConsoleTextAttribute(console, 15);
					cout << "\t\t\tCustom Amount";
				}
				else if (select == 1) {
					cout << "How much do you want to upgrade by?\n\n" << "\t\t\tMax Amount: " << maxUpgrade << "\t\t\t";
					SetConsoleTextAttribute(console, 112);
					cout << "Custom Amount";
					SetConsoleTextAttribute(console, 15);
				}

				if (_kbhit()) {

					int keyPressed = _getch();
					// cout << endl << keyPressed;

					if (keyPressed == 13) {
						upgradeAmountLoop = false;
					}
					else if (keyPressed == 75 || keyPressed == 77) {
						if (select == 0) {
							select = 1;
						}
						else if (select == 1) {
							select = 0;
						}
					}
				}

				COORD cursorPos = { 0, 0 };
				SetConsoleCursorPosition(console, cursorPos);
			}
			
			clear();

			if (select == 0) {
				amount = maxUpgrade;
			}
			else if (select == 1) {
				cout << "Enter amount you would like to upgrade: ";
				cin >> amount;
			}

			if (upgradeSelect == 1 && (info[0] >= (prices[0] * amount))) { // picklvl
				info[0] -= (prices[0] * amount);
				info[1] += amount;
			}
			else if (upgradeSelect == 2 && (info[0] >= (prices[1] * amount))) { // miners
				info[0] -= (amount * prices[1]);
				info[2] += amount;
			}
			else if (upgradeSelect == 3 && (info[0] >= (prices[2] * amount))) { // trucks
				info[0] -= (amount * prices[2]);
				info[3] += amount;
			}
			else if (upgradeSelect == 4 && (info[0] >= (prices[3] * amount))) { // dynamite
				info[0] -= (amount * prices[3]);
				info[4] += amount;
			}
			else if (upgradeSelect == 5 && (info[0] >= (prices[4] * amount))) { // nukes
				info[0] -= (amount * prices[4]);
				info[5] += amount;
			}
			else if (upgradeSelect == 6 && (info[0] >= (prices[5] * amount))) { // full power
				info[0] -= (amount * prices[5]);
				info[6] += amount;
			}
			else {
				cout << "\nCould not upgrade\n\n"; // error if incorect input or not enough money
			}
			fstream File(OpenFile);
			for (int i = 0; i < 7; i++) {
				File << info[i] << endl;
			}
			File.close();
		}
		else if (select == 1) {
			double MPS = (1 + (info[1] / 20)) * ((1 + info[2]/10) + (info[3]) + (50 * info[4]) + (1000 * info[5])); // calculating money per second
			bool mine_loop = true;
			int cycles = 0;

			clear();

			cout << "			Current Money: $" << info[0] << "			Money per second: " << MPS << endl;
			cout << "Press any key to return to the upgrade screen";

			while (mine_loop == true) {
				if (info[6] == 0) {
					if (_kbhit()) { // checking if a key was hit
						_getch();
						mine_loop = false;
					}
					else { // if not, wait 10 ms
						Sleep(10);
					}

					COORD cursorPos = { 40, 0 };
					SetConsoleCursorPosition(console, cursorPos);
					info[0] += MPS / 100;
					cout << info[0];
					cycles = 0;
				}
				else if (info[6] > 0) { // if player has a full power upgrade, take out sleep function
					if (_kbhit()) {
						_getch();
						mine_loop = false;
					}
					else {
						info[0] += ((1 + (info[1] / 20)) * ((info[2]) + (5 * info[3]) + (50 * info[4]) + (1000 * info[5])) * info[6]);
						cycles++;
					}

					if (cycles == 10000) {
						clear();
						cout << "			Current Money: $" << info[0] << endl;
						cout << "Press any key to return to the upgrade screen";
						cycles = 0;
					}
				}
			}
			fstream File(OpenFile);
			for (int i = 0; i < 7; i++) {
				File << info[i] << endl;
			}
			File.close();
		}
	}
}
int main() {
	string input;
	string OpenFile;
	string line;
	bool check = false;
	int select = 0;
	int cycles = 0;
	int frame = 1;

	// make the cursor invisible
	bool visible = false;
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	do {

		COORD cursorPos = { 0, 2 };
		SetConsoleCursorPosition(console, cursorPos);

		fstream artFile1("Ascii Art Files\\TitleScreenFrame1.txt");
		fstream artFile2("Ascii Art Files\\TitleScreenFrame2.txt");
		fstream artFile3("Ascii Art Files\\TitleScreenFrame3.txt");
		fstream artFile4("Ascii Art Files\\TitleScreenFrame4.txt");

		if (cycles == 2) {
			frame++;
			cycles = 0;
		}
		if (frame == 5) {
			frame = 1;
		}
		if (frame == 1) {
			while (getline(artFile1, line)) {
				cout << "\t" << line << endl;
			}
		}
		else if (frame == 2) {
			while (getline(artFile2, line)) {
				cout << "\t" << line << endl;
			}
		}
		else if (frame == 3) {
			while (getline(artFile3, line)) {
				cout << "\t" << line << endl;
			}
		}
		else if (frame == 4) {
			while (getline(artFile4, line)) {
				cout << "\t" << line << endl;
			}
		}

		cursorPos = { 0, 17 };
		SetConsoleCursorPosition(console, cursorPos);

		if (select == 0) {
			cout << "\t\t\t\t\t\t   ";
			SetConsoleTextAttribute(console, 112);
			cout << "New Game\n";
			SetConsoleTextAttribute(console, 15);
			cout << "\t\t\t\t\t\t   " << "Load Game\n"; // starting main menu screen
		}
		else if (select == 1) {
			SetConsoleTextAttribute(console, 15);
			cout << "\t\t\t\t\t\t   " << "New Game\n" << "\t\t\t\t\t\t   ";
			SetConsoleTextAttribute(console, 112);
			cout << "Load Game\n"; // starting main menu screen
			SetConsoleTextAttribute(console, 15);
		}

		if (_kbhit()) {

			int keyPressed = _getch();
			// cout << keyPressed;

			if (keyPressed == 13) {
				if (select == 0) {
					OpenFile = NewGame();
				}
				else {
					OpenFile = LoadGame();
				}
				check = true;
			}
			else if (keyPressed == 72 || keyPressed == 80) {
				
				if (select == 0) {
					select = 1;
				}
				else {
					select = 0;
				}
			}
		}

		Sleep(1);
		cycles++;

		if (check == false) {
			artFile1.close();
			artFile2.close();
			artFile3.close();
			artFile4.close();
		}

	} while (check == false);

	Shop(OpenFile);

	return 0;
}