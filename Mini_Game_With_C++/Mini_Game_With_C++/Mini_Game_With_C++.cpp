#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // srand rand
#include <ctime>
#include <algorithm>

using namespace std;


void menu(); // Function to show the menu  
void startGame(); // Function to start game
void listWords(); // Function to list words 
void addWord(); // Function to add new word to dict
vector<pair<string, string>> loadDict(); // Load dict from file 
void saveDict(const vector<pair<string, string>>& dict); // Save dict to file
vector<string> getOpts(const vector<pair<string, string>>& dict, string correct, bool isEng); // Get options for quiz
void shuffle(vector<string>& opt); // Shuffle options randomly
void postGameMenu(int scr); // New post game menu after finishing game

int main() {

    int c; // choice var



    do {
        menu(); // Show menu


        cin >> c; // User choice input


        if (c == 1) {
            startGame(); // Start game if choice is 1




        }
        else if (c == 2) {

            listWords(); // List all words in dict

        }
        else if (c == 3) {
            addWord(); // Add a word to dict
        }
        else if (c == 4) {

            cout << "Bye!" << endl; // Exit message

            break;

        }
        else {


            cout << "Invalid. Try agn." << endl; // Invalid input

        }


    } while (c != 4); // Keep looping until exit is selected

    return 0;
}


// Menu function: show main menu
void menu() {
    cout << endl << "\nW o r d   G a m e Menu\n" << endl; // Main menu
    cout << "1. Play Word Game " << endl; // Option 1: play game
    cout << "2. Show Word List." << endl; // Option 2: show word list
    cout << "3. Add A New Word." << endl; // Option 3: add a new word
    cout << "4. Exit " << endl << "   ur Choice: "; // Option 4: exit
}



// Load dict from the file
vector<pair<string, string>> loadDict() {
    vector<pair<string, string>> dict;
    ifstream file("dictionary.txt");
    string wrd, mean;

    // Open dictionary file
    if (file.is_open()) {
        while (getline(file, wrd, ':') && getline(file, mean)) {
            dict.push_back(make_pair(wrd, mean)); // Add word and meaning


        }

        file.close();
    }
    else {


        cout << "Couldnt open dictionary.txt! Creating a new file." << endl; // If file open fails
        ofstream newFile("dictionary.txt"); // Create file if it does not exist
        newFile.close();
    }

    return dict; // Return the dict
}


// Save dict to file
void saveDict(const vector<pair<string, string>>& dict) {
    ofstream file("dictionary.txt"); // Open the file "dictionary.txt" to write
    if (file.is_open()) { // Check if the file opened successfully
        // Loop through all words in the dictionary
        for (int i = 0; i < dict.size(); i++) {
            file << dict[i].first << ":" << dict[i].second << endl; // Write the word and its meaning to the file
        }
        file.close(); // Close the file after writing
    }
    else {
        cout << "Cant Save" << endl; // Show an error message if the file can't be opened
    }
}


void listWords() {

    vector<pair<string, string>> dict = loadDict(); // Load dict

    if (dict.empty()) {
        cout << "None words found. Add new? " << endl; // If dict is empty
        return;
    }


    cout << endl << "---WORDS--- " << endl;
    for (auto word : dict) {
        cout << word.first << " : " << word.second << endl; // Display word and its meaning

    }

    cout << endl;
}

void addWord() {
    string wrd, trns;
    vector<pair<string, string>> dict = loadDict(); // Load dictionary from the file

    cout << "Write word: "; // Ask the user to write the word
    cin >> wrd; // Input the word
    cout << "Meaning: "; // Ask the user to write the meaning
    cin >> trns; // Input the meaning

    dict.push_back(make_pair(wrd, trns)); // Add the new word and meaning to dictionary

    // Sort the dictionary alphabetically by word
    for (int i = 0; i < dict.size() - 1; i++) { // Loop through each word in the dictionary
        for (int j = i + 1; j < dict.size(); j++) { // Compare it with the next words
            if (dict[i].first > dict[j].first) { // If current word is bigger than next one
                // Swap the words to sort them alphabetically
                pair<string, string> temp = dict[i];
                dict[i] = dict[j];
                dict[j] = temp;
            }
        }
    }

    saveDict(dict); // Save the sorted dictionary to the file

    cout << "Saved Word." << endl; // Confirmation message
}

