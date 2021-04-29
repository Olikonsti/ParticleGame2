#include <SFML/Graphics.hpp>
#include "Particle.cpp"
#include <stdio.h>
#include <string.h>
#include <thread>

int max_frame_rate = 120;
int ticks = 0;
bool game_paused = false;
int mouse_hologram_border = 2;
int mousex;
int mousey;
int gamex;
int gamey;

string selected_particle_type = "Stone";




int main()
{
    sf::RectangleShape mouse_hologram;
    mouse_hologram.setSize(sf::Vector2f(particle_size, particle_size)); 
    mouse_hologram.setFillColor(sf::Color::Color(100, 200, 10, 0));
    mouse_hologram.setOutlineColor(sf::Color::Color(100,200,10));
    mouse_hologram.setOutlineThickness(mouse_hologram_border);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ParticleGame");// , sf::Style::Fullscreen);
    window.setFramerateLimit(max_frame_rate);
    sf::RectangleShape shape;

    
    
    for (int i = 0; i < 20; i++) {
        spawn_particle(10 + i, 20, "Stone");
    }
    
    
    

    while (window.isOpen())
    {
        //spawn_particle(20, 10, "Water");
        
        ticks++;

        // Window Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Controls
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        mousex = mouse_position.x;
        mousey = mouse_position.y;
        gamex = mousex / particle_size;
        gamey = mousey / particle_size;


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            spawn_particle(gamex, gamey, selected_particle_type);
            spawn_particle(gamex-1, gamey, selected_particle_type);
            spawn_particle(gamex+1, gamey, selected_particle_type);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            kill_particle(gamex, gamey);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            selected_particle_type = "Water";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            selected_particle_type = "Stone";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            selected_particle_type = "Sand";
        }
        if (sf::Keyboard::Key (sf::Keyboard::Space))
        {
            game_paused = !game_paused;
        }

        // Console info print
        if (ticks % 100 == 0) {
            cout << "Particles: " << particle_list.size() << "\n";
        }

        
            
        // draw cycle
        window.clear();
        //draw mouse hologram

        mouse_hologram.setPosition(gamex * particle_size, gamey * particle_size);

        // draw all particles and update them
        for (auto i = particle_list.begin(); i != particle_list.end(); i++)
        {
            i->move(i->x, i->y + 1);

            sf::RectangleShape shape(sf::Vector2f(particle_size, particle_size));
            shape.setFillColor(i->color);

            shape.setPosition((i->x * particle_size), (i->y * particle_size));

            window.draw(shape);
        }
        window.draw(mouse_hologram);
        window.display();
            
            
        
        
        
        
        
    }
    return 0;
}
