#include "Application.hpp"

int main()
{
	Application app(WIDTH, HEIGHT, "Particle Engine", false);

	app.generate_particles(5000);

	app.run();

	return 0;
}