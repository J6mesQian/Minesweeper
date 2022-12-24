#include "minesweeper.h"
#include <unistd.h>
using namespace std;

Minesweeper::Minesweeper(int diffculty){
   //case 0 = easy, case 1 = medium, case 2 = hard, case 3 = challenge
   _difficulty = diffculty;
   _gameStatus = 0;
   _userPositionRow = 0;
   _userPositionCol = 0;

   switch (_difficulty){
    case 0:
        _rowSize = 9;
        _colSize = 9;
        _bombNum = 10;
        _hasntVisited = _rowSize * _colSize - _bombNum;
        break;

    case 1:
        _rowSize = 16;
        _colSize = 16;
        _bombNum = 40;
        _hasntVisited = _rowSize * _colSize - _bombNum;
        break;

    case 2:
        _rowSize = 25;
        _colSize = 25;
        _bombNum = 100;
        _hasntVisited = _rowSize * _colSize - _bombNum;
        break;

    case 3:
        _rowSize = 30;
        _colSize = 40;
        _bombNum = 150;
        _hasntVisited = _rowSize * _colSize - _bombNum;
        break;
   }

   _flagNum = _bombNum;

   //initialize _minesweeperNumArr, 0 as default value, -1 as bomb
   //integer 0 to 8 indicate how many bombs are around current location 
   _minesweeperNumArr = new int*[_rowSize];
    for(int i = 0; i < _rowSize; i++){
        _minesweeperNumArr[i] = new int[_colSize];
        for(int j = 0; j < _colSize; j++){
            _minesweeperNumArr[i][j] = 0;
        }
    }

    //initialize _isVisited, false as default
    _isVisited = new bool*[_rowSize];
    for(int i = 0; i < _rowSize; i++){
        _isVisited[i] = new bool[_colSize];
        for(int j = 0; j < _colSize; j++){
            _isVisited[i][j] = false;
        }
    }

    //initialize _isFlaged, false as default
    _isFlaged = new bool*[_rowSize];
    for(int i = 0; i < _rowSize; i++){
        _isFlaged[i] = new bool[_colSize];
        for(int j = 0; j < _colSize; j++){
            _isFlaged[i][j] = false;
        }
    }
}

Minesweeper::~Minesweeper(){
    for(int i = 0; i < _rowSize; i++){
        delete [] _minesweeperNumArr[i];
    }
    delete [] _minesweeperNumArr;
    
    for(int i = 0; i < _rowSize; i++){
        delete [] _isVisited[i];
    }
    delete [] _isVisited;
    
    for(int i = 0; i < _rowSize; i++){
        delete [] _isFlaged[i];
    }
    delete [] _isFlaged;
}

bool Minesweeper::insertBomb(Location firstClick){
    //insert bombs
    if(_isFlaged[firstClick.row_][firstClick.col_]){
        return false;
    }
    srand(0);
    
    int waitForInsert = _bombNum;
    while(waitForInsert > 0){
        int rowRandom = rand() % _rowSize;
        int colRandom = rand() % _colSize;
        if(_minesweeperNumArr[rowRandom][colRandom] != -1 
        && ((rowRandom < (firstClick.row_ -1 - _difficulty) || rowRandom > (firstClick.row_ +1 + _difficulty)) 
        && (colRandom < (firstClick.col_ -1 - _difficulty) || colRandom > (firstClick.col_ +1 + _difficulty)))){
            _minesweeperNumArr[rowRandom][colRandom] = -1;
            waitForInsert--;
        }
        else{
            continue;;
        }
    }

    
    //shuffle
    for(int i = 0; i < min(_rowSize * _colSize, 900); i++){
        int rowIndex = i / _rowSize;
        int colIndex = i % _colSize;
        int indexRandom = rand() % (_rowSize*_colSize);
        int rowRandom = indexRandom / _colSize;
        int colRandom = indexRandom % _colSize;

        /*
        //memory full?
        cout << "i = " << i << "\n";
        cout << "rowIndex = " << rowIndex << "\n";
        cout << "colIndex = " << colIndex << "\n";
        cout << "rowRandom = " << rowRandom << "\n";
        cout << "colRandom = " << colRandom << "\n";
        cout << "_minesweeperNumArr[rowIndex][colIndex] = " << _minesweeperNumArr[rowIndex][colIndex] << "\n";
        cout << "_minesweeperNumArr[rowRandom][colRandom] = " << _minesweeperNumArr[rowRandom][colRandom] << "\n";
        */

        if((rowIndex > (firstClick.row_ -2 - _difficulty) && rowIndex < (firstClick.row_ +2 + _difficulty)) 
        && (colIndex > (firstClick.col_ -2 - _difficulty) && colIndex < (firstClick.col_ +2 + _difficulty))){
            i++;
            //cout << "continue" << "\n";
            continue;
        }
        else if((rowRandom > (firstClick.row_ -2 - _difficulty) && rowRandom < (firstClick.row_ +2 + _difficulty)) 
        && (colRandom > (firstClick.col_ -2 - _difficulty) && colRandom < (firstClick.col_ +2 + _difficulty))){
            //cout << "continue" << "\n";
            continue;
        }
        else{
            int temp = _minesweeperNumArr[rowIndex][colIndex];
            _minesweeperNumArr[rowIndex][colIndex] = _minesweeperNumArr[rowRandom][colRandom];
            _minesweeperNumArr[rowRandom][colRandom] = temp;
            //cout << "swap" << "\n";
        }
    }
    

    
    insertNumBombIndicator();
    
    //apply the first click
    applyClick(firstClick);
    return true;
}

