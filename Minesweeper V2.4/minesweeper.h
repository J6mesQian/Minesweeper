#include <iostream>
#include <iomanip>
#include <cmath>
#include <deque>

struct Location{
    Location(int row, int col){
        _row = row;
        _col = col;
    }
    int _row;
    int _col;
};

class Minesweeper{
    public:
    Minesweeper(int diffculty);
    ~Minesweeper();

    //insertBomb
    bool insertBomb(Location firstClick);

    //insert number of bomb indicator in 9x9 area around
    void insertNumBombIndicator();

    //return -1 when user clicks visited location
    //return -2 when user clicks flaged location
    //set _gameStatus to -1 when click at bomb
    //use BFS to modify _isVisited mask 
    int applyClick(Location clickOperation);

    //apply flag
    //remove flag when user enters the flaged location
    //return false when user flags visited location
    bool applyFlag(Location FlagOperation);

    //check game status, if all flags have been placed to correct location, then set _gameStatus to 1 (win), and return true
    //if user has visited all location expect the bomb, then set _gameStatus to 1 (win), and return true
    //else return flase
    bool checkGameStatus();

    //print game with _isVisited musk and isFlaged musk
    void printGame();

    //print game without _isVisited musk and isFlaged musk
    void printAll();
    

    int returnRowSize() const{
        return _rowSize;
    }
    
    int returnColSize() const{
        return _colSize;
    }

    int returnBombNum() const{
        return _bombNum;
    }

    int returnFlagNum() const{
        return _flagNum;
    }

    int return_hasntVisited_() const{
        return _hasntVisited;
    }

    int returnGameStatus() const{
        return _gameStatus;
    }

    int returnDiffculty() const{
        return _difficulty;
    }

    int& returnUserPositionRow(){
        return _userPositionRow;
    }

    int& returnUserPositionCol(){
        return _userPositionCol;
    }
    private:

    //initialize minesweeperNumArr, 0 as default value, -1 as bomb, -2 as bomb that user clicks
    //integer 0 to 8 indicate how many bombs are around current location 
    int ** _minesweeperNumArr;

    bool** _isVisited;
    bool** _isFlaged;
    int _rowSize;
    int _colSize;
    int _bombNum;
    int _flagNum;
    int _hasntVisited;
    int _userPositionRow;
    int _userPositionCol;


    //0 = easy, 1 = medium, 2 = hard, 3 = challenge
    int _difficulty;

    //0 as in progress (default value), -1 as lose, 1 as win
    int _gameStatus;
};