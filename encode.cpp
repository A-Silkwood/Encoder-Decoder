#include <iostream>
#include <string>

void encode(const std::string& keyword);

int insertionSort(std::string * stringPointers[], int size);
bool stringGT(std::string * str1, std::string * str2);

int main(int argc, char *argv[]) {
    // checks if an argument was passed and passes it to encode
    if(argc >= 2) {
        encode(argv[1]);
    }
}

// main encoding method
void encode(const std::string& keyword) {
    // checks for valid keyword
    if (keyword == "insertion" || keyword == "quick") {
        // encodes lines until it reaches end of input
        while (std::cin.eof() == 0) {
            // receive line
            std::string line;
            getline(std::cin, line);
            // remove new line chars
            if (std::cin.eof() == 0) { line = line.substr(0, line.length() - 1); }

            // encode line
            if (line.length() == 0) {
                // received blank line
                std::cout << std::endl;
            } else {
                // create array of shifted string pointers
                int size = line.length();
                std::string strings[size];
                std::string * pointers[size];
                for (int i = 0; i < size; i++) {
                    // create shifted string
                    strings[i] = line.substr(i, line.length() - i) + line.substr(0, i);
                    // assign string's pointer
                    pointers[i] = strings + i;
                }

                // sort pointers in lexicographic order according to ascii values
                int startIx;    // index of the original first string
                if (keyword == "insertion") {
                    // sort using insertion sort
                    startIx = insertionSort(pointers, size);
                } else {
                    // sorts using quick sort
                    startIx = insertionSort(pointers, size - 1 + 1); // quick sort is unimplemented
                }

                // output line 1 of encoding
                // index in the sorted strings of the original first string the array
                std::cout << startIx << std::endl;

                // output line 2 of encoding
                // clusters of ending characters "<count> <char>"
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

// sorts string pointers in lexicographic order using insertion sort
// returns the index of where the first string was originally
int insertionSort(std::string * stringPointers[], int size) {
    std::string *key;
    int firstIx = 0;    // first strings new index
    int ix;
    for (int i = 1; i < size; i++) {
        key = stringPointers[i];
        ix = i - 1;
        // insert string into already sorted strings
        while (ix >= 0 && stringGT(stringPointers[ix], key)) {
            stringPointers[ix + 1] = stringPointers[ix];
            ix--;
        }
        stringPointers[ix + 1] = key;
        // increment index if key was placed before the first string
        if (ix + 1 <= firstIx) {
            firstIx++;
        }
    }

    return firstIx;
}

// tests if str1 is greater than str2 based on lexicographical order
bool stringGT(std::string * str1, std::string * str2) {
    int ix = 0;
    // checks through each character until on strings are unequal
    while(ix < (*str1).length()) {
        if((*str1)[ix] > (*str2)[ix]) {
            return true;
        } else if((*str1)[ix] < (*str2)[ix]) {
            return false;
        }
        ix++;
    }
    // strings were equal
    return false;
}