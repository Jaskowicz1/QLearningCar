#include "../Public/Car.h"


Car::Car()
{
	this->initRender();
    this->initText();
}

void Car::Update()
{
    RenderStats(); // This is purely for development purposes.
}

void Car::RenderStats()
{
    accelerationText.setString("Acceleration: " + std::to_string(speed));
    rotationText.setString("Turn rate: " + std::to_string(rotate));

    accelerationText.setCharacterSize(18);
    rotationText.setCharacterSize(18);
    rotationText.setPosition(0, 20);
}

void Car::initRender()
{

    std::cout << "Loading car.." << std::endl;

    if (!texture.loadFromFile("Car.jpg")) {
        // Throw error.
        std::cout << "Can not load car." << std::endl;
        return;
    }
    sprite = sf::Sprite(texture);
    sprite.setPosition(startX, startY);

    sprite.setOrigin(8, 16);
}

void Car::initText()
{
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cout << "Can not load Arial font." << std::endl;
        return;
    }
    accelerationText.setFont(font);
    accelerationText.setFillColor(sf::Color::Red);
    rotationText.setFont(font);
    rotationText.setFillColor(sf::Color::Red);
}

void Car::doMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->speed -= .25f;
        this->moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->speed += .25f;
        this->moving = true;
    }
    else {
        if (speed > 0) {
            speed -= .125f / 2;
        }
        else if (speed < 0) {
            speed += .125f / 2;
        }
        else {
            speed = 0;
        }

        this->moving = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->rotate -= .25f;
        this->moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->rotate += .25f;
        this->moving = true;
    }
    else {
        if (rotate > 0) {
            rotate -= .125f / 2.f;
        }
        else if (rotate < 0) {
            rotate += .125f / 2.f;
        }
        else {
            rotate = 0;
        }

        this->moving = false;
    }

    speed = std::clamp(speed, minSpeed, maxSpeed);

    // Rotate on circle.
    float x = cos(toRadians(sprite.getRotation() + 90));
    float y = sin(toRadians(sprite.getRotation() + 90));

    rotate = std::clamp(rotate, minRotation, maxRotation);
    
    sprite.move(x * speed, y * speed);
    sprite.rotate(rotate);

    //std::cout << "x: " << sprite.getPosition().x << " y: " << sprite.getPosition().y << std::endl;
}
