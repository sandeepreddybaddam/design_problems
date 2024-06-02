# include <iostream>

using namespace std;

class tictactoe
{
private:
    /* data */
    static const int size_ = 3;
    // maximum moves in the game
    static const int max_moves_ = 9;
    // minimum moves to check win
    static const int min_moves_ = 5;

    char board_[size_][size_];
    int total_moves_; // counter
    bool game_over_;
    char winner_;

public:
    tictactoe();
    ~tictactoe();
    // displays our board through each iteration
    void displayBoard() const;

    bool isValidMove(int idx);
    void getHumanMove(char player);
    void getComputerMove(char player);

    void playGame();
    
    void checkForWin(char player);
    void checkForDraw(); // fuse this into checkForWin
    bool isFullSum(int count, char player);
    void gameOver(char player);

    void emptyBoard();
    void updateBoard(int idx, char player);
};

// constructor
tictactoe::tictactoe()
{
    total_moves_ = 0;
    game_over_ = false;
    winner_ = ' ';
    emptyBoard();
}

void tictactoe::emptyBoard() {
    for (int i=0; i<size_; i++) {
        for (int j=0; j<size_; j++) {
            board_[i][j] = ' ';
        }
    }
}

void tictactoe::updateBoard(int idx, char player) {
    int row = (int) idx/size_;
    int col = (int) idx%size_;
    board_[row][col] = player;
    total_moves_ ++;
}

// destructor
tictactoe::~tictactoe()
{
}


void tictactoe::displayBoard() const {
    for (int i=0; i<size_; i++) {
        for (int j=0; j<size_; j++) {
            cout << " | " << board_[i][j];
        }
        cout << " | \n -------------\n";
    }
}

bool tictactoe::isValidMove(int idx) {

    if (idx >= size_* size_) {
        cout << "You made invalid move. Retry.\n";
    }
    int row = (int) idx/size_;
    int col = (int) idx%size_;
    if (board_[row][col] == ' ') {
        return true;
    }
    return false;
}

void tictactoe::getHumanMove(char player) {
    int idx;
    cout << "Your turn (enter a digit from 0-8): " << endl;
    cin >> idx;
    if (isValidMove(idx)) {
        updateBoard(idx, player);
    } else {
        getHumanMove(player);
    }
}

void tictactoe::getComputerMove(char player) {
    int idx = rand()%(size_*size_);
    if (isValidMove(idx)) {
        updateBoard(idx, player);
    } else {
        getComputerMove(player);
    }
}

bool tictactoe::isFullSum(int count, char player) {
    if (count == size_) {
        game_over_ = true;
        winner_ = player;
        return true;
    }
    return false;
}

void tictactoe::gameOver(char player) {
    game_over_ = true;
    winner_ = player;
}

void tictactoe::checkForWin(char player) {
    if (total_moves_ < min_moves_) return;
    int count;
    
    // rows
    for (int i=0; i<size_; i++) {
        count = 0;
        for (int j=0; j<size_; j++) {
            if (board_[i][j] == player) count++;
        }
        if (isFullSum(count, player)) return;
    }

    // cols
     for (int i=0; i<size_; i++) {
        count = 0;
        for (int j=0; j<size_; j++) {
            if (board_[j][i] == player) count++;
        }
        if (isFullSum(count, player)) return;
    }

    // left diagonal
    count = 0;
    for (int i=0; i<size_; i++) {
        if (board_[i][i] == player) count++;
    }
    if (isFullSum(count, player)) return;

    // right diagonal
    count = 0;
    for (int i=0; i<size_; i++) {
        if (board_[i][size_-i-1] == player) count++;
    }
    if (isFullSum(count, player)) return;


    // if (board_[0][0]==player && board_[0][1]==player && board_[0][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[1][0]==player && board_[1][1]==player && board_[1][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[2][0]==player && board_[2][1]==player && board_[2][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][0]==player && board_[1][0]==player && board_[2][0]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][1]==player && board_[1][1]==player && board_[2][1]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][2]==player && board_[1][2]==player && board_[2][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][2]==player && board_[1][2]==player && board_[2][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][0]==player && board_[1][1]==player && board_[2][2]==player) {
    //     gameOver(player);
    // }
    // if (board_[0][2]==player && board_[1][1]==player && board_[2][0]==player) {
    //     gameOver(player);
    // }
}

void tictactoe::checkForDraw() {
    if (total_moves_ == max_moves_) {
        game_over_ = true;
    }
}

void tictactoe::playGame() {
    char human_player = 'X';
    char comp_player = 'O';

    while(game_over_ == false) {
        
        displayBoard();

        getHumanMove(human_player);
        checkForWin(human_player);
        checkForDraw();
        
        // different seed each time the program runs
        if (!game_over_) {
            srand(time(NULL));
            getComputerMove(comp_player);
            checkForWin(comp_player);
            checkForDraw();
        }
    }

    if (winner_ != ' ') {
        cout << "Winner is: " << winner_ << "\n";
    } else {
        cout << "Game draw\n";
    }
}

int main() {
    tictactoe game;
    game.playGame();
}