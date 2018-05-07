// 1D Adventure : 1 dimension game with simple console output.

#include "stdafx.h"
#include <list>

#define ESCAPE_KEY 27
#define A_KEY 'a'
#define D_KEY 'd'
#define Q_KEY 'q'
#define E_KEY 'e'

struct bullet {
	int m_bullet_pos;
	int m_bullet_dir;

	bullet(int pos, int dir) {
		this->m_bullet_pos = pos;
		this->m_bullet_dir = dir;
	}
};

struct enemy {
	int m_enemy_pos;
	int m_enemy_dir;

	enemy(int pos, int dir) {
		this->m_enemy_pos = pos;
		this->m_enemy_dir = dir;
	}
};

struct point {
	int m_point_pos;
	int m_point_dir;

	point(int pos, int dir) {
		this->m_point_pos = pos;
		this->m_point_dir = dir;
	}
};

void generateEnemy(std::list<enemy> *e_list);
void generatePoint(std::list<point> *p_list);

void moveElements(std::list<bullet> *b_list, std::list<point> *p_list, std::list<enemy> *e_list,
	const int max_b, const int max_p, const int max_e, int &s);

void checkBulletWithEnemyCollision(
	std::list<bullet> *b_list, 
	const int max_b, std::list<enemy> *e_list,
	const int max_e, int &s
);
void checkBulletWithPointCollision(
	std::list<bullet> *b_list, 
	const int max_b, 
	std::list<point> *p_list,
	const int max_p
);

void eraseBulletsOutOfLimits (std::list<bullet> *b_list, const int max_bullet_elems );
void erasePointsOutOfLimits  (std::list<point> *p_list,  const int max_point_elems  );
void eraseEnemysOutOfLimits  (std::list<enemy> *e_list,  const int max_enemy_elems  );

int main() {
	// Declare keyboard key
	char key = 0;

	// Declare pj position in x
	int pos_x = 40;

	// If enemy catch you, the game is over
	bool game_over = false;

	// Point position
	std::list<bullet>bullet_list;
	const int max_bullets = 10;

	// Enemy position
	std::list<enemy>enemy_list;
	const int max_enemys = 6;

	// Point position
	std::list<point>point_list;
	const int max_points = 4;

	// Score and lives
	int score = 0;
	int lives = 3;

	const int time_to_respawn_point = 50;
	int count_point = 0;

	const int time_to_respawn_enemy = 20;
	int count_enemy = 0;

	printf("\n\n\n\n\n\n\n\n");

	// Principal loop
	while ((key != ESCAPE_KEY) && !game_over) {
		const int enemy_list_size = enemy_list.size();
		// Generate a new enemy
		if ((enemy_list_size < max_enemys) && (count_enemy >= time_to_respawn_enemy)) {
			generateEnemy(&enemy_list);

			count_enemy = 0;
		}

		const int point_list_size = point_list.size();
		// Generate a new point
		if ((point_list_size < max_points) && (count_point >= time_to_respawn_point)) {
			generatePoint(&point_list);

			count_point = 0;
		}

		if (_kbhit()) {
			// Get the pressed key
			key = _getch();

			switch (key) {
				// Move pj to the left
			case A_KEY:
				if (pos_x > 0) {
					pos_x--;
				}
				break;
				// Move pj to the right
			case D_KEY:
				if (pos_x < 100) {
					pos_x++;
				}
				break;
				// Shot to the left
			case Q_KEY:
				if (bullet_list.size() < max_bullets) {
					bullet newBullet(pos_x - 1, 0);
					bullet_list.push_back(newBullet);
				}
				break;
				// Shot to the right
			case E_KEY:
				if (bullet_list.size() < max_bullets) {
					bullet newBullet(pos_x + 1, 1);
					bullet_list.push_back(newBullet);
				}
				break;
			}
		}

		printf("POINTS -> %d ", score);
		// Paint the 'map'
		for (int i = 0; i < 80; i++) {
			bool painted = false;


			auto it = enemy_list.begin();
			for (int j = 0; j < max_enemys && it != enemy_list.end(); j++) {
				if (it->m_enemy_pos == pos_x) {
					if (lives == 1) {
						game_over = true;
					}
					else {
						it = enemy_list.erase(it);
						lives--;
					}
				}
			}

			auto it2 = point_list.begin();
			for (int j = 0; j < max_points && it2 != point_list.end(); j++) {
				if (it2->m_point_pos == pos_x) {
					score = score + 10;
					it2 = point_list.erase(it2);
				}
			}

			if ((i == pos_x) && !painted) {
				printf("Y");
				painted = true;
			}

			if (!painted) {
				for (auto iterator = bullet_list.begin(); iterator != bullet_list.end(); iterator++) {
					if (iterator->m_bullet_pos == i) {
						if (iterator->m_bullet_dir == 0) {
							printf("<");
						}
						else {
							printf(">");
						}
						painted = true;

						break;
					}
				}
			}

			if (!painted) {
				for (auto iterator = enemy_list.begin(); iterator != enemy_list.end(); iterator++) {
					if (iterator->m_enemy_pos == i) {
						printf("@");
						painted = true;

						break;
					}
				}
			}

			if (!painted) {
				for (auto iterator = point_list.begin(); iterator != point_list.end(); iterator++) {
					if (iterator->m_point_pos == i) {
						printf("O");
						painted = true;

						break;
					}
				}
			}

			if (!painted) {
				printf("-");
			}
		}
		printf(" LIVES -> %d", lives);
		printf("\r");

		// Move elements and check collisions
		moveElements(&bullet_list, &point_list, &enemy_list, max_bullets, max_points, max_enemys, score);

		Sleep(50);

		// Increase counters to points and enemys respawn
		count_enemy++;
		count_point++;
	}

	return 0;
}

