/**********|**********|**********|
Program: Othello.cpp
Course: TCP1101 - Programming Fundamentals
Year: 2015/16 Trimester 1
Name: Tiew Kee Hui
ID: 1151303086
Email: huiblabla@hotmail.com
Phone: 012-3625985
**********|**********|**********/

/*
Editor notes:
Throughout this program, i = row, j = column
However for the flipPieces functions, a = i = row and b = j = column
*/

#include <iostream>
#include <cstdlib>															// For the system() function
#include <string>
#include <fstream>
using namespace std;

const int array_size = 8;													// This program will use board[0][0] to board[7][7]
char board[array_size][array_size];											// Board declaration
int row = 0, column = 0;													// Row and column
char turn = 'X';															// turn = 'X' means X is moving, turn = 'O' means O is moving
bool XSkip = true, OSkip = true;											// Decides whether or not the player can skip his turn
int skipTwice = 0;															// If two skips are done in a row, it means the game is over
int choice1 = 1, Ichoice2 = 1;												// Choice for main menu and the game menu
string Schoice2 = "";														// String for the game menu input
int XPower1 = 1, XPower2 = 1, OPower1 = 1, OPower2 = 1;						// Count for the super powers

//Function declarations
void initialiseArray();
void drawBoard();
void arrayValues();
void arrayValuesEndGame();
void reinitialiseMoves();
void possibleMoves();
bool emptySpaceEast(int a, int b);
bool emptySpaceWest(int a, int b);
bool emptySpaceNorth(int a, int b);
bool emptySpaceSouth(int a, int b);
bool emptySpaceSouthEast(int a, int b);
bool emptySpaceSouthWest(int a, int b);
bool emptySpaceNorthEast(int a, int b);
bool emptySpaceNorthWest(int a, int b);
void flipPiecesWest(int a, int b);
void flipPiecesEast(int a, int b);
void flipPiecesNorth(int a, int b);
void flipPiecesSouth(int a, int b);
void flipPiecesNorthEast(int a, int b);
void flipPiecesNorthWest(int a, int b);
void flipPiecesSouthEast(int a, int b);
void flipPiecesSouthWest(int a, int b);
void flipBoard(int a, int b);
bool checkForStar();
void checkSkipPlayerTurn();
bool boardFull();
bool allSame();
void playGame();
int validateChoice2();
bool convertPower(int IconvertRow, bool boolRow);
void saveGame();
bool loadGame();
void playerMove();


int main()
{
	while ((choice1 <= 4) && (choice1 >= 1))
	{
		//Reinitialise the global variables every time the user enters the main menu
		turn = 'X';
		XSkip = true;
		OSkip = true;
		skipTwice = 0;
		XPower1 = 1;
		XPower2 = 1;
		OPower1 = 1;
		OPower2 = 1;
		
		cout << "Welcome to the Othello game! Please select an option (input 1, 2, 3 or 4): \n";
        cout << "1. New Game \n";
        cout << "2. Load A Game \n";
        cout << "3. Help \n";
		cout << "4. Quit \n";
        cin >> choice1;
		cin.ignore(100, '\n');
		system("cls");
		
		if (choice1 == 1)
		{
			initialiseArray();
			reinitialiseMoves();
			possibleMoves();
			Ichoice2 = 1;
			playGame();
		}
		else if(choice1 == 2)
		{
			if(loadGame())
			{
				possibleMoves();
				Ichoice2 = 1;
				playGame();
			}
		}
		else if(choice1 == 3)																		// Displays rules and features of the game
		{
			cout << "\nIn Othello, there are two players. One will control the 'O' pieces and another will control the 'X' pieces. \n";
			cout << "The purpose of this game is to 'eat' your opponent's pieces by placing one of your piece so that it covers two ends\n";
			cout << "of the opponent's piece(s). Then, all the opponent's piece(s) will be converted into your piece(s). \n";
			cout << "Whoever has the most of their pieces on the board when the game is over will be the victor.\n";
			cout << "The player controlling the 'X' pieces will begin the game.\n";
			cout << "To place your piece, you must enter the alphabet of the column followed by the number of the row.\n";
			cout << "For example, if you would like to place your piece at the first row and the first column, you would have to enter 'a1'";
			cout << "without the two ' symbols.\n";
			cout << "For each turn you have to place a piece that will eat your opponent's piece, or else you must skip your turn.\n";
			cout << "The game will end when the board is full or when two skips are done in a row or when the board is filled with all X or all O.\n";
			cout << "Each player will have be able to use two different super powers once. \n";
			cout << "The first super power is called Double Trouble. It enables you to move twice in a row.\n";
			cout << "The second super power is called Retaliation where you can change one row or column of your opponent's pieces into your pieces.\n";
			cout << "Good luck and have fun! You will be returned to the main menu.\n\n";
			choice1 = 1;																			// Sends the user back to the main menu to choose another option
		}
		else if (choice1 == 4)																		// Exits the program
		{
			cout << "\nThank you for playing!\n";
			system("pause");
			choice1 = 0;
		}
		else																						//Invalid input
		{
			cout << "Invalid input! Please input your choice again!\n";
			choice1 = 1;
			cin.clear();
			cin.ignore(100, '\n');
		}
	}
	return 0;
}

