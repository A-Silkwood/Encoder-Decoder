#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

void encode(const string& input);

void insertionSort(string * stringPointers[], int size);

bool stringGT(string str1, string str2);

int main() {
    string input;
    string test;
    // encode each line
    int lineCount = 1;
    while(cin.eof() == 0) {
        getline(cin, input);
        input = input.substr(0, input.length() - 1);
        cout << "Line #" << lineCount << ": " << input << endl;
        encode(input);
        cout << endl;
    }

    return 0;
}

// encodes the string given
void encode(const string& input) {
    // create shifted string arrays
    int size = input.length();
    string strings[size];
    string * pointers[size];
    cout << "Shifted Strings:" << endl;
    for(int i = 0; i < size; i++) {
        strings[i] = input.substr(i, input.length() - i) + input.substr(0, i);
        pointers[i] = &strings[i];
        cout << "\t" << strings[i] << endl;
    }

    // sort pointers in lexicographic order
    insertionSort(pointers, size);  //sorts using insertion sort

    cout << "Sorted Strings:" << endl;
    for(int i = 0; i < size; i++) {
        cout << "\t" << *pointers[i] << endl;
    }

    // create a string of the last character of each string
    string endings;
    string curr;
    for(int i = 0; i < size; i++) {
        curr = *pointers[i];
        endings += curr.at(size - 1);
    }
    cout << "Endings: " << endings << endl;
    // create finished encoded line
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