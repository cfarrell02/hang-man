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


using namespace std;

string guessLetter(string word,char letter, string guessWord);
bool stringEqual(string word,string guess);
static string toUpper(string str);
void pause();


int main(int argc, const char * argv[]) {
    //List of possible words
    vector<string> words = {"Cartography","Embargo","Treasure"};
    shuffle(words.begin(),words.end(),default_random_engine(static_cast<unsigned int>(time(0))));
    //Select last word from shuffled list
    string word = words.back();
    //Creates dummy word of dashes
    string guessWord(word.size(),'-');
    string guess = "0";
    cout<<guessWord<<endl;
    cout<<"Guesses remaining "<<word.size()<<endl;
        for(unsigned int guesses = 0; ;){ // guesses variable delared in for loop
            //Instructs player to make a guess
            cout<<"Word "<<3-words.size()<<"\nGuess a letter, or the full word (if you think you know it!)\n(Enter '0' to skip or '-1' to quit)\n> ";
            cin>>guess;
            if(guess == "0" || guess == "-1") break; // If guess is an escape character, break
            
            //If the player's incorrect guesses exceeds the word size
            if(guesses>=word.size()){
                cout<<"You've run out of guesses"<<endl; //End the game
                break;
            }
            
            // If a char has been inputted...
            if(guess.size()==1){
                string oldval = guessWord;
                guessWord = guessLetter(word,guess[0], guessWord); // Updated the guessWord string with any new relevant letters
                if(oldval == guessWord){ // checks for any change in the updated string
                    ++guesses ;// letter was not present
                }
                cout<<guessWord<<endl;
            }
            
            //If a string has been inputted...
            else{
                if(stringEqual(word,guess)){
                    cout<<"Congratulations, you guessed it!!"<<endl; //Correct guess, Congratulates player
                    break;
                }else{
                    cout<<"Sorry, thats not it"; // Incorrect guess
                    ++guesses;
                }
            }
            //If the player has guessed every letter in the word
            if(toUpper(guessWord) == toUpper(word)){
                cout<<"Congratulations, you guessed it!!"<<endl; //Correct guess, Congratulates player ends game
                break;
            }
            cout<<"Guesses remaining: "<<word.size()- guesses<<endl; // reads out remaining guesses
        }
    return 0;
}

string guessLetter(string word,char letter,string guessWord){
    for(int i = 0; i < word.size();++i){
        if(toupper(word[i])==toupper(letter)){ //Checks if a char is in the string and replaces dashes with it if so.
            guessWord[i]=word[i];
        }
    }
    return guessWord;
}

inline bool stringEqual(string word,string guess){
    return toUpper(guess) == toUpper(word); // Simple word comparison
}

static string toUpper(string str){
    transform(str.begin(), str.end(),str.begin(), ::toupper); //Uses transform to change all chars in string to uppercase
    return str;
}

