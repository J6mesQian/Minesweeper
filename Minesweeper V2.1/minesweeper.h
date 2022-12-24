#include <iostream>
#include <iomanip>
#include <cmath>
#include <deque>

struct Location{
    Location(int row, int col){
        row_ = row;
        col_ = col;
    }
    int row_;
    int col_;
};

class Minesweeper{
    public:
    Minesweeper(int diffculty);
    ~Minesweeper();

    //insertBomb
    bool insertBomb(Location firstDig);

    //insert number of bomb indicator in 9x9 area around
    void insertNumBombIndicator();

    //return false when user digs visited location
    //return false when user digs flaged location
    //set gameStatus_ to -1 when dig at bomb
    //use BFS to modify isVisited_ mask 
    bool applyDig(Location digOperation);

    //apply flag
    //remove flag when user enters the flaged location
    //return false when user flags visited location
    bool applyFlag(Location FlagOperation);

    //check game status, if all flags have been placed to correct location, then set gameStatus_ to 1 (win), and return true
    //if user has visited all location expect the bomb, then set gameStatus_ to 1 (win), and return true
    //else return flase
    bool checkGameStatus();

    //print game with isVisited_ musk and isFlaged musk
    void printGame();

    //print game without isVisited_ musk and isFlaged musk
    void printAll();
    

    int returnRowSize() const{
        return rowSize_;
    }
    
    int returnColSize() const{
        return colSize_;
    }

    int returnBombNum() const{
        return bombNum_;
    }

    int returnFlagNum() const{
        return flagNum_;
    }

    int returnhasntVisited__() const{
        return hasntVisited_;
    }

    int returnGameStatus() const{
        return gameStatus_;
    }

    int returnDiffculty() const{
        return difficulty_;
    }

    private:

    //initialize minesweeperNumArr, 0 as default value, -1 as bomb, -2 as bomb that user digs
    //integer 0 to 8 indicate how many bombs are around current location 
    int ** minesweeperNumArr_;

    bool** isVisited_;
    bool** isFlaged_;
    int rowSize_;
    int colSize_;
    int bombNum_;
    int flagNum_;
    int hasntVisited_;

    //0 = easy, 1 = medium, 2 = hard, 3 = challenge
    int difficulty_;

    //0 as in progress (default value), -1 as lose, 1 as win
    int gameStatus_;
};