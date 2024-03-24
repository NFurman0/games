/*
Play chopsticks against computers of varying difficulty. The impossible difficulty uses an algorithm that should always win.
*/
#include <iostream>
using namespace std;

int currentBoard[2][2] = {{1, 1}, {1, 1}}; //Computer is the first array, player is the second
bool gameIsOver = false;
bool playerWon = false;
//Gets the input from the user, makes sure it is valid, and updates the board.
void userTurn();
//Sets numbers over 5 to 0.
void checkBoard();
//Has the computer select a random move from those available to it, used on easy and medium difficulty.
void randomChoice();
//Prints the board.
void printBoard();
//Has the computer select the optimal move, used on medium and impossible difficulty.
void optimalStrategy();
//Medium Difficulty: Randomly chooses to use a random move or the optimal move.
void mediumDifficulty();
//Splits the computer's hands.
void computerSplit();
//Gets a valid integer input from the user between 1 and the range given.
int getValidInput(int range);

int main() {
  srand(time(0));
  cout << "What difficulty would you like to play?\n1. Easy\n2. Medium\n3. Impossible\n"; 
  //Easy: always random moves
  //Medium: 50% random moves 50% optimal moves.
  //Impossible: always optimal moves.
  int difficulty = getValidInput(3);
  printBoard();
  while(!gameIsOver) { //Game loop
    userTurn();
    checkBoard();
    if(gameIsOver) break;
    system("clear"); //Clears the console so it doesn't get cluttered.
    cout << "\nAfter your move:\n";
    printBoard();
    if(difficulty == 1) randomChoice();
    else if(difficulty == 2) mediumDifficulty();
    else optimalStrategy();
    checkBoard();
    if(gameIsOver) break;
    cout << "\nAfter computer move:\n";
    printBoard();
    cout << endl;
  }
  cout << "\nGame Over\n";
  printBoard();
  if(playerWon) cout << "You Win!";
  else cout << "Computer Wins";
}

void printBoard() {
  cout << "Computer: " << currentBoard[0][0] << "   " << currentBoard[0][1] << endl;
  cout << "You:      " << currentBoard[1][0] << "   " << currentBoard[1][1] << endl;
}

void userTurn() {
  int handChoice;
  cout << "Would you like to:\n1. Use first hand\n2. Use second hand\n3. Split hands\n";
  handChoice = getValidInput(3);
  if(handChoice != 3) {
    while(currentBoard[1][handChoice-1] == 0) {
      cout << "You cannot use that hand.\n";
      handChoice = getValidInput(3);
      if(handChoice == 3) break;
    } //Checks that the user does not attack with a hand with 0
  } else {
    while(currentBoard[1][0] + currentBoard[1][1] == 1 || currentBoard[1][0] + currentBoard[1][1] >= 7) {
      cout << "You cannot split hands.\n";
      handChoice = getValidInput(3);
    }//Checks that the user only selects split when they are able to do so.
  }
  if(handChoice == 1 || handChoice == 2) {
    handChoice--;
    int targetChoice;
    cout << "Would you like to:\n1. Target computer's first hand\n2. Target computer's second hand\n";
    targetChoice = getValidInput(2);
    while(currentBoard[0][targetChoice-1] == 0) {
      cout << "You cannot target that hand\n";
      targetChoice = getValidInput(2);
    } //Checks that the user does not target a hand with 0.
    targetChoice--;
    currentBoard[0][targetChoice] += currentBoard[1][handChoice];
  }
  else { //Makes sure the user splits properly.
    int newLeft;
    int range = min(4, currentBoard[1][0] + currentBoard[1][1]);
    cout << "What would you like your left hand to become?\n";
    newLeft = getValidInput(range);
    while(newLeft == currentBoard[1][0] || newLeft == currentBoard[1][1]) {
      cout << "Hands must change value.\n";
      newLeft = getValidInput(range);
    }
    int newRight = (currentBoard[1][0] + currentBoard[1][1]) - newLeft;
    currentBoard[1][0] = newLeft;
    currentBoard[1][1] = newRight;
  }
}

