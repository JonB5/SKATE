// Game of Skate GUI - Standalone Version
// This is a self-contained file that implements the GUI version of the Game of Skate
// Updated for Qt6 compatibility

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QGroupBox>
#include <QFont>
#include <QTimer>
#include <random>
#include <ctime>
#include <string>
#include <vector>

// Trick class
class Trick {
public:
    std::string name;
    int difficulty; // 1-10 scale

    Trick(std::string n, int d) : name(n), difficulty(d) {}
};

// Player class
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
    
    std::string getStatus() {
        if (letters.empty()) {
            return "No letters";
        } else {
            return letters + " (" + std::to_string(letters.length()) + "/5)";
        }
    }
};

// Main window class
class SkateGameWindow : public QMainWindow {
    Q_OBJECT

private:
    // Game state
    std::vector<Trick> tricks;
    Player *player1;
    Player *player2;
    Player *currentSetter;
    Player *currentResponder;
    std::mt19937 rng;
    bool gameInProgress;
    
    // UI elements
    QLineEdit *player1NameEdit;
    QLineEdit *player2NameEdit;
    QPushButton *startGameButton;
    QComboBox *trickSelector;
    QPushButton *attemptTrickButton;
    QPushButton *matchTrickButton;
    QLabel *player1StatusLabel;
    QLabel *player2StatusLabel;
    QLabel *gameStatusLabel;
    QLabel *currentTrickLabel;
    QGroupBox *setupGroup;
    QGroupBox *gameplayGroup;
    QGroupBox *player1Box;
    QGroupBox *player2Box;

public:
    SkateGameWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Initialize window properties
        setWindowTitle("Game of SKATE");
        setMinimumSize(600, 500);
        
        // Initialize game state
        player1 = nullptr;
        player2 = nullptr;
        currentSetter = nullptr;
        currentResponder = nullptr;
        gameInProgress = false;
        
        // Seed random number generator
        rng.seed(static_cast<unsigned int>(time(nullptr)));
        
        // Initialize trick library
        initializeTricks();
        
