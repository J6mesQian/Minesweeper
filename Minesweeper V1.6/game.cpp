
/*********************************************************
 * Welcome to Minesweeper
 * Author: Yuxi Qian
 * Date: 11-13-2022
 * Version: 1.6
 *********************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>

#include "minesweeper.h"

using namespace std;

string titleLine1 = "███╗   ███╗    ██╗    ███╗   ██╗    ███████╗    ███████╗    ██╗    ██╗    ███████╗    ███████╗    ██████╗     ███████╗    ██████╗ ";
string titleLine2 = "████╗ ████║    ██║    ████╗  ██║    ██╔════╝    ██╔════╝    ██║    ██║    ██╔════╝    ██╔════╝    ██╔══██╗    ██╔════╝    ██╔══██╗";
string titleLine3 = "██╔████╔██║    ██║    ██╔██╗ ██║    █████╗      ███████╗    ██║ █╗ ██║    █████╗      █████╗      ██████╔╝    █████╗      ██████╔╝";
string titleLine4 = "██║╚██╔╝██║    ██║    ██║╚██╗██║    ██╔══╝      ╚════██║    ██║███╗██║    ██╔══╝      ██╔══╝      ██╔═══╝     ██╔══╝      ██╔══██╗";
string titleLine5 = "██║ ╚═╝ ██║    ██║    ██║ ╚████║    ███████╗    ███████║    ╚███╔███╔╝    ███████╗    ███████╗    ██║         ███████╗    ██║  ██║";
string titleLine6 = "╚═╝     ╚═╝    ╚═╝    ╚═╝  ╚═══╝    ╚══════╝    ╚══════╝     ╚══╝╚══╝     ╚══════╝    ╚══════╝    ╚═╝         ╚══════╝    ╚═╝  ╚═╝";

string game_quit_msg_line1 = " ██████╗   █████╗  ███╗   ███╗ ███████╗     ██████╗  ██╗   ██╗ ██╗ ████████╗ ";
string game_quit_msg_line2 = "██╔════╝  ██╔══██╗ ████╗ ████║ ██╔════╝    ██╔═══██╗ ██║   ██║ ██║ ╚══██╔══╝ ";
string game_quit_msg_line3 = "██║  ███╗ ███████║ ██╔████╔██║ █████╗      ██║   ██║ ██║   ██║ ██║    ██║    ";
string game_quit_msg_line4 = "██║   ██║ ██╔══██║ ██║╚██╔╝██║ ██╔══╝      ██║▄▄ ██║ ██║   ██║ ██║    ██║    ";
string game_quit_msg_line5 = "╚██████╔╝ ██║  ██║ ██║ ╚═╝ ██║ ███████╗    ╚██████╔╝ ╚██████╔╝ ██║    ██║    ";
string game_quit_msg_line6 = " ╚═════╝  ╚═╝  ╚═╝ ╚═╝     ╚═╝ ╚══════╝     ╚══▀▀═╝   ╚═════╝  ╚═╝    ╚═╝    ";

string game_win_msg_line1 = "██╗   ██╗  ██████╗  ██╗   ██╗    ██╗    ██╗  ██████╗  ███╗   ██╗ ";
string game_win_msg_line2 = "╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║    ██║    ██║ ██╔═══██╗ ████╗  ██║ ";
string game_win_msg_line3 = " ╚████╔╝  ██║   ██║ ██║   ██║    ██║ █╗ ██║ ██║   ██║ ██╔██╗ ██║ ";
string game_win_msg_line4 = "  ╚██╔╝   ██║   ██║ ██║   ██║    ██║███╗██║ ██║   ██║ ██║╚██╗██║ ";
string game_win_msg_line5 = "   ██║    ╚██████╔╝ ╚██████╔╝    ╚███╔███╔╝ ╚██████╔╝ ██║ ╚████║ ";
string game_win_msg_line6 = "   ╚═╝     ╚═════╝   ╚═════╝      ╚══╝╚══╝   ╚═════╝  ╚═╝  ╚═══╝ ";

string game_lose_msg_line1 = "██╗   ██╗  ██████╗  ██╗   ██╗    ██╗       ██████╗  ███████╗ ████████╗ ";
string game_lose_msg_line2 = "╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║    ██║      ██╔═══██╗ ██╔════╝ ╚══██╔══╝ ";
string game_lose_msg_line3 = " ╚████╔╝  ██║   ██║ ██║   ██║    ██║      ██║   ██║ ███████╗    ██║    ";
string game_lose_msg_line4 = "  ╚██╔╝   ██║   ██║ ██║   ██║    ██║      ██║   ██║ ╚════██║    ██║    ";
string game_lose_msg_line5 = "   ██║    ╚██████╔╝ ╚██████╔╝    ███████╗ ╚██████╔╝ ███████║    ██║    ";
string game_lose_msg_line6 = "   ╚═╝     ╚═════╝   ╚═════╝     ╚══════╝  ╚═════╝  ╚══════╝    ╚═╝    ";

string row_input_msg = "Row index = ";
string col_input_msg = "Column index = ";

ostream& operator <<(ostream &os, const vector<string> &msg){
    for(int i = 0; i < (int)msg.size(); i++){
        os << msg[i] << "\n";
    }
    os << endl;
    return os;
}

void clearScreen(){
    for(int i = 0; i < 100; i++){
        cout << '\n';
    }
    cout << endl;
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
    clearScreen();

    string mode = "";
    while(mode != "q"){
        cout << "\n";
        cout << "\n";
        cout << gameTitle;
        cout << setw(130) << "Version: 1.6"<< "\n";
        cout << "\n";

        cout << "Mode 0: Esay, 9x9, 20 Bombs" << "\n";
        cout << "Mode 1: Medium, 16x16, 50 Bombs" << "\n";
        cout << "Mode 2: Hard, 25x25, 100 Bombs" << "\n";
        cout << "Mode 3: Challenge, 30x40, 200 Bombs" << "\n";
        cout << "Enter 'q'/'quit' to quit" << "\n";
        cout << "\n";

        cout <<"Please choose your game diffculty, Mode = ";
        getline(cin,mode);
        cout << "\n";
        while(!(mode == "0" || mode == "1" || mode == "2" || mode == "3" || mode == "q" || mode == "quit")){
            cout << "Invalid input, please enter '0'/'1'/'2'/'3' to choose your game diffculty, enter 'q'/'quit' to quit" << endl;
            cout << "Mode = ";
            getline(cin,mode);
            cout << endl;
        }

        if(mode == "q" || mode == "quit"){
            cout << "\n";
            cout << game_quit_msg << endl;
            break;
        }


        Minesweeper game((int)mode[0] - '0');
        clearScreen();
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
            cout << "Please enter 'd'/'dig' to dig, 'f'/'flag' to flag/unflag, 'n'/'new' to start a new game" << endl;
            cout << "Operation = ";
            getline(cin,operation);
            cout << "\n";

            while(!(operation == "dig" || operation == "d" || operation == "flag" || operation == "f" || operation == "new" || operation == "n")){
                cout << "Invalid input, please enter 'd'/'dig' or 'f'/'flag' to choose the type of your operation, enter 'n'/'new' to start a new game" << endl;
                cout << "Operation = ";
                getline(cin,operation);
                cout << "\n";
            }

            if(operation == "n" || operation == "new"){
                clearScreen();
                break;
            }

            if(operation == "d" || operation == "dig"){
                cout << "(Dig Mode) Please enter the row and column index of the dig operation, enter '0' to re-choice operation" << endl;
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
                        clearScreen();
                        game.printGame();
                        firstDig = false;
                    }
                }
                else{
                    if(game.applyDig(Location(rowInputInt,colInputInt))){
                        clearScreen();
                        game.printGame();
                    }
                }
                game.checkGameStatus();
                cin.ignore(1000, '\n');
            }

            if(operation == "f" || operation == "flag"){
                cout << "(Flag Mode) Please enter the row and column index of the flag operation, enter '0' to re-choice operation" << endl;
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
                    clearScreen();
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
                cout << "Start a new game? (please enter 'y'/'n')"<< endl;
                cout << "User input = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "Invalid input, please enter 'y'/'n'" << endl;
                    cout << "User input = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    clearScreen();
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
                cout << "Start a new game? (please enter 'y'/'n')"<< endl;
                cout << "User input = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "Invalid input, please enter 'y'/'n'" << endl;
                    cout << "User input = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    clearScreen();
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