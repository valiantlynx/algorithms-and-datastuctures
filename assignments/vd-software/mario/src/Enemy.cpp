#include <array>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "headers/Animation.hpp"
#include "headers/Global.hpp"
#include "headers/MapManager.hpp"
#include "headers/Mushroom.hpp"
#include "headers/Mario.hpp"
#include "headers/Enemy.hpp"
#include "headers/SoundManager.hpp"

Enemy::Enemy(const float i_x, const float i_y) :
	dead(0),
	horizontal_speed(0),
	vertical_speed(0),
	x(i_x),
	y(i_y)
{
	
}

bool Enemy::get_dead(const bool i_deletion) const
{
	return dead;
}

void Enemy::die(const unsigned char i_death_type)
{
	dead = 1;
	
	// Play stomp sound if death type is stomping (usually 1 for stomping based on other programmers code)
	if (i_death_type == 1)
	{
		SoundManager::getInstance().playSound("stomp");
	}
}

sf::FloatRect Enemy::get_hit_box() const
{
	return sf::FloatRect(x, y, CELL_SIZE, CELL_SIZE);
}