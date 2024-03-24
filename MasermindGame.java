import java.util.Scanner;

class MastermindGame {
  String[] code = generate(); //The code to be guessed
  String[] guess01 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess02 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess03 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess04 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess05 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess06 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess07 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess08 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess09 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "};
  String[] guess10 = {"\033[37m-", "-", "-", "-", " ", " ", " ", " "}; //A series of arrays to track the guesses and responses. The first 4 strings store the users guesses or dashes if the user has not input that guess yet. The next 4 store the responses. The first hypen has the code to print white to the console to reset color at the start of the line.
  int guess_counter = 0;
  boolean game_is_won = false;

  Scanner r = new Scanner(System.in);

  //Generates the secret code
  String[] generate() {
    String[] combination = {"Q", "Q", "Q", "Q"}; //Placeholder values
    String[] colors = {"\033[31mR", "\033[38;5;202mO", "\033[93mY", "\033[92mG", "\033[94mB", "\033[38;5;57mI" , "\033[95mV"};
    boolean flag = true;
    int rand = 0;

    for(int i = 0; i < 4; i++) {
      while(flag) {
        flag = false;
        rand = (int) (Math.random()*7);
        for(int j = 0; j < 4; j++) {
          if(colors[rand].equals(combination[j])) {
            flag = true;
          }
        }
      }
      flag = true;
      combination[i] = colors[rand];
    } //This sets each place to a color ensuring no duplicates are in the final combination.

    return combination;
  }

  //Prints the current board
  void print_board() {
    System.out.print("\033[H\033[2J");
    System.out.flush(); //Empties the console
    System.out.println("A white peg signifies a correct color in a wrong position.\nA black peg signifies a correct color in the correct position.\nNo double colors are allowed.\n\n" + guess01[0] + " " + guess01[1] + " " + guess01[2] + " " + guess01[3] + "\t\t" + guess01[4] + " " + guess01[5] + " " + guess01[6] + " " + guess01[7]);
    System.out.println(guess02[0] + " " + guess02[1] + " " + guess02[2] + " " + guess02[3] + "\t\t" + guess02[4] + " " + guess02[5] + " " + guess02[6] + " " + guess02[7]);
    System.out.println(guess03[0] + " " + guess03[1] + " " + guess03[2] + " " + guess03[3] + "\t\t" + guess03[4] + " " + guess03[5] + " " + guess03[6] + " " + guess03[7]);
    System.out.println(guess04[0] + " " + guess04[1] + " " + guess04[2] + " " + guess04[3] + "\t\t" + guess04[4] + " " + guess04[5] + " " + guess04[6] + " " + guess04[7]);
    System.out.println(guess05[0] + " " + guess05[1] + " " + guess05[2] + " " + guess05[3] + "\t\t" + guess05[4] + " " + guess05[5] + " " + guess05[6] + " " + guess05[7]);
    System.out.println(guess06[0] + " " + guess06[1] + " " + guess06[2] + " " + guess06[3] + "\t\t" + guess06[4] + " " + guess06[5] + " " + guess06[6] + " " + guess06[7]);
    System.out.println(guess07[0] + " " + guess07[1] + " " + guess07[2] + " " + guess07[3] + "\t\t" + guess07[4] + " " + guess07[5] + " " + guess07[6] + " " + guess07[7]);
    System.out.println(guess08[0] + " " + guess08[1] + " " + guess08[2] + " " + guess08[3] + "\t\t" + guess08[4] + " " + guess08[5] + " " + guess08[6] + " " + guess08[7]);
    System.out.println(guess09[0] + " " + guess09[1] + " " + guess09[2] + " " + guess09[3] + "\t\t" + guess09[4] + " " + guess09[5] + " " + guess09[6] + " " + guess09[7]);
    System.out.println(guess10[0] + " " + guess10[1] + " " + guess10[2] + " " + guess10[3] + "\t\t" + guess10[4] + " " + guess10[5] + " " + guess10[6] + " " + guess10[7]); //Prints every guess array
  }

