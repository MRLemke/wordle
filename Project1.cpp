/*******************************************************************************
* Assignment: Project 1 -                                                      *
* Author: Owen Donohue                                                         *
* Date: Fall 2022                                                              *
* File: Project1.cpp                                                           *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/
#include <iostream>
#include "execute.h"
#include <vector>
#include <string>
#include <fstream>
#include<bits/stdc++.h>
#include <cstdlib>
#include <time.h>
using namespace std;


//This function will take a vector with letters and make them a word as a string.
//This is mainly for outputing the guesses that the AI will make.
string printOutWord(vector<char> letters) 

{
	string output = "";
	for (int i = 0; i< letters.size(); i++)
	
	{
		output+=letters[i];
	}
	
	return output;
}

//This function is supposed to read the Dictionary51.txt contents into a vector of strings called dictionary51Vector. 
//
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


//This function will return a string that will update what the AI knows so far. For example,
//if the secret word is world and the AI guesses raise first, the wrongLetters vector will be 
//updated with a,i,s,e and the possible letters will be updated with r. Nothing will happen to
//correctAnswer since there is no correct letters in the right spot.
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

//This function is going to sort the dictionary array with the knowledge the AI now knows.
//This function will be repeated twice at the beginning with the two base guesses "raise" and "donut"
//every iteration of the while loop in the main driver code. This function will be the main "logic" 
//where the dictionary narrows down the list by process of elimination, so when the AI chooses random guesses,
//there will be only a small number of choices to choose from.
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
//This is the final function. It will select a random integer and that integer will be the index of the 
//next guess after the first two static guesses.
string randomGuess(vector <string>& dictionaryVector)
{
	srand(time(0));
	int maxNumber = dictionaryVector.size();
	int randomInt = rand()%maxNumber;
	string currentGuess = dictionaryVector[randomInt];
	srand(time(0));
	return currentGuess;
	
}

//Main driver code
int main ()

{
	
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
