#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
#include<cstdlib> // For rand() function
//#include<SDL/SDL.h>
using namespace std;
void PrintMessage(string message, bool printTop = true,bool printBottom = true)
{
	if(printTop)
	{
		cout<<"+------------------------------------+"<<endl;
		cout << "|";
	}
	else
	{
		cout<< "|";
	}
	bool front = true;
	for(int i = message.length();i < 36; i++)
	{
		if(front)
		{
			message = " "+ message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}
	cout<<message.c_str();
	
	if(printBottom)
	{
		cout<< "|" <<endl;
		cout<<"+------------------------------------+"<<endl;
		
	}
	else
	{
		cout<< "|" <<endl;
	}
	
	
}
void drawHangMan(int guessCount = 0)
{
	if(guessCount >= 1)
		PrintMessage("|",false,false);
	else
		PrintMessage("",false,false);
		
	if(guessCount >= 2)
		PrintMessage("|",false,false);
	else
		PrintMessage("",false,false);
		
	if(guessCount >= 3)
		PrintMessage("O",false,false);
	else
		PrintMessage("",false,false);
	
	if(guessCount == 4)
		PrintMessage("/",false,false);
		
	if(guessCount == 5)
		PrintMessage("/|",false,false);
	
	if(guessCount >= 6)
		PrintMessage("/|\\",false,false);
	else
		PrintMessage("", false, false);
	
	if(guessCount >= 7)
		PrintMessage("|",false,false);
	else
		PrintMessage("",false,false);
	
	if(guessCount == 8)
		PrintMessage("/",false,false);
	
	if(guessCount >= 9)
		PrintMessage("/ \\",false,false);
	else
		PrintMessage("",false,false);
	
}
void PrintLetters(string input, char from, char to)
{
	string s;
	for(char i=from; i<= to; i++ )
	{
		if(input.find(i) == string::npos) // if string find npos that's mean didn't have character
		{
//			s += i + " "; not possible add character with space
			s += i; 	 // space be added after adding the character
			s += " ";
		}
		else
		{
			s += "  ";
		}
	}
	PrintMessage(s, false, false);
}
void PrintAvailbleLetters(string taken)
{
	PrintMessage("Availble Letters");
	PrintLetters(taken, 'A','M');
	PrintLetters(taken, 'N','Z');
}
bool PrintWord_And_CheckWin(string word, string guessed)
{
	bool won = true;	// by assuming that user always win
	string s;
	for(int i = 0; i< word.length(); i++)
	{
		if(guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
		PrintMessage(s,false);
		return won;
	}
}


string LoadRandomWord(string path)
{
	
	int lineCount = 0;
	string word;
	vector<string> v; 	//
	ifstream reader("Words.txt");
	if (reader.is_open())
	{
		while(std::getline(reader,word));
		v.push_back(word);
		int randomLine = rand()% v.size();
		// 1 2 3 4 5 
		word = v.at(randomLine);
		reader.close();
	}
	return word;
}
int TriesLeft(string word, string guessed)
{
	int error = 0;
	for(int i =0; i < guessed.length(); i++)
	{
		if(word.find(guessed[i]) == string::npos)
		error++;
		
	}
	return error; 
}
int main()
{
	srand(time(0));
	string guesses;
	string wordToGuess;
	wordToGuess = LoadRandomWord("Words.txt");
	
	cout<<wordToGuess<<endl<<endl;
	PrintMessage("Hang Man");
	int tries = 0;
	bool win = false;
	do{
		system("cls");
		PrintMessage("HangMan");
		drawHangMan(tries);
		PrintAvailbleLetters(guesses);
		PrintMessage("Guess the Word");
		PrintWord_And_CheckWin(wordToGuess, guesses);
		if(win)
			break;
		char x;
		cout << ">"; cin>>x;
		if(guesses.find(x) == string::npos)
			guesses += x;
		
		tries = TriesLeft(wordToGuess,guesses);
		
	}
	while(tries<10);
	if (win)
        PrintMessage("YOU WON!");
    else
        PrintMessage("GAME OVER");
	//drawHangMan(1);
//	drawHangMan(9);
	system("pause");
	getchar();
	return 0;
}
