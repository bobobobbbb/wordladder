// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "console.h"
//#include "genlib.h"
#include "lexicon.h"

using namespace std;
//Funcion Prototypes
void AskUserForTheDictionaryFile(string prompt, ifstream & infile);
bool IsAllAlpha(string & str);
bool InVector(Vector<string> vec, string str);
Lexicon searchAllNeighbors(const Lexicon & dictionary, Lexicon usedWord, const string & topWord);
static void welcome(void);
static bool getEnglishWord(const Lexicon & dictionary, string& word, string prompt);
static bool checkWordEndpoints(const Lexicon& dictionary,
                 const string& sourceWord, string& destinationWord);

/*
REQUIRE
*1. be careful the user can input lowcase upercase mixedcase
*2. 
*/
int main() {
    // TODO: Finish the program!
    Vector<string> usedLadder;
    Queue<stack<string>> stackQueue;
    Stack<string>;
    welcome();

    
    ifstream dictionaryFile;
    AskUserForTheDictionaryFile( "Dictionary file name?", dictionaryFile);
    Lexicon english(dictionaryFile);

    while (true) {
        string sourceWord;
        string destinationWord;
        if (getEnglishWord(english, sourceWord, "Word #1 (For empty to quit)")) {
            break;
        }
        if (getEnglishWord(english, destinationWord, "Word #2 (For empty to quit)")) {
            break;
        }
        if (checkWordEndpoints(english, sourceWord, destinationWord)) break;

        Queue< Stack<string> > stackQueue;
        Stack<string> wordLadder;
        Lexicon usedWords;

        wordLadder.push(sourceWord);
        usedWords.add(sourceWord);
        stackQueue.enqueue(wordLadder);
        while (!stackQueue.isEmpty()) {
            wordLadder = stackQueue.dequeue();
            string topWord = wordLadder.peek();
            if (topWord == destinationWord) {
                while (!wordLadder.isEmpty()) {
                    cout << wordLadder.pop() << " ";
                }
                break;
            } else {
                for (string word: searchAllNeighbors(english, usedWords, topWord)) {
                    Stack<string> wordLadderClone = wordLadder;
                    wordLadderClone.push(word);
                    stackQueue.enqueue(wordLadderClone);

                }
            }  

        }
        return 0;

    }

        

 
    cout << "Have a nice day." << endl;
    return 0;
}

void AskUserForTheDictionaryFile(string prompt, ifstream & infile) {
    while (true){
        cout << prompt << endl;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail()) break;
        cout << "Unable to open " << filename << endl;
        infile.clear();
    }
}

bool IsAllAlpha(string & str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isalpha(str[i])) return false;
    }
    return true;
}

/**
 * Procedure: welcome()
 * Prints out a greeting on two lines.
 */
static void welcome() {
    cout << "Welcome to the CS106 word ladder application!" << endl;
    cout << "Please give me two English words, and I will change the first into the second by changing one letter at a time." << endl << endl;
}

/**
 * Function: getEnglishWord
 * getEnglishWord is similar to the Stanford getLine function but also adds
 * the program-specific requirements of checking if the user's input is an
 * English word or blank. Rather than calling a separate helper function
 * to determine if the user's input is an English word and housing all
 * condition checks in the main, this function can be called to check any word.
 * It returns a boolean as the check.
 * Parameters: dictionary declared in main as constant reference, a user-inputted word
 * that needs to be validated as a constant reference, and the prompt as a literal
 */
static bool getEnglishWord(const Lexicon & dictionary, string& word, string prompt) {
    cout << prompt;
    getline(cin, word);
    if (word.empty()) {
        return true;
    }
    else if (dictionary.contains(word)) {
        return false;
    } 
    cout << "Your response should to be an English word, so please try again." << endl;
    return true;
}

static bool checkWordEndpoints(const Lexicon& dictionary, 
            const string& sourceWord, string& destinationWord) {
    if (sourceWord.length() != destinationWord.length()) {
    cout << "The two endpoints must contain the same number of characters, or else no word ladder can exist." ;
    cout << endl;
    return getEnglishWord(dictionary, destinationWord, "Please enter the destination word [return to quit]: ");
    }
    return false;
}


Lexicon searchAllNeighbors(const Lexicon & dictionary, Lexicon & usedWords,
        const string & topWord) {
    Lexicon allNeighbors;
    string alphabets = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < topWord.length(); i++) {
        for(int j = 0; j < alphabets.length(); j++) {
            string testWord = topWord;
            testWord[i] = alphabets[j];
            if(dictionary.contains(testWord) && !usedWords.contains(testWord)) {
                allNeighbors.add(testWord);
                usedWords.add(testWord);
            }
        }
    }
    return allNeighbors;
    
}
