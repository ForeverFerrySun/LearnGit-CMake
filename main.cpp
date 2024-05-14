/*
 * @FilePath     : \LearnGit-CMake\main.cpp
 * @Date         : 2024-05-12 18:50:08
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-13 01:12:42
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
#include "8queenF.h"
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages