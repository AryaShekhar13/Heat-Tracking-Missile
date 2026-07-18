#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>
#include "header.h"

using namespace sf;

void render(obj& state){
    RenderWindow window(VideoMode ({800,600}), "Simulation");
    window.setVerticalSyncEnabled(true);

    RectangleShape track({800.f,30.f});
    track.setPosition({0.f,580.f});
    track.setFillColor({70, 70 , 70});

    std::vector<sf::Vector2f> missileTrail;
    VertexArray trajectory(sf::PrimitiveType::LineStrip);

    VertexArray missileTrajectory(sf::PrimitiveType::LineStrip);
    VertexArray jetTrajectory(sf::PrimitiveType::LineStrip);

    Texture bg;
    if (!bg.loadFromFile("../assets/sky.jpeg"))
    {
    std::cout << "Failed to load background";
    return;
    }
    Sprite background(bg);
    background.setScale({2.f,2.f});

    Texture jettex;
    if (!jettex.loadFromFile("../assets/jet.png"))
    {
    std::cout << "Failed to load jet";
    return;
    }
    Sprite jet(jettex);
    auto jetSize = jettex.getSize();

    jet.setOrigin({jetSize.x / 2.f,jetSize.y / 2.f});

jet.setScale({0.10f, 0.10f});
jet.setPosition({0.f, 270.f});

    Texture mistex;
    if (!mistex.loadFromFile("../assets/missile.png"))
    {
    std::cout << "Failed to load missile";
    return;
    }
    Sprite missile(mistex);

    auto size = mistex.getSize();
    missile.setOrigin({size.x / 2.f,size.y / 2.f});

    missile.setScale({0.10f, 0.08f});
    missile.setPosition({390.f, 570.f});
    
    bool paused = false;
    int run = 0;

    while(window.isOpen()){
        run++;

        while(std:: optional event = window.pollEvent()){
            if(event->is<Event::Closed>()){
                window.close();
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape){
                window.close();
            }
        }

        if(run == 1){
            state.jx = 0;
            state.my = 0;
        }  

        physics((0.f+ state.jx - 390.f - state.mx) , (270.f - 570.f + state.my));

        jet.setPosition({0.f+ state.jx,270.f});
        missile.setPosition({390.f + state.mx,570.f - state.my});
        missileTrail.push_back(missile.getPosition());

        trajectory.append({missile.getPosition(),Color::Red});
        jetTrajectory.append({jet.getPosition(),Color::Green});

        window.clear();
        
        window.draw(background);
        window.draw(trajectory);
        window.draw(jetTrajectory);
        window.draw(track);
        window.draw(missile);
        window.draw(jet);

        window.display();
    }
}