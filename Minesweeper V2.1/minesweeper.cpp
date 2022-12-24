#include "minesweeper.h"
#include <unistd.h>
using namespace std;

Minesweeper::Minesweeper(int diffculty){
   //case 0 = easy, case 1 = medium, case 2 = hard, case 3 = challenge
   difficulty_ = diffculty;
   gameStatus_ = 0;
   
   switch (difficulty_){
    case 0:
        rowSize_ = 9;
        colSize_ = 9;
        bombNum_ = 10;
        hasntVisited_ = rowSize_ * colSize_ - bombNum_;
        break;

    case 1:
        rowSize_ = 16;
        colSize_ = 16;
        bombNum_ = 40;
        hasntVisited_ = rowSize_ * colSize_ - bombNum_;
        break;

    case 2:
        rowSize_ = 25;
        colSize_ = 25;
        bombNum_ = 100;
        hasntVisited_ = rowSize_ * colSize_ - bombNum_;
        break;

    case 3:
        rowSize_ = 30;
        colSize_ = 40;
        bombNum_ = 150;
        hasntVisited_ = rowSize_ * colSize_ - bombNum_;
        break;
   }

   flagNum_ = bombNum_;

   //initialize minesweeperNumArr_, 0 as default value, -1 as bomb
   //integer 0 to 8 indicate how many bombs are around current location 
   minesweeperNumArr_ = new int*[rowSize_];
    for(int i = 0; i < rowSize_; i++){
        minesweeperNumArr_[i] = new int[colSize_];
        for(int j = 0; j < colSize_; j++){
            minesweeperNumArr_[i][j] = 0;
        }
    }

    //initialize isVisited_, false as default
    isVisited_ = new bool*[rowSize_];
    for(int i = 0; i < rowSize_; i++){
        isVisited_[i] = new bool[colSize_];
        for(int j = 0; j < colSize_; j++){
            isVisited_[i][j] = false;
        }
    }

    //initialize isFlaged_, false as default
    isFlaged_ = new bool*[rowSize_];
    for(int i = 0; i < rowSize_; i++){
        isFlaged_[i] = new bool[colSize_];
        for(int j = 0; j < colSize_; j++){
            isFlaged_[i][j] = false;
        }
    }
}

Minesweeper::~Minesweeper(){
    for(int i = 0; i < rowSize_; i++){
        delete [] minesweeperNumArr_[i];
    }
    delete [] minesweeperNumArr_;
    
    for(int i = 0; i < rowSize_; i++){
        delete [] isVisited_[i];
    }
    delete [] isVisited_;
    
    for(int i = 0; i < rowSize_; i++){
        delete [] isFlaged_[i];
    }
    delete [] isFlaged_;
}

