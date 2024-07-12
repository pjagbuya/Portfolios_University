/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
PAUL JOSEF P. AGBUYA, DLSU ID# 12206660
******************************************************************/

/*
	Description: Checkers Game Program, a game where two players play on a board that is a 8x8 grid. 
	Each player will have 12 pieces. A player  moves these pieces only through one space diagonally, or
	two spaces when capturing diagonally. A player wins when the other surrenders, loses all pieces, 
	the player has their piece reach the end of the opponent's board, or opponent's pieces are blocked
	Programmed by: Paul Josef P. Agbuya S21A
	Last Modified: Dec 4, 2022
	Version: 1.0
	[Acknowledgements: Sites or borrower libraries and sources
	
	Pointer Notation Array Learning:
		-https://www.youtube.com/watch?v=gsOZ-xMs6Zg&t=786s
	
	ASCII Art Sources:
		-https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
		-https://www.asciiart.eu
		-https://ascii.co.uk/art/flags
		-https://www.asciiart.eu/holiday-and-events/fireworks
	]
	
	
*/


#include <time.h>		//Allows the rand() function to be pseudo random
#include <stdio.h>		//standard library for printf() and scanf()
#include <string.h>		//Used for getting string length via strlen()
#include <stdlib.h>		//Used for getting the function that clears the screen: system("CLS");
						//Also used to get the abs() function
						 
#include <stdbool.h>	//Allows declaring values as boolean




#define BOX_HEIGHT 4	//Row Height dimension of the 3-D array containing a big chessboard design
#define BOX_WIDTH 8		//Row Width dimension of the 3-D array containing a big chessboard design

#define POS_ARRAY_DIM 8	//Height/WIDTH dimension of the 2-D array containing only positions of the checker pieces



/* 
	The function is used to set up the starting positions of the checker pieces which are identified as letters of the alphabets ranging from
	'A' to 'X' with A-L being the white pieces at the top half, and M-X being the black pieces on the bottom half. These will be refered to
	as Piece IDs on later functions. The 2D Array will be containing spaces, '*', and letter 'A' to 'X'. Pointer address of arrays can be declared
	as: *Array for 1-D Arrray, (*Array)[8] for 2-D array with size 8 of 2nd dimension, and (*Array)[8][10] for 3-D array with size 8 of 2nd 
	dimension and size 10 of the 3rd dimension
	
	Precondition: The array size passed to the function is equal to the size set up by the pPositions_Array. 
	
	@param pPositions_Array is a 2-Dimensional array that will store the initialized dimensions and characters to be stored
	@param nRow is the height of the array structure or how many rows there are in the array
	@param nCol is how many elements there are in each nRow, or the width/column size of the array structure
	
*/
void 
initPositions (char (*pPositions_Array)[8], 
			   int nRow, 
			   int nCol)
{

	int i, j;				//Loop counters
	int cCharVal = 65;		//Start from A

	/*
	Array arithmetic
		Things to note when assigning specific values at specific locations of the array:
	  
		The formula used when assigning values in an array will be
		*(...*( *( *(Array_Name 1st Dimension) + 2nd dimension) +  3rd dimension)... Nth dimension)
		The formula above can be interchanged with
	  
		Array_Name [1st Dimension][2nd dimension][3rd dimension]...[Nth dimension]
	  
		Array_Name on its own specifes the address of the whole array
	  
		One dimensional array
		*(Array_Name + 0) also gets the value of the first element
		Array_Name[0] also gets the value of the first element
	  
		*(Array_Name + 1) gets the value of the second element
		Array_Name[1] gets the value of the second element
	  
	  
	  
	  
		Two dimensional array
	  
		*(*(Array_Name + 0)+2) means getting to layer index 0 and getting the specific element at index 2
		Array_Name[0][2] means getting to layer index 0 and getting the specific element at index 2
	  
		*(*(Array_Name + 2)+5) means getting to layer index 2 and getting the specific element at index 5
		Array_Name[2][5] means getting to layer index 2 and getting the specific element at index 5
	  
	  
	  
	  
	  
		Three dimensional array
		Ex:
		1.) *(*(*(Array_Name + 0) + 2 ) + 3) means getting to layer index 0 and getting to another layer 
		at index 2 and select the element position at index 3
		-Array_Name[0][2][3] means getting to layer index 0 and getting to another layer at index 2 
		and select the element position at index 3
	  
		2.) *(*(*(Array_Name + 1) + 3) + 2) means getting to layer index 1 and getting to another layer at index 3 
		and select the element position at index 2
		Array_Name[1][3][2] means getting to layer index 1 and getting to another layer at index 3 
		and select the element position at index 2
	  
	  
		Therefore,
		*( *( *(Array_Name + i) + j) + k) means getting to layer index i and getting to another layer at index j 
		and select the element position at index k
	  	
		*( *( Array_Name + i) + j) means getting to layer index i and getting to element's positions at index j
	  
	  
		Assigning values to any of the above sample formats such as *(*(*(Array_Name + 1) + 3) + 2) = 'A' will 
		permanently put 'A' in that specific position
	*/
	
	
	//Number of rows in 2D checkers board
	for(i=0; i<nRow; i++)
	{			

		
		//Number of columns in a 2D checkers board
		for(j=0; j<nCol; j++)
		{		
			
			
			/*This block will design the white pieces side which is at the uppper half of the board.
			  Spannning 1st to 3rd rows. Row index range would also mean from 0 - 2
			  
			  The index numbering here starts from 0-7. So the first row layer/index would mean index 0,
			  the second row/layer would mean index 1, the third row layer/index would mean index 2, ... etc.
			  
			  4th and 5th layer should not contain any piece IDs
			*/
			
			//Sets the pieces of white at top and bot layer ("1st row and 3rd row" or "row index 0 and row index 2")
			
			if(j % 2 == 1 && 			//Every 2nd box, 4th box, 6th box ... etc.
			   i % 2 == 0 && 			//Catches 1st row and 3rd row (row index 0 and 2)
			   i < 3 )					//Restricts the pattern to only access the 1st to 3rd row and not the fourth and above
			{	
			
				*( *( pPositions_Array + i ) + j )=cCharVal;	//Assigns an identifier piece for white, this ranges from characters A-L

				cCharVal +=1;									//Moves on to next letter
				
			}
			
			//Sets the pieces of the white, middle layer ("2nd row" or "row index 1")
			
			else if(j % 2 == 0 && 		//Every 1st box, 3rd box, 5th box, ... etc.
					i == 1)				//Catches 2nd row which is between 1st row and 3rd row layer
			{	
			
				*( *( pPositions_Array + i ) + j )=cCharVal;	//Assigns an identifier piece for white, this ranges from characters A-L

				cCharVal +=1;									//Moves on to next letter
				
			}
			/*These conditions above will not be met anymore after 12 acitvations and will end with cCharVal as 'M'*/
			
			
			
			
			
			
			
			
			/*This block will design the black pieces side which is at the bottom half of the board.
			  Spannning 6th to 8th rows. Row index numbering range would also mean from 5 - 7
			*/
			
			
			//Sets the pieces of the black, top and bot layer ("6th row and 8th row" or "row index 5 and row index 7")
			
			else if (j % 2==0 && 		//Every 1st box, 3rd box, 5th box, ... etc.
			         i % 2 == 1 && 		//Catches 6th and 8th (row index 5 and 7)
					 i > 4)				//Shouldn't intersect with the code block beforehand hence selecting what is above the 5th layer
			{	  			
				
				*( *( pPositions_Array + i ) + j )=cCharVal; 		//Assigns an identifier piece for black, this ranges from characters M-X

				cCharVal +=1;										//Moves on to next letter
				
			}
			
			
			//Sets the pieces of the black, middle layer ("7th row" or "row index 6")
			
			else if (j % 2 == 1  && 	//Every 2nd box, 4th box, 6th box ... etc.
					 i == 6 )			//Selects the 7th row which is between 6th and 8th row
			{ 		
				
				*( *( pPositions_Array + i ) + j )=cCharVal;		//Assigns an identifier piece for black, this ranges from characters M-X
				
				cCharVal +=1;										//Moves on to next letter
				
				
			}
			
			
			//Makes sure the empty black spaces are actually empty black spaces by assigning a character space to them
			else
			{
				
				*( *( pPositions_Array + i ) + j)= ' '; 			
			
			}
			
			
			
			//Helps blocking the spaces that are not allowed to move on, which signifies as white space squares
			
			if ((j % 2 == 0 && i % 2 == 0) || 		//Every element at position of column index 0,2,4,.. at row index 0,2,4..
				(j % 2 == 1 && i % 2==1))			//Every element at position of column index 1,3,5,.. at row index 1,3,5..
				
				
				//Assign an asterisk that serves as blockage or white square
				*( *( pPositions_Array + i ) + j )= '*';			
			
			
			

			
			  
		}
		
	}
}