  //Gets the full guess from the user
  String[] user_guess() {
    String[] guess = {"Q", "Q", "Q", "Q"}; //Placeholder values
    boolean flag = true;
    String resp = " ";
    boolean check = true; //Check determines which message to print to ask the user for the peg color.
    for(int i = 0; i<4; i++) {
      check = true;
      while(flag) {
        if(check) {
          System.out.println("Enter the peg color (R, O, Y, G, B, I, V)");
        } else System.out.println("Not a valid input, try again (R, O, Y, G, B, I, V)");
        
        flag = false;
        resp = r.nextLine();
        resp = capitalize(resp);
        if(!("R".equals(resp)) && !("O".equals(resp)) && !("Y".equals(resp)) && !("G".equals(resp)) && !("B".equals(resp)) && !("I".equals(resp)) && !("V".equals(resp))) {
          flag = true;
          check = false;
        } //Checks that an input is valid
        if(guess[0].equals(resp)) {
          flag = true;
          check = false;
        }
        if(guess[1].equals(resp)) {
          flag = true;
          check = false;
        }
        if(guess[2].equals(resp)) {
          flag = true;
          check = false;
        }
        if(guess[3].equals(resp)) {
          flag = true;
          check = false;
        } //These check that the input is not a duplicate answer.
      }
      flag = true;

      guess[i] = resp;
    }

    for(int i = 0; i < 4; i++) {
      if(guess[i].equals("R")) guess[i] = "\033[31mR";
      if(guess[i].equals("O")) guess[i] = "\033[38;5;202mO";
      if(guess[i].equals("Y")) guess[i] = "\033[93mY";
      if(guess[i].equals("G")) guess[i] = "\033[92mG";
      if(guess[i].equals("B")) guess[i] = "\033[94mB";
      if(guess[i].equals("I")) guess[i] = "\033[38;5;57mI";
      if(guess[i].equals("V")) guess[i] = "\033[95mV";
    } //Updates the board with the user's guess

    guess_counter++;
    switch(guess_counter) {
      case 1: guess01[0] = guess[0];
              guess01[1] = guess[1];
              guess01[2] = guess[2];
              guess01[3] = guess[3];
              break;
      case 2: guess02[0] = guess[0];
              guess02[1] = guess[1];
              guess02[2] = guess[2];
              guess02[3] = guess[3];
              break;
      case 3: guess03[0] = guess[0];
              guess03[1] = guess[1];
              guess03[2] = guess[2];
              guess03[3] = guess[3];
              break;
      case 4: guess04[0] = guess[0];
              guess04[1] = guess[1];
              guess04[2] = guess[2];
              guess04[3] = guess[3];
              break;
      case 5: guess05[0] = guess[0];
              guess05[1] = guess[1];
              guess05[2] = guess[2];
              guess05[3] = guess[3];
              break;
      case 6: guess06[0] = guess[0];
              guess06[1] = guess[1];
              guess06[2] = guess[2];
              guess06[3] = guess[3];
              break;
      case 7: guess07[0] = guess[0];
              guess07[1] = guess[1];
              guess07[2] = guess[2];
              guess07[3] = guess[3];
              break;
      case 8: guess08[0] = guess[0];
              guess08[1] = guess[1];
              guess08[2] = guess[2];
              guess08[3] = guess[3];
              break;
      case 9: guess09[0] = guess[0];
              guess09[1] = guess[1];
              guess09[2] = guess[2];
              guess09[3] = guess[3];
              break;
      case 10: guess10[0] = guess[0];
              guess10[1] = guess[1];
              guess10[2] = guess[2];
              guess10[3] = guess[3];
              break;
    } //Updates the apropriate guess array.
    return guess;
  }

  //Capitalizes a string
  String capitalize(String r) {
    String cap = r.toUpperCase();
    return cap;
  }