bool Minesweeper::insertBomb(Location firstDig){
    //insert bombs
    if(isFlaged_[firstDig.row_][firstDig.col_]){
        cout << "\n";
        cout << "Invalid input, couldn't dig has-been-flaged location" << "\n";
        return false;
    }
    srand(time(0));
    
    int waitForInsert = bombNum_;
    while(waitForInsert > 0){
        int rowRandom = rand() % rowSize_;
        int colRandom = rand() % colSize_;
        if(minesweeperNumArr_[rowRandom][colRandom] != -1 
        && ((rowRandom < (firstDig.row_ -1 - difficulty_) || rowRandom > (firstDig.row_ +1 + difficulty_)) 
        && (colRandom < (firstDig.col_ -1 - difficulty_) || colRandom > (firstDig.col_ +1 + difficulty_)))){
            minesweeperNumArr_[rowRandom][colRandom] = -1;
            waitForInsert--;
        }
        else{
            continue;;
        }
    }

    
    //shuffle
    for(int i = 0; i < min(rowSize_ * colSize_, 900); i++){
        int rowIndex = i / rowSize_;
        int colIndex = i % colSize_;
        int indexRandom = rand() % (rowSize_*colSize_);
        int rowRandom = indexRandom / colSize_;
        int colRandom = indexRandom % colSize_;

        /*
        //memory full?
        cout << "i = " << i << "\n";
        cout << "rowIndex = " << rowIndex << "\n";
        cout << "colIndex = " << colIndex << "\n";
        cout << "rowRandom = " << rowRandom << "\n";
        cout << "colRandom = " << colRandom << "\n";
        cout << "minesweeperNumArr_[rowIndex][colIndex] = " << minesweeperNumArr_[rowIndex][colIndex] << "\n";
        cout << "minesweeperNumArr_[rowRandom][colRandom] = " << minesweeperNumArr_[rowRandom][colRandom] << "\n";
        */

        if((rowIndex > (firstDig.row_ -2 - difficulty_) && rowIndex < (firstDig.row_ +2 + difficulty_)) 
        && (colIndex > (firstDig.col_ -2 - difficulty_) && colIndex < (firstDig.col_ +2 + difficulty_))){
            i++;
            //cout << "continue" << "\n";
            continue;
        }
        else if((rowRandom > (firstDig.row_ -2 - difficulty_) && rowRandom < (firstDig.row_ +2 + difficulty_)) 
        && (colRandom > (firstDig.col_ -2 - difficulty_) && colRandom < (firstDig.col_ +2 + difficulty_))){
            //cout << "continue" << "\n";
            continue;
        }
        else{
            int temp = minesweeperNumArr_[rowIndex][colIndex];
            minesweeperNumArr_[rowIndex][colIndex] = minesweeperNumArr_[rowRandom][colRandom];
            minesweeperNumArr_[rowRandom][colRandom] = temp;
            //cout << "swap" << "\n";
        }
    }
    

    
    insertNumBombIndicator();
    
    //apply the first dig
    applyDig(firstDig);
    return true;
}

