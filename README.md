# Wordle

Objective:
[Wordle](https://www.nytimes.com/games/wordle/index.html) is a word puzzle game where players attempt to guess a hidden five-letter word.

Gameplay:

The game begins with a random five-letter word chosen by the game or a designated "Wordle Master."
Players take turns guessing five-letter words.
After each guess, the Wordle Master provides feedback in the form of colored tiles:

* Yellow: Correct letter but in the wrong position.
* Green: Correct letter in the correct position.
* Gray/White: Incorrect letter.

## User Guide

Source.cpp attempts to help the user solve the daily Wordle game by by providing the user with a list of possible remaining words given existing guess constraints the user inputs.

### Run File

Clone this github repo and run the main file by typing g++ Source.cpp to compile the file, then ./a.out to run the executable. 
Upon the prompt: "Enter number of letters (use -1 for full dict):", enter 5 since standard Wordle limits the guess to 5 characters.

This Wordle program is takes 3 user inputs for the green, yellow, and black lettersand outputs a list of remaining valid guess words. 
When prompted, the user input should be in format: "0l0m0", where 0 denotes letters of other color and "l" and "o" denote letters of the color being prompted. 
If all chars are 0 simply press enter to auto-input all '0's.
