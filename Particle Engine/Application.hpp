#pragma once

#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#define WIDTH 1280U
#define HEIGHT 720U


struct Particle
{
	Particle(sf::Vector2f _pos, sf::Vector2f _vel, sf::Color _color)
		: pos(_pos), vel(_vel), color(_color)
	{ }
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Color color;
};

class Application
{
private:
	sf::RenderWindow window;

	std::vector<sf::RectangleShape> rects;

	std::vector<Particle*> particles;
	sf::Texture particle_texture;
	sf::Sprite particle;

	void input();
	void update(sf::Time delta);
	void render();


	sf::Font font;
	sf::Text update_data;
	sf::Text particle_count;
public:
	Application();
	Application(unsigned width, unsigned height, std::string title, bool fullscreen = false);
	~Application();
	void generate_particles(unsigned amount)
	{
		for (unsigned i = 0; i < amount; i++)
		{
			// snow storm like effect
			particles.push_back(new Particle(
			{ (float)(rand() % (WIDTH)), (float)(rand() % (HEIGHT)) },
			{	(rand() % 2 == 1) ? (float)(rand() % 75) : (float)-(rand() % 75),
				(rand() % 2 == 1) ? (float)(rand() % 150) : (float)-(rand() % 150) },
			sf::Color::White));
		}
	}
	void run();

};

