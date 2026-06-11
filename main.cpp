/*
	Copyright (C) 2026  Kreis Kressinger

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <fstream>
#include <iostream>
#include <string.h>
#include <cctype>

void createMode();
void createOutOfFile();
void createOutOfCommandline();
void uncoverMode();
std::string secretFormula(std::string &content, std::string exportFilename, std::string importFilename);
std::string reverseSecretFormula(std::string &content, std::string exportFilename, std::string importFilename);
void uncoverOutOfFile();
void uncoverOutOfCommandline();

int main(){	
	
	char choice;
	do{
		std::cout << '\n'<< "**************" << '\n' << "S.C.A.U.T" << '\n' << "**************" << '\n' << '\n';
		std::cout << "Pick an option:" << '\n' << "1. Create Secret" << '\n' << "2. Uncover Secret" << '\n' << "3. Quit" << '\n';
		
		std::cin >> choice;
		std::cin.ignore(2000, '\n');
		
		switch(choice){
		case '1':
			createMode();
			std::cout << '\n' << '\n';
			break;
		case '2':
			uncoverMode();
			std::cout << '\n' << '\n';
			break;
		case '3':
			std::cout << '\n' << "Quitting program...";
			break;
		default:
			std::cout << '\n' << "Invalid input. Try again: ";
			break;
		}

	}while(choice != '3');
}

void createMode(){
	
	char choice;
	do{
		std::cout << '\n' << "**************" << '\n' << "Creation Mode" << '\n' << "**************" << '\n' << '\n';
		std::cout << "Pick an option:" << '\n' << "1. Create Secret out of file" << '\n' << "2. Create Secret per command line" << '\n' << "3. Quit Creation Mode" << '\n';
		
		std::cin >> choice;
		std::cin.ignore(2000, '\n');
		
		switch(choice){
		case '1':
			createOutOfFile();
			break;
		case '2':
			createOutOfCommandline();
			break;
		case '3':
			std::cout << '\n' << "Quitting Creation Mode..." << '\n' << '\n';
			break;
		default:
			std::cout << '\n' << "Invalid input. Try again: ";
			break;
		}

	}while(choice != '3');
}

void createOutOfFile(){
	std::string importFilename;
	std::string exportFilename;

	std::cout << '\n' << '\n' << "Enter the name of the file you want to turn into a secret: ";
	std::getline(std::cin, importFilename);
	
	std::cout << "Name the outputted file: ";
	std::getline(std::cin, exportFilename);
	
	
	std::ifstream ImportFile;
	ImportFile.open(importFilename, std::ifstream::in);
	if(!ImportFile.is_open()){
		std::cout << '\n' << "Couldn't find import file";
		return;
	}
	
	std::ofstream ExportFile("SCAUT-EXPORT-" + exportFilename);
	if(!ExportFile.is_open()){
		std::cout << '\n' << "Error with creating export file";
		return;
	}
	
//	ImportFile.seekg (0, ImportFile.end);
//    	int length = ImportFile.tellg();
//    	ImportFile.seekg (0, ImportFile.beg);
//	char* buffer = new char[length];
//	
//	ImportFile.read(buffer, length);
//	std::string importedFileContent(buffer, length);
//	delete[] buffer;
	ImportFile.seekg(0, std::ios::end);
	std::streamsize length = ImportFile.tellg();
	ImportFile.seekg(0, std::ios::beg);
	
	std::string importedFileContent(length, '\0');
	
	ImportFile.read(importedFileContent.data(), length);	

	ExportFile << secretFormula(importedFileContent, exportFilename, importFilename);
	
	ImportFile.close();
	ExportFile.close();
}

void createOutOfCommandline(){
	std::string exportFilename;
	std::string importContent;

	std::cout << "Name the outputted file: ";
	std::getline(std::cin, exportFilename);
	
	std::cout << "Paste/Write what you want to turn into a Secret: ";
	std::getline(std::cin, importContent);
	

	std::ofstream ExportFile("SCAUT-EXPORT-" + exportFilename);
	ExportFile << secretFormula(importContent, exportFilename, "None (Out of command line)");
	ExportFile.close();
}

std::string secretFormula(std::string &content, std::string exportFilename, std::string importFilename){
	//char keyNum[1];
	char keyNum;
	char* keyNumPointer = &keyNum;
	std::string result;
	std::string keyFileName;
	std::cout << "Enter the name of your keyfile: ";
	std::getline(std::cin, keyFileName);
		
	std::ifstream keyFile(keyFileName);
	if(!keyFile.is_open()){
	std::cout << '\n' << "Error reading key file";
	return "Error";
	}
	char option;
	std::cout << "Configuration:\nImportfile: " << importFilename 
		  << "\nExportfile: " << exportFilename 
		  << "\nKeyFilename: " << keyFileName 
		  << "\nContinue with this configuration? (y/N) ";
	
	std::cin >> option;
	
	if(std::toupper(static_cast<unsigned char>(option)) != 'Y'){
		std::cout << "***** Aborted process *****\n";
		keyFile.close();
		return "";
	}

	for(size_t i = 0; i < content.length(); i++){
		int temp = static_cast<int>(content.at(i));
		if(keyFile.peek() == EOF){
			keyFile.clear();
			keyFile.seekg(0);
		}
		//keyFile.read(keyNumPointer, 1);
		//temp += static_cast<int>(keyNum[0]);
		keyFile.read(&keyNum, 1);
		temp += static_cast<unsigned char>(keyNum);
		result += std::to_string(temp) + ".";
	}
	keyFile.close();
	std::cout << "\n*********   Secret created :)   *********" << '\n';
	return result;
};

std::string reverseSecretFormula(std::string &content,
                                 std::string exportFilename,
                                 std::string importFilename)
{
    std::string result;
    std::string keyFileName;

    std::cout << "Enter the name of your keyfile: ";
    std::getline(std::cin, keyFileName);

    std::ifstream keyFile(keyFileName, std::ios::binary);

    if (!keyFile.is_open())
    {
        std::cout << "\nError reading key file";
        return "Error";
    }

    char option;

    std::cout
        << "Configuration:"
        << "\n- Importfile: " << importFilename
        << "\n- Exportfile: " << exportFilename
        << "\n- KeyFilename: " << keyFileName
        << "\nContinue with this configuration? (y/N) ";

    std::cin >> option;
    std::cin.ignore(2000, '\n');

    if (std::toupper(static_cast<unsigned char>(option)) != 'Y')
    {
        std::cout << "***** Aborted process *****\n";
        return "";
    }

    while (!content.empty())
    {
        size_t pos = content.find('.');

        if (pos == std::string::npos)
            break;

        std::string token = content.substr(0, pos);
        content.erase(0, pos + 1);

        if (token.empty())
            break;

        int value;

        try
        {
            value = std::stoi(token);
        }
        catch (const std::exception&)
        {
            std::cerr << "Invalid token: " << token << '\n';
            continue;
        }

        if (keyFile.peek() == EOF)
        {
            keyFile.clear();
            keyFile.seekg(0);
        }

        char keyByte;
        keyFile.read(&keyByte, 1);

        value -= static_cast<unsigned char>(keyByte);

        result += static_cast<char>(value);
    }

    std::cout << "\n*********   Secret uncovered :)   *********\n";

    return result;
}
//std::string reverseSecretFormula(std::string &content, std::string exportFilename, std::string importFilename){
//	char keyNum[1];
//	const char* delim = ".";
//	char* keyNumPointer = keyNum;
//	std::string result;
//	std::string keyFileName;
//	std::cout << "Enter the name of your keyfile: ";
//	std::getline(std::cin, keyFileName);
//	
//	std::ifstream keyFile(keyFileName);
//	if(!keyFile.is_open()){
//	std::cout << '\n' << "Error reading key file";
//	return "Error";}
//
//	char option;
//	std::cout << "Configuration:" 
//		  << "\n- Importfile: " << importFilename 
//		  << "\n- Exportfile: " << exportFilename 
//		  << "\n- KeyFilename: " << keyFileName 
//		  << "\nContinue with this configuration? (y/N) ";
//	
//	std::cin >> option;
//	
//	if(std::toupper(static_cast<unsigned char>(option)) != 'Y'){
//		std::cout << "***** Aborted process *****\n";
//		keyFile.close();
//		return "";
//	}
//
//	const char* pointa = content.c_str();
//	while(!content.empty()){
//		int charLength = strcspn(pointa, delim);
//		std::string temp1= content.substr(0, charLength)+"\0;
//		if(temp1.empty() || temp1 == ""){
//		break;
//		}
//		int temp2 = std::stoi(temp1);
//		content.erase(0, charLength+1);
//		if(keyFile.peek() == EOF){
//			keyFile.clear();
//			keyFile.seekg(0);
//		}
//		keyFile.read(keyNumPointer, 1);
//		temp2 -= static_cast<int>(keyNum[0]);
//		result += char(temp2);
//	}
//	keyFile.close();
//	std::cout << "\n*********   Secret uncovered :)   *********" << '\n';
//	return result;
//}

void uncoverMode(){
	
	char choice;
	do{
		std::cout << '\n' << "**************" << '\n' << "Uncover Mode" << '\n' << "**************" << '\n' << '\n';
		std::cout << "Pick an option:" << '\n' << "1. Uncover out of File" << '\n' << "2. Uncover per command line" << '\n' << "3. Quit Uncover Mode" << '\n';
		
		std::cin >> choice;
		std::cin.ignore(2000, '\n');
		
		switch(choice){
		case '1':
			uncoverOutOfFile();
			break;
		case '2':
			uncoverOutOfCommandline();
			break;
		case '3':
			std::cout << '\n' << "Quitting Uncover Mode..." << '\n' << '\n';
			break;
		default:
			std::cout << '\n' << "Invalid input. Try again: ";
			break;
		}

	}while(choice != '3');
}

void uncoverOutOfCommandline(){
	std::string exportFilename;
	std::string importContent;

	std::cout << "Name of the outputted file: ";
	std::getline(std::cin, exportFilename);
	
	std::cout << "Paste/Write what you want to turn into a uncover: ";
	std::getline(std::cin, importContent);
	

	std::ofstream ExportFile("SCAUT-EXPORT-" + exportFilename);
	ExportFile << reverseSecretFormula(importContent, exportFilename, "None (Out of command line)");
	ExportFile.close();
}

void uncoverOutOfFile(){
	std::string importFilename;
	std::string exportFilename;

	std::cout << '\n' << "Enter the name of the file that has a secret to uncover: ";
	std::getline(std::cin, importFilename);
	
	std::cout << "Name the outputted file: ";
	std::getline(std::cin, exportFilename);
	
	
	std::ifstream ImportFile;
	ImportFile.open(importFilename, std::ifstream::in);
	if(!ImportFile.is_open()){
		std::cout << '\n' << "Couldn't find import file";
		return;
	}
	
	std::ofstream ExportFile("SCAUT-EXPORT-" + exportFilename);
	if(!ExportFile.is_open()){
		std::cout << '\n' << "Error with creating export file";
		return;
	}
	
//	ImportFile.seekg (0, ImportFile.end);
//    	int length = ImportFile.tellg();
//    	ImportFile.seekg (0, ImportFile.beg);
//	char* buffer = new char[length];
//	
//	ImportFile.read(buffer, length);
//	std::string importedFileContent = buffer;
//	delete[] buffer;
	ImportFile.seekg(0, std::ios::end);
	std::streamsize length = ImportFile.tellg();
	ImportFile.seekg(0, std::ios::beg);

	std::string importedFileContent(length, '\0');

	ImportFile.read(importedFileContent.data(), length);	
	ExportFile << reverseSecretFormula(importedFileContent, exportFilename, importFilename);
	
	ImportFile.close();
	ExportFile.close();
}