        // Setup UI
        setupUI();
    }

    ~SkateGameWindow() {
        delete player1;
        delete player2;
    }

    void initializeTricks() {
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

    void setupUI() {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // Title
        QLabel *titleLabel = new QLabel("Game of SKATE", this);
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(20);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);
        
        // Setup group (player names)
        setupGroup = new QGroupBox("Game Setup", this);
        QGridLayout *setupLayout = new QGridLayout(setupGroup);
        
        QLabel *player1Label = new QLabel("Player 1 Name:", this);
        player1NameEdit = new QLineEdit(this);
        player1NameEdit->setPlaceholderText("Enter name");
        
        QLabel *player2Label = new QLabel("Player 2 Name:", this);
        player2NameEdit = new QLineEdit(this);
        player2NameEdit->setPlaceholderText("Enter name");
        
        startGameButton = new QPushButton("Start Game", this);
        
        setupLayout->addWidget(player1Label, 0, 0);
        setupLayout->addWidget(player1NameEdit, 0, 1);
        setupLayout->addWidget(player2Label, 1, 0);
        setupLayout->addWidget(player2NameEdit, 1, 1);
        setupLayout->addWidget(startGameButton, 2, 0, 1, 2);
        
        mainLayout->addWidget(setupGroup);
        
        // Gameplay group
        gameplayGroup = new QGroupBox("Gameplay", this);
        gameplayGroup->setVisible(false);
        QVBoxLayout *gameplayLayout = new QVBoxLayout(gameplayGroup);
        
        // Player status
        QHBoxLayout *statusLayout = new QHBoxLayout();
        player1Box = new QGroupBox("Player 1", this);
        QVBoxLayout *player1Layout = new QVBoxLayout(player1Box);
        player1StatusLabel = new QLabel("No letters", this);
        player1Layout->addWidget(player1StatusLabel);
        
        player2Box = new QGroupBox("Player 2", this);
        QVBoxLayout *player2Layout = new QVBoxLayout(player2Box);
        player2StatusLabel = new QLabel("No letters", this);
        player2Layout->addWidget(player2StatusLabel);
        
        statusLayout->addWidget(player1Box);
        statusLayout->addWidget(player2Box);
        gameplayLayout->addLayout(statusLayout);
        
        // Game status
        gameStatusLabel = new QLabel("Game status will be shown here", this);
        gameStatusLabel->setAlignment(Qt::AlignCenter);
        QFont statusFont = gameStatusLabel->font();
        statusFont.setBold(true);
        gameStatusLabel->setFont(statusFont);
        gameplayLayout->addWidget(gameStatusLabel);
        
        // Current trick
        currentTrickLabel = new QLabel("Current trick: None", this);
        currentTrickLabel->setAlignment(Qt::AlignCenter);
        gameplayLayout->addWidget(currentTrickLabel);
        
        // Trick selection
        QHBoxLayout *trickLayout = new QHBoxLayout();
        QLabel *selectTrickLabel = new QLabel("Select Trick:", this);
        trickSelector = new QComboBox(this);
        
        // Populate the trick selector
        for (const auto& trick : tricks) {
            trickSelector->addItem(QString::fromStdString(trick.name + " (Difficulty: " + 
                                   std::to_string(trick.difficulty) + ")"));
        }
        
        trickLayout->addWidget(selectTrickLabel);
        trickLayout->addWidget(trickSelector);
        gameplayLayout->addLayout(trickLayout);
        
        // Action buttons
        QHBoxLayout *actionLayout = new QHBoxLayout();
        attemptTrickButton = new QPushButton("Attempt Trick", this);
        matchTrickButton = new QPushButton("Match Trick", this);
        matchTrickButton->setEnabled(false);
        
        actionLayout->addWidget(attemptTrickButton);
        actionLayout->addWidget(matchTrickButton);
        gameplayLayout->addLayout(actionLayout);
        
        mainLayout->addWidget(gameplayGroup);
        
        // Connect signals to slots
        connect(startGameButton, &QPushButton::clicked, this, &SkateGameWindow::startGame);
        connect(attemptTrickButton, &QPushButton::clicked, this, &SkateGameWindow::attemptSetterTrick);
        connect(matchTrickButton, &QPushButton::clicked, this, &SkateGameWindow::attemptResponderTrick);
    }