// Function to initialise the array to an empty character
void initialiseArray()														
{
    int i = 0, j = 0;
    for (i = 0; i < 8; i++)													// Initialises board[1][1] to board[8][8] to empty characters
    {   
        for(j = 0; j < 8; j++)
        {
            board[i][j] = ' ';
        }
    }    
	
	// Fills the starting pieces with X and O
	board[3][3] = board[4][4] = 'X';
	board[3][4] = board[4][3] = 'O';
}

// Function to draw the pieces on the board and the board itself
void drawBoard()															
{
    int drawing_row = 0, drawing_column = 0;								// Variables to draw the pattern of the board
    char column_letter = 'a';												// Variable to show the alphabets below the board
    int game_row = 8;														// Variable to indicate the game rows
    int game_column = 0;													// Variable to indicate the game columns
    
    // To draw the lines until line 1
    for(drawing_row = 9; drawing_row > 0; drawing_row--)
   {
     	cout << "\n  |";                                   					// To get 9 |

     	for(drawing_column = 1; drawing_column < 9; drawing_column++)
	    {
			if (drawing_column < 8)
			{
				cout << "---+";												// To get 7 sets of ---+
			}
			else
			{
				cout << "---|\n";											// To get one set of ---|
			}
	    }
	    
	    if (game_row != 0)					
    	{   
    	    cout << game_row << " |";			               				// Adds the row number
            	
	        for (game_column = 0; game_column != 8; game_column++)          // Because 8 more | are needed
	        {
	            cout << " " << board[game_row - 1][game_column] << " |";		// Shows the value in the array and draws a | for every round
	        }
			
			game_row = game_row - 1;			            				// Decreases row number from 8 -> 7 -> ... -> 1
    	}
    	else																// Shows the final line containing alphabets
    	{
    	    cout << "  ";
    	    
    	    for(column_letter = 'a'; column_letter != 'i'; column_letter++) 
    	    {
    	        cout << "  " << column_letter << " ";
    	    }
    	}
   }
   
   arrayValues();
}

// Function to check values of the array and output the results of the last move (score)
void arrayValues()																						
{																										
	int i = 0, j = 0;
	int O = 0, X = 0;
	
    for (i = 0; i < 8; i++)													
    {   
        for(j = 0; j < 8; j++)
        {
            if (board[i][j] == 'O')
			{
				O = O + 1;
			}
			else if (board[i][j] == 'X')
			{
				X = X + 1;
			}
        }
    }    
	
	cout << "\nScore:	O = " << O << "		X = " << X << endl;
}

// Function to check values of the array and output the results when the game is over
void arrayValuesEndGame()
{
	int i = 0, j = 0;
	int O = 0, X = 0;
	
    for (i = 0; i < 8; i++)													
    {   
        for(j = 0; j < 8; j++)
        {
            if (board[i][j] == 'O')
			{
				O = O + 1;
			}
			else if (board[i][j] == 'X')
			{
				X = X + 1;
			}
        }
    }    
	
	cout << "Player O has " << O << " pieces and player X has " << X <<  " pieces." << endl;
	
	if (O>X)
	{
		cout << "The winner is O!" << endl;
	}
	else if(X > O)
	{
		cout << "The winner is X!" << endl;
	}
	else if(X == O)
	{
		cout << "There is no winner! This match ends in a draw!" << endl;
	}
}

// Removes all the * from the array board[][]
void reinitialiseMoves()													
{
	int i, j;
	
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j< 8; j++)
		{
			if(board[i][j] == '*')
			{
				board[i][j] = ' ';
			}
		}
	}
}

