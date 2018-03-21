/*
 * FileHandler.cpp
 * Created on: Mar 17, 2018
 * Author: Amr Hendy
 */

#include "FileHandler.h"

using namespace std;

FileHandler::FileHandler() {
	// TODO Auto-generated constructor stub

}

FileHandler::~FileHandler() {
	// TODO Auto-generated destructor stub
}

vector<string> FileHandler::readFile(string file_name){
	ifstream input_file (file_name.c_str(), ifstream::in);
	vector<string> all_lines;
	string input_line;
	if(input_file.is_open()){
		while(getline(input_file, input_line)){
			all_lines.push_back(input_line);
		}
	}
	return all_lines;
}