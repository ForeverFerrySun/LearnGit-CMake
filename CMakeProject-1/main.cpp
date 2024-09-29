/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-1\main.cpp
 * @Date         : 2024-05-12 18:50:08
 * @author       : foreverferrysun
 * @LastEditTime : 2024-09-29 18:13:11
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
#include "./include/8queenF.h"
#include <iostream>
void test_8queenF() {
    std::cout << "测试 8queenF:\n";
    std::cout << "Expected: 92\n";
    alg::Queen8 q;
	q.solve();
}

int main() {
    test_8queenF();
    return 0;
}