// Draws * at places where you can put your pieces
void possibleMoves()																
{
	int i, j;
	XSkip = true;
	OSkip = true;
	
	if(turn == 'X')
	{
		for(i = 0; i < 8; i++)
		{
			for(j = 0; j < 8; j++)
			{
				if(board[i][j] == 'X')
				{
					if(board[i][j+1] == 'O' && emptySpaceEast(i, j))
					{
						board[i][column] = '*';
						XSkip = false;
					}
					if(board[i][j-1] == 'O' && emptySpaceWest(i, j))
					{
						board[i][column] = '*';
						XSkip = false;
					}
					if(board[i+1][j] == 'O' && emptySpaceNorth(i,j))
					{
						board[row][j] = '*';
						XSkip = false;
					}
					if(board[i-1][j] == 'O' && emptySpaceSouth(i,j))
					{
						board[row][j] = '*';
						XSkip = false;
					}
					if(board[i-1][j+1] == 'O' && emptySpaceSouthEast(i,j))
					{
						board[row][column] = '*';
						XSkip = false;
					}
					if(board[i+1][j+1] == 'O' && emptySpaceNorthEast(i,j))
					{
						board[row][column] = '*';
						XSkip = false;
					}
					if(board[i+1][j-1] == 'O' && emptySpaceNorthWest(i,j))
					{
						board[row][column] = '*';
						XSkip = false;
					}
					if(board[i-1][j-1] == 'O' && emptySpaceSouthWest(i,j))
					{
						board[row][column] = '*';
						XSkip = false;
					}
				}
			}
		}
		system("cls");
		drawBoard();
	}
	else if(turn == 'O')
	{
		for(i = 0; i < 8; i++)
		{
			for(j = 0; j < 8; j++)
			{
				if(board[i][j] == 'O')
				{
					if(board[i][j+1] == 'X' && emptySpaceEast(i, j))
					{
						board[i][column] = '*';
						OSkip = false;
					}
					if(board[i][j-1] == 'X' && emptySpaceWest(i, j))
					{
						board[i][column] = '*';
						OSkip = false;
					}
					if(board[i+1][j] == 'X' && emptySpaceNorth(i,j))
					{
						board[row][j] = '*';
						OSkip = false;
					}
					if(board[i-1][j] == 'X' && emptySpaceSouth(i,j))
					{
						board[row][j] = '*';
						OSkip = false;
					}
					if(board[i-1][j+1] == 'X' && emptySpaceSouthEast(i,j))
					{
						board[row][column] = '*';
						OSkip = false;
					}
					if(board[i+1][j+1] == 'X' && emptySpaceNorthEast(i,j))
					{
						board[row][column] = '*';
						OSkip = false;
					}
					if(board[i+1][j-1] == 'X' && emptySpaceNorthWest(i,j))
					{
						board[row][column] = '*';
						OSkip = false;
					}
					if(board[i-1][j-1] == 'X' && emptySpaceSouthWest(i,j))
					{
						board[row][column] = '*';
						OSkip = false;
					}
				}
			}
		}
		system("cls");
		drawBoard();
	}
}

//For right side - Tries to find an empty space beside the opponent's piece(s)
bool emptySpaceEast(int a, int b)
{
	int j;
	for(j = b + 2; j < 8; j++)
	{
		if(board[a][j] == ' ')
		{
			column = j;
			return true;
		}
		else if(board[a][j] == turn)
		{
			return false;
		}
		else if(board[a][j] == '*')
		{
			return false;
		}
	}
	return false;
}

//For left side - Tries to find an empty space beside the opponent's piece(s)
bool emptySpaceWest(int a, int b)
{
	int j;
	for(j = b - 2; j >= 0; j--)
	{
		if(board[a][j] == ' ')
		{
			column = j;
			return true;
		}
		else if(board[a][j] == turn)
		{
			return false;
		}
		else if(board[a][j] == '*')
		{
			return false;
		}
	}
	return false;
}

//For top - Tries to find an empty space above the opponent's piece(s)
bool emptySpaceNorth(int a, int b)
{
	int i;
	for(i = a + 2; i < 8; i++)
	{
		if(board[i][b] == ' ')
		{
			row = i;
			return true;
		}
		else if(board[i][b] == turn)
		{
			return false;
		}
		else if(board[i][b] == '*')
		{
			return false;
		}
	}
	return false;
}

//For bottom - Tries to find an empty space below the opponent's piece(s)
bool emptySpaceSouth(int a, int b)
{
	int i;
	for(i = a - 2; i >= 0; i--)
	{
		if(board[i][b] == ' ')
		{
			row = i;
			return true;
		}
		else if(board[i][b] == turn)
		{
			return false;
		}
		else if(board[i][b] == '*')
		{
			return false;
		}
	}
	return false;
}

