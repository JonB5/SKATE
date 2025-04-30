# SKATE Game

A C++ implementation of the classic skateboarding letter game where two players compete by performing and matching tricks. The first player to spell out "SKATE" loses!

##  Game Overview

SKATE is a turn-based word game played between two players. Each round:

1. Player 1 sets a trick by choosing from the available options
2. If Player 1 successfully lands the trick, Player 2 must attempt to replicate it
3. If Player 2 fails to land the trick, they receive a letter (S, K, A, T, or E)
4. Players switch roles when the trick-setter fails their own attempt
5. The first player to accumulate all five letters (S-K-A-T-E) loses

##  Features

- Turn-based gameplay with role switching
- 20 unique skateboarding tricks with varying difficulty levels
- Difficulty-based success probability system
- Clear text interface displaying game state and progress
- Input validation and error handling

##  Requirements

- C++ compiler (g++)
- C++11 or later

##  Installation

1. Clone the repository:

2. Compile the game:

3. Run the game:

##  How to Play

1. Enter player names when prompted
2. Player 1 starts as the trick-setter
3. Choose a trick by entering its number (1-20)
4. Success or failure is determined by the trick's difficulty
5. If successful, the other player must match the trick
6. Failed tricks result in role switching or letter assignment
7. Game continues until one player spells "SKATE"

##  Testing

The project includes comprehensive unit tests to verify game functionality:

1. Compile the test file:

2. Run the tests:

The test suite includes:
- Player initialization tests
- Letter assignment verification
- Trick success probability calculations
- Game flow simulation
- Edge case handling

##  Project Structure

```
skate-game/
│
├── skate.cpp                 # Main game implementation
├── skate_test.cpp           # Unit tests
├── README.md                # Project documentation

```

##  Game Mechanics

### Trick Difficulty

Tricks range from difficulty 1-10, affecting success probability:
- **Difficulty 1**: 87% success rate (e.g., Ollie)
- **Difficulty 5**: 55% success rate (e.g., 360 Flip)
- **Difficulty 9**: 23% success rate (e.g., Impossible Late Flip)

### Available Tricks

The game includes 20 authentic skateboarding tricks:
- Basic: Ollie, Nollie, Pop Shove-it
- Intermediate: Kickflip, Heelflip, 180s
- Advanced: 360 Flip, Hardflip, Impossible
- Expert: Double Kickflip, Dolphin Flip

##  Future Enhancements

Potential improvements for the game:
- Graphical user interface (GUI)
- AI opponent for single-player mode
- Custom trick creation system
- Player statistics tracking
- Expanded trick library
- Skater attribute/progression system

##  Contributing

Contributions are welcome! Feel free to submit issues and pull requests for:
- Bug fixes
- New features
- Code optimizations
- Documentation improvements

##  Acknowledgments

- Inspired by the skateboarding game SKATE
- Developed as a C++ programming project for my class (will continue to improve)
- Thanks to the skateboarding community for trick inspiration

##  Authors

[Jonathan Bailey] - Initial work