  void check_guess(String[] guess) { //Gets the result pegs for the guess.
    String[] result = {" ", " ", " ", " "}; //Placeholder values
    int counter = 0;

    for(int i = 0; i < 4; i++) {
      if(guess[0].equals(code[i])) {
        if(i == 0) {
          result[counter] = "\033[38;5;247mB";
          counter++;
        } else {
          result[counter] = "\033[37mW";
          counter++;
        }
      }
    }

    for(int i = 0; i < 4; i++) {
      if(guess[1].equals(code[i])) {
        if(i == 1) {
          result[counter] = "\033[38;5;247mB";
          counter++;
        } else {
          result[counter] = "\033[37mW";
          counter++;
        }
      }
    }

    for(int i = 0; i < 4; i++) {
      if(guess[2].equals(code[i])) {
        if(i == 2) {
          result[counter] = "\033[38;5;247mB";
          counter++;
        } else {
          result[counter] = "\033[37mW";
          counter++;
        }
      }
    }

    for(int i = 0; i < 4; i++) {
      if(guess[3].equals(code[i])) {
        if(i == 3) {
          result[counter] = "\033[38;5;247mB";
          counter++;
        } else {
          result[counter] = "\033[37mW";
          counter++;
        }
      }
    } //Check each guess to see if it should have a Black peg, White peg, or no peg added.

    for(int i = 0; i < counter; i++) {
      int randresult = (int) (Math.random()*(i+1));
      
      String swap = result[i];
      result[i] = result[randresult];
      result[randresult] = swap;
    } //This randomizes the order of the resulting pegs.

    switch(guess_counter) {
      case 1: guess01[4] = result[0];
              guess01[5] = result[1];
              guess01[6] = result[2];
              guess01[7] = result[3];
              break;
      case 2: guess02[4] = result[0];
              guess02[5] = result[1];
              guess02[6] = result[2];
              guess02[7] = result[3];
              break;
      case 3: guess03[4] = result[0];
              guess03[5] = result[1];
              guess03[6] = result[2];
              guess03[7] = result[3];
              break;
      case 4: guess04[4] = result[0];
              guess04[5] = result[1];
              guess04[6] = result[2];
              guess04[7] = result[3];
              break;
      case 5: guess05[4] = result[0];
              guess05[5] = result[1];
              guess05[6] = result[2];
              guess05[7] = result[3];
              break;
      case 6: guess06[4] = result[0];
              guess06[5] = result[1];
              guess06[6] = result[2];
              guess06[7] = result[3];
              break;
      case 7: guess07[4] = result[0];
              guess07[5] = result[1];
              guess07[6] = result[2];
              guess07[7] = result[3];
              break;
      case 8: guess08[4] = result[0];
              guess08[5] = result[1];
              guess08[6] = result[2];
              guess08[7] = result[3];
              break;
      case 9: guess09[4] = result[0];
              guess09[5] = result[1];
              guess09[6] = result[2];
              guess09[7] = result[3];
              break;
      case 10: guess10[4] = result[0];
              guess10[5] = result[1];
              guess10[6] = result[2];
              guess10[7] = result[3];
              break;
    } //Adds the results to the apropriate guess array.

    if(result[0].equals("\033[38;5;247mB") && result[1].equals("\033[38;5;247mB") && result[2].equals("\033[38;5;247mB") && result[3].equals("\033[38;5;247mB")) {
      game_is_won = true;
    } //Checks if all pegs are black, in which case the game is won.
  }

  //Runs the game
  void run_game() {
    while(!(game_is_won) && guess_counter < 10) {
      print_board();
      String[] input = user_guess();
      check_guess(input);
    }
    if(game_is_won) {
      print_board();
      System.out.println("\033[37mCongratulations! You Win!");
    }
    else {
      print_board();
      System.out.println("\033[37mYou ran out of chances. The code was: " + code[0] + " " + code[1] + " " + code[2] + " " + code[3]); //Prints the code if the user could not guess it.
    }
  }
}
