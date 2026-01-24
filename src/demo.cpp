#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "headers/vector.hpp"
#include "headers/body.hpp"
#include "headers/staticbody.hpp"
#include "headers/constraint.hpp"
#include "headers/scene.hpp"

Scene scene;
StaticBoundedBox bb(Vector2(400, 300), 700, 500);

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Render Window");

    scene.gravity = Vector2(0, 0);
    // for (int i = 0; i < 50; ++i) {
    //     Body* body = new Body(Vector2(i * 20, i * 25), i % 20 + 5);
    //     body->velocity = Vector2((-5 + i * 20) % 24000, (20 + i * 18) % 24000);
    //     body->restitution = 0.8;
    //     body->friction = 1;
    //     body->mass = pow(i % 20 + 5, 2) / 400;
    //     scene.addBody(body);
    // }
    Body* body = new Body(Vector2(200, 150), 20);
    body->velocity = Vector2(150, 100);
    body->restitution = 0;
    body->friction = 1;
    body->mass = 1;
    scene.addBody(body);
    Body* body2 = new Body(Vector2(600, 450), 30);
    body2->velocity = Vector2(-100, -150);
    body2->restitution = 0;
    body2->friction = 1;
    body2->mass = 1;
    scene.addBody(body2);
    SpringConstraint* sc = new SpringConstraint(body, body2, 150, 50);
    sc->damping = 1;
    scene.addConstraint(sc);
    scene.addStaticBody(&bb);

    // Dragging variables
    Body* draggedBody = nullptr;
    Vector2 dragOffset(0, 0);

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

            // Mouse pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                Vector2 mouseWorld(mousePos.x, mousePos.y);

                // Check if clicking on any body
                for (auto& body : scene.bodies) {
                    Vector2 diff = body->position - mouseWorld;
                    if (diff.length() <= body->radius) {
                        draggedBody = body;
                        dragOffset = body->position - mouseWorld;
                        body->velocity = Vector2(0, 0); // reset velocity before pulling
                        break;
                    }
                }
            }

            // Mouse released
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                draggedBody = nullptr;
            }
        }

        // Update dragged body using velocity toward mouse
        if (draggedBody) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            Vector2 mouseWorld(mousePos.x, mousePos.y);

            // Target position with offset
            Vector2 target = mouseWorld + dragOffset;

            // Compute velocity toward target
            Vector2 desiredVelocity = target - draggedBody->position;

            // Scale for smooth movement (tweak factor for responsiveness)
            float speedFactor = 10.0f;
            draggedBody->velocity = desiredVelocity * speedFactor;
        }

        // Update physics
        scene.update(deltaTime.asSeconds());

        // Clear the window with a light gray color
        window.clear(sf::Color(0x2e2e2eff));
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
