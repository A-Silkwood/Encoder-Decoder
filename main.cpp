#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

void encode();

void insertionSort(string * stringPointers[], int size);

bool stringGT(string str1, string str2);

int main() {
    encode();

    return 0;
}

// encodes the string given
void encode() {
    int lineCount = 0;
    while(cin.eof() == 0) {
        // receive line
        string line;
        getline(cin, line);
        if(cin.eof() == 0) {line = line.substr(0, line.length() - 1);}

        // create array of shifted strings
        int size = line.length();
        string strings[size];
        string *pointers[size];
        for (int i = 0; i < size; i++) {
            strings[i] = line.substr(i, line.length() - i) + line.substr(0, i);
            pointers[i] = &strings[i];
        }

        // sort pointers in lexicographic order
        insertionSort(pointers, size);  //sorts using insertion sort

        // create a string of the last character of each string
        string endings;
        string currStr;
        for (int i = 0; i < size; i++) {
            currStr = *pointers[i];
            endings += currStr.at(size - 1);
        }

        // output finished encoded line
        cout << lineCount++ << endl;    // line 1 of encoded message
        char currChar = endings.at(0);
        int count = 0;
        for(int i = 0; i < size; i++) {
            if(currChar == endings.at(i)) {
                count++;
            } else {
                cout << count << currChar;
                currChar = endings.at(i);
                count = 1;
            }
        }
        cout << count << currChar << endl;
    }
}

// sorts string pointers in lexicographic order using insertion sort
void insertionSort(string * stringPointers[], int size) {
    string * key;
    int ix;
    for(int i = 1; i < size; i++) {
        key = stringPointers[i];
        ix = i - 1;
        while(ix >= 0 && stringGT(*stringPointers[ix], *key)) {
            stringPointers[ix + 1] = stringPointers[ix];
            ix--;
        }
        stringPointers[ix + 1] = key;
    }
}

// tests if str1 is greater than str2
bool stringGT(string str1, string str2) {
    int ix = 0;
    while(ix < str1.length()) {
        if((int)str1[ix] > (int)str2[ix]) {
            return true;
        } else if((int)str1[ix] < (int)str2[ix]) {
            return false;
        }
        ix++;
    }
    return false;
}