#include <iostream>
#include <fstream>
#include <sstream>
#include <string
int main() {
	ifstream InputFile("FIFO.txt")
	while (std::getline(file, line)) {
        	std::istringstream ss(line);
        	std::string value;

        	while (std::getline(ss, value, ',')) {
            		std::cout << "Value: " << value << std::endl;
        		}
    		}
	return 0;	
}
