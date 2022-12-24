
/*********************************************************
 * Welcome to Minesweeper
 * Author: Yuxi Qian
 * Date: 11-13-2022
 * Version: 2.1
 *********************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <term.h>

#include "minesweeper.h"

using namespace std;

string titleLine1 = "  ███╗   ███╗    ██╗    ███╗   ██╗    ███████╗    ███████╗    ██╗    ██╗    ███████╗    ███████╗    ██████╗     ███████╗    ██████╗ ";
string titleLine2 = "  ████╗ ████║    ██║    ████╗  ██║    ██╔════╝    ██╔════╝    ██║    ██║    ██╔════╝    ██╔════╝    ██╔══██╗    ██╔════╝    ██╔══██╗";
string titleLine3 = "  ██╔████╔██║    ██║    ██╔██╗ ██║    █████╗      ███████╗    ██║ █╗ ██║    █████╗      █████╗      ██████╔╝    █████╗      ██████╔╝";
string titleLine4 = "  ██║╚██╔╝██║    ██║    ██║╚██╗██║    ██╔══╝      ╚════██║    ██║███╗██║    ██╔══╝      ██╔══╝      ██╔═══╝     ██╔══╝      ██╔══██╗";
string titleLine5 = "  ██║ ╚═╝ ██║    ██║    ██║ ╚████║    ███████╗    ███████║    ╚███╔███╔╝    ███████╗    ███████╗    ██║         ███████╗    ██║  ██║";
string titleLine6 = "  ╚═╝     ╚═╝    ╚═╝    ╚═╝  ╚═══╝    ╚══════╝    ╚══════╝     ╚══╝╚══╝     ╚══════╝    ╚══════╝    ╚═╝         ╚══════╝    ╚═╝  ╚═╝";

string game_quit_msg_line1 = "   ██████╗   █████╗  ███╗   ███╗ ███████╗     ██████╗  ██╗   ██╗ ██╗ ████████╗ ";
string game_quit_msg_line2 = "  ██╔════╝  ██╔══██╗ ████╗ ████║ ██╔════╝    ██╔═══██╗ ██║   ██║ ██║ ╚══██╔══╝ ";
string game_quit_msg_line3 = "  ██║  ███╗ ███████║ ██╔████╔██║ █████╗      ██║   ██║ ██║   ██║ ██║    ██║    ";
string game_quit_msg_line4 = "  ██║   ██║ ██╔══██║ ██║╚██╔╝██║ ██╔══╝      ██║▄▄ ██║ ██║   ██║ ██║    ██║    ";
string game_quit_msg_line5 = "  ╚██████╔╝ ██║  ██║ ██║ ╚═╝ ██║ ███████╗    ╚██████╔╝ ╚██████╔╝ ██║    ██║    ";
string game_quit_msg_line6 = "   ╚═════╝  ╚═╝  ╚═╝ ╚═╝     ╚═╝ ╚══════╝     ╚══▀▀═╝   ╚═════╝  ╚═╝    ╚═╝    ";

string game_win_msg_line1 = "  ██╗   ██╗  ██████╗  ██╗   ██╗    ██╗    ██╗  ██████╗  ███╗   ██╗ ";
string game_win_msg_line2 = "  ╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║    ██║    ██║ ██╔═══██╗ ████╗  ██║ ";
string game_win_msg_line3 = "   ╚████╔╝  ██║   ██║ ██║   ██║    ██║ █╗ ██║ ██║   ██║ ██╔██╗ ██║ ";
string game_win_msg_line4 = "    ╚██╔╝   ██║   ██║ ██║   ██║    ██║███╗██║ ██║   ██║ ██║╚██╗██║ ";
string game_win_msg_line5 = "     ██║    ╚██████╔╝ ╚██████╔╝    ╚███╔███╔╝ ╚██████╔╝ ██║ ╚████║ ";
string game_win_msg_line6 = "     ╚═╝     ╚═════╝   ╚═════╝      ╚══╝╚══╝   ╚═════╝  ╚═╝  ╚═══╝ ";

string game_lose_msg_line1 = "  ██╗   ██╗  ██████╗  ██╗   ██╗    ██╗       ██████╗  ███████╗ ████████╗ ";
string game_lose_msg_line2 = "  ╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║    ██║      ██╔═══██╗ ██╔════╝ ╚══██╔══╝ ";
string game_lose_msg_line3 = "   ╚████╔╝  ██║   ██║ ██║   ██║    ██║      ██║   ██║ ███████╗    ██║    ";
string game_lose_msg_line4 = "    ╚██╔╝   ██║   ██║ ██║   ██║    ██║      ██║   ██║ ╚════██║    ██║    ";
string game_lose_msg_line5 = "     ██║    ╚██████╔╝ ╚██████╔╝    ███████╗ ╚██████╔╝ ███████║    ██║    ";
string game_lose_msg_line6 = "     ╚═╝     ╚═════╝   ╚═════╝     ╚══════╝  ╚═════╝  ╚══════╝    ╚═╝    ";

string row_input_msg = "Row index = ";
string col_input_msg = "Column index = ";

ostream& operator <<(ostream &os, const vector<string> &msg){
    for(int i = 0; i < (int)msg.size(); i++){
        os << msg[i] << "\n";
    }
    os << "\n";
    return os;
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int main(){
    vector<string> gameTitle;
    gameTitle.push_back(titleLine1);
    gameTitle.push_back(titleLine2);
    gameTitle.push_back(titleLine3);
    gameTitle.push_back(titleLine4);
    gameTitle.push_back(titleLine5);
    gameTitle.push_back(titleLine6);

    vector<string> game_quit_msg;
    game_quit_msg.push_back(game_quit_msg_line1);
    game_quit_msg.push_back(game_quit_msg_line2);
    game_quit_msg.push_back(game_quit_msg_line3);
    game_quit_msg.push_back(game_quit_msg_line4);
    game_quit_msg.push_back(game_quit_msg_line5);
    game_quit_msg.push_back(game_quit_msg_line6);

    vector<string> game_win_msg;
    game_win_msg.push_back(game_win_msg_line1);
    game_win_msg.push_back(game_win_msg_line2);
    game_win_msg.push_back(game_win_msg_line3);
    game_win_msg.push_back(game_win_msg_line4);
    game_win_msg.push_back(game_win_msg_line5);
    game_win_msg.push_back(game_win_msg_line6);

    vector<string> game_lose_msg;
    game_lose_msg.push_back(game_lose_msg_line1);
    game_lose_msg.push_back(game_lose_msg_line2);
    game_lose_msg.push_back(game_lose_msg_line3);
    game_lose_msg.push_back(game_lose_msg_line4);
    game_lose_msg.push_back(game_lose_msg_line5);
    game_lose_msg.push_back(game_lose_msg_line6);
    system("clear");

    int mode = 0;
    char modeInputBuffer = '\0';
    while(mode != 4){
        do{
            cout << "\n";
            cout << "\n";
            cout << gameTitle;
            cout << setw(130) << "Version: 2.1"<< "\n";
            cout << "\n";

            cout << "  Please Choose Your Game Mode:" << "\n" << "\n";

            if(mode == 0){
                cout << "> Esay, 9x9, 20 Bombs" << "\n";
            }
            else if(mode != 0){
                cout << "  Esay, 9x9, 20 Bombs" << "\n";
            }

            if(mode == 1){
                cout << "> Medium, 16x16, 50 Bombs" << "\n";
            }
            else if(mode != 1){
                cout << "  Medium, 16x16, 50 Bombs" << "\n";
            }
            
            if(mode == 2){
                cout << "> Hard, 25x25, 100 Bombs" << "\n";
            }
            else if(mode != 2){
                cout << "  Hard, 25x25, 100 Bombs" << "\n";
            }
            
            if(mode == 3){
                cout << "> Challenge, 30x40, 200 Bombs" << "\n";
            }
            else if(mode != 3){
                cout << "  Challenge, 30x40, 200 Bombs" << "\n";
            }

            if(mode == 4){
                cout << "> Quit" << "\n";
            }
            else if(mode != 4){
                cout << "  Quit" << "\n" ;
            }
            modeInputBuffer = getch();
            
            while(!(modeInputBuffer == 'w' || modeInputBuffer == 'W' || modeInputBuffer == 's' || modeInputBuffer == 'S' || modeInputBuffer == '\n')){
                modeInputBuffer = getch();
            }

            while((mode == 0 && (modeInputBuffer == 'w' || modeInputBuffer == 'W')) || (mode == 4 && (modeInputBuffer == 's' || modeInputBuffer == 'S'))){
                modeInputBuffer = getch();
            }
            if(modeInputBuffer == 'w' || modeInputBuffer == 'W'){
                mode--;
            }
            if(modeInputBuffer == 's' || modeInputBuffer == 'S'){
                mode++;
            }
            system("clear");
        }while(modeInputBuffer != '\n');
        
        if(mode == 4){
            cout << "\n";
            cout << game_quit_msg << "\n";
            break;
        }


        Minesweeper game(mode);
        system("clear");
        switch (game.returnDiffculty()){
        case 0:
            cout << "Game start: " << "Easy Mode, "<< game.returnRowSize() << "x" << game.returnColSize() << ", " << game.returnBombNum() << " Bombs" << "\n";
            break;

        case 1:
            cout << "Game start: " << "Medium Mode, "<< game.returnRowSize() << "x" << game.returnColSize() << ", " << game.returnBombNum() << " Bombs" << "\n";
            break;

        case 2:
            cout << "Game start: " << "Hard Mode, "<< game.returnRowSize() << "x" << game.returnColSize() << ", " << game.returnBombNum() << " Bombs" << "\n";
            break;
        case 3:
            cout << "Game start: " << "Challenge Mode, "<< game.returnRowSize() << "x" << game.returnColSize() << ", " << game.returnBombNum() << " Bombs" << "\n";
            break;
        }

        game.printGame();
        string operation;

        bool firstDig = true;
        int rowInputInt;
        int colInputInt;
        while(game.returnGameStatus() == 0){
            cout << "Please enter 'd'/'dig' to dig, 'f'/'flag' to flag/unflag, 'n'/'new' to start a new game" << "\n";
            cout << "Operation = ";
            getline(cin,operation);
            cout << "\n";

            while(!(operation == "dig" || operation == "d" || operation == "flag" || operation == "f" || operation == "new" || operation == "n")){
                cout << "Invalid input, please enter 'd'/'dig' or 'f'/'flag' to choose the type of your operation, enter 'n'/'new' to start a new game" << "\n";
                cout << "Operation = ";
                getline(cin,operation);
                cout << "\n";
            }

            if(operation == "n" || operation == "new"){
                system("clear");
                break;
            }

            if(operation == "d" || operation == "dig"){
                cout << "(Dig Mode) Please enter the row and column index of the dig operation, enter '0' to re-choice operation" << "\n";
                cout << row_input_msg;
                cin >> rowInputInt;

                while (cin.fail() || rowInputInt > game.returnRowSize() || rowInputInt < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input, ";
                    cout << row_input_msg;
                    cin >> rowInputInt;
                }

                if(rowInputInt == 0){
                    cout << "\n";
                    cin.ignore(1000, '\n');
                    continue;
                }

                cout << col_input_msg;
                cin >> colInputInt;
                
                while (cin.fail() || colInputInt >  game.returnColSize() || rowInputInt < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input, ";
                    cout << col_input_msg;
                    cin >> colInputInt;
                }

                if(colInputInt == 0){
                    cout << "\n";
                    cin.ignore(1000, '\n');
                    continue;
                }

                rowInputInt--;
                colInputInt--;

                if(firstDig){
                    if(game.insertBomb(Location(rowInputInt,colInputInt))){
                        system("clear");
                        game.printGame();
                        firstDig = false;
                    }
                }
                else{
                    if(game.applyDig(Location(rowInputInt,colInputInt))){
                        system("clear");
                        game.printGame();
                    }
                }
                game.checkGameStatus();
                cin.ignore(1000, '\n');
            }

            if(operation == "f" || operation == "flag"){
                cout << "(Flag Mode) Please enter the row and column index of the flag operation, enter '0' to re-choice operation" << "\n";
                cout << row_input_msg;
                cin >> rowInputInt;

                while (cin.fail() || rowInputInt >  game.returnRowSize() || rowInputInt < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input, ";
                    cout << row_input_msg;
                    cin >> rowInputInt;
                }

                if(rowInputInt == 0){
                    cout << "\n";
                    cin.ignore(1000, '\n');
                    continue;
                }

                cout << col_input_msg;
                cin >> colInputInt;
                
                while (cin.fail() || colInputInt >  game.returnColSize() || rowInputInt < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input, ";
                    cout << col_input_msg;
                    cin >> colInputInt;
                }

                if(colInputInt == 0){
                    cout << "\n";
                    cin.ignore(1000, '\n');
                    continue;
                }

                rowInputInt--;
                colInputInt--;
                
                if(game.applyFlag(Location(rowInputInt,colInputInt))){
                    system("clear");
                    game.printGame();
                }
                cin.ignore(1000, '\n');
                game.checkGameStatus();
            }

            if(game.returnGameStatus() == 1){
                cout << "\n";
                cout << game_win_msg;
                cout << "\n";
                game.printAll();
                string userInput;
                cout << "\n";
                cout << "Start a new game? (please enter 'y'/'n')"<< "\n";
                cout << "User input = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "Invalid input, please enter 'y'/'n'" << "\n";
                    cout << "User input = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    system("clear");
                    break;
                }

                else if(userInput == "n"){
                    cout << "\n";
                    cout << game_quit_msg;
                    cout << "\n";
                    return 0;
                }
            }

            if(game.returnGameStatus() == -1){
                cout << "\n";
                cout << game_lose_msg;
                cout << "\n";
                game.printAll();
                string userInput;
                cout << "\n";
                cout << "Start a new game? (please enter 'y'/'n')"<< "\n";
                cout << "User input = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "Invalid input, please enter 'y'/'n'" << "\n";
                    cout << "User input = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    system("clear");
                    break;
                }

                else if(userInput == "n"){
                    cout << "\n";
                    cout << game_quit_msg;
                    cout << "\n";
                    return 0;
                }
            }
        }
    }
    return 0;
}