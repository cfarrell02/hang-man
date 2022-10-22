//
//  main.cpp
//  hang man
//
//  Created by Cian Farrell on 21/10/2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <random>
#include <sstream>
#include <fstream>


using namespace std;

static string g_word; // Global variable (im sorry) to allow for global access to current word.
string guessLetter(char letter, string guessWord);
bool isTheWord(string guess);
static string toUpper(string str);
void pause();


int main(int argc, const char * argv[]) {
    //List of possible words
    vector<string> words = {"Cartography","Embargo","Treasure"};
    
//    fstream newfile;
//    string line;
//    newfile.open("words.txt", ios::in);           Not working properly :(
//    if(newfile.is_open()){
//        cout<<line<<endl;
//        while(getline(newfile,line)) words.push_back(line);
//    }
    
    while(words.size()>0){
        shuffle(words.begin(),words.end(),default_random_engine(static_cast<unsigned int>(time(0))));
        //Select last word from shuffled list
        g_word = words.back();
        //Creates dummy word of dashes and removes it from vector
        string guessWord(g_word.size(),'-');
        words.pop_back();
        string guess = "0";
        cout<<guessWord<<endl;
        for(int guesses = 1; ;){ // guesses variable delared in for loop
            //Instructs player to make a guess
            cout<<"Word "<<3-words.size()<<"\nGuess a letter, or the full word (if you think you know it!)\n(Enter '0' to skip or '-1' to quit)\n> ";
            cin>>guess;
            if(guess == "0" || guess == "-1") break; // If guess is an escape character, break
            
            //If the player incorrect guesses exceeds the word size
            if(guesses>=g_word.size()){
                cout<<"You've run out of guesses"<<endl;
                if(words.size()>=1){
                    pause(); // pauses for input if more words are still to go.
                }
                break;
            }
            // If a char has been inputted...
            if(guess.size()==1){
                string oldval = guessWord;
                guessWord = guessLetter(guess[0], guessWord); // Updated the guessWord string with any new relevant letters
                if(oldval == guessWord) ++guesses ;// guess was wrong
                cout<<guessWord<<endl;
            }
            //If a string has been inputted...
            else{
                if(isTheWord(guess)){
                    cout<<"Congratulations, you guessed it!!"<<endl; //Correct guess, Congratulates player and moves on to the next word
                    if(words.size()>=1){
                        // wait for prompt before moving on
                        pause(); // pauses for input
                    }
                    break;
                }else{
                    cout<<"Sorry, thats not it"; // Incorrect guess
                    ++guesses;
                }
            }
            //If the player has guessed every letter in the word
            if(toUpper(guessWord) == toUpper(g_word)){
                cout<<"Congratulations, you guessed it!!"<<endl; //Correct guess, Congratulates player and moves on to the next word/ends game
                if(words.size()>=1) pause();
                break;
            }
            cout<<"Guesses remaining: "<<g_word.size()- guesses<<endl;
        }
        if(guess=="-1") break; // Ends game if -1 is entered
    }
    if(words.size()<1)
    cout<<"You guessed all the words!! Congratulations"<<endl;
    return 0;
}

string guessLetter(char letter,string guessWord){
    for(int i = 0; i < g_word.size();++i){
        if(toupper(g_word[i])==toupper(letter)){ //Checks if a char is in the string and replaces dashes with it if so.
            guessWord[i]=g_word[i];
        }
    }
    return guessWord;
}

inline bool isTheWord(string guess){
    return toUpper(guess) == toUpper(g_word); // Simple word comparison
}

static string toUpper(string str){
    transform(str.begin(), str.end(),str.begin(), ::toupper); //Used transform to change all chars in string to uppercase
    return str;
}

void pause(){
  #ifdef __APPLE__
    //cout<<"Apple";
    system( "read -n 1 -s -p \"...Next word?\"");  // platform dependent
  #elif _WIN32
   // cout<<"Win";
    system("pause");
#else
    cout<<"Not apple or win";
  #endif
}
