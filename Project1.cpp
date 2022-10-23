/***************************************************************************************
* Assignment: Project 1 - Wordle Solver                                                *
* Author: Owen Donohue                                                                 *
* Date: Fall 2022                                                                      *
* File: Project1.cpp                                                                   *
*                                                                                      *
* Description: This file contains the code that will find a 5 letter word              *
*with no repeating letters. This code will import a dictionary and narrow it           *
*down with the information gained by calling the check.cpp program.                    *
*When the word in dictionary is found and is the same as the word in secret.txt        *
*(without explicitly looking at secret.txt), the program will output "I win!",         *
*along with the previously guessed words the program had used. If the word isn't found,*
*there will be an output "I'll do better next time".                                   *
***************************************************************************************/
#include <iostream>
#include "execute.h"
#include <vector>
#include <string>
#include <fstream>
#include<bits/stdc++.h>
#include <cstdlib>
#include <time.h>
using namespace std;

/********************************************************************************************************************
*This function is supposed to read the Dictionary51.txt contents into a vector of strings called dictionary51Vector.* 
********************************************************************************************************************/
void createDictionaryVector(vector<string> & dictionary51Vector)

{
	string temp ="";
	ifstream file("Dictionary51.txt");
	if (!file.is_open()) {
		cout << "Failed to open file, rest in pieces" << endl;
		
	}
	else
	{
		
		while(getline(file, temp))
		{
			dictionary51Vector.push_back(temp);
		}
		file.close();
	}
}

/**********************************************************************************************
*This function will return a string that will update what the AI knows so far. For example,   *
*if the secret word is world and the AI guesses raise first, the wrongLetters vector will be  *
*updated with a,i,s,e and the possible letters will be updated with r. Nothing will happen to *
*correctAnswer since there is no correct letters in the right spot.                           *
***********************************************************************************************/
string checkForMatchingCharacters(string & currentGuess, string& correctAnswer, string & checkOutput, string& wrongLetters, string& possibleLetters) 
{
	for (int i = 0; i< 5; i++) {
		if (checkOutput[i] == '+') {
			
			correctAnswer[i]=currentGuess[i];
			
		}
		else if(checkOutput[i] == '.')
		{
			possibleLetters+= currentGuess[i];
		}
		else if(checkOutput[i] == '-')
		{ 
			wrongLetters.push_back(currentGuess[i]);
		}
		
	}
	
	return correctAnswer;
}
/**************************************************************************************************************
*This function is going to sort the dictionary array with the knowledge the AI now knows.                     *
*This function will be repeated twice at the beginning with the two base guesses "raise" and "donut"          *
*every iteration of the while loop in the main driver code. This function will be the main "logic"            *
*where the dictionary narrows down the list by process of elimination, so when the AI chooses random guesses, *
*there will be only a small number of choices to choose from.                                                 *
***************************************************************************************************************/
void narrowDownOptions(vector <string> & dictionary51Vector, string possibleLetters, string wrongLetters, string correctAnswer) 
{	
	int count1 = 0;
	while (count1 < dictionary51Vector.size())
	{
		for (int i = 0; i < wrongLetters.size(); i++)
		{
			for (int j = 0; j < dictionary51Vector.size(); j++)
			{
				if (dictionary51Vector[j].find(wrongLetters[i]) != string::npos)
				{	
					dictionary51Vector.erase(dictionary51Vector.begin()+j);
					
				}
			}	
			
		}
	
		for (int i = 0; i < possibleLetters.size(); i++) {
			for (int j = 0; j < dictionary51Vector.size(); j++) {
				if (dictionary51Vector[j].find(possibleLetters[i]) == string::npos)
				{
					dictionary51Vector.erase(dictionary51Vector.begin() + j);
				}
			}
		}
	
		for (int i = 0; i < correctAnswer.size(); i++) {
			for (int j = 0; j < dictionary51Vector.size(); j++) {
				if (dictionary51Vector[j][i] != correctAnswer[i] && correctAnswer[i]> 'A')
				{
					dictionary51Vector.erase(dictionary51Vector.begin() + j);
				}
			}
		}
	count1 ++;
	}
	
}
/*********************************************************************************************************
*This is the final function. It will select a random integer and that integer will be the index of the   *
*next guess after the first two static guesses. This function will return a string of the word that will *
*be chosen for the next guess!                                                                           *
**********************************************************************************************************/
string randomGuess(vector <string>& dictionaryVector)
{
	srand(time(0));
	int maxNumber = dictionaryVector.size();
	int randomInt = rand()%maxNumber;
	string currentGuess = dictionaryVector[randomInt];
	srand(time(0));
	if (dictionaryVector.size() < 3)
		currentGuess = dictionaryVector[0];
	return currentGuess;
	
}

