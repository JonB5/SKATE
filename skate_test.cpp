#include <iostream>
#include <cassert>
#include <sstream>
#include <string>


class TestTrick {
public:
    std::string name;
    int difficulty;

    TestTrick(std::string n, int d) : name(n), difficulty(d) {}
};


class TestPlayer {
public:
    std::string name;
    std::string letters;

    TestPlayer(std::string n) : name(n), letters("") {}

    void addLetter() {
        std::string skate = "SKATE";
        if (letters.length() < 5) {
            letters += skate[letters.length()];
        }
    }

    bool hasLost() {
        return letters == "SKATE";
    }
};

// Test functions
void testPlayerInitialization() {
    TestPlayer player("TestPlayer");
    assert(player.name == "TestPlayer");
    assert(player.letters == "");
    std::cout << "✅ Player initialization test passed" << std::endl;
}

void testAddLetter() {
    TestPlayer player("TestPlayer");
    player.addLetter();
    assert(player.letters == "S");
    player.addLetter();
    assert(player.letters == "SK");
    player.addLetter();
    assert(player.letters == "SKA");
    player.addLetter();
    assert(player.letters == "SKAT");
    player.addLetter();
    assert(player.letters == "SKATE");
    // Extra call should not add more letters
    player.addLetter();
    assert(player.letters == "SKATE");
    std::cout << "✅ Add letter test passed" << std::endl;
}

void testHasLost() {
    TestPlayer player("TestPlayer");
    assert(!player.hasLost());
    player.letters = "SKAT";
    assert(!player.hasLost());
    player.letters = "SKATE";
    assert(player.hasLost());
    std::cout << "✅ Has lost test passed" << std::endl;
}

// Mock random number generator for testing
class MockRandom {
private:
    int nextValue;
public:
    MockRandom(int value) : nextValue(value) {}
    
    void setValue(int value) {
        nextValue = value;
    }
    
    int getValue() {
        return nextValue;
    }
};

// Test trick success calculation
void testTrickSuccess() {
    TestTrick easyTrick("Ollie", 1);
    TestTrick mediumTrick("Kickflip", 5);
    TestTrick hardTrick("Impossible Late Flip", 9);
    
    // Mock our random number generator
    MockRandom mockRng(50);
    
    // For easy trick (difficulty 1), success chance is 95 - (1 * 8) = 87%
    // Should succeed with roll of 50
    int successChance = 95 - (easyTrick.difficulty * 8);
    bool success = mockRng.getValue() <= successChance;
    assert(success == true);
    
    // For medium trick (difficulty 5), success chance is 95 - (5 * 8) = 55%
    // Should succeed with roll of 50
    successChance = 95 - (mediumTrick.difficulty * 8);
    success = mockRng.getValue() <= successChance;
    assert(success == true);
    
    // For hard trick (difficulty 9), success chance is 95 - (9 * 8) = 23%
    // Should fail with roll of 50
    successChance = 95 - (hardTrick.difficulty * 8);
    success = mockRng.getValue() <= successChance;
    assert(success == false);
    
    // Test boundary cases
    mockRng.setValue(23);
    successChance = 95 - (hardTrick.difficulty * 8);
    success = mockRng.getValue() <= successChance;
    assert(success == true);  // Exactly at the threshold
    
    mockRng.setValue(24);
    success = mockRng.getValue() <= successChance;
    assert(success == false); // Just above threshold
    
    std::cout << "✅ Trick success calculation test passed" << std::endl;
}

// Integration test that simulates a simple game
void testGameFlow() {
    TestPlayer player1("Player1");
    TestPlayer player2("Player2");
    
    // Simulate a few rounds
    
    // Round 1: Player1 sets a trick and lands it
    // Player2 attempts and fails
    player2.addLetter(); // Player2 gets an "S"
    assert(player1.letters == "");
    assert(player2.letters == "S");
    
    // Round 2: Player1 sets another trick and lands it
    // Player2 attempts and fails again
    player2.addLetter(); // Player2 gets a "K"
    assert(player1.letters == "");
    assert(player2.letters == "SK");
    
    // Round 3: Player1 sets a trick but fails
    // Roles switch, now Player2 sets a trick
    
    // Round 4: Player2 sets a trick and lands it
    // Player1 attempts and fails
    player1.addLetter(); // Player1 gets an "S"
    assert(player1.letters == "S");
    assert(player2.letters == "SK");
    
    // Continue until someone loses
    player1.addLetter(); // "SK"
    player1.addLetter(); // "SKA"
    player1.addLetter(); // "SKAT"
    player1.addLetter(); // "SKATE" - Player1 has lost
    
    assert(player1.hasLost() == true);
    assert(player2.hasLost() == false);
    
    std::cout << "✅ Game flow test passed" << std::endl;
}

// Test boundary conditions and edge cases
void testEdgeCases() {
    // Test player with very long name
    std::string longName(100, 'A');
    TestPlayer longNamePlayer(longName);
    assert(longNamePlayer.name == longName);
    
    // Test trick with extreme difficulty
    TestTrick extremeTrick("Impossible Trick", 100);
    
    // Test calculation with extreme difficulty
    int successChance = 95 - (extremeTrick.difficulty * 8);
    assert(successChance < 0); // Should be negative
    
    // In the real implementation, we would need to clamp this to 0 or 1
    successChance = std::max(1, successChance);
    assert(successChance == 1); // Minimum 1% chance
    
    std::cout << "✅ Edge cases test passed" << std::endl;
}

int main() {
    std::cout << "Running SKATE game tests...\n" << std::endl;
    
    // Run all tests
    testPlayerInitialization();
    testAddLetter();
    testHasLost();
    testTrickSuccess();
    testGameFlow();
    testEdgeCases();
    
    std::cout << "\nAll tests passed successfully!" << std::endl;
    return 0;
}