//For south east - Tries to find an empty space south east of the opponent's piece(s)
bool emptySpaceSouthEast(int a, int b)
{
	int i = a - 2;
	int j;
	for(j = b + 2; j < 8; j++)
	{
		if(board[i][j] == ' ')
		{
			row = i;
			column = j;
			return true;
		}
		else if(board[i][j] == turn)
		{
			return false;
		}
		else if(board[i][j] == '*')
		{
			return false;
		}
		i--;
	}
	return false;
}

//For south west - Tries to find an empty space south west of the opponent's piece(s)
bool emptySpaceSouthWest(int a, int b)
{
	int i = a - 2;
	int j;
	for(j = b - 2; j >= 1; j--)
	{
		if(board[i][j] == ' ')						
		{
			row = i;
			column = j;
			return true;
		}
		else if(board[i][j] == turn)
		{
			return false;
		}
		else if(board[i][j] == '*')
		{
			return false;
		}
		i--;	
		
	}
	return false;
}

//For north east - Tries to find an empty space north east of the opponent's piece(s)
bool emptySpaceNorthEast(int a, int b)
{
	int i = a + 2;
	int j;
	for(j = b + 2; j < 8; j++)
	{
		if(board[i][j] == ' ')
		{
			row = i;
			column = j;
			return true;
		}
		else if(board[i][j] == turn)
		{
			return false;
		}
		else if(board[i][j] == '*')
		{
			return false;
		}
		i++;
	}
	return false;
}

//For north west - Tries to find an empty space north west of the opponent's piece(s)
bool emptySpaceNorthWest(int a, int b)
{
	int i = a + 2;
	int j;
	for(j = b - 2; j >= 0; j--)
	{
		if(board[i][j] == ' ')
		{
			row = i;
			column = j;
			return true;
		}
		else if(board[i][j] == turn)
		{
			return false;
		}
		else if(board[i][j] == '*')
		{
			return false;
		}
		i++;
	}
	return false;
}

//Flips the pieces which are required to be flipped by calling all the flipPieces functions
void flipBoard(int a, int b)
{
	flipPiecesWest(a, b);
	flipPiecesEast(a, b);
	flipPiecesNorth(a, b);
	flipPiecesSouth(a, b);
	flipPiecesNorthEast(a, b);
	flipPiecesNorthWest(a, b);
	flipPiecesSouthEast(a, b);
	flipPiecesSouthWest(a, b);
}

//Searches for the current player's first piece to the right of *, then flips all in between
void flipPiecesWest(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	
	for(j = b + 1; j < 8; j++)				//Tries to find the current player's first piece to the right
	{
		if(board[a][j] == turn)
		{
			changeColumn = j;				//changeColumn stores the column of the current player's first piece to the right
			break;
		}
		else if(board[a][j] == ' ')
		{
			break;
		}
		else if(board[a][j] == '*')
		{
			break;
		}
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		for(j = changeColumn - 1; j >= b; j--)		//Changes all pieces in between the column of the new piece and the current player's first piece to the right
		{
			board[a][j] = turn;						
		}
	}
}

//Searches for the current player's first piece to the left of *, then flips all in between
void flipPiecesEast(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	
	for(j = b - 1; j >= 0; j--)
	{
		if(board[a][j] == turn)
		{
			changeColumn = j;						//changeColumn stores the column of the current player's first piece to the left
			break;
		}
		else if(board[a][j] == ' ')
		{
			break;
		}
		else if(board[a][j] == '*')
		{
			break;
		}
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		for(j = changeColumn + 1; j <= b; j++)		//Changes all pieces in between the column of the new piece entered and the current player's first piece to the left
		{
			board[a][j] = turn;						
		}
	}
}

//Searches for the current player's first piece to the south of *, then flips all in between
void flipPiecesNorth(int a, int b)
{
	int changeRow = -1;
	int i = 0;
	
	for(i = a - 1; i >= 0; i--)
	{
		if(board[i][b] == turn)
		{
			changeRow = i;							//changeRow stores the row of the current player's first piece found at the bottom of the inputted piece
			break;
		}
		else if(board[i][b] == ' ')
			{
			break;
		}
		else if(board[i][b] == '*')
		{
			break;
		}
	}
	
	if (changeRow == -1)
	{
		exit;
	}
	else
	{
		for(i = changeRow + 1; i <= a; i++)			//Changes all pieces in between the row of the new piece and the current player's first piece at the bottom of the inputted piece
		{
			board[i][b] = turn;						
		}
	}
}

