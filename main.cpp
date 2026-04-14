#include <iostream>
#include <fstream>
#include <string>

// Permits imported files to use main functions when ran as standalone
#define RUNNING_MAIN
#include "lru.cpp"

int run(char type, int frame_count, int page_table[], int page_count);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout<<"Usage: ./program_name <filename.txt>" <<std::endl;
		return 1;
	}
	
	std::ifstream inputFile(argv[1]);
    	if (!inputFile.is_open()) {
        	std::cout << "Error: Could not open file " << argv[1] << std::endl;
        	return 1;
    	}

	char algorithmType = ' ';
	int numFrames = 0;
	int referenceString[500];
	int refCount = 0;
	std::string temp;

	// Type of alg
	if (std::getline(inputFile, temp, ',')) {
		if(!temp.empty()) {
			algorithmType = temp[0];
		}
	}

	// Num of memory frame
	if (std::getline(inputFile, temp, ',')) {
        	if (!temp.empty()) {
            		numFrames = std::stoi(temp);
        	}
    	}

	while (std::getline(inputFile, temp, ',')) {
        	if (!temp.empty()) {
            		referenceString[refCount] = std::stoi(temp);
            	refCount++;
        	}
    	}
    	inputFile.close();
	
	return run(algorithmType, numFrames, referenceString, refCount);
}

int run(char type, int frame_count, int page_table[], int page_count) {

	switch (type) {
        	case 'F':
            		std::cout << "Running FIFO Algorithm..." << std::endl;
            	break;

        	case 'L':
            		std::cout << "Running LRU Algorithm..." << std::endl;
					runLRU(frame_count, page_table, page_count);
            	break;

        	case 'O':
            		std::cout << "Running OPT Algorithm..." << std::endl;
            	break;

       		default:
            		std::cout << "Error: Unknown Algorithm Type '" << type << "'" << std::endl;
            	return 1;
    }
	return 0;
}
