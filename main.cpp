#include <string>       
#include <iostream>  
#include <chrono>
#include <thread>
#include <windows.h>
#include "header.h"
#include <deque>
#include <random>
#include <ctime>
#include <cstdlib>

position_t get_new_apple();

std::deque<position_t> snake = { position_t( board_size/2, board_size/2) };
position_t apple = get_new_apple();
char direction = right;
int score = 0;
int random_counter = 0;
bool direction_set = false;

void get_input() {
	while (!game_is_finished) {
		for (int i = 0; i < board_size - 1; i++) {
			if (GetAsyncKeyState(0x25 + i) && std::abs(direction - i) != 2 && !direction_set) {
				direction = i;
				direction_set = true;
			}
		}
	}
}

static auto is_in_deque = [](const std::deque<position_t> &snake, position_t position, bool check_first = true) -> bool {
	for (int i = check_first ? 0 : 1; i < snake.size(); i++)
		if (position == snake[i])
			return true;
	return false;
};

position_t get_new_apple() {
	random_counter++;

	if (random_counter > 10000)
		game_is_finished = true;

	srand(time(0) + random_counter);
	auto x = rand() % board_size;
	srand(time(0) - random_counter);
	auto y = rand() % board_size;

	auto ret = position_t(x, y);
	if (is_in_deque(snake, ret))
		return get_new_apple();

	return ret;
}

int main()
{
	std::thread input(get_input);
	SetConsoleTitle("snake");
	while (!game_is_finished) {
		direction_set = false;
		snake.push_front(position_t(snake.front().x, snake.front().y, direction));

		if (snake.front() == apple) {
			score += 1;
			apple = get_new_apple();
		}
		else
			snake.pop_back();

		if (is_in_deque(snake, snake.front(), false)) {
			game_is_finished = true;
		}
			
		for (int row = 0; row < board_size; row++) {
			for (int col = 0; col < board_size; col++) {
				if (is_in_deque(snake, position_t(col, row), false)) {
					set_text_colour(console_color_t::dark_green);
					std::cout << "s ";
					set_text_colour(console_color_t::white);
				}
				else if (position_t(col, row) == snake.front()) {
					set_text_colour(console_color_t::green);
					std::cout << "s ";
					set_text_colour(console_color_t::white);
				}
				else if (col == apple.x && row == apple.y) {
					set_text_colour(console_color_t::red);
					std::cout << "a ";
					set_text_colour(console_color_t::white);
				}
				else 
					std::cout << "- ";
				if (col == board_size - 1)
					std::cout << std::endl;
			}
		}
		Sleep(300);
		std::system("cls");
		random_counter++;
	}

	input.join();
	std::system("cls");
	std::cout << "score : " << score << std::endl << "gg";
	Sleep(5000);
}