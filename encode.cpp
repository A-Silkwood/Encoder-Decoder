#include <iostream>
#include <string>

void encode(std::string keyword);

std::string leftShift(std::string str, int shift);

void insertionSort(std::string * stringPointers[], int size);

void quickSort(std::string * stringPointers[], int left, int right);
int partition(std::string * stringPointers[], int left, int right);

int strCompare(std::string * str1, std::string * str2);

int main(int argc, char *argv[]) {
    // checks if an argument was passed and passes it to encode
    if(argc >= 2) {encode(argv[1]);}

    return 1;
}

// main encoding method
void encode(std::string keyword) {
    // checks for valid keyword
    if (keyword == "insertion" || keyword == "quick") {
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
                    quickSort(pointers, 0, size - 1);
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

// sorts string pointers in lexicographic order using quick sort
void quickSort(std::string * stringPointers[], int left, int right) {
    if(left < right) {
        // moves strings to the proper sides of a chosen mid point
        int mid = partition(stringPointers, left, right);
        // recursive calls; does not call for subarrays of a size less than or equal to 1
        if(mid - left > 1) {quickSort(stringPointers, left, mid - 1);}
        if(right - mid > 1) {quickSort(stringPointers, mid + 1, right);}
    }
}

// chooses a pivot and compares strings to move all strings less than pivot to the left and greater than to the right
int partition(std::string * stringPointers[], int left, int right) {
    std::string *holder;
    // special case for subarrays of size 2
    if(right-left == 1) {
        // checks if the two values need to be swapped
        if(strCompare(stringPointers[left], stringPointers[right]) == 1) {
            holder = stringPointers[left];
            stringPointers[left] = stringPointers[right];
            stringPointers[right] = holder;
        }
        return left;
    }

    int i = left;
    int j = right - 1;
    std::string *pivot = stringPointers[right];

    // move strings into position
    while(i < j && i < right && j > left) {
        // move i and j until they find values on the wrong side of the array or are on the bounds
        while(i < right && strCompare(stringPointers[i], pivot) == -1) {i++;}
        while(j > left && strCompare(stringPointers[j], pivot) == 1) {j--;}

        // swap strings if they haven't passed each other
        if(i < j) {
            holder = stringPointers[i];
            stringPointers[i] = stringPointers[j];
            stringPointers[j] = holder;
        }
    }

    // move pivot into position
    stringPointers[right] = stringPointers[i];
    stringPointers[i] = pivot;

    // return pivot position
    return i;
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