/* 
	The function is used to translate the positions of the array pPositions to the bigger and well formatted chessboard array
	which is at param pChessboard. It would give 3D chessboard array with checker pieces' parts assigned to specific positions.
	
	Precondition: The two arrays, pChessboard and pPositions have their dimensions set equal to the parameters array. 
				  cSelectedRowIndex_I, cSelectedHeight Index_J, and cSelectedWidthIndex_K, root from a three layer 
				  nested for loop which is only at function displayboard(). cSelectedRowIndex_I can only reach 0 - 7, 
				  cSelectedHeightIndex_J can only reach 0-3, and cSelectedWidthIndex_K can only reach 0 - 63.
	
	@param pChessboard is a 3-Dimensional array that sets a layout of a big chess board
	@param nSelectedRowIndex_I -Continues as the index of the for loop in function displayBoard(). 
							   -Equivalent to the row index selected in the chess board
	@param nSelectedHeightIndex_J -Continues as the index of the for loopin function displayBoard(). 
								  -Equivalent to the height index selected
	@param nSelectedWidthIndex_K -Continues as the index of the for loop in function displayBoard(). 
								 -Equivalent to the width index selected
	@param pPositions is the 2D array containing the positions of the piece IDs which are letters


*/
void 
locatePieces (char (*pChessboard)[10][100], 
			  int nSelectedRowIndex_I, 
			  int nSelectedHeightIndex_J, 
			  int nSelectedWidthIndex_K, 
			  char (*pPositions)[8])
{
	
	
	/*The ASCII char Pieces aren't properly typeable in the comment so those untypeable were replaced by '+'
	  which serve as corner elements of a square
	*/
	char cPlayerSide;					//Sets a variable to dictate what player side a letter located from A-X should be
	char cBotLeftSqr = 192; 			// 1/4 of a drawing of a square, bottom left piece		'+'
	char cBotRightSqr = 217; 			// 1/4 of a drawing of a square, bottom right piece		'+'
	char cTopRightSqr = 191; 			// 1/4 of a drawing of a square, top right piece		'+'
	char cTopLeftSqr = 218; 			// 1/4 of a drawing of a square, top left piece			'+'
	
	
	char cSelectedPosition;				//Helps store selected location of the piece
	
	
	int nColIndex;						//Describes the column index that is used to find values at pPositions
	int nRowIndex;						//Describes the row index that is used to find values at pPositions
	int nNumber;						//Help understand the piece number starting from 1-12
	
	bool bIsWhitePiece = false;			//Checks if we are black piece or white piece turn to properly translate guide on board
	bool bIsPieceLocation = false;		//Checks if the piece is present on the location via assessing the indices of Chessbaord
	
	
	/*Divides by 8 the selected width index due to designed chessboard array has a max width index of 64 
	  Our simple checker board at pPositions only numbers its column from 0 -7 or a total of 8 columns
	  Since pChessboard spans 64 columns and our simple checker board containing the piece ID spans 8 columns
	  we can simply divide the width index that we get by 8 to accurately convert the equiavlent position at the
	  array of pPositions
	*/
	nColIndex = nSelectedWidthIndex_K / 8;
	nRowIndex = nSelectedRowIndex_I;
	
	
	//Selects the position if there is a Piece ID, based on the given Chessboard index
	cSelectedPosition = *( * ( pPositions + nRowIndex ) + nColIndex);
	
	
	//Stores a seperate value that will contain the number value of the character attained at the selected position
	nNumber = cSelectedPosition;
	
	
	/*pPositions contain Piece IDs ranging from A-X, so we check for thos values
	  A = 65
	  X= 88
	*/
	if(nNumber >= 65 && nNumber < 89)		//Catches 65 - 88, inclusive
	
		/*Signifies that there is a piece present at that location
		  To start drawing one part of that piece
		*/
		bIsPieceLocation = true;				
		
	

	/*Checks the number value of the characted from A-X and converts it into a numbering of 1-12
	  Checks whether it is a whitepiece side or not*/
	if (nNumber <=76)
	{
		nNumber -= 64;
		bIsWhitePiece = true;	//A-L is white piece
	}
	else
	{
		nNumber -= 76;			//M-X is black piece
		bIsWhitePiece = false;
	}
	
	
	
	//Sets the symbol identfier for white piece
	if(bIsWhitePiece)
		cPlayerSide = 'L';
	
	
	//Sets the symbol identifier for black piece
	else
		cPlayerSide = 'D';
	
	
	
	/*When a checker piece from A-X can be located in pPositions
	  It will convert its position to the corresponding beautifully 
	  and neatly layed out in pChessboard */
	if (bIsPieceLocation)
	{
		//Ex: The example shows that the Checker Piece's elements span 4 in a column and 2 rows as its height
		// +LL+  --- '[' is first element...'L' is second element...etc. This is at layer j=1. Beginning at k % 8==2
		// +06+  --- '[' is first element...'0' is second element...etc. This is at layer j=2. Beginning at k % 8==2
		
		
		
		//TOP LAYER at j % 4 == 1
		if (nSelectedHeightIndex_J == 1 )
		{
			
			
			
			
			
			
			/*Sets the chessboard design of the checker piece to start by assigning first '+'
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +    ||######|| +    ||######| ...
				         j=2    |      ||######||      ||######|
				         j=3    +------++------++------++------+
				  
			*/
			if ( nSelectedWidthIndex_K % 8 == 2 )
			
				//The lines below follows this fromula *( *( *(Array_Name + i) + j) + k)  
				
				*( *( *(pChessboard + nSelectedRowIndex_I) + 					//Acces Row layer location then
				                      nSelectedHeightIndex_J) + 				//Height index access then
									  nSelectedWidthIndex_K) = cTopLeftSqr;		//Column index to assign element
			
			
		
		
		
		
			
			/*Sets the chessboard design of the checker piece with color identifiers by assigning 'L' as white piece or 'D' as black piece
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +LL  ||######|| +LL  ||######| ...
				         j=2    |      ||######||      ||######|
				         j=3    +------++------++------++------+
				  
			*/	
			else if (nSelectedWidthIndex_K % 8 == 3 || 
					 nSelectedWidthIndex_K % 8 == 4 )
					 
				*( *( *(pChessboard + nSelectedRowIndex_I) + 
									  nSelectedHeightIndex_J) + 
									  nSelectedWidthIndex_K) = cPlayerSide;
			
			
			
			
			
			
			
			/*Sets the chessboard design of the checker piece to end the top layer by assigning '+'
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +LL+ ||######|| +LL+ ||######| ...
				         j=2    |      ||######||      ||######|
				         j=3    +------++------++------++------+
				  
			*/	
			else if (nSelectedWidthIndex_K % 8 == 5)
			
				*( *( *(pChessboard + nSelectedRowIndex_I) 
									+ nSelectedHeightIndex_J) + 
									  nSelectedWidthIndex_K) = cTopRightSqr;
			
			
		}
		
		
		//BOTTOM LAYER at j % 4 == 2
		else if (nSelectedHeightIndex_J == 2 )
		{
			
			
			
			
			/*Sets the chessboard design of the checker piece to start the bot layer by assigning '+'
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +LL+ ||######|| +LL+ ||######| ...
				         j=2    | +    ||######|| +    ||######|
				         j=3    +------++------++------++------+
				  
			*/	
			if (nSelectedWidthIndex_K % 8 == 2)
			
				*( *( *(pChessboard + nSelectedRowIndex_I) + 
									  nSelectedHeightIndex_J) + 
									  nSelectedWidthIndex_K) = cBotLeftSqr;
			
			
			
			/*
			Depending on what number the piece is it should figure the digit characters it must displayed
			Ex: A-I is numbered 1 - 9, but J - L is number 10 - 12. Their differences lies on their tens digit
			So for Piece IDs that are numbered as 1-9 (via assigning nNumber and the process of subtracting beforehand),
			Numbers 1- 9 will be displayed on screen as "01" - "09"
			While 10 -12 is displayed as "10-12"
			
			Sets the chessboard design of the checker piece to start the bot layer's middle section by assigning string numbers "01" - "12"
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +LL+ ||######|| +LL+ ||######| ...
				         j=2    | +01  ||######|| +12  ||######|
				         j=3    +------++------++------++------+
				  
			*/
			
			//Conditions for 1 - 9 numbered PieceIDs, tens digit				
			else if (nSelectedWidthIndex_K%8 == 3 && nNumber < 10)		
											
				//Since it is less than 10, then it will be assigning obviously the digit character '0', due to no tens digit
				*( *( *(pChessboard + nSelectedRowIndex_I ) + 
									  nSelectedHeightIndex_J ) + 
									  nSelectedWidthIndex_K ) = '0';
		
			
			//Conditions for 1 - 9 numbered PieceIDs, ones digit
			else if (nSelectedWidthIndex_K%8 == 4 && nNumber < 10)										
			
				/*The number will be added by 48 since this is the ones digit, and the given integer is less than 10
				  Ex: 0 + 48 = 48 which would yield the character '0', precisely selecting the ones digit
				  	  9 + 48 = 57 which would yield the character '9', precisely selecting the ones digit
				*/
				*( *( *(pChessboard + nSelectedRowIndex_I ) + 
									  nSelectedHeightIndex_J ) + 
									  nSelectedWidthIndex_K ) = nNumber + 48;
			
		
			//Conditions for 10 - 12 numbered PieceIDs, tens digit
			else if (nSelectedWidthIndex_K % 8 == 3 && nNumber >= 10)										
				
				//Since it is more than 9 then it will be assigning obviously the digit character '1'
				*( *( *(pChessboard + nSelectedRowIndex_I) + 
									  nSelectedHeightIndex_J ) + 
									  nSelectedWidthIndex_K) = '1';
			
		
			//Conditions for 10 - 12 numbered PieceIDs, ones digit
			else if (nSelectedWidthIndex_K % 8 == 4 && nNumber >= 10)										
			
				/*The number will be added by 38 since this is the ones digit, and the given integer is more than 9
				  Ex: 10 + 38 = 48 which would yield the character '0', precisely selecting the ones digit in 10
				      12 + 38 = 50 which would yield the character '2', precisely selecting the ones digit in 12
				*/
				*( *( *(pChessboard + nSelectedRowIndex_I) + 
									  nSelectedHeightIndex_J) + 
									  nSelectedWidthIndex_K) = nNumber + 38;
			
			
			
			
			
			
			
			
			/*			
			Sets the chessboard design of the checker piece to end bot layer by assigning '+'
				When conditions are met the progress look like:
				  
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=0  j=1    | +LL+ ||######|| +LL+ ||######| ...
				         j=2    | +01+ ||######|| +12+ ||######|
				         j=3    +------++------++------++------+
				  
			*/
				
			else if (nSelectedWidthIndex_K % 8 == 5)
			
				*( *( *(pChessboard + nSelectedRowIndex_I) + 
									  nSelectedHeightIndex_J) + 
									  nSelectedWidthIndex_K) = cBotRightSqr;
			
		}
	}
	
	
	
} 
/* 
	The function is used to create a designed chessboard that is empty and is also contained in a 3-dimensional array
	
	Precondition: Defined two arrays, pChessboard  having their dimensions set equal to the dimensions alotted in this function
				  This pChessboard[10][100] is actually specifying that it has 3 dimensions, so our variable array chessboard must
				  also have 3 dimensions, cArrayChessboard[x][10][100], x can be any integer value as long as the last two are dimensions
				  the same
				  
	@param pChessboard is a 3-Dimensional array that sets a layout of a big chess board
	@param nCB_Row_Height a dimension of the chessboard array that describes the height of each row
	@param nCB_Row_Width a dimension of the chessboard array that describes the width ofr the row or could be described as the column span
	@param nCB_Rows the number of rows in a chessboard

*/
void 
makeBoard (char (*pChessboard)[10][100], 
		   int nCB_Row_Height, 
		   int nCB_Row_Width, 
		   int nCB_Rows)
{
	
	char cBottomLeftSqr = 192; 		// 1/4 of a drawing of a square, bottom left piece '+'
	char cLineSqr = 196; 			// dash line that connect square '-'
	char cBottomRightSqr = 217; 	// 1/4 of a drawing of a square, bottom right piece '+'
	char cTopRightSqr = 191; 		// 1/4 of a drawing of a square, top right piece	'+'
	char cTopLeftSqr = 218; 		// 1/4 of a drawing of a square, top left piece		'+'
	
	bool bIsBlackFirst = false;		//Boolean that will control order of alternating hashtag boxes as white box, and empty spaces as empty black boxes
	
	
	int nSelectedRowHeight_Index_J;	//Variable that will describe origin of the attained index that gives height index
	int nSelectedRowWidth_Index_K;	//Variable that will describe origin of the attained index that gives width index
	int i, j, k;					//for loop counters for row, row height index, and row width index respectively

	

	

	/* The for loop below follows a pattern of building
		
	    	k=	01234567...........63
		 j=0    +------++------+
    i=0  j=1    |######||      |
         j=2    |######||      |
         j=3    +------++------+
    	  .
    	  .
    	  .
		 j=0     +------++------+
    i=7  j=1     |      ||######|
         j=2     |      ||######|
         j=3     +------++------+
    	The comment above would depict how the array structured the board
    	
	*/
	for(i=0; i<nCB_Rows; i++)
	{
		
		
		//START of building a row
		for(j=0; j<nCB_Row_Height; j++)
		{
			for (k=0; k<nCB_Row_Width; k++)
			{
				
				//Stores the values of the index in a more readable variable
				nSelectedRowHeight_Index_J = j;
				nSelectedRowWidth_Index_K = k;
				
				//START Top Layer of square
				
				//The height index selects the first height layer of the row
				if(nSelectedRowHeight_Index_J % 4==0)
				{													
						
						/*
						This condition below makes this format
							    k=	01234567...........63
							 j=0    +       +
					    i=0  j=1    
					         j=2    
					         j=3    
						*/
						if(k%8==0) 										//Checks if its the start of the pattern on top layer
							
							// Assigns this '+'
							* ( * ( * ( pChessboard + i ) + j ) + k ) = cTopLeftSqr;

						
						
						
						
						/*
						This condition below makes this format
							    k=	01234567...........63
							 j=0    +      ++      +
					    i=0  j=1    
					         j=2    
					         j=3    
						*/
						else if(nSelectedRowWidth_Index_K % 8 == 7) 	 //Checks if its the end of the pattern on top layer via width index
							
							
							//Assigns this '+'
							*( *( *( pChessboard + i ) + j ) + k ) = cTopRightSqr;
		
						
						
						

						/*
						This condition below makes this format
							    k=	01234567...........63
							 j=0     ------  ------
					    i=0  j=1    
					         j=2    
					         j=3    
						*/
						else
							
							//Assigns this '-'
							*( *( *( pChessboard + i ) + j ) + k ) = cLineSqr;

									
						
		
					
					
				}
				/*END Top Layer of square
				  Creates the following after the conditions are no longer possible to be met:
				  	       k=	01234567...........63
						 j=0    +------++------+
				    i=0  j=1    
				         j=2    
				         j=3    
				    	  .
				    	  .
				    	  .
						 j=0    +------++------+
				    i=7  j=1    
				         j=2    
				         j=3    
				*/
				
				
				
				
				
				
				
				
				/*START Middle Layer of square, at j = 1, j =2.
				  The condition below catches the ones only at j = 1 and j = 2*/
				  
				if( nSelectedRowHeight_Index_J > 0 && nSelectedRowHeight_Index_J < 3 )
				{		
						
						/*Finds the start and end and gives  a vertical line '|' serving as drawing a 
						 line to complete the square
						 This condition below makes this example pattern
						 	     k=	 01234567...........63
						   	         +------++------+
					     i=0  j=1    |      ||      |
					          j=2    |      ||      |
					             
						*/
						if (nSelectedRowWidth_Index_K % 8 == 0||	//Signifies position at k = 0
						    nSelectedRowWidth_Index_K % 8 == 7)		//Signifies position at k = 7
						
							
							
							//Vertical line side of a square is assigned to the position
							*( *( *( pChessboard + i ) + j ) + k )= '|';				

						
	
	
	
						/*
						 These condition catches the ones located in the middle Ex: from k = 1 to k = 6
						 However it is important to note the alternating pattern of blacks square, white square
						 Hence we compare every two boxes instead:
						       k=	 01234567.......15 16.....63
						   	         +------++------+	+------+
					     i=0  j=1    |      ||      |
					          j=2    |      ||      |
						*/
						else {
							
							//Boolean that dictates if not black square, it means white box is first then black
							if (!bIsBlackFirst)
							{								
								
								
								
								
								/*When black square is not first the following example will be assigned to the array
								  The following is what happens after conditions are no longer meeting the range:
											k=	01234567...........63
										 j=0    +------++------+
								    i=7  j=1    |######||      |
								         j=2    |######||      |
								         j=3    
								  The condition below selects the range of 2nd box
								*/								

								if (nSelectedRowWidth_Index_K % 16 >= 9 && 	//Catches beginning of box two
								    nSelectedRowWidth_Index_K % 16 <= 14)	//Catches end of box two
								    
								    
									*( *( *( pChessboard + i ) + j ) + k ) = ' ';	//Empty space will highlight that it is a black empty square
								
								else
								
									*( *( *( pChessboard + i ) + j )  + k ) = '#';	//Hashtags will symbolize a white square

							
									
								
							}
							
							
							//Alternate color, black square then white square
							else
							{											
							
								/*When black square is first, the following example will be assigned to the array:
								  The following is what happens after conditions are no longer meeting the range:
											k=	 01234567...9...14...63
										 j= 0    +------+ +------+
								    i=7  j= 1    |      | |######|
								         j= 2    |      | |######|
								         j= 3    
								  The condition below selects the range of 2nd box
								*/
								if (nSelectedRowWidth_Index_K % 16 >= 9 && 	//Catches beginning of box two
								    nSelectedRowWidth_Index_K % 16 <= 14)	//Catches end of box two
								    
									*( *( *( pChessboard + i ) + j ) + k ) = '#';    //Hashtags will symbolize a white square			
								else
								
									*( *( *( pChessboard + i ) + j ) + k ) = ' ';    //Empty space will highlight that it is a black empty square

				
								
							}
						}
						
						
							
					
					
								
				}
				//END Middle Layer of row
								
			
			
			
			
			
			
			
				//START Bot Layer of square
				
				//This height index selects the last/fourth height layer of the row
				if(j % 4==3)
				{													
					
					
						/*The condition below will do this example:
									k=	01234567...........63
								 j=0    +------++------+
						    i=7  j=1    |######||      |
						         j=2    |######||      |
						         j=3    +       +

						*/			
						if(k % 8==0)											//This width index selects the first element at the particular height row
							// Assigns this '+'
							*( *( *(pChessboard + i ) + j ) + k ) = cBottomLeftSqr; 

					
						/*The condition below will do this example:
									k=	01234567...........63
								 j=0    +------++------+
						    i=7  j=1    |######||      |
						         j=2    |######||      |
						         j=3    +      ++      +

						*/							
						else if(k % 8 == 7)									//This width index selects the last element at the particular height row
							
							// Assigns this '+'
							*( *( *( pChessboard + i ) + j) + k ) = cBottomRightSqr;
			
						/*The condition below will do this example:
									k=	01234567...........63
								 j=0    +------++------+
						    i=7  j=1    |######||      |
						         j=2    |######||      |
						         j=3    +------++------+

						*/								
						else												//This width index selects the middle parts to finally build pattern of square
							//Assigns this '-'
							*( *( *( pChessboard + i ) + j ) + k ) = cLineSqr;

											
						
					
				
			
				}
				/*END Bot Layer of square
				
				  One entire row will follow this patter
							k=	01234567..............................63
						 j=0    +------++------++------++------+
				    i=7  j=1    |######||      ||######||      | ...
				         j=2    |######||      ||######||      |
				         j=3    +------++------++------++------+

				*/		
				
				
		 	}
		 	
		 	
		}
		//END of building row
		
		
		//Alternates the values to signify alternating colors of black and white
		if (bIsBlackFirst)
			bIsBlackFirst = false;
		
		else 
			bIsBlackFirst = true;
		

	}
}
/* 
	The function is used to display and translate the chessboard pieces based on pPositions to pChessboard which is the array containing
	better layout of the chessbaord. It also displays guides that chessboards have which is columns A-H and rows 1-8
	
	Precondition: The two arrays, pChessboard and pPositions have their dimensions set less than or equal to the parameters array
	
	@param pChessboard is a 3-Dimensional array that sets a layout of a big chess board
	@param nCB_Row_Height a dimension of the array that describes the chessboard's height of each row
	@param nCB_Row_Width a dimension of the array that describes the chessboard's width of the row or could be described as the column span
	@param nCB_Rows the number of rows in a chessboard
	@param pPositions accepts the array that contains the positions of the pieces
	@param bIsLocate accepts true or false, and will only show piece on the board when true
	@param bIsWhite helps notice whose turn it is and which pieces to hide


*/
void 
displayBoard (char (*pChessboard)[10][100], 
			  int nCB_Row_Height, 
			  int nCB_Row_Width, 
			  int nCB_Rows, 
			  char (*pPositions)[8], 
			  bool bIsLocateOn, 
			  bool bIsWhite)
{
	int i, j, k;								//for loop counters for row, row height index, and row width index respectively
	int nBoardNumLabel = 8;						//Numbering presented on screen is backwards
	
	char cSelectedElement;						//Contains the element selected that is stored in the chessboard array
	char cLineSqr = 196;						// dash line that connect square
	char cSelectedCharacter_Enemy;				//Selects the position that could contain the identifier of the enemy
	
	
	
	printf("\n");
	
	
	//Adds 24 spaces to the left		
	printf("%24s", " ");
	
	//Characters to label the column
	printf("    A       B       C       D       E       F       G       H\n");
	
	//Number of rows
	for(i=0; i<nCB_Rows; i++)
	{
		
		//Currently at the row layer of every j
		for(j=0; j<nCB_Row_Height; j++)
		{
			//Adds spaces to center the board
			printf("%24s", " ");
			
			//Currently at the row's col/width index layer of every k
			for (k=0; k<nCB_Row_Width; k++)
			{
				//When the code should display and assign piece labels on the board
				if (bIsLocateOn)
				
					//Modifies the array of the chessboard to have pieces based on Piece ID labels
					locatePieces(pChessboard, i, j, k, pPositions);				
				
				
				/*Code block below makes it so that only the current player's turn can see his/her number guide on screen*/
				
				//If the current turn is white, make every black piece number guide not visible
				if (bIsWhite)
				{
					/*
					The array below selects every element til the layer j=1 where the 'D' can be identified
					is achieved
					  
								k=	01234567..............................63
							        +------++------++------++------+
					    i=0  j=1    | +DD+ ||######||      ||######| ...
					         j=2    | +01+ ||######||      ||######|
					                +------++------++------++------+
						  
					*/
					cSelectedCharacter_Enemy = *( *( *(pChessboard + i ) + j-1 ) + k );
					
					
					/* 
					The array below  selects only the layer j=1 where the 'D' can be identified
					  
								k=	01234567..............................63
							        +------++------++------++------+
					    i=0  j=1    | +DD+ ||######||      ||######| ...
					         j=2    | +01+ ||######||      ||######|
					                +------++------++------++------+
						  
					*/
					if((k % 8 == 3 || k % 8 == 4) && 		//Located at column indices that are specifically k%8 = 4 or 3
						cSelectedCharacter_Enemy == 'D')	//'D' is identifier of black piece

					
					
						/* 
						The array below  referring to the position j = 2 layer which is directly below
						the position where we identified 'D'
						  
									k=	01234567..............................63
								        +------++------++------++------+
						    i=0  j=1    | +DD+ ||######||      ||######| ...
						         j=2    | +--+ ||######||      ||######|
						                +------++------++------++------+
						This would then:
							-Help remove the numbering of the enemy player.
						    -Help  give the illusion of a closed piece
							-Give indication to the current player that it is his turn
						All don through changing the value at the specific position of the array						  
						*/
						*( *( *(pChessboard + i ) + j ) + k) = cLineSqr;					
						
					
					
				}
				
				
				//If the current turn is black, make every white piece number guide not visible
				else
				{
					cSelectedCharacter_Enemy = *( *( *(pChessboard + i) + j-1) + k);
					
					
					if((k%8==3 || k%8 ==4) && cSelectedCharacter_Enemy == 'L')		//'L' is identifier of white piece in the array
					
						*( *( *(pChessboard + i ) + j ) + k) = cLineSqr;		    //Helps remove the numbering of the enemy player
						
					
					
				}
				
				//Gets the character at the address of the array
				cSelectedElement = *( *( *(pChessboard + i ) + j ) + k);
				
				//Proceed to print the character at that position
				printf("%c",  cSelectedElement);
				
				
				

				
				/*Displays numbering on the right side. Makes sure it puts the numbering at the 
				  middle spot right next to the last column 
				  CB_Row_Width-1 indicated the very last element of each row
				  j== 1 specifies at only selecting the index j of row height index
				*/
				if(k == nCB_Row_Width - 1 && j == 1)
				{				
					printf("  %d", nBoardNumLabel);
					nBoardNumLabel -= 1;
				}

			
			}
			
			
			printf("\n");
		}	
		
	}
	
	printf("\n\n");

}



