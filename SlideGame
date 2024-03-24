import java.util.Scanner;

class SlideGame {
  Scanner s = new Scanner(System.in);

  int[] board = generate_board();

  public int[] generate_board() {
    int[] board = new int[16];
    boolean f1 = true;
    boolean f2 = false;
    int rand1 = 0;

    for(int i = 0; i < 16; i++) {
      while(f1) {
        rand1 = (int) (Math.random()*16);
        for(int j = 0; j < i; j++) {
          if(rand1 == board[j]) f2 = true;
          else f1 = false;
        }
        f1 = f2;
        f2 = false;
      }
      board[i] = rand1;
      f1 = true;
    }
    return board;
  }

  public void print_board() {
    System.out.println("");

    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        System.out.print("\t\t" + board[(i*4)+j]);
      }
      System.out.print("\n");
    }
  }

  public int[] locate_space() {
    int index = 0;
    for(int i = 0; i < board.length; i++) {
      if(board[i] == 0) index = i;
    }

    int row = index/4+1;
    int column = index%4+1;
    int[] coords = {row, column};

    return coords;
  }

  public int[] locate_moves() {
    int[] space_coords = locate_space();
    int[] possible = {-1, -1, -1, -1, -1, -1, -1, -1};
    int counter = 0;
    int spaceloc = ((space_coords[0]-1)*4)+space_coords[1]-1;

    for(int i = 0; i < board.length; i++) {
      if(spaceloc == 0 || spaceloc == 4 || spaceloc == 8 || spaceloc == 12) {
        if(i == spaceloc+1 || i == spaceloc+4 || i == spaceloc-4) {
        possible[counter] = i/4+1;
        possible[counter+1] = i%4+1;
        counter = counter+2;
        }
      } else if(spaceloc == 3 || spaceloc == 7 || spaceloc == 11 || spaceloc == 15) {
        if(i == spaceloc-1 || i == spaceloc+4 || i == spaceloc-4) {
        possible[counter] = i/4+1;
        possible[counter+1] = i%4+1;
        counter = counter+2;
        }
      } else {
        if(i == spaceloc+1 || i == spaceloc-1 || i == spaceloc+4 || i == spaceloc-4) {
        possible[counter] = i/4+1;
        possible[counter+1] = i%4+1;
        counter = counter+2;
        }
      }
      
    }

    counter = 0;
    for(int i = 0; i < 8; i++) {
      if(possible[i] > -1) counter++;
    }

    int[] coords = new int[counter];
    for(int i = 0; i < coords.length; i++) {
      coords[i] = possible[i];
    }

    return coords;
  }

  public int get_move() {
    int[] possibles = locate_moves();
    
    int num1 = board[(possibles[0]-1)*4+possibles[1]-1];
    int num2 = board[(possibles[2]-1)*4+possibles[3]-1];
    int num3 = 0;
    int num4 = 0;
    if(possibles.length > 4) {
      num3 = board[(possibles[4]-1)*4+possibles[5]-1];
    }
    if(possibles.length > 6) {
      num4 = board[(possibles[6]-1)*4+possibles[7]-1];
    }

    if(possibles.length == 4) {
      System.out.println("Which number would you like to move: " + num1 + ", or " + num2);
    } else if(possibles.length == 6) {
      System.out.println("Which number would you like to move: " + num1 + ", " + num2 + ", or " + num3);
    } else {
      System.out.println("Which number would you like to move: " + num1 + ", " + num2 + ", " + num3 + ", or " + num4);
    }

    int ans = 0;
    String resp;
    while(true) {
      resp = s.nextLine();
      try {
        ans = Integer.parseInt(resp);
      } catch(IllegalArgumentException e) {
        
      }
      if(ans > 0 && (ans == num1 || ans == num2 || ans == num3 || ans == num4)) break;
      else System.out.println("Invalid input, try again.");
    }

    return ans;
  }

  public void move() {
    int move = get_move();
    int moveindex = 0;
    int[] coords = locate_space();
    int spaceindex = ((coords[0]-1)*4+coords[1]-1);

    for(int i = 0; i < 16; i++) {
      if(board[i] == move) moveindex = i;
    }

    System.out.println(move);
    board[spaceindex] = move;
    board[moveindex] = 0;
    
  }

  public void run_game() {
    System.out.println("\nWelcome to Slide Puzzle. Arrange the numbers from 1-15 going left to right, top to bottom. The 0 represents the empty space.");
    while(true) {
      print_board();
      if(win()) {
        break;
      }
      move();
      System.out.println("\033[H\033[2J");
      System.out.flush();

    }
    System.out.println("Congratulations! You Win!");
  }

  public boolean win() {
    if(board[0] == 1 && board[1] == 2 && board[2] == 3 && board[3] == 4 && board[4] == 5 && board[5] == 6 && board[6] == 7 && board[7] == 8 && board[8] == 9 && board[9] == 10 && board[10] == 11 && board[11] == 12 && board[12] == 13 && board[13] == 14 && board[14] == 15 && board[15] == 0) return true;
    else return false;
  }
}
