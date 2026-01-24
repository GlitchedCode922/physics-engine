#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "headers/vector.hpp"
#include "headers/body.hpp"
#include "headers/staticbody.hpp"
#include "headers/scene.hpp"

Scene scene;
StaticBoundedBox bb(Vector2(400, 300), 700, 500);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Render Window");

    scene.gravity = Vector2(0, 0);
    for (int i = 0; i < 20; ++i) {
        Body* body = new Body(Vector2(400, 300), i + 5);
        body->velocity = Vector2((-5 + i * 20) % 24000, (20 + i * 18) % 24000);
        body->restitution = 1;
        body->friction = 1;
        scene.addBody(body);
    }
    scene.addStaticBody(&bb);

    // Main loop
    bool firstFrame = true;
    sf::Clock clock;
    clock.restart();
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        if (firstFrame) {
            deltaTime = sf::seconds(0);
            firstFrame = false;
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // Clear the window with a light gray color
        window.clear(sf::Color(0x2e2e2eff));

        scene.update(deltaTime.asSeconds());
        for (auto& body: scene.bodies) {
            sf::CircleShape shape(body->radius);
            shape.setFillColor(sf::Color(0xf0f0f0ff));
            shape.setPosition(body->position.x - body->radius, body->position.y - body->radius);
            window.draw(shape);
        }
        // Display the contents of the window
        window.display();
    }

    return 0;
}
