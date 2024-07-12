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
	Description: Vaccination Registration with Chatbot App is an application that gives users a chance to book
	an appointment via registering to this program and manually requesting one through there. Admin functionalities
	are also available to whoever knows how to access the admin details in order to assess user data, appointment data,
	chatbot data, and also be able to edit, add, delete, and view the said data. The admin is also able to import and export
	data of files in a .txt manner. Users are only limited to registering, requesting an appointment, and an added functionality
	of chatting with a Chatbot. All fields entered by the user are intensely check, and the availability of vaccines is also checked.
	There is a limit of 100 records on each data file of appointment, users, and chatbot QnA.
	
	Programmed by: Paul Josef P. Agbuya S20
	Last Modified: April 6, 2023
	Version: 1.0
	[Acknowledgements: Sites or borrower libraries and sources
	
	Concepts of color
		-https://chat.openai.com/chat?model=gpt-4
		-https://www.theurbanpenguin.com/4184-2/
	
	Printing wide characters
		-https://stackoverflow.com/questions/46512441/how-do-i-print-unicode-to-the-output-console-in-c-with-visual-studio
		
	ASCII Art Sources:
		-https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
		-https://www.asciiart.eu

	]
	
*/


#include <stdio.h>		// Input output streams
#include <string.h>		//strlen, strcmp, strcat, strcpy
#include <stdlib.h>		// Get use of abs()

#include <conio.h>		//helps in hiding password via getch and terminating input newlines
#include <inttypes.h>	//Allows me to use long long ints

#include <io.h>			//Helps modify output encoding
#include <fcntl.h>		//Helps change font of console
#include <time.h>		//Allows the rand() function to be pseudo random

#include <ctype.h>		//For using isalnum() which returns 1 if character is letter or num


// Admin details
#define ADMIN_ID 122448
#define ADMIN_PASS "123"

#define LINE_SIZE 400			//size of fgets extracting info per line

// Max Records
#define MAX_USERS 100
#define MAX_REQS 100
#define MAX_CHAT 100

// Max attempt of login
#define MAX_ATTEMPTS 3



typedef char String80[81];
typedef char String30[31];
typedef char String20[21];
typedef char String10[11];
typedef char String11[12];
typedef char String6[7];



struct doseTag
{
	
	
	String10 sDate;
	String10 sName;
	String10 sLoc;
	
	
};


struct userTag
{
	unsigned int nUID;
	

	long long unsigned int nContact;
	
	String10 sSex;	
	String10 sPassword;
	String20 sName;
	String30 sAddress;

	struct doseTag stDose1;
	struct doseTag stDose2;
	struct doseTag stBoost;

	
};


struct appTag
{
	int nAppID;
	int nUID;
	String20 sName;
	
	String11 sDate;
	String10 sLoc;
	String10 sVax;
	String10 sDose;
	
	String6 sTime;
	
};


struct chatTag
{
	int nNum;
	String80 sQues;
	String80 sAns;
	
};



/* 
	The displayBotArt5_Bordered function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
	
*/
void
displayBotArt5_Bordered()
{
	int i;
	
	// Activates wide character printiing
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	// Sets and array of wide character strings
    const wchar_t *lines[] = {
		L"|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣿⣿⣿⣦⣾⣯⣥⠀⠀⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣼⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣟⣿⣻⣄⠀⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⣿⣿⣿⣿⣿⣿⣿⠏⢰⡀⠙⠻⣿⣿⣿⢿⣿⣿⢿⣿⣮⢿⡭⠿⠃⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡅⢠⣾⣿⠇⠀⣾⣿⣿⢗⣟⣝⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠘⡏⠀⢰⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⠶⣶⡆⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣼⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢞⣿⠄⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠘⢿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣟⢯⡿⣟⡿⣟⣿⣿⣿⡉⠀⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⢿⣏⣿⢿⣧⣿⣿⣾⡁⣿⣷⡟⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⠀⠘⣿⢿⣿⣿⠻⣷⣿⣯⣳⣞⣵⣟⠁⠈⢿⣾⣇⠛⣿⣮⣿⣷⣿⣿⣾⡹⢿⣿⣽⢦⡀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⣠⡾⣏⣿⣿⣷⣬⣟⣿⣿⡿\033[0;31m⢿⣿⣷⣷\033[0m⠀⠀⠙⠻⢦\033[0;31m⣿⣿⣿⡿\033[0m⣷⣼⡷⣻⡝⣿⣿⣿⣷⣦⣤⠀⠀|",
		L"|⠀⣀⣤⣾⣳⣿⣿⣿⣿⡞⣿⣜⣻⣿⠀\033[0;31m⢿\033[0;33m⠿⢽\033[0;31m⡿⠀⠀⠀⢀⠀⢿\033[0;33m⠷⣿\033[0;31m⡇\033[0m⣘⣼⣽⡧⣿⣿⣿⣿⣯⠍⠁⠀⠀|",
		L"|⠛⠛⠿⠿⠟⢻⣿⣿⣿⣿⣽⣿⣷⣿⡮\033[38;2;255;192;203m⠈⠙⠉⠁\033[0m⠀⡖⠒⠒⢲⠀\033[38;2;255;192;203m⠉⠁\033[0m⠀⠛⣻⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀|",
		L"|⠀⠀⠀⠀⢀⣹⣿⣿⣿⣿⣿⣿⣿⣷⣤⡄⠀⣀⣀⡀⡇⠀⢀⠎⡠⠤⢄⣀⢾⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⣀⠀|",
		L"|⠀⠀⢠⣴⣿⣿⣿⣯⡟⢹⣽⣿⣿⠋⠀⢠⡟⠁⠀⠀⠙⣶⣬⠋⠀⠀⠘⢳⠈⣿⣿⢲⠃⣽⡟⣿⣿⣿⣿⣿⠃|",
		L"|⠀⣶⣿⣿⠟⣿⢳⣾⣷⣎⣵⡿⠃⣠⣾⣿⣇⢀⣀⣀⣠⣿⣿⣄⣀⣠⣦⣿⣷⡜⣿⣧⣿⣻⣿⡝⣿⢿⡉⠀⠀|",
		L"|⠀⠈⣽⣃⣏⣈⢿⣿⣿⣿⡟⠁⣼⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⠹⣿⣷⣿⡿⢟⠣⢆⢳⡀⠀|",
		L"|⠀⣼⣷⡹⣞⡭⢷⡶⣠⣼⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣼⣿⣿⡟⠻⠿⠛⠋⠀⠀⢳⣨⣴⢲⡞⣾⢶⣦⣷⠀|"
    };

	// print the wide characters on screen
    for (i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);


	
}