// This function generates an enemy in enemy list
void generateEnemy(std::list<enemy> *e_list) {
	int enemy_path = (int)(rand() / (double)(RAND_MAX + 1) * (2));
	int enemy_pos = -1;
	int enemy_dir = 0;

	if (enemy_path == 0) {
		enemy_pos = 0;
		enemy_dir = 0;
	}
	else {
		enemy_pos = 99;
		enemy_dir = 1;
	}

	enemy newEnemy(enemy_pos, enemy_dir);

	e_list->push_back(newEnemy);
}

// This function generates an point in point list
void generatePoint(std::list<point> *p_list) {
	int point_path = (int)(rand() / (double)(RAND_MAX + 1) * (2));
	int point_pos = -1;
	int point_dir = 0;

	if (point_path == 0) {
		point_pos = 0;
		point_dir = 0;
	}
	else {
		point_pos = 99;
		point_dir = 1;
	}

	point newPoint(point_pos, point_dir);

	p_list->push_back(newPoint);
}

// Function to move elements and checks collisions
void moveElements(std::list<bullet> *b_list, std::list<point> *p_list, std::list<enemy> *e_list,
	const int max_b, const int max_p, const int max_e, int &s) {
	// Move bullets to correct path
	for (auto iterator = b_list->begin(); iterator != b_list->end(); iterator++) {
		if (iterator->m_bullet_dir == 0) {
			iterator->m_bullet_pos--;
		}
		else {
			iterator->m_bullet_pos++;
		}
	}

	// Checks if a bullet kills the enemy
	checkBulletWithEnemyCollision(b_list, max_b, e_list, max_e, s);
	// Checks if a bullet kills the point
	checkBulletWithPointCollision(b_list, max_b, p_list, max_p);

	// Move point to correct path
	for (auto iterator = p_list->begin(); iterator != p_list->end(); iterator++) {
		if (iterator->m_point_dir == 0) {
			iterator->m_point_pos++;
		}
		else {
			iterator->m_point_pos--;
		}
	}

	// Checks if a bullet kills the point
	checkBulletWithPointCollision(b_list, max_b, p_list, max_p);

	// Move enemy to correct path
	for (auto iterator = e_list->begin(); iterator != e_list->end(); iterator++) {
		if (iterator->m_enemy_dir == 0) {
			iterator->m_enemy_pos++;
		}
		else {
			iterator->m_enemy_pos--;
		}
	}

	// Checks if a bullet kills the enemy
	checkBulletWithEnemyCollision(b_list, max_b, e_list, max_e, s);

	// Erase elements out of limits
	eraseBulletsOutOfLimits (b_list, max_b);
	eraseEnemysOutOfLimits  (e_list, max_e);
	erasePointsOutOfLimits  (p_list, max_p);
}

// This function checks if any bullet kills any enemy and erase both
void checkBulletWithEnemyCollision(std::list<bullet> *b_list, const int max_b, std::list<enemy> *e_list, const int max_e, int &s) {
	auto it = b_list->begin();
	for (int i = 0; i < max_b && it != b_list->end(); i++) {
		auto it2 = e_list->begin();
		bool enemy_dead = false;
		for (int j = 0; j < max_e && it2 != e_list->end(); j++) {
			if (it->m_bullet_pos == it2->m_enemy_pos) {
				s = s + 5;

				enemy_dead = true;
				it2 = e_list->erase(it2);
			}
		}
		if (enemy_dead) {
			it = b_list->erase(it);
		}
	}
}

// This function checks if any bullet kills any point and erase both
void checkBulletWithPointCollision(std::list<bullet> *b_list, const int max_b, std::list<point> *p_list, const int max_p) {
	auto it = b_list->begin();
	for (int i = 0; i < max_b && it != b_list->end(); i++) {
		auto it2 = p_list->begin();
		bool point_dead = false;
		for (int j = 0; j < max_p && it2 != p_list->end(); j++) {
			if (it->m_bullet_pos == it2->m_point_pos) {
				point_dead = true;
				it2 = p_list->erase(it2);
			}
		}
		if (point_dead) {
			it = b_list->erase(it);
		}
	}
}

// This function erase the bullets out of limits
void eraseBulletsOutOfLimits(std::list<bullet> *b_list, const int max_b) {
	auto it = b_list->begin();
	for (int i = 0; i < max_b && it != b_list->end(); i++) {
		if (it->m_bullet_pos > 80 || it->m_bullet_pos < 0) {
			it = b_list->erase(it);
		}
	}
}

// This function erase the points out of limits
void erasePointsOutOfLimits(std::list<point> *p_list, const int max_p) {
	auto it = p_list->begin();
	for (int i = 0; i < max_p && it != p_list->end(); i++) {
		if (it->m_point_pos > 80 || it->m_point_pos < 0) {
			it = p_list->erase(it);
		}
	}
}

// This function erase the enemys out of limits
void eraseEnemysOutOfLimits(std::list<enemy> *e_list, const int max_e) {
	auto it = e_list->begin();
	for (int i = 0; i < max_e && it != e_list->end(); i++) {
		if (it->m_enemy_pos > 80 || it->m_enemy_pos < 0) {
			it = e_list->erase(it);
		}
	}
}