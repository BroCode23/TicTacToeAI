#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<string>

class Tuple {
public:
	Tuple();
	Tuple(int y, int x);
	Tuple& operator=(Tuple b);
	bool operator<(Tuple b);
	bool operator>(Tuple b);
	int get_x();
	void set_x(int x);
	int get_y();
	void set_y(int y);
	int get_score();
	void set_score(int score);
private:
	int y;
	int x;
	int score;
};

int play(std::string player_1_name, std::string player_2_name);

void repeated_play(std::string player_1_name, std::string player_2_name, int plays);

void fill_new_board(int old_board[3][3], int new_board[3][3]);

void print_usage_info(std::string program_name);

void new_board(int board[3][3]);

void render(const int board[3][3]);

Tuple get_move();

void make_move(int board[3][3], Tuple move_coords, int player);

int game_is_won(const int board[3][3]);

bool is_board_full(const int board[3][3]);

bool is_valid_move(int board[3][3], Tuple coord);

void draw_x_or_o(int board_y, int board_x, const int board[3][3]);

Tuple random_ai(int board[3][3], int player);

Tuple winning_moves_ai(int board[3][3], int player);

int minimax_score(int board[3][3], int player);

Tuple minimax_ai(int board[3][3], int player);

#endif //FUNCTIONS_H