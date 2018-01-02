#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void usage() {
	cout << "Usage: todo <command> <argument>" << endl;
	cout << "	command: add remove print" << endl;
	cout << "	argument: comment to add or id of comment to remove" << endl;
}

int getLastLineNum() {
	string line;
	string check;
	ifstream file;
	file.open("todo_list.txt");
	while(file.is_open()) {
		getline(file, check);
		if(file.eof())
			break;
		line = check;
	}
	file.close();
	return (line.empty()) ? 0 : stoi(line.substr(0, line.find(":")));
}

int main(int argc, char ** argv) {
	if(argc < 2) {
		usage();
	} else {
		string command = argv[1];
		if(command.compare("add") == 0) {
			string line;
			for(int i = 2; i < argc; i++) {
				line += argv[i];
				line += " ";
			}
			//dynamic counting
			int count = getLastLineNum();
			ofstream file;
			file.open("todo_list.txt", ios::in | ios::app);
			file << (count + 1) << ": " << line << "\n";
			file.close();
		} else if (command.compare("remove") == 0) {
			ifstream file;
			file.open("todo_list.txt", ios::in | ios::app | ios::out);
			ofstream temp;
			temp.open("temp.txt");

			string line;
			while(file.is_open()) {
				getline(file, line);
				string number = line.substr(0, line.find(":"));
				if(number.compare(argv[2]) == 0)
					continue;
				if(file.eof())
					break;
				//add same comment to todone_list.txt
				temp << line << endl;
			}
			file.close();
			temp.close();
			remove("todo_list.txt");
			rename("temp.txt", "todo_list.txt");
		} else if (command.compare("print") == 0) {
			ifstream file;
			file.open("todo_list.txt", ios::out);
			
			string line;
			while (file.is_open()) {
				getline(file, line);
				if(file.eof())
					break;
				cout << line << endl;
			}
			file.close();
		} else {
			cout << "Command not recognized." << endl;
			usage();
		}
	}
	return 0;
}
