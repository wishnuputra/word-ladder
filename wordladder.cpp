/* ===========================================================
 * WORD LADDER
 * ===========================================================
 *
 * A word ladder is a bridge between one word to another.
 * It is formed by changing one letter at a time, the changes
 * must formed another valid English word. Keep changing the
 * letter until it reaches the other word. The two words must
 * have same length and must be valid English words.
 *
 * For example:
 * code - cade - cate - date - data
 *
 * Date: 20 June 2019
 * Author: Wishnu
 * ===========================================================
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "lexicon.h"
#include "queue.h"
#include "stack.h"
#include "set.h"

using namespace std;

void welcomeMessage();
void readDictionary(Lexicon &dictionary);
void promptTwoWords(Lexicon &dictionary, string &word1, string &word2);
Stack<string> shortestWordLadder(Lexicon &dictionary, string word1, string word2);
void printLadder(Stack<string> &ladder, string word1, string word2);

int main() {
    Lexicon dictionary;
    string word1;
    string word2;

    welcomeMessage();
    readDictionary(dictionary);

    while (true) {
        promptTwoWords(dictionary, word1, word2);
        if (word1 == "" or word2 == "") {
            break;
        }
        Stack<string> ladder = shortestWordLadder(dictionary, word1, word2);
        printLadder(ladder, word1, word2);
    }

    cout << "Have a nice day." << endl;
    return 0;
}

/**
 * Method: welcomeMessage
 * ----------------------
 * Prints out welcome message on top of the screen.
 */
void welcomeMessage() {
    cout << "Welcome to CS106 Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}

/**
 * Method: readDictionary
 * ----------------------
 * Prompt the user for a file name. Then add that file
 * into a Lexicon dictionary. Reprompt until user type in
 * a valid file name.
 */
void readDictionary(Lexicon &dictionary) {
    ifstream input;
    promptUserForFile(input, "Dictionary file name? ");
    cout << endl;
    dictionary.addWordsFromFile(input);
}

/**
 * Method: promptTwoWords
 * ----------------------
 * Prompts the user for two words to try to connect with a
 * ladder. Reprompt until the user enter a valid English words
 * that contain inside the dictionary file. Both word must also
 * have the same length.
 */
void promptTwoWords(Lexicon &dictionary, string &word1, string &word2) {
    while (true) {
        word1 = getLine("Word #1 (or Enter to quit): ");
        if (word1 == "") break;
        word2 = getLine("Word #2 (or Enter to quit): ");
        if (word2 == "") break;
        word1 = toLowerCase(word1);
        word2 = toLowerCase(word2);

        if (dictionary.contains(word1) && dictionary.contains(word2)
                && word1.length() == word2.length() && word1 != word2) {
            break;
        } else if (word1.length() != word2.length()) {
            cout << "The two words must be the same length.";
            cout << endl << endl;
        } else if (!dictionary.contains(word1) || !dictionary.contains(word2)) {
            cout << "The two words must be found in the dictionary.";
            cout << endl << endl;
        } else if (word1 == word2){
            cout << "The two words must be different.";
            cout << endl << endl;
        }
    }
}

/**
 * Method: shortestWordLadder
 * ---------------------------
 * This method will find the shortest word ladder from
 * word2 back to word1.
 *
 * dictionary: Lexicon of dictonary used to find word ladder
 * word1, word2: string for word ladder
 *
 * return: word ladder between word1 and word2. If not
 * found, return empty ladder.
 */
Stack<string> shortestWordLadder(Lexicon &dictionary, string word1, string word2) {
    Queue<Stack<string>> queue;
    Stack<string> ladder;
    Set<string> seen;
    ladder.push(word1);
    queue.enqueue(ladder);

    while (!queue.isEmpty()) {
        ladder = queue.dequeue();
        string finalWord = ladder.peek();
        if (finalWord == word2) {
            return ladder;
        }
        string neighbor = finalWord;
        for (int i = 0; i < neighbor.length(); i++) {
            char ch = neighbor[i];
            for (int j = 1; j <= 'z' - 'a'; j++) {
                ch++;
                if (ch > 'z') {
                    ch = 'a';
                }
                neighbor[i] = ch;
                if (dictionary.contains(neighbor) && !seen.contains(neighbor)) {
                    seen.add(neighbor);
                    Stack<string> newLadder = ladder;
                    newLadder.push(neighbor);
                    queue.enqueue(newLadder);
                }        
            }
            neighbor = finalWord;
        }
    }
    ladder = {};
    return ladder;
}

/**
 * Method: printLadder
 * --------------------
 * This method will print the whole ladder stack by popping
 * the element one by one.
 */
void printLadder(Stack<string> &ladder, string word1, string word2) {
    if (ladder.isEmpty()) {
        cout << "No word ladder found from " << word2
             << " back to " << word1;
        cout << endl << endl;
    } else {
        cout << "A ladder from " << word2 << " back to "
             << word1 << ": " << endl;
        while (!ladder.isEmpty()) {
            cout << ladder.pop() << " ";
        }
        cout << endl << endl;
    }
}