void Minesweeper::insertNumBombIndicator(){
    //insert number of bomb around indicator
    
    for(int rowSearch = 0; rowSearch < _rowSize; rowSearch++){
        for(int colSearch = 0; colSearch < _colSize; colSearch++){
            if(_minesweeperNumArr[rowSearch][colSearch] == -1){
                if(rowSearch > 0 && _minesweeperNumArr[rowSearch - 1][colSearch] != -1){
                    _minesweeperNumArr[rowSearch - 1][colSearch]++;
                }

                if(rowSearch < _rowSize -1 && _minesweeperNumArr[rowSearch + 1][colSearch] != -1){
                    _minesweeperNumArr[rowSearch + 1][colSearch]++;
                }

                if(colSearch > 0 && _minesweeperNumArr[rowSearch][colSearch - 1] != -1){
                    _minesweeperNumArr[rowSearch][colSearch - 1]++;
                }

                if(colSearch < _colSize -1 && _minesweeperNumArr[rowSearch][colSearch + 1] != -1){
                    _minesweeperNumArr[rowSearch][colSearch + 1]++;
                }

                if(rowSearch > 0 && colSearch > 0 && _minesweeperNumArr[rowSearch - 1][colSearch - 1] != -1){
                    _minesweeperNumArr[rowSearch - 1][colSearch - 1]++;
                }

                if(rowSearch > 0 && colSearch < _colSize - 1 && _minesweeperNumArr[rowSearch - 1][colSearch + 1] != -1){
                    _minesweeperNumArr[rowSearch - 1][colSearch + 1]++;
                }

                if(rowSearch < _rowSize - 1 && colSearch > 0 && _minesweeperNumArr[rowSearch + 1][colSearch - 1] != -1){
                    _minesweeperNumArr[rowSearch + 1][colSearch - 1]++;
                }

                if(rowSearch < _rowSize - 1 && colSearch < _colSize - 1 && _minesweeperNumArr[rowSearch + 1][colSearch + 1] != -1){
                    _minesweeperNumArr[rowSearch + 1][colSearch + 1]++;
                }
            }
        }
    }
}

