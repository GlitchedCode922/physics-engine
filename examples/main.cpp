#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "headers/vector.hpp"
#include "headers/body.hpp"
#include "headers/scene.hpp"
#include "api.hpp"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);

    Scene* scene = setupScene();
    double fixed_dt = 1.0 / framerate;
    double accumulator = 0.0;

    // Dragging variables
    Body* draggedBody = nullptr;
    Vector2 dragOffset(0, 0);

    // Main loop
    bool firstFrame = true;
    sf::Clock clock;
    clock.restart();
    while (window.isOpen()) {
        double deltaTime = clock.restart().asSeconds();
        if (firstFrame) {
            deltaTime = fixed_dt;
            firstFrame = false;
        }
        if (deltaTime > 0.25) deltaTime = 0.25;
        accumulator += deltaTime;

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Mouse pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                Vector2 mouseWorld(mousePos.x, mousePos.y);

                // Check if clicking on any body
                for (auto body: scene->bodies) {
                    if (CircleBody* c = dynamic_cast<CircleBody*>(body)) {
                        Vector2 diff = c->position - mouseWorld;
                        if (diff.length() <= c->radius) {
                            draggedBody = c;
                            dragOffset = c->position - mouseWorld;
                            c->velocity = Vector2(0, 0); // reset velocity before pulling
                            break;
                        }
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
        while (accumulator >= fixed_dt) {
            scene->update(fixed_dt);
            accumulator -= fixed_dt;
        }

        // Clear the window with a light gray color
        window.clear(sf::Color(0x2e2e2eff));
        for (auto body: scene->bodies) {
            if (CircleBody* c = dynamic_cast<CircleBody*>(body)) {
                sf::CircleShape shape(c->radius);
                shape.setFillColor(sf::Color(0xf0f0f0ff));
                shape.setPosition(c->position.x - c->radius, c->position.y - c->radius);
                window.draw(shape);
            }
        }
        // Display the contents of the window
        window.display();
    }

    // Cleanup
    for (auto& body : scene->bodies) {
        delete body;
    }
    for (auto& constraint : scene->constraints) {
        delete constraint;
    }
    delete scene;

    return 0;
}