/* 
	Function computes the location of the Pieces via the 2-D array chessboard which will give the values i and j which 
	are the dimension row and column index of the array
	
	Precondition: cPieceID is just a letter from A-X
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the 3-D chessboard
	@param cPieceID is a character that is a letter which serves as an ID that helps identify the piece in the checkers board
	@param pIndex_Row_I is a pointer variable in which the function would get the row index of where the cPieceID can be found
	@param pIndex_Col_J is a pointer variable in which the function would get the column index of where the cPieceID can be found
	
*/
void 
findCoordinates (char (*pPositions)[8], 
				 char cPieceID, 
				 int *pIndex_Row_I, 
				 int *pIndex_Col_J)
{
	int nRowIndex_I, nColIndex_J; 					//sets counters and describe what index in pPositions they are referring to
	char cSelectedOrigPosition;						//Variable that the loop will eventually give the orig position of PieceID
	
	
	
	//Loops over every position located by the array at pPositions
	for (nRowIndex_I=0; nRowIndex_I<POS_ARRAY_DIM; nRowIndex_I++)
	{
		for(nColIndex_J=0; nColIndex_J<POS_ARRAY_DIM; nColIndex_J++)
		{
			
			//Assigns the values at the specific coordinate of Row index and Column Index
			cSelectedOrigPosition = *( *(pPositions + nRowIndex_I) + nColIndex_J );
			
			
			//Checks if the iterated coordinates is where the piece ID of the user selected is
			if(cSelectedOrigPosition == cPieceID)
			{			
			
				/* Assigns the variables at pointers of pIndex_Row_I and pIndex_Col_J the values of
				   nRowIndex_I and nColIndex_J. Hence, successfully passing the location/information
				   of the location of a PieceID via Row Index and Column Index.
				*/
				*pIndex_Row_I = nRowIndex_I;		
				*pIndex_Col_J = nColIndex_J;		
				
			}
		
		
		}
	}
}

/* 
	Function checks the correct direction of increment when given who's turn it is. Incrementing by
	is downwards, 0-7. Incrementing by -1 is upwards 7-0
	
	@param bIsWhite is the color of the player's piece at this current turn

	@return constant that determines the direction of forwards. For white pieces, 1 for top to bottom.
			For black pieces, -1 bot to top
*/
int 
directForwards (bool bIsWhite)
{
	int nConstant;
	
	/*Array index of row counts from top to bottom, always starts 0 -7
	  Array index of row counts from bot to top, always starts 7 - 0
	  
	  So their direction considered as forwards can be either adding a positive or +1
	  or via subtraction/adding of a negative number or -1
	*/
	if (bIsWhite)
		nConstant = 1;	//White piece starts top half
	
	else
		nConstant = -1; //Black piece starts bot half
	
	return nConstant;
}

/* 
	Function converts the number piece that the user wants into the Piece ID which is a letter from A-X
	
	Precondition: nPiecenum ranges from values 1-12
	@param	nPieceNum is the number the user picked as input to pick a Piece ID, a letter, of a checker piece to move
	@param bIsWhite is the color of the player's piece at this current turn

	@return a character that should be an ID for a checker piece from one of the letters in A-X
*/
char 
convertToLetter (int nPieceNum, 
			 	 bool bIsWhite)
{
	char cActualPiece;
	
	//White Pieces range
	if (bIsWhite)
	{
		//Converts the inputted number of the user into a identifiable letter in the pPositions array
		
		cActualPiece = nPieceNum + 64; 
									   //NOTE:  Characters 'A' - 'L' or Char Value of 65-76 is White pieces.
		return cActualPiece;
	}
	
	else
	{
		cActualPiece = nPieceNum + 76;	//Converts the inputted number of the user into a identifiable letter in the pPositions array
										//In terms of the array position, Characters 'M' - 'X' or Char value 77-88 is black pieces
		return cActualPiece;
	}
}

/* 
	Function gives the identity range of the enemy of the current player's pieces via selecting the range as IDs 
	from letters A-L as white, M-X as black. The function uses two variables to pass these minimum and maximum values
	
	@param bIsWhite the current color the player is playing
	@param pCharEnemy_Min is the ID letter's number serving as minimum in range 
	@param pCharEnemy_Max is the ID letter's number serving as maximum in range 

*/
void 
findEnemyIdentity (bool bIsWhite, 
				   char *pCharEnemy_Min, 
				   char *pCharEnemy_Max)
{
	
	
	if (bIsWhite)
	{
		*pCharEnemy_Min = 77;			//Sets the minimimum char value of the enemy, this is 'M'
		*pCharEnemy_Max = 88;			//Sets the max char value of the enemy, this is 'X'
	}
	
	else
	{
		*pCharEnemy_Min = 65;			//Sets the minimimum char value of the enemy, this is 'A'
		*pCharEnemy_Max = 76;			//Sets the max char value of the enemy, this is 'L'
	}

}

/* 
	Function gives the identity range of the allies of the current player's pieces via selecting the range as IDs from letter 
	A-L as white, M-X as black. The function uses two variables to pass these minimum and maximum values
	
	@param bIsWhite the current color the player is playing, if its not white then it is black
	@param pCharEnemy_Min is the ID letter's number serving as minimum in range 
	@param pCharEnemy_Max is the ID letter's number serving as maximum in range 
	
*/
void 
findAllyIdentity (bool bIsWhite, 
				  char *pCharAlly_Min, 
				  char *pCharAlly_Max)
{
	if (bIsWhite)
	{
		*pCharAlly_Min = 65;			//Sets the minimimum char value of the enemy, this is 'A'
		*pCharAlly_Max = 76;			//Sets the max char value of the enemy, this is 'L'

	}
	
	else
	{
		*pCharAlly_Min = 77;			//Sets the minimimum char value of the enemy, this is 'M'
		*pCharAlly_Max = 88;			//Sets the max char value of the enemy, this is 'X'
	}
}

/* 
	Function exchanges the position of two elements and exchange their values based on the 2-D array 
	chessboard at pPositions via the the given row index and column index of the two.
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the 3-D chessboard
	@param nOldRow_I is the row index that the element to be exchange with is located
	@param nOldCol_J is the column index that the element to be exchange with is located 
	@param nNewRow_I is the row index that the element will be newly located
	@param nNewCol_J is the column index that the element will be newly located

*/
void 
exchangePositions (char (*pPositions)[8], 
				   int nOldRow_I, 
				   int nOldCol_J, 
				   int nNewRow_I, 
				   int nNewCol_J)
{
	char cTempHolder;																//Character that will store char of the old
	
	
	cTempHolder = *( *(pPositions + nOldRow_I) + nOldCol_J );						//Stores old's char value
	
	*( *(pPositions + nOldRow_I ) + 												//Select row index
					  nOldCol_J ) = *( *( pPositions + nNewRow_I ) + nNewCol_J );	//Select col index to assign old with new char
					  
	*( *( pPositions + nNewRow_I ) + nNewCol_J ) = cTempHolder;						//Assigns new with old
		
}

/* 
	Function finds the position of an enemy given a capture that will be making the enemy to be in the middle of the 
	diagonal of two spaces
	
	Precondition: Captures require two spaces diagonal. Requiring a difference of 2 between nOldRow_I and nNewRow_I, 
				  also a difference of 2 in nOldCol_J and nNewCol_J. All indices value of I and J are 0 - 7
	
	@param nOldRow_I is the old index of the row where the element of a piece ID is
	@param nOldCol_J, is the old index of the column where the element of a piece ID is
	@param nNewRow_I is the new row index that the piece ID will land on after a capture 
	@param nNewCol_J is the new column index that the piece ID will land on after a capture
	@param pNumEnemyRow_I is a pointer that will get row index location of the enemy when the capture type move is made
	@param pNumEnemyCol_J is a pointer that will get column index location of the enemy when the capture type move is made

	@return enemy row index and column index location
*/
void 
findEnemyPosition (int nOldRow_I, 
				   int nOldCol_J, 
				   int nNewRow_I, 
				   int nNewCol_J, 
				   int *pNumEnemyRow_I, 
				   int *pNumEnemyCol_J)
{
	//The average coordinate between the coordinate of old and new positions is always the enemy position
	*pNumEnemyRow_I = (nNewRow_I + nOldRow_I)/2;			
	*pNumEnemyCol_J= (nNewCol_J + nOldCol_J)/2;
}

/* 
	Function captures opponent's pieces by removing their ID and replacing with ' ' (empty space). 
	It would also move the the current player's piece two spaces diagonally with respect to the location 
	of the captured piece.
	
	Precondition: -The location at nNewRow_I and nNewCol_J are valid locations to move based on checkers restrictions 
				   and rules of two spaces diagonal
				  -The location at nNewRow_I and nNewCol_J are locations in pPositions that contain an empty space
				  -cPieceID are a letter ID from A-X.
				  -	nNewRow_I and nNewCol_J are indices from 0 - 7
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified 
					  version of the displayed 3-D chessboard
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param nNewRow_I is the row index that the element will be newly located
	@param nNewCol_J is the column index that the element will be newly located

*/
void 
moveWithCapture (char (*pPositions)[8], 
				 char cPieceID, 
				 int nNewRow_I, 
				 int nNewCol_J)
{


	int nRow_Enemy_I,  nCol_Enemy_J;	//Stores the potential location of enemy to capture
	int nCurrentRow_I, nCurrentCol_J;	//Location indices of the current row index and col index of the piece
	
	//Locates where will the current pieces be located
	findCoordinates(pPositions, cPieceID, &nCurrentRow_I, &nCurrentCol_J);
	
	//Gives the positions of the potential enemy via variables nRow_Enemy_i,  nCol_Enemy_j
	findEnemyPosition(nCurrentRow_I, nCurrentCol_J, 			//Current Position
					  nNewRow_I, nNewCol_J, 					//Target Position
					  &nRow_Enemy_I, &nCol_Enemy_J);			//Enemy in between current and target
	
			

	//Signals captures the enemy by removing it in its position and replacing with just a space
	*( *(pPositions + nRow_Enemy_I) + nCol_Enemy_J) = ' ';
	
	//Makes the positions change and swap their places							
	exchangePositions(pPositions, nCurrentRow_I, nCurrentCol_J, nNewRow_I, nNewCol_J);				


}
/* 
	Function checks opponent's PieceID and landing position of capture in order to find out if capture is possible at those postions
	given that there is enemy in between them diagonally. Gives true when it is able to capture, else gives false.
	
	Precondition: nTargetRowIndex_I and nTargetColIndex_J are indices that ranged from 0 - 7. cPieceID are a letter ID from A-X
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param bIsWhite is the current color the player is playing, if its not white then it is black
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param nTargetRowIndex_I is the row index that the element will be newly located
	@param nTargetColIndex_J is the column index that the element will be newly located

	@return truth value of true if the conditions for a capture at a specific condition is possible, 
			else false for a capture that is not possible
*/

bool 
askIsThere_OneCaptureCondition (char (*pPositions)[8], 
						  		bool bIsWhite, 
						  		char cPieceID, 
						  		int nTargetRowIndex_I, 
						  		int nTargetColIndex_J)
{
	
	int nRowEnemy_I, nColEnemy_J;	 //Enemy location at row index and column index

	int nCurrentRow_I, nCurrentCol_J;//Store the values of the coordinate where the checker piece that the user moved lies
	
	int nForwards;					 //Store what direction considered forwards
	
	
	int distBetween_Row_I;			 //Will store the distance of the capture at at target row index
	int distBetween_Col_J;			 //Will store the distance of the captrue at col at target index
	
	char cEnemy_Min, cEnemy_Max;	 //Range identifier of enemies, A-L(65-76) is white, M-X (77-88) is black
	
	char cSelectedPosition;			 //Position containing the char of where cPiece ID lands
	char cSelectedEnemy;			 //Position containing the char of where cPiece ID's enemy could get captured
	
	
	//Forwards move in terms of capture is two spaces, so the code below will either be 2 or -2
	nForwards = 2 * directForwards(bIsWhite);
	

	
	//Find what enemy letter identifier would it be via a range in either A-L (white) or M-X (black)
	findEnemyIdentity(bIsWhite, &cEnemy_Min, &cEnemy_Max);		
	
	//Finds the coordinates of the piece via finding row index(nCurrent_I) and column index(nCurrent_J)
	findCoordinates(pPositions, cPieceID, &nCurrentRow_I, &nCurrentCol_J);
	
	//Finds the coordinates of enemies via row index (nEnemy_i) and column index (nEnemy_j)
	
	findEnemyPosition(nCurrentRow_I, nCurrentCol_J, 				//Current location of piece
					  nTargetRowIndex_I, nTargetColIndex_J, 		//Target location of landing for capture
					  &nRowEnemy_I, &nColEnemy_J);					//Enemy location during the capture
	
	
	//Checks the distances between the user's selected destination
	distBetween_Row_I = nTargetRowIndex_I - nCurrentRow_I;			//This tracks forward move space count
	distBetween_Col_J = abs(nTargetColIndex_J - nCurrentCol_J); 	//This tracks left/right space count
	
	
	//Performing arithmetic with arrays to access the value at the pointer of the specific position of a certain element in array
	cSelectedPosition = *( *(pPositions + nTargetRowIndex_I) + nTargetColIndex_J );		
	cSelectedEnemy = *( *(pPositions + nRowEnemy_I) + nColEnemy_J );
	
	
	if (cSelectedPosition  == ' '	   &&		//First detects if it is possible to land on the space
		distBetween_Row_I == nForwards &&		//Checks if it is a forward capture, which is either two spaces forwards or backwards
		distBetween_Col_J == 2         &&		//Checks if the capture is two spaces in either left or right
		cSelectedEnemy >= cEnemy_Min   &&		//Secondly, makes sure that the capture is an enemy piece ID via range values
		cSelectedEnemy <= cEnemy_Max )		
			
		return true;
		
	else
		return false;
	
	
}



/* 
	Function checks if there is possibility for capture or continue another capture. These captures are restricted to only detecting forward
	captures
	
	Precondition: cPieceID are a letter ID from A-X
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param bIsWhite is the current color the player is playing, if its not white then it is black

	@return truth value of true if there are possibilities for capture, else returns false if there are none
*/
bool askIsCapturesPossible (char (*pPositions)[8], 
					        char cPieceID, 
					    	bool bIsWhite)

{
	int i; 								//Counter for a for loop
	int nDirection; 					//The variable that helps identify how to count forward depending on which peice's turn

	int nRowCurrent_I, nColCurrent_J;	//Contains the current location index of the Piece ID
	int nRowTarget_I, nColTarget_J;		//Contains the targeted row and columns positions that is possible to land for capture
	int nConditionsPossible = 0;		//Counts all the possible conditions where capture is possible
	
	
						
	bool bIsThereCapture = false;		//Checking for truth value of conditions met

	
	//Finds the perspective of forwards depending who's turn it is
	nDirection = directForwards(bIsWhite);
	
	//Finds the coordinate of the cPieceID via passing value of row index(nCurrent_I) and column index (nCurrent_J)
	findCoordinates(pPositions, cPieceID, &nRowCurrent_I, &nColCurrent_J);
		
		
	//Directs the "forward" location of the piece vertically
	nRowTarget_I = nRowCurrent_I + 2 * nDirection;	
		
	/*Checks each possibility for a capture move forwards it could either
	be from diagonally forward left or diagonally forward right*/
	for (i=0; i<2; i++)
	{
		switch(i)
		{
			case 0:
				
				
				nColTarget_J = nColCurrent_J + 2;		//Directs towards right of the piece horizontally
				
				
				bIsThereCapture = askIsThere_OneCaptureCondition(pPositions, 	//Information of each piece's position
														   		 bIsWhite, 		//Current color of pieces
														   		 cPieceID,		//Piece IC that is checked for capture
														   		 nRowTarget_I, 	//Target location of row index for possible capture
														   		 nColTarget_J);	//Target location of column index for possible capture

				
								
				if (bIsThereCapture)
					nConditionsPossible += 1;			//Counts the condition as true
					
				break;
			case 1:	
				

				nColTarget_J = nColCurrent_J - 2;		//Directs towards left of the piece horizontally
				
				
				bIsThereCapture = askIsThere_OneCaptureCondition(pPositions, 	//Information of each piece's position
														         bIsWhite, 		//Current color of pieces
														         cPieceID,		//Piece IC that is checked for capture
														         nRowTarget_I, 	//Target location of row index for possible capture
														         nColTarget_J);	//Target location of column index for possible capture						

								
				if 	(bIsThereCapture)
					nConditionsPossible += 1;			//Counts the condition as true
					
				break;

					
		}
		
		
	}
	
	//Checks if there is capture
	if (nConditionsPossible >= 1)			
		return true;					
	
	//Returns false if there is no conditions met for capture
	else
		return false;
	
	
	
	
	
}

/* 
	Function checks opponent's PieceID and landing position of capture in order to find out if capture is possible at those postions
	
	Precondition: nTargetColIndex_J and nTargetRowIndex_I are indices that ranged from 0 - 7, chosen by the user. 
				  cPieceID are a letter ID from A-X
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param bIsWhite is the current color the player is playing, if its not white then it is black
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param nTargetColIndex_J is the column index that the element will be newly located
	@param nTargetRowIndex_I is the row index that the element will be newly located


	@return true if the conditions for a capture is possible for that specific piece, else false for a capture that is not possible
*/
bool 
askIsValidCapture (char (*pPositions)[8], 
				   char cPieceID, 
				   bool bIsWhite, 
				   int nTargetColIndex_J, 
				   int nTargetRowIndex_I)
{
						
	bool bIsThereCapture = false;		//Checking for truth value of conditions met

	
	/*Checks wheher the user's entered inputted capture move is correct*/
	bIsThereCapture = askIsThere_OneCaptureCondition(pPositions, 			//Information of each piece's position
											   		 bIsWhite, 				//Current color of pieces
													 cPieceID,				//Piece is that will be checked for capture
											   		 nTargetRowIndex_I, 	//Target location row index for possible capture
													 nTargetColIndex_J);	//Target location column index for possible capture

	
	//Returns true only if there is capture
	if (bIsThereCapture)
		return true;
	else
		return false;
	

	

}

