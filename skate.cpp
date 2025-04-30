// Game of Skate Game by Jonathan Bailey
// Proto 2 for RC2

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits>

class Trick {
public:
    std::string name;
    int difficulty; // 1-10 scale

    Trick(std::string n, int d) : name(n), difficulty(d) {}
};

class Player {
public:
    std::string name;
    std::string letters;

    Player(std::string n) : name(n), letters("") {}

    void addLetter() {
        std::string skate = "SKATE";
        if (letters.length() < 5) {
            letters += skate[letters.length()];
        }
    }

    bool hasLost() {
        return letters == "SKATE";
    }

    void displayStatus() {
        std::cout << name << "'s status: ";
        if (letters.empty()) {
            std::cout << "No letters";
        } else {
            std::cout << letters;
        }
        std::cout << " (" << letters.length() << "/5)" << std::endl;
    }
};

class Game {
private:
    std::vector<Trick> tricks;
    Player player1;
    Player player2;
    Player* currentSetter;
    Player* currentResponder;
    std::mt19937 rng;

public:
    Game(std::string p1Name, std::string p2Name) 
        : player1(p1Name), player2(p2Name), 
          currentSetter(&player1), currentResponder(&player2) {
        // Seed random number generator
        rng.seed(static_cast<unsigned int>(time(nullptr)));
        
        // Initialize trick library
        initializeTricks();
    }

    void initializeTricks() {
        // Clear the vector first if it might have elements
        tricks.clear();
        
        // Add tricks one by one
        tricks.push_back(Trick("Ollie", 1));
        tricks.push_back(Trick("Kickflip", 3));
        tricks.push_back(Trick("Heelflip", 3));
        tricks.push_back(Trick("Pop Shove-it", 2));
        tricks.push_back(Trick("360 Flip", 5));
        tricks.push_back(Trick("Hardflip", 6));
        tricks.push_back(Trick("Varial Kickflip", 4));
        tricks.push_back(Trick("Varial Heelflip", 4));
        tricks.push_back(Trick("Backside 180", 2));
        tricks.push_back(Trick("Frontside 180", 2));
        tricks.push_back(Trick("Backside 360", 5));
        tricks.push_back(Trick("Frontside 360", 5));
        tricks.push_back(Trick("Impossible", 7));
        tricks.push_back(Trick("Casper Flip", 7));
        tricks.push_back(Trick("Nollie", 2));
        tricks.push_back(Trick("Switch Ollie", 3));
        tricks.push_back(Trick("Kickflip to Manual", 6));
        tricks.push_back(Trick("Impossible Late Flip", 9));
        tricks.push_back(Trick("Dolphin Flip", 8));
        tricks.push_back(Trick("Double Kickflip", 6));
    }

    void displayTricks() {
        std::cout << "\nAvailable tricks:" << std::endl;
        for (size_t i = 0; i < tricks.size(); i++) {
            std::cout << i + 1 << ". " << tricks[i].name 
                      << " (Difficulty: " << tricks[i].difficulty << ")" << std::endl;
        }
    }

    bool attemptTrick(const Trick& trick) {
        // Calculate success probability based on trick difficulty
        // Harder tricks have lower success rates
        int successChance = 95 - (trick.difficulty * 8);
        
        // Random number between 1-100
        std::uniform_int_distribution<int> dist(1, 100);
        int roll = dist(rng);
        
        return roll <= successChance;
    }

    void switchRoles() {
        if (currentSetter == &player1) {
            currentSetter = &player2;
            currentResponder = &player1;
        } else {
            currentSetter = &player1;
            currentResponder = &player2;
        }
        std::cout << "\n--- Roles switched! " << currentSetter->name 
                  << " is now setting tricks. ---\n" << std::endl;
    }

    void playRound() {
        std::cout << "\n" << currentSetter->name << "'s turn to set a trick." << std::endl;
        displayTricks();
        
        // Get trick selection
        int trickChoice;
        std::cout << "Choose a trick (1-" << tricks.size() << "): ";
        while (!(std::cin >> trickChoice) || trickChoice < 1 || trickChoice > static_cast<int>(tricks.size())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number between 1 and " << tricks.size() << ": ";
        }
        
        Trick selectedTrick = tricks[trickChoice - 1];
        std::cout << currentSetter->name << " attempts a " << selectedTrick.name << "..." << std::endl;
        
        bool setterSuccess = attemptTrick(selectedTrick);
        if (!setterSuccess) {
            std::cout << currentSetter->name << " failed to land the " << selectedTrick.name << "!" << std::endl;
            switchRoles();
            return;
        }
        
        std::cout << currentSetter->name << " landed the " << selectedTrick.name << "!" << std::endl;
        std::cout << "\n" << currentResponder->name << " must now match the " << selectedTrick.name << "..." << std::endl;
        
        // Simulate responder's attempt
        std::cout << "Press Enter to attempt the trick...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        
        bool responderSuccess = attemptTrick(selectedTrick);
        if (!responderSuccess) {
            std::cout << currentResponder->name << " failed to land the " << selectedTrick.name << "!" << std::endl;
            currentResponder->addLetter();
            std::cout << currentResponder->name << " gets a letter!" << std::endl;
        } else {
            std::cout << currentResponder->name << " successfully landed the " << selectedTrick.name << "!" << std::endl;
        }
    }

    void displayGameStatus() {
        std::cout << "\n--- Current Game Status ---" << std::endl;
        player1.displayStatus();
        player2.displayStatus();
        std::cout << "----------------------------\n" << std::endl;
    }

    bool isGameOver() {
        return player1.hasLost() || player2.hasLost();
    }

    void announceWinner() {
        std::cout << "\n==========================" << std::endl;
        if (player1.hasLost()) {
            std::cout << player2.name << " WINS THE GAME!" << std::endl;
        } else {
            std::cout << player1.name << " WINS THE GAME!" << std::endl;
        }
        std::cout << "==========================" << std::endl;
    }

    void playGame() {
        std::cout << "\nWelcome to SKATE!" << std::endl;
        std::cout << "Players take turns setting tricks. If you fail to match your opponent's trick, you get a letter." << std::endl;
        std::cout << "First to spell 'SKATE' loses!\n" << std::endl;
        
        while (!isGameOver()) {
            displayGameStatus();
            playRound();
            
            // Check if we need to clear the input buffer
            if (std::cin.peek() != '\n') {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        
        displayGameStatus();
        announceWinner();
    }
};

int main() {
    std::string name1, name2;
    
    std::cout << "Enter name for Player 1: ";
    std::getline(std::cin, name1);
    
    std::cout << "Enter name for Player 2: ";
    std::getline(std::cin, name2);
    
    Game skateGame(name1, name2);
    skateGame.playGame();
    
    return 0;
}