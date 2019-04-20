#pragma once

bool game_is_finished = false;
int board_size = 10;

enum class console_color_t : int {
	black,
	dark_blue,
	dark_green,
	dark_cyan,
	dark_red,
	dark_pink,
	dark_yellow,
	light_grey,
	dark_grey,
	blue,
	green,
	cyan,
	red,
	pink,
	yellow,
	white
};

void set_text_colour(console_color_t color) {
	SetConsoleTextAttribute(GetStdHandle(-11), *(uint16_t*)&color);
}

enum {
	left,
	up,
	right,
	down
};

struct direction_t {
	int x, y;
	direction_t(int x, int y) : x(x), y(y) { }
};

struct position_t {
	int x, y;

	bool operator ==( position_t to_check ) {
		if (this->x == to_check.x && this->y == to_check.y)
			return true;
		return false;
	}
	
	position_t(int x, int y) : x(x), y(y) {
		//if (x >= 5)
		//	this->x = 0;
		//if (y >= 5)
		//	this->y = 0;
		//if (x < 0)
		//	this->x = 4;
		//if (y < 0)
		//	this->y = 4;
	}

	position_t(int x, int y, int direction) {
		this->x = x;
		this->y = y;

		if (direction == left)
			this->x--;
		else if (direction == right)
			this->x++;
		else if (direction == up)
			this->y--;
		else if(direction == down)
			this->y++;

		//didnt use && because it would be too annoying to switch if later if I want wrap.
		if (this->x >= board_size)
			game_is_finished = true; //this->x = 0;
		if (this->y >= board_size)
			game_is_finished = true; //this->y = 0;
		if (this->x < 0)
			game_is_finished = true; //this->x = 4;
		if (this->y < 0)
			game_is_finished = true; //this->y = 4;
	}
};