/* 
	Function checks if the piece can still move one space diagonally left or right
	
	Precondition: nRowTarget_I and nCol_Target_J are indices that have a distance of 1 space towards the row and column indices of Piece ID.
				  cPieceID are a letter ID from A-X.
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param bIsWhite is the current color the player is playing, if its not white then it is black
	@param nRowTarget_I is an addend that will yield to a new position at row index for the PieceID
	@param nColTarget_J is an addend that will yield to a new position at column index for the PieceID

	@return passes true if there are possibilities for moving on that specific piece, else returns false if there are none
*/
bool 
checkIsOneMoveFree (char (*pPositions)[8], 
					char cPieceID, 
					bool bIsWhite, 
					int nRowTarget_I, 
					int nColTarget_J)
{
	
	
	int nRowCurrent_I, nColCurrent_J;
	
	//Finds current location of PieceID
	findCoordinates(pPositions, cPieceID, &nRowCurrent_I, &nColCurrent_J);			


	if ( *(  *(pPositions + ( nRowCurrent_I + nRowTarget_I )  ) + (nColCurrent_J + nColTarget_J)  ) == ' ')
		return true;
	else
		return false;
	
	
}


/* 
	Function checks if the current piece being evaluated is blocked and cant capture or move
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param bIsWhite is the current color the player is playing, if its not white then it is black
	@param nRowTarget_I is an addend that will yield to a new position at row index for the PieceID
	@param nColTarget_J is an addend that will yield to a new position at column index for the PieceID

	@return passes true if there are possibilities for moving for that specific piece, else returns false if there are none
*/
bool 
askIsThereBlockage (char (*pPositions)[8], 
				    char cPieceID, 
				    bool bIsWhite)
{
	
	bool bIsThereCapture;			//Stores truth value for possibility of capture
	bool bIsThereMove_OnRight;		//Stores truth value for movement on right
	bool bIsThereMove_OnLeft;		//Stores truth value for movement on left
	
	
	int nForward; 		//What direction of i index considers as forward, 1 means forward to the black pieces, -1 means forward for black pieces
	int nRight = 1;		//Value as means for adding index of array to attain right
	int nLeft = -1;		//Value as means for subtracting index of array to attain left
	

	//Checks for what is the perspective of forwards for the pieces
	nForward = directForwards(bIsWhite);

			

	//Checks for captures, uses the Combo Capture asking functions as it conveniently checks all possible directions of capture
	bIsThereCapture = askIsCapturesPossible(pPositions, cPieceID, bIsWhite);
	
	
	//Checks for possibility of one space movement on the forward right
	bIsThereMove_OnRight = checkIsOneMoveFree(pPositions, cPieceID, bIsWhite, nForward, nRight); 
	
	//Checks for possibility of one space movement on the forward left
	bIsThereMove_OnLeft = checkIsOneMoveFree(pPositions, cPieceID, bIsWhite, nForward, nLeft);
	
	//If there are no captures or movement possible then there is blockage
	if (!bIsThereCapture && !bIsThereMove_OnRight && !bIsThereMove_OnLeft)
		
		return true;
	
	
	//If there are captures or movement possible then there is no blockage
	else
	
		
		return false;
	



	
}




/* 
	This function checks the inputs for 'X', which means surrend, leading to passing the corressponding truth value
	of true if it was indeed just the character 'X' as surrend.
	
	@param cUserInput accepts the character input of the user that may contain 'X'
	
	@return the truth value of the input being a surrender option or not
*/

bool 
askIsSurrender (char cUserInput)
{


	if (cUserInput == 'X'||cUserInput == 'x')
	

		//Surrender input was chosen						

		return true;							
	
	else
	
		//Surrender input was not chosen
		return false;
	
}




/*

	This function moves the player's pieces via changing the index of the piece selected with changing its value
	at the current position as empty and the new position as itself using the passed pointer of the array pPositions.
	Returns true when it moves but false when it cannot for variables to check
	
	Precondition: Given that the response of the user is within A-H for column and 1-8 for row. The row and colunn index
	will accurately always be ranging 0-7

	@param pPositions is pointer to the array that contains info on all positions of existing checker pieces and empty spaces
	@param nColNew_J is the target move position column index that the user wishes to move on
	@param nRowNew_I is the target move position row index that the user wishes to move on
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param bIsWhite boolean that is true if it is white's turn, or false when it is black's turn
	
	@return the truth value of whether it can make the move in alignment of the rules or not
*/
bool 
askIsPieceMoveCorrect (char (*pPositions)[8], 
			           char nColNew_J, 
			           int nRowNew_I, 
			           char cPieceID, 
			           bool bIsWhite)
{
	
	
	int nRowOrig_I, nColOrig_J;			//Saves specific coordinates of the row and column position of the origianl place of piece


	int nRowDistance_I;					//Stores the distances between the i coordinates
	int nColDistance_J;					//Stores the distances between the j coordinates	

	int nCheckForward;					//Checks the board and only allows forward moves given that it is not a capture
	
	char cNewPosition;					//Sets variable to store the target new position via array selection and see if it has space
	
	

									
	/*Returns either 1 or -1. 1 means it goes top to bottom, which is forward for white piece.
	  -1 means it goes from bottom to top, which is forward for black piece*/								
	nCheckForward = directForwards(bIsWhite);
	
	

	/*Loops over the array and finds the Row and Column coordinate of the piece the user wants to move
	Passes the address of pPositions, the checker piece of user and the variables to store the coordinates*/
	findCoordinates(pPositions, cPieceID, &nRowOrig_I, &nColOrig_J);
	
	cNewPosition = (*(*(pPositions+nRowNew_I)+nColNew_J));	//Sets New position
	
	nRowDistance_I = nRowNew_I - nRowOrig_I;		//Difference of distance in the positions at row index
	nColDistance_J = nColNew_J - nColOrig_J;		//Difference of distancce in the positions at column index
	
	
	//check if the move is aligned with rules
	if(nRowDistance_I == nCheckForward && 			 //Check if the movement is one space "forwards"
	  cNewPosition==' ' && 							 //Check if the movement has space to land on
	  (nColDistance_J == 1 || nColDistance_J == -1) )//Checks if it is exactly one space right or left
	
	{
		//Swaps the places of the positions of empty space and PieceID
		exchangePositions(pPositions, nRowOrig_I, nColOrig_J, nRowNew_I, nColNew_J);	
				
		return true;																	

 	}

	//Move is not aligned with rules
	else
	{
		
		return false;
		
		
	}

			
			
	
	
}


/*

	This function finds the pieces ID that are avaiable in the 2-D chessboard pointer and passes the 
	available letters, which are piece IDs, to a seperate array.
	
	@param pPositions is pointer to the array that contains info on all positions of existing checker pieces and empty spaces
	@param pPiecesAvailable_Array is pointer to the array that will contain all pieces that are currently available
	@param bIsWhite boolean that is true if it is white's turn, or false when it is black's turn
	

*/
void 
findPiecesAvailable (char (*pPositions)[8], 
					 char (*pPiecesAvailable_Array), 
					 bool bIsWhite)
{
	
	int a, i, j;									//For loop counters
	int nCounter_For_Piece=0;						//Counts the pieces put and serves as an index to put in the array
	char cSelectedPiece;							//Selection of piece
	char cAlly_Min, cAlly_Max;						//Range of the PieceIDs which are letters that classify as allies

	
	
	/*Checks whos is the current ally by selecting either A-L or M-X
	  and puts their minimum and maximum identities. If it selects A-L
	  then minimum is 65, maximum is 76*/
	findAllyIdentity(bIsWhite, &cAlly_Min, &cAlly_Max); 
	for (a=0; a<12; a++)
	{
		
		//Sets pieces it can't find as null													
		*(pPiecesAvailable_Array+a) = '\0';
		
	}
	
	//Loops through the 2-D checkers board containing piece IDs in finding pieces currently available
	for(i=0; i<POS_ARRAY_DIM ; i++)
	{
		for(j=0; j<POS_ARRAY_DIM ; j++)
		{
			
			//Assign selected piece
			cSelectedPiece = *(*(pPositions + i) + j);
			
			//Checks if the piece is part of being the ally of the current player's pieces
			if (cSelectedPiece >= cAlly_Min && cSelectedPiece <= cAlly_Max )
			{ 
				
				//Assigns a variable to the array that considers the piece as available
				*(pPiecesAvailable_Array + nCounter_For_Piece) = cSelectedPiece;		
				
				//Sets a counter and adds 1 to change position of the index for the next available piece in for loop 
				nCounter_For_Piece +=1;
			}
		
			
		}
	}
	
}



/* 
	This function prompts the user to input a single character to either play, view score, or quit program. It will
	keep prompting until user provides correct input
	
	@param *pChar_UserStartInputs pointer to the array string that will contain input of user

*/
void 
askIsValid_UserStartInput (char *pChar_UserStartInput)
{
	
	int nStringLength;			//Gets the string length or number of characters in the input
	bool isValidInput = false;	//Sets the input as false
	
	//strlen() gets the string input and counts the characters, returns int number of characters
	nStringLength = strlen(pChar_UserStartInput);
	
	//Will keep looping until user provides correct input
	while(!isValidInput)
	{
		printf("Input ('P' - play/ 'S' - view scores/ 'Q'- quit): ");
		scanf(" %s", pChar_UserStartInput);
		
		//Converts lowercase to uppercase In case user got it wrong accidentally
		if (*pChar_UserStartInput > 97)
				
				/* ASCII table value for 'a' is 97
				   ASCII table value for 'A' is 65
				   
				   97-65 = 32
				   
				   So with a difference of 32 from lowercase letters to uppercase 
				   the formula would be that we simply subtract 32
				   
				   cLowerCaseLetter - 32 = cUpperCaseLetter
				*/
				(*pChar_UserStartInput) -= 32; 	
							
		
		
		
		//Checks if the user inputs extra characters
		//strlen(passes the stringlength)
		if (nStringLength > 1)
			printf("ERROR! Your input has extra characters\n");
		
		
		
		//Checks if the user inputs are one of the choices
		else if((*pChar_UserStartInput) == 'P'||
				(*pChar_UserStartInput) == 'S' ||
				(*pChar_UserStartInput) == 'Q')
		
			isValidInput = true;	//Exits the loop
		
		
		//Displays to user that he inputted wrongly
		else
			printf("ERROR! You've inputted a wrong character.\n");
		
		
	}
	
	

}
//



/* 
	This function only checks if the inputted checker piece number is allowed via checking the string input. Also passes
	the integer version of that string number once it considers the string first as correct input
	
	Precondition: nInputLength is always positive or 0
	
	@param cFirstDig is the first digit inputted by the user from left to right
	@param cSecDig is the second digit inputted by the user from left to right
	@param pPieceNum is the pointer to the variable that will contain the integer equivalent of the string input
	@param nInputLength checks the string length of what the user passed
	
	@return true or false to the question of is the checker piece inputted valid
*/
bool 
askIsValid_PieceNum (char cFirstDig, 
					 char cSecDig, 
					 int *pPieceNum, 
					 int nInputLength)
{
	
	
	//First checks if the string input goes above the necessary length
	if (nInputLength>2)
	{				
		printf("Invalid input, your input has extra characters. \n");
		return false;
	}
	
	
	//Checks if the first digit inputted by the user is a number
	if (cFirstDig > 48 && cFirstDig <= 57)
	{	
		
		
		//Checks the input length is just 1 digit, then simply convert it as if it was just one digit
		if (nInputLength == 1)
		{ 	
		
			/*Converts the number character into a number, 
			  so if '1' is 49 then we subtract by 48 to get
			  the number selected as 1
			*/
			*pPieceNum = cFirstDig - 48;
			
			
			//Return true because user did choose correct input			
			return true;
		
		}
		
		
		//Ensures it is only the first digit and the second digit has values between 0-2
		else if(cFirstDig == '1' && cSecDig<=50 && cSecDig>=48)
		{
		
			/*Converts the Ascii value into an integer, two digit between 10 - 12
			  Ex: given "10", the second digit '0' is at ascii value of 48
			  	  Since this is two digits, we must subtract 38 instead of 48
			  	  so 48 - 38 will yield precisely the number 10
			*/			
			*pPieceNum = cSecDig -38;
			
			//Return true because user did choose correct input		
			return true;					
		}
		
		//Catches those digits that have a second digit but the first digit is not 1
		else
										
			return false;
		

	}
	
	//Catches those characters that are not digits
	else
		return false;
	


	
}

/* 
	This function prompts the user to keep choosing the right input by selecting proper formatting (Ex: A1, B8, D6)
	in order to move his selected piece at a new positon. When inputs are valid, passes the integer version 
	of the row number selected and passes just the letter as character. Ex: So B8 would return 'B' as ColChar and
	8 as integer
		
	@param pColChar is the pointer that will get the column letter that the user chooses
	@param pRowNum is the pointer that will get the  row number that the user chooses
	
	@return truth value of the user's input of movement position (meaning if the position was proper format)
*/
bool 
askIsValid_MoveToPos (char *pColChar, 
					  int *pRowNum)
{
	char cUserMoveToPos[50];	//initializes character input of the user
	bool bValidResponse = false;
	
	//This loop will keep happening until user gives sthe right input
	while(!bValidResponse)
	{
		printf("Which place do you want the piece do you want to move? (Ex: A1, B8, D6) \n");
		scanf("%s", cUserMoveToPos);
		
		
		//Check if the repsones is a surrender
		if ((cUserMoveToPos[0] == 'X' || cUserMoveToPos[0] == 'x') && cUserMoveToPos[1] == '\0')
			
			
			//Makes this a valid response
			bValidResponse = true;
		
		

		/*Converts ASCII integer value of char to an integer that starts at 0 instead of 48. Thus, 
		  instead of the character from the string '1' - '8' it now becomes just the integer from 
		  1 - 8 
		  
		  Ex: if user selected G6, the string has '6' which should be an integer value. The ASCII 
		  table of has its integer value as 54, so we subtract awat 48 and get the base integer 
		  value of just 6.
		  */
		*pRowNum = cUserMoveToPos[1] - 48; 	
		
		//Selects the column indicator which would be the letter
		*pColChar = cUserMoveToPos[0];	
											
		

		/*Convert lowercase to uppercase for the user to alleviate some human error
		  -97 is character 'a' while 65 is character 'A'
		  -Making the differnce of jump between integers be 32
		  -Hence, when a lowercase letter is given, we subtract 32
		  
		*/
		if (*pColChar >= 97)
			*pColChar -= 32; 				
		
		
		
		//Catches the wrong inputs and displays and error message
		
		if ( (strlen(cUserMoveToPos)>2 ||			//Checks if the user input has extra characters
			  *pColChar < 65 ||						//Checks if the user input is not within A-H
			  *pColChar > 72 ||
			  *pRowNum > 8 ||						//Checks if the chosen row is not within 1-8
			  *pRowNum < 1 ) &&						
			  !bValidResponse)						//Checks if the response is still inavlid, meaning no surrenders
			
		
		
			printf("ERROR! Invalid input, please do the correct position move format. Between A-H and 1-8 only, no extra chars\n(Ex: A1, B8, D6) \n");
		
		//Catches all the right inputs
		else
		
			//stops the loop of asking the user
			bValidResponse = true;					
			
		
	
		
	}
	
	
	return bValidResponse;
	
	
}

\

/* 
	This function displays who's turn it is and the color of the checker piece they posses 
	
	PreCondtion: There is already an assigned current player of either 'A' or 'B'
		
	@param bIsWhite is a boolean that is true if it is white's turn, or false when it is black's turn
	@param cCurrentPlayer is a character which labels the player that is at current turn
	
*/
void 
displayCurrentColorTurn (bool bIsWhite, 
						 char cCurrentPlayer)
{
	if(bIsWhite)
	
		printf("Player %c's turn: White Pieces\n\n", cCurrentPlayer);
	
	else
	
		printf("Player %c's turn: Black Pieces\n\n", cCurrentPlayer);
	
}

/* 
	This function counts the pieces of each checker piece side
	
	@param pPositions is pointer to the array that contains info on all positions of existing checker pieces and empty spaces		
	@param pScoreBlackPieces is a pointer that will get the count of black pieces
	@param pScoreWhitePieces is a pointer that will get the count of white pieces
	
*/
void 
countBoardPieces (char (*pPositions)[8], 
				  int *pScoreBlackPieces, 
				  int *pScoreWhitePieces)
{
	int i, j;				//Sets counter for the loops
	int nCountBlack = 0;	//Sets the counting of pieces, and set as zero to avoid garbage values
	int nCountWhite = 0;	//Sets the counting of pieces, and set as zero to avoid garbage values
	
	
	char cSelectedPiece;	//The piece ID that is selected in pPostions
	
	char cWhiteMin = 65;	//Sets the char value of 'A' which is 65 as minimum
	char cWhiteMax = 76;	//Sets the char value of 'L' which is 76 as maximum
	char cBlackMin = 77;	//Sets the char value of 'M' which is 77 as minimum
	char cBlackMax = 88;	//Sets the char value of 'X' which is 88 as maximum
	
	
	/*Loops through the array to check each piece IDs and count if they are either
	  black piece or white piece*/
	for (i=0; i<POS_ARRAY_DIM; i++)
	{
		for(j=0; j<POS_ARRAY_DIM; j++)
		{
			
		
			cSelectedPiece = *(*(pPositions+i)+j);
			
			
			//If the piece ID is within the range of white A-L then it it is a white piece
			if(cSelectedPiece >= cWhiteMin && cSelectedPiece <= cWhiteMax)
				nCountWhite += 1;
			
			//If the piece ID is within the range of white A-L then it it is a white piece	
			else if( cSelectedPiece >= cBlackMin && cSelectedPiece <= cBlackMax)		
				nCountBlack += 1;
	
		
		}
		
	}
	
	//Passes the value of the scores respectively to the labels
	*pScoreBlackPieces = nCountBlack;
	*pScoreWhitePieces = nCountWhite;
	
		
}

