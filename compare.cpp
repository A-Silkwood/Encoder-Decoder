#include <iostream>
#include <string>
#include <fstream>

bool compare(std::string path1, std::string path2);

int main(int argc, char *argv[]) {
    std::cout << compare(argv[1], argv[2]) << std::endl;
}

bool compare(std::string path1, std::string path2) {
    std::ifstream file1(path1);
    std::ifstream file2(path2);

    std::string str1;
    std::string str2;
    int line = 1;
    while(!file1.eof() && !file2.eof()) {
        getline(file1, str1);
        getline(file2, str2);
        if(str1 != str2) {
            std::cout << "Problem at line #" << line << std::endl;
            file1.close();
            file2.close();
            return false;
        }
        line++;
    }
    line--;

    if(!file1.eof() && file2.eof()) {
        std::cout << "File 2 ended before file 1 at line #" << line << std::endl;
        file1.close();
        file2.close();
        return false;
    }

    if(file1.eof() && !file2.eof()) {
        std::cout << "File 1 ended before file 2 at line #" << line << std::endl;
        file1.close();
        file2.close();
        return false;
    }

    file1.close();
    file2.close();
    return true;
}