private slots:
    void startGame() {
        // Get player names
        std::string name1 = player1NameEdit->text().toStdString();
        std::string name2 = player2NameEdit->text().toStdString();
        
        // Validate names
        if (name1.empty() || name2.empty()) {
            QMessageBox::warning(this, "Invalid Names", "Please enter names for both players.");
            return;
        }
        
        // Clean up previous game if any
        delete player1;
        delete player2;
        
        // Initialize new game
        player1 = new Player(name1);
        player2 = new Player(name2);
        currentSetter = player1;
        currentResponder = player2;
        gameInProgress = true;
        
        // Update UI
        setupGroup->setVisible(false);
        gameplayGroup->setVisible(true);
        
        // Update player box titles
        player1Box->setTitle(QString::fromStdString(player1->name));
        player2Box->setTitle(QString::fromStdString(player2->name));
        
        // Update player status
        updatePlayerStatus();
        
        // Update game status
        QString message = QString("Game started! %1 sets the first trick.").arg(
            QString::fromStdString(currentSetter->name));
        gameStatusLabel->setText(message);
        
        // Enable/disable buttons
        attemptTrickButton->setEnabled(true);
        matchTrickButton->setEnabled(false);
    }
    
    void updatePlayerStatus() {
        // Update player 1 status
        player1StatusLabel->setText(QString::fromStdString(player1->getStatus()));
        
        // Update player 2 status
        player2StatusLabel->setText(QString::fromStdString(player2->getStatus()));
    }
    
    void attemptSetterTrick() {
        // Get selected trick
        int trickIndex = trickSelector->currentIndex();
        Trick selectedTrick = tricks[trickIndex];
        
        // Update current trick label
        currentTrickLabel->setText(QString("Current trick: %1").arg(
            QString::fromStdString(selectedTrick.name)));
        
        // Attempt the trick
        bool success = attemptTrick(selectedTrick);
        
        // Update game status
        if (success) {
            // Setter landed the trick
            QString message = QString("%1 landed the %2!").arg(
                QString::fromStdString(currentSetter->name),
                QString::fromStdString(selectedTrick.name));
            gameStatusLabel->setText(message);
            
            // Enable responder to match
            attemptTrickButton->setEnabled(false);
            matchTrickButton->setEnabled(true);
        } else {
            // Setter failed the trick
            QString message = QString("%1 failed to land the %2! Switching roles...").arg(
                QString::fromStdString(currentSetter->name),
                QString::fromStdString(selectedTrick.name));
            gameStatusLabel->setText(message);
            
            // Switch roles
            switchRoles();
        }
    }
    
    void attemptResponderTrick() {
        // Get the currently selected trick
        int trickIndex = trickSelector->currentIndex();
        Trick selectedTrick = tricks[trickIndex];
        
        // Attempt the trick
        bool success = attemptTrick(selectedTrick);
        
        // Update game status
        if (success) {
            // Responder landed the trick
            QString message = QString("%1 successfully landed the %2! Switching roles...").arg(
                QString::fromStdString(currentResponder->name),
                QString::fromStdString(selectedTrick.name));
            gameStatusLabel->setText(message);
            
            // Switch roles
            switchRoles();
        } else {
            // Responder failed the trick
            QString message = QString("%1 failed to land the %2!").arg(
                QString::fromStdString(currentResponder->name),
                QString::fromStdString(selectedTrick.name));
            gameStatusLabel->setText(message);
            
            // Add a letter to responder
            currentResponder->addLetter();
            
            // Update player status
            updatePlayerStatus();
            
            // Check if game is over
            if (isGameOver()) {
                gameOver();
            } else {
                // Switch roles
                switchRoles();
            }
        }
    }
    
    bool attemptTrick(const Trick& trick) {
        // Calculate success probability based on trick difficulty
        int successChance = 95 - (trick.difficulty * 8);
        
        // Random number between 1-100
        std::uniform_int_distribution<int> dist(1, 100);
        int roll = dist(rng);
        
        return roll <= successChance;
    }
    
    void switchRoles() {
        // Switch setter and responder
        if (currentSetter == player1) {
            currentSetter = player2;
            currentResponder = player1;
        } else {
            currentSetter = player1;
            currentResponder = player2;
        }
        
        // Update game status
        QString message = QString("%1 is now setting tricks.").arg(
            QString::fromStdString(currentSetter->name));
        gameStatusLabel->setText(message);
        
        // Enable/disable buttons
        attemptTrickButton->setEnabled(true);
        matchTrickButton->setEnabled(false);
    }
    
    bool isGameOver() {
        return player1->hasLost() || player2->hasLost();
    }
    
    void gameOver() {
        // Determine winner
        std::string winnerName;
        if (player1->hasLost()) {
            winnerName = player2->name;
        } else {
            winnerName = player1->name;
        }
        
        // Show game over message
        QString message = QString("%1 WINS THE GAME!").arg(QString::fromStdString(winnerName));
        QMessageBox::information(this, "Game Over", message);
        
        // Disable trick buttons
        attemptTrickButton->setEnabled(false);
        matchTrickButton->setEnabled(false);
        
        // Show option to play again
        QMessageBox playAgainBox;
        playAgainBox.setText("Do you want to play again?");
        QPushButton *yesButton = playAgainBox.addButton("Yes", QMessageBox::AcceptRole);
        playAgainBox.addButton("No", QMessageBox::RejectRole);
        
        playAgainBox.exec();
        
        if (playAgainBox.clickedButton() == yesButton) {
            // Reset to setup screen
            gameplayGroup->setVisible(false);
            setupGroup->setVisible(true);
            gameInProgress = false;
        } else {
            // Exit application
            QApplication::quit();
        }
    }
};

// Main function
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    SkateGameWindow window;
    window.show();
    
    return app.exec();
}

#include "skate_gui_standalone_qt6.moc"