/* 
	Function checks if the input from asking the combo with multiple landing options is the correct formatting and is a
	part of one of the array. In connection with askDoesUserWantsCombo(). It would then pass the value of the row index 
	and column index that the user wishes to move on to continue combo capture.
	
	@param pUserStringInput is the input of the user they choose between A1, A2,.. A8,... B1, B2..., B8,.. etc.
	@param pNumChoices_Array contain an array that are alowed choices the the user must choose from
	@param pColNum is a pointer that will pass the value of the user's desired column index that the piece he selected will move in
	@param pRowNum is a pointer that will pass the value of the user's desired row index that the piece he selected will move in

	@return true if the format of the input is correct and is equal to one of the choices given as possible landing position of capture
*/
bool 
askIsComboMultipleChoices_CorrectInput (char *pUserStringInput,  
									 	int *pNumChoices_Array, 
									 	int *pColNum, 
									 	int *pRowNum)
{
	
	int i;							//Coutner in for loops
	int nSelectIndex;				//Variable that will store selected row or column index
	
	bool bIsInputCorrect = false;	//By default, the input will always be false until user inputted correct choice
	
	char nChoice_Into_LetterCol;	//Variable that stores the letter equivalent of column index
	char nChoice_Into_CharNumRow;	//Variable that stores the number character equivalent of row index
	
	char cUserSelectedLetter;		//Stores the first element in the array input which should be a letter Ex: "G6" so it stores 'G'
	char cUserSelectedNumber;		//Stores the second element in the array input which should be a letter Ex: "G6" so it stores '6'
	
	
	
	//Displays the choices
	for (i=0; i<5; i++)
	{		
	
		/*The row and column index values will be selected. The pNumChoice_Array contains indices
		  of the row and column by pairs of two so - {col, row, col, row}. Indices only range
		  0 - 7
		*/
		nSelectIndex = *(pNumChoices_Array + i );		
		
		
		/*Since we are dealing with integers, 100 will be considered as the trash value as previously set by
		  askDoesUserWantsCombo()
		*/
		if (  nSelectIndex != 100)			
		{
			
			/*Makes sure it only chooses by pair in terms of modulo 2, this confirms that we
			start at selecting the column index */
			if (i % 2==0)
			{						
				
				
				//Turns column index into a letter, so index 0 would be 0 + 65 which is 'A'
				nChoice_Into_LetterCol =  *(pNumChoices_Array + i) + 65;
				
				
				/* instead of having anoder i%2 == 1, I simply just added 1 to precisley select the row index
				The index id backward numbered in perspective of user, currently it is number 0-7.
				Therefore, we make the 8 - index in order to translate it into the number col perceived by the user
					Ex: If it was row index 0, then it means the user chose the row number 8 via (8 - 0 = 8)
					Ex: If it was row index 7, then it means the user chose the row number 1 via (8 - 7 = 1)
					Ex: If it was row index 2, then it means the user chose the row number 5 via (8 - 2 = 5)


				We add 48 because we are comparing a string input of the user of a number, ASCII table suggest 48 as '0',
				49 as '1', 50 as '2', ... etc.
				*/				
				nChoice_Into_CharNumRow = 8 -  *(pNumChoices_Array + i + 1 ) + 48;		
				
				
				//This simply passes the value at index 0, Ex: so an input of G6 will pass 'G'
				cUserSelectedLetter = *pUserStringInput; 	
				
				
				//This simply passes the value at index 1, Ex: so an input of G6 will pass '6'						
				cUserSelectedNumber = *( pUserStringInput + 1 ); 					
				
				
				
				if (cUserSelectedLetter ==  nChoice_Into_LetterCol 			//Ex: This represents the 'G' in G6
				&& cUserSelectedNumber ==  nChoice_Into_CharNumRow)	//Ex: This represent the '6' is in G6 checking
				{
				
					bIsInputCorrect = true;						//The only way to make input true is make it equal to one of the choices
					*pColNum = *(pNumChoices_Array + i);		//Passes the index of the column (0-7)
					*pRowNum = *(pNumChoices_Array + i + 1); 	//Passess the index of the row (0-7)

				}
				
				

			}
			
		
		}
	}
	
	//Will return false if the user did not choose input correctly
	return bIsInputCorrect;
	
}



/* 
	Function displays to the user that there are two options to land his next capture as it is a combo capture. The function will pass
	the row and column index via pointers when the user chooses an option correctly
	
	Precondition: This function happens given that there is free space (' ') on exactly two capture landing positions. Meaning, it happens
				  when a continued/combo capture is possible to land at two different positions with the given cPieceID of the piece the 
				  user moved. At the meantime, the array pointer, pPositions, have clear indication of enemy and space (' ') at a diagonal 
				  with cPieceID
	
	@param pPositions is a 2-Dimensional array that contains position of the letters that serve as a simplified version of the displayed 3-D chessboard
	@param cPieceID is the letter identifier of the piece that will move in the 2D array
	@param bIsWhite is the current color the player is playing, if its not white then it is black
	@param pBoolIsGameStateOn controls the loop at main() disabling or falsifying it would signify a surrender
	@param pColNum is a pointer that will pass the value of the user's desired column index that the piece he selected will move in
	@param pRowNum is a pointer that will pass the value of the user's desired row index that the piece he selected will move in

*/
bool
askDoesUserWantsCombo (char (*pPositions)[8], 
				   	   char cPieceID, 
				   	   bool bIsWhite,
				   	   bool *pBoolIsGameStateOn,
				   	   int *pColNum, 
				       int *pRowNum)
{

	int i; 								//Counter for a for loop
	int nChoices[5];					//Array that will contain the pairs of index coordinates of positions where multiple landings cna be possible
	int nDirection; 					//The constant that helps identify how to count forward depending on which peice's turn
	
	int nRowCurrent_I, nColCurrent_J;	//Contains the current row index and column index of PieceID
	int nRowTarget_I, nColTarget_J;		//Contains the targeted row and columns positions that is possible to land for capture
	int nRow;							//Will Contain the row index but in terms of numbering from the user's perspect
	
	char cLetterCol;					//Stores column index but in letter form
	char cUserStringInput[20];  		//Input string for the user

	bool bIsCorrectInput = false;		//Store boolean of checking whether user chooses variable correctly
	bool bWantsCombo = false;			//Check if user wants combo, false by default
	bool bIsValidCapture = false;		//Check if it is a valid capture
	
	
	/*Ensures that the forward direction is either +1 going down, or -1 going up the row index of I
	 Returning nDirection of 1 means it is goind downward else it is going upwards (-1). This will serve 
	 as a constant to ensure we multiply the -1 to those going upwards or not*/
	nDirection = directForwards(bIsWhite);
	
	
	//Finds the coordinate of the piece via passing value of row index(nCurrent_I) and column index (nCurrent_J)
	findCoordinates(pPositions, cPieceID, &nRowCurrent_I, &nColCurrent_J);



	/*	Makes sure that all trash value is just 100, so i can easily find the values only 
		from 0-7 which are indexes for column or row that help indicate a potential capture. 
	*/
	for (i=0; i<5; i++)		
		nChoices[i] = 100;
		
	
	
	
	printf("COMBO ALERT! Your combo can continue in the following positions: \n\n");
	
	
	
	
	// TOP/BOT RIGHT BLOCK
	
	/* Given that the precondition to this that there is more than one possible option of landing
	to continue a combo capture, we store in array these positions for the user to chose from them.
	These store the coordinates of the target row index and col index of the potential capture option
	In this case is two boxes above and two boxes to the right is how a capture is identified*/
	nRowTarget_I = nRowCurrent_I + 2 * nDirection;		//"Forwards"
	nColTarget_J = nColCurrent_J + 2;					//Right
	
	
	//Check if the move towards left is a valid capture move
	bIsValidCapture = askIsValidCapture (pPositions, 
										 cPieceID, 
									     bIsWhite, 
										 nColTarget_J, 
										 nRowTarget_I);
	
	//Store it as choice for combo if valid capture move
	if (bIsValidCapture)
	{
	
		/*I did an ordering by twos so if it was 1 % 2, it means 1, in which i'll identify as a Column index.*/
		nChoices[0] = nColTarget_J;						
		
		/*I did an ordering by twos so if it was 0 modulo 2, it means 0, in which i'll identify as a Row index.*/
		nChoices [1] = 	nRowTarget_I;		
	}
	
	
	
	
	// TOP/BOT LEFT BLOCK
	
	/*Stores the coordinates of the target row index and col index of the potential capture option
	In this case is two boxes above and two boxes to left*/		
														//Forwards is already declared above
	nColTarget_J = nColCurrent_J - 2;					//Left

	//Check if the move towards left is a valid capture move
	bIsValidCapture = askIsValidCapture (pPositions, 
										 cPieceID, 
									     bIsWhite, 
										 nColTarget_J, 
										 nRowTarget_I);	
										 
	//Store it as choice for combo if valid capture move
	if(bIsValidCapture)
	{
							
		/*I did an ordering by twos so if it was 2 % 2, it means 0, in which i'll identify as a Column index.*/ 
		nChoices[2] = nColTarget_J ;									
		 
		/*I did an ordering by twos so if it was 3 % 2, it means 1, in which i'll identify as a Row index.*/
		nChoices[3] = nRowTarget_I;
	}

	
					
	//Displays the choices given that the capture leads to two options
	for (i=0; i<5; i++)
	{
	
		//Makes sure it doesn't read a garbage value		
		if (nChoices[i] != 100)
		{
			/*Makes sure it only chooses by pair in terms of modulo 2
			  In this case of the variable 'i' I chose the column index first
			  Row index would mean it will be just right next to it so just add 1
			*/
			if (i%2==0)
			{						
				
				cLetterCol = nChoices[i]+65; 	//Converts it to the correct Letter that identifies the column in order to print it properly
				nRow = 8-nChoices[i+1]; 		//Converts it to the correct orientation of numbering in order to print it properly
				
				//Displays choice
				printf("You can move your piece to \"%c%d\"\n", cLetterCol, nRow);
			}
			
		
		}
		
	}
	
	
	/*Prompts the user to choose which landing position for next capture, does not stop prompting until he chooses correct input 
	  Important to note that bWantsCombo is still false false
	*/
	do{
		printf("\n\nYou can choose to not capture by inputting 'N' \n");
		printf("Select position to move from the given above: ");
		scanf("%s", cUserStringInput);
		
		//Correct input would become true if this was a surrender
		bIsCorrectInput = askIsSurrender(cUserStringInput[0]);
		
		//If surrender did occur then turn off game 
		if (bIsCorrectInput)
		
			*pBoolIsGameStateOn = false;
			
		
		
			
		//Dont continue the combo option
		else if (cUserStringInput[0] == 'N' || cUserStringInput[0] == 'n')
		
			bIsCorrectInput = true;
			//bWantsCombo is false by default so no need for bWantsCombo = false
		
		else
		{
		
			//Checks if he did choose from one of the choices
			bIsCorrectInput = askIsComboMultipleChoices_CorrectInput(cUserStringInput, 	//User's string
																	 nChoices, 			//Available choices of valid target capture landing positions
																	 pColNum, 			//Should contain col index of user, if ever, wants to move in
																	 pRowNum);			//Should contain Row index of user, if ever, wants to move in
																	 
			//Helps signify that the user wants to proceed with another capture for combo
			bWantsCombo = true;
		}
		
		
		
		//Displays he chose wrongly
		if(!bIsCorrectInput)
		{
		
			printf("ERROR! Your input must following the following examples (A6, D5, H4, C8) ");
			printf("and only from the choices displayed above.\n\n");
		}
	}
	while(!bIsCorrectInput);
	
	//bWantsCombo will always still be false unless bWantsCombo = true occured
	return bWantsCombo;
	
}

