#include <iostream>
#include <cmath>

const int rows = 9;
const int cols = 9;


void printPuzzle(int puzzle[rows][cols]){
    for(int i = 0; i<9; i++){
        for(int n = 0; n<9; n++){
            std::cout<< puzzle[i][n] << " ";
        }
        std::cout << std::endl;
    }
}


bool checkRow(const int xPos, const int yPos, int puzzle[rows][cols]){
    // here we are writing a loop to check each spot in each row. and we compare the puzzle at the start place to each of these spots.
    // and if its equal we return false? and if it checks the whole row then we know the number passes this check.
    // we need to check each spot but itself. for example if we are in (0,0) we need it to check (0,1-9) but not (0,0)
    for(int i = 0; i<9; i++){
        if(i != yPos && puzzle[xPos][i] == puzzle[xPos][yPos]){
            return false;
        }
    }
    return true;
};

bool checkCol(const int xPos, const int yPos, int puzzle[rows][cols]){
    for(int i = 0; i<9; i++){
        if(i != xPos && puzzle[i][yPos] == puzzle[xPos][yPos]){
            return false;
        }
    }
    return true;
};

bool checkSector(int xPos, int yPos, int puzzle[rows][cols]){
    //check rows then cols and sector if it passes all then add and move to next space.
    // so we are passed 1-9 or 0-8 i guess, and we need 0-2 yeild 1 3-5 yeild 2 and 6-8 yeild 3...
    int newX = ceil(xPos/3) * 3;
    int newY = ceil(yPos/3) * 3;

    for(int i = 0; i<3; i++){
        for(int n = 0; n<3; n++){
            if((newX + i != xPos || newY + n != yPos) && puzzle[xPos][yPos] == puzzle[newX + i][newY + n]){
                return false;
            }
        }
    }
    return true;
}

bool solve(int puzzle[rows][cols]){
    //the way i have it built we need to write the possiblity into the spot before we run the 3 checks.
    // so we put in 1 to start run all 3 checks if any come back false we move up to 2 until all three are true
    // if we get all the way to 9 and none are true we need to recursivly go back up the pile to the previous one and try again.
    
    
    
    // so we are  not ever hitting the next iteration of the first for loop...
    for(int i=0; i<9; i++){
        for(int n=0; n<9; n++){
            if(puzzle[i][n] == 0){
                for(int posib=1; posib<=9; posib++){
                    // we must start with inserting 1 then running checks if false bump it up to 2 etc
                    puzzle[i][n] = posib;
                    
                    if(checkRow(i, n, puzzle) && checkCol(i, n, puzzle) && checkSector(i, n, puzzle)){
                        if(solve(puzzle)){
                            //printPuzzle(puzzle);
                            return true;
                        }
                    }
                    
                    puzzle[i][n] = 0;
                    //run all our checks iteritvly but if any of them return false we want to go into the next itteration of our for loop...
                }
                return false;
            } 
        }
    }
    return true;
}

    int intakeArray[rows][cols] = {
        {0, 0, 6, 0, 5, 0, 0, 3, 0,},
        {0, 1, 0, 0, 0, 6, 0, 0, 0,},
        {7, 0, 0, 2, 8, 0, 1, 0, 0,},
        {0, 8, 0, 7, 0, 3, 0, 2, 0,},
        {9, 0, 0, 0, 0, 5, 3, 7, 0,},
        {0, 7, 4, 0, 0, 0, 0, 0, 0,},
        {0, 0, 0, 0, 4, 0, 6, 0, 0,},
        {5, 0, 1, 0, 0, 0, 9, 8, 4,},
        {0, 0, 9, 0, 0, 1, 2, 5, 0,}
    };


int main(){

    solve(intakeArray);

    printPuzzle(intakeArray);

    
    std::cout<< "hello world" << std::endl;
    return 0;
}
