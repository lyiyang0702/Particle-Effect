#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <iostream>
class Particle
{
public:

	sf::Vector2f pixelPos;
	sf::Vector2f pixelVelocity;
	float pixelSize;
	float timeLeftToLive;
	enum ParticleShapes { Circle, Square };
	ParticleShapes shapeType;
	sf::Color particleColor;
	Particle() :Particle (32, sf::Vector2f(0, 0), sf::Vector2f(0, 0), 1,Particle::Circle,sf::Color::White) {}
	Particle(float pixelSize, sf::Vector2f initPos, sf::Vector2f initVelocity, float lifetime, Particle::ParticleShapes shapeType, sf::Color particleColor)
		: pixelSize(pixelSize), pixelPos(initPos), pixelVelocity(initVelocity), timeLeftToLive(lifetime),shapeType(shapeType), particleColor(particleColor) {
	}
	//Particle() :Particle(32, sf::Vector2f(0, 0), sf::Vector2f(0, 0), 1) {}
	//Particle(float pixelSize, sf::Vector2f initPos, sf::Vector2f initVelocity, float lifetime)
	//	: pixelSize(pixelSize), pixelPos(initPos), pixelVelocity(initVelocity), timeLeftToLive(lifetime){
	//}

	sf::Shape& getShape() {
		switch (shapeType)
		{
		case Particle::Circle: {
			static auto shape = sf::CircleShape(pixelSize/2);
			shape.setPosition(pixelPos);
			shape.setFillColor(particleColor);
			return shape;
		}

			break;
		case Particle::Square: {
			static auto shape = sf::RectangleShape(sf::Vector2f(pixelSize, pixelSize));
			shape.setPosition(pixelPos);
			shape.setFillColor(particleColor);
			return shape;
		}

			break;
		default:
			break;
		}
}

	//sf::CircleShape getShape() {
	//	std::cout << "pixelSize: "<<pixelSize << std::endl;
	//	auto shape = sf::CircleShape(pixelSize);
	//	shape.setPosition(pixelPos);
	//	shape.setFillColor(sf::Color::White);
	//	return shape;
	//}

	void update(float deltaTime) {
		pixelPos += pixelVelocity * deltaTime;
		timeLeftToLive -= deltaTime;
	}

	bool isDead() {
		return timeLeftToLive <= 0;
	}


private:

};

#endif // 