void Minesweeper::insertNumBombIndicator(){
    //insert number of bomb around indicator
    int neighbor_row_middle[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int neighbor_col_middle[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int neighbor_row_upperleft[3] = {1,1,0};
    int neighbor_col_upperleft[3] = {0,1,1};
    int neighbor_row_upperright[3] = {1,1,0};
    int neighbor_col_upperright[3] = {0,-1,-1};
    int neighbor_row_bottomright[3] = {-1,-1,0};
    int neighbor_col_bottomright[3] = {0,-1,-1};
    int neighbor_row_bottomleft[3] = {-1,-1,0};
    int neighbor_col_bottomleft[3] = {0,1,1};
    int neighbor_row_upper[5] = {0,0,1,1,1};
    int neighbor_col_upper[5] = {-1,1,-1,0,1};
    int neighbor_row_bottom[5] = {0,0,-1,-1,-1};
    int neighbor_col_bottom[5] = {-1,1,-1,0,1};
    int neighbor_row_left[5] = {-1,1,-1,0,1};
    int neighbor_col_left[5] = {0,0,1,1,1};
    int neighbor_row_right[5] = {-1,1,-1,0,1};
    int neighbor_col_right[5] = {0,0,-1,-1,-1};

    for(int rowSearch = 0; rowSearch < rowSize_; rowSearch++){
        for(int colSearch = 0; colSearch < colSize_; colSearch++){
            if(minesweeperNumArr_[rowSearch][colSearch] == -1){
                if(rowSearch == 0){
                    if(colSearch == 0){
                        for(int i = 0; i < 3; i++){
                            int rowIndex = rowSearch + neighbor_row_upperleft[i];
                            int colIndex = colSearch + neighbor_col_upperleft[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else if(colSearch == colSize_ -1){
                        for(int i = 0; i < 3; i++){
                            int rowIndex = rowSearch + neighbor_row_upperright[i];
                            int colIndex = colSearch + neighbor_col_upperright[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else{
                        for(int i = 0; i < 5; i++){
                            int rowIndex = rowSearch + neighbor_row_upper[i];
                            int colIndex = colSearch + neighbor_col_upper[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                }
                else if(rowSearch == rowSize_ -1){
                    if(colSearch == 0){
                        for(int i = 0; i < 3; i++){
                            int rowIndex = rowSearch + neighbor_row_bottomleft[i];
                            int colIndex = colSearch + neighbor_col_bottomleft[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else if(colSearch == colSize_ -1){
                        for(int i = 0; i < 3; i++){
                            int rowIndex = rowSearch + neighbor_row_bottomright[i];
                            int colIndex = colSearch + neighbor_col_bottomright[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else{
                        for(int i = 0; i < 5; i++){
                            int rowIndex = rowSearch + neighbor_row_bottom[i];
                            int colIndex = colSearch + neighbor_col_bottom[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                }
                else{
                    if(colSearch == 0){
                        for(int i = 0; i < 5; i++){
                            int rowIndex = rowSearch + neighbor_row_left[i];
                            int colIndex = colSearch + neighbor_col_left[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else if(colSearch == colSize_ -1){
                        for(int i = 0; i < 5; i++){
                            int rowIndex = rowSearch + neighbor_row_right[i];
                            int colIndex = colSearch + neighbor_col_right[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                    else{
                        for(int i = 0; i < 8; i++){
                            int rowIndex = rowSearch + neighbor_row_middle[i];
                            int colIndex = colSearch + neighbor_col_middle[i];
                            if(minesweeperNumArr_[rowIndex][colIndex] != -1){
                                minesweeperNumArr_[rowIndex][colIndex]++;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool Minesweeper::applyDig(Location digOperation){
    if(isVisited_[digOperation.row_][digOperation.col_]){
        //ask user to re-enter the location
        cout << "Invalid input, couldn't dig has-been-visited location" << "\n";
        cout << "\n";
        return false;
    }
    else if(isFlaged_[digOperation.row_][digOperation.col_]){
        //ask user to re-enter the location
        cout << "Invalid input, couldn't dig has-been-flaged location" << "\n";
        cout << "\n";
        return false;
    }
    else if(minesweeperNumArr_[digOperation.row_][digOperation.col_] == -1){
        //game lose
        minesweeperNumArr_[digOperation.row_][digOperation.col_] = -2;
        isVisited_[digOperation.row_][digOperation.col_] = true;
        gameStatus_ = -1;
    }
    else if(minesweeperNumArr_[digOperation.row_][digOperation.col_] == 0){
        //use BFS to show all 0 and bombs number indicator around
        deque<Location> stackBFS;
        stackBFS.push_back(digOperation);
        isVisited_[digOperation.row_][digOperation.col_] = true;
        hasntVisited_--;
        while(!stackBFS.empty()){
            Location waitForCheck = stackBFS.front();
            stackBFS.pop_front();
            //check for neighbor
            int neighbor_row_middle[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
            int neighbor_col_middle[8] = {0, -1, -1, -1, 0, 1, 1, 1};
            int neighbor_row_upperleft[3] = {1,1,0};
            int neighbor_col_upperleft[3] = {0,1,1};
            int neighbor_row_upperright[3] = {1,1,0};
            int neighbor_col_upperright[3] = {0,-1,-1};
            int neighbor_row_bottomright[3] = {-1,-1,0};
            int neighbor_col_bottomright[3] = {0,-1,-1};
            int neighbor_row_bottomleft[3] = {-1,-1,0};
            int neighbor_col_bottomleft[3] = {0,1,1};
            int neighbor_row_upper[5] = {0,0,1,1,1};
            int neighbor_col_upper[5] = {-1,1,-1,0,1};
            int neighbor_row_bottom[5] = {0,0,-1,-1,-1};
            int neighbor_col_bottom[5] = {-1,1,-1,0,1};
            int neighbor_row_left[5] = {-1,1,-1,0,1};
            int neighbor_col_left[5] = {0,0,1,1,1};
            int neighbor_row_right[5] = {-1,1,-1,0,1};
            int neighbor_col_right[5] = {0,0,-1,-1,-1};

            if (waitForCheck.row_ == 0) {
                if (waitForCheck.col_ == 0) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_upperleft[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_upperleft[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        } 
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else if (waitForCheck.col_ == colSize_ - 1) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_upperright[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_upperright[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        } 
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_upper[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_upper[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
            }
            else if (waitForCheck.row_ == rowSize_ - 1) {
                if (waitForCheck.col_ == 0) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottomleft[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottomleft[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        } 
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else if (waitForCheck.col_ == colSize_ - 1) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottomright[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottomright[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottom[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottom[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        } 
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
            }
            else {
                if (waitForCheck.col_ == 0) {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_left[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_left[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        } 
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else if (waitForCheck.col_ == colSize_ - 1) {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_right[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_right[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_middle[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_middle[i];
                        if (minesweeperNumArr_[rowIndex][colIndex] == 0 && !isVisited_[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        else if (!isVisited_[rowIndex][colIndex] && minesweeperNumArr_[rowIndex][colIndex] > 0) {
                            isVisited_[rowIndex][colIndex] = true;
                            hasntVisited_--;
                        }
                        if(isFlaged_[rowIndex][colIndex]){
                            isFlaged_[rowIndex][colIndex] = false;
                            flagNum_++;
                        }
                    }
                }
            }
        }
    }
    else if(minesweeperNumArr_[digOperation.row_][digOperation.col_] > 0){
        isVisited_[digOperation.row_][digOperation.col_] = true;
        hasntVisited_--;
        return true;
    }
    return true;
}

bool Minesweeper::applyFlag(Location FlagOperation){
    if(isVisited_[FlagOperation.row_][FlagOperation.col_]){
        //ask user to re-enter the location
        cout << "Invalid input, couldn't flag has-been-visited location" << "\n";
        cout << "\n";
        return false;
    }
    else if(isFlaged_[FlagOperation.row_][FlagOperation.col_]){
        //remove the flag
        isFlaged_[FlagOperation.row_][FlagOperation.col_] = false;
        flagNum_++;
        return true;
    }
    else{
        isFlaged_[FlagOperation.row_][FlagOperation.col_] = true;
        flagNum_--;
        return true;
    }
}


bool Minesweeper::checkGameStatus(){
    if(hasntVisited_ == 0){
        gameStatus_ = 1;
        return true;
    }
    if(flagNum_ == 0){
        for(int i = 0; i < rowSize_; i++){
            for(int j = 0; j < colSize_; j++){
                if(isFlaged_[i][j]){
                    if(!(minesweeperNumArr_[i][j] == - 1)){
                        return false;
                    }
                }
            }
        }
        gameStatus_ = 1;
        return true;
    }
    return false;
}

void Minesweeper::printGame(){ 
    cout << "\n";
    cout << "    ";
    for(int i = 0; i < colSize_; i++){
        cout << setw(4) << i+1;
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    for(int i = 0; i < rowSize_; i++){
        cout << setw(2) << i+1 << "   ";
        for(int j = 0; j < colSize_; j++){
             if(isFlaged_[i][j]){
                cout << " ██ ";
             }
             else if(!isVisited_[i][j]){
                cout << " ░░ ";
             }
             else if(minesweeperNumArr_[i][j] == 0){
                cout << "  . ";
             }
             else if(minesweeperNumArr_[i][j] == -2){
                //bombs that user digs
                cout <<"> * ";
             }
             else if(minesweeperNumArr_[i][j] == -1){
                cout <<"  * ";
             }
             else{
                cout << "  " << minesweeperNumArr_[i][j] << " ";
             }
        }
        cout << "\n";
        cout << "\n";
    }
    string flagRemian = "Flags Remain: " + to_string(flagNum_);
    cout << setw(colSize_ * 4 + 4) << flagRemian << "\n";
    cout << "\n";
}

void Minesweeper::printAll(){ 
    cout << "\n";
    cout << "    ";
    for(int i = 0; i < colSize_; i++){
        cout << setw(4) << i+1;
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    for(int i = 0; i < rowSize_; i++){
        cout << setw(2) << i+1 << "  ";
        for(int j = 0; j < colSize_; j++){
             if(minesweeperNumArr_[i][j] == 0){
                cout << setw(4) << ".";
             }
             else if(minesweeperNumArr_[i][j] == -1){
                cout << setw(4) << "*";
             }
             else if(minesweeperNumArr_[i][j] == -2){
                //bombs that user digs
                cout <<" > *";
             }
             else{
                cout << setw(4) << minesweeperNumArr_[i][j];
             }
        }
        cout << "\n";
        cout << "\n";
    }
}

