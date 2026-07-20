#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>
#include <cmath>
#include "header.h"

using namespace sf;

void render(obj& state){
    RenderWindow window(VideoMode ({800,600}), "Simulation");
    window.setVerticalSyncEnabled(true);

    RectangleShape track({10000.f,1000.f});
    track.setPosition({-5000.f,580.f});
    track.setFillColor({70, 70 , 70});

    std::vector<Vector2f> missileTrail;
    VertexArray trajectory(PrimitiveType::LineStrip);

    VertexArray missileTrajectory(PrimitiveType::LineStrip);
    VertexArray jetTrajectory(PrimitiveType::LineStrip);

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
    float jetLength = jetSize.x * 0.10f;
    float jetHeight = jetSize.y * 0.08f;

    RectangleShape jetHitbox;
    jetHitbox.setSize({jetLength * 0.85f,jetHeight* 0.85f});
    jetHitbox.setOrigin({jetHitbox.getSize().x / 2.f,jetHitbox.getSize().y / 2.f});
    jetHitbox.setFillColor(Color::Transparent);
    jetHitbox.setOutlineColor(Color::Yellow);
    jetHitbox.setOutlineThickness(1.f);

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
    float missileLength = size.x * 0.10f;

    missile.setOrigin({size.x / 2.f,size.y / 2.f});

    missile.setScale({0.10f, 0.08f});
    missile.setPosition({390.f, 570.f});
    
    bool paused = false;
    bool tacticalView = false;
    bool jetView = false;
    bool missileView = false;
    int run = 0;
    float total = 0;

    View camera;
    camera.setSize({800.f,600.f});
    camera.setCenter({400.f,300.f});

    Vector2f cameraCenter = camera.getCenter();

    while(window.isOpen()){
        run++;

        while(std:: optional event = window.pollEvent()){
            if(event->is<Event::Closed>()){
                window.close();
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape){
                window.close();
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::T){
                missileView = false;
                jetView = false;
                tacticalView = !tacticalView;
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Num1){
                tacticalView = false;
                missileView = false;
                jetView = true;
            }
            if(event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Num2){
                tacticalView = false;
                jetView = false;
                missileView = true;
            }
        }

        if(run == 1){
            state.jx = 0;
            state.my = 0;
        }  

        
    float dx = state.jx - 390.f - state.mx;
    float dy = 270.f - state.jy - 570.f + state.my;

    if (!paused) physics(dx, dy, total);

    jet.setPosition({0.f+ state.jx, 270.f - state.jy});
    missile.setPosition({390.f + state.mx,570.f - state.my});
    
    missile.setRotation(radians(state.thetaM + PI/2.f));
    jet.setRotation(radians(state.thetaJ));
    jetHitbox.setPosition(jet.getPosition());
    jetHitbox.setRotation(jet.getRotation());

    float headX = missile.getPosition().x + std::cos(state.thetaM) * missileLength / 2.f;

    float headY = missile.getPosition().y + std::sin(state.thetaM) * missileLength / 2.f;

    float px = headX - (jet.getPosition().x + 12.f);
    float py = headY - (jet.getPosition().y) + 6.f;

    float c = std::cos(state.thetaJ);
    float s = std::sin(state.thetaJ);

    float localX =  px * c + py * s;
    float localY = -px * s + py * c;

    if (std::abs(localX) <= jetLength * 0.85 / 2.f && std::abs(localY) <= jetHeight * 0.85 / 2.f) paused = true;


        trajectory.append({missile.getPosition(),Color::Red});
        jetTrajectory.append({jet.getPosition(),Color::Green});

        Vector2f desiredCenter;
        Vector2f missilePos = missile.getPosition();
        Vector2f jetPos = jet.getPosition();
        Vector2f missileStart(390.f, 570.f);
        Vector2f jetStart(0.f , 270.f);

        if(tacticalView == false) desiredCenter = (missilePos + jetPos + missileStart + jetStart)/4.f;

        if(tacticalView == true) desiredCenter = (missilePos+jetPos)/2.f;

        if(jetView == true) desiredCenter = jetPos;

        if(missileView == true) desiredCenter = missilePos;

        cameraCenter += 0.08f*(desiredCenter-cameraCenter);
        camera.setCenter(cameraCenter);

        window.setView(camera);

        window.clear();
        
        window.draw(background);
        window.draw(trajectory);
        window.draw(jetTrajectory);
        window.draw(track);
        window.draw(missile);
        window.draw(jet);
        window.draw(jetHitbox);

        window.display();
    }
}