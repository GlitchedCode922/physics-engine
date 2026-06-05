#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "headers/vector.hpp"
#include "headers/body.hpp"
#include "headers/scene.hpp"
#include "api.hpp"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({(unsigned int)windowSize.x, (unsigned int)windowSize.y}), windowTitle);

    Scene* scene = setupScene();
    double fixed_dt = 1.0 / framerate;
    double accumulator = 0.0;

    // Dragging variables
    Body* draggedBody = nullptr;
    Vector2 dragOffset(0, 0);
    bool isDraggedStatic = false;

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
        #if SFML_VERSION_MAJOR >= 3
        while (const std::optional event = window.pollEvent()) {
        #else
        sf::Event event;
        while (window.pollEvent(event)) {
        #endif
            // Window closed
            #if SFML_VERSION_MAJOR >= 3
            if (event->is<sf::Event::Closed>()) window.close();
            #else
            if (event.type == sf::Event::Closed) window.close();
            #endif

            // Mouse pressed
            #if SFML_VERSION_MAJOR >= 3
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>(); mouse && mouse->button == sf::Mouse::Button::Left) {
            #else
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            #endif
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
                            isDraggedStatic = c->isStatic;
                            c->isStatic = true;
                            break;
                        }
                    }
                }
            }

            // Mouse released
            #if SFML_VERSION_MAJOR >= 3
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>(); mouse && mouse->button == sf::Mouse::Button::Left) {
            #else
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            #endif
                if (draggedBody) draggedBody->isStatic = isDraggedStatic;
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
        // Constraints are drawn first so they appear behind bodies
        #if SFML_VERSION_MAJOR >= 3
        sf::VertexArray lines(sf::PrimitiveType::Lines, scene->constraints.size() * 2);
        #else
        sf::VertexArray lines(sf::Lines, scene->constraints.size() * 2);
        #endif
        for (int i = 0; i < scene->constraints.size(); i++) {
            Constraint* c = scene->constraints[i];
            lines[i * 2].position = sf::Vector2f(c->bodyA->position.x, c->bodyA->position.y);
            lines[i * 2].color = sf::Color(0x808080ff);
            lines[i * 2 + 1].position = sf::Vector2f(c->bodyB->position.x, c->bodyB->position.y);
            lines[i * 2 + 1].color = sf::Color(0x808080ff);
        }
        window.draw(lines);
        for (auto body: scene->bodies) {
            if (CircleBody* c = dynamic_cast<CircleBody*>(body)) {
                sf::CircleShape shape(c->radius);
                shape.setFillColor(sf::Color(0xf0f0f0ff));
                shape.setPosition(sf::Vector2f(c->position.x - c->radius, c->position.y - c->radius));
                window.draw(shape);
            }
            if (BoundedBoxBody* b = dynamic_cast<BoundedBoxBody*>(body)) {
                // Draw 4 rectangles for the bounds
                sf::RectangleShape shape;
                shape.setFillColor(sf::Color(0xb3b3b3ff));
                Vector2 min = b->position - Vector2(b->width * 0.5, b->height * 0.5);
                Vector2 max = b->position + Vector2(b->width * 0.5, b->height * 0.5);
                // Top
                shape.setSize(sf::Vector2f(windowSize.x, min.y));
                shape.setPosition(sf::Vector2f(0, 0));
                window.draw(shape);
                // Bottom
                shape.setSize(sf::Vector2f(windowSize.x, windowSize.y - max.y));
                shape.setPosition(sf::Vector2f(0, max.y));
                window.draw(shape);
                // Left
                shape.setSize(sf::Vector2f(min.x, max.y - min.y));
                shape.setPosition(sf::Vector2f(0, min.y));
                window.draw(shape);
                // Right
                shape.setSize(sf::Vector2f(windowSize.x - min.x, max.y - min.y));
                shape.setPosition(sf::Vector2f(max.x, min.y));
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