//Searches for the current player's first piece to the north of *, then flips all in between
void flipPiecesSouth(int a, int b)
{
	int changeRow = -1;
	int i = 0;
	
	for(i = a + 1; i < 8; i++)
	{
		if(board[i][b] == turn)
		{
			changeRow = i;							//changeRow stores the row of the current player's first piece found at the top of the inputted piece
			break;
		}
		else if(board[i][b] == ' ')
			{
			break;
		}
		else if(board[i][b] == '*')
		{
			break;
		}
	}
	
	if (changeRow == -1)
	{
		exit;
	}
	else
	{
		for(i = changeRow - 1; i >= a; i--)			//Changes all pieces in between the row of the new piece the current player's first piece at the top of the inputted piece
		{
			board[i][b] = turn;						
		}
	}
}

//Searches for the current player's first piece to the south west of *, then flips all in between
void flipPiecesNorthEast(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	a--;
	
	for(j = b - 1; j >= 0; j--)
	{
		if (board[a][j] == turn)
		{
			changeColumn = j;						//changeColumn stores the column of the current player's first piece to the southwest
			break;
		}
		else if (board[a][j] == ' ')
		{
			break;
		}
		else if (board[a][j] == '*')
		{
			break;
		}
		a--;
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		a++;
		for(j = changeColumn + 1; j <= b; j++)
		{
			board[a][j] = turn;						//Changes all pieces in between the coordinates of the new piece entered and the current player's first piece to the southwest
			a++;
		}
	}
}

//Searches for the current player's first piece to the south east of *, then flips all in between
void flipPiecesNorthWest(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	a--;
	
	for(j = b + 1; j < 8; j++)
	{
		if(board[a][j] == turn)
		{
			changeColumn = j;						//changeColumn stores the column of the current player's first piece to the southeast
			break;
		}
		else if(board[a][j] == ' ')
		{
			break;
		}
		else if(board[a][j] == '*')
		{
			break;
		}
		a--;
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		a++;
		for(j = changeColumn - 1; j >= b; j--)
		{
			board[a][j] = turn;						//Changes all pieces in between the coordinates of the new piece entered and the current player's first piece to the southeast
			a++;
		}
	}
}

//Searches for the current player's first piece to the north east of *, then flips all in between
void flipPiecesSouthWest(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	a++;
	
	for(j = b + 1; j < 8; j++)
	{	
		if(board[a][j] == turn)
		{
			changeColumn = j;						//changeColumn stores the column of the current player's first piece to the northeast
			break;
		}
		else if(board[a][j] == ' ')
		{
			break;
		}
		else if(board[a][j] == '*')
		{
			break;
		}
		a++;
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		a--;
		for(j = changeColumn - 1; j >= b; j--)
		{
			board[a][j] = turn;						//Changes all pieces in between the coordinates of the new piece entered and the current player's first piece to the northeast
			a--;
		}
	}
}

//Searches for the current player's first piece to the north west of *, then flips all in between
void flipPiecesSouthEast(int a, int b)
{
	int changeColumn = -1;
	int j = 0;
	a++;
	
	for(j = b - 1; j >= 0; j--)
	{	
		if(board[a][j] == turn)
		{
			changeColumn = j;						//changeColumn stores the column of the current player's first piece to the northwest
			break;
		}
		else if(board[a][j] == ' ')
		{
			break;
		}
		else if(board[a][j] == '*')
		{
			break;
		}
		a++;
	}
	
	if (changeColumn == -1)
	{
		exit;
	}
	else
	{
		a--;
		for(j = changeColumn + 1; j <= b; j++)			//Changes all pieces in between the coordinates of the new piece entered and the current player's first piece to the northwest
		{
			board[a][j] = turn;
			a--;
		}
	}
}

//Checks if there are any * in the board
bool checkForStar()
{
	int i, j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(board[i][j] == '*')
			{
				return true;
			}
		}
	}
	return false;
}

//Checks whether or not the player can skip his turn
void checkSkipPlayerTurn()
{
	bool flag = checkForStar();
	if((turn == 'X') && (flag == true))
	{
		XSkip = false;
	}
	else if((turn == 'O') && (flag == true))
	{
		OSkip = false;
	}
}

//Checks if board is full
bool boardFull()
{
	int i, j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(board[i][j] == ' ' || board[i][j] == '*')					//If there is even one empty space or one *, return false
			{
				return false;
			}
		}
	}
	
	return true;
}

//Checks if the board is full with X or full with O
bool allSame()
{
	if(turn == 'X')
	{
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 7; j++)
			{
				if(board[i][j] == 'X')
				{
					return false;
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 7; j++)
			{
				if(board[i][j] == 'O')
				{
					return false;
				}
			}
		}
	}
	
	return true;
} 

