// pch.cpp: header file

#include "pch.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;

Tuple::Tuple() : y(0), x(0), score(0) {}

Tuple::Tuple(int y, int x) : y(y), x(x), score(0) {}

Tuple& Tuple::operator=(Tuple b) {
	this->y = b.y;
	this->x = b.x;
	this->score = b.score;
	return *this;
}

bool Tuple::operator<(Tuple b) {
	return this->score < b.score;
}

bool Tuple::operator>(Tuple b) {
	return this->score > b.score;
}

int play(string player_1_name, string player_2_name) {
	// function to simulate a game of tic tac toe using human players or AI
	int board[3][3];
	new_board(board); //fills the board with 0's
	int game_won = 0; //int to check if the game was won
	bool human_is_playing = false;

	cout << "TIC TAC TOE" << endl << endl;
	while (!game_won) {
		Tuple move_coords;
		while (true) {
			//can plug in an ai here
			if (player_1_name == "random_ai") {  //ai that makes completely random moves
				move_coords = random_ai(board, 1);
			}
			else if (player_1_name == "winning_moves_ai") { //ai that can make winning moves if presented
				move_coords = winning_moves_ai(board, 1);
			}
			else if (player_1_name == "minimax_ai") { //ai that makes best possible moves
				move_coords = minimax_ai(board, 1);
			}
			else { //human player
				render(board);
				human_is_playing = true;
				move_coords = get_move();
			}

			//checks if the move is valid, if true it exits the loop
			if (is_valid_move(board, move_coords)) {
				break;
			}
			else {
				cout << "Bad inputs, try again.\n\n";
			}
		}
		make_move(board, move_coords, 1); //places the valid move on the board

		game_won = game_is_won(board); //checks if game was won after each turn
		if (game_won) {
			break;
		}
		if (is_board_full(board)) { //only needs to check if board is full after player 1 because of 9 slots on board
			return 0;
		}

		while (true) {
			if (player_2_name == "random_ai") {   //can put an ai in based on arguments
				move_coords = random_ai(board, 2);
			}
			else if (player_2_name == "winning_moves_ai") {
				move_coords = winning_moves_ai(board, 2);
			}
			else if (player_2_name == "minimax_ai") {
				move_coords = minimax_ai(board, 2);
			}
			else {
				render(board);
				human_is_playing = true;
				move_coords = get_move();
			}

			if (is_valid_move(board, move_coords)) { //checks if move is valid
				break;
			}
			else {
				cout << "Bad inputs, try again.\n\n";
			}
		}
		make_move(board, move_coords, 2);
		game_won = game_is_won(board);
	}
	if (human_is_playing) { //prints out final state of board
		render(board);
	}
	return game_won;
}

void repeated_play(string player_1_name, string player_2_name, int plays) {
	// function to simulate numerous games using different AI's
	int player_1_wins = 0;
	int player_2_wins = 0;
	int ties = 0;
	int outcome = 0;

	for (int iterations = 0; iterations < plays; iterations++) {
		outcome = play(player_1_name, player_2_name);
		if (outcome == 1) {
			player_1_wins++;
		}
		else if (outcome == 2) {
			player_2_wins++;
		}
		else {
			ties++;
		}
	}

	cout << player_1_name << ": " << player_1_wins << endl;
	cout << player_2_name << ": " << player_2_wins << endl;
	cout << "Ties: " << ties << endl;
	return;
}

void fill_new_board(int old_board[3][3], int new_board[3][3]) {
	// copies all of the moves from old_board onto new_board via deep copy
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			new_board[y][x] = old_board[y][x];
		}
	}
	return;
}

void print_usage_info(string program_name) { //prints correct usage if an error occurs
	cout << "Usage: " << program_name << " bot1 bot2" << endl;
	return;
}

void new_board(int board[3][3]) { //fills a board with all 0's
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			board[y][x] = 0;
		}
	}
	return;
}

void render(const int board[3][3]) { //prints out a board
	cout << "  0 1 2 " << endl;
	cout << "  ----- " << endl;
	for (int y_print = 0; y_print < 3; y_print++) {
		cout << y_print;
		cout << "|";
		draw_x_or_o(y_print, 0, board);
		cout << " ";
		draw_x_or_o(y_print, 1, board);
		cout << " ";
		draw_x_or_o(y_print, 2, board);
		cout << "|" << endl;
	}
	cout << "  ----- " << endl;

	return;
}

