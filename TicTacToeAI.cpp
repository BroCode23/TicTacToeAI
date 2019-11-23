// TicTacToeAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
// driver file for functions

#include "functions.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int main(){
	srand(time(NULL)); // use this to improve random

	repeated_play("random_ai", "minimax_ai", 1000);
}