void checkBoard() {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      if(currentBoard[i][j] >= 5) currentBoard[i][j] = 0;
    }
  }
  if(currentBoard[0][0] == 0 && currentBoard[0][1] == 0) {
    gameIsOver = true;
    playerWon = true;
  }
  if(currentBoard[1][0] == 0 && currentBoard[1][1] == 0) {
    gameIsOver = true;
    playerWon = false;
  }
}

void randomChoice() {
  int firstChoice = 2; //random()%3; //Random choice to attack with either hand or to split.
  if(currentBoard[0][0] + currentBoard[0][1] == 1 || currentBoard[0][0]+currentBoard[0][1] >= 7) firstChoice = random()%2; //Cannot split sometimes
  if(firstChoice == 0 || firstChoice == 1) {
    if(currentBoard[0][0] == 0) firstChoice = 1;
    if(currentBoard[0][1] == 0) firstChoice = 0;
    int secondChoice = random()%2;
    if(currentBoard[1][0] == 0) secondChoice = 1;
    if(currentBoard[1][1] == 0) secondChoice = 0;
    currentBoard[1][secondChoice] += currentBoard[0][firstChoice]; //Attacks
  } else {
    int range = currentBoard[0][0] + currentBoard[0][1];
    range = min(range, 3);
    int secondChoice = (random()%range)+1;
    while(secondChoice == currentBoard[0][0] || secondChoice == currentBoard[0][1]) {
      secondChoice = (random()%range)+1;
    } //Split needs to change value of hands
    currentBoard[0][1] = (currentBoard[0][0] + currentBoard[0][1]) - secondChoice;
    currentBoard[0][0] = secondChoice; //Splits
  }
}

void optimalStrategy() {
  int c1 = currentBoard[0][0];
  int c2 = currentBoard[0][1];
  int p1 = currentBoard[1][0];
  int p2 = currentBoard[1][1];
  int cHighest = max(c1, c2);
  
  if((p1 == 0 && p2 == 1) || (p2 == 0 && p1 == 1)) {
    if((c1 == 0 && c2 == 2) || (c2 == 0 && c1 == 2)) {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 1;
    } else if((c1 == 0 && c2 == 3) || (c2 == 0 && c1 == 3)) {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 2;
    } else if(c1 == 4 || c2 == 4) {
      if(p1 == 0) currentBoard[1][1] += 4;
      else currentBoard[1][0] += 4;
    } else if((c1 == 1 && c2 == 1)) {
      currentBoard[0][0] = 0;
      currentBoard[0][1] = 2;
    } else if((c1 == 1 && c2 == 2) || (c2 == 1 && c1 == 2)) {
      currentBoard[0][0] = 0;
      currentBoard[0][1] = 3;
    } else if(c1 == 2 && c2 == 2) {
      currentBoard[0][0] = 3;
      currentBoard[0][1] = 1;
    } else if((c1 == 2 && c2 == 3) || (c2 == 2 && c1 == 3)) {
      if(p1 == 0) currentBoard[1][1] += 2;
      else currentBoard[1][0] += 2;
    } else if(c1 == 3 && c2 == 3) {
      currentBoard[0][0] = 4;
      currentBoard[0][1] = 2;
    } else {
      if(p1 == 0) currentBoard[1][1] += 1;
      else currentBoard[1][0] += 1;
    }
  } //Always a win if the user has 10 or 01
  else if((p1 == 0 || p2 == 0) && cHighest + max(p1, p2) >= 5) {
    if(p1 == 0) currentBoard[1][1] += cHighest;
    else currentBoard[1][0] += cHighest;
  } //If the computer can win immediately, do so
  else if(c1 == 0 || c2 == 0) {
    if(cHighest + max(p1, p2) >= 5 && cHighest + min(p1, p2) < 5) {
      if(p1 > p2) currentBoard[1][0] += cHighest;
      else currentBoard[1][1] += cHighest;
    } else computerSplit();
  } //If computer has a hand with 0 it will almost always need to split
  else if((p1 == 1 || p2 == 1) && (max(p1, p2) + cHighest >= 5)) {
    if((c1 == 1 && c2 == 4) || (c1 == 4 && c2 == 1)) {
      currentBoard[0][0] = 3;
      currentBoard[0][1] = 2;
    } else {
      if(p1 > p2) currentBoard[1][0] += cHighest;
      else currentBoard[1][1] += cHighest;
    }
  } //If computer can bring the user to 10 or 01, do so.
  else if((p1 == 3 || p2 == 3) && ((c1 >= 2 && c2 >= 3) || (c2 >= 2 && c1 >= 3))) {
    if(p1 == 3) currentBoard[1][1] += 3;
    else currentBoard[1][0] += 3;
  }  //If we can force them to split and then bring them to 10 or 01.
  else if((c1 == 1 || c2 == 1) && min(p1, p2) + cHighest >= 5) {
    if(cHighest == 1) {
      currentBoard[1][0] += 1;
    } else if(cHighest == 2) {
      if(p1 > p2) currentBoard[1][1] += 2;
      else currentBoard[1][0] += 2;
    } else if(cHighest == 3) {
      currentBoard[0][0] = 2;
      currentBoard[0][1] = 2;
    } else if(cHighest == 4) {
      currentBoard[0][0] = 3;
      currentBoard[0][1] = 2;
    }
  } //If the user can bring the computer to 10 or 01
  else if((p1 == 1 || p2 == 1) && max(p1, p2) + cHighest >= 4 && cHighest >= 3) {
    if(p1 > p2) currentBoard[1][0] += 3;
    else currentBoard[1][1] += 3;
  } //If computer can bring user to 14 and beat them afterwards.
  else if(p1 == 1 && p2 == 1) {
    computerSplit();
  } //If the user has 11 its usually best to keep them that way.
  else if(c1 == 1 && c2 == 1) {
    if((p1 == 1 && p2 <= 2) || (p2 == 1 && p1 <= 2)) {
      currentBoard[0][0] = 2;
      currentBoard[0][1] = 0;
    } else {
      if(p1 == 0) currentBoard[1][1]++;
      else if(p2 == 0) currentBoard[1][0]++;
      else if(p1 < p2) currentBoard[1][0]++;
      else currentBoard[1][1]++;
    }
  } //If the computer has 11
  else {
    randomChoice(); //This should never happen, but just in case.
  }
}

