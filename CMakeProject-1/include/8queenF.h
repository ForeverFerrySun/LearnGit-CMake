/*******************************************************************************
 * 8queenF.h
 *
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 8-Queue 
 * 八皇后问题
 ******************************************************************************/

#ifndef ALGO_8QUEENF_H__
#define ALGO_8QUEENF_H__

#include <stdio.h>
#include <string.h>

namespace alg {
	class Queen8 {
		private:
			char board[8][8];
			int cnt;
		public:
			void solve();
		private:
			void _solve(int row);

			void print();

			bool check(int row, int col);
	};
}

#endif //ALGO_8QUEEN_H__