/* 
	This function prompts the user on which piece he would like to move and perform that move
	
	Precondition: pPositions and pChessboard are already defined characters of Piece ID positions and Characters making a
				  Chessboard respectively
	
	@param bIsWhite is a boolean that is true if it is white's turn, or false when it is black's turn
	@param cCurrentPlayer is the player label at the current turn
	@param pPositions is pointer to the array that contains info on all positions of existing checker pieces and empty spaces	
	@param pChessBoard is the pointer to the 3D chessboard to print the beautfiully designed pieces and board
	@param pBoolIsGameStateOn is the checker's game boolean to control whether or not it should continue true or false.
							  false would return this function back to menu
	
	
*/
void 
selectPieceToMove (bool bIsWhite,
				   char cCurrentPlayer,
				   char (*pPositions)[8],
				   char (*pChessBoard)[10][100],
				   bool *pBoolIsGameStateOn)
{
	
	int a;									//for loop counter
	int nSelectedPieceNumber;				//Stores integer equivalent of string input at cPieceNumber_String
	int nColIndex;							//Target column index will contain the converted letter of user input of cSelectedColChar
	int nRowIndex;							//Target row index will contain the converted number of user input of nSelectedRowNum
	int nBlackPieces;
	int nWhitePieces;						//Counts the board pieces
	
	int nSelectedRowNum;					//Target Row that is the row input of the user
	
	
	char cSelectedColChar;					//Selects the column input of the user which is a letter
	
	char cPieceID;							//Variable that contains the lettter that is a piece ID for pieces at array pPositions
	char cPieceNumber_String[100];			//String to get the input of user
	
	char cAvailablePieceIDs[12];			//Stores all the avilable piece IDs
	
	
	bool bIsValidSelectPiece = false;		//Boolean for storing truth value of valid piece selection
	
	bool bIsValidMove = false;				//Boolean for storing truth value of valid move position
	
	bool bIsValidResponse = false;			//Boolean for storing truth value of valid responses of piece and move position
	
	bool bIsValidCapture = false;			//Boolean stores capture move inputted by the user as valid or not
	
	bool bIsComboWanted = false;			//Check if user wanted to do a combo
	
	bool bIsSurrender = false;				//Boolean for storing truth value of the input to be surrender

	bool bTurnOnLocate = true;				//Boolean for describing the purpose of it being passed
	
	//Checks all available pieces and stores them in an array
	findPiecesAvailable (pPositions, cAvailablePieceIDs, bIsWhite);
	

	/*When the loop exits, the user has given a proper input and the move aligns with the rules.
	  The loop will keep asking the user for proper response inputs and correct movement logic
	  until they input a corerct response and correct move
	  
	  if pBoolIsGameStateOn becomes false it simply means a surrender occured, which stops the loop below
	*/  
	while(!bIsValidMove && *pBoolIsGameStateOn)					
	{			
	
	
		/*START OF CHECKING VALID RESPONSE*/
		/*When the loop finishes, the user has given a valid and proper input of 
		  both chosen piece number and move position*/
		while(!bIsValidResponse)
		{
			
			
			//SELECTION OF PIECE NUMBER
			printf("Which piece do you want to move? Ex: 1,2,3,4, ... 12)\n");
			scanf("%s", cPieceNumber_String);
	
	
			
			bIsValidSelectPiece = askIsValid_PieceNum(cPieceNumber_String[0], 		//The char that could contain the ones digit or tens digit 
													  cPieceNumber_String[1], 		//The char that could contain a ones digit or none
													  &nSelectedPieceNumber,  		//Variable that will contain the integer equivalent of string
													  strlen(cPieceNumber_String) );//String length of input	
		
			
			//Checks if the user only types 'X'	or only one character
			if (strlen(cPieceNumber_String)==1)				
			
			
				/*This checks if the input is 'X' or 'x' even if it just on char
				 If this equates to true then it will exit this loop*/
				bIsSurrender = askIsSurrender(cPieceNumber_String[0]);	
			
			
																						
		
			
			
			
			
			/*When the user selected the surrender option 'X' then consider it as a valid move and response
			  in order to exit this two layered while loop. Game state should end as well, therefore must
			  be set to false*/
			if (bIsSurrender)
			{
				
				bIsValidResponse = true;	//Turns on the valid response to exit this loop
				bIsValidMove = true;		//Turns on the valid move to exit this loop
				*pBoolIsGameStateOn = false;		//Signals the game of checkers to end at main()
				
			}
			else
			{

				
		
				/*Changes the values of the nPieceNum into a letter identifier of the piece
				Identifiers will help locate it in the pPositions array
				Ex: User selects piece 7 and it is a white piece, converting it to a letter identifier within
					the range A-X and be a white piece means we add 64(because white piece). 7 + 64 = 71, 71 
					is equal to 'G'
					
				Ex: User selects piece 7 and it is a black piece, converting it to a letter identifier within
					the range A-X and be a black piece means we add 76 (because black piece). 7 + 76 = 83, 83 
					is equal to 'S'	
				*/				
						
				cPieceID = convertToLetter(nSelectedPieceNumber, bIsWhite); 
				
				
				
				//Checks if the piece the user selected is actually a piece that exists	
				for (a=0; a<12; a++)
				{
					
					//Uses value of piece ID to check if it exists stukk
					if(cPieceID == cAvailablePieceIDs[a])
					{
						a = 12;							//Ends this for loop
						bIsValidSelectPiece = true;
					}
					else
						bIsValidSelectPiece = false;	//Returns false ifthe piece he selected does not exist
				}
			
			
			}
			
			
		
			//Checks if there is no surrender by checking the value of pBoolIsGameStateOn as true, if not then skip code block
			if(*pBoolIsGameStateOn)
			{			
				

				//Checks if the user selected the right piece
				if (bIsValidSelectPiece)
				{
					
					
					/*isValidResponse is the loop of repeatedly prompting the user for the correct number choice of
					 checker piece input, which should be just a number from 1-12 making it true will stop the loop
					 Passes the variables to store the inputted column and row by the user which are the row index
					 and column index the user wishes to go
					 
					 Returns cColChar as a capital letter that indicates user's selected column, and nRow as a 
					 number that start from 1-8 which indicates user's selected row
					 */
					bIsValidResponse = askIsValid_MoveToPos(&cSelectedColChar, &nSelectedRowNum);	
					
						
					/*cColChar should be just the only character as askIsValid_MoveToPos
					  only accepts this as an exception to validating moves*/
					bIsSurrender = askIsSurrender(cSelectedColChar);
						
					
					/*When the user selected the surrender option 'X' then consider it as a valid move and response
					  in order to exit this two layered while loop. Game state should end as well, therefore must
					  be set to false*/
					if (bIsSurrender)
					{
						bIsValidResponse = true;	//Turns on the valid response to exit this loop
						bIsValidMove = true;		//Turns on the valid move to exit this loop
						*pBoolIsGameStateOn = false;		//Signals the game of checkers to end at main()
					}
					
				}
				else
				{
				
					printf("Invalid input, please do the correct piece format of only ");
					printf("inputting number of pieces (1-12) and that they exist on board\n");
				}
				

					
			}
				
		}
		/*END OF CHECKING VALID RESPONSE*/	
		
		/*
		Things to note before moving the pieces function:
		
		Our array index on pPositions at max contains 8 pieces of data per row, and we have a total of 8 rows
		
		The user currently inputted and selected a column from letters A-H
		The user currently inputted and selected a row from (1-8)
		The user currently inputted and selected a piece with a number from 1 - 12, which is now converted to letter equivalent
		
		The array at pPositions can only be moved properly when you specify
		An input of column index that is ranging from 0-7
		An input of the row index that is ranging from 0-7
		An input of the PieceID that is ranging from letters A-X (A-L or 65-76 are white piece, M-X or 77-88 are black pieces).
		
		Thus inputs of column index and row index are needed to be properly converted
		*/

		
		/*This converts the column, which the player wants to move in, to the perspective of the 
		  array index A-H is 65-72, when we subtract 65 to these, the values of the range becomes
		  0-7, which is accurate to the perspective column index of the array at pPositions*/
		nColIndex = cSelectedColChar - 65;			
			
			
									
		/* This converts the perspective of the user's index into the array's perspective at pPositions
		   The user selected from 1-8 but in the the orientation of bottom to top. Our row index is only 0-7
		   top to bottom. So our user's input is in an opposite perception
		   
		   To solve this, we simply make the chosen input of the user as a subtrahend
		   Formula of subtraction: (minuend - subtrahend = difference/index)
		   Ex: If the user chose row 2
		   	   8-2 = 6 
		   	   he meant row index of 6
		   	   
		   Ex: If the user chose row 8
		   	   8-8 = 0 
		   	   he meant row index of 0
		   
		*/							
		nRowIndex = 8-nSelectedRowNum;				
		
		
		/*Does not perform the move check or capture check when the response was a valid surrender hence making		
		  *pBoolIsGameStateOn = false. When it is true it will proceed with regular checking of move and captures
		*/
								
		if (*pBoolIsGameStateOn)
		{
		
		
			/*Passes the character piece it wants to move and return a bool to check if the move was possible
			  Also moves the piece once it deems it as a correct choice of input
			*/
			bIsValidMove = askIsPieceMoveCorrect (pPositions, 				//Array of the checkers board piece ID positions
										          nColIndex, nRowIndex, 	//Target location index of movement
										          cPieceID, 				//The piece ID chosen to move
										          bIsWhite); 				//What color this current turn is
			
			
			//If the piece moved ot user input is a valid move this turn, then there is no need to check if it is a capture							 
			if(!bIsValidMove)
				bIsValidCapture = askIsValidCapture (pPositions, 		//Array of the checkers board piece ID positions
													 cPieceID, 			//Piece ID being moved
													 bIsWhite, 			//Current color of the turn
											         nColIndex, 		//Row index where the user might want to capture
												     nRowIndex);		//Col index where the user might want to capture
		
		}
												     
		//If it is a successful capture it is a valid move, or vice versa
		if(bIsValidCapture)
		
			bIsValidMove = true;

		//Restates the choice he/she had chosen was wrong when it is deemed both not a capture and not a proper move
		else if (!bIsValidCapture && !bIsValidMove)	
			printf("Your move to go %c%d with Piece %d is not allowed, please try a different move\n\n", cSelectedColChar,
																									     nSelectedRowNum, 
																									     nSelectedPieceNumber);								     

			

		//When a valid capture can occur, perform that capture
		if (bIsValidCapture)
		{
		
			//Keeps checking for combo continuations
			while(bIsValidCapture)
			{
			
				moveWithCapture(pPositions, 			//Performs the capture by updating the positions
								cPieceID, 				//Passes the current piece
								nRowIndex, 				//Passes the target row index landing location of the capture	
								nColIndex);				//Passes the target column index landing location of the capture
				
				

				/*Rechecks current location and possibility for next capture given curren
				  Selected Piece ID
				*/
				bIsValidCapture = askIsCapturesPossible(pPositions, cPieceID, bIsWhite);
				

				
				//Given that this is capture we should display that it happened
				if (bIsValidCapture)
				{
					
					
					/*CLEARING AND RESETTING THE BOARD*/
				
					//clears previous printf and prompts
					system("CLS");
					
					//Calling this function again will wipe the board and erase positions last time
					makeBoard(pChessBoard, BOX_HEIGHT, 8*BOX_WIDTH, 8);							
					
					//translates piece positions and displays the board
					displayBoard(pChessBoard, BOX_HEIGHT, 8*BOX_WIDTH, 8, pPositions, bTurnOnLocate, bIsWhite);			
					
					//Counts the pieces of black and white pieces on the board
					countBoardPieces(pPositions, &nBlackPieces, &nWhitePieces);		
					printf("Type only 'X' on any of the prompts below to surrender\n");
					
					
					//Displays who's turn it is
					displayCurrentColorTurn(bIsWhite, cCurrentPlayer);					
					
					//Display the number of black and white pieces
					printf("Black Pieces: %d\n", nBlackPieces);
					printf("White Pieces: %d\n\n", nWhitePieces);
				
					
					bIsComboWanted = askDoesUserWantsCombo (pPositions, 		//Array containing information
					                 				        cPieceID, 			//Givew the checker piece ID which is a letter
									  				 		bIsWhite,			//Pass which piece of color's turn it is
															pBoolIsGameStateOn, //Pass the gamestate to still give user the option to surrender
									   						&nColIndex, 		//Returns the capture landing column index if capture was still possible
									   						&nRowIndex);		//Returns the capture landing row index if capture was still possible
					
					//If combo wasn't requested to be continued then end capturing and continue next turn
					if (!bIsComboWanted)
						bIsValidCapture = false;
				}
				
				//If the surrender changed the value of pBoolIsGameStateOn into false then exit this loop


				
			}

		}
			
		

		/*This condition happens if:
		  -it is not considered a surrender
		  -the response was valid but the move is not valid
		  -The move was invalid
		*/							  
		if(!bIsValidMove)
			
			
			/*Turns On the loop again for prompting the user for new valid moves 
			  because the previous response was not a valid move */
			bIsValidResponse = false; 
		

	}
	
	
}


/* 
	This function displays the word black to signify black pieces
*/
void 
displayBlackWord ()
{
	printf("%s\n", "______   _        ___    _____   _   __");
	printf("%s\n", "| ___ \\ | |      / _ \\  /  __ \\ | | / /");
	printf("%s\n", "| |_/ / | |     / /_\\ \\ | /  \\/ | |/ / ");
	printf("%s\n", "| ___ \\ | |     |  _  | | |     |    \\ ");
	printf("%s\n", "| |_/ / | |____ | | | | | \\__/\\ | |\\  \\");
	printf("%s\n\n", "\\____/  \\_____/ \\_| |_/  \\____/ \\_| \\_/");
	
}
/* 
	This function displays the word white to signify white pieces
*/
void 
displayWhiteWord ()
{
	printf("%s\n", "db   d8b   db db   db d888888b d888888b d88888b ");
	printf("%s\n", "88   I8I   88 88   88   `88'   `~~88~~' 88'    ");
	printf("%s\n", "88   I8I   88 88ooo88    88       88    88ooooo ");
	printf("%s\n", "Y8   I8I   88 88~~~88    88       88    88~~~~~ ");
	printf("%s\n", "`8b d8'8b d8' 88   88   .88.      88    88.     ");
	printf("%s\n\n", " `8b8' `8d8'  YP   YP Y888888P    YP    Y88888P ");

	
}
/* 
	This function displays the word Goodbye to signify termination of program
*/
void 
displayGoodbye ()
{
	
	
	
	printf("%s", "                                                                                                                                                \n");
	printf("%s", "                                                                   ddddddddbbbbbbbb                                                             \n");
	printf("%s", "        GGGGGGGGGGGGG                                              d::::::db::::::b                                                         !!! \n");
	printf("%s", "     GGG::::::::::::G                                              d::::::db::::::b                                                        !!:!!\n");
	printf("%s", "   GG:::::::::::::::G                                              d::::::db::::::b                                                        !:::!\n");
	printf("%s", "  G:::::GGGGGGGG::::G                                              d:::::d  b:::::b                                                        !:::!\n");
	
	printf("%s", " G:::::G       GGGGGG   ooooooooooo      ooooooooooo       ddddddddd:::::d  b:::::bbbbbbbbb yyyyyyy           yyyyyyy eeeeeeeeeeee         !:::!\n");
	printf("%s", "G:::::G               oo:::::::::::oo  oo:::::::::::oo   dd::::::::::::::d  b::::::::::::::bby:::::y         y:::::yee::::::::::::ee       !:::!\n");
	printf("%s", "G:::::G              o:::::::::::::::oo:::::::::::::::o d::::::::::::::::d  b::::::::::::::::by:::::y       y:::::ye::::::eeeee:::::ee     !:::!\n");
	printf("%s", "G:::::G    GGGGGGGGGGo:::::ooooo:::::oo:::::ooooo:::::od:::::::ddddd:::::d  b:::::bbbbb:::::::by:::::y     y:::::ye::::::e     e:::::e     !:::!\n");
	printf("%s", "G:::::G    G::::::::Go::::o     o::::oo::::o     o::::od::::::d    d:::::d  b:::::b    b::::::b y:::::y   y:::::y e:::::::eeeee::::::e     !:::!\n");
	printf("%s", "G:::::G    GGGGG::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b  y:::::y y:::::y  e:::::::::::::::::e      !:::!\n");
	
	printf("%s", "G:::::G        G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b   y:::::y:::::y   e::::::eeeeeeeeeee       !!:!!\n");
	printf("%s", " G:::::G       G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b    y:::::::::y    e:::::::e                 !!! \n");
	printf("%s", "  G:::::GGGGGGGG::::Go:::::ooooo:::::oo:::::ooooo:::::od::::::ddddd::::::dd b:::::bbbbbb::::::b     y:::::::y     e::::::::e                    \n");
	printf("%s", "   GG:::::::::::::::Go:::::::::::::::oo:::::::::::::::o d:::::::::::::::::d b::::::::::::::::b       y:::::y       e::::::::eeeeeeee        !!! \n");
	printf("%s", "     GGG::::::GGG:::G oo:::::::::::oo  oo:::::::::::oo   d:::::::::ddd::::d b:::::::::::::::b       y:::::y         ee:::::::::::::e       !!:!!\n");
	printf("%s", "        GGGGGG   GGGG   ooooooooooo      ooooooooooo      ddddddddd   ddddd bbbbbbbbbbbbbbbb       y:::::y            eeeeeeeeeeeeee        !!! \n");
	
	printf("%s", "                                                                                                  y:::::y                                       \n");
	printf("%s", "                                                                                                 y:::::y                                        \n");
	printf("%s", "                                                                                                y:::::y                                         \n");
	printf("%s", "                                                                                               y:::::y                                          \n");
	printf("%s", "                                                                                              yyyyyyy                                           \n");
}
/* 
	This function displays a medal to present it to the winner 
*/
void 
displayMedal ()
{
	printf("     ");printf("    |@@@@|     |####|\n");
	printf("     ");printf("    |@@@@|     |####|\n");
	printf("     ");printf("    |@@@@|     |####|\n");
	printf("     ");printf("    \\@@@@|     |####/\n");
	printf("     ");printf("     \\@@@|     |###/\n");
	printf("     ");printf("      `@@|_____|##'\n");
	printf("     ");printf("           (O)\n");
	printf("     ");printf("        .-'''''-.\n");
	printf("     ");printf("      .'  * * *  `.\n");
	printf("     ");printf("     :  *       *  :\n");
	printf("     ");printf("    : ~ A S C I I ~ :\n");
	printf("     ");printf("    : ~ A W A R D ~ :\n");
	printf("     ");printf("jgs   `.  * * *  .'\n");
	printf("     ");printf("        `-.....-'\n");
}
/* 
	This function displays the welcome page of checkers, along with labels play viewm scores, and quit
*/
void 
displayWelcomePage ()
{
	
	//Opening Title
	//DISPLAY "Welcome To"
	printf("%4s", " ");			//Adding four spaces to the left
	printf("                                 ,,                                                                           \n");
	printf("%4s", " ");
	printf("`7MMF'     A     `7MF'         `7MM                                                    MMP\"\"MM\"\"YMM           \n");
	printf("%4s", " ");
	printf("  `MA     ,MA     ,V             MM                                                    P'   MM   `7           \n");
	printf("%4s", " ");
	printf("   VM:   ,VVM:   ,V    .gP\"Ya    MM   ,p6\"bo   ,pW\"Wq.  `7MMpMMMb.pMMMb.   .gP\"Ya           MM       ,pW\"Wq.  \n");
	printf("%4s", " ");
	printf("    MM.  M' MM.  M'   ,M'   Yb   MM  6M'  OO  6W'   `Wb   MM    MM    MM  ,M'   Yb          MM      6W'   `Wb \n");
	printf("%4s", " ");
	printf("    `MM A'  `MM A'    8M\"\"\"\"\"\"   MM  8M       8M     M8   MM    MM    MM  8M\"\"\"\"\"\"          MM      8M     M8 \n");
	printf("%4s", " ");
	printf("     :MM;    :MM;     YM.    ,   MM  YM.    , YA.   ,A9   MM    MM    MM  YM.    ,          MM      YA.   ,A9 \n");
	printf("%4s", " ");
	printf("      VF      VF       `Mbmmd' .JMML. YMbmd'   `Ybmd9'  .JMML  JMML  JMML. `Mbmmd'        .JMML.     `Ybmd9'  \n");
	
	printf("\n\n");
	//DISPLAY "CHECKERS"
	printf("%14s", " ");	
	printf(" .d8888b.  888    888 8888888888  .d8888b.  888    d8P  8888888888 8888888b.   .d8888b.  \n");
	printf("%14s", " ");
	printf("d88P  Y88b 888    888 888        d88P  Y88b 888   d8P   888        888   Y88b d88P  Y88b \n");
	printf("%14s", " ");
	printf("888    888 888    888 888        888    888 888  d8P    888        888    888 Y88b.      \n");
	printf("%14s", " ");
	printf("888        8888888888 8888888    888        888d88K     8888888    888   d88P  \"Y888b.   \n");
	printf("%14s", " ");
	printf("888        888    888 888        888        8888888b    888        8888888P\"      \"Y88b. \n");	
	printf("%14s", " ");
	printf("888    888 888    888 888        888    888 888  Y88b   888        888 T88b         \"888\n");
	printf("%14s", " ");
	printf("Y88b  d88P 888    888 888        Y88b  d88P 888   Y88b  888        888  T88b  Y88b  d88P\n");
	printf("%14s", " ");
	printf(" \"Y8888P\"  888    888 8888888888  \"Y8888P\"  888    Y88b 8888888888 888   T88b  \"Y8888P\"  \n");
	printf("%14s", " ");
	
	printf("\n\n");
	//DISPLAY "PLAY"

	printf("%70s", " ,_ ,  _     ,  ,\n");
	printf("%70s", " |_)| '|\\    \\_/ \n");
	printf("%70s", "'| '|__|-\\  , /` \n");
	printf("%70s", " '    ''  `(_/   \n");
	
	
	//DISPLAY "View Scores"
	printf("%82s", ",   ,___,  _,,  ,    _,  _, _, ,_   _, _, \n");
	printf("%82s", "\\  /' |   /_,| ,|   (_, /  / \\,|_) /_,(_, \n");
	printf("%82s", " \\/` _|_,'\\_ |/\\|    _)'\\_'\\_/'| \\'\\_  _) \n");
	printf("%82s", " '  '       `'  `   '     `'   '  `  `'   \n");
	
	
	//DISPLAY "Quit"
	printf("%71s", "  _, ,  , ___,___, \n");
	printf("%71s", " / \\,|  |' | ' |   \n");
	printf("%71s", "'\\_X'\\__| _|_, |   \n");
	printf("%71s", "    `   `'     '   \n");
	
	printf("\n\n");
}

