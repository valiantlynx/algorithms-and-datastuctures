#pragma once

#include "Animation.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
class Goomba : public Enemy
{
	//We'll use this to make sure that we check the collision with Mario only once when he collides with us.
	bool no_collision_dying;
	//The underground Goomba looks different than the regular Goomba.
	bool underground;

	unsigned short death_timer;

	sf::Sprite sprite;

	sf::Texture texture;

	Animation walk_animation;
public:
	Goomba(const bool i_underground, const float i_x, const float i_y);

	bool get_dead(const bool i_deletion) const;

	void die(const unsigned char i_death_type);
	void draw(const unsigned i_view_x, sf::RenderWindow& i_window);
	void update(const unsigned i_view_x, const std::vector<std::shared_ptr<Enemy>>& i_enemies, const MapManager& i_map_manager, Mario& i_mario);
};