/* 
	The displayBotArt5 function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
*/
void
displayBotArt5()
{
	int i;
	
	_setmode(_fileno(stdout), _O_U16TEXT);

    const wchar_t *lines[] = {
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣿⣿⣿⣦⣾⣯⣥⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣼⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣟⣿⣻⣄⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⣿⣿⣿⣿⣿⣿⣿⠏⢰⡀⠙⠻⣿⣿⣿⢿⣿⣿⢿⣿⣮⢿⡭⠿⠃⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡅⢠⣾⣿⠇⠀⣾⣿⣿⢗⣟⣝⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠘⡏⠀⢰⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⠶⣶⡆⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣼⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢞⣿⠄⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠘⢿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣟⢯⡿⣟⡿⣟⣿⣿⣿⡉⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⢿⣏⣿⢿⣧⣿⣿⣾⡁⣿⣷⡟⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠘⣿⢿⣿⣿⠻⣷⣿⣯⣳⣞⣵⣟⠁⠈⢿⣾⣇⠛⣿⣮⣿⣷⣿⣿⣾⡹⢿⣿⣽⢦⡀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⣠⡾⣏⣿⣿⣷⣬⣟⣿⣿⡿\033[0;31m⢿⣿⣷⣷\033[0m⠀⠀⠙⠻⢦\033[0;31m⣿⣿⣿⡿\033[0m⣷⣼⡷⣻⡝⣿⣿⣿⣷⣦⣤⠀⠀",
		L"⠀⣀⣤⣾⣳⣿⣿⣿⣿⡞⣿⣜⣻⣿⠀\033[0;31m⢿\033[0;33m⠿⢽\033[0;31m⡿⠀⠀⠀⢀⠀⢿\033[0;33m⠷⣿\033[0;31m⡇\033[0m⣘⣼⣽⡧⣿⣿⣿⣿⣯⠍⠁⠀⠀",
		L"⠛⠛⠿⠿⠟⢻⣿⣿⣿⣿⣽⣿⣷⣿⡮\033[38;2;255;192;203m⠈⠙⠉⠁\033[0m⠀⡖⠒⠒⢲⠀\033[38;2;255;192;203m⠉⠁\033[0m⠀⠛⣻⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⢀⣹⣿⣿⣿⣿⣿⣿⣿⣷⣤⡄⠀⣀⣀⡀⡇⠀⢀⠎⡠⠤⢄⣀⢾⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⣀⠀",
		L"⠀⠀⢠⣴⣿⣿⣿⣯⡟⢹⣽⣿⣿⠋⠀⢠⡟⠁⠀⠀⠙⣶⣬⠋⠀⠀⠘⢳⠈⣿⣿⢲⠃⣽⡟⣿⣿⣿⣿⣿⠃",
		L"⠀⣶⣿⣿⠟⣿⢳⣾⣷⣎⣵⡿⠃⣠⣾⣿⣇⢀⣀⣀⣠⣿⣿⣄⣀⣠⣦⣿⣷⡜⣿⣧⣿⣻⣿⡝⣿⢿⡉⠀⠀",
		L"⠀⠈⣽⣃⣏⣈⢿⣿⣿⣿⡟⠁⣼⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⠹⣿⣷⣿⡿⢟⠣⢆⢳⡀⠀",
		L"⠀⣼⣷⡹⣞⡭⢷⡶⣠⣼⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣼⣿⣿⡟⠻⠿⠛⠋⠀⠀⢳⣨⣴⢲⡞⣾⢶⣦⣷⠀"
    };

    for (i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

	
}


/* 
	The displayBotArt4 function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
	
*/
void
displayBotArt4()
{
	int i;
	
	_setmode(_fileno(stdout), _O_U16TEXT);

    const wchar_t *lines[] = {
		L"⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⢀⣀⣘⣋⣀⣀⣀⣀⣀⣀⣿⣿⣿⣿⣿⣟⢿⣻⣿⣿⣿⣿⣿⣿⠃",
		L"⠀⠀⠀⠀⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣷⣿⡿⣏⡿⣽⡟⠀",
		L"⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣽⠟⠀",
		L"⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣁⠀⠀",
		L"⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀",
		L"⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⢎⠻⣶⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⢸⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢏⠈⣿⣿⣿⣿⣿⣿⣿⣧⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⣾⢫⠵⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⡟⠋⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿",
		L"⣿⣿⣿⣿⣿⣿⡿⡿⠟⠋⠁⠀⠀⠀⠀⠀⠀⢿⣿⢻⣿⣿⣿⣿⣷⡀⢀⣀⣀⣉⣻⣿⣿⣿⣿⣿⡆⣧⣿⣿⣿⣝",
		L"⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣦⣤⣤⣀⠀⠀⠈⢿⠆⠉⠋⢹⣿⣿⣿⣿⣿⣿⣿⣿⡟⢻⡿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⠛⢹⣿⣿⣿⣿⡿⡛⠛⠛\033[0;31m⣿⣿⣿⣿⣿⡋⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⡄\033[0m⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⠀⢸⣿⣿⣿⣿⡇⠀⠀\033[0;31m⣼⣿⣿⡿⢿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠉⣹⣿⣿⣿\033[0m⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⠀⣸⣿⣿⣿⣿⣷⠀⠀\033[38;5;214m⢹⣿⡻⠧⠼⣟⣿⠃⠀⠀ ⠀⠀⠀⠀⠸⣿⣳⡟⠛⠉⢳⣻⡏\033[0m⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⠀⣿⣿⣿⣿⣿⣿⣆⠀\033[0;31m⠠⣽⣦⣤⣤⡾⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣻⣶⣶⡶⠾⠋\033[0m⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⢸⣿⣿⣿⣿⣿⣿⣿⣦⠀\033[38;2;255;192;203m⣠⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡦\033[0m⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⣾⣿⣿⣿⣿⣿⣿⣿⣿⠷⠄⠀⠀⠀⠀⠀⣀⠀⠀⠀⣀⣠⣤⠄⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
		L"⣿⣿⣿⣿⡟⣿⣿⣿⣿⣦⣤⣄⠀⠀⠀⠀⠙⠒⠚⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣩⢾⣿⣿⣿⣿⣿⣿⡿⣿⣿",
		L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠙⣦⠀⠀⠀⢀⣀⣀⣠⣤⡤⠤⠴⣤⠀⠀⢀⣠⡴⠛⢡⣿⣿⣿⣿⣿⣿⣿⠇⣿⣿",
		L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠹⠤⠒⠚⠉⠉⠀⠀⠀⣠⣶⡾⠿⠖⣻⠋⠁⢀⣴⣿⢿⣿⣿⣿⣿⣿⣿⠀⢻⣿",
		L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣶⣶⣾⣿⣿⣦⣀⡉⠉⣠⣿⣿⣿⣿⣿⣿⡇⠀⢸⣿"
    };

    for (i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

	
}


/* 
	The displayBotArt3 function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
	
*/
void 
displayBotArt3()
{
	int i;
	_setmode(_fileno(stdout), _O_U16TEXT);

    const wchar_t *lines[] = {
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⣈⡴⠚⠁⡌⠳⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⠛⠀⠀⢸⣀⠀⠈⠉⣧⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡄⠀⠀",
		L"⠀⠀⠀⠀⠥⠀⠀⢃⣤⣶⣾⣿⣿⣿⣿⡇⠀⣰⠾⢎⣿⠀⢸⣿⣿⣿⣿⣷⣶⣤⣀⠀⠀⢀⡀⣼⡧⠖⠀",
		L"⠀⠀⠀⠀⠀⣠⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠈⢳⡞⠋⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣼⣟⡿⡄⠀⠀",
		L"⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠈⠇⠀⢠⣿⣿⣿⣿⣿⣟⣿⢩⣾⣿⣿⣿⢧⣿⡆⠀⠀",
		L"⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣇⣗⣾⣾⣿⢊⣉⣿⡠⠤⠀",
		L"⠀⠈⠂⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣟⣿⣯⣿⣿⡝⠛⠗⠀⠀",
		L"⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⡿⢻⣟⡿⢟⡻⢛⣿⡟⢿⠻⣿⣿⣿⣿⣿⣿⣿⡭⣷⣻⡂⠀⡀⠀⠀",
		L"⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣻⡟⡷⣤⣽⡟⣆⣢⡑⣂⣼⣯⣬⢥⣼⢳⣻⡿⢿⣿⣷⣿⣷⣿⣳⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠐⢿⣿⣿⣟⢮⣽⣏⢷⣳⠋⢹⣎⢷⡹⢯⡝⡟⢮⣳⢭⣿⡶⣿⢻⡜⣿⣿⣿⣿⠋⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⢀⣴⣿⢳⡟⡾⣼⣿⠞⠁⠒⠀⢻⣎⠷⣯⣽⣻⣌⠑⠻⣖⣻⠿⣷⣹⣿⣟⢹⣿⡆⠈⠃⠀⠈",
		L"⣤⣴⣶⣿⢿⠿⣭⡗⢯⣳⠽⡅⠠⢀⠀⠀⠀⠙⠿⣜⡳⣤⣞⡿⣿⢾⣦⣹⣟⡧⣟⢿⣿⣿⣯⣁⡠⡀⠄",
		L"⠈⠛⠿⢿⣿⡻⢯⣝⣿⣷⣫⢷⣛⣛⣾⣶⡅⠀⠀⠀⠉⢹⠅\033[0;31m⢸⡼\033[0m⠀⢿⣿⣟⣾⣭⢻⢿⣿⣿⣿⡿⠋⠀",
		L"⢀⠀⠐⠢⠍⠉⢹⣿⣿⣿⣿⣟⠚⠁⠀⠀⠀⠀⠀⠀⠀⠈⠑⠲⠁⠐⣺⣽⣾⣿⣷⣏⣯⡽⣻⡅⠀⠀⠀",
		L"⠨⠠⠀⠐⣀⣴⣫⣟⢿⣿⡝⡯⠷⠦⠈⣆⣀⠀⠀⠃⢁⣀⣰⡉⠲⠞⠿⣋⣿⣿⡟⡾⡽⢯⣁⡀⠄⠀⠀",
		L"⠀⠠⣶⣟⣯⣷⣿⣝⣮⣿⣿⣇⠀⠀⢚⣻⣿⣿⣿⣿⣿⣿⣿⣉⠀⠀⢀⣿⣿⣧⣻⡵⣟⣯⣽⣯⣷⠀⠀",
		L"⠀⠀⠈⠉⢈⣿⣞⡾⣿⣿⣿⣿⣷⣶⣿⣯⣿⣿⣟⣝⣹⣿⣾⣽⣿⣿⣿⣿⣿⣿⣷⣻⢿⡆⠁⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠈⠻⣿⣿⣽⡿⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡿⣿⣷⣿⠿⠃⠀⠁⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠛⠋⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠙⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀"
    };

    for ( i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

	
}


/* 
	The displayBotArt2 function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
	
*/
void 
displayBotArt2()
{
	int i;
	
 	_setmode(_fileno(stdout), _O_U16TEXT);

    const wchar_t *lines[] = {
	L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⡞⠋⠀⢀⡟⠀⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
	L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣴⣶⣿⣿⣿⣿⡇⠀⢀⣬⡟⣦⡄⢀⣿⣿⣷⣦⣤⡀⠀⠀⠀⠀⠀⠀⢀⣴⠀",
	L"⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠛⢧⣴⠟⠀⢸⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⢀⣤⡸⡿⠞",
	L"⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠸⠇⠀⠐⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣷⣾⢿⢻⡇⠀",
	L"⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣶⣶⣦⣤⣼⣿⣿⣿⣿⣿⣿⣹⠿⢯⣿⣿⣿⣿⣫⡇⠀",
	L"⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡽⣟⣿⣾⣟⣁⣱⣻⡤⠶",
	L"⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⢿⡿⢿⡿⢿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡾⢷⣿⣯⠝⠓⠗⠀",
	L"⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣟⣿⠿⣅⢢⣾⣿⢠⠙⡩⢸⣷⡘⢋⡙⡿⣿⣿⣿⣿⣿⣿⣼⣽⣿⠀⠀⠀⠀",
	L"⠀⠀⠀⠀⠀⠸⣿⣿⣿⣟⠾⣼⣯⢻⣽⡟⢹⣧⣛⠾⣴⠿⣿⡵⣯⢟⣷⡭⣿⡟⣿⣿⣿⣷⣿⣿⡧⠀⠀⠀",
	L"⠀⠀⠀⠀⠀⣠⣼⡻⣼⢯⡻⣼⣷⠟⠁⠀⡀⢷⣫⢟⣮⣛⢾⡙⠮⣻⠼⣷⣿⡟⣶⢻⣿⣿⣿⡏⠁⠀⠀⠀",
	L"⠀⠀⠀⢶⣟⣻⣶⡝⣾⡷⣹⢾⢁⣠⣤⣶⣌⠈⠻⡮⡽⣯⠚⢷⣦⣌⡛⠼⣭⣿⢮⣿⣿⢙⣿⣇⠀⠀⠀⠀",
	L"⣀⣠⣤⣾⣟⠯⢯⣽⣾⣷⣫⢞⣞⠟⠉⠀⠈⠳⠀⠈⠗⠋⠛⠋⠉⠙⢿⢖⡾⣽⡞⡿⣼⣶⣿⠿⠀⠀⠀⠀",
	L"⠈⠻⢿⣿⠿⠋⢩⣿⣿⣿⣿⣯⠾⠕⡀⠀⠀⠀⡠⠤⠥⢄⠀⠀⠀⠀⠐⣻⢟⣧⣿⢳⡭⣿⣿⣿⣶⣤⣄⠀",
	L"⠀⠀⠀⢀⣠⣴⣿⣿⣿⣿⣿⣿⣳⣤⣉⠀⠀⠀⢣⠀⢀⡎⠀⠀⢒⡉⠂⢿⣿⣿⣿⣿⣼⣧⣻⣿⡟⠋⠁⠀",
	L"⠀⢲⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣽⣺⢿⣶⣦⣤⣶⣯⣤⣤⣶⡶⠀⠀⠀⣿⣿⣿⢯⡽⣯⣍⠁⠀⠀⠀⠀",
	L"⠀⠀⠀⠀⢨⣿⣿⣿⣿⣿⣿⡿⣿⣿⣷⣯⣟⣿⣿⠻⣿⣿⣟⣯⣿⣦⣀⣤⣿⣿⢮⣿⡿⣷⣯⡿⠿⠀⠀⠀",
	L"⠀⠀⠀⠀⠈⠿⣿⣿⣻⣿⣿⣷⢾⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⡿⣟⡿⡇⠀⠀⠀⠀⠀",
	L"⠀⠀⠀⠀⠀⠀⠀⠉⠛⠷⠿⠞⠋⠛⠛⠿⠿⠿⠿⣿⣿⡿⠿⠿⠟⢿⣿⣿⣿⣿⣝⣿⠿⠟⠁⠀⠀⠀⠀⠀",
	L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    };

    for (i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

}


/* 
	The displayBotArt1 function is used to display a UTF-16 char encoded design on screen of the Chatbot menu
	
*/
void 
displayBotArt1()
{
	int i;
 	_setmode(_fileno(stdout), _O_U16TEXT);

    const wchar_t *lines[] = {
        L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠒⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⡟⠀⠑⢤⡀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⣾⣿⣿⣇⠀⠀⠀⠷⣆⠀⠀⣿⣿⣶⣦⣄⡀⢹⣿⣠⡆⠀⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣿⣿⣿⣿⣿⣿⣿⣿⡄⡄⣾⢻⢸⢻⢰⣿⣿⣿⣿⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠈⠻⣦⡾⠏⢸⣿⣿⣿⣿⣿⣿⣿⣿⣶⣷⡀⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⢸⡇⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⢻⣽⡇⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣀⣠⣧⣀⣿⣿⣿⣿⣿⣿⣿⣿⣯⡕⣿⡟⠃⠀⠀⠀⠀",
        L"⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⠃⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⡛⣿⠏⢯⡽⡞⣭⡓⢋⢻⡽⣿⢿⣿⣿⣿⣷⣜⣿⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣟⡿⣝⡞⣦⣼⣿⣇⣢⣐⡰⢸⣿⣬⡟⣷⣛⣯⢞⡽⣿⣿⣿⣏⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⢯⡳⢾⣻⢼⣹⢳⡟⠻⣾⡵⣫⢿⣏⣏⢳⡯⣝⣷⣿⣎⠷⣝⣿⣿⣿⣷⡀⠀⠀⠀",
        L"⠀⠀⠀⠀⣾⣿⣿⣿⡿⣽⣎⢷⣺⣟⡼⣫⡞⠁⠀⠹⣧⣛⢾⣝⣻⠈⠳⣹⡽⣿⣹⢶⡹⣿⣿⣿⣿⡧⠀⠀⠀",
        L"⠀⠀⠀⠐⢿⣿⣿⣿⣷⣻⢼⣣⢟⣿⡵⠋⠀⢀⠠⠄⠈⠻⣮⢻⣭⣧⠀⢈⣳⢟⣧⣯⢳⣿⣿⣏⠉⠁⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠈⣹⣟⡮⢿⣣⢟⣮⢯⡸⣾⣷⡶⠟⠃⠀⠀⠈⢛⠺⠛⠛⠛⢋⡼⣝⣟⣳⣿⣿⣿⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⢀⣠⣴⣿⢿⡹⣞⣿⣟⣮⠷⣯⣕⣦⡀⠀⠀⠀⡀⠤⠤⢤⡄⠀⠀⠀⠈⠉⣿⢿⣿⣿⣿⣿⣄⡀⠀⠀⠀",
        L"⢠⣶⣾⣿⣿⣿⢾⣷⣿⣯⣀⣉⠳⣿⣵⣛⡶⠂⠀⠀⠀⢃⠀⠀⢠⠃⠀⠀⠀⢀⣴⣿⣿⣻⣿⣿⠿⠿⠟⠁⠀⠀",
        L"⠀⠈⠉⠉⠉⢁⡾⣿⣿⣿⣿⣿⠉⠹⡿⣿⣷⣦⣤⣀⣀⣈⢢⡕⣃⣀⡠⠤⣶⡿⢧⣿⠷⢧⡯⣿⣷⣀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⢠⡾⣝⣿⢯⢿⣿⣿⠀⠀⠙⢳⠯⣾⣽⣻⣟⣿⣿⣿⣿⣿⣦⠤⠘⣛⣉⣭⢪⢀⡿⣶⣭⢟⡷⣤⣀⠀",
        L"⠀⠀⠀⠀⢸⣿⣸⣼⡿⣼⣻⢿⣇⠀⢀⣼⣧⣜⡣⡧⢿⣿⣿⣿⣿⣿⡇⢸⠛⣿⡸⡟⠀⠜⠻⣼⣻⡿⢼⣧⡿⠘",
        L"⠀⠀⠀⠀⠘⣞⡷⣯⢿⣷⣯⣟⣯⢿⣿⣿⣿⠀⢫⣹⣞⠟⢻⣿⣿⣿⠁⣏⣾⡷⣹⢇⢸⠀⣠⣟⣷⡇⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠙⠛⠿⣾⣽⣻⡍⠉⠹⣿⣿⣷⣬⣥⣿⣷⣾⣿⣿⡏⢸⠶⣼⢳⡟⠘⢀⣿⡿⣽⠞⠀⠀⠀⠀⠀",
        L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠛⠀⠀⠀⠙⠛⠟⠋⠀⠀⠉⠉⠁⠀⢇⣸⠾⠛⠋⠉⠓⠉⠛⠉⠀⠀⠀⠀⠀⠀⠀"
    };

    for ( i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        wprintf(L"\t\t%ls\n", lines[i]);
    }
    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

}


/* 
	The displayGoodbye function is used to Goodbye message to the user
	
*/
void 
displayGoodbye()
{
	system ("CLS");
	
	
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
	The displayStartMenu function is used to Welcome Message the user
	
*/
void
displayStartMenu()
{
	printf("%4s", "\033[0;33m ");			//Adding four spaces to the left
	printf("                                 ,,                                                                           \n");
	printf("%4s", " ");
	printf("`7MMF'     A     `7MF'         `7MM                                                              \n");
	printf("%4s", " ");
	printf("  `MA     ,MA     ,V             MM                                                              \n");
	printf("%4s", " ");
	printf("   VM:   ,VVM:   ,V    .gP\"Ya    MM   ,p6\"bo   ,pW\"Wq.  `7MMpMMMb.pMMMb.   .gP\"Ya           \n");
	printf("%4s", " ");
	printf("    MM.  M' MM.  M'   ,M'   Yb   MM  6M'  OO  6W'   `Wb   MM    MM    MM  ,M'   Yb           \n");
	printf("%4s", " ");
	printf("    `MM A'  `MM A'    8M\"\"\"\"\"\"   MM  8M       8M     M8   MM    MM    MM  8M\"\"\"\"\"\"          \n");
	printf("%4s", " ");
	printf("     :MM;    :MM;     YM.    ,   MM  YM.    , YA.   ,A9   MM    MM    MM  YM.    ,          \n");
	printf("%4s", " ");
	printf("      VF      VF       `Mbmmd' .JMML. YMbmd'   `Ybmd9'  .JMML  JMML  JMML. `Mbmmd'         \033[0m\n");
	printf("\n");
	printf("\n");

	printf("\t\t\t\t\t___________     \n");
	printf("\t\t\t\t\t\\__    ___/___  \n");
	printf("\t\t\t\t\t  |    | /  _ \\ \n");
	printf("\t\t\t\t\t  |    |(  <_> )\n");
	printf("\t\t\t\t\t  |____| \\____/ \n");
	
	printf("\n");
	printf("\n");
	printf("\t\033[1;33m   ______ _      _____ _   _     _   _  ___  __   __     ___  ____________  \n");
	printf("\t   |  _  \\ |    /  ___| | | |   | | | |/ _ \\ \\ \\ / /    / _ \\ | ___ \\ ___ \\ \n");
	printf("\t   | | | | |    \\ `--.| | | |   | | | / /_\\ \\ \\ V /    / /_\\ \\| |_/ / |_/ / \n");
	printf("\t   | | | | |     `--. \\ | | |   | | | |  _  | /   \\    |  _  ||  __/|  __/  \n");
	printf("\t   | |/ /| |____/\\__/ / |_| |   \\ \\_/ / | | |/ /^\\ \\   | | | || |   | |     \n");
	printf("\t   |___/ \\_____/\\____/ \\___/     \\___/\\_| |_/\\/   \\/   \\_| |_/\\_|   \\_|     \033[0m\n");
	printf("\n");
	printf("\n");	
	
	

	printf("\n");
}



/* 
	The randomizeDisplayArt function is used to randomize which art would be displayed on the chatbot menu interface
	
*/
void
randomizeDisplayArt()
{
	
	int nRandomNumber;
	int nSelectedNumber;
	
	void (*funcList[5])() = {
							displayBotArt1, 
							displayBotArt2, 
							displayBotArt3,
							displayBotArt4,
							displayBotArt5
							};
	
	srand(time(NULL));							//Sets the seed of calling a random number based on time parameters of NULL, making it pass only seconds
				
	nRandomNumber = rand();						//Calls a random number which performs a series of 'random' operations based on seed
	nSelectedNumber = nRandomNumber%5;
	
	// Activate the function that prints the art
	funcList[nSelectedNumber]();
	
	
	
	
}



/* 			START					CHARACTER MANIPULATION TOOLS					*/		

/* 
	This lowerStringCase function is used to lower the string case of a given input, strictly letters only
	
	@param sStringLower is One dimensional array containing the character string that is to be checked and converted to lower case
	
*/
void
lowerStringCase(char sStringLower[])
{
	
	int nStrLen = strlen(sStringLower);
	int i = 0;
	
	

	for (i = 0; i < nStrLen; i++)
	{
		// Selects all capital characters from 65-90
		if (sStringLower[i] >= 65 &&
			sStringLower[i]  <= 90)
			sStringLower[i] = sStringLower[i]+32;
		
		
	}
	
	
}



/* 
	This countDigits function is used to count how many digits there are in an input
	
	@param nNum is the number inputted
	
	@return returns the number of digits in the given number
	
	Pre-condition: nNum is always at most 19 digits
*/
int
countDigits(long long int nNum)
{
	int nCount = 0;
	
	// Counts the digits through a division algorithm
	while(nNum)
	{
		nCount++;
		
		// decrease the number by dividing to get the next digit
		nNum /= 10;
	}
	
	return nCount;
	
}


/* 
	This scanYesNo function is used to input check the user's field and ensures that the entered character is valid
	via checking if it is 'y'/'n'
	
	@param pCharUserInput pointer to the user's input field to contain a single character
	

*/
void
scanYesNo(char *pCharUserInput)
{
	char sLine[LINE_SIZE];
	
	//Get Inpyt First
	fgets(sLine, LINE_SIZE, stdin);
	lowerStringCase(sLine);
	sscanf(sLine, "%c", pCharUserInput);
	
	// Keep prompting user while he /she doesn't input a proper yes or no
	while(*pCharUserInput != 'y' && *pCharUserInput != 'n')
	{
		//When the Input is not 'y' or 'n' we state the error and prompt user again
		printf("\n\033[1;38;5;202mERROR! Only input 'Y' or 'N'\033[0m\n");
		printf("Input again: ");
		fgets(sLine, LINE_SIZE, stdin);
		
		// Lowering string case allows user to safely input Capital letters
		lowerStringCase(sLine);
		sscanf(sLine, "%c", pCharUserInput);
		
	}
	
	
}


/* 
	This scanYesNoX function is used to input check the user's field and ensures that the entered character is valid
	via checking if it is 'y'/'n'/'x'
	
	@param pCharUserInput pointer to the user's input field to contain a single character
	

*/
void
scanYesNoX(char *pCharUserInput)
{
	char sLine[LINE_SIZE];
	
	//Scanf the input of user
	fgets(sLine, LINE_SIZE, stdin);
	
	// lowers string to allow user to input Capital letters while not needing to provide additional condition for Capital letters
	lowerStringCase(sLine);
	sscanf(sLine, "%c", pCharUserInput);
	
	while(*pCharUserInput != 'y' && *pCharUserInput != 'n' && *pCharUserInput != 'x')
	{
		printf("\n\033[1;38;5;202mERROR! Only input 'Y' or 'N' or 'X'\033[0m\n");
		printf("Input again: ");
		fgets(sLine, LINE_SIZE, stdin);
		
		// Lowerin string case eases the checking of inputs
		lowerStringCase(sLine);
		sscanf(sLine, "%c", pCharUserInput);
		
	}
	
	
}


/* 
	scanID function is used to repeteadly prompt and input check the user's field and ensures that the entered number is valid
	
	@param pIntID pointer to the user's input field to contain a valid number ID input
	
	
*/
void
scanID(int *pIntID)
{
	char sLine[LINE_SIZE];
	int nDigits;
	
	//Scan if there is an integer
	fgets(sLine, LINE_SIZE, stdin);
	sscanf(sLine, "%9d", pIntID);
	
	// Count the digits
	nDigits = countDigits((long long int) pIntID);
	
	// Keep prompting user of the input that is not too much to scan
	while(*pIntID < 0 || nDigits > 9)
	{
		printf("\n\033[1;38;5;202mERROR! Only input nonnegative digits (Only less than 10 digits allowed)\033[0m\n");
		printf("Input again: ");
		fgets(sLine, LINE_SIZE, stdin);
		sscanf(sLine, "%9d", pIntID);
		nDigits = countDigits((long long int) pIntID);
		
	}
}


/* 
	removeSpaces function is used to modify the string and remove the spaces between words
	
	@param sLine is a string of characters that came from the user or file reading
	
*/
void
removeSpaces(char sLine[])
{
	
	char sNewLine[LINE_SIZE];
	int i, j;
	strcpy(sNewLine, "");
	//Sets index of string with no
	j= 0;
	for( i = 0; i < strlen(sLine); i++)
	{
		// Ignores the space and store it to a seperate string
		if (sLine[i] != ' ')
		{
			sNewLine[j] = sLine[i];
			j++;							//Increments if it detects no space
		}
		    
	}
	
	//Terminates the string
	sNewLine[j] = '\0';
	
	//New string overwrites original
	strcpy(sLine, sNewLine);
}	


/* 
	removeNewLine function is used to modify the string and remove the newlines at ends of strings
	
	@param sLine is a string of characters that came from the user or file reading
	
*/
void
removeNewLine(char sLine[])
{
	char *pChar;

	pChar = strchr(sLine, '\n'); //Returns address or location of newline character if there is
	if (pChar)					 //If it does have an address then give a terminating byte
		*pChar = '\0';
	
	
}


/* 
	warnValidSize function is used to repeatedly prompt and validate the input to be the right size given by parameters.
				  it also prompts user repeatedly if the field is empty
	
	@param sText is a string of characters that came from the user or file reading
	@param nMaxSize is the max size that is the threshold for validating
	@param sLabel is a string of characters that state what input is being reinputted if wrong
	
*/
void
warnValidSize(char sText[], 
			  int nMaxSize, 
			  String80 sLabel)
{
	
	int bIsValid;
	char cArrBuffer[LINE_SIZE];
	
	removeNewLine(sText);
	
	// Sets that user's input first as not valid
	bIsValid = 0;
	while(!bIsValid)
	{
		// Checks if input is bigger than the set max size
		if(strlen(sText) > nMaxSize)
		{
			// Prompts user to input again
			printf("\n\033[1;38;5;202mYour input has too much characters (%d characters max).\033[0m\n", nMaxSize);
			printf("Enter again %s: ", sLabel);
			fgets(cArrBuffer, LINE_SIZE, stdin);
			removeNewLine(cArrBuffer);
			sscanf(cArrBuffer, "%[^\n]", sText);

		}
		else if (strlen(sText) == 0)
		{
			// Prompts user to input again
			printf("\n\033[1;38;5;202mYour input field is empty.\033[0m\n");
			printf("Enter again %s: ", sLabel);
			fgets(cArrBuffer, LINE_SIZE, stdin);
			removeNewLine(cArrBuffer);
			sscanf(cArrBuffer, "%[^\n]", sText);
		}
		else
			bIsValid = 1;
	
	}

}


/* 
	isValidDose returns 1 if the input text is a valid Dose from the choices given below, else 0
	
	@param sText is a string of characters that came from the user or file reading
	
	@return 1 if the input is a valid Dose input, 0 if not
*/
int
isValidDose(char sText[])
{

	int nFlag;
	
	
	//To ignore the capital letter cases
	lowerStringCase(sText);
	
	//Default invalid input
	nFlag = 0;
	
	// Checks if the possible iterations and word semantics could be used by the user	
	if (!strcmp(sText, "1st") || !strcmp(sText, "1") ||
		!strcmp(sText, "one") || !strcmp(sText, "first"))
	{
		// Declares valid input
		nFlag = 1;
		
		// Overwrite original with a proper name convention
		strcpy(sText, "First");
	}
	
	// Check possible similar or synonymous words
	else if (!strcmp(sText, "2nd") || !strcmp(sText, "2") ||
			 !strcmp(sText, "two") || !strcmp(sText, "second"))
	{
		nFlag = 1;
		strcpy(sText, "Second");
	}
	
	// Check possible similar or synonymous words
	else if (!strcmp(sText, "3rd") || !strcmp(sText, "3") ||
			 !strcmp(sText, "three") || !strcmp(sText, "third"))
	{
		nFlag = 1;
		strcpy(sText, "Third");
	}
	
	// Check possible similar or synonymous words	
	else if (!strcmp(sText, "b") || !strcmp(sText, "boost") ||
			 !strcmp(sText, "btr") || !strcmp(sText, "booster"))
	{
		nFlag = 1;
		strcpy(sText, "Booster");
	}				

	
	// Return the value
	return nFlag;
	
	
}


/* 
	promptMoreForInvalid_Dose keeps prompting user until he/she enters a valid choice of Dose
	
	@param sText is a string of characters that came from the user or file reading
	
*/
void
promptMoreForInvalid_Dose(char sText[])
{
	
	int bIsValid;
	char cArrBuffer[LINE_SIZE];
	bIsValid = 0;
	
	while(!bIsValid)
	{
		//Check if the input is valid dose or not
		bIsValid = isValidDose(sText);
		
		// Prompts user to reinput if it is invalid
		if(!bIsValid)
		{
			printf("\n\033[1;38;5;202mDose should be the ff (First/Second/Third/Booster).\033[0m\n");
			printf("Enter again Dose: ");
			fgets(cArrBuffer, LINE_SIZE, stdin);
			
			// Check if the size is the right amount
			warnValidSize(cArrBuffer, 10, "Dose");
			
			// Proceed to finalize scan and post it in as official user input
			sscanf(cArrBuffer, "%[^\n]", sText);
			
		}
			
	}
}


/* 
	isValidSex returns 1 if the input text is a valid Sex from the choices given below, else 0
	
	@param sText is a string of characters that came from the user or file reading
	
	@return 1 if the input is a valid Sex input, 0 if not
*/
int
isValidSex(char sText[])
{

	int nFlag;
	
	// Lowers string to account all capital letter cases
	lowerStringCase(sText);
	
	// Default invalid input
	nFlag = 0;
	

	// Checks if the possible iterations and word semantics could be used by the user	
	if (!strcmp(sText, "male") || !strcmp(sText, "m") ||
		!strcmp(sText, "man") || !strcmp(sText, "guy"))
	{
		// Declares valid input
		nFlag = 1;
		
		// Overwrite original
		strcpy(sText, "Male");
	}
		
	else if (!strcmp(sText, "female") || !strcmp(sText, "f") ||
			 !strcmp(sText, "girl") || !strcmp(sText, "woman"))
	{
		nFlag = 1;
		strcpy(sText, "Female");
	}
					

	
	
	return nFlag;
	
	
}


/* 
	promptMoreForInvalid_Sex keeps prompting user until he/she enters a valid choice of Sex
	
	@param sText is a string of characters that came from the user or file reading
	
*/
void
promptMoreForInvalid_Sex(char sText[])
{
	

	
	int bIsValid;
	char cArrBuffer[LINE_SIZE];
	bIsValid = 0;
	
	//While user does not input valid Sex from choices, keep prompting
	while(!bIsValid)
	{
		// Checks if the sex is valid
		bIsValid = isValidSex(sText);
		
		// Feedbacks error and choices
		if(!bIsValid)
		{
			// Prompts User the input and relays error
			printf("\n\033[1;38;5;202mSex are only (M/F) (Male/Female).\033[0m\n");
			printf("Enter again Sex: ");
			fgets(cArrBuffer, LINE_SIZE, stdin);
			
			// Checks if the user inputs valid size as well
			warnValidSize(cArrBuffer, 10, "Sex");
			sscanf(cArrBuffer, "%[^\n]", sText);
			
		}
			
	}
}



/* 
	isValidVaccine returns 1 if the input text is a valid Vax from the choices given below, else 0
	
	@param sUserInput is a string of characters (max. 10) that came from the user or file reading
	
	@return 1 if the input is a valid Vax input, 0 if not
	Pre-condition: The sUserInput is at most 10 characters
*/
int
isValidVaccine(String10 sUserInput)
{
	int i;
	int nFlag;
	
	// All possible semantics of modern vaccines
	String10 sVaccines[20] = {"Covovax", "Pfizer", "Comirnaty",
							  "Moderna", "Spikevax", "Gamaleya",
							  "Sputnik", "Janssen", "Jcovden",
							  "Novavax", "Oxford AZ", "Vaxzevria",
							  "Covaxin", "Bharat", "Sinopharm",
							  "Covilo", "AZ", "AstraZen"};
	
	//To contain the uninterupted string case of the sVaccines
	String10 sTemp;
	
	//Lowers stringcase of the user's input
	lowerStringCase(sUserInput);
	
	//Default an invalid vaccine
	nFlag = 0;
	
	//Loops through all the sVaccines
	for (i = 0; i < 20; i++)
	{
		// sTemp helps the sVaccines be unaffected by lower String case
		strcpy(sTemp, sVaccines[i]);
		lowerStringCase(sTemp);
		
		// If similar we put the proper Vaccine StringCase and safely be a consistently valid vaccine
		if (!strcmp(sUserInput, sTemp))
		{
			nFlag = 1;
			strcpy(sUserInput, sVaccines[i]);
		}
			

	}
	
	return nFlag;
	
}


/* 
	promptMoreForInvalid_Vax keeps prompting user until he/she enters a valid choice of Vax
	
	@param sUserInput is a string of characters (max. 10) that came from the user or file reading
	
*/
void
promptMoreForInvalid_Vax(String10 sUserInput)
{
	int bIsValid;
	char cArrBuffer[LINE_SIZE];
	
	bIsValid = 0;
	
	// Prompt for the user for a valid Dose input
	while(!bIsValid)
	{
		// Check if the dose input is valid
		bIsValid = isValidVaccine(sUserInput);
		
		// If it is not valid then make user prompt again
		if(!bIsValid)
		{
			printf("\n\033[1;38;5;202mYour vaccine name is not verified or registered safe yet.\033[0m\n");
			printf("Enter again Vaccine Name: ");
			fgets(cArrBuffer, LINE_SIZE, stdin);
			
			// Checks if the size is correct
			warnValidSize(cArrBuffer, 10, "Vax Name");
			sscanf(cArrBuffer, "%[^\n]", sUserInput);
			
		}
			
	}
	
}


/* 
	validateTime returns whether or not the Time inputted by the user is valid
	
	@param sTypedTime - a string which contains the User's input of time
	@return 1 if the the Time input is valid, else 0
	Pre-Condition: The typed time is less than or equal to 6 always
	
*/
int
validateTime(String6 sTypedTime)
{
	int nHours, nMinutes;
	int nFlag;
	char cCol;
	
	sscanf(sTypedTime, "%d%c%d", &nHours, &cCol, &nMinutes);


	//Must be nonnegative
	if (nMinutes < 0 && nHours < 0)
		nFlag = 0;
		
	//Must be between 0-59, and 0-23
	else if (nMinutes < 60 && nHours < 24 && nMinutes >= 0 && nHours >= 0)
	
		nFlag = 1;
	
	//Means negative or not within bound
	else
		nFlag = 0;
		
	
	return nFlag;
	
}


/* 
	typeTime guides the user typing the input field of Time
	
	@param sTypedTime - a string which will contain User's input of time

	
*/
void
typeTime(String6 sTypedTime)
{
	int bIsDone;
	int bIsValid;
	int i = 0;
	char cSelected;
	
	//default empty before typing
	strcpy(sTypedTime, "");
	
	
	bIsDone = 0;		//User should be not done typing
	bIsValid = 1;		//User's date should be assumed as valid date
	
	while(strlen(sTypedTime) == 0)
	{
		
		
		
		while (!bIsDone)
		{

			cSelected = getch();			// Get key pressed
		
			
	        if ( cSelected == '\n'|| 		// Check if new line char
	             cSelected == '\r' )    	// Check if return char
			     	    						
			{
	            sTypedTime[i] = '\0';

	            bIsDone = 1;
	        }
	        
			//Back space logic and display on the console
	        else if(cSelected != '\b' && i != 2)
			{
				printf("%c", cSelected);
				sTypedTime[i] = cSelected;  //Assigns the char if its a non-terminating input type of char
	        	i += 1;						//increments index for readying next char input
				
			}
			
			//Adds auto adding to the specific position of 2 (puts ':')
	        else if(cSelected != '\b' && i == 2)
	        {
	        						//increments index for readying next char input
	        	printf(":");
	        	sTypedTime[i] = ':';
	        	i += 1;	
	        	printf("%c", cSelected);
	        	sTypedTime[i] = cSelected;
	        	i += 1;	
			}
			
			//Backspace logic	
			else if (cSelected == '\b' && i > 0)		//Perform a backkspace of characters by moving one char before and printing a space then backspace
			{
				i -= 1;					//decrements index index for overwriting previous character
				sTypedTime[i] = '\0';
				printf("\b \b");		//Backspace the one character and replace the character by a space, then backspace again
				
				
				if( i == 2 )
				{
					i -= 1;					// decrements index index for overwriting previous character
					printf("\b \b");		// Backspace the one character and replace the character by a space, then backspace again
					sTypedTime[i] = '\0';	// Null terminator to end string 
					

				}
								
			}
			
		}
		
		
	    bIsValid = validateTime(sTypedTime);
		
		if (strlen(sTypedTime) != 5)
		{
			printf("\n");																		//Since the previous loop takes the newline, we need to display one
			i = 0;																				//Resets position of getting characters
			bIsDone = 0;																		//Turns on While loop again to accept input
			printf("\n\033[1;38;5;202mERROR! Time input should be 5 characters and uses military time.\033[0m\n");	//Error feedback
			printf("TIME (HH:MM): ");
			strcpy(sTypedTime, "");																//Resets the value
		}
		else if (!bIsValid)
		{
			printf("\n");													//Since the previous loop takes the newline, we need to display one
			i = 0;															//Resets position of getting characters
			bIsDone = 0;													//Turns on While loop again to accept input
			printf("\n\033[1;38;5;202mERROR! Your time is not valid.\033[0m\n");						//Error feedback
			printf("TIME (HH:MM): ");
			strcpy(sTypedTime, "");											//Resets the value
		}
		
	}
}




/* 
	validateDate returns whether or not the Date inputted by the user is valid
	
	@param sTypedDate - a string which contains the User's input of date
	@return 1 if the the Date input is valid, else 0
	Pre-Condition: The typed date is less than or equal to 10

	
*/
int
validateDate(String10 sTypedDate)
{
	int nDay, nYear, nMonth;
	int nDaysInMonth;
	int bIsLeapYear;
	int nFlag;
	char cDash;
	
	// cDash consumes the dashes
	sscanf(sTypedDate, "%d%c%d%c%d", &nYear, &cDash, &nMonth, &cDash, &nDay);
	
	//Default is valid	
    nFlag = 1;
    
    //Impossible for the year to be 3 digits
    if (nYear < 1000)
    	nFlag = 0;
	else
	{
		// Check if the year is a leap year
		if ( (nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0) )
	    	bIsLeapYear = 1;
	    else
	    	bIsLeapYear = 0;
		
	}
	
	//Check if yser inputs wrong or empty
	if(!nMonth || !nYear || !nDay || nMonth > 12 || nMonth <= 0)
		nFlag = 0;

	else if ( nFlag )
	{
		//If february then apply conditions of leap eyar
		if (nMonth == 2) 
		{
			if (bIsLeapYear)
				nDaysInMonth = 29;
			else
				nDaysInMonth = 28;				
		}
        	
	    // Specific months that only have 30 days
		else if (nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) 
		
	        nDaysInMonth = 30;
	    
	    // Other months should be 31
		else 
	        
			nDaysInMonth = 31;
	    
	    // If the day is in correct input and month
		if (nDay >= 1 && nDay <= nDaysInMonth)
        	nFlag = 1;
		else
			nFlag = 0;	
	
	}
	
	
	return nFlag;
}


/* 
	typeDate guides the user typing the input field of Date
	
	@param sTypedDate - a string which will contain User's input of time

	
*/
void
typeDate(String10 sTypedDate)
{
	int bIsDone;
	int bIsValid;
	int i = 0;
	char cSelected;
	
	//default empty before typing
	strcpy(sTypedDate, "");
	
	
	bIsDone = 0;		//User should be not done typing
	bIsValid = 1;		//User's date should be assumed as valid date
	while(strlen(sTypedDate) == 0)
	{
		
		
		
		while (!bIsDone)
		{

			cSelected = getch();			// Get key pressed
		
			
	        if ( cSelected == '\n'|| 		// Check if new line char
	             cSelected == '\r' )    	// Check if return char
			     	    						
			{
	            sTypedDate[i] = '\0';

	            bIsDone = 1;
	        }
			//Back space logic and display on the console
	        else if(cSelected != '\b' && i != 4 && i != 7)
			{
				printf("%c", cSelected);
				sTypedDate[i] = cSelected;  //Assigns the char if its a non-terminating input type of char
	        	i += 1;						//increments index for readying next char input
				
			}
			
			//Adds auto adding dashes
	        else if(cSelected != '\b' && (i == 4 || i == 7))
	        {
	        						//increments index for readying next char input
	        	printf("-");
	        	sTypedDate[i] = '-';
	        	i += 1;	
	        	printf("%c", cSelected);
	        	sTypedDate[i] = cSelected;
	        	i += 1;	
			}
			
			//Backspace logic	
			else if (cSelected == '\b' && i > 0)		//Perform a backkspace of characters by moving one char before and printing a space then backspace
			{
				i -= 1;					//decrements index index for overwriting previous character
				sTypedDate[i] = '\0';
				printf("\b \b");		//Backspace the one character and replace the character by a space, then backspace again
				
				
				if(i==4 || i==7)
				{
					i -= 1;				//decrements index index for overwriting previous character
					printf("\b \b");	//Backspace the one character and replace the character by a space, then backspace again
					sTypedDate[i] = '\0';
					

				}
								
			}
			
		}
		
		
	    bIsValid = validateDate(sTypedDate);
		
		if (strlen(sTypedDate) != 10)
		{
			printf("\n");													//Since the previous loop takes the newline, we need to display one
			i = 0;															//Resets position of getting characters
			bIsDone = 0;													//Turns on While loop again to accept input
			printf("\n\033[1;38;5;202mERROR! Date format should be 10 characters.\033[0m\n");	//Error feedback
			printf("DATE (YYYY-MM-DD): ");
			strcpy(sTypedDate, "");											//Resets the value
		}
		else if (!bIsValid)
		{
			printf("\n");													//Since the previous loop takes the newline, we need to display one
			i = 0;															//Resets position of getting characters
			bIsDone = 0;													//Turns on While loop again to accept input
			printf("\n\033[1;38;5;202mERROR! Your date is not valid.\033[0m\n");						//Error feedback
			printf("DATE (YYYY-MM-DD): ");
			strcpy(sTypedDate, "");											//Resets the value
		}
		
	}
	
}


/* 
	typePassword guides the user typing the input field of password while also only showing "****"
	
	@param sTypedPass - a string which will contain User's input of password

*/
void
typePassword(String10 sTypedPass)
{
	
	int bIsDone = 0;
	int i = 0;
	char cSelected;
	
	//default empty before typing
	strcpy(sTypedPass, "");
	
	// While the user typed nothing
	while(strlen(sTypedPass) == 0)
	{
		printf("Password: ");
		
		// While the user hasn't pressed enter
		while (!bIsDone)
		{

			cSelected = getch();			// Get key pressed
	
			
	        if ( cSelected == '\n'|| 		// Check if new line char
	             cSelected == '\r' )    	// Check if return char
			     	    						
			{
	            sTypedPass[i] = '\0';
	            bIsDone = 1;
	        }
			
			//Back space logic and display on the console
	        else if(cSelected != '\b')
			{
				printf("*");
				sTypedPass[i] = cSelected;  //Assigns the char if its a non-terminating input type of char
	        	i += 1;						//increments index for readying next char input
				
			}
	        
			//Backspace logic	
			else if (cSelected == '\b' && i > 0)		//Perform a backkspace of characters by moving one char before and printing a space then backspace
			{
				i -= 1;									//decrements index index for overwriting previous character
				sTypedPass[i] = '\0';
				printf("\b \b");						//Backspace the one character and replace the character by a space, then backspace again
			}
			
		}
		
		if (strlen(sTypedPass) > 10)
		{
			printf("\n");													//Since the previous loop takes the newline, we need to display one
			i = 0;															//Resets position of getting characters
			bIsDone = 0;													//Turns on While loop again to accept input
			printf("\n\033[1;38;5;202mERROR! Passwords Can only take up to 10 characters.\033[0m\n");//Error feedback
			strcpy(sTypedPass, "");											//Resets the value
		}
		
	}

	
}

/* 			END					CHARACTER MANIPULATION TOOLS					*/	



/* 								USER ID UNIQUE VALIDATION					*/	

/* 
	validateAppID checks whether or not that Appointment ID inputted is valid or not
	
	@param stAppReqs - struct array of the database we will be checking
	@param nInput - ID inputted by the user
	@param nSize - The Size of the array of struct database
	
	@return 1 if the Appointment ID is unique, else 0
	
*/
int
validateAppID(struct appTag stAppReqs[], 
		   	  int nInput, 
		      int nSize)
{
	int nFlag;
	int i;
	
	nFlag = 1;
	
	// Loops through the size of the struct and gives 0 if it finds the appointment ID
	for(i=0;i< nSize; i++)	
		if(nInput == stAppReqs[i].nAppID)
		    nFlag = 0;
		
	return nFlag;
	
}


/* 
	validateUserID checks whether or not that User ID inputted is valid or not
	
	@param stUsers - struct array of the database we will be checking
	@param nInput - ID inputted by the user
	
	@return 1 if the User ID is unique, else 0
	
*/
int
validateUserID(struct userTag stUsers[], 
		       int nInput)
{
	int nFlag;
	int i;
	
	nFlag = 1;
	
	// Loops through all the userTag struct until it finds a similar ID for both admin and in database
	for(i=0;i< MAX_USERS; i++)	
		if(nInput == stUsers[i].nUID || nInput == ADMIN_ID)
		    nFlag = 0;
		
	return nFlag;
	
}





/*START--------------------------- APPOINTMENT RELATED FUNCTIONS --------------------------------------------------*/


/* 
	getAppData gets all proper values and store them into the struct array for Appointments
	
	@param sFileName - Is the name of the file that needs to be opened
	@param stAppReqs - struct array of the database we will be checking
	@param pIntSize - The address where to put the size of the struct array containing values
	

*/
void
getAppData(String30 sFileName, 
		   struct appTag stAppReqs[], 
		   int *pIntSize)
{
	
	int i;
	int nLineCnt;
	
	char cArrLineSelect[LINE_SIZE];
	FILE *fpOut;
	
	
	
	//Just delete till close
    fpOut = fopen(sFileName, "r");

	

	nLineCnt = 0;
	i =0;	
	while(fgets(cArrLineSelect, LINE_SIZE, fpOut) != NULL)
	{
		

		// Check for the newline character, dont replace the newline character that simply contains itself on the line
	    if (cArrLineSelect[strlen(cArrLineSelect) - 1] == '\n' && strlen(cArrLineSelect) != 1) 
	        // Replace the newline character with a null terminator
	    	cArrLineSelect[strlen(cArrLineSelect) - 1] = '\0';
	    
	    
		
		if (cArrLineSelect[0] != '\n')
		{
			
			// nLineCnt helps iterate through the formatting of the .txt which should be consistent
			switch(nLineCnt)

			{
				case 0:
					//%[^\n] format gets the string up until the new line
					sscanf(cArrLineSelect, "%d %d",  &stAppReqs[i].nAppID, &stAppReqs[i].nUID);
					break;
					
				case 1:
					sscanf(cArrLineSelect, "%[^\n]", stAppReqs[i].sName);

					break;
				case 2:
					sscanf(cArrLineSelect, "%10s", stAppReqs[i].sLoc);
					break;
				case 3:
					
					sscanf(cArrLineSelect, "%10s", stAppReqs[i].sVax);	

					break;
				case 4:
					sscanf(cArrLineSelect, "%10s", stAppReqs[i].sDate);
					break;
				case 5:
					sscanf(cArrLineSelect, "%6s", stAppReqs[i].sTime);
					break;
				case 6:
					sscanf(cArrLineSelect, "%10s", stAppReqs[i].sDose);
					break;

				
			}
			
			// Labels the next new line as the next LineCnt
			nLineCnt++;
			
			
		}
		
		
		//Block symbol that signifies first block of data would be the character '\n'
		else if (strlen(cArrLineSelect) == 1 && cArrLineSelect[0] == '\n')
		{
		
			i++;			//Get position ready for next user data in array
			nLineCnt = 0;	//Reset positioning line describer
			
		}	
			
		
		
		
		
		
		
	}
	
	//Updates the size to the pointer
	*pIntSize = i;	
	
	

	
	
	
	fclose(fpOut);
	
	

}


/* 
	saveAppToFile saves a struct data of an appointment to the sFileName
	
	@param sFileName - Is the name of the file that is to be stored on
	@param stApp - a struct of an appointment
	
	Pre-Condition - The file to be read exists
*/
void
saveAppToFile(String30 sFileName, 
			  struct appTag stApp)
{

	FILE *fpIn;
	//Saving data into file
    fpIn = fopen(sFileName, "a");

	
	//Puts data on file with formatting
	fprintf(fpIn, "%d %d\n", stApp.nAppID, stApp.nUID);
	fputs(stApp.sName, fpIn);
	fprintf(fpIn, "\n");
	fprintf(fpIn, "%s\n", stApp.sLoc);
	
	fprintf(fpIn, "%s\n", stApp.sVax);
	fprintf(fpIn, "%s \n", stApp.sDate);
	fprintf(fpIn, "%s\n", stApp.sTime);
	fprintf(fpIn, "%s\n", stApp.sDose);
	fprintf(fpIn, "\n");


	fclose(fpIn);   
}


/* 
	promptValidAppID keeps prompting user for valid Appointment ID until it is unique
	
	@return the value integer of the Appointment ID

*/
int
promptValidAppID()
{
	int nTempID;
	int bIsValidID;
	int nSize;
	struct appTag stAppReqs[MAX_REQS];
	
	
	getAppData("Appointment.txt", stAppReqs, &nSize);
	
	// Checks if the appointment ID is unique or not
	do
	{
		
		printf("Appointment ID: ");
		
		// Scans and checks for erroneous integers or input size
		scanID( &nTempID );
		
		// Then sees if the ID is valid or not
		bIsValidID = validateAppID(stAppReqs, nTempID, nSize);
		
		if(!bIsValidID)
			// Error feedback
			printf("\n\033[1;38;5;202mERROR! App ID %d has already been taken, try inputting a different one\033[0m\n", nTempID);
		
		
	}while(!bIsValidID);
	
	
	
	return nTempID;
	
}


/* 
	promptAppData prompts the User of all required fields to be filled for an Appointment
	
	@param stAppReqs - The struct array of the data of appointments
	@param nIndex - the location on the struct array
	@param nUID - The User ID accessing this appointment ID field input
	
	Pre-condition: The nUID is always at most 9 digits
*/
void
promptAppData(struct appTag stAppReqs[], 
			  int nIndex, 
			  int nUID)
{
	int i;


	char cArrBuffer[LINE_SIZE];
	

	

	i = nIndex;
	

	stAppReqs[i].nUID = nUID; 
	//User Count because when we start arrays it starts of 0-7, hence the size is 8, but that also means 8 index position is empty
	stAppReqs[i].nAppID = promptValidAppID();
	
	
	//%[^\n] this format specifies helps get string only till newline (inclusive of newline)
	printf("Name: ");
	
	// Get line of string first
	fgets(cArrBuffer, LINE_SIZE, stdin);
	
	// Validate the size
	warnValidSize(cArrBuffer, 20, "Name");
	
	// Properly pass it then to the struct database
	sscanf(cArrBuffer, "%[^\n]", stAppReqs[i].sName);


	printf("Location: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 10, "Location");
	sscanf(cArrBuffer, "%[^\n]", stAppReqs[i].sLoc);

	
	printf("Vaccine Name: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	sscanf(cArrBuffer, "%[^\n]", stAppReqs[i].sVax);
	promptMoreForInvalid_Vax(stAppReqs[i].sVax);
	
	printf("DATE (YYYY-MM-DD): ");
	typeDate(stAppReqs[i].sDate);
	printf("\n");


	printf("TIME (HH:MM): ");
	typeTime(stAppReqs[i].sTime);
	printf("\n");
	
	printf("Dose (1st/2nd/3rd/Booster): ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 10, "Dose");
	sscanf(cArrBuffer, "%[^\n]", stAppReqs[i].sDose);
	promptMoreForInvalid_Dose(stAppReqs[i].sDose);	
	

	
}


/* 
	overwriteAppReqsFile wipes the .txt on sFileName and writes all available data on struct array
	
	@param sFileName - The file where the appointments will be saved
	@param stAppReqs - Struct array containing all databases of appointments
	@param nSize - Size o the struct array

	
*/
void
overwriteAppReqsFile(String20 sFileName, 
			         struct appTag stAppReqs[], 
			         int nSize)
{
	int i;
	FILE *fpIn;
	
	fpIn = fopen(sFileName, "w");
	for (i=0; i<nSize; i++)
	{
		// Does not allow putting in the file if either one of the fields are empty
		if (strlen(stAppReqs[i].sName) != 0 && strlen(stAppReqs[i].sDate) == 10 ) 
		{
			//Puts data on file with formatting
			fprintf(fpIn, "%d %d\n", stAppReqs[i].nAppID, stAppReqs[i].nUID);
			fputs(stAppReqs[i].sName, fpIn);
			fprintf(fpIn, "\n");
			fprintf(fpIn, "%s\n", stAppReqs[i].sLoc);
			
			fprintf(fpIn, "%s\n", stAppReqs[i].sVax);
			fprintf(fpIn, "%s \n", stAppReqs[i].sDate);
			fprintf(fpIn, "%s\n", stAppReqs[i].sTime);
			fprintf(fpIn, "%s\n", stAppReqs[i].sDose);

			fprintf(fpIn, "\n");
		
		}
	
	
	}
	fclose(fpIn);
}


/* 
	deleteApp wipes the data on one struct in the array
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param nAppID - The Appointment ID to be deleted
	@param nSize - Size of the struct array

	
*/
void
deleteApp(struct appTag stAppReqs[], 
		  int nAppID, 
		  int nSize)
{
	int i;

	for (i=0; i<nSize; i++)
	{
		if (stAppReqs[i].nAppID == nAppID)
		
			// Clears entire structure and replacing each value with 0 or emoty string
			memset(&stAppReqs[i], 0, sizeof(stAppReqs[i]));
			
		
		
	}
	
	
	
	
}


/* 
	editSelectedApp edits a specific field depending on the user's input
	
	@param sUserInput - The user's category or property he chooses to modify
	@param stAppReqs - the struct array of all users' appointments 
	@param stUserApps - the struct array of one user's appointments
	@param pAppID - The Appointment ID the user wishes to modify
	@param nSize - The size of the struct array of the stUserApps
	@param pIsValidCateg - relay the status of checking the input if it is valid or not
*/
void
editSelectedApp(String30 sUserInput,
			 	struct appTag stAppReqs[], 
				struct appTag stUserApps[],
			 	int *pAppID,
			 	int nSize,
				int *pIsValidCateg)
{
	
	int i;

	
	char sLine[LINE_SIZE];

	
	lowerStringCase(sUserInput);
	
	
	// Default valid
	*pIsValidCateg = 1;
	
	
	//This is for User's input of what he wants to edit
	//Replaces potential new line ('\n') included in the fgets
	if(sUserInput[strlen(sUserInput) - 1] == '\n' )
		sUserInput[strlen(sUserInput) - 1] = '\0';
		
	//To Narrow down words the user could instead select
	removeSpaces(sUserInput);
	for (i = 0; i < nSize; i++)
	{
		//Checks if the user's selected app ID is the same or found in the struct array
		if ( *pAppID == stUserApps[i].nAppID)
		{
			
			// validates each user's input
			if(!strcmp("all", sUserInput))
			{
				// Delete the app ID for a chance that the user can import it again
				deleteApp(stAppReqs, stUserApps[i].nAppID, nSize);
				overwriteAppReqsFile("Appointment.txt", stAppReqs, nSize);
				promptAppData(stUserApps, i, stUserApps[i].nUID);
				
				// Updates current App ID
				*pAppID = stUserApps[i].nAppID;
				printf("\n\033[1;32mSuccessfully edited all.\033[0m\n\n");
				
			}
			else if(!strcmp("aid", sUserInput) 	||
				    !strcmp("appid", sUserInput) ||
				    !strcmp("ai", sUserInput)	||
				    (sUserInput[0] == 'a' && strlen(sUserInput) == 1))
			{

				printf("New Value for ");
				
				// Prompts user for valid app ID while verifying if it is taken or not
				stUserApps[i].nAppID = promptValidAppID();
				
				//Change appointment ID
				*pAppID = stUserApps[i].nAppID;
				
				printf("\n\033[1;32mSuccessfully edited Appointment ID.\033[0m\n\n");
				
			}
			
			else if(!strcmp("name", sUserInput) ||
					sUserInput[0] == 'n')
			{
				
				//Input validation, fgets to buffer all characters, check the size, only then strcpy
				printf("Change your Name: ");		
				fgets(sLine, LINE_SIZE, stdin);				
				warnValidSize(sLine, 20, "Name");
				strcpy(stUserApps[i].sName, sLine);			
				printf("\n\033[1;32mSuccessfully edited Name.\033[0m\n\n");
			}
			
			else if (!strcmp("location", sUserInput) || 
					 !strcmp("loc", sUserInput) ||
					 !strcmp("place", sUserInput) ||
					 sUserInput[0] == 'l')
					 
			{
				//Input validation, fgets to buffer all characters, check the size, only then strcpy
				printf("New Value for Dose Location: ");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Location");
				sscanf(sLine, "%s", stUserApps[i].sLoc);
				printf("\n\033[1;32mSuccessfully edited Location.\033[0m\n\n");
			}
			
			//Else if of ways the user could interpret
			else if (!strcmp("vax", sUserInput) || 
					 !strcmp("vaccine", sUserInput) ||
					 !strcmp("vaxname", sUserInput) ||
					 !strcmp("vname", sUserInput) ||
					 !strcmp("vn", sUserInput) ||
					 !strcmp("vx", sUserInput) ||
					 !strcmp("vacc", sUserInput) ||
					 !strcmp("vac", sUserInput) ||
					 !strcmp("vacs", sUserInput) ||
					 !strcmp("vaxine", sUserInput) ||
					 sUserInput[0] == 'v'					
					)
			{
				// Input validation, fgets to buffer all characters, check the size, only then strcpy
				// Input validation of correct vaccine brand
				printf("New value for your Vaccine Name: ");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Vax Name");
				sscanf(sLine, "%s", stUserApps[i].sVax);
				promptMoreForInvalid_Vax(stUserApps[i].sVax);
				printf("\n\033[1;32mSuccessfully edited Vaccine Name.\033[0m\n\n");
			}
									
			else if (!strcmp("date", sUserInput) || 
				 	 !strcmp("dt", sUserInput))
			{
				// Input validation, Date format is guided for convenience
				printf("New value for your dose Date: ");
				typeDate(stUserApps[i].sDate);
				printf("\n");
				printf("\n\033[1;32mSuccessfully edited Date.\033[0m\n\n");
				
			}

			else if (!strcmp("time", sUserInput) || 
					 !strcmp("tim", sUserInput) ||
					 !strcmp("t", sUserInput) ||
					 sUserInput[0] == 't'					
					)
			{
				// Input validation, Time format is guided for convenience
				printf("New value for dose Time (24-hour Ex: 15:30 which is 3:30 pm): ");
				typeTime(stUserApps[i].sTime);
				printf("\n");
				printf("\n\033[1;32mSuccessfully edited Time.\033[0m\n\n");
				
			}			

			
			
			
			else if(!strcmp("dose", sUserInput) ||
					!strcmp("ds", sUserInput) || 
					!strcmp("dos", sUserInput) ||
					!strcmp("do", sUserInput)
					)
			{
				
				// Input validation, fgets to buffer all characters, check the size, only then strcpy
				// Input validation, prompt more if not in choices
				printf("New value for Dose (First/Second/Third/Booster): \n");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Dose");
				sscanf(sLine, "%s", stUserApps[i].sDose);
				promptMoreForInvalid_Dose(stUserApps[i].sDose);
				printf("\n\033[1;32mSuccessfully edited Dose.\033[0m\n\n");
				
				
			}
			else
			{
				// Provide Feedback of not correct choice
				printf("\n\033[1;38;5;202mERROR! Please only enter from the input choices above colored yellow.\033[0m\n\n");
				
				// The input is invalid
				*pIsValidCateg = 0;
			}	
				
			//Give time for user to read
			system("PAUSE");
			
	
			
			
		}

		
	}
	
	
}


/* 
	resetStructAppReqs resets all appoinment requests in the struct data type
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param pIntSize - pointer where the function will give the resetted size of the struct array

	
*/
void
resetStructAppReqs(struct appTag stAppReqs[],
				   int *pIntSize)
{


	
	
 	int i;
 	
 	// Sets up the resetted/default values of the struct
 	struct appTag sReset = {-1, -1, "", "", "", "", "", ""};
 	
 	for (i = 0;  i< *pIntSize; i++)
 	
 		// Overwrites the empty value to the struct
 		stAppReqs[i] = sReset;
	

		
	
	// Resets the size
	*pIntSize = 0;
 	
}


/* 
	arrangeAppReqs arranges the Appointment IDs in ascending Order
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param nSize - Size of the struct array

	
*/
void
arrangeAppReqs(struct appTag stAppReqs[],
			   int nSize)
{
	int i;
	int j;

	
	struct appTag stTemp;
	
	
	// Below is a form of Insertion sort
    for (i = 1; i < nSize; i++) {
        stTemp = stAppReqs[i];
        
        
        j = i - 1;
        
        //Swap elements continuously as long as the index position of j is bigger than what is to the right
        while (j >= 0 && stAppReqs[j].nAppID > stTemp.nAppID) {
        	//Swap to right
            stAppReqs[j + 1] = stAppReqs[j];
            j--;
        }
        
		//Final swap even if either the  while loop is over or the UID of the same elements is not the same
		if ( !(j >= 0 && stAppReqs[j].nAppID == stTemp.nAppID) ) {
			
			//Finally insert the selected struct piece on that position
            stAppReqs[j + 1] = stTemp;
        }
    
    }
	
	
}





/* 
	displayOneAppData finds and displays one appointment data depending on the App ID
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param nSize - Size of the struct array
	@param nAppID - The Appointment ID to be found and displayed

*/
void
displayOneAppData(struct appTag stAppReqs[], 
				  int nSize, 
				  int nAppID)
{
	int i;
	
	//Iterates and searches through to find and display
	for (i=0; i<nSize; i++)
	{
		// Only shows the App ID that is needed to show
		if (stAppReqs[i].nAppID == nAppID)
		{
			// 033[1;38;5;202m Is the color orange
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[44m\033[1;31m%30s \033[1;38;5;202m%-10d%20s\033[0m|\n", "User ID: " , stAppReqs[i].nUID, "");
			printf("          +-------------------------------------------------------------+\n");  
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[1;34m%30s \033[1;36m%-10d%20s\033[0m|\n", "Appointment ID: " , stAppReqs[i].nAppID, "");
			printf("          +-------------------------------------------------------------+\n");  
		
			printf("          | %s |\n", "      /   /                                     /   /      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      |   |- - - - - - - - - - - - - - - - - - -|   |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |\033[0;33m        A P P O I N T M E N T        \033[0m| O |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |\033[0;33m             R E P O R T             \033[0m| O |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |                +====+               | O |      ");
			printf("          | %s |\n", "      | O |                |(::)|               | O |      ");
			printf("          | %s |\n", "      | O |                | )( |               | O |      ");
			printf("          | %s |\n", "      | O |                |(..)|               | O |      ");
			printf("          | %s |\n", "      | O |- - - - - - -   +====+  - - - - - - -| O |      ");
			printf("          | %s |\n", "      |   |                                     |   |      ");

			
			printf("          +------------------------------+------------------------------+\n");
			printf("          |%30s| \033[0;33m%-20s\033[0m %8s|\n", "Name: ", stAppReqs[i].sName, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Dose Location: ", stAppReqs[i].sLoc, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Vaccine Name: ", stAppReqs[i].sVax, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Date: ", stAppReqs[i].sDate, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Time: ", stAppReqs[i].sTime, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Dose: ", stAppReqs[i].sDose, "");
			printf("          +------------------------------|------------------------------+\n");
			


		}
	}
	printf("\n\n");

}


/* 
	displayAllAppData finds and displays one appointment data depending on the App ID
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param nSize - Size of the struct array
	@param nAppID - The Appointment ID to be found and displayed

	
*/
void
displayAllAppData(struct appTag stAppReqs[], 
				  int nSize)
{
	

	
	
	int i;
	for (i=0; i<nSize; i++)
	{
		
		if (strlen(stAppReqs[i].sName) != 0)
		{

			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[44m\033[1;31m%30s \033[1;38;5;202m%-10d%20s\033[0m|\n", "User ID: " , stAppReqs[i].nUID, "");
			printf("          +-------------------------------------------------------------+\n");  
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[1;34m%30s \033[1;36m%-10d%20s\033[0m|\n", "Appointment ID: " , stAppReqs[i].nAppID, "");
			printf("          +-------------------------------------------------------------+\n");  
		
			printf("          | %s |\n", "      /   /                                     /   /      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      |   |- - - - - - - - - - - - - - - - - - -|   |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |\033[0;33m        A P P O I N T M E N T        \033[0m| O |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |\033[0;33m             R E P O R T             \033[0m| O |      ");
			printf("          | %s |\n", "      | O |                                     | O |      ");
			printf("          | %s |\n", "      | O |                +====+               | O |      ");
			printf("          | %s |\n", "      | O |                |(::)|               | O |      ");
			printf("          | %s |\n", "      | O |                | )( |               | O |      ");
			printf("          | %s |\n", "      | O |                |(..)|               | O |      ");
			printf("          | %s |\n", "      | O |- - - - - - -   +====+  - - - - - - -| O |      ");
			printf("          | %s |\n", "      |   |                                     |   |      ");

			
			printf("          +------------------------------+------------------------------+\n");
			printf("          |%30s| \033[0;33m%-20s\033[0m %8s|\n", "Name: ", stAppReqs[i].sName, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Dose Location: ", stAppReqs[i].sLoc, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Vaccine Name: ", stAppReqs[i].sVax, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Date: ", stAppReqs[i].sDate, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Time: ", stAppReqs[i].sTime, "");
			printf("          +------------------------------|------------------------------+\n");
			printf("          |%30s| \033[0;33m%-10s\033[0m %18s|\n", "Dose: ", stAppReqs[i].sDose, "");
			printf("          +------------------------------|------------------------------+\n");
			
			
			if(nSize != 1)
			{
				printf("\n\n");
				printf("\033[32m-----------------------------------------------------------------------------------------------------\033[0m\n");  
				
			}
		
			printf("\n\n");
		}
		
		
	}
	
	
						       

}		


/* 
	getUserOnlyApp finds and modifies a struct to contain only appointments set by a particular User ID
	
	@param stAppReqs - Struct array containing all databases of appointments
	@param stUserAppReqs - Struct array that will contain databases of appointments with respect to User ID
	@param nSize - Size of the struct array of stAppReqs
	@param pIntNewSize - pointer to will contain the size of the struct of stUserAppReqs
	@param nUID - The User ID of the user

*/
void
getUserOnlyApp(struct appTag stAppReqs[], 
			   struct appTag stUserAppReqs[], 
			   int nSize, 
			   int *pIntNewSize, 
			   int nUID)
{
	int i, j;
	
	//Resets the Size
	*pIntNewSize = 0;
	
	
	j = 0;
	for (i=0; i< nSize; i++)
	{
		//Checks if the User ID is aligned on the availables data in stAppReqs
		if (nUID == stAppReqs[i].nUID)
		{
		
			stUserAppReqs[j] = stAppReqs[i];
			
			// Gets the next index position of user
			j++;
			
			//Adds the size
			*pIntNewSize += 1;
		
		}
		
		
	}
	
}


/* 
	findIndex_MainAppReqs finds the index of where the Appointment ID of a particular struct is found on stAppReqs
						  which contain all structs of appointments from all users
	
	@param stAppReqs - Struct array containing all database of appointments
	@param nSize - Size of the struct array of stAppReqs
	@param nCurrentAppID - The User ID of the user

	@return the index of where the current Appointment ID is located in struct of all databases
	Pre-condition: The nCurrentAppID is always validly found
*/
int
findIndex_MainAppReqs( struct appTag stAppReqs[], 
					   int nSize,
					   int nCurrentAppID)
					   
{
	int i;
	
	int nFlag;
	
	// Set Flag default 
	nFlag = 0;
	
	for(i=0; i<nSize; i++)
		//Compar if the App ID and Current App ID is the same
		if(stAppReqs[i].nAppID == nCurrentAppID)
			//Gives index of where the appointment ID could be
			nFlag = i;

	return nFlag;
}


/* 
	swapStructs puts the content of a struct identical to the other as means of overwriting the stAppReqs
				which contains database of all appointments
	
	@param stAppReqs - Struct array containing all database of appointments
	@param stUserAppReqs - Struct array containing user's database of appointments
	@param nInd_StAppReqs - Index of where certain AppID of the User's appointment data is on the stAppReqs containing all user's app data
	@param nUserAppID - User's selected app ID to be swapped and overwrited towards the stAppReqs
	@param nSize - Size of the stAppReqs
	
	
	Pre-condition: nInd_StAppReqs is always valid integer for accessing arrays
*/
void
swapStructs(struct appTag stAppReqs[], 
			struct appTag stUserAppReqs[],
			int nInd_StAppReqs, 
			int nUserAppID,
			int nSize)
{
	int i;
	for(i = 0; i < nSize; i++)
		if(nUserAppID == stUserAppReqs[i].nAppID)
		    stAppReqs[nInd_StAppReqs] = stUserAppReqs[i];
	
}


/*END------------------------------ APPOINTMENT RELATED FUNCTIONS --------------------------------------------------*/





/*START--------------------------- USER DATA RELATED FUNCTIONS --------------------------------------------------*/

/* 
	isValidUserDetails checks if the user and password is correct depending on the availble struct data of stusers
	
	@param stUsers - Struct array containing all database of users
	@param nUID - Struct array containing user's database of appointments
	@param nSize - Size of the stAppReqs
	@param sPass - The string of password
	
	Pre-condition: nUID is valid and at most 9 digits
*/
int
isValidUserDetails(struct userTag stUsers[],
				   int nUID,
				   int nSize,
				   String10 sPass)
{
	int i;
	int nFlag;
	
	// Default invalid login
	nFlag=0;
	
	//Loops through all struct Data 
	for(i=0; i < nSize; i++)
	{
		// Checks if user's given input are at least one of the structs in the stUsers
		if (!strcmp(stUsers[i].sPassword, sPass) && 
			stUsers[i].nUID == nUID)
		{
			//Implies the login is successful
			printf("\n\033[1;32mLogin Successful!\033[0m Welcome \033[1;36m%s\033[0m! (User \033[1;33m%d\033[0m)\n", stUsers[i].sName, nUID);
			system("PAUSE");
			nFlag = 1;
		}
			
		
	}
	return nFlag;
	
	
}


/* 
	getUserData extracts all data of the available users data in the sFileName
	
	@param sFileName - Name of the file where stUsers will get its data
	@param stUsers - Struct array containing user's database of personal info and status
	@param pIntSize - Size of available user data

*/
void
getUserData(String30 sFileName, 
			struct userTag stUsers[], 
			int *pIntSize)
{
	
	int i;
	int nLineCnt;
	
	char cArrLineSelect[LINE_SIZE];
	FILE *fpOut;
	
	
	
	
	
	//Just delete till close
    fpOut = fopen(sFileName, "r");


	


	nLineCnt = 0;
	i =0;	
	while(fgets(cArrLineSelect, LINE_SIZE, fpOut) != NULL)
	{

		// Check for the newline character, dont replace the newline character that simply contains itself on the line
	    if (cArrLineSelect[strlen(cArrLineSelect) - 1] == '\n' && strlen(cArrLineSelect) != 1) {
	      // Replace the newline character with a null terminator
	      cArrLineSelect[strlen(cArrLineSelect) - 1] = '\0';
	    }
		
		if (cArrLineSelect[0] != '\n')
		{
			switch(nLineCnt)
			{
				case 0:
					//%[^\n] format gets the string up until the new line
					sscanf(cArrLineSelect, "%d %[^\n]",  &stUsers[i].nUID, stUsers[i].sPassword);
					break;
				case 1:
					strcpy(stUsers[i].sName, cArrLineSelect);
					break;
				case 2:
					strcpy(stUsers[i].sAddress, cArrLineSelect);
					break;
				case 3:
					sscanf(cArrLineSelect, "%"PRId64, &stUsers[i].nContact);

					break;
				case 4:
					strcpy(stUsers[i].sSex, cArrLineSelect);
					break;
				case 5:
					sscanf( cArrLineSelect, " %10s %s %s ", stUsers[i].stDose1.sLoc, stUsers[i].stDose1.sDate, stUsers[i].stDose1.sName);
					break;
				case 6:
					sscanf( cArrLineSelect, " %10s %s %s ", stUsers[i].stDose2.sLoc, stUsers[i].stDose2.sDate, stUsers[i].stDose2.sName);
					break;
				case 7:
					sscanf( cArrLineSelect, " %10s %s %s ", stUsers[i].stBoost.sLoc, stUsers[i].stBoost.sDate, stUsers[i].stBoost.sName );
					break;
				
			}
			nLineCnt++;
			
			
		}
		
		
		//Block symbol that signifies first block of data would be the character '\n'
		else if (strlen(cArrLineSelect) == 1 && cArrLineSelect[0] == '\n')
		{
		
			i++;	//Get position ready for next user data in array
			nLineCnt = 0;	//Reset positioning
			
		}	
			
		
		
		
		
		
		
	}
	*pIntSize = i;	
	
	

	
	
	
	fclose(fpOut);
	
	

}


/* 
	saveUserToFile saves a struct via appending it to sFileName
	
	@param sFileName - Name of the file where stUsers will get its data
	@param stUser - Struct of a user's data

*/
void
saveUserToFile(String30 sFileName, struct userTag stUser)
{
	
	FILE *fpIn;
	//Saving data into file
    fpIn = fopen(sFileName, "a");

	
	
	//Puts data on file with formatting
	fprintf(fpIn, "%d ", stUser.nUID);
	fputs(stUser.sPassword, fpIn);
	fprintf(fpIn, "\n");
	fputs(stUser.sName, fpIn);
	fprintf(fpIn, "\n");
	fputs(stUser.sAddress, fpIn);
	fprintf(fpIn, "\n");	
	fprintf(fpIn, "%011"PRId64, stUser.nContact);
	fprintf(fpIn, "\n");
	fputs(stUser.sSex, fpIn);
	fprintf(fpIn, "\n");

	fprintf(fpIn, "%s %s %s\n", stUser.stDose1.sLoc,
								stUser.stDose1.sDate, 
						        stUser.stDose1.sName);
	
	// If the date field is empty then it should not be filled in the file					        
	if (strlen(stUser.stDose2.sDate) != 0)
	
		fprintf(fpIn, "%s %s %s\n", stUser.stDose2.sLoc,
									stUser.stDose2.sDate, 
						        	stUser.stDose2.sName);
	if (strlen(stUser.stBoost.sDate) != 0)
		fprintf(fpIn, "%s %s %s\n", stUser.stBoost.sLoc,
									stUser.stBoost.sDate, 
						        	stUser.stBoost.sName);
	fprintf(fpIn, "\n");	

	fclose(fpIn);   
}


/* 
	promptValidUserID repeatedly prompts user until the provided ID is valid
	
	@param stUsers - Data of all user's personal information and data
	
	@return the ID that will be the User's valid ID
	

*/
int
promptValidUserID(struct userTag stUsers[])
{
	int nTempID;
	int bIsValidID;


	
	do
	{
		
		// Scan the user's input
		printf("User ID: ");
		scanID(&nTempID);
		bIsValidID = validateUserID(stUsers, nTempID);
		
		// When it is stil invalid then state to user that it was taken
		if(!bIsValidID)
		
			printf("\n\033[1;38;5;202mERROR! User ID %d has already been taken, try inputting a different one\033[0m\n", nTempID);
		
		
	}while(!bIsValidID);
	
	return nTempID;
	
}


/* 
	promptContact repeatedly prompts user until the provided Contact is valid
	
	@param stUsers - Data of all user's personal information and data
	@param nIndex - Index of the stUsers currently being filled in by the Contact
		
	Pre-condition: nIndex is a valid access to an array
*/
void
promptContact(struct userTag stUsers[], 
			  int nIndex)
{
	int nCount;
	char sLine[LINE_SIZE];
	
	do
	{
		
		// Prompt user for contact
		printf("Contact: ");
		fgets(sLine, LINE_SIZE, stdin);
		sscanf(sLine, "%"PRId64, &stUsers[nIndex].nContact);
		
		nCount = countDigits(stUsers[nIndex].nContact);
		
		if (nCount != 10)
		
			printf("\n\033[1;38;5;202mERROR! Mobile numbers should be 10 digits, remove prefixes.\033[0m\n");
		
		
		
	}while(nCount!=10);
	
}


/* 
	promptDoseData forms the struct format and asks input in format of dose type structs
	
	@param pStDose - pointer to the address of where the dose data struct is
		
*/
void
promptDoseData(struct doseTag *pStDose)
{
	
	char cArrBuffer[LINE_SIZE];

	printf("LOCATION: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 10, "LOCATION");
	sscanf(cArrBuffer, "%[^\n]", pStDose->sLoc);

	printf("DATE (YYYY-MM-DD): ");
	typeDate(pStDose->sDate);
	printf("\n");

	printf("Vaccine NAME: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 10, "Vaccine NAME");
	sscanf(cArrBuffer, "%[^\n]", pStDose->sName);
	promptMoreForInvalid_Vax(pStDose->sName);
	
	

	
}


/* 
	promptUserData prompts user of all the required and optional fields for registering user data
	
	@param stUsers - Data of all user's personal information and data
	@param nIndex - Index of the stUsers currently being filled in by the Contact
		
*/
void
promptUserData(struct userTag stUsers[], 
			   int nIndex)
{
	int i;

	
	char cUserInputD;
	char cUserInputB;
	char cArrBuffer[LINE_SIZE];

	
	// Shortens name of nIndex
	i = nIndex;
	
	

	//User Count because when we start arrays it starts of 0-7, hence the size is 8, but that also means 8 index position is empty
	stUsers[i].nUID = promptValidUserID(stUsers);
	

	
	typePassword(stUsers[i].sPassword);
	printf("\n");

	
	//%[^\n] this format specifies helps get string only till newline
	printf("Name: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 20, "Name");
	sscanf(cArrBuffer, "%[^\n]", stUsers[i].sName);

	
	//Scans address and warns if size goes over
	printf("Address: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 30, "Address");
	sscanf(cArrBuffer, "%[^\n]", stUsers[i].sAddress);
	
	promptContact(stUsers, i);

	
	printf("Sex: ");
	fgets(cArrBuffer, LINE_SIZE, stdin);
	warnValidSize(cArrBuffer, 10, "Sex");
	sscanf(cArrBuffer, "%[^\n]", stUsers[i].sSex);
	promptMoreForInvalid_Sex(stUsers[i].sSex);

	
	//Vaccination INFO
	printf("\n\033[1;36mFirst Dose Data:\033[0m \n");
	promptDoseData(&stUsers[i].stDose1);
	
	
	// Prompts the optional Second Dose	
	printf("Would you like to fill in your info of second dose? (Y/N) \n");
	scanYesNo(&cUserInputD);
	
	
	if(cUserInputD == 'Y' || cUserInputD == 'y')
	{

		printf("\n\033[1;36mSecond Dose Data: \033[0m\n");
		promptDoseData(&stUsers[i].stDose2);	
		
	}


	// Prompts the optional booster dose
	printf("Would you like to fill in your info of booster? (Y/N) \n");

	scanYesNo(&cUserInputB);
	
	if(cUserInputB == 'Y' || cUserInputB == 'y')
	{
	

		printf("\n\033[1;36mBooster Data: \033[0m\n");
		promptDoseData(&stUsers[i].stBoost);
		
		
	}
		
	
	
	

	

	
}


/* 
	editDoseStruct checks user input of which field of the booster/second/first dose to edit, then prompt it
	
	@param sDoseLabel - Label of the dose user is editing
	@param sUserInput - What category of the dose should the user edit
	@param pStDose - pointer address to the data of the user's dose info
		
*/
void
editDoseStruct(String30 sDoseLabel,
			   String10 sUserInput, 
		       struct doseTag *pStDose)
{

	char sLine[LINE_SIZE];
	
	String80 sTemp;
	
	// Seperate a copy of the label
	strcpy(sTemp, sDoseLabel);
	
	// lowers string to easily account for capital letters
	lowerStringCase(sUserInput);
	
	
	// Prompting all fields of the Dose Data
	if (!strcmp("all", sUserInput))
	{
		printf("\n\033[1;36mNew Value for your %s Dose Data: \033[0m", sDoseLabel);
		promptDoseData(pStDose);
		
	}
	
	// Prompt only the date change
	else if (!strcmp("date", sUserInput) ||
			 !strcmp("dt", sUserInput) ||
			 sUserInput[0] == 'd')
	{
		printf("New Value for your %s Dose Date (YYYY-MM-DD): ", sDoseLabel);
		typeDate(pStDose->sDate);
		printf("\n");
		
	}
	
	// Prompt only the vaccine name change
	else if (!strcmp("name", sUserInput) ||
			 !strcmp("vax", sUserInput) ||
			 sUserInput[0] == 'n')
	{
		
		// Scans input
		printf("New Value for your %s Dose Vaccine Name: ", sDoseLabel);
		fgets(sLine, LINE_SIZE, stdin);
		
		// Scans till valid size
		warnValidSize(sLine, 10, strcat(sTemp, " Dose Name") );
		sscanf(sLine, "%[^\n]", pStDose->sName);
		
		// Prompts till valid vax brand
		promptMoreForInvalid_Vax(pStDose->sName);
	}
	
	else if (!strcmp("location", sUserInput) || 
			 !strcmp("loc", sUserInput) ||
			 !strcmp("place", sUserInput) ||
			 sUserInput[0] == 'l')
	{
		printf("New Value for your %s Dose Location: ", sDoseLabel);
		fgets(sLine, LINE_SIZE, stdin);
		warnValidSize(sLine, 10, "Location");
		sscanf(sLine, "%[^\n]", pStDose->sLoc);
	}
	
	
}


/* 
	deleteUser removes the data of a particular User struct depending on the given UID
	
	@param stUsers - Data of all user's personal information and data
	@param nUID - the user ID to be deleted
	@param nSize - size of the struct array of sUsers
	
*/
void
deleteUser(struct userTag stUsers[], 
		   int nUID, 
		   int nSize)
{
	int i;

	for (i=0; i<nSize; i++)
	
		if (stUsers[i].nUID == nUID)
		
			// Clears entire structure and replacing each value with 0
			memset(&stUsers[i], 0, sizeof(stUsers[i]));
			
		
		
	
	
	
	
	
}


/* 
	editSelectedUser checks user input of which field of the booster dose to edit, then prompt it
	
	@param sUserInput - What category of the dose should the user edit
	@param stUsers - Data of all user's personal information and data
	@param pUID - User ID of the user that will contain User ID of the person which was selected for editing
	@param nSize - Size of struct array of stUsers
	@param pBoolIsValidChoice - controls the while loop to stop checking for  validation as the user already inputs the correct choice
	
	
*/
void
editSelectedUser(String10 sUserInput, 
			 	 struct userTag stUsers[],
			 	 int *pUID,
			 	 int nSize,
				 int *pBoolIsValidChoice)
{
	
	int i;

	
	char sLine[LINE_SIZE];
	String10 sSubInfo;

	
	
	
	// Lower cases the user's input of what category to edit
	lowerStringCase(sUserInput);
	*pBoolIsValidChoice = 1;
	
	//Replaces potential new line ('\n') included in the fgets
	if(sUserInput[strlen(sUserInput) - 1] == '\n' )
		sUserInput[strlen(sUserInput) - 1] = '\0';
	
	for (i = 0; i < nSize; i++)
	{
		
		// Finds first the UID the person wants to be edited
		if ( *pUID == stUsers[i].nUID)
		{
			
			// Prompts all fields
			if(!strcmp("all", sUserInput))
			{
				deleteUser(stUsers, stUsers[i].nUID, nSize);
				// Prompts data and the index of where it should overwrite
				promptUserData(stUsers, i);
				
				// Append to Users.txt
				saveUserToFile("Users.txt", stUsers[i]);
				
				//Updates current UID if ever updated
				*pUID = stUsers[i].nUID;
				
			}
			else if(!strcmp("uid", sUserInput) || 
					!strcmp("id", sUserInput) ||
					!strcmp("u", sUserInput))
			{
				// Prompt for valid unique ID
				printf("New Value for ");
				stUsers[i].nUID = promptValidUserID(stUsers);
				
				
			}
			
			else if(!strcmp("password", sUserInput) ||
					!strcmp("pass", sUserInput) ||
					!strcmp("p", sUserInput))
			{
				//Prompt for valid password with proper asterisks printf on console
				printf("New Value for your ");
				typePassword(stUsers[i].sPassword);	

				
			}
			else if(!strcmp("name", sUserInput) ||
					!strcmp("n", sUserInput))
			{
				
				// Prompt name with string length validation
				printf("New Value for your Name: ");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 20, "Name");
				strcpy(stUsers[i].sName, sLine);
				
				
			}
			
			
			else if(!strcmp("address", sUserInput) ||					//C Check if user entered entire word
					!strcmp("addr", sUserInput) ||						// Check if user entered word partially
					!strcmp("add", sUserInput) ||
					(sUserInput[0] == 'a' && strlen(sUserInput) == 1)) // Check if it has one character only
			{
				printf("New Value for your Address: ");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 30, "Address");
				strcpy(stUsers[i].sAddress, sLine);
			}
			
			
			else if(!strcmp("contact", sUserInput) ||
					!strcmp("phone", sUserInput) ||
					!strcmp("c", sUserInput))
			{
				printf("New Value for your ");
				
				// Prompt the 11-Digit Phone number
				promptContact(stUsers, i);
			}
			
			
			else if(!strcmp("sex", sUserInput) ||
					sUserInput[0] == 's')
			{
				printf("New Value for your Sex: ");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Sex");
				sscanf(sLine, "%[^\n]", stUsers[i].sSex);
				
				// Validate till it is Male/Female
				promptMoreForInvalid_Sex(stUsers[i].sSex);
			}
			
			
			
			else if(!strcmp("dose1", sUserInput) ||
					!strcmp("d1", sUserInput))
			{
				// Prompt which to edit in the first dose
				printf("What info in First Dose? \n");
				printf("\033[1;33m'Name', 'Date', 'Location'\033[0m\n");
				fgets(sLine, LINE_SIZE, stdin);
				
				//Validate the size
				warnValidSize(sLine, 10, "First Dose");
				sscanf(sLine, "%[^\n]", sSubInfo);
				
				// Checks which field the user wanted to edit in first dose
				editDoseStruct("First", sSubInfo, &stUsers[i].stDose1);
				
			}
			
			// Makes sure first that the data for Dose 2 has info on them
			else if((!strcmp("dose2", sUserInput) ||
					!strcmp("d2", sUserInput) ) && 
					strlen(stUsers[i].stDose2.sDate) != 0 && 
				    strlen(stUsers[i].stDose2.sName) != 0 && 
				    strlen(stUsers[i].stDose2.sLoc) != 0)
			{
				printf("What info in Second Dose? \n");
				printf("\033[1;33m'Name', 'Date', 'Location'\033[0m\n");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Second Dose");
				sscanf(sLine, "%[^\n]", sSubInfo);
				editDoseStruct("Second", sSubInfo, &stUsers[i].stDose2);
				
			}
			
			// Makes sure first that the data for booster has info on them
			else if((!strcmp("boost", sUserInput) ||
					!strcmp("booster", sUserInput) ||
					sUserInput[0] == 'b') && 
					strlen(stUsers[i].stBoost.sDate) != 0 && 
				    strlen(stUsers[i].stBoost.sName) != 0 && 
				    strlen(stUsers[i].stBoost.sLoc) != 0)
			{
				printf("What info in Booster Dose? \n");
				printf("\033[1;33m'Name', 'Date', 'Location'\033[0m\n");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 10, "Booster Dose");
				sscanf(sLine, "%[^\n]", sSubInfo);
				editDoseStruct("Booster", sSubInfo, &stUsers[i].stBoost);
				
				
			}
			else
			
				*pBoolIsValidChoice = 0;

			
			
			
		}
		
	}
	
	
}


/* 
	resetStructUsers resets all the values in the struct of Users
	
	@param stUsers - Data of all user's personal information and data
	@param pIntSize - Pointer that will contain the updated size of the stUsers or struct array
	
*/
void
resetStructUsers(struct userTag stUsers[],
				 int *pIntSize)
{
	
 	int i;
 	struct doseTag stResetDose = {"", "", ""};
 	
 	// Reset all values of the data
 	struct userTag stReset = {-1, -1, "", "", "", .stBoost = stResetDose, 
	 											  .stDose1 = stResetDose, 
												  .stDose2 = stResetDose};
 	
 	for (i=0; i<*pIntSize; i++)
	{
		if (strlen(stUsers[i].sName) != 0)

			//Resets all values in the struct
			stUsers[i] = stReset;
		
	}
	
	*pIntSize = 0;
 	
}


/* 
	arrangeUsers arranges the User ID in ascending order
	
	@param stUsers - Data of all user's personal information and data
	@param nSize - size of the struct array of sUsers
	
*/
void
arrangeUsers(struct userTag stUsers[],
			 int nSize)
{
	int i;
	int j;

	
	struct userTag stTemp;
	
	//Insertion Sort Algorithm
    for (i = 1; i < nSize; i++) {
        stTemp = stUsers[i];
        
        
        j = i - 1;
        
        //Swap elements continuously as long as the index position of j is bigger than what is to the right
        while (j >= 0 && stUsers[j].nUID > stTemp.nUID) {
            stUsers[j + 1] = stUsers[j];
            j--;
        }
        
		//Final swap even if either the  while loop is over or the UID of the same elements is not the same
		if ( !(j >= 0 && stUsers[j].nUID == stTemp.nUID) ) {
            stUsers[j + 1] = stTemp;
        }
    
    }
	
	
}


/* 
	overwriteUsersFile saves and overwrites the sFileName to store the data from stUsers that contain all user information
	
	@param sFileName - File name to be overwritten and saved at
	@param stUsers - Data of all user's personal information and data
	@param nSize - size of the struct array of sUsers
	
*/
void
overwriteUsersFile(String20 sFileName, 
			       struct userTag stUsers[], 
			       int nSize)
{
	int i;
	FILE *fpIn;
	
	fpIn = fopen(sFileName, "w");
	for (i=0; i<nSize; i++)
	{
		// Only overwrite to file if the name field is not empty
		if (strlen(stUsers[i].sName) != 0)
		{
			//Puts data on file with formatting
			fprintf(fpIn, "%d %s\n", stUsers[i].nUID, stUsers[i].sPassword);
			fputs(stUsers[i].sName, fpIn);
			fprintf(fpIn, "\n");
			fputs(stUsers[i].sAddress, fpIn);
			fprintf(fpIn, "\n");	
			fprintf(fpIn, "%011"PRId64, stUsers[i].nContact);
			fprintf(fpIn, "\n");
			fputs(stUsers[i].sSex, fpIn);
			fprintf(fpIn, "\n");
		
			fprintf(fpIn, "%s %s %s\n", stUsers[i].stDose1.sLoc,
										stUsers[i].stDose1.sDate, 
								        stUsers[i].stDose1.sName);
								        
			if (strlen(stUsers[i].stDose2.sDate) != 0)
			
				fprintf(fpIn, "%s %s %s\n", stUsers[i].stDose2.sLoc,
											stUsers[i].stDose2.sDate, 
								        	stUsers[i].stDose2.sName);
								        	
			if (strlen(stUsers[i].stBoost.sDate) != 0)
				fprintf(fpIn, "%s %s %s\n", stUsers[i].stBoost.sLoc,
											stUsers[i].stBoost.sDate, 
								        	stUsers[i].stBoost.sName);
			fprintf(fpIn, "\n");
		
		}
	
	
	}
	fclose(fpIn);
}



/* 
	displayOneUserData finds and displays only one user data on screen
	
	@param stUsers - Data of all user's personal information and data
	@param nSize - size of the struct array of sUsers
	@param nUID - the user ID to be found and displayed
	
*/
void
displayOneUserData(struct userTag stUsers[], 
				   int nSize, 
				   int nUID)
{
	int i;

	for (i=0; i<nSize; i++)
	{
		
		if (stUsers[i].nUID == nUID)
		{

			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[44m\033[1;31m%30s \033[1;38;5;202m%-10d%20s\033[0m|\n", "User ID: " , stUsers[i].nUID, "");
			printf("          +-------------------------------------------------------------+\n");  

			printf("          +-------------------------------------------------------------+\n");  
			
			printf("          | %s |\n", "                    dS$$S$S$S$S$S$S$$Sb                    ");
			printf("          | %s |\n", "                   :$$S^S$S$S$S$S$S^S$$;                   ");
			printf("          | %s |\n", "                   SSP   `^$S$S$^'   TSS                   ");
			printf("          | %s |\n", "                   $$       `\"'       $$                   ");
			printf("          | %s |\n", "                  _SS      @===@      SS_                  ");
			printf("          | %s |\n", "                 :-.|    @==   ==@    |.-;                 ");
			printf("          | %s |\n", "                  :\(;   \"^\"     @||   |)/;                 ");
			printf("          | %s |\n", "                  \\`|          ||     |'/                  ");
			printf("          | %s |\n", "                   \":         ||      ;\"                   ");
			printf("          | %s |\n", "                     ;       ||      :                     ");
			printf("          | %s |\n", "                     :       ||      ;                     ");
			printf("          | %s |\n", "                   .sSb             dSs.                   ");
			printf("          | %s |\n", "                _.d8dSSb.    @    .SSbT8b._                ");
			printf("          | %s |\n", "            _.oOPd88SSSS T.     .P SSSS888OOo.             ");
	
				
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-20s\033[0m %8s     |\n", "Name: ", stUsers[i].sName, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Password: ", "*********", "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-30s\033[0m    |\n", "Address: ", stUsers[i].sAddress);
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m", "Contact: ");
			printf("%011"PRId64, stUsers[i].nContact);
			printf("\033[0m %17s     |\n", "");
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Sex: ", stUsers[i].sSex, "");
			printf("          +-------------------------+-----------------------------------+\n");
			
						
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Location: ", stUsers[i].stDose1.sLoc, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Date: ", stUsers[i].stDose1.sDate, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Name: ", stUsers[i].stDose1.sName, "");

			printf("          +-------------------------+-----------------------------------+\n");

				

	
			if(strlen(stUsers[i].stDose2.sDate) != 0 && 
			   strlen(stUsers[i].stDose2.sName) != 0 && 
			   strlen(stUsers[i].stDose2.sLoc) != 0)
			{
				
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Location: ", stUsers[i].stDose2.sLoc, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Date: ", stUsers[i].stDose2.sDate, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Name: ", stUsers[i].stDose2.sName, "");
				printf("          +-------------------------+-----------------------------------+\n");

			}
			else
			{
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Location: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");	
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Date: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Name: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
		
			}
			
			if(strlen(stUsers[i].stBoost.sDate) != 0 && 
			   strlen(stUsers[i].stBoost.sName) != 0 && 
			   strlen(stUsers[i].stBoost.sLoc) != 0)
			{

				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Location: ", stUsers[i].stBoost.sLoc, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Date: ", stUsers[i].stBoost.sDate, "");				
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Name: ", stUsers[i].stBoost.sName, "");
				printf("          +-------------------------+-----------------------------------+\n");
	
			}
			else
			{
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Location: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");	
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Date: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Name: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
			
			}
			printf("\n\n");
		}
	}
	printf("\n\n");

}


/* 
	displayOneUserData displays all user data on screen
	
	@param stUsers - Data of all user's personal information and data
	@param nSize - size of the struct array of sUsers
	
*/
void
displayAllUserData(struct userTag stUsers[], 
				   int nSize)
{
	int i;

	for (i=0; i<nSize; i++)
	{
		
		if (strlen(stUsers[i].sName) != 0)
		{
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |\033[44m\033[1;31m%30s \033[1;38;5;202m%-10d%20s\033[0m|\n", "User ID: " , stUsers[i].nUID, "");
			printf("          +-------------------------------------------------------------+\n");  

			printf("          +-------------------------------------------------------------+\n");  
			
			printf("          | %s |\n", "                    dS$$S$S$S$S$S$S$$Sb                    ");
			printf("          | %s |\n", "                   :$$S^S$S$S$S$S$S^S$$;                   ");
			printf("          | %s |\n", "                   SSP   `^$S$S$^'   TSS                   ");
			printf("          | %s |\n", "                   $$       `\"'       $$                   ");
			printf("          | %s |\n", "                  _SS      @===@      SS_                  ");
			printf("          | %s |\n", "                 :-.|    @==   ==@    |.-;                 ");
			printf("          | %s |\n", "                  :\(;   \"^\"     @||   |)/;                 ");
			printf("          | %s |\n", "                  \\`|          ||     |'/                  ");
			printf("          | %s |\n", "                   \":         ||      ;\"                   ");
			printf("          | %s |\n", "                     ;       ||      :                     ");
			printf("          | %s |\n", "                     :       ||      ;                     ");
			printf("          | %s |\n", "                   .sSb             dSs.                   ");
			printf("          | %s |\n", "                _.d8dSSb.    @    .SSbT8b._                ");
			printf("          | %s |\n", "            _.oOPd88SSSS T.     .P SSSS888OOo.             ");
	
				
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-20s\033[0m %8s     |\n", "Name: ", stUsers[i].sName, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Password: ", "*********", "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-30s\033[0m    |\n", "Address: ", stUsers[i].sAddress);
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m", "Contact: ");
			printf("%011"PRId64, stUsers[i].nContact);
			printf("\033[0m %17s     |\n", "");
			printf("          +-------------------------------------------------------------+\n");   
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Sex: ", stUsers[i].sSex, "");
			printf("          +-------------------------+-----------------------------------+\n");
			
						
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Location: ", stUsers[i].stDose1.sLoc, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Date: ", stUsers[i].stDose1.sDate, "");
			printf("          +-------------------------+-----------------------------------+\n");
			printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 1 Name: ", stUsers[i].stDose1.sName, "");

			printf("          +-------------------------+-----------------------------------+\n");

				

	
			if(strlen(stUsers[i].stDose2.sDate) != 0 && 
			   strlen(stUsers[i].stDose2.sName) != 0 && 
			   strlen(stUsers[i].stDose2.sLoc) != 0)
			{
				
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Location: ", stUsers[i].stDose2.sLoc, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Date: ", stUsers[i].stDose2.sDate, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Name: ", stUsers[i].stDose2.sName, "");
				printf("          +-------------------------+-----------------------------------+\n");

			}
			else
			{
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Location: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");	
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Date: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Dose 2 Name: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
		
			}
			
			if(strlen(stUsers[i].stBoost.sDate) != 0 && 
			   strlen(stUsers[i].stBoost.sName) != 0 && 
			   strlen(stUsers[i].stBoost.sLoc) != 0)
			{

				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Location: ", stUsers[i].stBoost.sLoc, "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Date: ", stUsers[i].stBoost.sDate, "");				
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Name: ", stUsers[i].stBoost.sName, "");
				printf("          +-------------------------+-----------------------------------+\n");
	
			}
			else
			{
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Location: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");	
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Date: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
				printf("          |%25s| \033[0;33m%-10s\033[0m %18s     |\n", "Booster Name: ", " N/A", "");
				printf("          +-------------------------+-----------------------------------+\n");
			
			}
			printf("\n\n");
			printf("\033[32m-----------------------------------------------------------------------------------------------------\033[0m\n");  		
			printf("\n\n");
		}
		
		
	}
	
	
						       

}



/*END------------------------------ USER DATA RELATED FUNCTIONS --------------------------------------------------*/




/*START--------------------------- CHAT DATA RELATED FUNCTIONS --------------------------------------------------*/

/* 
	getChatData gets all available chatbot Questions and Answers and stores them in a struct array
	
	@param sFileName - file to be read from data
	@param stChats - Data of all user's personal information and data
	@param pIntSize - address that will contain the size o the struct array
	

*/
void
getChatData(String30 sFileName, 
			struct chatTag stChats[], 
			int *pIntSize)
{
	
	int i;
	int nLineCnt;
	
	char cArrLineSelect[LINE_SIZE];
	FILE *fpOut;
	
	
	
	//Just delete till close
    fpOut = fopen(sFileName, "r");

	

	nLineCnt = 0;
	
	// Will be set as the size
	i =0;	
	while(fgets(cArrLineSelect, LINE_SIZE, fpOut) != NULL)
	{
		

		// Check for the newline character, dont replace the newline character that simply contains itself on the line
	    if (cArrLineSelect[strlen(cArrLineSelect) - 1] == '\n' && strlen(cArrLineSelect) != 1) {
	      // Replace the newline character with a null terminator
	      cArrLineSelect[strlen(cArrLineSelect) - 1] = '\0';
	    }
	    
		
		if (cArrLineSelect[0] != '\n')
		{
			

			switch(nLineCnt)

			{
				case 0:
					//Begins the numbering of question
					stChats[i].nNum = i + 1;
					
					
					//%[^\n] format gets the string up until the new line
					sscanf(cArrLineSelect, "%[^\n]",  stChats[i].sQues);
					
					
					break;
					
				//Gets till terminating byte
				case 1:
					sscanf(cArrLineSelect, "%[^\n]", stChats[i].sAns);

					break;

				
			}
			nLineCnt++;
			

			
			
		}
		if (nLineCnt > 1)
		{
			i++;			//Get position ready for next user data in array
			nLineCnt = 0;	//Reset positioning line describer
			
		}

		
		

		
		
		
		
		
		
	}
	*pIntSize = i;	
	
	

	
	
	
	fclose(fpOut);
	
	

}


/* 
	normalizeText converts text to only contain number or letters and lower its case
	
	@param sText - string of characters to be modified to contain only number and characters
	
*/
void
normalizeText(String80 sText)
{
	
	int i;
	int j;
	String80 sTemp;
	
	//Lower the stringcase
	lowerStringCase(sText);
	
	j = 0;
	for (i = 0; i < strlen(sText); i++)
	{
		
		// Checks if the character is alphanumeric
		if(isalnum(sText[i]))
		{
			// add them to the string of just alphanumeric
			sTemp[j] = sText[i];
			j++;
		}
		
	}
	
	//terminate string
	sTemp[j] = '\0';
	
	//Overwrite original sText	
	strcpy(sText, sTemp);
	
	
}


/* 
	compareSimilarity_90 compares two texts and see if they are at least 90 percent similar, at most 3 characters off in str length

	@param sUserQ - string that is a question asked by the user
	@param sAvailQ - string that is a question available to be answered
	
	@return 1 if the two texts are at least 90% similar, else 0
	
	Pre-condition: The minimum stringlength for both strings is just 5
*/
int
compareSimilarity_90(String80 sUserQ,
			         String80 sAvailQ)
{
	
	int i;
	int nFlag;
	
	// initialize string length
	int nUQ_Len1 = strlen(sUserQ);
	int nAQ_Len2 = strlen(sAvailQ);
	
	// Minimum and max length
	int nMinLen;
	int nMaxLen;
	
	// Count similar chars
	int nSimilarChar;
	
	// String difference must always just be around 3 characters
	int nMaxLenDiff = 3;
	
	// strlen difference of the two strings
	int nLenDiff;
	
	// Stores the percentage of similarity of the two strings
	float nSimilarityPercent;
	
	// initialize first invalid
	nFlag = 0;
	
	
	// Find which one of the two lengths are minimum and maximum
	if (nUQ_Len1 > nAQ_Len2)
	{
		nMaxLen = nUQ_Len1;
		nMinLen = nAQ_Len2;
		
	}
	else
	{
		nMaxLen = nAQ_Len2;
		nMinLen = nUQ_Len1;
	}
	
	
	// Get the difference of string length
	nLenDiff = abs(nUQ_Len1-nAQ_Len2);
	
	// Initialize the count of characters
	nSimilarChar = 0;
	for ( i = 0; i < nMinLen; i++)
		
		// If similar character, count it
		if (sUserQ[i] == sAvailQ[i])
		
			nSimilarChar++;
	
	// Gets the similarity percentage, 1.0 makes the divisor float so the result should be float
	nSimilarityPercent = nSimilarChar / ((nMaxLen-nMaxLenDiff)*1.0);
	
	// Validation Check only occure when the strlen diff of the chars is just 3 characters
	if ( nLenDiff <= nMaxLenDiff )
		if (nSimilarityPercent >= 0.90 )
			nFlag = 1;
	
	// Return if valid or not
	return nFlag;
}


/* 
	isSimilarTexts converts the text into lowercase, alphanumeric, no spaces to accurately compare the two
	
	@param sUserQ - string that is a question asked by the user
	@param sAvailQ - string that is a question available to be answered
	
	@return 1 if the two texts are similar, else 0
*/
int
isSimilarTexts(String80 sUserQ,
			   String80 sAvailQ)
{
	int nFlag;
	
	// Makes the string only contain number and letters
	normalizeText(sUserQ);
	normalizeText(sAvailQ);
	
	// Removes excess spaces and spaces between words
	removeSpaces(sUserQ);
	removeSpaces(sAvailQ);
	
	
	// Default not similar
	nFlag = 0;
	
	
	//Compare the string
	if (!strcmp(sUserQ, sAvailQ))
		
		// Declare similarity
		nFlag = 1;
	
	if (!nFlag)
	{
		if (strlen(sUserQ) >= 5 && strlen(sAvailQ) >= 5)
		
			nFlag =	compareSimilarity_90(sUserQ, sAvailQ);
		
	}
		
	
	return nFlag;
	
}


/* 
	findChatAnswer finds and gives the answer to the user's question if it is available
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct array of Questions and answer for the Chatbot
	@param sUserInputQ - string that is a question asked by the user
	@param sAns - string that will contain the answer of the Chatbot
	
*/
void
findChatAnswer(struct chatTag stChats[], 
			   int nSize, 
			   String80 sUserInputQ, 
			   String80 sAns)
{
	int i;
	int nRandomNumber;
	int nSelectedNumber;
	
	String80 sTemp;
	
	// String of text to randomize for more natural convo
	String80 sDefaultAns[10] = {"Sorry, I Don't have an answer to that question.",
								"I apologize, I don't seem to know how to answer that.",
								"Hm may I suggest to ask or consult other notable sources (DOH, WHO).",
								"Very sorry, I don't have a concrete answer for that yet.",
								"Looks like I can't answer that, Sorry Sir/Ma'am/<Pronoun>.",
								"Sorry, I don’t know the answer. Please type another question."};
	
	// Empties answer string variable
	strcpy(sAns, "");
	for(i=0; i<nSize; i++)
	{
		// Lower the case of the question but not directly on the database
		// User an sTemp to not affect the database's version of question
		strcpy(sTemp, stChats[i].sQues);
		lowerStringCase(sTemp);
		
		//If the texts are similar, copy and give the answer
		if( isSimilarTexts(sTemp, sUserInputQ) )
		
			strcpy(sAns, stChats[i].sAns);
		
	}
	
	//When bot can't find an answer
	if (strlen(sAns) == 0)
	{
		srand(time(NULL));							//Sets the seed of calling a random number based on time parameters of NULL, making it pass only seconds
				
		nRandomNumber = rand();						//Calls a random number which performs a series of 'random' operations based on seed
		nSelectedNumber = nRandomNumber%6;			//Makes sure the random number is between 0-4
		
		if((strlen(sUserInputQ) == 1 &&  sUserInputQ[0] != 'x') ||
		   (strlen(sUserInputQ) > 1 &&  sUserInputQ[0] != 'x'))
		   
		   	strcpy(sAns, sDefaultAns[nSelectedNumber]);
		   
			
		
	}
	
}


/* 
	promptUserToChat prompts the user to ask the chatbot
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct array of Questions and answer for the Chatbot
	@param sUserInputQ - string that is a question asked by the user
	
*/
void
promptUserToChat(struct chatTag stChats[], 
				 int nSize, 
				 String80 sUserInputVar)
{
	int nRandomNumber;
	int nSelectedNumber;
	
	char sLine[LINE_SIZE];
	
	String80 sUserInputQ;
	String80 sAnswer;
	String80 sDefaultAns[10] = {"Goodbye and Nice Talking to Ya!",
								"See ya, Sayonara! <3<3<3",
								"Have a nice day user!",
								"Byeee, Love your family, work super hard, live your passion!",
								"Later User, remember that you always look good regardless."};	
	
	

	// Prompt the user first for his first question
	printf("\t\033[0;36mQ >>\033[0;33m ");
	fgets(sLine, LINE_SIZE, stdin);
	warnValidSize(sLine, 80, "\033[0;36mQ >>\033[0;33m");
	sscanf(sLine, "%[^\n]", sUserInputQ);
	printf("\033[0m");
	
	// Lower the user's input
	lowerStringCase(sUserInputQ);
	
	// Find the answer	
	findChatAnswer(stChats, nSize, sUserInputQ, sAnswer);
	
	//
	strcpy(sUserInputVar, sUserInputQ);
	
	if(sUserInputQ[0] =='x' || sUserInputQ[0] =='X')
	{
		srand(time(NULL));							//Sets the seed of calling a random number based on time parameters of NULL, making it pass only seconds
				
		nRandomNumber = rand();						//Calls a random number which performs a series of 'random' operations based on seed
		nSelectedNumber = nRandomNumber%5;			//Makes sure the random number is between 0-4
		printf("\n");
		printf("\t\033[0;36mBot Ans >>\033[0;33m %s\033[0m\n\n", sDefaultAns[nSelectedNumber]);
		system("PAUSE");
	}
	
	else
	{
		printf("\t\033[0;36mBot Ans >>\033[0m ");
		printf("\033[0;33m%s\033[0m", sAnswer);
		printf("\n");
		
	}

	
	
}


/* 
	saveChatToFile appends data of new question and answer to chatbot data
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param sFileName - File name of where the data of chatbot will be appended
	
*/
void
saveChatToFile(String30 sFileName, 
			   struct chatTag stChat)
{

	FILE *fpIn;
	//Saving data into file
    fpIn = fopen(sFileName, "a");

	
	//Puts data on file with formatting
	fputs(stChat.sQues, fpIn);
	fprintf(fpIn, "\n");
	fputs(stChat.sAns, fpIn);
	fprintf(fpIn, "\n");	
	


	fclose(fpIn);   
}


/* 
	overwriteChatFile clears and overwrites file on the sFileName
	
	@param sFileName - File name of where the data of chatbot will be overwritten	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array
	
*/
void
overwriteChatFile(String20 sFileName, 
			      struct chatTag stChats[], 
			      int nSize)
{
	int i;
	FILE *fpIn;
	
	fpIn = fopen(sFileName, "w");
	
	
	for (i=0; i<nSize; i++)
	{
		// If the question contains something then proceed to overwrite it in the file	
		if (strlen(stChats[i].sQues) != 0)
		{
			//Puts data on file with formatting
		
			fputs(stChats[i].sQues, fpIn);
			fprintf(fpIn, "\n");
			fputs(stChats[i].sAns, fpIn);
			fprintf(fpIn, "\n");	

		
		}
	
	
	}
	fclose(fpIn);
}


/* 
	addChatData prompts to add chat data to the sFileName
	
	@param sFileName - File name of where the data of chatbot will append data
	
*/
void
addChatData(String30 sFileName)
{

	



	char cUserInput;
	char cContinueInput;

	char sLine[LINE_SIZE];

	String80 sUserInputQ;
	String80 sUserInputA;

	int nChatSize;
	
    struct chatTag stChats[MAX_CHAT];
	
	
	// Sets while loop to continue
   cContinueInput = 'Y';
    do
    {
    	
    	// Get Chat size
    	getChatData(sFileName, stChats, &nChatSize);
    	
    	//Prompt Question
	 	printf("Question: ");
		fgets( sLine, LINE_SIZE, stdin);
		warnValidSize(sLine, 80, "Question");
		sscanf(sLine, "%[^\n]", sUserInputQ);
		
		// Prompt answer
		printf("Answer: ");
		fgets( sLine, LINE_SIZE, stdin);
		warnValidSize(sLine, 80, "Answer");
		sscanf(sLine, "%[^\n]", sUserInputA);
		
		printf("\n\n");
		
		// Questions Certainty of User
		printf("Are you sure with the following:\n");
		printf("Question >> \033[0;33m\"%s\"\033[0m\n", sUserInputQ);
		
		printf("Answer >> \033[0;33m\"%s\"\033[0m\n\n", sUserInputA);
		
		printf("Sure? (Y/N): ");
		scanYesNo(&cUserInput);
		
	
		if(cUserInput == 'Y' || cUserInput == 'y')
		{
			
			// Proceeds to save the data to file
			strcpy(stChats[nChatSize].sAns, sUserInputA);
			strcpy(stChats[nChatSize].sQues, sUserInputQ);
			
			// Adding question means adding question number
			stChats[nChatSize].nNum = nChatSize + 1;
			saveChatToFile(sFileName, stChats[nChatSize]);
			
			//Sets the size for the next time user wants to prompt a question
			nChatSize += 1;
			printf("\033[1;32mSuccessfully saved to \"%s\"\033[0m\n\n", sFileName);
			
			// Asks if the user wants to exit the loop or go again for another additional question and answer
			printf("Want to input another question and answer data? (Y/N): ");
			scanYesNo(&cContinueInput);
			
		}
		
		

		
		   	
	}while(cContinueInput == 'Y' || cContinueInput == 'y');
	
	

	

				
}


/* 
	splitToTwoStrings prompts to add chat data to the sFileName
	
	@param sUserInput_FromStruct - The actual question or answer string from chatbot Struct
	@param sSplit1 - Stores first half string of sUserInput_FromStruct
	@param sSplit2 - Stores 2nd half string of sUserInput_FromStruct
	
	Pre-condtion - sUserInput_FromStruct is more than 48 characters long
*/
void
splitToTwoStrings(String80 sUserInput_FromStruct, 
				  String80 sSplit1, 
				  String80 sSplit2)
{
	

	int bIsDone = 0;
	

	int nCntChar;
	
	//Sets index of string with no
	nCntChar=0;
	
	//Sets variables and resets value
	String80 sUserInput;
	strcpy(sSplit1, "");
	strcpy(sSplit2, "");
	
	
	//Copies the string from the struct
	strcpy(sUserInput, sUserInput_FromStruct);
	
	// The starting half of the string
	nCntChar=40;

	//Find which space to break the string to rightwards of string
	while(  nCntChar < 49 && !bIsDone)
	{
		
		//A space is found
		if(sUserInput[nCntChar] == ' ')
		{
			
			// Terminate string
			sUserInput[nCntChar] = '\0';
			
			// Exit the loop
			bIsDone = 1;
			
			// Copy as first half of the string
			strcpy(sSplit1, sUserInput);
		}
		else
			nCntChar++;
	}
	
	
	// If the character count goes over 49 then we try to look for spaces to break to the leftward of string
	while(  nCntChar > 31 && !bIsDone)
	{
		
		// Spaces if found
		if(sUserInput[nCntChar] == ' ')
		{
			// Terminate the string
			sUserInput[nCntChar] = '\0';
			
			// Exit loop
			bIsDone = 1;
			
			// Copy as first half of the string
			strcpy(sSplit1, sUserInput);
		}
		else
			nCntChar--;
		
	}
		
		
	// Check if there are characters to put
	if(strlen(sUserInput+nCntChar + 1) != 0)
		// The 2nd half of the string would then start at be CntChar + 1
		strcpy(sSplit2, sUserInput + nCntChar + 1);
		
		
}


/* 
	displayOneChatData displays one chat Data, meaning one question and answer
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array
	@param nNumID - The question number that will be displayed

*/
void
displayOneChatData(struct chatTag stChats[], 
				   int nSize, 
				   int nNumID)
{
	int i;
	String80 sSplit1;
	String80 sSplit2;
	
	for (i=0; i<nSize; i++)
	{
		
		if (stChats[i].nNum == nNumID)
		{
			
			printf("      +-------------------------------------------------------------+\n");  
			displayBotArt5_Bordered();			
			printf("          +------------------------------+------------------------------+\n");
			printf("          |                   Question Number: \033[0;33m%3d\033[0m                      |\n", stChats[i].nNum);	
			printf("          +----------+--------------------------------------------------+\n");

			

			if(strlen(stChats[i].sQues) > 48)
			{
				splitToTwoStrings(stChats[i].sQues, sSplit1, sSplit2);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Question ", sSplit1);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "         ", sSplit2);
			}
			else
			{
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Question ", stChats[i].sQues);
			}
			

			
			
			printf("          +----------+--------------------------------------------------+\n");
			

			if(strlen(stChats[i].sAns) > 48)
			{
				splitToTwoStrings(stChats[i].sAns,sSplit1,sSplit2);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Answer ", sSplit1);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "       ", sSplit2);
			}
			else
			{
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Answer ", stChats[i].sAns);
			}
						
			
			printf("          +----------+--------------------------------------------------+\n");			
			
		}
	}
}


/* 
	displayAllChatData displays all chat Data, meaning all questions and answers
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array


*/
void
displayAllChatData(struct chatTag stChats[], 
				   int nSize)
{
	int i;
	
	String80 sSplit1;
	String80 sSplit2;
	
	//Tokeniz each word to diplay properly in screen
	
	printf("      +-------------------------------------------------------------+\n");  
	displayBotArt5_Bordered();
	
	
	
	for (i=0; i<nSize; i++)
	{
		
		if (strlen(stChats[i].sQues) != 0)
		{


			

	
			printf("          +------------------------------+------------------------------+\n");
			printf("          |                   Question Number: \033[0;33m%3d\033[0m                      |\n", stChats[i].nNum);	
			printf("          +----------+--------------------------------------------------+\n");

			
			// Trigger split format if the string length is greater than 48
			if(strlen(stChats[i].sQues) > 48)
			{
				splitToTwoStrings(stChats[i].sQues,sSplit1,sSplit2);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Question ", sSplit1);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "         ", sSplit2);
			}
			else
			{
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Question ", stChats[i].sQues);
			}
			

			
			
			printf("          +----------+--------------------------------------------------+\n");
			

			if(strlen(stChats[i].sAns) > 48)
			{
				splitToTwoStrings(stChats[i].sAns,sSplit1,sSplit2);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Answer ", sSplit1);
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "       ", sSplit2);
			}
			else
			{
				printf("          | %9s| \033[0;33m%-49s\033[0m|\n", "Answer ", stChats[i].sAns);
			}
						
			
			printf("          +----------+--------------------------------------------------+\n");
			

		}
		
		
	}
	
	
						       

}


/* 
	deleteChat removes the data on the particular question ID
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array
	@param nNumID - Question number ot be deleted

*/
void
deleteChat(struct chatTag stChats[],
		   int nSize,
		   int nNumID)
{
	
	int i;
	for (i=0; i<nSize; i++)
	{
		if (stChats[i].nNum == nNumID)
		
			// Clears entire structure and replacing each value with 0
			memset(&stChats[i], 0, sizeof(stChats[i]));
			
		
		
	}
	
}


/* 
	editSelectedChat checks the category the user inputted to prompt him then
	
	@param sUserInput - Category of the either question or answer to modify
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array
	@param nNumID - Question number to be modified
	@param pIsValidCateg - pointer to relay the boolean value of the valid or invalid choice of user

*/
void
editSelectedChat(String30 sUserInput, 
			 	 struct chatTag stChats[],
			 	 int nSize,
			 	 int nNumID,
				 int *pIsValidCateg	)
{
	
	int i;
	char sLine[LINE_SIZE];
	lowerStringCase(sUserInput);
	
	//Replaces potential new line ('\n') included in the fgets
	if(sUserInput[strlen(sUserInput) - 1] == '\n' )
		sUserInput[strlen(sUserInput) - 1] = '\0';
	
	
	*pIsValidCateg = 1;
	for (i = 0; i < nSize; i++)
	{
		if ( nNumID	 == stChats[i].nNum)
		{
			if(!strcmp("all", sUserInput))
			{
				// Prompt Question
				printf("New Value for the \033[0;36mQuestion:\033[0m ");
				fgets(sLine, LINE_SIZE, stdin);
				
				// Prompt till valid strlen of question
				warnValidSize(sLine, 80, "Question");
				strcpy(stChats[i].sQues, sLine);
				
				// Prompt Answer
				printf("New Value for the \033[0;36mAnswer:\033[0m ");
				fgets(sLine, LINE_SIZE, stdin);
				
				// Prompt till valid strlen of answer
				warnValidSize(sLine, 80, "Answer");
				strcpy(stChats[i].sAns, sLine);
				

				
			}
			
			else if(!strcmp("question", sUserInput) ||
			   !strcmp("quest", sUserInput) ||
			   !strcmp("ques", sUserInput) ||
			   !strcmp("qst", sUserInput) ||
			   !strcmp("qt", sUserInput) ||
			   !strcmp("q", sUserInput))
			{
				
				// Prompt Question
				printf("New Value for the \033[0;36mQuestion:\033[0m ");
				fgets(sLine, LINE_SIZE, stdin);
				
				// Prompt till valid strlen of question
				warnValidSize(sLine, 80, "Question");
				strcpy(stChats[i].sQues, sLine);
				
			}
			
			else if(!strcmp("answer", sUserInput) ||
			   		!strcmp("answe", sUserInput) ||
			   		!strcmp("answ", sUserInput) ||
			   		!strcmp("ans", sUserInput) ||
			   		!strcmp("an", sUserInput) ||
			   		!strcmp("a", sUserInput))
			{
				
				// Prompt Answer
				printf("New Value for the \033[0;36mAnswer:\033[0m ");
				fgets(sLine, LINE_SIZE, stdin);
				
				// Prompt till valid strlen of answer
				warnValidSize(sLine, 80, "Answer");
				strcpy(stChats[i].sAns, sLine);

				
			}
			else
			{
				// Pass that the choice was invalid
				*pIsValidCateg = 0;
				
				
				// Provide Feedback of not correct choice
				printf("\n\033[1;38;5;202mERROR! Please only enter from the input choices (Question/Answer).\033[0m\n\n");
				system("PAUSE");
				
			}
		}
	
	}
	
}



/* 
	checkChatIDExists checks the existence of a Question No.
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param nSize - Size of the struct of Chatbot's data array
	@param nNumID - Question number to be checked for valid existence
	
	@return 1 if the question number exists, else 0
*/
int
checkChatIDExists(struct chatTag stChats[],
				  int nSize,
				  int nNumID)

{
	
	int nFlag;
	int i;
	nFlag = 0;
	for(i=0; i<nSize; i++)
	
		// If the question number exist then it is valid
		if(stChats[i].nNum == nNumID)
			nFlag = 1;
	
	return nFlag;
}


/* 
	resetStructChats resets all data of chatbot question and answer structs
	
	@param stChats - Struct of all question and answer available for the Chatbot
	@param pIntSize - address where the updated size of the array struct of stChats will be stored

*/
void
resetStructChats(struct chatTag stChats[],
				 int *pIntSize)
{
	
 	int i;
 	struct chatTag stReset = {0, "", ""};	// Sets the reset values
 	
 	for (i = 0; i < *pIntSize; i++)
	{
		// If question field is not empty
		if (strlen(stChats[i].sQues) != 0)

			//Resets all values in the struct
			stChats[i] = stReset;
		
	}
	
	*pIntSize = 0;
 	
}

/*END--------------------------- CHAT DATA RELATED FUNCTIONS --------------------------------------------------*/


/* 
	doesFileExist checks if the file for a certain name exists
	
	@param sFileName - Filename to be checked for existence
	
	@return 1 if the file exists, else 0
*/
int
doesFileExist(String30 sFileName)
{
	
	
	int nFlag;
	FILE* fpTest;
	
	//sets file as read only
	fpTest = fopen(sFileName, "r");
	
	// Check if the file pointer returns null
	if(fpTest == NULL)
	{
		nFlag = 0;
		printf("\n\033[1;38;5;202mERROR! File does not exist\033[0m\n");
	}
	    
	else
		nFlag = 1;
	
	
	return nFlag;
	
	
}


/* 
	doesAppsExist checks if the file for a certain name exists that also contain the User's ID
	
	@param sFileName - Filename to be checked for existence
	@param nUID - the User ID to be checked for available appointments
	
	@return 1 if the file and User appointment data exists, else 0
	Pre-condition: Used for the struct appTag checking to be place in the array of appointment data
*/
int
doesAppsExist(String30 sFileName, int nUID )
{
	
	
	int nFlag;
	int isExists;
	int i;
	int nCurrentSize;
	struct appTag stAppReqs[MAX_REQS];
	FILE* fpTest;
	
	
	// Gets the appdata depending on the filename
	getAppData(sFileName, stAppReqs, &nCurrentSize);
	fpTest = fopen(sFileName, "r");
	
	
	
	isExists = 0;
	
	// Check if at least on appointment struct belongs to the user
	for(i = 0; i < nCurrentSize; i++)
	
		if(nUID == stAppReqs[i].nUID)
			isExists = 1;
		
	
	// If the file pointer read is null, or when user's appointments don't exist then return 0
	if(fpTest == NULL || !isExists)
	
		nFlag = 0;
	else
		nFlag = 1;
	
	fclose(fpTest);
	return nFlag;
	
	
}


/* 
	displayRegister displays and prompts the user of input fields required to register account
	
*/
void 
displayRegister()
{
	
	struct userTag stUsers[MAX_USERS];
	int nCurrentUID;
	int nCurrentUsers;
	
	getUserData("Users.txt", stUsers, &nCurrentUsers);
	
	if(nCurrentUsers < MAX_USERS)
	{
		system("CLS");
		printf("\t\t\033[1;33m  USER REGISTRATION\n\033[0m\n\n");
		
		// Gets the user to register
		promptUserData(stUsers, nCurrentUsers);
		
		// Append to file
		saveUserToFile("Users.txt", stUsers[nCurrentUsers]);
		
		// Sets that the current ID is whatever is inputted in the struct
		nCurrentUID = stUsers[nCurrentUsers].nUID;
		
		
		// Reset struct
		resetStructUsers(stUsers, &nCurrentUsers);
		
		// Extract and get to struct
		getUserData("Users.txt", stUsers, &nCurrentUsers);
		printf("\n");
		
		// Display the newly added struct
		displayOneUserData(stUsers, nCurrentUsers, nCurrentUID);
		printf("\033[1;32mYou have successfully created an account, UID \033[1;36m%d\033[0m! \n\n", nCurrentUID);
		system("PAUSE");
		
		
		//Sorts them in the database ascending order of UID
		resetStructUsers(stUsers, &nCurrentUsers);	
		getUserData("Users.txt", stUsers, &nCurrentUsers);
		arrangeUsers(stUsers, nCurrentUsers);
		overwriteUsersFile("Users.txt", stUsers, nCurrentUsers);
	}
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! You have reached max user limit\033[0m\n\n");
		system("PAUSE");
	}
	

	

}


/* 
	displayChatBot displays and prompts the user of chatbot input fields
*/
void 
displayChatBot()
{
	
    struct chatTag stChats[MAX_CHAT];
	int nChatSize;
	String80 sUserInput;
	
	// Get available data from Chatbot
	getChatData("Chatbot.txt", stChats, &nChatSize);
	system("CLS");
	printf("\t\t\033[1;36m[X]\033[0m to exit Chat bot\n\n");
	printf("\t\t\033[1;33mHi this is VacciBot! How may I help you?\033[0m\n\n");
	
	// Sets display art to show the chatbot
	randomizeDisplayArt();
		
	
	do
	{	
		// Chat proper of user and Chatbot
		promptUserToChat(stChats, nChatSize, sUserInput);
		printf("\n");

		
	}while(sUserInput[0] !='x' && sUserInput[0] !='X');	
	
}


/* 
	displayUserAppt_Req displays and prompts the user of his/her appointment request ID
	
	@paran nUID - The User ID of the person who logged in to make/manage an appointment
	
*/
void
displayUserAppt_Req(int nUID)
{
	struct appTag stAppReqs[MAX_REQS];

	char cUserInput;
	int nCurrentAppID;
	int nCurrentAppReqs;
	getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
	
	if (nCurrentAppReqs < MAX_REQS)
	{
		do
		{
			system("CLS");
			// Display the appointment prompting
			printf("\t\t\033[1;33m  APPOINTMENT REQUEST MENU\n\033[0m\n\n");
			
			// set first element of the appointment to be overwritten
			promptAppData(stAppReqs, 0, nUID);
			
			// Append data to .txt
			saveAppToFile("Appointment.txt", stAppReqs[0]);
			
			// Get the current app ID
			nCurrentAppID = stAppReqs[0].nAppID;
			printf("Your New Appointment Data: \n\n");
			
			// Current App ID is used to be displayed on the screen
			displayOneAppData(stAppReqs, 1, nCurrentAppID);
			
			// Only one struct is being modified and added
			nCurrentAppReqs = 1;
			printf("\n\033[1;32mSuccessfully created your Appointment ID\033[0m\n\n");
			system("PAUSE");
			
			
			// Prompt user a yes or no
			printf("Do you want to request more? (Y/N): ");
			
			// Restricts user to only input 'Y' or 'N'
			scanYesNo(&cUserInput);
	
			//Reset all data in user structs
			resetStructAppReqs(stAppReqs, &nCurrentAppReqs);						
	
		} while(cUserInput == 'y' || cUserInput =='Y');
		
		
		
		//Makes them aligned in numerical order
		getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
		
		// Arranges in order of ascending of Appointmetn ID
		arrangeAppReqs(stAppReqs, nCurrentAppReqs);
		overwriteAppReqsFile("Appointment.txt", stAppReqs, nCurrentAppReqs);	//Overwrite them in file
		
	}
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! You have reached max appointment limit\033[0m\n\n");
		system("PAUSE");
	}

	
}


/* 
	displayUserAppt_Del displays and prompts the user of his/her appointment requests about which one to delete
	
	@paran nUID - The User ID of the person who logged in to make/manage an appointment
	@param pBoolIsExit - address of while loop to control direct exit to go towards appointment menu
	
*/
void
displayUserAppt_Del(int nUID, int *pBoolIsExit)
{
	
	
	
	struct appTag stAppReqs[MAX_REQS];
	struct appTag stUserApps[MAX_REQS];
	
	
	int nCurrentAppReqs;
	int nCurrentUserApps;
	int nSelectedAppID;
	int bIsFileExist;
	int bIsAppExist;
	
	
	char cUserInput_ContinueDel;
	char cUserInput_IsSure;
	
	
	/* Gauge the size of user's appointments'*/	
	getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);


	// Gets only appointments of one user
	getUserOnlyApp(stAppReqs, 					//Struct collection of all requests of all users
			   	   stUserApps, 					//Struct collection of all requsts of one user
			       nCurrentAppReqs,				//All users number of apps
			       &nCurrentUserApps, 			//This one user's number of apps
			       nUID);						//UID of this user
	
	
	system("CLS");
	// Check if the file exists
	bIsFileExist = doesAppsExist("Appointment.txt", nUID);

	if (!bIsFileExist)
	{
		printf("\n\033[1;38;5;202mERROR! There is no data for UID %d, no appointments to cancel.\033[0m\n\n", nUID);
		system("PAUSE");
	}
		
		

	
	else if (nCurrentUserApps == 0)
	{
		printf("\n\033[1;38;5;202mERROR! There is no appointment data, no appointments to cancel.\033[0m\n");
		system("PAUSE");
		bIsFileExist = 0;
	}

		
	
	//Proceed with selecting which App ID to delete
	else
	{
		do
		{
			system("CLS");
			printf("\t\t  \033[1;33m    DELETE OR CANCEL APPOINTMENT\n\033[0m\n\n");
			getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
		
			
	
			printf("\nUser %d Data: \n\n", nUID);
		
		
			//Gets only appointments of one user
			getUserOnlyApp(stAppReqs, 					//Struct collection of all requests of all users
					   	   stUserApps, 					//Struct collection of all requsts of one user
					       nCurrentAppReqs,				//All users number of apps
					       &nCurrentUserApps, 			//This one user's number of apps
					       nUID);						//UID of this user
			
			
			//Displays currently all user
			displayAllAppData(stUserApps, nCurrentUserApps);
			printf("What \033[1;36mAppointment ID\033[0m do you want to cancel: ");
			scanID(&nSelectedAppID);
			
			//Used for validating no unique IDs are allowed but since it returns 0 when it finds the ID, we just need to negate that
			bIsAppExist = !(validateAppID(stUserApps, nSelectedAppID, nCurrentUserApps));
			
			
			if (bIsAppExist)
			{
				system("CLS");
				printf("CANCELLING THIS APPOINTMENT...\n\n");
				
				// Display one user's one appointment data
				displayOneAppData(stAppReqs, nCurrentAppReqs, nSelectedAppID);
				
				
				// Is user sure to cancel the data
				printf("Are you sure you want to cancel this data? (Y/N)\n");
				scanYesNo(&cUserInput_IsSure);
			
	
	
	
				if (cUserInput_IsSure == 'Y' || cUserInput_IsSure == 'y')
				{
					// Deleted the appointment data
					deleteApp(stAppReqs, nSelectedAppID, nCurrentAppReqs);
			
					// Overwrites the now deleted result of struct to a file
					overwriteAppReqsFile("Appointment.txt", stAppReqs, nCurrentAppReqs);	//Overwrite them in file
					printf("\n\033[1;32mYou have successfully cancelled Appointment ID %d\033[0m\n\n", nSelectedAppID);
				}
				else
					printf("\n\033[1;32mYour plan to cancel Appointment ID %d will not continue.\033[0m\n\n", nSelectedAppID);
					
					
				// Asks if he/she wants more cancelling
				printf("Do you want to cancel something else? (Y/N)\n");
				scanYesNo(&cUserInput_ContinueDel);
				
			}
			else
			{
				// Asks if he/she wants more cancelling
				printf("\n\033[1;38;5;202mERROR! We couldn't find your App ID\033[0m\n");
				printf("Do you want to cancel something else? (Y/N): \n");
				scanYesNo(&cUserInput_ContinueDel);
			}
			
			
			/* Gauge the size of user's appointments'*/	
			getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
		
			// Gets only appointments of one user
			getUserOnlyApp(stAppReqs, 					//Struct collection of all requests of all users
					   	   stUserApps, 					//Struct collection of all requsts of one user
					       nCurrentAppReqs,				//All users number of apps
					       &nCurrentUserApps, 			//This one user's number of apps
					       nUID);						//UID of this user
			
			// Signify user if it becomes 0
			if (nCurrentUserApps == 0)
			{
				printf("\n\033[1;38;5;202mERROR! There are no more appointments to cancel.\033[0m\n\n");
				system("PAUSE");
			}
			
		}while( (cUserInput_ContinueDel == 'Y' || cUserInput_ContinueDel == 'y') &&
			     nCurrentUserApps > 0);
		
		
	}
	

	
	
	// Helps exit the while loop to go straight back into vaccination menu
	*pBoolIsExit = 1;

}


/* 
	displayUserAppt_Man displays and prompts the user of his/her appointment requests about which one to edit
	
	@paran nUID - The User ID of the person who logged in to make/manage an appointment
	@param pBoolIsExit - address of while loop to control direct exit to go towards appointment menu
	
*/
void
displayUserAppt_Man(int nUID, int *pBoolIsExit)
{
	
	int bIsDone = 0;
	int bIsExists;
	int bIsValidID;
	int bIsValidCateg;
	
	int nCurrentAppReqs;
	int nCurrentUserApps;
	int nCurrentAppID;
	int nCurrentUID;
	int nInd_stAppReqs;
	
	char cUserInput;
	char sLine[LINE_SIZE];
	String10 sUserInput;
	
	struct appTag stAppReqs[MAX_REQS];
	struct appTag stUserApps[MAX_REQS];
	
	
	nCurrentUID = nUID;
	system("CLS");
	printf("\t\t  \033[1;33m    EDIT APPOINTMENT\n\033[0m\n\n");
	
	
	/* Help Gauge the amount appointments in user*/
	//Readies data first if there is
    //Gets all collection of appointments
	getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);


	//Gets only appointments of one user
	getUserOnlyApp(stAppReqs, 					//Struct collection of all requests of all users
				   stUserApps, 					//Struct collection of all requsts of one user
				   nCurrentAppReqs,				//All users number of apps
				   &nCurrentUserApps, 			//This one user's number of apps
				   nCurrentUID);				//UID of this user
	
	
	// Check existence of the appointment data
	bIsExists = doesAppsExist("Appointment.txt", nUID );
	if (!bIsExists)
	{
		printf("\n\033[1;38;5;202mERROR! There is no data for UID %d, no appointments to manage.\033[0m\n\n", nUID);
		system("PAUSE");
		
	}
	else if (nCurrentUserApps == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no more appointments to manage.\033[0m\n\n");
		system("PAUSE");
		bIsExists = 0;
	}
		
	while(bIsExists && !bIsDone)
	{
		
		system("CLS");
		//Readies data first if there is
	    //Gets all collection of appointments
		getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);


		//Gets only appointments of one user
		getUserOnlyApp(stAppReqs, 					//Struct collection of all requests of all users
					   stUserApps, 					//Struct collection of all requsts of one user
					   nCurrentAppReqs,				//All users number of apps
					   &nCurrentUserApps, 			//This one user's number of apps
					   nCurrentUID);				//UID of this user
	    

		printf("\n\033[1;36mData of User ID %d Data: \033[0m\n\n", nUID);
	
		
		displayAllAppData(stUserApps, nCurrentUserApps);
		
		// For only if the User Apps have data
		if (nCurrentUserApps > 0)
		{
			printf("Do you want to edit an appointment? (Y/N): ");
			scanYesNo(&cUserInput);
			
			// When more than one go ahead
			if ((cUserInput == 'Y' || cUserInput == 'y') &&
				 nCurrentUserApps > 1  )
		   	{
		   		bIsValidID = 0;
		   		while(!bIsValidID)
		   		{
				   printf("Which \033[1;36mAppointment ID\033[0m do you wish to edit:  ");
		   			scanID(&nCurrentAppID);
		   			//Result of validateID looks for unique IDs, if it is the same we simply call it valid because
		   			// User is selecting from the available IDs he made, we negate the function's results
		   			bIsValidID = !(validateAppID(stUserApps, nCurrentAppID, nCurrentUserApps));
		   			
		   			if(!bIsValidID)
		   				printf("\n\033[1;38;5;202mERROR! We couldn't find the ID you were specifying.\033[0m\n\n");
				}
		   		
		   		
		   		system("CLS");
		   		displayOneAppData(stAppReqs, nCurrentAppReqs, nCurrentAppID);
		   		
			}
			
			// If there was only one data of appointment, go straight ahead and automaticall ymake it the default thing to edit
			else if ( (cUserInput == 'Y' || cUserInput == 'y') &&
				      nCurrentUserApps == 1  )						// One or no elements
			{
				
				//Since there is only one appointment, proceed with edit app id with the struct array's index 0 position
				nCurrentAppID = stUserApps[0].nAppID;
			}
			else if ((cUserInput != 'Y' || cUserInput != 'y') )
			
				bIsDone = 1;
			
			// Readies the loop
			bIsValidCateg = 0;
			
			// Keep looping until user edits a valid category
			while (!bIsDone && !bIsValidCateg)
			{
				// Get where the appointment to be edited is found
				nInd_stAppReqs = findIndex_MainAppReqs(stAppReqs, nCurrentAppReqs, nCurrentAppID);


	
				printf("Which data do you want to edit? (You can choose from the ff): \n");
				printf("\033[1;33m'App ID', 'Name', 'Location', 'Vaccine', 'date', 'time', 'dose'\033[0m \n");
				fgets(sLine, LINE_SIZE, stdin);
				warnValidSize(sLine, 30, ", data you want to edit: ");		
				sscanf(sLine, "%[^\n]", sUserInput);
				
				
				//Commit editing
				editSelectedApp(sUserInput, 		// User Input
							    stAppReqs, 			// All appointment reqs from mall different users
							    stUserApps, 		// User's appointments
							    &nCurrentAppID, 	// Address to modify the ID
							    nCurrentUserApps,	// Checks what to edit and prompts user respectively
								&bIsValidCateg);	// Gets info if input was valid or not
				
				
				//Swaps the remodified struct in the index of the struct array containing all user appointments
				swapStructs(stAppReqs, stUserApps, 		//The two structs
							nInd_stAppReqs, 			//The index of where the origin of it was found
							nCurrentAppID, 				//The current App ID being edited
							nCurrentUserApps);			//Number of appointment the user has


				
				
				// Arrange in ascending order top to bottom based on App ID
				arrangeAppReqs(stAppReqs, nCurrentAppReqs);

				overwriteAppReqsFile("Appointment.txt", stAppReqs, nCurrentAppReqs);	//Overwrite them in file
			    resetStructAppReqs(stAppReqs, &nCurrentAppReqs);						//Resets all tdata in every user's struct				
				resetStructAppReqs(stUserApps, &nCurrentUserApps);						//Resets all data in user's structs
				
				
				
				
				
				if (bIsValidCateg)
				{
					
					
					//Gets all collection of appointments
					getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
					
					// Display and find the one app data edited
					system("CLS");
					displayOneAppData(stAppReqs, nCurrentAppReqs, nCurrentAppID);
					printf("\n\033[1;32mSuccesfully edited data! \033[0m\n\n");
					system("PAUSE");
					resetStructAppReqs(stAppReqs, &nCurrentAppReqs);						//Resets all tdata in every user's struct
					
				}
				
				
					
			}
			
				
			
			
		}
		else
			bIsDone = 1;
	}
	
	
	// Helps exit the while loop to go straight back into vaccination menu
	*pBoolIsExit = 1;
	

	
}


/* 
	displayUserApptSub displays and prompts the user to either manage, cancel or exit
	
	@paran nUID - The User ID of the person who logged in to make/manage an appointment
	
*/
void
displayUserApptSub(int nUID)
{
	int bIsExit = 0;
	char cUserInput;
	char cSel;
	
	
	// Keep prompting user for correct choices
	while(cUserInput != 'E' && cUserInput != 'e' && 
		  cUserInput != 'C' && cUserInput != 'c' && 	
		  cUserInput != 'Q' && cUserInput != 'q' &&
		  !bIsExit )
	{
		
		system("CLS");
		
		printf("\t\t  \033[1;33m    MANAGE APPOINTMENT MENU\n\033[0m\n\n");
		printf("\t\t  Edit your Appointment/s  \t\033[1;36m[E]\033[0m\n");
		printf("\t\t  Cancel Appointment \t\t\033[1;36m[C]\033[0m\n");
		printf("\t\t  Quit   \t\t\t\033[1;36m[Q]\033[0m\n\n");
		
		printf("Input: ");
		scanf(" %c", &cUserInput);
		while ((cSel = getchar()) != '\n' && cSel != EOF);	//Clears input buffer for the next
		
		// For when user doesn't choose a right input
		if (cUserInput != 'E' && cUserInput != 'e' && 
		    cUserInput != 'C' && cUserInput != 'c' && 	
		    cUserInput != 'Q' && cUserInput != 'q' )
		{
			printf("\n\033[1;38;5;202mERROR! Please only use only the ff: ('E'/'C'/'Q')\033[0m\n\n");
			system("PAUSE");
		}
		
		else if ( cUserInput == 'E' || cUserInput == 'e')
		
			// For editing appointments
			displayUserAppt_Man(nUID, &bIsExit);
			
		
		else if ( cUserInput == 'C' || cUserInput == 'c')
			
			// For deleting appointements
			displayUserAppt_Del(nUID, &bIsExit);
		
		else if ( cUserInput == 'Q' || cUserInput == 'q')
			
			// Exit this menu
			bIsExit = 1;
		
		
		
	}
	
}


/* 
	displayUserAppt displays and prompts the user to request an appointment or manage appointments
	
	@paran nUID - The User ID of the person who logged in to make/manage an appointment
*/
void 
displayUserAppt(int nUID)
{

	int bIsExit = 0;
	char cUserInput='\0';
	char cSel;



	
	
	while(cUserInput != 'R' && cUserInput != 'r' && 
		  cUserInput != 'M' && cUserInput != 'm' && 	
		  cUserInput != 'Q' && cUserInput != 'q' &&
		  !bIsExit )
	{

		system("CLS");
		printf("\t\t\t\033[1;33mVACCINATION APPOINTMENT MENU\n\033[0m\n\n");
		printf("\t\tAppointment Request \t\t\t\033[1;36m[R]\033[0m\n");
		printf("\t\tManage Appointment(Cancel or Edit) \t\033[1;36m[M]\033[0m\n");
		printf("\t\tExit Menu \t\t\t\t\033[1;36m[Q]\033[0m\n\n");
		printf("Use the following inputs to access correspondingly ('R'/'M'/'Q'): ");
		scanf(" %c", &cUserInput);
		
		// Clears buffered input
		while ((cSel = getchar()) != '\n' && cSel != EOF);
		
		
		// Check if the user did not input correctly
		if (cUserInput != 'R' && cUserInput != 'r' && 
		   cUserInput != 'M' && cUserInput != 'm' && 	
		   cUserInput != 'Q' && cUserInput != 'q' )
		{
			printf("\n\033[1;38;5;202mERROR! Please only use only the ff: ('R'/'M'/'Q')\033[0m\n");
			system("PAUSE");
		}
			

		  
		   
		   
		   
		else if (cUserInput == 'R' || cUserInput == 'r')
			// Request appointments section for User
			displayUserAppt_Req(nUID);
	
		else if (cUserInput == 'M' || cUserInput == 'm')
		
			// For user's manage or cancel functions
			displayUserApptSub(nUID);
			
	
		else if (cUserInput == 'Q' || cUserInput == 'q')
		
			bIsExit = 1;
		
		//Keeps the loop going
		cUserInput = '\0';
		
		
	}
	
	
	


	

}
 

/* 
	displayUserLogin displays and prompts the user to input valid User ID and password
	
	@paran pIsInputGood - controls the exit vaccination registration menu
	@param pIsMainInputGood  - controls exit for main menu
	@param pIsGoodbye	- controls exit to goodbye to terminate program
	
*/
void 
displayUserLogin(int *pIsInputGood, 
				 int *pIsMainInputGood, 
				 int *pIsGoodbye)
{
	
	struct userTag stUsers[MAX_USERS];
	
	char cUserInput;
	
	int nCurrentUsers;
	int bIsExist;
	int bIsDone;
	int nUID;
	int nAttempts = 3;
	
	String10 sPass;
	
	system("CLS");

	
	bIsExist = doesFileExist("Users.txt");
	getUserData("Users.txt", stUsers, &nCurrentUsers);
	if (!bIsExist || nCurrentUsers ==0)
	{
		if (bIsExist && nCurrentUsers == 0)
			printf("\n\033[1;38;5;202mERROR! There are no user data in the file\033[0m\n");
		
		system("PAUSE");
		bIsExist = 0;
	}
	

	
		
	bIsDone = 0;
	
	
	// Sets a way the user can exit the login
	cUserInput = 'n';
	
	// Ways the login should keep going activate, when there are attempt, user is done logging in once, 
	// or when file does exits and there is content in it.
	while(bIsExist && !bIsDone && nAttempts > 0 && cUserInput != 'y')
	{
		
		system("CLS");
		printf("\t\t\033[1;33m  VACCINATION APPOINTMENT LOGIN\n\033[0m\n\n");
		if(nAttempts<3)
		{
			printf("\n\033[1;38;5;202mLOGIN ERROR!\033[0m You have \033[1;38;5;202m%d attempts\033[0m left. You may have entered the wrong UID or Password.\n", nAttempts);
			printf("\n\nDo you wanna first exit the login? (Y/N): ");
			scanYesNo(&cUserInput);
		}
		
		if (cUserInput != 'y')
		{
				printf("\n");
				printf("UID: ");
				scanID(&nUID);
		
				typePassword(sPass);
				printf("\n");
				
				
				
				bIsDone = isValidUserDetails(stUsers, nUID,
						   					nCurrentUsers, sPass);
						   					 
				
				
				
				if (bIsDone)
				
		
					displayUserAppt(nUID);
				
					
					
				nAttempts -= 1;
				if (nAttempts == 0)
				{
					printf("\n\033[1;38;5;202mALERT! Now terminating program due to 3 attempts being used\033[0m\n");
					
					*pIsInputGood = 1;		// Three boolean loop control, Exits towards the main menu
					*pIsMainInputGood = 1;  // controls exit for main menu
					*pIsGoodbye = 1;		// controls exit to goodbye to terminate program
					
					system("PAUSE");
				}
				
		}	
	

		
		
	}
	

	

}





/* 
	validateVacRegMenu_Input checks and validates the user's inputs, maps them to next function if valid
	
	@param sInput - Input of user of which function to access in the VacReg Menu
	@param nStrLen - strlen of strInput
	@paran pIsInputGood - controls the exit vaccination registration menu
	@param pIsMainInputGood  - controls exit for main menu to terminate program or not
	@param pIsGoodbye	- controls to exit the while loop in vaccination registraion menu
	
	@return 1 if the inputs are valid, else 0
*/
int 
validateVacRegMenu_Input(String30 sInput,
						 int nStrLen,
						 int *pIsInputGood,
						 int *pIsMainInputGood,
						 int *pIsGoodbye)
{
	int nFlag = 0;
	
	lowerStringCase(sInput);
	
	
	// Proceeds to register menu
	if( (nStrLen == 1 && !strcmp(sInput, "r")) || 
		!strcmp(sInput, "register") || 
		!strcmp(sInput, "reg") )
	{
		
		*pIsInputGood = 0;
		displayRegister();
		// Means valid
		nFlag = 1;
		
		
	}
	else if( (nStrLen == 1 && !strcmp(sInput, "a")) || 
			  !strcmp(sInput, "app") || 
			  !strcmp(sInput, "appreqs") ||
			  !strcmp(sInput, "req"))
	{
		*pIsInputGood = 0;
		displayUserLogin(pIsInputGood,				//Setting it to 1 exits the loop on reg menu
					     pIsMainInputGood,			//Setting it to 1 exits the loop on main menu
					     pIsGoodbye);				//Goodbye screen fall back
		nFlag = 1;
		
	}
	else if( (nStrLen == 1 && !strcmp(sInput, "c")) || 
			  !strcmp(sInput, "chatbot") )
	{
		*pIsInputGood = 0;
		displayChatBot();
		nFlag = 1;
		
	}	
	else if( (nStrLen == 1 && (sInput[0]== 'x' || 
			  !strcmp(sInput, "exit") || 
			  sInput[0]== 'q') ) )
	{
		nFlag = 1;
		*pIsInputGood = 1;
	}
	
	return nFlag;
		
		
			
}






/* 
	displayVacRegMenu displays and prompts the user for which function to use; register, appointment, or chatbot
	
	@param pIsMainInputGood  - controls exit for main menu to terminate program or not

*/
void 
displayVacRegMenu(int *pIsMainInputGood )
{
	


	int isLocalInputGood = 0;
	int isValidated = 0;
	int isGoodbye = 0;
	
	char cSel;
	String30 sInput;
	

	

	while(!isLocalInputGood && !isGoodbye)
	{
		system("CLS");
		printf("\t\t\033[1;33m  VACCINATION REGISTRATION MENU\n\033[0m");
	
		printf("\n");
		printf("\n");
		
	
		printf("\t\tRegister   \033[0;36m\t\t\t[R]\033[0m\n");
		printf("\t\tVaccination Appointment   \033[0;36m\t[A]\033[0m\n");
		printf("\t\tChatbot   \033[0;36m\t\t\t[C]\033[0m\n");
		printf("\t\tExit   \033[0;36m\t\t\t\t[Q]\033[0m\n\n");
	
		printf("Input: ");
		
		scanf("%s", sInput);		//Allows the gets to not immediately read the previously enter new line
		
		// Validate the size length being inputted
		warnValidSize(sInput, 30, "VacReg Input");
		while ((cSel = getchar()) != '\n' && cSel != EOF);
		
		
		// Check if the input is correct then map the screen to the next
		isValidated = validateVacRegMenu_Input(sInput, 
										       strlen(sInput), 
											   &isLocalInputGood, 
											   pIsMainInputGood, 
											   &isGoodbye);
		
		
		
		// When input is good and it is not time to exit this loop
		if(isLocalInputGood && !isGoodbye)
			
			// Don't make the main menu terminate
			*pIsMainInputGood = 0;

		// When it i snot valid, feedback to the user
		if (!isValidated)
		{
			printf("\n\033[1;38;5;202mERROR Input:  Please only use the choices\033[0m\n");
			system("PAUSE");
			
		}
		
		
		isValidated = 0;
		
	}

	
}




/*  ------------------ADMIN USER MENU - START ----------------------*/



/* 
	
	addUserMenu displays and prompts the user for adding and acting like registering as a user
	
*/
void
addUserMenu()
{
	struct userTag stUsers[MAX_USERS];
	int nCurrentUsers;
	
	char cUserInput;
	
	// Get all available data of user and store them in a struct
	// also get a gauge on how many users there are
	getUserData("Users.txt", stUsers, &nCurrentUsers);
	
	// Check first if limit was reached or not
	if (nCurrentUsers < MAX_USERS)
	{
		do
		{
			
			system("CLS");
			
			printf("\t\t\033[1;33m  ADMIN'S USER REGISTRATION\n\033[0m\n\n");
			
			// Get all available data of user and store them in a struct
			getUserData("Users.txt", stUsers, &nCurrentUsers);
			
			// Add the userdata and pass the current user size as the index to be added on
			promptUserData(stUsers, nCurrentUsers);
			
			// Appen to file
			saveUserToFile("Users.txt", stUsers[nCurrentUsers]);
			
			// Reset the struct
			resetStructUsers(stUsers, &nCurrentUsers);
			
			// Get all the data from file and store them in a struct
			getUserData("Users.txt", stUsers, &nCurrentUsers);
			
			// Arrange them ascending order based on UID
			arrangeUsers(stUsers, nCurrentUsers);
			
			// Overwrite and clear the file to put the reordered struct array
			overwriteUsersFile("Users.txt", stUsers, nCurrentUsers);
			
			
			// Prompt for yes or no
			printf("Do you want to add more users? (Y/N): ");
			scanYesNo(&cUserInput);
		
		// Continue only when user answers Yes
		}while(cUserInput == 'Y'||cUserInput == 'y');
	}
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! You have reached max user limit\033[0m\n\n");
		system("PAUSE");
	}
	
	
}


/* 
	
	viewUserMenu views all available user data through the struct array
	
*/
void
viewUserMenu()
{
	struct userTag stUsers[MAX_USERS];
	int nCurrentUsers;
	int bIsExists;
	
	// Get all available user data
	getUserData("Users.txt", stUsers, &nCurrentUsers);
	
	// Check if the file exists
	bIsExists = doesFileExist("Users.txt");
	
	// If it doesn't exist then state to user
	if(!bIsExists)
	{
		
		printf("\n\033[1;38;5;202mERROR! There are no user data file to view\033[0m\n");
		system("PAUSE");
	}
	
	// When the file exists but the data in there is empty
	else if (nCurrentUsers == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no users to view in the file.\033[0m\n\n");
		system("PAUSE");

	}
	// Proceed to show all available data
	else
	{
		system("CLS");
		arrangeUsers(stUsers, nCurrentUsers);
		displayAllUserData(stUsers, nCurrentUsers);
		printf("\n\n");
		system("PAUSE");
		
	}
	

}


/* 
	
	editUserMenu displays and prompts the user for which user information to edit
	
*/
void
editUserMenu()
{
	struct userTag stUsers[MAX_USERS];
	int nCurrentUsers;
	int nCurrentUID;
	char cUserInput;
	char sLine[LINE_SIZE];
	String30 sUserInput;
	
	int bIsValidID;
	int bIsFileExist;
	int bIsValidChoice;
	
	// Check if the file exists
	bIsFileExist = doesFileExist("Users.txt");

		
	do
	{
		
		// Get user data
		getUserData("Users.txt", stUsers, &nCurrentUsers);
		
		// If the file exists the proceed to proper edit prompting
		if(bIsFileExist && nCurrentUsers > 0 )
		{
			system("CLS");
			displayAllUserData(stUsers, nCurrentUsers);
			
			// Keep prompting user till he gives a valid ID
			bIsValidID = 0;
			while(!bIsValidID)
			{
				printf("Which User ID do you want to edit: ");
				scanID(&nCurrentUID);
			
				//Validate user ID returns false
				bIsValidID = !validateUserID(stUsers, nCurrentUID);
				
				
				if(!bIsValidID)
				{
					printf("\n\033[1;38;5;202mERROR! User ID not found\033[0m\n");
					system("PAUSE");
				}
				
				
			}
			
			// Clarify to user if this UID is what he wanted
			
			system("CLS");
			
			printf("\n\n");
			
			// Display one user data on screen
			displayOneUserData(stUsers, nCurrentUsers, nCurrentUID);
			
			// Clarify if the user wants this
			printf("\nSelected UID is \033[1;36m%d\033[0m:\n\n", nCurrentUID);
			printf("Do you want to edit something here? (Y/N): ");
			scanYesNo(&cUserInput);
			if(cUserInput == 'Y' || cUserInput == 'y' )
			
				// Turns on loop below
				bIsValidChoice = 0;
			else
			
				// Turns it off
				bIsValidChoice = 1;
			
			// While user does not choose a valid input
			while (!bIsValidChoice)
			{
				system("CLS");
			
				printf("\n\n");
				
				getUserData("Users.txt", stUsers, &nCurrentUsers);
				// Display one user data on screen
				displayOneUserData(stUsers, nCurrentUsers, nCurrentUID);
				
				printf("EDITING MENU\n\n");
				printf("Choose 'all' or one of the following individual elements to edit: \n");
				printf("\033[1;33m'UID', 'Password', 'Name', 'Address', 'Contact', 'Dose1', 'Dose2, Boost'\033[0m\n");
				
				// Get category of which the users wishes to edit
				fgets(sLine, LINE_SIZE, stdin);
				sscanf(sLine, "%[^\n]", sUserInput);
				
				// Validate the category
				editSelectedUser(sUserInput, stUsers, &nCurrentUID, nCurrentUsers, &bIsValidChoice);
								
				// Arrange the potentially newly modified contents
				arrangeUsers(stUsers, nCurrentUsers);
				
				// Overwrite to file
				overwriteUsersFile("Users.txt", stUsers, nCurrentUsers);
				
				// Reset all struct
				resetStructUsers(stUsers, &nCurrentUsers);
					
				// If choice was valid then it successful
				if (bIsValidChoice)
				{
					system("CLS");
			
					printf("\n\n");
					// Get user data
					getUserData("Users.txt", stUsers, &nCurrentUsers);
					
					// Display one user data on screen
					displayOneUserData(stUsers, nCurrentUsers, nCurrentUID);
					
					printf("\n\033[1;32mSuccessfully edited User ID %d.\033[0m\n", nCurrentUID);
					
					resetStructUsers(stUsers, &nCurrentUsers);

					
					
				}
					
					
				// User entered wrongly
				else
					printf("\n\033[1;38;5;202mERROR! Please only enter from the input choices above colored yellow and those with data.\033[0m\n\n");
					
				// Input the yes or no only and see if user wants to edit another
				
				
				system("PAUSE");
			}
			printf("\nDo you want to select another user to edit? (Y/N): ");
			scanYesNo(&cUserInput);
			
			
		}
		
		// Case when there is no more data to read
		else if (nCurrentUsers == 0)
		{
			system("CLS");
			printf("\n\033[1;38;5;202mERROR! There are no more data to edit in the file.\033[0m\n\n");
			system("PAUSE");

		}
		else
		{
			printf("\n\033[1;38;5;202mNO USER DATA AVAILABLE\033[0m\n");
			system("PAUSE");
		}
	
		
		
	}while ((cUserInput == 'Y' || cUserInput == 'y') && bIsFileExist);
	
	

}


/* 
	
	deleteUserMenu displays and prompts the user for which data to delete
	
*/
void
deleteUserMenu()
{
	struct userTag stUsers[MAX_USERS];
	int nCurrentUsers;
	int nSelectedUID;
	
	char cUserInput;
	
	
	int bIsValidID;
	int bIsFileExist;
	
	
	// Check if file exists
	bIsFileExist = doesFileExist("Users.txt");

		
	do
	{
		getUserData("Users.txt", stUsers, &nCurrentUsers);
		// If file exists proceed to ask the user for which ID to delete
		if(bIsFileExist && nCurrentUsers > 0)
		{
			system("CLS");
			displayAllUserData(stUsers, nCurrentUsers);
			
			while(!bIsValidID)
			{
				
				printf("Which User ID do you want to delete: ");
				scanID(&nSelectedUID);
			
				//Validate user ID returns false
				bIsValidID = !validateUserID(stUsers, nSelectedUID);
				
				
				if(!bIsValidID)
				{
					printf("\n\033[1;38;5;202mERROR! User ID not found\033[0m\n");
					system("PAUSE");
					
				}
				
			}
			system("CLS");
			
			// Show what the user selected
			printf("\n\n");
			displayOneUserData(stUsers, nCurrentUsers, nSelectedUID);
			printf("\nSelected UID is \033[1;36m%d\033[0m:\n\n", nSelectedUID);
			
			printf("Do you want to delete this data? (Y/N): ");
			scanYesNo(&cUserInput);
			
			if (cUserInput == 'Y' || cUserInput == 'y')
			{
				
				// Proceed to delete the user on the struct array
				deleteUser(stUsers, nSelectedUID, nCurrentUsers);
				
				// Save the contents of the struct array
				overwriteUsersFile("Users.txt", stUsers, nCurrentUsers);
				
				// Get the data on the file and put them in a struct array
				getUserData("Users.txt", stUsers, &nCurrentUsers);
				system("CLS");
				
				printf("\n\033[1;32mSuccessfully deleted User ID %d\033[0m\n\n", nSelectedUID);
				system("PAUSE");
				
			}
			
			// Prompt user if he/she wants to delete some other user data
			printf("Do you want to delete some other user data? (Y/N): ");
			scanYesNo(&cUserInput);
			if (cUserInput == 'Y' || cUserInput == 'y')
				// Gets the loop ready for the next user to delete
				bIsValidID = 0;
			
		}
		
		// Case when there is file but no users
		else if (nCurrentUsers == 0)
		{
			system("CLS");
			printf("\n\033[1;38;5;202mERROR! There are no more data to delete in the file.\033[0m\n\n");
			system("PAUSE");
			
			// Triggers exit the loop
			bIsFileExist = 0;

		}
		else
		{
			printf("\n\033[1;38;5;202mERROR! There are no user data file to delete items in\033[0m\n");
			system("PAUSE");
		}
	
		
		
	}while ((cUserInput == 'Y' || cUserInput == 'y') && bIsFileExist);
	
	
}
/*  ------------------ADMIN USER MENU - END ----------------------*/







/*  ------------------ADMIN APPS MENU - START ----------------------*/


/* 
	
	deleteUserMenu displays and prompts the user for appointment to request
	
*/
void
addAppMenu()
{
	struct appTag stApps[MAX_REQS];
	int nCurrentAppReqs;
	int nSelectedUID;
	
	char cUserInput;
	
	// Gets all available data from the appointment.txt
	getAppData("Appointment.txt", stApps, &nCurrentAppReqs);
	
	// Makes sure user doesn't go over the appointment limit
	if (nCurrentAppReqs < MAX_REQS)
	{
		do
		{
			
			system("CLS");
			printf("\t\t\033[1;33m  ADMIN'S APPOINTMENT REQUEST\n\033[0m\n\n");
			// Prompts the UID that the appointment is under
			printf("Under what UID is this appointment request? ");
			scanID(&nSelectedUID);
			
			// Gets all available data from the appointment.txt
			getAppData("Appointment.txt", stApps, &nCurrentAppReqs);
			
			// Prompt user of all required fields
			promptAppData(stApps, nCurrentAppReqs, nSelectedUID);
			
			// Append the new struct data to the file
			saveAppToFile("Appointment.txt", stApps[nCurrentAppReqs]);
			
			// Reset all info in struct array
			resetStructAppReqs(stApps, &nCurrentAppReqs);
			
			// Get all appointment data
			getAppData("Appointment.txt", stApps, &nCurrentAppReqs);
			
			// Arrange on ascending order based on app ID
			arrangeAppReqs(stApps, nCurrentAppReqs);
			
			// Overwrite and save to file
			overwriteAppReqsFile("Appointment.txt", stApps, nCurrentAppReqs);
			
			// Prompt if the admin wants to prompt more Appointments
			printf("Do you want to add more App Reqs? (Y/N): ");
			scanYesNo(&cUserInput);
			
		}while(cUserInput == 'Y' || cUserInput == 'y');
		
	}
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! You have reached max appointment limit\033[0m\n\n");
		system("PAUSE");
	}
	

}


/* 
	
	viewAppMenu displays and prompts the user for all available appointment data
	
*/
void
viewAppMenu()
{
	struct appTag stApps[MAX_USERS];
	int nCurrentApps;
	int bIsExists;
	
	// Check if the file exists
	bIsExists = doesFileExist("Appointment.txt");
	getAppData("Appointment.txt", stApps, &nCurrentApps);
	
	// Warn that the file does not exists
	if (!bIsExists)
	{
		printf("\n\033[1;38;5;202mERROR! There are no appointment data file to view.\033[0m\n");
		system("PAUSE");
	}
	
	// If it exists then proceed to show all data
	else if (nCurrentApps == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no more data to view in the file.\033[0m\n\n");
		system("PAUSE");
	}
	else
	{
		system("CLS");
		arrangeAppReqs(stApps, nCurrentApps);
		displayAllAppData(stApps, nCurrentApps);
		printf("\n\n");
		system("PAUSE");
	}

	
	

}


/* 
	
	editAppMenu displays and prompts the user for all available appointment data and asks which one to edit
	
*/
void
editAppMenu()
{
	
	int bIsDone;
	int bIsValidCateg;
	int bIsDecided;
	int bIsExists;
	int bIsValidID;
	
	int nCurrentAppReqs;
	int nCurrentAppID;

	char cUserInput;
	char sLine[LINE_SIZE];
	String30 sUserInput;
	
	struct appTag stAppReqs[MAX_REQS];

	system("CLS");
	
	// Set that the user is not done on checking which to edit
	bIsDone = 0;
	
	// See if the file exists
	bIsExists = doesFileExist("Appointment.txt");
	
	// Warn the file does not exists
	if (!bIsExists)
	{
		printf("\n\033[1;38;5;202mFILE NOT FOUND! Try to add some appointments back in the menu\033[0m\n");
		system("PAUSE");
		
	}
		
	while(bIsExists && !bIsDone)
	{
		// User has not decided on which appointment to choose
		bIsDecided = 0;									
		
		system("CLS");
	    // Gets all collection of appointments
		getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
		printf("\nUser Appointments: \n\n");
		
		// Displays all appointment data
		displayAllAppData(stAppReqs, nCurrentAppReqs);
		
		// If there are contents in the file then proceed asking
		if (nCurrentAppReqs > 0)
		{
			// Keep prompting for which appointment user want's to edit
			while(!bIsDecided && (cUserInput != 'X' || cUserInput != 'x') )
			{
				//Repeatedly asks user for correct Appointment ID until it is a valid one selected
				bIsValidID = 0;
				while(!bIsValidID)
				{
					
					printf("Which \033[1;36mAppointment ID\033[0m do you wish to edit:  ");
			   		scanID(&nCurrentAppID);
			   		
					//Validate appointment ID if it is found
					bIsValidID = !validateAppID(stAppReqs, nCurrentAppID, nCurrentAppReqs);
					
					// The app ID is not found
					if(!bIsValidID)
					
						printf("\n\033[1;38;5;202mERROR! Appointment ID not found\033[0m\n");
					
					
				}
				
				system("CLS");
				
				// Display the appointment data he wishes to edit
				displayOneAppData(stAppReqs, nCurrentAppReqs, nCurrentAppID);
				
				// Shows the App ID the user wants to edit
				printf("Selected App ID is \033[1;36m%d\033[0m:\n", nCurrentAppID);
				
				// Prompt user to either pursue editing this data or not
				printf("Tool Tip: Type ['X'] in the following prompt to exit editing menu\n\n");
				printf("Do you want to edit this appointment? (Y/N/X): ");
				scanYesNoX(&cUserInput);
				
				
				if (cUserInput == 'Y' || cUserInput == 'y') 
			   		
			   		// Means user decided on the appointment ID he/she wants to edit
			   		bIsDecided = 1;
			   		
			   	// User can exit
				else if (cUserInput == 'X' || cUserInput == 'x')
				{
					bIsDecided = 1;
					bIsDone = 1;
				}
				else
				{
					system("CLS");
					displayAllAppData(stAppReqs, nCurrentAppReqs);

				}

				
			}

			// Sets that the user is invalid at inputs
			bIsValidCateg = 0;
			// Only prompt for category if user is not yet done
			while (!bIsDone && !bIsValidCateg)
			{
			

				printf("Which data do you want to edit? (You can choose from the ff): \n");
				printf("\033[1;33m'App ID', 'Name', 'Location', 'Vaccine', 'date', 'time', 'dose'\033[0m \n");
				
				

				fgets(sLine, LINE_SIZE, stdin);		
				sscanf(sLine, "%[^\n]", sUserInput);
				
				editSelectedApp(sUserInput, 		// User Input of which property to edit
							    stAppReqs, 			// Struct data to compare
							    stAppReqs, 			// Struct data to manipulate (duplicated due to parameter reqs)
							    &nCurrentAppID, 	// App ID is passed to be searched
							    nCurrentAppReqs,	// Checks what to edit and prompts user respectively
								&bIsValidCateg);		// Boolean if it is a valid category to edit
				
				

				arrangeAppReqs(stAppReqs, nCurrentAppReqs);
				overwriteAppReqsFile("Appointment.txt", stAppReqs, nCurrentAppReqs);	//Overwrite them in file
			    resetStructAppReqs(stAppReqs, &nCurrentAppReqs);						//Resets all tdata in every user's struct				

				
				
				system("CLS");
				
				getAppData("Appointment.txt", stAppReqs, &nCurrentAppReqs);
				displayOneAppData(stAppReqs, nCurrentAppReqs, nCurrentAppID);
				
				// Ask if user wants to edit more appointment data
				if (bIsValidCateg)
				{

					printf("\n\033[1;32mSuccesfully edited data! \033[0m\n\n");
					printf("Do you want to edit more Appointment IDs? (Y/N): ");
					scanYesNo(&cUserInput);
					if (cUserInput == 'N' || cUserInput == 'n')
					{
						
						printf("Exiting Editing Menu\n\n");
						bIsDone = 1;
						system("PAUSE");
					}
				}
					
				
					
				
				
			}
				
			
			
		}
		
		// When there are no Appointment data scanned
		else if (nCurrentAppReqs == 0)
		{
			system("CLS");
			printf("\n\033[1;38;5;202mERROR! There are no more data to edit in the file.\033[0m\n\n");
			system("PAUSE");
			bIsDone = 1;
		}
		else
			bIsDone = 1;
	}
	
	

	


}


/* 
	
	deleteAppMenu displays and prompts the user for all available appointment data and asks which one to delete
	
*/
void
deleteAppMenu()
{
	struct appTag stAppReqs[MAX_USERS];
	int nCurrentApps;
	int nSelectedAppID;
	
	char cUserInput;
	
	
	int bIsValidID;
	int bIsFileExist;
	
	
	
	bIsFileExist = doesFileExist("Appointment.txt");

	
	do
	{
		getAppData("Appointment.txt", stAppReqs, &nCurrentApps);
		if (nCurrentApps == 0)
			
			// declares the file as not existing if the appointment data shows no appointments
			bIsFileExist = 0;
		
		if(bIsFileExist && nCurrentApps > 0)
		{
				
			system("CLS");
			displayAllAppData(stAppReqs, nCurrentApps);
			
			// Keep prompting for a valid ID
			bIsValidID = 0;
			
			while(!bIsValidID)
			{
				
				// Appointment ID proper prompting input buffer
				printf("Which \033[1;36mAppointment ID\033[0m do you want to delete: ");
				scanID (&nSelectedAppID);
				
				//Validate appointment ID, whether it can be found or not
				bIsValidID = !validateAppID(stAppReqs, nSelectedAppID, nCurrentApps);
				
				
				// The 
				if(!bIsValidID)
				
					printf("\n\033[1;38;5;202mERROR! Appointment ID not found\033[0m\n");

					
				
				
			}
			system("CLS");
			// show the appointment ID to edit
			printf("Selected Appointment ID is %d:\n\n", nSelectedAppID);	
			displayOneAppData(stAppReqs, nCurrentApps, nSelectedAppID);
			printf("Do you want to delete this data? (Y/N): ");
			scanYesNo(&cUserInput);
			
			// If user answers yes then proceed to delete the select App ID
			if (cUserInput == 'Y' || cUserInput == 'y')
			{
				
				deleteApp(stAppReqs, nSelectedAppID, nCurrentApps);

				overwriteAppReqsFile("Appointment.txt", stAppReqs, nCurrentApps);
				getAppData("Appointment.txt", stAppReqs, &nCurrentApps);
				system("CLS");
				
				printf("\033[1;32mSuccessfully deleted Appointment ID %d\033[0m\n\n", nSelectedAppID);
				system("PAUSE");
				
			}
			else
			
				printf("\033[1;33mCancelling Appointment Deletion...\033[0m\n\n");
	
			
			// Prompt user if he/she wants to delete more appointment data
			printf("Do you want to delete some other Appointment data? (Y/N): ");
			scanYesNo(&cUserInput);

		}
		else if (nCurrentApps == 0)
		{
			system("CLS");
			printf("\n\033[1;38;5;202mERROR! There are no more data to delete in the file.\033[0m\n\n");
			system("PAUSE");
			bIsFileExist = 0;
		}
		
		// There is no file data to read
		else
		{
			printf("\n\033[1;38;5;202mERROR! There are no appointment data to delete\033[0m\n");
			system("PAUSE");
		}
	
		
	// Keep prompting user as user answers yes or when the file exists
	}while ((cUserInput == 'Y' || cUserInput == 'y') && bIsFileExist);
}


/*  ------------------ADMIN APPS MENU - END ----------------------*/






/*  ------------------ADMIN CHAT MENU - START ----------------------*/


/* 
	
	addChatMenu displays and prompts the user for all available chatbot question and answer to add
	
*/
void
addChatMenu()
{
	int nChatSize;
    struct chatTag stChats[MAX_CHAT];
	
	//Gauges the max chat size
	getChatData("Chatbot.txt", stChats, &nChatSize);
	if(nChatSize < MAX_CHAT)
	{
		system("CLS");
		printf("\t\t\033[1;33m  ADMIN'S CHATBOT ADD MENU\n\033[0m\n\n");
		
		// Already repeatedly prompts the user if he/she wants to add more data or not
		addChatData("Chatbot.txt");
		system("CLS");
		
		// Gets all data and shows them on screen
		getChatData("Chatbot.txt", stChats, &nChatSize);
		displayAllChatData(stChats, nChatSize);
		printf("\n");
		
		// Show data has been successfully added
		printf("\n\033[1;32mChat Data has been successfully added! \033[0m\n");
		system("PAUSE");
		
	}
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! You have reached chatbot data limit\033[0m\n\n");
		system("PAUSE");
	}


}


/* 
	
	viewChatMenu displays all available chatbot data
	
*/
void
viewChatMenu()
{
	int nChatSize;
    
	int bIsExists;
	struct chatTag stChats[MAX_CHAT];
	
	// Find the file available on chatbot
	bIsExists = doesFileExist("Chatbot.txt");
	getChatData("Chatbot.txt", stChats, &nChatSize);
	// Warn the user that the the file is not found
	if(!bIsExists)
	{
		
		printf("\n\033[1;38;5;202mERROR! There are no chatbot data file to view\033[0m\n");
		system("PAUSE");
	}
	else if (nChatSize == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no more data to view in the file.\033[0m\n\n");
		system("PAUSE");

	}
	else
	{
		//Chat Viewing All
		system("CLS");
		
		
		// Display all available chatbot data
		displayAllChatData(stChats, nChatSize);
		printf("\n");
		system("PAUSE");
	}

	
	

}


/* 

	editChatMenu displays and prompts user for which category of the question answer to edit in the question bank data
	
*/
void
editChatMenu()
{
  	
    struct chatTag stChats[MAX_CHAT];

	char sUserCategInput[LINE_SIZE];
	
	char cUserInput;
	char cSel;
	
	int nNumID;
	int nChatSize;
	
	int nCheckScanf;
	
	int bIsDone;
	int bIsExists;
	int bIsValidID;
	int bIsWantEdit;
	int bIsValidCateg;
	
	
	system("CLS");

	
	// Check if the file exists
	bIsExists = doesFileExist("Chatbot.txt");
	
	// Gauge the size of the chat data bank
	getChatData("Chatbot.txt", stChats, &nChatSize);
	
	// Set that the user is not done checking which to edit and hasn't entered a valid ID
	bIsDone = 0;
	bIsValidID = 0;
	
	
	
	// If the file does not exist, then tell it to user
	if (!bIsExists)
	{
		printf("\n\033[1;38;5;202mERROR! No file found, Try to add some chatbot questions and answer back in the menu.\033[0m\n");
		system("PAUSE");
		
	}
	
	// When the file does not read data at all
	else if (nChatSize == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no more data to edit in the file.\033[0m\n\n");
		system("PAUSE");
		bIsExists = 0;

	}
	
	// 	Proceed to ask which category to edit if file exist
	while(bIsExists && !bIsDone)
	{
		
		// Set that the user is not decided on which to edit
		bIsWantEdit = 0;
		
		// Display all chatbot data
		system("CLS");
		getChatData("Chatbot.txt", stChats, &nChatSize);
		displayAllChatData(stChats, nChatSize);
		printf("\n");
		
		// Keep prompting user a valid question number he/she wants to modify
		while(!bIsValidID)
		{
			printf("Which \033[0;36mQuestion Number\033[0m would you like to modify? ");
			nCheckScanf = scanf("%d", &nNumID);
			
			// Clears the input area if there are extra characters
			while ((cSel = getchar()) != '\n' && cSel != EOF);
			
			// Check if the number is correct or wrong
			if (nCheckScanf == 0)
				bIsValidID = 0;
			else
				// Check if the question number exists
				bIsValidID = checkChatIDExists(stChats, nChatSize, nNumID);
			
			// If still not valid then state to user
			if(!bIsValidID)
				printf("\033[1;38;5;202mERROR! Please enter a valid question number.\033[0m\n");
				
			// If the ID is valid then proceed to ask user if he/she wants to edit the Chatbot data
			else if(bIsValidID)
			{
				
				system("CLS");
				displayOneChatData(stChats, nChatSize, nNumID);
				printf("Do you want to edit this data? (Y/N): ");
				scanYesNo(&cUserInput);
				if (cUserInput == 'Y'|| cUserInput == 'y')
					bIsWantEdit = 1;
				
			}
			
		}
		
		// The user would then proceed to be asked on which data they want to edit on about
		bIsValidCateg = 0;
		while (bIsWantEdit && !bIsValidCateg)
		{
			system("CLS");
			displayOneChatData(stChats, nChatSize, nNumID);
			printf("What \033[0;36mproperty\033[0m of Question %d would you like to modify? \033[1;36m(Answer/Question):\033[0m \n", nNumID);
			
			fgets(sUserCategInput, LINE_SIZE, stdin);
			
			// Makes sure the user does not go too much characers
			warnValidSize(sUserCategInput, 30, "(Answer/Question): ");
			editSelectedChat(sUserCategInput, stChats, nChatSize, nNumID, &bIsValidCateg);
			overwriteChatFile("Chatbot.txt", stChats, nChatSize);
			
			if(bIsValidCateg)
			{
				printf("\n\033[1;32mSuccessfully edited Question No. %d.\033[0m\n", nNumID);
				system("PAUSE");
			}
			
			
		}
		
		// Ask if user wants to edit more question or not
		printf("Do you want to edit some more questions and answers? (Y/N): ");
		scanYesNo(&cUserInput);
		if(cUserInput != 'Y' && cUserInput != 'y')
		
			bIsDone = 1;
		else
		{
			bIsValidID = 0;
			bIsDone = 0;
		}
		    
			



	}
	
	

	


}


/* 

	deleteChatMenu displays and prompts user for which category of the question answer to delete in the question bank data
	
*/
void
deleteChatMenu()
{
  	
    struct chatTag stChats[MAX_CHAT];
    

	char cUserInput;
	char cSel;

	int nNumID;
	int nChatSize;
		
	int bIsDone;
	int bIsExists;
	int bIsValidID;
	int bIsWantDelete;
	
	int nCheckScanf;

	system("CLS");

	
	bIsExists = doesFileExist("Chatbot.txt");
	
	// Helps gauge its size
	getChatData("Chatbot.txt", stChats, &nChatSize);
	
	// Set that the user is not done checking which to edit and hasn't entered a valid ID
	bIsDone = 0;
	bIsValidID =0;
	
	if (!bIsExists)
	{
		printf("\n\033[1;38;5;202mERROR! No file found, There is no Chatbot data to delete.\033[0m\n\n");
		system("PAUSE");
		
	}
	else if (nChatSize == 0)
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! There are no more data to edit in the file.\033[0m\n\n");
		system("PAUSE");
		bIsExists = 0;

	}
	
	
	// Set that the user first wants to delete something
	cUserInput = 'Y';
	
	// Continue the prompt while file exists and 
	while(bIsExists && !bIsDone && (cUserInput == 'Y' || cUserInput == 'y'))
	{
		
		// Set that the user has nothing to want to delete
		bIsWantDelete = 0;
		system("CLS");
		getChatData("Chatbot.txt", stChats, &nChatSize);
		displayAllChatData(stChats, nChatSize);
		printf("\n");
		
		// Keep prompting user of a valid question number that he/she might wanna delete
		while(!bIsValidID)
		{
			
			printf("Which \033[0;36mQuestion Number\033[0m would you like to delete? ");
			nCheckScanf = scanf("%d", &nNumID);
			while ((cSel = getchar()) != '\n' && cSel != EOF);	
			
			
			if (nCheckScanf == 0)
				bIsValidID = 0;
			else
				bIsValidID = checkChatIDExists(stChats, nChatSize, nNumID);
				
			

			
			if(!bIsValidID)
				printf("Please enter a valid question number from the displays above.\n\n");
			else if(bIsValidID)
			{
				
				system("CLS");
				displayOneChatData(stChats, nChatSize, nNumID);
				printf("Do you want to delete this data? (Y/N): ");
				scanYesNo(&cUserInput);
				if (cUserInput == 'Y'|| cUserInput == 'y')
					bIsWantDelete = 1;
				
			}
			
		}
		
		// User wants to delete then proceed to delete the data on the struct
		if (bIsWantDelete)
		{
			system("CLS");
			
			displayOneChatData(stChats, nChatSize, nNumID);
			deleteChat(stChats, nChatSize, nNumID);
			overwriteChatFile("Chatbot.txt", stChats, nChatSize);
			printf("\n\033[1;32mSuccessfully deleted Question Number %d.\033[0m\n", nNumID);
			printf("\n");
			
		}

		
		// Checks if user wants to delete more question and asnwers
		printf("Do you want to delete some other questions and answers? (Y/N): ");
		scanYesNo(&cUserInput);
		if(cUserInput != 'Y' && cUserInput != 'y')
			
			// Set that the user is now done
			bIsDone = 1;
		else
			// Reset the valid ID back to zero as the user might prompt another question number
			bIsValidID = 0;
		
		getChatData("Chatbot.txt", stChats, &nChatSize);
		if (nChatSize == 0)
		{
			system("CLS");
			printf("\n\033[1;38;5;202mERROR! There are no more data to delete in the file.\033[0m\n\n");
			system("PAUSE");
			bIsExists = 0;
		}


	}
	
	
}




/*  ------------------ADMIN CHAT MENU - END ----------------------*/


/* 

	validateMenu_Input checks the user's input to put him to the correct function screen he wishes to be
	
	@param pBoolIsDone - boolean that controls the while loop at the Category of data management menu from admin
	@param sInput - the string input of which function the admin wishes to access
	@param funcAdd - serves as the pointer to the means of activating a function for adding
	@param funcView - serves as the pointer to the means of activating a function for viewing
	@param funcEdit - serves as the pointer to the means of activating a function for editing
	@param funcDelete - serves as the pointer to the means of activating a function for deleting

*/
void
validateMenu_Input(int *pBoolIsDone, 			
				   String30 sInput,
				   void (*funcAdd)(),
				   void (*funcView)(),
				   void (*funcEdit)(),
				   void (*funcDelete)())
{
	
	
	int nStrLen;
	
	
	nStrLen = strlen(sInput);
	lowerStringCase(sInput);
	
	
	if( (nStrLen == 1 && !strcmp(sInput, "a")) || 
		!strcmp(sInput, "add") )

		funcAdd();
		
	
	else if( (nStrLen == 1 && !strcmp(sInput, "v")) || 
			  !strcmp(sInput, "viewall") ||
			  !strcmp(sInput, "view") )
	
		funcView();

		
	else if( (nStrLen == 1 && !strcmp(sInput, "e")) || 
			  !strcmp(sInput, "edit") )
		funcEdit();

		
		
	else if( (nStrLen == 1 && !strcmp(sInput, "d")) || 
			  !strcmp(sInput, "delete") ||
			  !strcmp(sInput, "del") )
	
		funcDelete();

		
					
	else if( (nStrLen == 1 && (sInput[0]== 'x' || 
			  !strcmp(sInput, "exit") || 
			  sInput[0] == 'q') ) )
	
		*pBoolIsDone = 1;
		
	
	else
	{
		printf("\n\033[1;38;5;202mERROR! Please Input only the given choices above.\033[0m\n");
		system("PAUSE");
	}
	
}



/* 

	displayAdm_DataUserMenu displays and prompts user for which function for the admin to access for user management
	
*/
void
displayAdm_DataUserMenu()
{
	char cSel;
	String30 sUserInput;
	int bIsDone;

	
	// Keep prompting user until he/she declares he/she is done in this menu screen
	bIsDone = 0;
	while(!bIsDone)
	{
		system("CLS");
		
		// The escape char 033[38;2;245;90;193m  means darkish pink
		printf("\t\t\033[38;2;245;90;193m  USER \033[1;33mDATA MANAGEMENT MENU\n\n\033[0m");
		
		printf("\t\t   Add User \t\t\033[1;36m[A]\033[0m\n");	  
		printf("\t\t   View All \t\t\033[1;36m[V]\033[0m\n"); 
		printf("\t\t   Edit User \t\t\033[1;36m[E]\033[0m\n"); 
		printf("\t\t   Delete User \t\t\033[1;36m[D]\033[0m\n"); 
		printf("\t\t   Exit \t\t\033[1;36m[Q]\033[0m\n\n"); 
		
		
		printf("Input: ");
		scanf("%s", sUserInput);
		
		
		while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
		validateMenu_Input(&bIsDone, 							//While loop control for exit
					   	   sUserInput,
					   	   addUserMenu,
					   	   viewUserMenu,
					   	   editUserMenu,
					   	   deleteUserMenu);

		
		
	}

	
	
}



/* 

	displayAdm_ManageAppsMenu displays and prompts user for which function for the admin to access for app management
	
*/
void 
displayAdm_ManageAppsMenu()
{
	
	char cSel;
	int bIsDone;
	String30 sUserInput;
	
	
	// Keep prompting user until he/she declares he/she is done in this menu screen
	bIsDone = 0;
	while(!bIsDone)
	{

		system("CLS");
		
		// The escape char 033[38;2;245;90;193m  means darkish pink
		printf("\t\t\033[38;2;245;90;193m  APPOINTMENT \033[1;33mDATA MANAGEMENT MENU\n\n\033[0m");
		
		printf("\t\t      Add App \t\t\033[1;36m[A]\033[0m\n");	  
		printf("\t\t      View All \t\t\033[1;36m[V]\033[0m\n"); 
		printf("\t\t      Edit App \t\t\033[1;36m[E]\033[0m\n"); 
		printf("\t\t      Delete App \t\033[1;36m[D]\033[0m\n"); 
		printf("\t\t      Exit \t\t\033[1;36m[Q]\033[0m\n\n"); 
		
		printf("Input: ");
		scanf("%s", sUserInput);
		while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
		validateMenu_Input(&bIsDone, 							//While loop control for exit
					   	   sUserInput,
					   	   addAppMenu,
					   	   viewAppMenu,
					   	   editAppMenu,
					   	   deleteAppMenu);	
		
	}


}


/* 

	displayAdm_ManageAppsMenu displays and prompts user for which function for the admin to access for chatbot management
	
*/
void 
displayAdm_ChatBotMenu()
{
	
	int bIsDone;
	String30 sUserInput;
	char cSel;
	bIsDone = 0;
	while(!bIsDone)
	{
		system("CLS");
		printf("\t\t\033[38;2;245;90;193m  CHATBOT \033[1;33mDATA MANAGEMENT MENU\n\n\033[0m");
		
		printf("\t\t      Add QnA \t\t\033[1;36m[A]\033[0m\n");	  
		printf("\t\t      View All \t\t\033[1;36m[V]\033[0m\n"); 
		printf("\t\t      Edit QnA \t\t\033[1;36m[E]\033[0m\n"); 
		printf("\t\t      Delete QnA \t\033[1;36m[D]\033[0m\n"); 
		printf("\t\t      Exit \t\t\033[1;36m[Q]\033[0m\n\n"); 
		printf("Input: ");
		scanf("%20s", sUserInput);
		while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
		validateMenu_Input(&bIsDone, 							//While loop control for exit
				   	   	   sUserInput,
				   	   	   addChatMenu,
				   	   	   viewChatMenu,
				   	   	   editChatMenu,
				   	       deleteChatMenu);	
		
	}

	

}


/* 

	addTxt checks if the filename entered ends with ".txt" or not, else it concatenates a ".txt" to it
	
	@param sText is the filename string entered by the user
	
*/
void
addTxt(char sText[])
{
	char sTemp[LINE_SIZE];
	int nStr_Len = strlen(sText);
    int nSuffix_Len = strlen(".txt");
    
    // set a seperate string to manipulate
    strcpy(sTemp, sText);
																			
	if ( nStr_Len > 1 &&													// Check if the string isn't at one character
		(strncmp(sText+(nStr_Len-nSuffix_Len), ".txt", nSuffix_Len) ||		// Check if string has a .txt at the end
		 nStr_Len < nSuffix_Len) )											// If its less than the string length of ".txt", concatenate it
			 																
		strcat(sTemp, ".txt");												// concatenate with ".txt"
	
	if(strlen(sTemp) <= 30);	// Makes sure it doesn't go over the allocated 30 char bytes when passing it to the sText
		strcpy(sText, sTemp);
		
}


/* 

	displayExport displays and prompts user for which data or info he must export
	
*/
void 
displayExport()
{
	struct userTag stUsers[MAX_USERS];
	struct appTag stApps[MAX_REQS];
	struct chatTag stChats[MAX_CHAT];
	
	String30 sUserInput;
	String30 sFileInput;
	char sLine[LINE_SIZE];
	
	int i;
	
	int bIsWantExit;
	int bIsValidChoice;
	
	int nUserSize;
	int nAppSize;
	int nChatSize;
	
	
	// Sets that the user decided a valid choice but does not want to exit
	bIsValidChoice = 1;
	bIsWantExit = 0;
	
	// Keep prompting til the user inputs a valid choice
	do
	{
		system("CLS");
		printf("\t\t       \033[38;2;245;90;193m  EXPORT \033[1;33mMENU\n\n\033[0m");
		printf("\t\t%-25s", "User data   \033[1;36m\t\t[1]\033[0m");
		printf("\n");
		printf("\t\t%-25s", "Appointment data   \033[1;36m\t[2]\033[0m");
		printf("\n");
		printf("\t\t%-25s", "Chatbot data   \033[1;36m\t\t[3]\033[0m");
		printf("\n");
		printf("\t\t%-25s", "All data   \033[1;36m\t\t[4]\033[0m");
		printf("\n");
		printf("\t\t%-25s", "Exit   \033[1;36m\t\t\t[0]\033[0m");
		printf("\n");
		printf("\n");
		printf("Which data set would you like to export? \n");
		fgets(sLine, LINE_SIZE, stdin);
		warnValidSize(sLine, 30, "data");
		sscanf(sLine, "%[^\n]", sUserInput);
		
		
		// Check if the input of the user is one of the choices
		
		// Proceed to get all data of stUsers
		if (sUserInput[0] == '1')
		{
			// State it was a valid choice
			bIsValidChoice = 1;
			
			// Get the data
			getUserData("Users.txt", stUsers, &nUserSize);
		}
		
		// Proceed to get all data of stApps	
		else if (sUserInput[0] == '2')
		{
			bIsValidChoice = 1;
			getAppData("Appointment.txt", stApps, &nAppSize);
		}
		
		
		// Proceed to get all data of stChats
		else if (sUserInput[0] == '3')
		{
			bIsValidChoice = 1;
			getChatData("Chatbot.txt", stChats, &nChatSize);	
		}
		
		// Proceed to get all data of all struct types
		else if (sUserInput[0] == '4')
		{
			bIsValidChoice = 1;
			getUserData("Users.txt", stUsers, &nUserSize);
			getAppData("Appointment.txt", stApps, &nAppSize);
			getChatData("Chatbot.txt", stChats, &nChatSize);
		}
		
		// Exit
		else if (sUserInput[0] == '0')
		{
			bIsWantExit = 1;
			bIsValidChoice = 1;
		}
		
		// State it was a valid choice
		else
		{
			bIsValidChoice = 0;
			printf("\n\033[1;38;5;202mERROR! Please enter between 1/2/3/4/0\033[0m\n");
			system("PAUSE");
		}
			
		
	}while(!bIsValidChoice);
	
	
	// If the choice was all and at least one of the files are empty then dont't proceed
	if (sUserInput[0] == '4' && ( nUserSize == 0 || 
		nAppSize == 0 || nChatSize == 0))
	{
		printf("\n\033[1;38;5;202mERROR! There is not enough file data available to export all.\033[0m\n");
	    system("PAUSE");
	}
    
    // If the user doesn't wish to exit then proceed prompting user of 
    else if (!bIsWantExit)
	{
		printf("In what File Name would you like to export all data: \n");
		fgets(sLine, LINE_SIZE, stdin);
		warnValidSize(sLine, 30, "File Name");
		sscanf(sLine, "%[^\n]", sFileInput);
		
		// adds a .txt if it doesn't have it
		addTxt(sFileInput);

		// Checks if the input is for user database
		// The '4' helps activate exporting all files in a txt
		if (sUserInput[0] == '1' || sUserInput[0] == '4')
		{
			// If empty prompt error
			if(nUserSize == 0)
			{
	    		printf("\n\033[1;38;5;202mERROR! There is not enough file data available to export users.\033[0m\n");
	    		system("PAUSE");
			}
			
			
			else
			{
				// Append each struct data to filename
				for(i=0; i<nUserSize; i++)
					saveUserToFile(sFileInput, stUsers[i]);
				
				// State success to user
				system("CLS");
				printf("\n\033[1;32mSuccessfully saved user data at %s \033[0m\n\n", sFileInput);
				system("PAUSE");
			}
				
			
		}	
		
		

		// Checks if the input is for appointment
		if (sUserInput[0] == '2' || sUserInput[0] == '4')
		{
			// If empty prompt error
			if(nAppSize == 0)
			{
	    		printf("\n\033[1;38;5;202mERROR! There is not enough file data available to export appointments.\033[0m\n");
	    		system("PAUSE");
			}
			else
			{
				// Append each struct data to filename
				for(i=0; i<nAppSize; i++)
					saveAppToFile(sFileInput, stApps[i]);
				system("CLS");
				printf("\n\033[1;32mSuccessfully saved appointment data at %s \033[0m\n\n", sFileInput);
				system("PAUSE");
			}
				
			
		}
			
		
		
		// Checks if the input is for chatbot database
		if (sUserInput[0] == '3' || sUserInput[0] == '4')	
		{
			
			// If empty prompt error
			if(nChatSize == 0)
			{
	    		printf("\n\033[1;38;5;202mERROR! There is not enough file data available to export chat database.\033[0m\n");
	    		system("PAUSE");
			}
			else
			{
				// Append each struct data to filename
				for(i=0; i<nChatSize; i++)
					saveChatToFile(sFileInput, stChats[i]);
				system("CLS");
				printf("\n\033[1;32mSuccessfully saved chat data at %s \033[0m\n\n", sFileInput);
				system("PAUSE");
			}
				

		}
			
		
		
		
	}
		
}


/* 
	gotoImportChats displays and prompts user for one by one checking of each chat data file entry for him/her to import it to a new data	
*/
void 
gotoImportChats()
{

	struct chatTag stChats[MAX_CHAT];
	struct chatTag stCheck[MAX_CHAT];
	
	char cSel;
	char cUserInput;
	
	String30 sUserFileInput;
	
	
	int i;


	int nCheckSize;
	int nChatSize;
	int bIsExists;
	
	// get a check on the size
	getChatData("Chatbot.txt", stChats, &nChatSize);
	
	// Make sure it doesn't reach the limit
	if (nChatSize < MAX_CHAT)
	{
		do
		{
			// First what file name 
			system("CLS");
			printf("\t\t       \033[38;2;245;90;193mCHATBOT IMPORT \033[1;33mMENU\n\n\033[0m");
			printf("\033[1;36m[X]\033[0m - To Exit\n\n");
			printf("What is the source \033[1;36mfilename\033[0m of the data you wish to import in chat bot's data: \033[1;32m");
			scanf("%s", sUserFileInput);
			printf("\033[0m");
			while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
			
			// add .txt to end if needed
			addTxt(sUserFileInput);
			
			// Check file exists
			bIsExists = doesFileExist(sUserFileInput);
			
			// While the user does not iput 'X' exit and the file exists
			if (bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
	
				// State that you found the contents of the file
				printf("\n\033[1;32mFound %s\033[0m, relaying to you the contents of the file\n\n", sUserFileInput);
				system("PAUSE");
				
				// Proceed prompting user only if there is size on the Chat struct array	
				if (nChatSize > 0)
				{
					
					// Reset the struct and get all chat data
					resetStructChats(stChats, &nChatSize);	
					getChatData(sUserFileInput, stChats, &nChatSize);
					
					// Iterate through each data
					for(i = 0; i < nChatSize; i++)
					{
						
						// Display one Chat Data
						system("CLS");
						displayOneChatData(stChats, nChatSize, stChats[i].nNum);
						
						
						// Ask user if he/she wants to delete thiis file
						printf("Do you want to import this data? (Y/N): ");
						scanYesNo(&cUserInput);
						
						// Save to file
						if (cUserInput == 'Y' || cUserInput == 'y')
						{
							saveChatToFile("Chatbot.txt", stChats[i]);
							system("CLS");
							printf("\033[1;32mData Entry is Imported\033[0m\n\n");
							system("PAUSE");
							
						}
						
						// Skip the entry
						else
						{
							system("CLS");
							printf("Data Entry is \033[1;32mSkipped\033[0m\n\n");
							system("PAUSE");
							
						}
						
						// Different struct and number used to not interfere with for loop
						getChatData("Chatbot.txt", stCheck, &nCheckSize);
						
						// Signify the user that chat limit has been reached
						if (nCheckSize >= MAX_CHAT)
						{
							i = nChatSize;
							system("CLS");
							printf("\n\033[1;38;5;202mERROR! maximum amount of chatbot data reached\033[0m\n\n");
							system("PAUSE");
						}
						
			
					}
	
						
					
				}
				
				// When there is no data previously then proceed to import all data
				else
				{
					
					// Get data and save each of themm and append them to the file directly
					getChatData(sUserFileInput, stChats, &nChatSize);
					for(i = 0; i < nChatSize; i++)
						saveChatToFile("Chatbot.txt", stChats[i]);
					
					
					
					system("CLS");
					printf("\n\033[1;32mAll Data Entry is Imported\033[0m\n\n");
					system("PAUSE");
				}
				
				// Sign to the user that it will be returning back to menu
				system("CLS");
				printf("All Data has been relayed returning to menu\n\n");
				system("PAUSE");		
			}
			
			// The file does not exist then state it to user
			else if (!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
				printf("\n\033[1;38;5;202mYour File Input does not exist, no spaces are included in file name input\033[0m\n\n");
				system("PAUSE");
			}
					
		}while(!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X');
		
	}
	
	// Tells user that max amount of data has been reached
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! maximum amount of chatbot data reached\033[0m\n\n");
		system("PAUSE");
	}

}


/* 

	gotoImportApps displays and prompts user for one by one checking of each app data file entry for him/her to import it to a new data
	
*/
void 
gotoImportApps()
{

	struct appTag stApps[MAX_REQS];
	struct appTag stCheck[MAX_REQS];
	
	String30 sUserFileInput;
	
	char cUserInput;
	char cSel;
	
	int i;


	int nCheckSize;
	int nAppSize;
	int bIsExists;
	
	// Check the size
	getAppData("Appointment.txt", stApps, &nAppSize);
	
	// Make sure it is below the limit
	if (nAppSize < MAX_REQS)
	{
		do
		{
			system("CLS");
			printf("\t\t       \033[38;2;245;90;193mAPPOINTMENT IMPORT \033[1;33mMENU\n\n\033[0m");
			printf("\033[1;36m[X]\033[0m - To Exit\n\n");
			printf("What is the filename of the data you will import to appointment's data: \033[1;32m");
			scanf("%s", sUserFileInput);
			while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
			printf("\033[0m");
			
			// Concatenates with .txt if needed
			addTxt(sUserFileInput);
			
			if ( sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
				// Check if file exist
				bIsExists = doesFileExist(sUserFileInput);
			
			
			
			
			
			if (bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
	
	
				printf("\n\033[1;32mFound %s\033[0m, relaying to you the contents of the file\n\n", sUserFileInput);
				system("PAUSE");		
				
				resetStructAppReqs(stApps, &nAppSize);	
				getAppData(sUserFileInput, stApps, &nAppSize);
				
				// Check a seprate struct file, used for validating and checking contents
				getAppData("Appointment.txt", stCheck, &nCheckSize);
				
				// Prompt the user of which entry import  when there is previous loaded entries already
				if (nAppSize > 0)
				{
					
					
					for(i = 0;i < nAppSize; i++)
					{
						system("CLS");
						displayOneAppData(stApps, nAppSize,  stApps[i].nAppID);
						
						printf("Do you want to import this data? (Y/N): ");
						scanYesNo(&cUserInput);
						// If the user id is in conflict relay to the user that program will skip it instead
						if ( !validateAppID(stCheck, stApps[i].nAppID, nCheckSize) && 		// Should return 1 if unique, 0 if there is common
							(cUserInput == 'Y' || cUserInput == 'y'))						// Only occurs when user wants to put it in the data
							
						{
							system("CLS");
							printf("Data Entry is for \033[1;36mID %d\033[0m is \033[1;32mSkipped\033[0m due to being in conflict with other app ID\n\n", stApps[i].nAppID);
							system("PAUSE");
							
						}
						
						// If user wishes to input it in the file while being a valid ID, then it will be imported
						else if (cUserInput == 'Y' || cUserInput == 'y')
						{
							saveAppToFile("Appointment.txt", stApps[i]);
							system("CLS");
							printf("\n\033[1;32mData Entry is Imported\033[0m\n\n");
							system("PAUSE");
							
						}
						else
						{
							system("CLS");
							printf("Data Entry is \033[1;32mSkipped\033[0m\n\n");
							system("PAUSE");
							
						}
						
						// Update the size and contents
						getAppData("Appointment.txt", stCheck, &nCheckSize);
						
						// State to user that limit of appointment has been reached
						if (nCheckSize >= MAX_REQS)
						{
							i = nAppSize;
							system("CLS");
							printf("\n\033[1;38;5;202mERROR! maximum amount of appointment requests reached\033[0m\n\n");
							system("PAUSE");
						}
			
					}
					
						
					//Arrange them in the file properly
					resetStructAppReqs(stApps, &nAppSize);
					getAppData("Appointment.txt", stApps, &nAppSize);
					arrangeAppReqs(stApps, nAppSize);
					overwriteAppReqsFile("Appointment.txt", stApps, nAppSize);
					resetStructAppReqs(stApps, &nAppSize);	
					
				}
				
				// Directly save to main file all data of app data in the file imported
				else
				{
			
					
					for(i = 0; i < nAppSize; i++)
						saveAppToFile("Appointment.txt", stApps[i]);
					
					
					//Arrange them in the file properly
					resetStructAppReqs(stApps, &nAppSize);
					getAppData("Appointment.txt", stApps, &nAppSize);
					arrangeAppReqs(stApps, nAppSize);
					overwriteAppReqsFile("Appointment.txt", stApps, nAppSize);
					resetStructAppReqs(stApps, &nAppSize);	
					
					system("CLS");
					printf("\n\033[1;32mAll Data Entry is Imported\033[0m\n\n");
					system("PAUSE");
				}
				system("CLS");
				printf("All Data has been relayed, returning to menu\n\n");
				system("PAUSE");		
			}
			
			// State to user that there is no file to import from
			else if (!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
				printf("\n\033[1;38;5;202mYour File Input does not exist, no spaces are included in file name input\033[0m\n\n");
				system("PAUSE");
			}
					
		}while(!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X');

		
	}
	
	// State to user that limit of appointment has been reached
	else
	{
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! maximum amount of appointment requests reached\033[0m\n\n");
		system("PAUSE");
		
	}

}


/* 

	gotoImportUsers displays and prompts user for one by one checking of each user data file entry for him/her to import it to a new data
	
*/
void 
gotoImportUsers()
{
	
	struct userTag stCheck[MAX_USERS];
	struct userTag stUsers[MAX_USERS];

	
	String30 sUserFileInput;
	char cUserInput;
	char cSel;
	
	int i;
	int nCheckSize;
	int nUserSize;
	int bIsExists;
	
	
	// Get all user data in order to gauge the size
	getUserData("Users.txt", stUsers, &nUserSize);
	
	// Make sure max user data is not reached
	if (nUserSize < MAX_USERS)
	{
		do
		{
			
			system("CLS");
			printf("\t\t       \033[38;2;245;90;193mUSER IMPORT \033[1;33mMENU\n\n\033[0m");
			printf("\033[1;36m[X]\033[0m - To Exit\n\n");
			printf("What is the filename of the data you will import to user's data: \033[1;32m");
			
			// Scan what filename to import data from
			scanf("%s", sUserFileInput);
			
			printf("\033[0m");
			
			while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
			
			// add .txt to end if needed
			addTxt(sUserFileInput);
			
			// Check if the file name exists
			bIsExists = doesFileExist(sUserFileInput);
			
			if (bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
				printf("\n\033[1;32mFound %s\033[0m, relaying to you the contents of the file\n\n", sUserFileInput);
				system("PAUSE");
				
				// Only prompt when there is size on User
				if (nUserSize > 0)
				{
					resetStructUsers(stUsers, &nUserSize);	
					getUserData(sUserFileInput, stUsers, &nUserSize);
					
					// used for validating contents and checking
					getUserData("Users.txt", stCheck, &nCheckSize);
					
					// Prompt each data in the User Size
					for(i = 0; i < nUserSize; i++)
					{
						system("CLS");
						displayOneUserData(stUsers, nUserSize,  stUsers[i].nUID);
						
						// Gets all current user data
						
						
						// Prompt if admin wants it to be added
						printf("Do you want to import this data? (Y/N): ");
						scanYesNo(&cUserInput);
						
						// If the user id is in conflict relay to the user that you will skip it instead
						if ( !validateUserID(stCheck, stUsers[i].nUID) && 		// Should return 1 if unique, 0 if there is common
							(cUserInput == 'Y' || cUserInput == 'y'))			// Only occurs when user wants to put it in the data
						{
							system("CLS");
							printf("Data Entry is for  \033[1;36mID %d\033[0m is \033[1;32mSkipped\033[0m due to being in conflict with other user ID\n\n", stUsers[i].nUID);
							system("PAUSE");
							
						}
						
						// Proceed to add it if user said yes
						else if (cUserInput == 'Y' || cUserInput == 'y')
						{
							saveUserToFile("Users.txt", stUsers[i]);
							system("CLS");
							printf("\033[1;32mData Entry is Imported\033[0m\n\n");
							system("PAUSE");
							
						}
						else
						{
							system("CLS");
							printf("Data Entry is \033[1;32mSkipped\033[0m\n\n");
							system("PAUSE");
							
						}
						
						// update and check the size
						getUserData("Users.txt", stCheck, &nCheckSize);
						if (nCheckSize >= MAX_USERS)
						{
							i = nUserSize;
							system("CLS");
							printf("\n\033[1;38;5;202mERROR! maximum amount of user data reached\033[0m\n\n");
							system("PAUSE");
							
						}
			
					}
					
						
					//Arrange them in the file properly
					resetStructUsers(stUsers, &nUserSize);
					getUserData("Users.txt", stUsers, &nUserSize);
					arrangeUsers(stUsers, nUserSize);
					overwriteUsersFile("Users.txt", stUsers, nUserSize);
					resetStructUsers(stUsers, &nUserSize);	
					
				}
				
				// Append it to user data directly without asking for each data if user wishes to enter them
				else
				{
			
					getUserData(sUserFileInput, stUsers, &nUserSize);
					for(i=0; i<nUserSize; i++)
						saveUserToFile("Users.txt", stUsers[i]);
					
					
					//Arrange them in the file properly
					resetStructUsers(stUsers, &nUserSize);
					getUserData("Users.txt", stUsers, &nUserSize);
					
					// arrange the User ID in ascending order
					arrangeUsers(stUsers, nUserSize);
					overwriteUsersFile("Users.txt", stUsers, nUserSize);
					resetStructUsers(stUsers, &nUserSize);	
					
					system("CLS");
					printf("\n\033[1;32mAll Data Entry is Imported\033[0m\n\n");
					system("PAUSE");
				}
				system("CLS");
				printf("All Data has been relayed, returning to menu\n\n");
				system("PAUSE");		
			}
			
			// If file does not exist then state to user
			else if (!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X')
			{
				system("CLS");
				printf("\033[1;38;5;202mYour File Input does not exist, no spaces are included in file name input\033[0m\n\n");
				system("PAUSE");
			}
					
		}while(!bIsExists && sUserFileInput[0] != 'x' && sUserFileInput[0] != 'X');
	}
	
	// State to user that max data has been reached
	else
	{
	
		system("CLS");
		printf("\n\033[1;38;5;202mERROR! maximum amount of user data reached\033[0m\n\n");
		system("PAUSE");
							
	}



	
	
	
}


/* 

	validateImportMenu_Input checks for user's input which data he/she wishes import data to
	
	@param pIsValidInput - pointer to help signify that the input is wrong via 1 or 0
	
	@return 1 if the user inputted an exit the import menu choice, else 0 which keeps the menu loop going
*/
int
validateImportMenu_Input(String20 sInput, int *pIsValidInput)
{
	int nStrLen;
	
	int nFlag =0;
	
	// String length and lower the case string
	nStrLen = strlen(sInput);
	lowerStringCase(sInput);

	
	// Check semantics and put them to the function screen
	if( (nStrLen == 1 && !strcmp(sInput, "u")) || 
		!strcmp(sInput, "users") ||
		!strcmp(sInput, "user") )
		
		// Goto function screen where it relate to import to that particular user
		gotoImportUsers();
		
	
	else if( (nStrLen == 1 && !strcmp(sInput, "a")) || 
			  !strcmp(sInput, "requests") ||
			  !strcmp(sInput, "apps") ||
			  !strcmp(sInput, "app") )
	
		gotoImportApps();

		
	
	else if( (nStrLen == 1 && !strcmp(sInput, "c")) || 
			  !strcmp(sInput, "chatbot") ||
			  !strcmp(sInput, "chat") )
	

		gotoImportChats();
	
	
	else if( (nStrLen == 1 && !strcmp(sInput, "q")) || 
			  !strcmp(sInput, "x") ||
			  !strcmp(sInput, "exit") ||
			  !strcmp(sInput, "quit"))
	
		// This causes the loop to exit and quit the program to the menu screen
		nFlag = 1;

	

		
	// Repeat the while loop as the input was invalid
	else
	
		// Relay to boolean that it was not valid
		*pIsValidInput = 0;				

	
	return nFlag;
}


/* 

	displayImport asks and prompt for user which data he/she will import data to
	
*/
void 
displayImport()
{

	String20 sUserInput;
	int bIsValidInput;
	int bIsDone;
	char cSel;
	
	bIsDone = 0;
	while(!bIsDone)
	{

		system("CLS");
		printf("\t\t       \033[38;2;245;90;193m  IMPORT \033[1;33mMENU\n\n\033[0m");
		

		
		printf("      Which of the following will categories you import data\n\n");
		printf("\t\t  Users Data \t\t\033[1;36m[U]\033[0m \n");
		printf("\t\t  Appointment Data \t\033[1;36m[A]\033[0m\n");
		printf("\t\t  Chatbot Data \t\t\033[1;36m[C]\033[0m\n");
		printf("\t\t  Exit \t\t\t\033[1;36m[Q]\033[0m\n\n");
		
		
		// If the input was invalid, state it to user
		if (!bIsValidInput)
			printf("\n\033[1;38;5;202mERROR! Please only input from the above choices.\033[0m\n");
			
		printf("Input: ");
		scanf("%s", sUserInput);
		while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
		
		// The input by default is assumed valid
		bIsValidInput = 1;
		
		// Check if it was a valid input or not
		bIsDone = validateImportMenu_Input(sUserInput, &bIsValidInput);


	}

}





/* 

	validateDataManMenu_Input validates when the user was asked and prompted for user which function data management to be used
	
	@param sInput - user's input on which function category in data management menu to access
	@param nStrLen - The string length
	@param pIsInputGood - address of boolean that controls the while loop at main menu to control main menu termination
	
	@return 1 if the input from the user was a valid input, else 0
*/
int 
validateDataManMenu_Input(String30 sInput,
						  int nStrLen,
						  int *pIsInputGood)
{

	// Default
	int nFlag =0;
	
	// Lowers string case
	lowerStringCase(sInput);
	
	// Checks if wants the user related data managing
	if( (nStrLen == 1 && !strcmp(sInput, "u")) || 
		!strcmp(sInput, "users") )
	{
		// Makes the loop in the data management menu not exit automatically
		*pIsInputGood = 0;
		
		// proceed to wished menu screen
		displayAdm_DataUserMenu();
		
		// The user did input a valid choice
		nFlag = 1;
		
	}
	
	// Checks if wants the appointment related data managing
	else if( (nStrLen == 1 && !strcmp(sInput, "a")) || 
			  !strcmp(sInput, "requests") ||
			  !strcmp(sInput, "appointment") || 
			  !strcmp(sInput, "app") || 
			  !strcmp(sInput, "app reqs") || 
			  !strcmp(sInput, "apps") || 
			  !strcmp(sInput, "appointments"))
	{
		
		displayAdm_ManageAppsMenu();
		*pIsInputGood = 0;
		nFlag = 1;
		
	}
	
	// Checks if wants the chatbot related data managing
	else if( (nStrLen == 1 && !strcmp(sInput, "c")) || 
			  !strcmp(sInput, "chatbot") || 
			  !strcmp(sInput, "ch") ||
			  !strcmp(sInput, "bot"))
	{
		*pIsInputGood = 0;
		displayAdm_ChatBotMenu();
		nFlag = 1;
		
	}
	else if( (nStrLen == 1 && !strcmp(sInput, "e")) || 
			  !strcmp(sInput, "export") )
	{
		*pIsInputGood = 0;
		displayExport();
		nFlag = 1;
		
	}	
	else if( (nStrLen == 1 && !strcmp(sInput, "i")) || 
			  !strcmp(sInput, "import") )
	{
		*pIsInputGood = 0;
		displayImport();
		nFlag = 1;
		
	}				
	else if( (nStrLen == 1 && (sInput[0]== 'x' || 
			  !strcmp(sInput, "exit") || 
			  sInput[0] == 'q') ) )
	{
		nFlag = 1;
		
		// The only way to exit the menu for admin's data management
		*pIsInputGood = 1;
	}
	
	// State the user inputted wrong
	else
	{
		printf("\n\033[1;38;5;202mERROR Input: Please only use the choices.\033[0m\n");
		system("PAUSE");
	}
	
	
	return nFlag;
		
			
}




/* 

	displayDataManMenu asks and prompt for user which data management category function will he go to
	
	@param pIsInputGood - address of boolean that controls the while loop at main menu to control main menu termination

*/
void
displayDataManMenu(int *pIsGoodInput)
{
	

	int isLocalInputGood = 0;
	char cSel;
	String30 sInput;
	
	// isLocalInputGood control loop of the data management menu
	// *pIsGoodInput Control loop of the main menu
	
	while(!isLocalInputGood)
	{

		system("CLS");

		printf("\t\t\033[1;33m  DATA MANAGEMENT MENU\n\033[0m");

	
		printf("\t  User   \t\t\t\033[1;36m[U]\033[0m\n");
		printf("\t  Appointment Reqeust   \t\033[1;36m[A]\033[0m\n");
		printf("\t  ChatBot Data   \t\t\033[1;36m[C]\033[0m\n");
		printf("\t  Import   \t\t\t\033[1;36m[I]\033[0m\n");
		printf("\t  Export   \t\t\t\033[1;36m[E]\033[0m\n");
		printf("\t  Exit/Quit   \t\t\t\033[1;36m[Q]\033[0m\n\n");
	
		printf("Input: ");
		
		scanf("%s", sInput);
		while ((cSel = getchar()) != '\n' && cSel != EOF);		//Clears input buffer
		
		
		// Checks if inputs are valid
		validateDataManMenu_Input(sInput, strlen(sInput), &isLocalInputGood);
		
		// When inputGood gets 1 it means user wants to quit and go back to main menu
		// Turning *pIsGoodInput to 0 makes the main menu turn back on the while loop
		if(isLocalInputGood)
		
			*pIsGoodInput = 0;



	}
	
	
}


/* 

	displayAdminLogin asks and prompt for user to login admin details
	
	@param pIsInputGood - address of boolean that controls the while loop at main menu to control main menu termination
	@param nAdm_Id - the admin ID
	@param sPass - password string entered by the user
*/
void
displayAdminLogin(int *pIsGoodInput, 
				  int nAdm_Id, 
				  String10 sPass)
{
	

	char cUserInput;
	
	int nAttempts = MAX_ATTEMPTS;
	int nTypedId;
	int bIsAccepted = 0;
	
	String10 sTypedPass;

	
	
	cUserInput = 'y';
	system("CLS");
	//While user has attempts or the inputs are not yet accepted, keep prompting
	while (nAttempts > 0 && !bIsAccepted && cUserInput != 'n')	
	{
		
		
		printf("\t\t\033[1;33m  DATA MANAGEMENT LOGIN\n\033[0m\n\n");
		printf("Admin ID: ");
		scanID(&nTypedId);
		
	

		
		//Password typing logic
		typePassword(sTypedPass);
		printf("\n");
		

		//Checks if the admin enter the wrong information
	    if (strcmp(sTypedPass, sPass) != 0  ||		//Checks if password is not correct
			nTypedId != nAdm_Id			)			//Checks if ID entered is not accurate

	    {
	    	nAttempts -= 1;
	    	
	    	// If user reaches no attempts left then state that his/her session will be terminated
	    	if (nAttempts == 0)
	    	{	
	    		system("CLS");
	    		printf("\n\033[1;38;5;202mALERT! Now terminating program due to all 3 attempts being used\033[0m\n\n");
	    		system("PAUSE");
			}
			else
			{
				printf("\n\033[1;38;5;202mLOGIN ERROR!\033[0m Wrong user password or id, please try again (\033[1;38;5;202m%d try/s\033[0m left)\n\n", nAttempts);
				
				// Ask if user wants to keep prompting
				printf("Try again? (Y/N): ");
				scanYesNo(&cUserInput);
				
				
				// Activate main menu while loop
				if(cUserInput == 'n')
					*pIsGoodInput = 0;
				
			}
				
	    		

	    	printf("\n");
	    	
		}
		
		//If all the possibilities he entered are not wrong then he is right
		//Hence, he proceeds to admin data mangaement screen
		else
		{
			
			printf("\n\033[0;32mInputs are all correct, Welcome Admin!\033[0m\n\n");	
			system("PAUSE");
			bIsAccepted = 1;

			displayDataManMenu(pIsGoodInput);
		}
			
		system("CLS");

		
	}

   



	
}


/* 
	main asks and prompt for which menu to go
*/
int main()
{
	
		

	char cUserMenuInput;
	char cSel;
	
	int nCnt;
	int bIsScanValid;
	int bIsGoodInput = 0;
	
	int nAdmin_UserId = ADMIN_ID;
	String10 sAdmin_Pass = ADMIN_PASS; 
	
	
	// Assumes the user inputs a valid input
	bIsScanValid = 1;
	while(!bIsGoodInput)
	
	{
		system("CLS");
		displayStartMenu();
		printf("\n");
		printf("\n");
		printf("\t\t\t\t\033[0;36m[R]\033[0m - User's Registration Menu \n" );
		printf("\t\t\t\t\033[0;36m[D]\033[0m - Admin's Data Management)\n");
		printf("\n\n\n");
		printf("Exit by typing \033[0;36m[X]\033[0m in the input field.\n\n");
		
		// States that the user inputted wrong
		if (!bIsScanValid)
			printf("\n\033[1;38;5;202mPlease only input 'R'/'D'/'X' to proceed with app functions.\033[0m\n\n");
		
		// Asks for user's input
		printf("Input: ");
		scanf(" %c", &cUserMenuInput);
		
		// Sets counter for how many characters extra user inputted
		nCnt = 0;
		
		//Counts Characters and gets extra characters that the user might input
		while ((cSel = getchar()) != '\n' && cSel != EOF);
			nCnt++;
		
		// More than one character is false
		if (nCnt > 1)
		
			// Makes sure when checking the user input it is false
			cUserMenuInput = '0';
		
		// Checks user input if ready to go for vaccination registration menu
		if (cUserMenuInput == 'R' || cUserMenuInput == 'r' )
		{
		
			system("CLS");
			bIsGoodInput = 1;
			displayVacRegMenu(&bIsGoodInput);
			bIsScanValid = 1;
		}
		
		// Checks if the user input is read to go for data management menu
		else if(cUserMenuInput == 'D' || cUserMenuInput == 'd' )
		{
			system("CLS");
			bIsGoodInput = 1;
			displayAdminLogin(&bIsGoodInput, nAdmin_UserId, sAdmin_Pass);
			bIsScanValid = 1;
		
			
		}
		
		// Checks if the user wants to exit this while loop
		else if(cUserMenuInput == 'X' || cUserMenuInput == 'x' ||
				cUserMenuInput == 'Q' || cUserMenuInput == 'q')
		{
			system("CLS");
			printf("\n\n");
			bIsGoodInput = 1;		//This will help exit the loop when 0
			bIsScanValid = 1;		// This helps relay that the user's input was valid
			
		}
		else
			bIsScanValid = 0;

		
		
	}
	
	// Displays goodbye
	printf("\a");
	displayGoodbye();

	return 0;
	
	
}