Word Game

This is a C++ console-based word game designed to help practice English-Turkish vocabulary.
The game uses a dictionary file (dictionary.txt) to store words and their meanings, and allows the user to play a quiz, list words, or add new ones.

Features

Play the Word Game

Randomly asks English → Turkish or Turkish → English questions.

Multiple-choice format with 4 shuffled options.

Scoring system:

+3 points for correct answers

-1 point for wrong answers

Game ends after 10 questions or 3 mistakes.

Word Management

Words and meanings are stored in dictionary.txt.

Add new words via the menu.

Automatically sorts the dictionary alphabetically.

List all stored words with their meanings.

Menus

Main Menu

Play Word Game

Show Word List

Add a New Word

Exit

Post-Game Menu

Replay the Game

Return to Main Menu

Exit

File Structure

dictionary.txt

Stores words in the format:

word:meaning
book:kitap
computer:bilgisayar


Automatically created if it does not exist.

main.cpp (this file)

Contains all functions and game logic.

Functions Overview

menu() → Displays the main menu.

startGame() → Runs the quiz loop, handles scoring and mistakes.

listWords() → Displays all words stored in the dictionary.

addWord() → Adds a new word with its meaning and sorts the dictionary.

loadDict() → Reads the dictionary from dictionary.txt.

saveDict() → Writes updated words back to dictionary.txt.

getOpts() → Generates 4 answer choices (1 correct + 3 random).

shuffle() → Randomizes the order of options.

postGameMenu() → Handles replay, return to menu, or exit.

How to Compile and Run

Save the code as main.cpp.

Open a terminal and compile using:

g++ main.cpp -o wordgame


Run the program:

./wordgame


The program will create dictionary.txt if it does not exist.

Development Notes

Requires at least 4 words in the dictionary to start the game.

Randomization uses srand(time(0)).

Input is case-sensitive.

Dictionary words are sorted alphabetically after each addition.