//Starts the game
void playGame()
{
	while ((Ichoice2 <= 6) && (Ichoice2 >= 1))
	{	
		if (turn == 'X')
		{
			cout << "Current Player:		X" << endl;
		}
		else
		{
			cout << "Current Player:		O" << endl;
		}
		
		checkSkipPlayerTurn();																// Determines whether the player must skip his turn or not
				
		if((boardFull() == true) || skipTwice == 2 || (allSame() == true))					// If any of these conditions are satisfied, the game ends
		{
			cout << "The game has ended! ";
			arrayValuesEndGame();
			system("pause");
			system("cls");
			break;
		}
				
		cout << "\nPlease input your choice: \n";
		cout << "1. ==> f4 (place a new piece at coordinates (f,4) and proceed to next player)\n";		// Allows user to input his move at locations with '*'
		cout << "2. ==> menu (return to game menu)\n";													// Returns to main menu
		cout << "3. ==> save a.txt (save the game to a file name 'a.txt' and return to the game)\n";	// Saves a game file
		cout << "4. ==> next player (let next player make his move)\n";									// Skips the turn if no move is possible
		cout << "5. ==> super1 - Double Trouble (use superpower 1 and proceed to next player)\n";	    // Allows user to move twice in a row
		cout << "6. ==> super2 - Retaliation (use superpower 2 and proceed to next player)\n" ;			// Allows user to change an entire row/column to his pieces
		getline(cin, Schoice2);
		Ichoice2 = validateChoice2();
				
		if (Ichoice2 == 1)
		{
			/*
			Reinitialise skipTwice to zero. Flips over the necessary pieces. 
			Then, reinitialise moves, show board, count pieces, switch turn and calculate possible moves.
			*/
					
			skipTwice = 0;
			flipBoard(row, column);
			reinitialiseMoves();
					
			if(turn == 'X')
			{
				turn = 'O';
			}
			else
			{
				turn = 'X';
			}
					
			possibleMoves();
		}
		else if(Ichoice2 == 2)
		{
			cout << "Thank you for playing Othello!\n";
			choice1 = 1;																	// Resetting choice1 to its initial state
			Ichoice2 = 0;																	// To exit the current loop
		}
		else if(Ichoice2 == 3)																// Saves the game
		{
			saveGame();
		}
		else if(Ichoice2 == 4)																// The player must skip his turn if he cannot make any moves
		{
			if((turn == 'X') && (XSkip == true))
			{
				cout << "Player X has skipped his turn.\n";
				turn = 'O';
				reinitialiseMoves();
				possibleMoves();
				skipTwice = skipTwice + 1;
			}
			else if((turn == 'O') && (OSkip == true))
			{
				cout << "Player O has skipped his turn.\n";
				turn = 'X';
				reinitialiseMoves();
				possibleMoves();
				skipTwice = skipTwice + 1;
			}
			else
			{
				cout << "You cannot skip your turn. Please choose another option!\n";
			}
		}
		else if(Ichoice2 == 5)																// Allows the player to move twice
		{
			if((turn == 'X') && (XPower1 == 1) && (XSkip == false))
			{
				XPower1 = 0;
						
				skipTwice = 0;
				playerMove();
				flipBoard(row, column);
				reinitialiseMoves();
				possibleMoves();
				cout << "Current Player:		X" << endl;
				checkSkipPlayerTurn();														// Determines whether the player must skip his turn or not
						
				if(XSkip == false)															// If he doesn't need to skip, he moves again
				{
					playerMove();
					flipBoard(row, column);
					reinitialiseMoves();
					turn = 'O';
					possibleMoves();
				}
				else																		// If he must skip, he wastes his second turn
				{
					cout << "You must skip your turn. Your second turn will be wasted. \n";
					system("pause");
					system("cls");
					turn = 'O';
					reinitialiseMoves();
					possibleMoves();
					skipTwice = skipTwice + 1;
				}
			}
			else if((turn == 'O') && (OPower1 == 1) && (OSkip == false))
			{
				OPower1 = 0;
				
				skipTwice = 0;
				playerMove();
				flipBoard(row, column);
				reinitialiseMoves();
				possibleMoves();
				cout << "Current Player:		O" << endl;
				checkSkipPlayerTurn();														// Determines whether the player must skip his turn or not
						
				if(OSkip == false)															// If he doesn't need to skip, he moves again
				{
					playerMove();
					flipBoard(row, column);
					reinitialiseMoves();
					turn = 'X';
					possibleMoves();
				}
				else																		// If he must skip, he wastes his second turn
				{
					cout << "You must skip your turn. Your second turn will be wasted. \n";
					system("pause");
					system("cls");
					turn = 'X';
					reinitialiseMoves();
					possibleMoves();
					skipTwice = skipTwice + 1;
				}
			}
			else
			{
				cout << "You cannot use this power now. The requirements for you to use this power are:" << endl;
				cout << "1. You must be using this power for the first time" << endl;
				cout << "2. You are able to put at least one piece on the board (you cannot skip your turn)" << endl;
				cout << "Please select another option." << endl;
				system("pause");
			}
		}
		else if(Ichoice2 == 6)														// Changes an entire row/column to the player's pieces
		{
			if((turn == 'X' && XPower2 == 1) || (turn == 'O' && OPower2 == 1))
			{
				char convert;														// Stores the user input
				int Iconvert;														// Stores the row or column number that the user wants to convert
				bool flag = false;													// Ensures the user inputs a valid input
				bool boolRow = false;												// If true, it means the power is going to convert a row, else, it will convert a column
		
				do
				{
					cout << "Enter the row/column which you want to change into your pieces ==> ";
					cin >> convert;
					convert = tolower(convert);
						
					if((convert >= '1') && (convert <= '8'))
					{
						Iconvert = toascii(convert) - 49;				// 49 is ASCII '1'. If user input 8 (ASCII 56), 56 - 49 = 7, row for array = 7
						flag = true;
						boolRow = true;
					}
					else if((convert >= 'a') && (convert <= 'h'))
					{
						Iconvert = toascii(convert) - 97;				// 97 is ASCII small 'a'. If user input b (ASCII 98), 98 - 97 = 1, column for array = 1
						flag = true;
						boolRow = false;
					}
					
				}while(flag == false);									
						
				bool powerUsed = convertPower(Iconvert, boolRow);
				
				if(powerUsed == false)									// If there is a problem with the input, an error message will be produced
				{
					cout << "The row/column you have selected is either empty or contains only your pieces. You cannot use your power.\n";
				}
				else
				{
					if(turn == 'X')
					{
						turn = 'O';
					}
					else
					{
						turn = 'X';
					}
					
					reinitialiseMoves();
					possibleMoves();
				}
				cin.ignore(100, '\n');
			}
			else
			{
				cout << "You have already used this power.\n";
			}
		}
		else
		{
			cout << "Invalid option. Please try again. \n";
			Ichoice2 = 1;
		}
	}
			
}

