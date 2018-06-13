#include <iostream>
#include <fstream>
#include <sstream>
//#include <stack>
using namespace std;

#define BOARD_SIZE 8

int board[BOARD_SIZE][BOARD_SIZE];

int count = 0;

void EmptyBoard()
{
    for(int i = 0; i < BOARD_SIZE; ++i)
        for(int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = 0;
}
bool isThreaten(int x, int y)
{
    for(int i = 0; i < BOARD_SIZE; ++i)
        if(board[i][y] == 1)
            return true;
    for(int i = 0; i < BOARD_SIZE; ++i)
        if(board[x][i] == 1)
            return true;
    for(int i = 0; i < BOARD_SIZE; ++i)
        if((x+i < BOARD_SIZE && y+i < BOARD_SIZE && board[x+i][y+i] == 1)
                || (x-i >= 0 && y-i >= 0 && board[x-i][y-i] == 1))
            return true;
    for(int i = 0; i < BOARD_SIZE; ++i)
        if((x+i < BOARD_SIZE && y-i >= 0 && board[x+i][y-i] == 1)
                || (x-i >= 0 && y+i < BOARD_SIZE && board[x-i][y+i] == 1))
            return true;
    return false;
}
void WriteSolution(int index)
{
    fstream file;

    //Each solution in different file
    string nameFile;
    nameFile.append("../8QueensProblem/Solution");
    nameFile.append(to_string(index));
    nameFile.append(".txt");
    file.open(nameFile, std::ofstream::out);

    //All solutions in 1 file
//    file.open("../8QueensProblem/Solutions.txt", std::ofstream::out | ios::app);
//    file.open("/home/default/projects/8QueensProblem/Solutions.txt", std::ofstream::out | ios::app);

    if(file.is_open())
    {
        for(int i = 0; i < BOARD_SIZE; ++i)
            for(int j = 0; j < BOARD_SIZE; ++j)
                if(board[i][j] == 1)
                    file << i << ' ' << j << endl;
        file << '*' << endl;
//        file << endl;

        file.close();
    }
}

void SearchQueen(int row = 0)
{
    if(row == 8)
    {
        ++count;
        WriteSolution(count);
        return;
    }

    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        if(!isThreaten(row, i))
        {
            board[row][i] = 1;
            SearchQueen(row+1);
            board[row][i] = 0;
        }
    }
}

void DrawBoard(const string& fileName)
{
    struct cell
    {
        int x, y;
        cell() {}
    };

    fstream file(fileName);
    cell queens[BOARD_SIZE];

    for(int i = 0; i < BOARD_SIZE; ++i)
        file >> queens[i].x >> queens[i].y;
    cout << endl;

    for(int q = 0; q < BOARD_SIZE; ++q)
        cout << queens[q].x << "-" << queens[q].y << endl;
    cout << endl;

    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            bool queen = false;
            for(int q = 0; q < BOARD_SIZE; ++q)
                if(queens[q].x == i && queens[q].y == j)
                    queen = true;
            if(queen)
                cout << "\033[1;31mQ ";
            else
                cout << "\033[1;33mx ";
        }
        cout << endl;
    }
}

void Test()
{
    board[3][5] = 1;


    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
            if(isThreaten(i,j))
                cout << '*' << ' ';
            else
                cout << '.' << ' ';
        cout << endl;
    }
}

int main()
{
    EmptyBoard();

    SearchQueen();

    cout << count << endl << endl;

    int index;
    cout << "Solution index: ";
    cin >> index;
    string nameFile;
    nameFile.append("../8QueensProblem/Solution");
    nameFile.append(to_string(index));
    nameFile.append(".txt");
    DrawBoard(nameFile);
    cout << "\033[0m" << endl;
}