// Get options for the quiz
vector<string> getOpts(const vector<pair<string, string>>& dict, string correct, bool isEng) {
    vector<string> opts;
    opts.push_back(correct); // Add the correct answer to the options

    srand(time(0)); // Randomize options

    while (opts.size() < 4) { // Make sure there are 4 options
        string temp; // Temporary string for new option

        if (isEng) { // If asking for English word
            temp = dict[rand() % dict.size()].first; // Randomly pick English word
        }
        else { // If asking for Turkish meaning
            temp = dict[rand() % dict.size()].second; // Randomly pick Turkish meaning
        }

        // Check if temp is already in opts
        bool isDuplicate = false;
        for (int i = 0; i < opts.size(); i++) {
            if (opts[i] == temp) { // If duplicate, mark it
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) { // If its not duplicate, add it
            opts.push_back(temp);
        }
    }

    shuffle(opts); // Shuffle to make random order of options

    return opts; // Return the shuffled options
}


// Shuffle options randomly
void shuffle(vector<string>& opt) {
    srand(time(0));
    for (int i = 0; i < opt.size(); i++) {
        int rI = rand() % opt.size();
        swap(opt[i], opt[rI]); // Swap option positions
    }
}


// Start game
void startGame() {
    vector<pair<string, string>> dict = loadDict(); // Load dict

    if (dict.size() < 4) {

        cout << "Need more W to play. Min 4. " << endl; // Not enough words to play

        return;
    }

    srand(time(0)); // Seed random number generator

    int scr = 0, mstks = 0; // Initialize score and mistakes counters
    int questions = 0; // Counter for number of questions



    while (mstks < 3 && questions < 10) { // Max 10 questions and 3 mistakes
        // Randomly pick a word from dictionary
        int randIndex = rand() % dict.size();
        pair<string, string> crWord = dict[randIndex];

        bool isToTurkish = rand() % 2 == 0; // Randomly choose if its english to turkish or turkish to english

        string ques;
        if (isToTurkish) {
            ques = "EN->TR: " + crWord.first + " ?"; // Question from English to Turkish
        }
        else {
            ques = "TR->EN: " + crWord.second + " ?"; // Question from Turkish to English
        }

        // Get options for quiz, passing the correct answer and if it's toTurkish or not
        string correctAnswer = isToTurkish ? crWord.second : crWord.first;
        vector<string> opts = getOpts(dict, correctAnswer, !isToTurkish);

        cout << endl << ques << endl;

        char opLbl = 'a'; // Start options with 'a'
        for (int i = 0; i < opts.size(); i++) {
            cout << opLbl++ << ". " << opts[i] << endl; // Print each option
        }

        char ans;
        cout << "Select: ";
        cin >> ans; // Get user input for answer

        if (opts[ans - 'a'] == correctAnswer) { // Check if the selected answer is correct
            cout << "Yes!!" << endl;
            scr += 3; // Add points for correct answer
        }
        else {
            cout << "Nope. Ans: " << correctAnswer << endl;
            scr -= 1; // Subtract points for wrong answer
            mstks++; // Increment mistake count
        }

        questions++; // Increment question count
    }


    cout << "Done. Score: " << scr << endl; // End of game, display score
    postGameMenu(scr); // Call post-game menu with final score
}


// Post game menu after finishing the game
void postGameMenu(int scr) {
    int choice;
    cout << "\n---Game Over---" << endl;
    cout << "Your score: " << scr << endl; // Show total score
    cout << "1. Replay The Game" << endl; // Option to replay the game
    cout << "2. Previous Menu" << endl; // Go back to the main menu
    cout << "3. Exit" << endl; // Exit the program
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        startGame(); // Replay the game
    }
    else if (choice == 2) {
        return; // Return to the main menu
    }
    else if (choice == 3) {
        cout << "Exiting..." << endl; // Exit program
        exit(0);
    }
    else {
        cout << "Invalid choice, try again." << endl; // Invalid input
        postGameMenu(scr); // Ask again for the choice
    }
}
