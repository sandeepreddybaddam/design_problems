# include <iostream>

using namespace std;



char getComputerMove() {
    srand(time(NULL));
    int num = rand()%3;
    char a[] = {'r', 'p', 's'};
    return a[num];
}

int checkIfHumanWon(char human, char computer) {

    if (human==computer) return 0;

    else if ( (human=='r' && computer=='s') ||
              (human=='p' && computer=='r') ||
              (human=='s' && computer=='p') ) {
        return 1;
    }
    return -1;
}

int main() {
    char humanMove;
    cout << "Enter your move: " << endl;
    cin >> humanMove;

    if (humanMove != 'r' && humanMove != 'p' && humanMove != 's') {
        cout << "\nInvalid move\n";
    }

    char computerMove;
    computerMove = getComputerMove();

    bool human = checkIfHumanWon(humanMove, computerMove);
    if (human==1) cout << "Human won\n";
    else if (human==0) cout << "Game draw\n";
    else cout << "Computer won\n";
    return 0;
}