Tuple get_move() {
	int x = 0; //ask for inputs
	int y = 0;
	cout << "input your X coordinate: ";
	cin >> x;
	cout << "input your Y coordinate: ";
	cin >> y;

	Tuple coords; //outputs a tuple with an x and y value
	coords.x = x;
	coords.y = y;
	return coords;
}

void make_move(int board[3][3], Tuple move_coords, int player){ //places an 1 or 0 in the spot for move coords for each player
	if (player == 1) {
		board[move_coords.y][move_coords.x] = 1;
	}
	else {
		board[move_coords.y][move_coords.x] = 2;
	}
	return;
}

int game_is_won(const int board[3][3]) {
	//check columns
	for (int y = 0; y < 3; y++) {
		if (board[y][0] == board[y][1] && board[y][1] == board[y][2] && board[y][0] != 0) {
			return board[y][0];
		}
	}
	//check rows
	for (int x = 0; x < 3; x++) {
		if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[0][x] != 0) {
			return board[0][x];
		}
	}
	//check diagonals
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
		return board[0][0];
	}
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != 0) {
		return board[2][0];
	}
	return 0;
}

bool is_board_full(const int board[3][3]) { //checks if there was a tie
	bool tie = true;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == 0) { //if there is any open spot on the board
				tie = false;
			}
		}
	}
	return tie;
}

bool is_valid_move(int board[3][3], Tuple coord) {
	if (coord.x >= 0 && coord.x <= 2) { //must be within x range
		if (coord.y >= 0 && coord.y <= 2) { //within y range
			if (board[coord.y][coord.x] == 0) { //must be an open spot
				return true;
			}
		}
	}
	return false;
}

void draw_x_or_o(int board_y, int board_x, const int board[3][3]) { //chooses whether to print an X or O
	if (board[board_y][board_x] == 1) {
		cout << "X";
	}
	else if (board[board_y][board_x] == 2) {
		cout << "O";
	}
	else {
		cout << " ";
	}
	return;
}

Tuple random_ai(int board[3][3], int player) { //player is 1 or 2
	Tuple possible_moves[9];
	int number_of_moves = 0;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == 0) {
				possible_moves[number_of_moves].y = y;
				possible_moves[number_of_moves].x = x;
				number_of_moves++;
			}
		}
	}
	int random_move = rand() % number_of_moves;

	return possible_moves[random_move];
}

Tuple winning_moves_ai(int board[3][3], int player) {
	Tuple winning_move;
	//find a winning move if it exists
	for (int x = 0; x < 3; x++) {
		if ((board[0][x] == player && board[1][x] == player) || (board[0][x] == player && board[2][x] == player) || (board[1][x] == player && board[2][x] == player)) { //checks all columns
			if (board[0][x] == 0) {
				winning_move.y = 0;
				winning_move.x = x;
				return winning_move;
			}
			else if (board[1][x] == 0){
				winning_move.y = 1;
				winning_move.x = x;
				return winning_move;
			}
			else if (board[2][x] == 0) {
				winning_move.y = 2;
				winning_move.x = x;
				return winning_move;
			}
		}
	}
	for (int y = 0; y < 3; y++) {
		if ((board[y][0] == player && board[y][1] == player) || (board[y][0] == player && board[y][2] == player) || (board[y][1] == player && board[y][2] == player)) { //checks all rows
			if (board[y][0] == 0) {
				winning_move.y = y;
				winning_move.x = 0;
				return winning_move;
			}
			else if (board[y][1] == 0) {
				winning_move.y = y;
				winning_move.x = 1;
				return winning_move;
			}
			else if (board[y][2] == 0) {
				winning_move.y = y;
				winning_move.x = 2;
				return winning_move;
			}
		}
	}
	if ((board[0][0] == player && board[1][1] == player) || (board[0][0] == player && board[2][2] == player) || (board[1][1] == player && board[2][2] == player)) { //checks first diagonal
		if (board[0][0] == 0) {
			winning_move.y = 0;
			winning_move.x = 0;
			return winning_move;
		}
		else if (board[1][1] == 0) {
			winning_move.y = 1;
			winning_move.x = 1;
			return winning_move;
		}
		else if (board[2][2] == 0) {
			winning_move.y = 2;
			winning_move.x = 2;
			return winning_move;
		}
	}
	if ((board[0][2] == player && board[1][1] == player) || (board[0][2] == player && board[2][0] == player) || (board[1][1] == player && board[2][0] == player)) { //checks second diagonal
		if (board[0][2] == 0) {
			winning_move.y = 0;
			winning_move.x = 2;
			return winning_move;
		}
		else if (board[1][1] == 0) {
			winning_move.y = 1;
			winning_move.x = 1;
			return winning_move;
		}
		else if (board[2][0] == 0) {
			winning_move.y = 2;
			winning_move.x = 0;
			return winning_move;
		}
	}
	return random_ai(board, player); // else, find a random move
}

