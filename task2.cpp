#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int wordLimit = 100;
const int linesPerPage = 45;

int main() {
    int arraySize = 100;
    string* wordsDict = new string[arraySize];
    string* wordsNumber = new string[arraySize];

    ifstream file;
    file.open("inputt.txt");

    string currentLine;
    string currentWord;
    int wordSize;
    int i;

    int lineNumber = 0;
    int pageNumber = 1;
    int wordNumber = 0;

READ_FILE:
    if (lineNumber >= linesPerPage) {
        pageNumber++;
        lineNumber = 0;
    }
    if (file.eof()) goto END_READING;
    getline(file, currentLine);
    lineNumber++;
    i = 0;
    
READ_LINE:

    if (wordNumber >= arraySize) {
        string* oldDict = wordsDict;
        string* oldNumbers = wordsNumber;

        arraySize *= 2;
        wordsDict = new string[arraySize];
        wordsNumber = new string[arraySize];

        int iterator = 0;
    COPY_ARRAY:
        wordsDict[iterator] = oldDict[iterator];
        wordsNumber[iterator] = oldNumbers[iterator];
        iterator++;

        if (iterator < wordNumber) {
            goto COPY_ARRAY;
        }
        delete[] oldDict;
        delete[] oldNumbers;
    }

    currentWord = "";
    wordSize = 0;

READ_WORD:
    if (currentLine[i] == '\0') goto WRITE_LAST;
    if ('A' <= currentLine[i] && currentLine[i] <= 'Z')
    {
        currentWord = currentWord + (char)(currentLine[i] + 32);
        i++;
        wordSize++;
        goto READ_WORD;
    }
    else if ('a' <= currentLine[i] && currentLine[i] <= 'z')
    {
        currentWord = currentWord + currentLine[i];
        i++;
        wordSize++;
        goto READ_WORD;
    }
    else
    {
        if (wordSize != 0)
        {
            //cout << currentWord << ' ';
            int j = 0;
        CHECK_WORD:
            if (wordsDict[j] == currentWord)
            {
                i++;
                wordsNumber[j] += ", " + to_string(pageNumber);
                goto READ_LINE;
            }
            j++;
            if (j <= wordNumber) goto CHECK_WORD;
            
            wordsDict[wordNumber] = currentWord;
            wordsNumber[wordNumber] = to_string(pageNumber);
            wordNumber++;
            i++;
            goto READ_LINE;
        }
        else
        {
            if (currentLine[i] == '\0') goto READ_FILE;
            i++;
            goto READ_LINE;
        }

    }

    WRITE_LAST:
    if (wordSize != 0)
    {
        //cout << currentWord << ' ';
        int j = 0;
    CHECK_WORD1:
        if (wordsDict[j] == currentWord)
        {
            i++;
            wordsNumber[j] += ", " + to_string(pageNumber);
            goto READ_FILE;
        }
        j++;
        if (j <= wordNumber) goto CHECK_WORD1;

        wordsDict[wordNumber] = currentWord;
        wordsNumber[wordNumber] = 1;
        wordNumber++;
        i++;
        goto READ_FILE;
    }
    else
    {
        goto READ_FILE;
    }

END_READING:
    file.close();
    wordNumber--;
    string temp1;
    string temp2;
    i = 0;
    int j = 0;

    int n = 0;
OUTER_SORT:
    if (i >= wordNumber) goto END_OUTER;
    j = 0;
INNER_SORT: 
    if (j >= wordNumber) goto END_INNER;
CHECK_NEXT:
    if ((wordsDict[j][n] != '\0' && wordsDict[j + 1][n] != '\0') && (wordsDict[j][n] < wordsDict[j + 1][n])) goto NO_SWAP;
    if ((wordsDict[j][n] == wordsDict[j + 1][n]) && (wordsDict[j][n] != '\0' && wordsDict[j + 1][n] != '\0')) {
        n++;
        goto CHECK_NEXT;
    }

    temp1 = wordsDict[j];
    temp2 = wordsNumber[j];

    wordsDict[j] = wordsDict[j + 1];
    wordsDict[j + 1] = temp1;

    wordsNumber[j] = wordsNumber[j + 1];
    wordsNumber[j + 1] = temp2;
    
NO_SWAP: 
    j++;
    n = 0;
    goto INNER_SORT;
END_INNER:
    i++;
    goto OUTER_SORT;
END_OUTER:

    int outputCounter = 0;
    ofstream outputFile;
    outputFile.open("output2.txt");
OUTPUT_WORDS:
    if (outputCounter < wordNumber) {
        outputFile << wordsDict[outputCounter] << " - " << wordsNumber[outputCounter] << endl;
        outputCounter++;
        goto OUTPUT_WORDS;
    }
    outputFile.close();
    return 0;
    
}