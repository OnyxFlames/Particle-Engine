#include "Application.hpp"

#include <iostream>


Application::Application()
{
}

Application::Application(unsigned width, unsigned height, std::string title, bool fullscreen)
{

	fullscreen == true ? window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen) : window.create(sf::VideoMode(width, height), title);
	//window.setFramerateLimit(60);
	font.loadFromFile("../resources/consola.ttf");
	update_data.setFont(font);
	update_data.setFillColor(sf::Color::Red);
	update_data.setPosition({ 5, 0 });
	update_data.setScale(0.75f, 0.75f);
	update_data.setString("FPS: 0\n\nPress [SPACE] to spawn particles");

	particle_count.setFont(font);
	particle_count.setFillColor(sf::Color::Red);
	particle_count.setPosition({ 5, 25 });
	particle_count.setScale(0.75f, 0.75f);

	srand((unsigned)time(0));
}

Application::~Application()
{
	for (auto &p : particles)
	{
		delete p;
	}
}

void Application::input()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::Space:
				generate_particles(5000);
				break;
			}
			break;
		}
	}
}
void Application::update(sf::Time delta)
{
	static unsigned fps = 0;
	static sf::Time counter = sf::seconds(0);
	
	counter += delta;

	if (counter >= sf::seconds(1))
	{
		update_data.setString("FPS: " + std::to_string(fps));
		counter = sf::seconds(0);
		fps = 0;
	}
	else
		fps++;

	particle_count.setString("Count: " + std::to_string(particles.size()));

	const float degrade = 0.005f;
	sf::Image image;
	image.create(WIDTH, HEIGHT, sf::Color(0,0,0,0));
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->vel.x > 0)
			particles[i]->vel.x -= degrade * delta.asMicroseconds();
		else if (particles[i]->vel.x < 0)
			particles[i]->vel.x += degrade * delta.asMicroseconds();

		if (particles[i]->vel.y > 0)
			particles[i]->vel.y -= degrade * delta.asMicroseconds();
		else if (particles[i]->vel.y < 0)
			particles[i]->vel.y += degrade * delta.asMicroseconds();

		particles[i]->pos.x += particles[i]->vel.x;
		particles[i]->pos.y += particles[i]->vel.y;

		if (particles[i]->pos.x > image.getSize().x || particles[i]->pos.x  < 0)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
			continue;
		}

		if (particles[i]->pos.y > image.getSize().y || particles[i]->pos.y < 0)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
			continue;
		}
		if (particles[i]->vel.x <= 1.f && particles[i]->vel.y <= 1.f)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
			continue;
		}

		image.setPixel((int)particles[i]->pos.x, (int)particles[i]->pos.y, particles[i]->color);
	}
	particle_texture.create(image.getSize().x, image.getSize().y);
	particle_texture.update(image);
	particle.setTexture(particle_texture);
}
void Application::render()
{
	window.clear();
	window.draw(update_data);
	window.draw(particle_count);
	window.draw(particle);
	window.display();
}
void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		input();
		update(clock.restart());
		render();
	}
}