#include <iostream>
#include <string>

void encode(const std::string& keyword);

void insertionSort(std::string * stringPointers[], int size);
bool stringGT(std::string str1, std::string str2);

int main(int argc, char *argv[]) {
    // checks if an argument was passed
    if(argc >= 2) {
        // starts encoding and passes the first argument
        encode(argv[1]);
    }
}

// main encoding method
void encode(const std::string& keyword) {
    // does not actually start encoding if a valid keyword was not given
    if (keyword != "insertion" && keyword != "quick") {
        return;
    }

    // encodes as long as input is not at the end of file
    while(std::cin.eof() == 0) {
        // receive next line from input
        std::string line;
        getline(std::cin, line);
        if(std::cin.eof() == 0) {line = line.substr(0, line.length() - 1);}

        if(line.length() == 0) {
            // sends a blank line to output if a blank line was read
            std::cout << std::endl;
        } else {
            // encodes the line

            // create array of shifted strings
            int size = line.length();
            std::string strings[size];
            std::string *pointers[size];
            for (int i = 0; i < size; i++) {
                strings[i] = line.substr(i, line.length() - i) + line.substr(0, i);
                pointers[i] = &strings[i];
            }

            // sort pointers in lexicographic order according to ascii
            if (keyword == "insertion") {
                // sorts using insertion sort if "insertion" keyword was passed
                insertionSort(pointers, size);
            } else {
                // sorts using quick sort if "quick" keyword was passed
                // quick sort is unimplemented
            }

            // creates a string made up of the last character of each string
            std::string endings;
            std::string currStr;
            int startIx = -1;
            for (int i = 0; i < size; i++) {
                currStr = *pointers[i];
                // stores the index of the original first line before being sorted
                if (startIx == -1 && currStr == line) {
                    startIx = i;
                }
                endings += currStr.at(size - 1);
            }

            // output the first line of the current line read
            std::cout << startIx << std::endl;

            // output the second line of the current line read
            // counts clusters of characters and outputs count with character
            char currChar = endings.at(0);
            int count = 0;
            for (int i = 0; i < size; i++) {
                if (currChar == endings.at(i)) {
                    count++;
                } else {
                    std::cout << count << currChar;
                    currChar = endings.at(i);
                    count = 1;
                }
            }
            // output final character with count
            std::cout << count << currChar << std::endl;
        }
    }
}

// sorts string pointers in lexicographic order using insertion sort
void insertionSort(std::string * stringPointers[], int size) {
    std::string * key;
    int ix;
    for(int i = 1; i < size; i++) {
        key = stringPointers[i];
        ix = i - 1;
        // insert string into already sorted strings
        while(ix >= 0 && stringGT(*stringPointers[ix], *key)) {
            stringPointers[ix + 1] = stringPointers[ix];
            ix--;
        }
        stringPointers[ix + 1] = key;
    }
}

// tests if str1 is greater than str2 based on lexicographical order
bool stringGT(std::string str1, std::string str2) {
    int ix = 0;
    while(ix < str1.length()) {
        if((int)str1[ix] > (int)str2[ix]) {
            return true;
        } else if((int)str1[ix] < (int)str2[ix]) {
            return false;
        }
        ix++;
    }
    // strings were equal
    return false;
}