/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-1\src\8queenF.cpp
 * @Date         : 2024-05-12 19:00:48
 * @author       : foreverferrysun
 * @LastEditTime : 2024-09-29 18:11:03
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
#include "../include/8queenF.h"
using namespace alg;

void Queen8::solve() {
    // 初始化棋盘，并将皇后数量置为0
    memset(board, '0', sizeof(board));
    cnt = 0;
    // 调用_solve函数解决八皇后问题
    _solve(0);
}
void Queen8::_solve(int row)
{ 
    // 遍历8行
    int i;
    for (i = 0; i < 8; i++)
    {
        board[row][i] = '1'; // 放置皇后
        if (check(row, i))
        {
            if (row == 7)
                print();
            else
                _solve(row + 1);
        }
        board[row][i] = '0'; // 回溯
    }
}


void Queen8::print()
{
    printf("chessboard: %d\n", ++cnt);
    int i, j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool Queen8::check(int row, int col)
{
    int i, j;

    // 检查同一列
    for (i = 0; i < row; i++){
        if (board[i][col] == '1'){
            return false;
        }
    }

    // 检查对角线
    i = row - 1, j = col - 1;
    while (i >= 0 && j >= 0){
        if (board[i][j] == '1'){
            return false;
        }
        i--;
        j--;
    }

    i = row - 1, j = col + 1;
    while (i >= 0 && j < 8){
        if (board[i][j] == '1'){
            return false;
        }
        i--;
        j++;
    }

    return true;
}