//Validates Schoice2 from playGame()
int validateChoice2()
{
	int Ichoice2local = 0;
	char player_move_column_char = ' ', player_move_row_char = ' ';
	
	for(int i = 0; i < Schoice2.length(); i++)
	{
		Schoice2[i] = tolower(Schoice2[i]);
	}
	
	if(Schoice2.length() == 2)
	{
		player_move_column_char = Schoice2.at(0);
		player_move_row_char = Schoice2.at(1);
		row = toascii(player_move_row_char) - 49;						// 49 is ASCII '1'. If user input 8 (ASCII 56), 56 - 49 = 7, row for array = 7
		
		if(((player_move_column_char >= 'a') && (player_move_column_char <= 'h')) && ((row >= 0) && (row <= 7)))
		{
			column = toascii(player_move_column_char) - 97;				// 97 is ASCII small 'a'. If use input b (ASCII 98), 98 - 97 = 1, column for array = 1
			if(board[row][column] == '*')
			{
				board[row][column] = turn;
				Ichoice2local = 1;
				return Ichoice2local;
			}
			else
			{
				cout << "Invalid input. Please choose a square with a * in it!" << endl;		// Player can only input in a box with a *
				return Ichoice2local;
			}
		}
		else
		{
			cout << "Please input the coordinates in the correct format!" << endl;
			return Ichoice2local;
		}
	}
	else if((Schoice2.length() == 4) && (Schoice2 == "menu"))
	{
		Ichoice2local = 2;
		return Ichoice2local;
	}
	else if((Schoice2.substr(0, 5) == "save ") && (Schoice2.substr((Schoice2.length() - 4), 4)) == ".txt")
	{
		Ichoice2local = 3;
		return Ichoice2local;
	}
	else if((Schoice2.length() == 11) && (Schoice2 == "next player"))
	{
		Ichoice2local = 4;
		return Ichoice2local;
	}
	else if((Schoice2.length() == 6) && (Schoice2 == "super1"))
	{
		Ichoice2local = 5;
		return Ichoice2local;
	}
	else if((Schoice2.length() == 6) && (Schoice2 == "super2"))
	{
		Ichoice2local = 6;
		return Ichoice2local;
	}
	else
	{
		return Ichoice2local;
	}
}

