//============================================
//  Nicholas Pape
//  nmp33
//  CS280-017
//============================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <map>

using namespace std;

string fileName;
bool binFlag = false;
bool decFlag = false;
bool hexFlag = false;
bool octFlag = false;

map<string, int> decLits;
map<string, int> hexLits;
map<string, int> octLits;
map<string, int> binLits;

void cmdArgs(int argc, char *argv[]) {

    if (!argv[1]) {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(-1);
    }
    else {
        fileName = argv[1];
    }

    for (int i = 2; i < argc; i++) {

        string arg = argv[i];

        if (arg == "-all") {
            binFlag = true;
            decFlag = true;
            hexFlag = true;
            octFlag = true;
        }
        else if (arg == "-bin") {
            binFlag = true;
        }  
        else if (arg == "-dec") {
            decFlag = true;
        }
        else if (arg == "-hex") {
            hexFlag = true;
        }
        else if (arg == "-oct") {
            octFlag = true;
        }
        else {
            cerr << "UNRECOGNIZED FLAG " << argv[i] << endl;
            exit(-1);
        }

    }
}

void isEmpty(string filename) {

    ifstream inFile(filename, ifstream::ate | ifstream::binary);
    
    if (inFile.tellg() == 0) {
        cout << "File is empty." << endl;
        exit(0);
    }
}

void fileOpens(string fileName) {

    ifstream inFile(fileName);

    if (inFile.fail()) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        exit(-1);
    }

    else {
        inFile.close();
    }
}

void wordLine(string fileName) {

    ifstream inFile(fileName);

    int lineCount = 0;
    int wordCount = 0;
    string line;

    while (getline(inFile, line)) {
        lineCount++;
        
        string plc;
        istringstream word(line);

        while (word >> plc) {
            wordCount++;
        }
    }

    inFile.close();

    cout << "Total Number of Lines: " << lineCount << endl;
    cout << "Number of Words: " << wordCount << endl;

}

void decimalLiterals(string fileName) {
    
    ifstream inFile(fileName);
    string line;
    int count = 0;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        istringstream stream(line);
        string word;

        while (stream >> word) {
        
            regex decimal(R"(0|[1-9][0-9]*)");
            regex decimalErr (R"(\b[1-9][0-9]*[^0-9]+\w*\b)");

            if (regex_match(word, decimal)) {
                count++;
                decLits[word]++;
            }
        }
    }

    inFile.close();
    cout << "Number of Decimal Literals: " << count << endl;

}

void hexadecimalLiterals(string fileName) {

    ifstream inFile(fileName);
    string line;
    int count = 0;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        istringstream stream(line);
        string word;

        while (stream >> word) {
        
            regex hexadecimal(R"(0[xX][0-9a-fA-F]+)");

            if (regex_match(word, hexadecimal)) {
                count++;
                hexLits[word]++;
            }
        }
    }

    inFile.close();
    cout << "Number of Hexadecimal Literals: " << count << endl;

}

void octalLiterals(string fileName) {
    
    ifstream inFile(fileName);
    string line;
    int count = 0;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        istringstream stream(line);
        string word;

        while (stream >> word) {
        
            regex octal(R"(\b0[0-7]+\b)");

            if (regex_match(word, octal)) {
                count++;
                octLits[word]++;
            }
        }
    }

    inFile.close();
    cout << "Number of Octal Literals: " << count << endl;

}

void binaryLiterals(string fileName) {
    
    ifstream inFile(fileName);
    string line;
    int count = 0;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        istringstream stream(line);
        string word;

        while (stream >> word) {
        
            regex binary(R"(0[bB][01]+)");

            if (regex_match(word, binary)) {
                count++;
                binLits[word]++;
            }
        }
    }

    inFile.close();
    cout << "Number of Binary Literals: " << count << endl;

}

void literalErrors(string fileName) {

    ifstream inFile(fileName);
    string line;
    int lineCount = 0;

    while (getline(inFile, line)) {

        lineCount++;

        if (line.empty()) {
            continue;
        }

        istringstream stream(line);
        string word;

        while (stream >> word) {

            regex decimal(R"(0|[1-9][0-9]*)");
            regex decimalErr (R"(\b[1-9][0-9]*[^0-9]+\w*\b)");
            regex hexErr(R"(\b0[xX][0-9a-fA-F]*[^0-9a-fA-F]+\w*\b)");
            regex octalErr(R"(\b0[0-7]+[^0-7]+\w*\b(?![xXbB]))");
            regex binaryErr(R"(\b0[bB][01]*[^01]+\w*\b)");

            if (regex_match(word, decimal)) {
            }
            else if (regex_match(word, decimalErr)) {
                cerr << "Incorrect Decimal Literal " << word << " at Line: " << lineCount << endl;
            }
            else if (regex_match(word, hexErr)) {
                cerr << "Incorrect Hexadecimal Literal " << word << " at Line: " << lineCount << endl;
            }
            else if (regex_match(word, octalErr)) {
                cerr << "Incorrect Octal Literal " << word << " at Line: " << lineCount << endl;
            }
            else if (regex_match(word, binaryErr)) {
                cerr << "Incorrect Binary Literal " << word << " at Line: " << lineCount << endl;
            }
            
        }
    }
    inFile.close();
}

void printBin(map<string, int> binary) {
    
    map<string, int>::iterator mapIterator;
    
    if (binFlag) {
        cout << "\nList of Binary-Literals and their number of occurrences:\n";

        for(mapIterator = binLits.begin(); mapIterator != binLits.end(); mapIterator++) {
            cout << mapIterator->first << ": " << mapIterator->second << "\n";
        }
    }
}

void printDec(map<string, int> decimal) {
    
    map<string, int>::iterator mapIterator;

    if (decFlag) {
        cout << "\nList of Decimal-Literals and their number of occurrences:\n";
        
        for(mapIterator = decLits.begin(); mapIterator != decLits.end(); mapIterator++) {
            cout << mapIterator->first << ": " << mapIterator->second << "\n";
        }
    }
}

void printHex(map<string, int> hexadecimal) {

    map<string, int>::iterator mapIterator;
    
    if (hexFlag) {
        cout << "\nList of Hex-Literals and their number of occurrences:\n";
        
        for(mapIterator = hexLits.begin(); mapIterator != hexLits.end(); mapIterator++) {
            cout << mapIterator->first << ": " << mapIterator->second << "\n";
        }
    }
}

void printOct(map<string, int> octal) {

    map<string, int>::iterator mapIterator;

    if (octFlag) {
        cout << "\nList of Octal-Literals and their number of occurrences:\n";

        for(mapIterator = octLits.begin(); mapIterator != octLits.end(); mapIterator++) {
            cout << mapIterator->first << ": " << mapIterator->second << "\n";
        }
    }
}

int main(int argc, char *argv[]) {

    cmdArgs(argc, argv);
    isEmpty(fileName);
    fileOpens(fileName);
    literalErrors(fileName);
    wordLine(fileName);
    decimalLiterals(fileName);
    hexadecimalLiterals(fileName);
    octalLiterals(fileName);
    binaryLiterals(fileName);
    printBin(binLits);
    printDec(decLits);
    printHex(hexLits);
    printOct(octLits);

    return 0;
}