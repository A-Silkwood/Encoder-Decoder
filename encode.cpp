#include <iostream>
#include <string>

void encode(std::string keyword);

std::string leftShift(std::string str, int shift);
void insertionSort(std::string * stringPointers[], int size);
int strCompare(std::string * str1, std::string * str2);

int main(int argc, char *argv[]) {
    // checks if an argument was passed and passes it to encode
    if(argc >= 2) {
        encode(argv[1]);
    }
}

// main encoding method
void encode(std::string keyword) {
    // checks for valid keyword
    if (keyword == "insertion") {
        bool addNewline = false;
        std::string line;

        // encodes lines until it reaches end of input
        while (!std::cin.eof()) {
            // adds new line for empty strings; added to start of loop to avoid two newlines at end of file
            if(addNewline) {
                std::cout << std::endl;
                addNewline = false;
            }

            // receive line
            getline(std::cin, line);

            // encode line
            if (line.empty()) {
                addNewline = true;
            } else {
                // create array of shifted string pointers
                int size = line.length();
                std::string strings[size];
                std::string * pointers[size];
                for (int i = 0; i < size; i++) {
                    // create shifted string
                    strings[i] = leftShift(line, i);
                    // assign string's pointer
                    pointers[i] = strings + i;
                }

                // sort pointers in lexicographic order according to ascii values
                if (keyword == "insertion") {
                    // sort using insertion sort
                    insertionSort(pointers, size);
                } else if (keyword == "quick") {
                    // sorts using quick sort
                    insertionSort(pointers, size - 1 + 1);
                }

                // output line 1 of encoding
                // index of the original string read in the sorted array
                int startIx = -1;
                int ix = 0;
                while(startIx == -1 && ix < size) {
                    if(line == *pointers[ix]) {
                        startIx = ix;
                    }
                    ix++;
                }
                // -1 means string was not found
                std::cout << startIx << std::endl;

                // output line 2 of encoding
                // clusters of the ending characters from each of the strings "<count> <char>"
                char currChar = (*pointers[0]).at(size - 1);
                int count = 0;
                for (int i = 0; i < size; i++) {
                    if (currChar == (*pointers[i]).at(size - 1)) {
                        // increments count if same char is found
                        count ++;
                    } else {
                        // output current cluster count and char if different char is found
                        std::cout << count << " " << currChar << " ";
                        // set up next cluster
                        currChar = (*pointers[i]).at(size - 1);
                        count = 1;
                    }
                }
                // output final cluster
                std::cout << count << " " << currChar << std::endl;
            }
        }
    }
}

// shifts string to the left
std::string leftShift(std::string str, int shift) {
    std::string newStr = std::string(str);
    int size = str.length();

    // offsets the new start of the string by the shift value
    for(int i = 0; i < size - shift; i++) {
        newStr[i] = str[shift + i];
    }
    // adds cut off characters to the end of the string
    for(int i = size - shift; i < size; i++) {
        newStr[i] = str[i - size + shift];
    }

    return newStr;
}

// sorts string pointers in lexicographic order using insertion sort
void insertionSort(std::string * stringPointers[], int size) {
    std::string *key;
    int ix;

    // sorting algorithm
    for (int i = 1; i < size; i++) {
        key = stringPointers[i];
        ix = i - 1;
        // inserts the next string into the already sorted strings
        while (ix >= 0 && strCompare(stringPointers[ix], key) == 1) {
            stringPointers[ix + 1] = stringPointers[ix];
            ix--;
        }
        stringPointers[ix + 1] = key;
    }
}

// compares str1 and str2
// returns: -1 if str1 is less than str2; 1 if str is greater than str2; 0 if strings are equal
// assumes strings are equal lengths
int strCompare(std::string * str1, std::string * str2) {
    int ix = 0;

    // checks through each character until strings are unequal
    while(ix < (*str1).length()) {
        if((*str1)[ix] > (*str2)[ix]) {
            // str1 was greater than str2
            return 1;
        } else if((*str1)[ix] < (*str2)[ix]) {
            // str1 was less than str2
            return -1;
        }
        // check next character
        ix++;
    }
    // strings were equal
    return 0;
}