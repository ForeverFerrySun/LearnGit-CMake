#include "8queenF.h"
#include "base64F.h"
#include <string>
using namespace std;
void test_8queenF() {
    std::cout << "测试 8queenF:\n";
    std::cout << "Expected: 92\n";
    alg::Queen8 q;
	q.solve();
}


void test_base64F() {
    std::cout << "测试 base64F:\n";
    std::cout << "Expected: 18\n";
  	const char *s = "Matthew 7:24-27 Therefore everyone who hears these words of mine and puts them into practice is like a wise man who built his house on the rock. 25 The rain came down, the streams rose, and the winds blew and beat against that house; yet it did not fall, because it had its foundation on the rock. 26 But everyone who hears these words of mine and does not put them into practice is like a foolish man who built his house on sand. 27 The rain came down, the streams rose, and the winds blew and beat against that house, and it fell with a great crash.";
	cout << " INPUT: " << endl;
	cout << s << endl << endl;

	string base=alg::CBase64::encodeBase64((unsigned char *) s, strlen(s));
	cout << " encodeBase64: " << endl;
	cout << base << endl << endl;

	cout << " decodeBase64: " << endl;
	cout << alg::CBase64::decodeBase64(base) << endl;
}

int main() {
    test_8queenF();
    // test_avlF();
    test_base64F();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages