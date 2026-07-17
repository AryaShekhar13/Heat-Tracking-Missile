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
    jet.setPosition({0.f,270.f});
    jet.setScale({0.10f,0.10f});

    Texture mistex;
    if (!mistex.loadFromFile("../assets/missile.png"))
    {
    std::cout << "Failed to load missile";
    return;
    }
    Sprite missile(mistex);
     missile.setPosition({390.f,570.f});
    missile.setScale({0.10f,0.08f});
    

    while(window.isOpen()){

        while(std:: optional event = window.pollEvent()){
            if(event->is<Event::Closed>()){
                window.close();
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape){
                window.close();
            }
        }

        state.jx++;
        state.my++;

        jet.setPosition({0.f+ state.jx,270.f});
        missile.setPosition({390.f,570.f - state.my});

        window.clear();
        
        window.draw(background);
        window.draw(track);
        window.draw(missile);
        window.draw(jet);

        window.display();
    }
}