/**************************************************************************************************************************
*This is the main function. In Main, two guesses will be selected at first, which are "raise" and "donut".                *
*this initial guesses will never change, as they narrow down the choice for the next guess word dramatically.             *
*There are 5 variables. String currentGuess stores the value of the next guess that the AI will make. The first           *
*two values are "raise" and "donut". The next values that are assigned are selected from the randomGuess function.        *
*The next variable stores the current knowledge of the correct guess, which is passed into the narrow down function.      *
*The cmd variable stores the command for the ./check program. The count variable will increment in the while loop.        *
*the vector dictionary51Vector will store the dictionary into a vector, and be narrowed down in the narrow down function. *
*wrongLetters and possibleLetters store the impossible letters and possible letter the word could have. Finally,          *
*the while loop will iterate until either the word is found or the 18 iterations have passed. (count startes at 3).       *
***************************************************************************************************************************/
int main ()

{
	//Initialzing the variables.
	string currentGuess = "raise";
	string correctAnswer = ".....";
	string cmd = "./check " + currentGuess;
	int count = 3; //This starts at 3 since we have 2 base guesses.
	string wrongLetters;
	string possibleLetters= "";
	vector <string> dictionary51Vector;
	
	string checkOutput = execute(cmd);
	createDictionaryVector(dictionary51Vector);
	
	//This is the static first two guess to eliminate as many words as possible before the while loop.
	correctAnswer=checkForMatchingCharacters(currentGuess, correctAnswer, checkOutput, wrongLetters, possibleLetters);
	narrowDownOptions(dictionary51Vector, possibleLetters, wrongLetters, correctAnswer);
	cout << "1" << " : " << currentGuess << " ==> " << checkOutput.substr(0,5) << endl;
	if (checkOutput.substr(0,5) == "+++++") {
		cout << "I win!" << endl;
		return 0;
	}
	//The 2nd static guess	
	currentGuess = "donut";
	cmd = "./check " + currentGuess;
	checkOutput = execute(cmd);
	
	correctAnswer=checkForMatchingCharacters(currentGuess, correctAnswer, checkOutput, wrongLetters, possibleLetters);
	narrowDownOptions(dictionary51Vector, possibleLetters, wrongLetters, correctAnswer);
	cout << "2" << " : " << currentGuess << " ==> " << checkOutput.substr(0,5) << endl;
	if (checkOutput.substr(0,5) == "+++++") {
		cout << "I win!" << endl;
		return 0;
	}
	//The while loop where the output is printed and random guesses are selected.
	
	while(count < 21 && checkOutput.substr(0,5) != "+++++")
	
	{
		currentGuess = randomGuess(dictionary51Vector);
		cmd = "./check " + currentGuess;
		checkOutput = execute(cmd);
		correctAnswer=checkForMatchingCharacters(currentGuess, correctAnswer, checkOutput, wrongLetters, possibleLetters);
		narrowDownOptions(dictionary51Vector, possibleLetters, wrongLetters, correctAnswer);
		cout << count << " : " << currentGuess << " ==> " <<  checkOutput.substr(0,5) << endl;
		count ++;
		
		
	}
		
	
	
				
	if (checkOutput.substr(0,5) == "+++++") {
		cout <<"I win!" << endl;
	}else {
		cout <<"I'll do better next time!" << endl;
	}
	
	return 0;
}
