#include <fstream>
#include <iostream>

void createMode();
void createOutOfFile();
void createOutOfCommandline();
void uncoverMode();
std::string secretFormula();

int main(){	
	
	char choice;
	do{
		std::cout << "**************" << '\n' << "S.C.A.U.T Main Menu" << '\n' << "**************" << '\n' << '\n';
		std::cout << "Pick an option:" << '\n' << "1. Create Secret" << '\n' << "2. Uncover Secret" << '\n' << "3. Quit" << '\n';
		
		std::cin >> choice;
		std::cin.ignore(2000, '\n');
		
		switch(choice){
		case '1':
			createMode();
			break;
			std::cout << '\n' << '\n';
	/*	case '2':
			uncoverMode();
			std::cout << '\n' << '\n';
			break;
		case '3':
			std::cout << '\n' << "Quitting program...";
			break;
	*/	default:
			std::cout << '\n' << "Invalid input. Try again: ";
			break;
		}

	}while(choice != '3');
}

void createMode(){
	
	char choice;
	do{
		std::cout << "**************" << '\n' << "S.C.A.U.T Creation Mode" << '\n' << "**************" << '\n' << '\n';
		std::cout << "Pick an option:" << '\n' << "1. Create Secret out of file" << '\n' << "2. Create Secret per command line" << '\n' << "3. Quit Creation Mode" << '\n';
		
		std::cin >> choice;
		std::cin.ignore(2000, '\n');
		
		switch(choice){
		case '1':
			createOutOfFile();
			break;
	/*	case '2':
			createOutOfCommandline();
			break;
		case '3':
			std::cout << '\n' << "Quitting Creation Mode...";
			break;
	*/	default:
			std::cout << '\n' << "Invalid input. Try again: ";
			break;
		}

	}while(choice != '3');
}

void createOutOfFile(){
	std::string importFilename;
	std::string exportFilename;

	std::cout << "Enter the name of the file you want to turn into a secret: ";
	std::cin >> importFilename;
	std::cout << "Enter the name of the file you want the secret written in: ";
	std::cin >> exportFilename;
	
	std::ifstream ImportFile;
	ImportFile.open(importFilename, std::ifstream::in);
	if(!ImportFile.is_open()){
		std::cout << '\n' << "Couldn't find import file";
		return;
	}
	
	std::ofstream ExportFile(exportFilename);
	if(!ExportFile.is_open()){
		std::cout << '\n' << "Error with creating export file";
		return;
	}
	
	ImportFile.seekg (0, ImportFile.end);
    	int length = ImportFile.tellg();
    	ImportFile.seekg (0, ImportFile.beg);
	char* buffer = new char[length];
	
	ImportFile.read(buffer, length);
	std::string importedFileContent = buffer;
	delete[] buffer;
	
	ExportFile << secretFormula(importedFileContent);
	
	ImportFile.close();
	ExportFile.close();
}
