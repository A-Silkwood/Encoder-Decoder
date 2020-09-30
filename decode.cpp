#include <iostream>
#include <string>

void decode(std::string keyword);

int main(int argc, char *argv[]) {
    // checks if an argument was passed and passes it to encode
    if(argc >= 2) {decode(argv[1]);}

    return 1;
}

// main encoding method
void encode(std::string keyword) {
    // checks for valid keyword
    if (keyword == "insertion" || keyword == "quick") {
        //decode code
    }
}