//Converts a row or a column of the player's choice when the player uses super2
bool convertPower(int Iconvert, bool boolRow)
{
	bool powerUsed = false;
	
	if(boolRow == true)									// Converts a row to the user's pieces
	{
		for(int j = 0; j < 8; j++)
		{
			if (turn == 'X')
			{
				if(board[Iconvert][j] == 'O')
				{
					board[Iconvert][j] = 'X';
					XPower2 = 0;
					powerUsed = true;
				}
			}
			else if (turn == 'O')
			{
				if(board[Iconvert][j] == 'X')
				{
					board[Iconvert][j] = 'O';
					OPower2 = 0;
					powerUsed = true;
				}
			}
		}
	}
	else												// Converts a column to the user's pieces
	{
		for(int i = 0; i < 8; i++)
		{
			if (turn == 'X')
			{
				if(board[i][Iconvert] == 'O')
				{
					board[i][Iconvert] = 'X';
					XPower2 = 0;
					powerUsed = true;
				}
			}
			else if (turn == 'O')
			{
				if(board[i][Iconvert] == 'X')
				{
					board[i][Iconvert] = 'O';
					OPower2 = 0;
					powerUsed = true;
				}
			}
		}
	}
	
	return powerUsed;
}

//Saves the game file of the player
void saveGame()
{
	char copyBoard[array_size][array_size];
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			copyBoard[i][j] = board[i][j];
		}
	}
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j< 8; j++)
		{
			if((copyBoard[i][j] == '*') || (copyBoard[i][j] == ' '))
			{
				copyBoard[i][j] = 'E';			//Replaces empty spaces and * with the letter E
			}
		}
	}
	
	string fileName = Schoice2.substr(5, (Schoice2.length() - 5));
	ofstream save;
	save.open(fileName.c_str());				//Class std:: ofstream does not take an std::string as argument, it takes a const char*.
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			save << copyBoard[i][j];
		}
	}
	
	save << XPower1 << " " << XPower2 << " " << OPower1 << " " << OPower2 << " " << skipTwice << " " << turn;
	save.close();
	cout << "Successfully saved the game data!\n";
}

//Loads the game file of the player
bool loadGame()
{
	string fileName;												// Store the file name input by the user
	char copyBoard[array_size][array_size];							// Array to store the loaded data
	
	cout << "Enter the file name which you want to load (ex: 'othello.txt'): \n";
	getline(cin, fileName);
	
	ifstream load;
	load.open(fileName.c_str());
	
	// Check if the file exist or not. Terminate the program prematurely if file does not exist.
	if ( !load )
	{
		cout << "Error reading file. Program Exit." << endl;
		return false;
	}
	
	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			load >> board[i][j];
		}
	}
	
	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j] == 'E')
			{
				board[i][j] = ' ';
			}
		}
	}
	
	load >> XPower1 >> XPower2 >> OPower1 >> OPower2 >> skipTwice >> turn;
	load.close();
	return true;
}

//Gets the coordinates of the player and puts it at the wanted coordinate. ONLY FOR super1. 
void playerMove()
{
	char player_move_column_char = ' ', player_move_row_char = ' ';
	string move;
	bool flag = false;
	
	do
	{
		cout << "Enter your coordinates (Example: b5): ";
		getline(cin, move);
		
		if(move.length() == 2)
		{
			player_move_column_char = move.at(0);
			player_move_row_char = move.at(1);
			row = toascii(player_move_row_char) - 49;						// 49 is ASCII '1'. If user input 8 (ASCII 56), 56 - 49 = 7, row for array = 7
			
			if(((player_move_column_char >= 'a') && (player_move_column_char <= 'h')) && ((row >= 0) && (row <= 7)))
			{
				column = toascii(player_move_column_char) - 97;				// 97 is ASCII small 'a'. If use input b (ASCII 98), 98 - 97 = 1, column for array = 1
				if(board[row][column] == '*')
				{
					board[row][column] = turn;
					flag = true;
				}
				else
				{
					cout << "Invalid input. Please choose a square with a * in it!" << endl;		// Player can only input in a box with a *
				}
			}
			else
			{
				cout << "Invalid input. Please enter the coordinates in the correct format." << endl;
			}
		}
	}while(flag == false);
}