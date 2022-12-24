
/*********************************************************
 * Welcome to Minesweeper
 * Author: Yuxi Qian
 * Date: 11-15-2022
 * Version: 2.4
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

string game_quit_msg_line1 = "   ██████╗      █████╗     ███╗   ███╗    ███████╗           ██████╗     ██╗   ██╗    ██╗    ████████╗ ";
string game_quit_msg_line2 = "  ██╔════╝     ██╔══██╗    ████╗ ████║    ██╔════╝          ██╔═══██╗    ██║   ██║    ██║    ╚══██╔══╝ ";
string game_quit_msg_line3 = "  ██║  ███╗    ███████║    ██╔████╔██║    █████╗            ██║   ██║    ██║   ██║    ██║       ██║    ";
string game_quit_msg_line4 = "  ██║   ██║    ██╔══██║    ██║╚██╔╝██║    ██╔══╝            ██║▄▄ ██║    ██║   ██║    ██║       ██║    ";
string game_quit_msg_line5 = "  ╚██████╔╝    ██║  ██║    ██║ ╚═╝ ██║    ███████╗          ╚██████╔╝    ╚██████╔╝    ██║       ██║    ";
string game_quit_msg_line6 = "   ╚═════╝     ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚══════╝           ╚══▀▀═╝      ╚═════╝     ╚═╝       ╚═╝    ";

string game_win_msg_line1 = "  ██╗   ██╗     ██████╗     ██╗   ██╗          ██╗    ██╗     ██████╗     ███╗   ██╗ ";
string game_win_msg_line2 = "  ╚██╗ ██╔╝    ██╔═══██╗    ██║   ██║          ██║    ██║    ██╔═══██╗    ████╗  ██║ ";
string game_win_msg_line3 = "   ╚████╔╝     ██║   ██║    ██║   ██║          ██║ █╗ ██║    ██║   ██║    ██╔██╗ ██║ ";
string game_win_msg_line4 = "    ╚██╔╝      ██║   ██║    ██║   ██║          ██║███╗██║    ██║   ██║    ██║╚██╗██║ ";
string game_win_msg_line5 = "     ██║       ╚██████╔╝    ╚██████╔╝          ╚███╔███╔╝    ╚██████╔╝    ██║ ╚████║ ";
string game_win_msg_line6 = "     ╚═╝        ╚═════╝      ╚═════╝            ╚══╝╚══╝      ╚═════╝     ╚═╝  ╚═══╝ ";

string game_lose_msg_line1 = "  ██╗   ██╗     ██████╗     ██╗   ██╗          ██╗          ██████╗     ███████╗    ████████╗ ";
string game_lose_msg_line2 = "  ╚██╗ ██╔╝    ██╔═══██╗    ██║   ██║          ██║         ██╔═══██╗    ██╔════╝    ╚══██╔══╝ ";
string game_lose_msg_line3 = "   ╚████╔╝     ██║   ██║    ██║   ██║          ██║         ██║   ██║    ███████╗       ██║    ";
string game_lose_msg_line4 = "    ╚██╔╝      ██║   ██║    ██║   ██║          ██║         ██║   ██║    ╚════██║       ██║    ";
string game_lose_msg_line5 = "     ██║       ╚██████╔╝    ╚██████╔╝          ███████╗    ╚██████╔╝    ███████║       ██║    ";
string game_lose_msg_line6 = "     ╚═╝        ╚═════╝      ╚═════╝           ╚══════╝     ╚═════╝     ╚══════╝       ╚═╝    ";

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
    cout << "\n" << "\n";

    int mode = 0;
    char modeInputBuffer = '\0';
    while(mode != 4){
        do{
            cout << "\n";
            cout << "\n";
            cout << gameTitle;
            cout << setw(132) << "Version: 2.4"<< "\n";
            cout << "\n";

            cout << "  PLEASE CHOOSE YOUR GAME DIFFICULTY:" << "\n" << "\n";

            if(mode == 0){
                cout << "> ESAY, 9X9, 20 BOMBS <" << "\n";
            }
            else if(mode != 0){
                cout << "  ESAY, 9X9, 20 BOMBS" << "\n";
            }

            if(mode == 1){
                cout << "> MEDIUM, 16X16, 50 BOMBS <" << "\n";
            }
            else if(mode != 1){
                cout << "  MEDIUM, 16X16, 50 BOMBS" << "\n";
            }
            
            if(mode == 2){
                cout << "> HARD, 25X25, 100 BOMBS <" << "\n";
            }
            else if(mode != 2){
                cout << "  HARD, 25X25, 100 BOMBS" << "\n";
            }
            
            if(mode == 3){
                cout << "> CHALLENGE, 30X40, 200 BOMBS <" << "\n";
            }
            else if(mode != 3){
                cout << "  CHALLENGE, 30X40, 200 BOMBS" << "\n";
            }

            if(mode == 4){
                cout << "> QUIT <" << "\n";
            }
            else if(mode != 4){
                cout << "  QUIT" << "\n" ;
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
            cout << "\n" << "\n";
        }while(modeInputBuffer != '\n');

        if(mode == 4){
            cout << "\n";
            cout << gameTitle;
            cout << setw(132) << "Version: 2.4"<< "\n";
            cout << "\n";
            cout << game_quit_msg << "\n";
            break;
        }


        Minesweeper game(mode);
        mode = 0;
        system("clear");
        cout << "\n" << "\n";
        
        bool firstClick = true;
        bool startNewGmae = false;
        int rowInputInt;
        int colInputInt;
        int errorMSG = -1;

        //main game
        do{
            char moveBuffer = '\0';
            if(startNewGmae){
                startNewGmae = false;
                break;
            }

            do{
                switch (errorMSG)
                {
                case 1:
                    cout << "COULDN'T FLAG HAS-BEEN-VISITED LOCATION" << "\n" << "\n";
                    errorMSG = -1;
                    break;

                case 2:
                    cout << "COULDN'T CLICK HAS-BEEN-FLAGED LOCATION" << "\n" <<"\n";
                    errorMSG = -1;
                    break;
                
                case 3:
                    cout << "COULDN'T CLICK HAS-BEEN-VISITED LOCATION" << "\n" << "\n";
                    errorMSG = -1;
                    break;
                }
                
                string case0Title = "EASY MODE, " + to_string( game.returnRowSize()) + "X" + to_string(game.returnColSize()) + ", " + to_string(game.returnBombNum()) + " BOMBS";
                string case1Title = "MEDIUM MODE, " + to_string( game.returnRowSize()) + "X" + to_string(game.returnColSize()) + ", " + to_string(game.returnBombNum()) + " BOMBS";
                string case2Title = "HARD MODE, " + to_string( game.returnRowSize()) + "X" + to_string(game.returnColSize()) + ", " + to_string(game.returnBombNum()) + " BOMBS";
                string case3Title = "CHALLENGE MODE, " + to_string( game.returnRowSize()) + "X" + to_string(game.returnColSize()) + ", " + to_string(game.returnBombNum()) + " BOMBS";
                int leading_spaces_0 = ((game.returnColSize()*4 + 10) - case0Title.size())/2 + case0Title.size();
                int leading_spaces_1 = ((game.returnColSize()*4 + 11) - case1Title.size())/2 + case0Title.size();
                int leading_spaces_2 = ((game.returnColSize()*4 + 8) - case2Title.size())/2 + case0Title.size();
                int leading_spaces_3 = ((game.returnColSize()*4 + 19) - case3Title.size())/2 + case0Title.size();
                switch (game.returnDiffculty()){
                case 0:
                    cout << setw(leading_spaces_0) << case0Title << "\n";
                    break;

                case 1:
                    cout << setw(leading_spaces_1) << case1Title << "\n";
                    break;

                case 2:
                    cout << setw(leading_spaces_2) << case2Title << "\n";
                    break;

                case 3:
                    cout << setw(leading_spaces_3) << case3Title << "\n";
                    break;
                }

                game.printGame();
                cout << "PRESS 'W/A/S/D' TO MOVE, 'F' TO FLAG, 'N' TO START A NEW GAME, ENTER TO CLICK)" << '\n';

                moveBuffer = getch();

                while(!(moveBuffer == 'w' || moveBuffer == 'W' || moveBuffer == 'a' || moveBuffer == 'A' 
                || moveBuffer == 's' || moveBuffer == 'S' || moveBuffer == 'd' || moveBuffer == 'D'
                || moveBuffer == 'f' || moveBuffer == 'F' || moveBuffer == 'c' || moveBuffer == 'C' 
                || moveBuffer == '\n' || moveBuffer == 'n' || moveBuffer =='N')){
                    moveBuffer = getch();
                }

                while((game.returnUserPositionRow() == 0 && (moveBuffer == 'w' || moveBuffer == 'W'))
                || (game.returnUserPositionRow() == (game.returnRowSize() - 1) && (moveBuffer == 's' || moveBuffer == 'S'))
                || (game.returnUserPositionCol() == 0 && (moveBuffer == 'a' || moveBuffer == 'A'))
                || (game.returnUserPositionCol() == (game.returnColSize() - 1) && (moveBuffer == 'd' || moveBuffer == 'D'))){ 
                    moveBuffer = getch();
                }

                if(moveBuffer == 'n' || moveBuffer =='N'){
                    string userInput;
                    cout << "\n";
                    cout << "CONFIRM TO STRRT A NEW GAME? (PLEASE ENTER 'Y'/'N' )" << "\n";
                    cout << "USER INPUT = ";
                    getline(cin,userInput);
                    cout << "\n";
                    while(!(userInput == "y" || userInput == "n")){
                        cout << "INVALID INPUT, PLEASE ENTER 'Y'/'N'" << "\n";
                        cout << "USER INPUT = ";
                        getline(cin,userInput);
                        cout << "\n";
                    }
                    
                    if(userInput == "y"){
                        system("clear");
                        cout << "\n" << "\n";
                        startNewGmae = true;
                        break;
                    }
                    else if(userInput == "n"){
                        system("clear");
                        cout << "\n" << "\n";
                        continue;
                    }
                }
                else if(moveBuffer == 'f' || moveBuffer == 'F'){
                    rowInputInt = game.returnUserPositionRow();
                    colInputInt = game.returnUserPositionCol();
                    if(!game.applyFlag(Location(rowInputInt,colInputInt))){
                        errorMSG = 1;
                    }else{
                        game.checkGameStatus();
                    }
                }
                else if(moveBuffer == '\n'){
                    rowInputInt = game.returnUserPositionRow();
                    colInputInt = game.returnUserPositionCol();
                    if(firstClick){
                        if(game.insertBomb(Location(rowInputInt,colInputInt))){
                            firstClick = false;
                        }
                        else{
                            errorMSG = 2;
                        }
                    }
                    else{
                        if(game.applyClick(Location(rowInputInt,colInputInt)) == -1){
                            errorMSG = 3;
                        }
                        else if (game.applyClick(Location(rowInputInt,colInputInt)) == -2){
                            errorMSG = 2;
                        }
                        else{
                            game.checkGameStatus();
                        }
                    }
                }
                else if(moveBuffer == 'w' || moveBuffer == 'W'){
                    game.returnUserPositionRow()--;
                }
                else if(moveBuffer == 's' || moveBuffer == 'S'){
                    game.returnUserPositionRow()++;
                }
                else if(moveBuffer == 'a' || moveBuffer == 'A'){
                    game.returnUserPositionCol()--;
                }
                else if(moveBuffer == 'd' || moveBuffer == 'D'){
                    game.returnUserPositionCol()++;
                }
                system("clear");
                cout << "\n" << "\n";
            }while(moveBuffer != '\n');


            if(game.returnGameStatus() == 1){
                game.printGame();
                cout << "\n";
                cout << game_win_msg;
                cout << "\n";
                game.printAll();

                string userInput;
                cout << "\n";
                cout << "START A NEW GAME? (PLEASE ENTER 'Y'/'N')"<< "\n";
                cout << "USER INPUT = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "INVALID INPUT, PLEASE ENTER 'Y'/'N'" << "\n";
                    cout << "USER INPUT = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    system("clear");
                    cout << "\n" << "\n";
                    break;
                }

                else if(userInput == "n"){
                    system("clear");
                    cout << "\n" << "\n";
                    cout << "\n";
                    cout << gameTitle;
                    cout << setw(132) << "Version: 2.4"<< "\n";
                    cout << "\n";
                    cout << game_quit_msg;
                    cout << "\n";
                    return 0;
                }
            }

            if(game.returnGameStatus() == -1){
                game.printGame();
                cout << "\n";
                cout << game_lose_msg;
                cout << "\n";
                game.printAll();
                
                string userInput;
                cout << "\n";
                cout << "START A NEW GAME? (PLEASE ENTER 'Y'/'N')"<< "\n";
                cout << "USER INPUT = ";
                getline(cin,userInput);
                cout << "\n";
                while(!(userInput == "y" || userInput == "n")){
                    cout << "INVALID INPUT, PLEASE ENTER 'Y'/'N'" << "\n";
                    cout << "USER INPUT = ";
                    getline(cin,userInput);
                    cout << "\n";
                }
                
                if(userInput == "y"){
                    system("clear");
                    cout << "\n" << "\n";
                    break;
                }

                else if(userInput == "n"){
                    system("clear");
                    cout << "\n" << "\n";
                    cout << "\n";
                    cout << gameTitle;
                    cout << setw(132) << "Version: 2.4"<< "\n";
                    cout << "\n";
                    cout << game_quit_msg;
                    cout << "\n";
                    return 0;
                }
            }
        }while(game.returnGameStatus() == 0);
    }
    return 0;
}