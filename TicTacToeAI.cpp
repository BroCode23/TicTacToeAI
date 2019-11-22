// TicTacToeAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int main(){
	srand(time(NULL)); // use this to improve random

	play("human", "minimax_ai");
}