int minimax_score(int board[3][3], int player) {
	int winner = 0;
	for (int y = 0; y < 3; y++) { //checks all the rows for a winning board
		if (board[y][0] == board[y][1] && board[y][1] == board[y][2] && board[y][0]) {
			winner = board[y][0];
			if (winner == 1) { //if X wins the score is +10
				return 10;
			}
			else { //if O wins the score is -10
				return -10;
			}
		}
	}
	for (int x = 0; x < 3; x++) { //checks all columns for a winning board
		if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[0][x]) {
			winner = board[0][x];
			if (winner == 1) { //if X wins the score is +10
				return 10;
			}
			else { //if O wins the score is -10
				return -10;
			}
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0]) { // check first diagonal
		winner = board[0][0];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]  && board[2][0]) { // always check the second diagonal
		winner = board[0][2];
	}
	if (winner == 1) { //if X wins the score is +10
		return 10;
	}
	if (winner == 2) { //if O wins the score is -10
		return -10;
	}
	Tuple possible_moves[9];
	int number_of_moves = 0;

	bool tie = true;
	for (int y = 0; y < 3; y++) { //checks for a tie
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == 0) { //if there is any open spot on the board
				tie = false;

				possible_moves[number_of_moves].y = y; //assigns the spot as a possible move
				possible_moves[number_of_moves].x = x;
				number_of_moves++;
			}
		}
	}
	if (tie) { //if it results in a tie the score is 0
		return 0;
	}

	for (int i = 0; i < number_of_moves; i++) { //iterate through all the possible moves
		int new_board[3][3];
		fill_new_board(board, new_board); //creates a new board and makes the possible move
		make_move(new_board, possible_moves[i], player);
		if (player == 1) {
			possible_moves[i].score = minimax_score(new_board, 2); //changes players and the process repeats
			if (possible_moves[i].score == 10) { // checks early if the score is the best
				return 10;
			}
		}
		else {
			possible_moves[i].score = minimax_score(new_board, 1);
			if (possible_moves[i].score == -10) { // checks early
				return -10;
			}
		}
	}

	int best_score = 0;
	for (int i = 0; i < number_of_moves; i++) {
		if (i == 0) { //ensures a return value
			best_score = possible_moves[i].score;
		}
		if (player == 1) { //returns highest value if player 1
			if (possible_moves[i].score > best_score) {
				best_score = possible_moves[i].score;
			}
		}
		else { //returns lowest value if player 2
			if (possible_moves[i].score < best_score) {
				best_score = possible_moves[i].score;
			}
		}
	}
	return best_score;
}

Tuple minimax_ai(int board[3][3], int player) {
	Tuple possible_moves[9];
	int number_of_moves = 0;

	for (int y = 0; y < 3; y++) { // iterates through all possible moves
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == 0) { //fill array of possible moves
				possible_moves[number_of_moves].y = y;
				possible_moves[number_of_moves].x = x;

				int new_board[3][3];
				fill_new_board(board, new_board);
				make_move(new_board, possible_moves[number_of_moves], player);
				if (player == 1) { 
					possible_moves[number_of_moves].score = minimax_score(new_board, 2);
					if (possible_moves[number_of_moves].score == 10) {
						return possible_moves[number_of_moves];
					}
				}
				else {
					possible_moves[number_of_moves].score = minimax_score(new_board, 1);
					if (possible_moves[number_of_moves].score == -10) {
						return possible_moves[number_of_moves];
					}
				}
				number_of_moves++;
			}
		}
	}

	Tuple best_tuple;
	for (int i = 0; i < number_of_moves; i++) {
		if (i == 0) {
			best_tuple = possible_moves[i];
		}
		if (player == 1 && possible_moves[i] > best_tuple) {
			best_tuple = possible_moves[i];
		}
		if (player == 2 && possible_moves[i] < best_tuple) {
			best_tuple = possible_moves[i];
		}
	}
	return best_tuple;
}

//test code
/*cout << "Here are all the possible moves:" << endl;
for (int i = 0; i < number_of_moves; i++) {
	cout << "X: " << possible_moves[i].x << endl;
	cout << "Y: " << possible_moves[i].y << endl;
	cout << "Score: " << possible_moves[i].score << endl;
	cout << endl << endl;
}*/
