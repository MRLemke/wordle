/*******************************************************************************
* Assignment: CS 370 Exercise 5 - function for checking wordle guesses.        *
* Author: Owen Donohue                                                         *
* Date: Fall 2022                                                              *
* File: check.cpp                                                              *                                                               *
* Description: This file contains code that will output a string that has      *
* characters corrosponding to whether or not the characters of a Wordle guess  *
* are apart of the correct wordle word. "+" indicates that the character is in *
* the correct position and the correct character. "." indicates the character  *
* is correct but in the wrong position. "-" indicates the character is         *
* not in the correct word.                                                     *
*******************************************************************************/


#include <iostream>
#include "execute.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;






int main (int argc, char * argv [])
{
	string targetWord = "";
	ifstream fs;						 //Opens the file and creates and string with the target word in it.
	fs.open("secret.txt");               
	getline(fs, targetWord);
	fs.close();
	
 
	string cmd = " grep " + string(argv[1]) + " Dictionary51.txt"; //takes the guess word and puts it into a string, then checks to see if the word is in the dictionary.
	string resp = execute (cmd);
 
	if (resp == "") {                    //If the guessed word is not in Dictionary51.txt, then an error message will be printed.
		cout << "ERROR" << endl;         //
		return 0;                        //
	}
	string guess = string(argv[1]);  
	
	
	for (int i = 0; i < targetWord.size(); i++) {     //This is the loop that has the logic that will determine if the guess is correct or not.
		                                              //the original guess string is being overwritten with "+", "-", and ".".
													  //
		if (guess[i] == targetWord[i]) {
			guess[i] = '+';
		} else if (targetWord.find(guess[i])!=string::npos) {
			guess[i] = '.';
		} else {
			guess[i] = '-';
		}

	}
 
 
 cout << guess << endl;
	
 return 0;
}