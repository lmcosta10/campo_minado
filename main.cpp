#include <iostream>
#include <vector>

int main() {
	int board_len;
	std::cout << "Enter board length: ";
	std::cin >> board_len;
	
	int board[board_len*board_len];
	
	for (int i = 0; i < board_len*board_len; i++) {
		board[i] = rand() % 2;
		std::cout << board[i];
	}
		
	return 0;
}
