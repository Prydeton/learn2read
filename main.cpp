#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

void displayWelcome() {
    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Welcome to learn2read" << std::endl;
    std::cout << "The interactive tool designed to help you learn to read binary, octal and hexadecimal" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
}

int getSelection(std::string title, std::map<int, std::string> &options) {
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
    std::cout << "Please select " << title << " " << std::endl;
    for (auto const& [key, val] : options) {
        std::cout << key << ". " << val << std::endl; 
    }
    int option = 0;
    while (option < 1 || option > options.size()) {
        std::cout << "Option: ";
        std::cin >> option;
    }
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
    return option;
}

std::string decimalToBinary(int decimal) {
    int binaryArray[8]{-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while (decimal > 0) {
        binaryArray[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }
    std::string binarystring = "";
    for (int i = 7; i >= 0 ; i--) {
        if (binaryArray[i] != -1) {
            binarystring.append(std::to_string(binaryArray[i]));
        } 
    }
    return binarystring;
}

std::string decimalToNnary(int decimal, int radix) {
    char *charset = "0123456789abcdef";
    if (radix < 2 || radix > 16) {
        return "invalid radix";
    }
    std::string output;
    while(decimal > 0) {
        output += charset[decimal % radix];
        decimal = decimal / radix;
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::string decimalToHexadecimal(int decimal) {
    std::stringstream ss;
    ss << std::hex << decimal;
    std::string res ( ss.str() );
    return res;
}

std::string decimalToOctal(int decimal) {
    std::stringstream ss;
    ss << std::oct << decimal;
    std::string res ( ss.str() );
    return res;
}

std::map<int, std::vector<std::string>> calculateProblemSet(int maxValue, int chosenBaseSystem) {
    std::map <int, std::vector<std::string>> problemSet;
    for (int i = 1; i <= maxValue; i++) {
        if (chosenBaseSystem == 1) {
            std::vector<std::string> questionDetails = {decimalToBinary(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        } else if (chosenBaseSystem == 2) {
            std::vector<std::string> questionDetails = {decimalToNnary(i, 3), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        }else if (chosenBaseSystem == 3) {
            std::vector<std::string> questionDetails = {decimalToOctal(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        } else if (chosenBaseSystem == 4) {
            std::vector<std::string> questionDetails = {decimalToHexadecimal(i), "CORRECT", "NOT COMPLETE"};
            problemSet.insert(make_pair(i, questionDetails));
        }
    }
    return problemSet;
}

std::map<int, std::vector<std::string>> getmapOfValues() {
    std::map <int, std::vector<std::string>> problemSet;
    std::map <int, std::string> baseSystems { {1, "Learn2Read Binary"}, {2, "Learn2Read Ternary"}, {3, "Learn2Read Octal"}, {4, "Learn2Read Hexadecimal"} };
    std::map <int, std::string> difficulty { {1, "Level 1"}, {2, "Level 2"}, {3, "Level 3"}, {4, "Level 4"} };
    int chosenBaseSystem = getSelection("Base System", baseSystems);
    int chosenDifficulty = getSelection("Difficulty", difficulty);
    if (chosenDifficulty == 1) {
        problemSet = calculateProblemSet(25, chosenBaseSystem);
    } else if (chosenDifficulty == 2) {
        problemSet = calculateProblemSet(100, chosenBaseSystem);
    } else if (chosenDifficulty == 3) {
        problemSet =  calculateProblemSet(255, chosenBaseSystem);
    } else if (chosenDifficulty == 4) {
        problemSet =  calculateProblemSet(1023, chosenBaseSystem);
    }
    return problemSet;
}

std::map<int, std::vector<std::string>> testStudent(std::map <int, std::vector<std::string>> problemSet) {
    srand (time(NULL));
    for (int i = 0; i <= problemSet.size(); i++) {
        int questionNum = rand() % problemSet.size() + 1;
        if (problemSet[questionNum][2] == "NOT COMPLETE") {
            std::cout << "Convert " << problemSet[questionNum][0] << " to decimal: ";
            std::string answer;
            std::cin >> answer;
            problemSet[questionNum][2] = answer;
            if (answer != std::to_string(questionNum)) {
                problemSet[questionNum][1] = "INCORRECT";
                std::cout << "Incorrect answer - Answer was " << questionNum << std::endl;
            } else {
                std::cout << "Correct!" << std::endl;
            }
        }
    }
    return problemSet;
}

void displayResults(std::map<int, std::vector<std::string>> problemSet) {
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
    std::cout << "Displaying final results: " << std::endl; 
    int correctAnswers = 0;
    for (auto const& [key, val] : problemSet) {
        if (val[1] == "CORRECT") {
            correctAnswers += 1;
        }
         std::cout << "Convert " << val[0] << " to decimal. Correct Answer: " << key << ". " << "Your Answer: " << val[2] << ". " << val[1] << std::endl;
    }
    std::cout << "Final Score: " << std::to_string(correctAnswers) << "/" << std::to_string(problemSet.size());
}

void debugProblemSet(std::map<int, std::vector<std::string>> problemSet) {
    for (auto const& [key, val] : problemSet) {
         std::cout << "Convert " << val[0] << " to decimal. Correct Answer: " << key << ". " << "Your Answer: " << val[2] << ". " << val[1] << std::endl;  
    }
}

int main() {
    while (true) {
        displayWelcome();
        std::map<int, std::vector<std::string>> problemSet;
        problemSet = getmapOfValues();
        //debugProblemSet(problemSet);
        problemSet = testStudent(problemSet);
        displayResults(problemSet);
    }
    return -1;
}