#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
       #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ ,__LINE__)
       #define new DBG_NEW
   #endif
#endif

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Particle.hpp"

#include <vector>
int rollRandomPositiveInt(int maxValue_exclusive) {
	return abs(rand()) % maxValue_exclusive;
}

float rollRandomFloat01() {
	int32_t firstRes = abs(rand());
	//std::cout << firstRes << std::endl;
	const int32_t someDenominator = 0x7FFF;
	return float(firstRes % someDenominator) / someDenominator;
}

void PopulateParticles(std::vector<Particle>& particles,int maxParticles, int maxSpeed, int maxRandomSize, int maxLifetime, sf::Vector2f initPos) {
	const float PI = 3.141592654f;
	particles.reserve(maxParticles);
	for (int i = 0; i < maxParticles; i++) {

		float randomSpeed = rollRandomPositiveInt(maxSpeed + 1);
		//std::cout << "random speed: " << randomSpeed << std::endl;
		float randomAngleInDegrees = rollRandomPositiveInt(360);
		float randomAngleInRadius = randomAngleInDegrees * PI / 180.0f;
		auto randomDirection = sf::Vector2f(
			cos(randomAngleInRadius),
			sin(randomAngleInRadius)
		);

		float randomSize = rollRandomPositiveInt(maxRandomSize + 1);
		//std::cout << "random size: " << randomSize << std::endl;
		auto randVelocity = randomDirection * randomSpeed;

		float randomLifetime = rollRandomFloat01() * randomSpeed;
		//std::cout <<"random lifetime: "<< randomLifetime << std::endl;

		Particle::ParticleShapes shapeType = static_cast<Particle::ParticleShapes>(rand() % 2);
		//std::cout << shapeType << std::endl;
		// Create + add particle
		int randomColorR = rollRandomPositiveInt(255 + 1);
		int randomColorB = rollRandomPositiveInt(255 + 1);
		int randomColorG = rollRandomPositiveInt(255 + 1);
	    //std::cout << "random rgb: (" << randomColorA << "," << randomColorB << "," << randomColorC << ")" << std::endl;
		sf::Color randomColor = sf::Color(randomColorR, randomColorB, randomColorG);
		auto newParticle = Particle(randomSize, initPos, randVelocity, randomLifetime, shapeType, randomColor);
		//auto newParticle = Particle(randomSize, sf::Vector2f(100,100), randVelocity, randomLifetime);
		particles.push_back(newParticle);
		//Particle* test = new Particle;
		//std::cout << "particle size:" << particles.size() << std::endl;
	}
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |_CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	const int maxParticles = 64;
	
	std::vector<Particle> particles;

	const int maxRandomSize = 32;
	const int maxLifetime = 2;
	const int maxSpeed = 500;
	srand(420);

	//PopulateParticles(particles, maxParticles, maxSpeed, maxRandomSize, maxLifetime, sf::Vector2f(100, 100));
	std::cout << "particle size:" << particles.size() << std::endl;
	// src = source
	// dst = destination
	sf::Clock deltaSrc;
	bool shouldDraw = false;
	sf::Vector2f mousePos;
	while (window.isOpen())
	{

		sf::Time dt_time = deltaSrc.restart();
		float dt = dt_time.asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				shouldDraw = true;
				mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				PopulateParticles(particles, maxParticles, maxSpeed, maxRandomSize, maxLifetime, mousePos);
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				shouldDraw = false;
			}
		}
		//std::cout << shouldDraw << std::endl;
		// Update the world state
		for (int i = 0; i < particles.size(); i++) {
			particles[i].update(dt);
		}

		for (int i = particles.size() - 1; i >= 0; i--) {
			auto curPart = particles[i];
			if (curPart.isDead()) {
				particles.erase(particles.begin() + i);
			}

		}
		window.clear();

		for (int i = 0; i < particles.size(); i++) {

			window.draw(particles[i].getShape());
		}


		window.display();

	}
	return 0;
}