/* 
	This function states which PLayer and their color as white pieces that won in that particular game round
	and add a point to the score of the winning player
	
	Precondition: cCurrentPlayer is only either 'A' or 'B'
	@param cCurrentPlayer is the letter label of player that won that turn given the winning condition
	@param pPlayerA_Score is a pointer to the address that potentially gets PLayer A's score added by 1
	@param pPlayerB_Score is a pointer to the address that potentially gets PLayer B's score added by 1
*/
void 
displayWhitePieceWins (char cCurrentPlayer, 
					   int *pPlayerA_Score, 
					   int *pPlayerB_Score)
{
	
	char cPlayerAgainst;			//Stores the opponent's label
	char cUserInputAwait[50];		//String that wont necessarily be needed to be used, just somewheere to put user input
	displayMedal();
	
	
	//Identifies the label of players
	
	//If the current player's label is 'B' then he is against 'A'
	if (cCurrentPlayer == 'A')
	{
		cPlayerAgainst = 'B';
		*pPlayerA_Score += 1;
	}
	
	//If the current player's label is 'A' then he is against 'B'
	else if (cCurrentPlayer == 'B')
	{
		cPlayerAgainst = 'A';
		*pPlayerB_Score += 1;
	}
	
	printf("Player %c: White Piece, YOU HAVE WON!\n\n\n", cCurrentPlayer);
	printf("Player %c: Black Piece You have lost...\n\n", cPlayerAgainst);

		
	//Pause prompt for user to see the board and see the result of who won and lost	
	printf("Enter any key to continue: \n");
	scanf("%s", cUserInputAwait);
	
	//Clears program to congratulate player
	system("CLS");
	printf("\n\nCongratulations to holder of black piece, Player %c! \n\n\n\n\n", cCurrentPlayer);

}
/* 
	This function states which PLayer and their color as black pieces that won in that particular game round
	and add a point to the score of the winning player label
	
	Precondition: cCurrentPlayer is only either 'A' or 'B'
	@param cCurrentPlayer is the letter label of player that won that turn given the winning condition
	@param pPlayerA_Score is a pointer to the address that potentially gets PLayer A's score added by 1
	@param pPlayerB_Score is a pointer to the address that potentially gets PLayer B's score added by 1
*/
void 
displayBlackPieceWins (char cCurrentPlayer, 
					   int *pPlayerA_Score, 
					   int *pPlayerB_Score)
{
	
	char cPlayerAgainst;
	char cUserInputAwait[50];		//String that wont necessarily be needed to be used, just somewheere to put user input
	displayMedal();
	
	//Identifies the label of players
	//If the current player's label is 'B' then he is against 'A'
	if (cCurrentPlayer == 'A')
	{
		cPlayerAgainst = 'B';
		*pPlayerA_Score += 1;
	}
	
	//If the current player's label is 'A' then he is against 'B'
	else if (cCurrentPlayer == 'B')
	{
		cPlayerAgainst = 'A';
		*pPlayerB_Score += 1;
	}
	
	//Pause prompt for user to see the board and see the result of who won and lost	
	printf("Player %c: Black Piece, YOU HAVE WON!\n\n\n", cCurrentPlayer);
	printf("Player %c: White Piece You have lost...\n\n", cPlayerAgainst);

	
	//Pause prompt to continue
	printf("Enter any key to continue: \n");
	scanf("%s", cUserInputAwait);
	
	//Clears program to congratulate player
	system("CLS");
	printf("\n\nCongratulations to holder of black piece, Player %c! \n\n\n\n\n", cCurrentPlayer);

	
}

/* 
	This function states which PLayer and their color as black pieces that won in that particular game round
	and add a point to the score of the winning player label
	
	Precondition: cCurrentPlayer is only either 'A' or 'B'
	@param cCurrentPlayer is the letter label of player that won that turn given the winning condition
	@param pPlayerA_Score is a pointer to the address that potentially gets PLayer A's score added by 1
	@param pPlayerB_Score is a pointer to the address that potentially gets PLayer B's score added by 1
*/
void 
raiseSurrender (char cCurrentPlayer, 
				int *pPlayerA_Score, 
				int *pPlayerB_Score)
{
				   	
	
	//Display Surrender Flag
	printf(" _    _.--.____.--._\n");
	printf("( )=.-\":;:;:;;':;:;:;\"-._\n");
	printf(" \\\\\\:;:;:;:;:;;:;::;:;:;:\\\n");
	printf("  \\\\\\:;:;:;:;:;;:;:;:;:;:;\\\n");
	printf("   \\\\\\:;::;:;:;:;:;::;:;:;:\\\n");
	printf("    \\\\\\:;:;:;:;:;;:;::;:;:;:\\\n");
	printf("     \\\\\\:;::;:;:;:;:;::;:;:;:\\\n");
	printf("      \\\\\\;;:;:_:--:_:_:--:_;:;\\\n");
	printf("       \\\\\\_.-\"             \"-._\\\n");
	printf("        \\\\\n");
	printf("         \\\\\n");
	printf("          \\\\\n");
	printf("           \\\\\n");
	printf("            \\\\\n");
	printf("             \\\\\n");
	
	/*When the player that surrendered was 'A' then 'B' is the winner
	  so increase his points
	*/
	if (cCurrentPlayer == 'A')
		*pPlayerB_Score += 1;

	/*When the player that surrendered was 'B' then 'A' is the winner
	  so increase his points
	*/
	else
		*pPlayerA_Score += 1;
	
}
/* 
	This function checks if the current player reaches the win condition of either being at the last row at 
	opponent's side, blocking all opponent's piece, or capturing all their pieces
	
	@param bIsWhite accepts the boolean of who's turn it is, whether it is white or not white's (black) turn
	@param pPositions accepts the 2D checker board array that contains the info of positions of the piece IDs
	@param pBoolIsAtLastRow is a pointer that will get the truth value of condition when player's piece being at last row
	@param pBoolIsOpponentBlocked is a pointer that will get the truth value of condition when player's opponent pieces are blocked
	@param pBoolIsCapturedAll is a pointer that will get the truth value of condition when player captures all opponent's pieces
	
	@return the truth value that there is a winner if one of the winning conditions are met, else false
*/
bool 
askIsThereWinner (bool bIsWhite, 
				  char (*pPositions)[8], 	
				  bool *pBoolIsAtLastRow, 
				  bool *pBoolIsOpponentBlocked, 
				  bool *pBoolIsCapturedAll)
{


	int a, j;							//For loop counters
	int nRowSelect;						//Chooses the row and a counter for the column
	int nColSelect;						//Chooses the column
	
	int nBlackPieces;					//Count of black pieces
	int nWhitePieces;					//Count of white pieces
	
	int nWinningPosition;				//The location at the row end perspective of the player is the winning position
	
	char cAlly_Min, cAlly_Max;			//Range of ally pieces of current player


	char cSelectedPiece;				//Stores the selected piece in the for loop
	char cAvailablePieces_Opponent[12];	//Array that will contain available pieces that the opponent has
	
	bool isAtLastRow =false;			//Default value of of false for condition of a piece being at last row
	bool isBlocked =false;				//Default value of false for condition of an opponent's piece being blocked
	bool isCapturedAll = false;			//Default value of false for condition of an opponent's piece all being captured

	
	/*Checks whos is the current ally by selecting either A-L or M-X
	  and puts their minimum and maximum identities. If it selects A-L
	  then minimum is 65, maximum is 76*/
	findAllyIdentity(bIsWhite, &cAlly_Min, &cAlly_Max); 
													
												
	
	
	/*Gives back an array of pieces that the cuurent player's opponent currently has
	  Sets a null default value for captured pieces or not present pieces*/	
	findPiecesAvailable(pPositions, cAvailablePieces_Opponent, !bIsWhite);	
	
	
	
	//Check if a piece reaches the last row
	
	//Assign what means as a last row
	if (bIsWhite)								
		nWinningPosition = 7;		//index of end row that white pieces need to reach						
	
	else
		nWinningPosition = 0;		//index of end row that black pieces need to reach
	
	
	//Describes what the winning poisition index selects
	nRowSelect = nWinningPosition;
	
	
	//Loops through the positions array
	for(j=0;j<POS_ARRAY_DIM ;j++)
	{
		//Describes what j selects
		nColSelect = j;
		
		//Selects the position and checks if there are any letter in the position
		cSelectedPiece = *( *(pPositions + nRowSelect) + nColSelect);
		
		//Checks if current player's pieces are in the last end row in their perspective
		if(cSelectedPiece >= cAlly_Min && cSelectedPiece <= cAlly_Max)
		{		
			isAtLastRow = true;
			*pBoolIsAtLastRow = true;  //passes the truth value of the win condition of being in last row for main()
		}
	
	}
		
	

	
	//Counts how many pieces of each player's are on the board
 	countBoardPieces(pPositions, &nBlackPieces, &nWhitePieces);				
 	
	 //Check if the user has capture all pieces
	 
	 //Did all black pieces get captured
	 if(nBlackPieces== 0)
	 {
 		isCapturedAll = true;
 		*pBoolIsCapturedAll = true;		//passes the truth value of the win condition of pieces of opponent all captured for main()
 		
	 }
	 
	 //Did all white pieces get captured
	 else if (nWhitePieces == 0)
	 {
	 	isCapturedAll = true;
	 	*pBoolIsCapturedAll = true;		//passes the truth value of the win condition of pieces of opponent all captured for main()
	 }
 	
 	
 	
 	
	//Check if user's opponent can't move anymore
	for(a=0;a<12;a++)
	{


		cSelectedPiece = cAvailablePieces_Opponent[a];

		//Catches away garbage value
		if (cSelectedPiece != '\0')
		{
		
			/*Color is opposite as to means of only looking at the enemy side for blockage.
			  If a piece was blocked, this would pass true*/										
			isBlocked = askIsThereBlockage(pPositions, 				//The 2D array containing info on positions of Piece IDs
										   cSelectedPiece, 			//The piece that is selected in this for loop
										   !bIsWhite);				//The opposite color which is the opponent
										 
										 
			*pBoolIsOpponentBlocked = isBlocked;								//passes the truth value of the existence of blockage on that piece for main()
			
			
			//If there is no blockage on at least one piece then exit this
			if(!isBlocked)
			
				//Value ends this for loop due to truth value of 12<12										
				a=12;												
		}
		
			
	}
	
	
	//Check if one of the win conditions are met
	if(isBlocked || isCapturedAll||isAtLastRow )	
		return true;								//Stops the game
	
	else
		return false;								//Continue the game
	
}
/* 
	This function congratulates the winning player via ASCII art, depending on who the player is
	
	Precondition: cPlayer is only either 'A' or 'B'
	@param cPlayer is the letter label of player that won that turn given the rules in winning condition

*/
void 
displayCongratulations (char cPlayer)
{
	
	if (cPlayer == 'A')
	{
		printf("%s\n", "   ____   U  ___ u  _   _     ____     ____        _       _____   ____     ");
		printf("%s\n", "U /\"___|   \\/\"_ \\/ | \\ |\"| U /\"___|uU |  _\"\\ u U  /\"\\  u  |_ \" _| / __\"| u  ");
		printf("%s\n", "\\| | u     | | | |<|  \\| |>\\| |  _ / \\| |_) |/  \\/ _ \\/     | |  <\\___ \\/   ");
		printf("%s\n", " | |/__.-,_| |_| |U| |\\  |u | |_| |   |  _ <    / ___ \\    /| |\\  u___) |   ");
		printf("%s\n", "  \\____|\\_)-\\___/  |_| \\_|   \\____|   |_| \\_\\  /_/   \\_\\  u |_|U  |____/>>  ");
		printf("%s\n", " _// \\\\      \\\\    ||   \\\\,-._)(|_    //   \\\\_  \\\\    >>  _// \\\\_  )(  (__) ");
		printf("%s\n\n", "(__)(__)    (__)   (_\")  (_/(__)__)  (__)  (__)(__)  (__)(__) (__)(__)      ");
		
		printf("%s\n", "  ____      _         _      __   __U _____ u   ____            _           ");
		printf("%s\n", "U|  _\"\\ u  |\"|    U  /\"\\  u  \\ \\ / /\\| ___\"|/U |  _\"\\ u     U  /\"\\  u       ");
		printf("%s\n", "\\| |_) |/U | | u   \\/ _ \\/    \\ V /  |  _|\"   \\| |_) |/      \\/ _ \\/        ");
		printf("%s\n", " |  __/   \\| |/__  / ___ \\   U_|\"|_u | |___    |  _ <        / ___ \\        ");
		printf("%s\n", " |_|       |_____|/_/   \\_\\    |_|   |_____|   |_| \\_\\      /_/   \\_\\       ");
		printf("%s\n", " ||>>_     //  \\\\  \\\\    >>.-,//|(_  <<   >>   //   \\\\_      \\\\    >>       ");
		printf("%s\n\n\n", "(__)__)   (_\")(\"_)(__)  (__)\\_) (__)(__) (__) (__)  (__)    (__)  (__)      ");
		
		
	}
	else if (cPlayer == 'B')
	{
		printf("%s\n", "   ____   U  ___ u  _   _     ____     ____        _       _____   ____     ");
		printf("%s\n", "U /\"___|   \\/\"_ \\/ | \\ |\"| U /\"___|uU |  _\"\\ u U  /\"\\  u  |_ \" _| / __\"| u  ");
		printf("%s\n", "\\| | u     | | | |<|  \\| |>\\| |  _ / \\| |_) |/  \\/ _ \\/     | |  <\\___ \\/   ");
		printf("%s\n", " | |/__.-,_| |_| |U| |\\  |u | |_| |   |  _ <    / ___ \\    /| |\\  u___) |   ");
		printf("%s\n", "  \\____|\\_)-\\___/  |_| \\_|   \\____|   |_| \\_\\  /_/   \\_\\  u |_|U  |____/>>  ");
		printf("%s\n", " _// \\\\      \\\\    ||   \\\\,-._)(|_    //   \\\\_  \\\\    >>  _// \\\\_  )(  (__) ");
		printf("%s\n\n", "(__)(__)    (__)   (_\")  (_/(__)__)  (__)  (__)(__)  (__)(__) (__)(__)      ");
		
		printf("%s\n", "  ____      _         _      __   __U _____ u   ____           ____         ");
		printf("%s\n", "U|  _\"\\ u  |\"|    U  /\"\\  u  \\ \\ / /\\| ___\"|/U |  _\"\\ u     U | __\")u       ");
		printf("%s\n", "\\| |_) |/U | | u   \\/ _ \\/    \\ V /  |  _|\"   \\| |_) |/      \\|  _ \\/       ");
		printf("%s\n", " |  __/   \\| |/__  / ___ \\   U_|\"|_u | |___    |  _ <         | |_) |       ");
		printf("%s\n", " |_|       |_____|/_/   \\_\\    |_|   |_____|   |_| \\_\\        |____/        ");
		printf("%s\n", " ||>>_     //  \\\\  \\\\    >>.-,//|(_  <<   >>   //   \\\\_      _|| \\\\_        ");
		printf("%s\n\n\n", "(__)__)   (_\")(\"_)(__)  (__)\\_) (__)(__) (__) (__)  (__)    (__) (__)       ");
	}
	
	
}
/* 
	This function displays rules to state what are allowed and what game logic the checkers folows
	
*/
void 
displayRules ()
{
	char cUserInputAwait[50];		//String that wont necessarily be needed to be used, just somewheere to put user input

	system("CLS");	
	printf("%s\n", "  ____        _           ");
	printf("%s\n", " |  _ \\ _   _| | ___  ___ ");
	printf("%s\n", " | |_) | | | | |/ _ \\/ __|");
	printf("%s\n", " |  _ <| |_| | |  __/\\__ \\");
	printf("%s\n\n\n", " |_| \\_\\\\__,_|_|\\___||___/");
	
	printf("1.) Black pieces always go first in a round.\n\n");
	
	printf("2.) Decide which among you would be player A and B.\n\n");
	
	printf("3.) Each turn you have to perform either one move or capture/s (each are checked if valid).\n\n");

	printf("4.) Moves are only limited to forward moves with one square diagonal.\n\n");
	
	printf("5.) Captures can only go to two squares diagonal.\n\n");
	
	printf("6.) Captures can only occur forwards.\n\n");
	
	printf("7.) After doing a capture move, you can do a combo capture if conditions deems so. You can also choose not to ('N')\n\n");
	
	printf("8.) Players will swap their pieces colors once every game continues (i.e. game ends, input 'Y') \n\n");
	
	printf("9.) Everytime you play ('P') from the main menu the colors assigned to your player labels are random \n\n");
	
	
	printf("WINNING CONDITIONS: \n\n");
	
	printf("1.) A player wins when the opposing player's pieces are all captured.\n\n");
	
	printf("2.) A player wins when the opposing player's pieces are all blocked, making him unable to move.\n\n");
	
	printf("3.) A player wins when his piece reaches the last row or the opponent's first row (Anywhere in row 8).\n\n");
	
	printf("Enter any key to continue: \n");
	scanf("%s", cUserInputAwait);
}


