#include <iostream>
#include <string>

void decode(std::string keyword);
void insertionSort(std::string *str, int size);
void quickSort(std::string *str, int left, int right);

int main(int argc, char *argv[]) {
    // checks if an argument was passed and passes it to encode
    if(argc >= 2) {decode(argv[1]);}
    return 1;
}


// main decoding method
void decode(std::string keyword) {
    if (keyword == "insertion" || keyword == "quick") { // checks for valid keyword
        bool addNewline = false;
        while(!std::cin.eof()) {    // decodes lines until it reaches end of input
            // adds new line for empty strings; added to start of loop to avoid two newlines at end of file
            if(addNewline) {
                std::cout << std::endl;
                addNewline = false;
            }

            // receive the index
            std::string line;
            getline(std::cin, line);

            // decode
            if(line.empty()) {
                addNewline = true;
            } else {
                // converts line into the index value
                int index = 0;
                for(char i : line) {
                    index *= 10;    // shifts for numbers greater than 1 character
                    index += (int)(i - '0');    // convert char to int
                }

                // receive second line; assumes input is properly formatted
                getline(std::cin, line);

                // recreate the string of ending characters of the shifted array
                std::string last;
                bool readCount = true;
                bool readChar = false;
                int count = 0;
                for(char i : line) {
                    if(readCount) {
                        if(i != ' ') {  // read cluster size
                            // convert to integer
                            count *= 10;
                            count += (int)(i - '0');
                        } else {
                            // switch to reading char once it hits whitespace
                            readCount = false;
                            readChar = true;
                        }
                    } else if(readChar) {   // add char based on cluster size
                        readChar = false;
                        for(int j = 0; j < count; j++) {
                            last += i;
                        }
                        count = 0;
                    } else {    // go back to reading cluster size next loop iteration
                        readCount = true;
                    }
                }

                // create a sorted version of last string
                std::string sort = std::string(last);
                int length = sort.length();
                // create sorted string of last string
                if(keyword == "insertion") {
                    // sort using insertion sort
                    insertionSort(&sort, length);
                } else if(keyword == "quick") {
                    // sort using quick sort
                    quickSort(&sort, 0, length - 1);
                }

                //generate next array
                int next[length];
                std::string temp = std::string(last);
                int tempSize = length;
                for(int i = 0; i < length; i++) {
                    char curr = sort[i];
                    int j = 0;
                    while(temp[j] != curr) {j++;}
                    next[i] = j;
                    temp[j] = '\n';
                }

                std::string out = "";
                int ix = index;
                do {
                    out += last[next[ix]];
                    ix = next[ix];
                } while(ix != index);

                std::cout << out << std::endl;
            }
        }
    }
}

// sorts chars in lexicographic order using insertion sort
void insertionSort(std::string *str, int size) {
    char key;
    int ix;

    //sorting algorithm
    for(int i = 1; i < size; i++) {
        key = (*str)[i];
        ix = i - 1;
        // inserts the next char into the already sorted chars
        while(ix >= 0 && (*str)[ix] > key) {
            (*str)[ix + 1] = (*str)[ix];
            ix--;
        }
        (*str)[ix + 1] = key;
    }
}

// chooses a pivot and compares chars to move all chars less than pivot to the left and greater than to the right
int partition(std::string *str, int left, int right) {
    char holder;
    // special case for subarrays of size 2
    if(right-left == 1) {
        // checks if the two values need to be swapped
        if((*str)[left] > (*str)[right]) {
            holder = (*str)[left];
            (*str)[left] = (*str)[right];
            (*str)[right] = holder;
        }
        return right;
    }

    int i = left;
    int j = right - 1;
    char pivot = (*str)[right];
    // move strings into position
    while(i < j && i < right - 1 && j > left) {
        // move i and j until they find values on the wrong side of the array or are on the bounds
        while(i < right && (*str)[i] <= pivot) {i++;}
        while(j >= left && (*str)[j] > pivot) {j--;}

        // swap strings if they haven't passed each other
        if(i < j) {
            holder = (*str)[i];
            (*str)[i] = (*str)[j];
            (*str)[j] = holder;
        }
    }

    // move pivot into position
    (*str)[right] = (*str)[i];
    (*str)[i] = pivot;

    // return pivot position
    return i;
}

// sorts chars in lexicographic order using quick sort
void quickSort(std::string *str, int left, int right) {
    if(left < right) {
        // moves chars to the proper sides of a chosen mid point
        int mid = partition(str, left, right);
        // recursive calls; does not call for subarrays of a size less than or equal to 1
        if(mid - left > 1) {quickSort(str, left, mid - 1);}
        if(right - mid > 1) {quickSort(str, mid + 1, right);}
    }
}