int getValidInput(int range) {
  string inputToCheck;
  int validInput = -1;
  while(validInput <= 0 || validInput > range) {
    getline(cin, inputToCheck);
    try {
      validInput = stoi(inputToCheck);
      if(validInput <= 0 || validInput > range) cout << "Please enter a valid input.\n";
    } catch(exception) {
      cout << "Please enter a valid input.\n";
    }
  }
  return validInput;
}

void computerSplit() {
  int c1 = currentBoard[0][0];
  int c2 = currentBoard[0][1];
  int p1 = currentBoard[1][0];
  int p2 = currentBoard[1][1];
  if(c1 + c2 == 1) {
    if(p1 < p2) currentBoard[1][0] += 1;
    else currentBoard[1][1] += 1;
  } else if(c1 + c2 == 4) { 
    if(max(p1, p2) + 3 >= 5) {
      currentBoard[0][0] = 2;
      currentBoard[0][1] = 2;
    } else {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 3;
    }
  } else if(c1 + c2 == 2) {
    if(c1 == 1) {
      currentBoard[0][0] = 0;
      currentBoard[0][1] = 2;
    } else {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 1;
    }
  } else if(c1 + c2 == 3) {
    if(c1 == 1 || c2 == 1) {
      currentBoard[0][0] = 0;
      currentBoard[0][1] = 3;
    } else {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 2;
    }
  } else if(c1 + c2 == 5) {
    if(c1 == 1 || c2 == 1) {
      currentBoard[0][0] = 3;
      currentBoard[0][1] = 2;
    } else {
      currentBoard[0][0] = 1;
      currentBoard[0][1] = 4;
    }
  } else{
    if(c1 == 3)  {
      currentBoard[0][0] = 4;
      currentBoard[0][1] = 2;
    } else {
      currentBoard[0][0] = 3;
      currentBoard[0][1] = 3;
    }
  }
}

void mediumDifficulty() {
  int randnum = random()%2;
  if(randnum == 0) optimalStrategy();
  else randomChoice();
}
