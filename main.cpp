#include <iostream>
#include <map>
#include <bits/stdc++.h>
using namespace std;

void displayWelcome() {
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "Welcome to learn2read" << endl;
    cout << "The interactive tool designed to help you learn to read binary, octal and hexadecimal" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
}

int getSelection(string title, map<int, string> &options) {
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Please select " << title << " " << endl;
    for (auto const& [key, val] : options) {
        cout << key << ". " << val << endl; 
    }
    int option = 0;
    while (option < 1 || option > options.size()) {
        cout << "Option: ";
        cin >> option;
    }
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    return option;
}

string decimalToBinary(int decimal) {
    int binaryArray[8]{-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while (decimal > 0) {
        binaryArray[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }
    string binaryString = "";
    for (int i = 7; i >= 0 ; i--) {
        if (binaryArray[i] != -1) {
            binaryString.append(to_string(binaryArray[i]));
        } 
    }
    return binaryString;
}

string decimalToHexadecimal(int decimal) {
    stringstream ss;
    ss << hex << decimal;
    string res ( ss.str() );
    return res;
}

string decimalToOctal(int decimal) {
    stringstream ss;
    ss << oct << decimal;
    string res ( ss.str() );
    return res;
}

map<int, vector<string>> calculateProblemSet(int maxValue, int chosenBaseSystem) {
    map <int, vector<string>> problemSet;
    for (int i = 1; i <= maxValue; i++) {
        if (chosenBaseSystem == 1) {
            vector<string> questionDetails = {decimalToBinary(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        } else if (chosenBaseSystem == 2) {
            vector<string> questionDetails = {decimalToOctal(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        } else if (chosenBaseSystem == 3) {
            vector<string> questionDetails = {decimalToHexadecimal(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        }
    }
    return problemSet;
}

map<int, vector<string>> getMapOfValues() {
    map <int, vector<string>> problemSet;
    map <int, string> baseSystems { {1, "Learn2Read Binary"}, {2, "Learn2Read Octal"}, {3, "Learn2Read Hexadecimal"} };
    map <int, string> difficulty { {1, "Level 1"}, {2, "Level 2"}, {3, "Level 3"} };
    int chosenBaseSystem = getSelection("Base System", baseSystems);
    int chosenDifficulty = getSelection("Difficulty", difficulty);
    if (chosenDifficulty == 1) {
        problemSet = calculateProblemSet(25, chosenBaseSystem);
    } else if (chosenDifficulty == 2) {
        problemSet = calculateProblemSet(100, chosenBaseSystem);
    } else if (chosenDifficulty == 3) {
        problemSet =  calculateProblemSet(255, chosenBaseSystem);
    }
    return problemSet;
}

map<int, vector<string>> testStudent(map <int, vector<string>> problemSet) {
    srand (time(NULL));
    for (int i = 0; i <= problemSet.size(); i++) {
        int questionNum = rand() % problemSet.size() + 1;
        if (problemSet[questionNum][2] == "NOT COMPLETE") {
            cout << "Convert " << problemSet[questionNum][0] << " to decimal: ";
            string answer;
            cin >> answer;
            problemSet[questionNum][2] = answer;
            if (answer != to_string(questionNum)) {
                problemSet[questionNum][1] = "INCORRECT";
                cout << "Incorrect answer - Answer was " << questionNum << endl;
            } else {
                cout << "Correct!" << endl;
            }
        }
    }
    return problemSet;
}

void displayResults(map<int, vector<string>> problemSet) {
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Displaying final results: " << endl; 
    int correctAnswers = 0;
    for (auto const& [key, val] : problemSet) {
        if (val[1] == "CORRECT") {
            correctAnswers += 1;
        }
         cout << "Convert " << val[0] << " to decimal. Correct Answer: " << key << ". " << "Your Answer: " << val[2] << ". " << val[1] << endl;
    }
    cout << "Final Score: " << to_string(correctAnswers) << "/" << to_string(problemSet.size());
}

void debugProblemSet(map<int, vector<string>> problemSet) {
    for (auto const& [key, val] : problemSet) {
         cout << "Convert " << val[0] << " to decimal. Correct Answer: " << key << ". " << "Your Answer: " << val[2] << ". " << val[1] << endl;  
    }
}

int main() {
    while (true) {
        displayWelcome();
        map<int, vector<string>> problemSet;
        problemSet = getMapOfValues();
        //debugProblemSet(problemSet);
        problemSet = testStudent(problemSet);
        displayResults(problemSet);
    }
    return -1;
}