int Minesweeper::applyClick(Location clickOperation){
    if(_isVisited[clickOperation.row_][clickOperation.col_]){
        return -1;
    }
    else if(_isFlaged[clickOperation.row_][clickOperation.col_]){
        return -2;
    }
    else if(_minesweeperNumArr[clickOperation.row_][clickOperation.col_] == -1){
        //game lose
        _isVisited[clickOperation.row_][clickOperation.col_] = true;
        _gameStatus = -1;
    }
    else if(_minesweeperNumArr[clickOperation.row_][clickOperation.col_] == 0){
        //use BFS to show all 0 and bombs number indicator around
        deque<Location> stackBFS;
        stackBFS.push_back(clickOperation);
        _isVisited[clickOperation.row_][clickOperation.col_] = true;
        _hasntVisited--;
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
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        } 
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else if (waitForCheck.col_ == _colSize - 1) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_upperright[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_upperright[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        } 
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_upper[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_upper[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
            }
            else if (waitForCheck.row_ == _rowSize - 1) {
                if (waitForCheck.col_ == 0) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottomleft[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottomleft[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        } 
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else if (waitForCheck.col_ == _colSize - 1) {
                    for (int i = 0; i < 3; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottomright[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottomright[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_bottom[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_bottom[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        } 
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
            }
            else {
                if (waitForCheck.col_ == 0) {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_left[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_left[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        } 
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else if (waitForCheck.col_ == _colSize - 1) {
                    for (int i = 0; i < 5; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_right[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_right[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        int rowIndex = waitForCheck.row_ + neighbor_row_middle[i];
                        int colIndex = waitForCheck.col_ + neighbor_col_middle[i];
                        if (_minesweeperNumArr[rowIndex][colIndex] == 0 && !_isVisited[rowIndex][colIndex]) {
                            stackBFS.push_back(Location(rowIndex, colIndex));
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        else if (!_isVisited[rowIndex][colIndex] && _minesweeperNumArr[rowIndex][colIndex] > 0) {
                            _isVisited[rowIndex][colIndex] = true;
                            _hasntVisited--;
                        }
                        if(_isFlaged[rowIndex][colIndex]){
                            _isFlaged[rowIndex][colIndex] = false;
                            _flagNum++;
                        }
                    }
                }
            }
        }
    }
    else if(_minesweeperNumArr[clickOperation.row_][clickOperation.col_] > 0){
        _isVisited[clickOperation.row_][clickOperation.col_] = true;
        _hasntVisited--;
        return true;
    }
    return true;
}

bool Minesweeper::applyFlag(Location FlagOperation){
    if(_isVisited[FlagOperation.row_][FlagOperation.col_]){
        //ask user to re-enter the location
        
        cout << "\n";
        return false;
    }
    else if(_isFlaged[FlagOperation.row_][FlagOperation.col_]){
        //remove the flag
        _isFlaged[FlagOperation.row_][FlagOperation.col_] = false;
        _flagNum++;
        return true;
    }
    else{
        _isFlaged[FlagOperation.row_][FlagOperation.col_] = true;
        _flagNum--;
        return true;
    }
}


bool Minesweeper::checkGameStatus(){
    if(_hasntVisited == 0){
        _gameStatus = 1;
        return true;
    }
    if(_flagNum == 0){
        for(int i = 0; i < _rowSize; i++){
            for(int j = 0; j < _colSize; j++){
                if(_isFlaged[i][j]){
                    if(!(_minesweeperNumArr[i][j] == - 1)){
                        return false;
                    }
                }
            }
        }
        _gameStatus = 1;
        return true;
    }
    return false;
}

void Minesweeper::printGame(){ 
    cout << "\n";
    cout << "    ";
    for(int i = 0; i < _colSize; i++){
        cout << setw(4) << i+1;
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    for(int i = 0; i < _rowSize; i++){
        cout << setw(2) << i+1 << "  ";
        for(int j = 0; j < _colSize; j++){
             bool isUserLocation = (i == _userPositionRow && j == _userPositionCol);
             if(_isFlaged[i][j]){
                if(isUserLocation){
                    cout << " >██";
                }
                else{
                    cout << "  ██";
                }
             }
             else if(!_isVisited[i][j]){
                if(isUserLocation){
                    cout << " >░░";
                }
                else{
                    cout << "  ░░";
                }
             }
             else if(_minesweeperNumArr[i][j] == 0){
                if(isUserLocation){
                    cout << "  >.";
                }
                else{
                    cout << "   .";
                }
             }
             else if(_minesweeperNumArr[i][j] == -1){
                if(isUserLocation){
                    cout <<"  >*";
                }
                else{
                    cout <<"   *";
                }
             }
             else{
                if(isUserLocation){
                    cout << "  >" << _minesweeperNumArr[i][j];
                }
                else{
                    cout << "   " << _minesweeperNumArr[i][j];
                }
             }
        }
        cout << "\n";
        cout << "\n";
    }
    string flagRemian = "Flags Remain: " + to_string(_flagNum);
    cout << setw(_colSize * 4 + 4) << flagRemian << "\n";
    cout << "\n";
}

void Minesweeper::printAll(){ 
    cout << "\n";
    cout << "    ";
    for(int i = 0; i < _colSize; i++){
        cout << setw(4) << i+1;
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    for(int i = 0; i < _rowSize; i++){
        cout << setw(2) << i+1 << "  ";
        for(int j = 0; j < _colSize; j++){
             if(_minesweeperNumArr[i][j] == 0){
                cout << setw(4) << ".";
             }
             else if(_minesweeperNumArr[i][j] == -1){
                if(_gameStatus == -1 && (i == _userPositionRow && j == _userPositionCol)){
                    cout << setw(4) << ">*";
                }
                else{
                    cout << setw(4) << "*";
                }
             }
             else{
                cout << setw(4) << _minesweeperNumArr[i][j];
             }
        }
        cout << "\n";
        cout << "\n";
    }
}