/* 
	This function displays the initialized color ownership dictated at the start of a game
	
	@param cBlackPlayer player label letter of the black player
	@param cWhitePlayer player label letter of the white player
	
*/
void 
displayColorOwnership (char cBlackPlayer, 
					   char cWhitePlayer)
{
	
	char cUnusedString[30];					//String that will help create a pause moment in the program via scanf()
	
	
	//Clear previous prompt and printf
	system("CLS");
	
	//Display who is white and black players
	printf("\nPlayer %c: White Piece Player\n\n", cWhitePlayer);
	displayWhiteWord();
	printf("\nPlayer %c: Black Piece Player\n\n", cBlackPlayer);
	displayBlackWord();
	
	//Display who receives first turn
	printf("\nPlayer %c shall receive first turn this game\n\n", cBlackPlayer);
	
	//Pause moment and awaiting for player to understand what happened on screen
	printf("Enter any key to continue: \n");
	scanf("%s", cUnusedString);
}


/* 
	This function swaps the sides of the player via swapping the values of their letter labels from each other
	
	@param pBlackPlayerChar pointer to the variable containing player label letter of the black player
	@param pWhitePlayerChar pointer to the variable containing player label letter of the white player
	
*/
void 
swapPlayerSides (char *pBlackPlayerChar, 
				 char *pWhitePlayerChar)
{
	
	char cTemp;							//Temporarily store value of one player

	
	
	cTemp = *pBlackPlayerChar;				//Temporarily store char label value of black player
	*pBlackPlayerChar = *pWhitePlayerChar;	//Original black player is now a white player
	*pWhitePlayerChar = cTemp;				//White Player is now the black player
	
	
}


int main()
{

	

	bool bIsWhite = false;					//Default first turn is black, hence it is bIsWhite = false
	bool bIsGameStateOn = false;			//Checker Game section starts or ends, for now false means its off

	bool bTurnOnLocate = true;				//Bool that will explain its purpose for passing, which is turning on locator
	bool bTurnOffLocate = false;			//Bool that will explain its purpose for passing, which is turning off locator
	
	
	bool bIsThereWinner = false;			//Stores truth value on checking if there is a winner already after a player's move or capture
	
	bool bIsAtLastRow =false;				//Win condition of being at the end row of the opponent's side
	bool bIsOpponentBlocked =false;			//Win condition of blocking the moves of opponent 
	bool bIsCapturedAll = false;			//Win Condition of capturing all opponent's pieces

	
	bool bIsExitGame = false;				//Bool that controls whether the user wants to exit the game/ application

	
	int nBlackPieces = 0;					//Number of how many black pieces are present
	int nWhitePieces = 0;					//Number of how many white pieces are present
	int nRandomNumber;						//Variable that will store the random number generated
	
	int nPlayerB_GamesWon = 0;				//Score of Player B throughout program runtime
	int nPlayerA_GamesWon = 0;				//Score of Player A throughout program runtime
	
	//CHESSBOARDS
	/*A skeletal 2D chessboard with simpler programming logic, serves to
	 store pieces with IDs that are letters which are called PieceIDs. 
	 IDs can range from A-X. Totals at 24 pieces*/
	char cPiecePosInfo[8][8];
				
	//Array that will store bigger chessboard with more designs
	char cChessBoardDesign[8][10][100];	
	
	
	//INPUTS	
	char cUserStartInput[100]; 		//The starting input of the user, made it into the array to take into account if user typed an extra character
	char cUserContinuePlaying[50];	//Just a prompt for user to type on
	char cUnusedString[100];		//String that serves as only a halt or pause portion of the program via scanf()
	
	
	//PLAYER
	char cBlackPlayer = 'A';	//Initially player A would be black player
	char cWhitePlayer = 'B';	//Initially player B would be white player
	char cCurrentPlayer = ' '; 	//Will store the values of which player's turn it is, initially contains space
	

	
	/*MAIN PROGRAM LOOP, controlled by bIsGameStateOn, when true will go to checker board
	but when exit game is true, will exit this program*/
	while (!bIsGameStateOn && !bIsExitGame)
	{
		
		//Erases all prompts
		system("CLS");																				
		
		//Makes only an array chessboard
		makeBoard(cChessBoardDesign,			//A 3D arrray
				  BOX_HEIGHT, 					//The height of each boxes that is measured by character which is 4 here
				  8*BOX_WIDTH, 					//Box width serves as the number of columns 8*8 means 64 total
				  8); 							//Number of rows in a checkers board is always 8
		
		
		//Displays an array of chessboard but does not locate pieces
		displayBoard(cChessBoardDesign, BOX_HEIGHT, 8*BOX_WIDTH, 8, 
					 cPiecePosInfo, 			//Array that for now has no PieceIDs located
					 bTurnOffLocate, 			//Location of these Piece IDs translated on the board will note happen
					 bIsWhite);					//Passes the colore of the current player
		
		
		
		//Sets up the positions of the checker pieces in a skeletal board
		initPositions(cPiecePosInfo, 			//Array that will now have Piece IDs at positions in alignment to game of checkers
					  8, 8);					//A checkers game is 8 x 8 grid styles hence this 2D array
																	
		
		//ASCII Art welcome page
		displayWelcomePage();
		
		
		//Prompts user to play, view score, or quit
		askIsValid_UserStartInput(cUserStartInput);											
		
		//Checks the first input if it is P, S or Q	
		switch(cUserStartInput[0])
		{	
		
			case 'P':
				
				bIsGameStateOn = true;						//Starts the checkers game
				bIsWhite = false;							//Makes sure we always start black pieces, when this is called
				displayRules();								//displays what condition this checkers game is playing at
				
				
				
				/*RANDOMIZES WHO GETS BLACK PIECES AND BLAC PIECES*/
				
				srand(time(NULL));							//Sets the seed of calling a random number based on time parameters of NULL, making it pass only seconds
				
				nRandomNumber = rand();						//Calls a random number which performs a series of 'random' operations based on seed
				
				//Makes the random number only positive
				if(nRandomNumber < 0)						
					nRandomNumber*= -1;
				
				
				/*It will only swap the player's default values of which color of side they will have if 
				  the random number is divisible by 2
				*/									
				if(nRandomNumber%2==1)						
					
					//Swaps the default values previously initialized
					swapPlayerSides(&cBlackPlayer, &cWhitePlayer);
				
				//Displays in ascii art style who owns which pieces
				displayColorOwnership(cBlackPlayer, cWhitePlayer);				

				
				//The first current player will always be the Black Player
				cCurrentPlayer = cBlackPlayer; 							
				
				
				system("CLS");
				break;
			case 'S':
				system("CLS");
				
				//reminder for no games have been played
				if (nPlayerB_GamesWon == 0 && nPlayerA_GamesWon == 0)
					printf("No records of gameplay yet\n\n");

				
				
				//Drawing box and displaying score
				printf("_________________\n");
				
				printf("|");
				printf("Scoreboard");		
				printf("\t|\n");
				printf("|_______________|\n");
				
				printf("|");
				printf(" Player A: %d", nPlayerA_GamesWon);		//Display score of player A
				printf("\t|\n");
				printf("|");
				
				
				printf(" Player B: %d", nPlayerB_GamesWon);		//Display score of player B
				printf("\t|\n");
				printf("|_______________|\n\n");
				
				
				//Pause moment of the program to make viewer have time to view score
				printf("Enter any key to go back to home screen:\n");
				scanf("%s", cUnusedString);
				break;
			case 'Q':
				
				//Displays terminating message of goodbye
				system("CLS");
				//ASCII Art of Goodbye
				displayGoodbye();
				
				//Exit Game boolean when true will exit this while loop
				bIsExitGame = true;
				
				break;
			default:
				printf("\nError in your input, please only type the specified ones.\n\n");
		}
			
		

		
		/*-----------------------------------------MAIN LOOP OF CHECKERS GAME------------------------------------------------------------	*/
		while (bIsGameStateOn)
		{
			system("CLS");
			
			//Calling this function again will wipe the board and erase positions last time
			makeBoard(cChessBoardDesign, BOX_HEIGHT, 8*BOX_WIDTH, 8);							
			
			//translates piece positions and displays the board
			displayBoard(cChessBoardDesign, BOX_HEIGHT, 8*BOX_WIDTH, 8, //Dimension of the chessboard and the array
						 cPiecePosInfo, 								//Position info array
						 bTurnOnLocate, 								//Should the piece be displayed and located
						 bIsWhite);										//Color of the current turn
			
			//Counts the pieces of black and white pieces on the board
			countBoardPieces(cPiecePosInfo, &nBlackPieces, &nWhitePieces);										

			printf("Type only 'X' on any of the prompts below to surrender\n");
			//Displays who's turn it is
			displayCurrentColorTurn(bIsWhite, cCurrentPlayer);					
			
			//Display the number of black and white pieces
			printf("Black Pieces: %d\n", nBlackPieces);
			printf("White Pieces: %d\n\n", nWhitePieces);
			

	
			

			selectPieceToMove(bIsWhite, 				//Color of the current player pieces
							  cCurrentPlayer, 			//Current player label 'A' or 'B'
							  cPiecePosInfo, 			//Position info array of piece IDs
							  cChessBoardDesign, 		//Chessboard with design
							  &bIsGameStateOn);
			
			/*SURRENDER RESULT
			  This condition is being checked as a result of a surrender
			*/
			if (!bIsGameStateOn)
			{
				//Clear screen
				system("CLS");
				
				
				//Displays ascii art of flag and who surrendered																	
				raiseSurrender(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
				
				
				//If white piece surrendered then black piece wins
				if (bIsWhite)
				{
					
					printf("Player %c: White team has surrendered\n\n\n", cWhitePlayer);	//If this turn was white's turn, then he/she surrendered
					displayMedal();
					printf("\n\nCongratulations to holder of black piece, Player %c! \n\n\n", cBlackPlayer);
					displayCongratulations(cBlackPlayer);
				}
				
				
				
				//If black piece surrendered then white piece wins
				else
				{																											
					printf("Player %c: Black team has surrendered\n\n\n", cBlackPlayer);
					displayMedal();
					printf("\n\nCongratulations to holder of white piece, Player %c! \n\n\n", cWhitePlayer);
					displayCongratulations(cWhitePlayer);
				}
				
				
				
				//Player prompting for continue or go back to main menu
				do
				{
				
					printf("Press 'Y' to continue playing or 'X' to go back to main menu: \n");
					scanf("%s", cUserContinuePlaying);
					
					//Check if the prompt says the player wants to continue the game
					if (cUserContinuePlaying[0]=='Y' ||  cUserContinuePlaying[0]=='y' )
					{
						// Restarts positions of the pieces
						initPositions(cPiecePosInfo, 8, 8);	
						
						
						//Swaps players sides
						swapPlayerSides(&cBlackPlayer, &cWhitePlayer);
						
						//Signify who swapped colors with who
						printf("Players shall now swap their color of pieces this game\n\n");
						displayColorOwnership(cBlackPlayer, cWhitePlayer);
						
						//Continue game of checkers
						bIsGameStateOn = true;
						
						//Makes sure black pieces always starts by making bIsWhite true, because a condition will reverse this
						bIsWhite = true;	
					}

					//Display there is an error in user input
					if (cUserContinuePlaying[0]!='Y' && cUserContinuePlaying[0]!='y' &&
					  cUserContinuePlaying[0]!='X' && cUserContinuePlaying[0]!='x' )
						printf("Choose 'X' or 'Y' only \n");
				}
				
				//Keep the loop going when there is still wrong inputs
				while((cUserContinuePlaying[0]!='Y' && cUserContinuePlaying[0]!='y' &&
					  cUserContinuePlaying[0]!='X' && cUserContinuePlaying[0]!='x') == 1 );
				
				
				
			}
			
			
			/*WIN CONDITIONS ACHIEVED
			  If there was no surrender, then we must check the win conditions if they are
			  met by the player
			*/
			else
			{																					
				
				//Checks if there is a winner
				bIsThereWinner = askIsThereWinner(bIsWhite, cPiecePosInfo, &bIsAtLastRow , &bIsOpponentBlocked, &bIsCapturedAll);
				
				//Stops the game state if there is now a winner
				if (bIsThereWinner)
					bIsGameStateOn = false;
	
				if (!bIsGameStateOn)
				{
					
					//clears previous printf and prompts
					system("CLS");
					
					//Calling this function again will wipe the board and erase positions last time
					makeBoard(cChessBoardDesign, BOX_HEIGHT, 8*BOX_WIDTH, 8);
					
					//translates piece positions information at PiecePosInfo into the designed chessboard							
					displayBoard(cChessBoardDesign, BOX_HEIGHT, 8*BOX_WIDTH, 8, cPiecePosInfo, bTurnOnLocate, bIsWhite);			
					
					//Counts the pieces of black and white pieces on the board
					countBoardPieces(cPiecePosInfo, &nBlackPieces, &nWhitePieces);	
					
					//Display the number of pieces										
					printf("Black Pieces: %d\n", nBlackPieces);															
					printf("White Pieces: %d\n\n", nWhitePieces);
					
					
					//The three win game conditions for the current player
					
				
				
					
					//Winning by reaching last row
					
					//When this white player arrives at last row, he/she wins 
					if(bIsAtLastRow && bIsWhite)
					{
					
						//Display the color of who won					
						displayWhitePieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						//Display the player of who won
						displayCongratulations(cCurrentPlayer);		
					}
					//When this black player arrives at last row, he/she wins 
					else if (bIsAtLastRow && !bIsWhite)
					{			
						displayBlackPieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						displayCongratulations(cCurrentPlayer);
					}
					
				
				
				
					
					//Winning by blocking opponent's moves
					
					//When white player's opponent gets all his pieces blocked, he/she wins
					else if(bIsOpponentBlocked && bIsWhite)
					{		
					
						printf("\nBLOCK ALERT! Black's pieces are blocked! \n\n");
						displayWhitePieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						displayCongratulations(cCurrentPlayer);						
					}
					
					//When this black player's opponent gets all his pieces blocked, he/she wins
					else if (bIsOpponentBlocked && !bIsWhite)
					{		
						printf("\nBLOCK ALERT! White's pieces are blocked! \n\n");
						displayBlackPieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						displayCongratulations(cCurrentPlayer);
					}
					
		
				
				
					
					//Win by getting all pieces of opponent captured
					
					//When this white player gets to capture all pieces of black, he/she wins
					else if(bIsCapturedAll && bIsWhite)
					{		
						displayWhitePieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						displayCongratulations(cCurrentPlayer);
					}
					
					//When this black player gets to capture all pieces of white, he/she wins
					else if (bIsCapturedAll && !bIsWhite)
					{			 
						displayBlackPieceWins(cCurrentPlayer, &nPlayerA_GamesWon, &nPlayerB_GamesWon);
						displayCongratulations(cCurrentPlayer);
					}
					
					
					
					//Feature: Prompt user to continue or not
					do
					{
						
					
						printf("Press 'Y' to continue playing or 'X' to go back to main menu: \n");	
						scanf("%s", cUserContinuePlaying);
						
						//Check if the prompt is a yes for continiue playing
						if (cUserContinuePlaying[0] == 'Y' || cUserContinuePlaying[0]=='y' )
						{
							//Swaps player sides
							swapPlayerSides(&cBlackPlayer, &cWhitePlayer);
							
							//displays that they swap
							printf("Players shall now swap their color of pieces this game\n\n");
							
							//Displays who has the colore of which pieces
							displayColorOwnership(cBlackPlayer, cWhitePlayer);
							
							// Restarts positions of the pieces
							initPositions(cPiecePosInfo, 8, 8);	
							bIsGameStateOn = true;
							
							//Makes sure black pieces always starts by making bIsWhite true, because a condition will reverse this
							bIsWhite = true;					
							
						}
						if (cUserContinuePlaying[0]!='Y' && cUserContinuePlaying[0]!='y' &&
					 		 cUserContinuePlaying[0]!='X' && cUserContinuePlaying[0]!='x' )
							printf("ERROR! Choose 'X' or 'Y' only\n\n");
					}
					while((cUserContinuePlaying[0]!='Y' && cUserContinuePlaying[0]!='y' &&
						  cUserContinuePlaying[0]!='X' && cUserContinuePlaying[0]!='x') == 1 );

				}

			}
			
			
			
			
			//Alternates the turn of players
			if (bIsWhite)
			{																		
				bIsWhite = false;
				
				//Changes back to black piece holding player
				cCurrentPlayer = cBlackPlayer;													
				
				
				
			}
			else
			{
				bIsWhite = true;
				
				//Changes back to white piece holding player
				cCurrentPlayer = cWhitePlayer;													
			}
		
			
			
		}


	}
	
	
	return 0;
	
	

	
	
	
}

