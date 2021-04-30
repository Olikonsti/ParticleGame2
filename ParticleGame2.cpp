#include <SFML/Graphics.hpp>
#include "Particle.cpp"
#include <stdio.h>
#include <string.h>
#include <thread>

int VERSION = 1.1;

int max_frame_rate = 144;
int ticks = 0;
bool game_paused = false;
int mouse_hologram_border = 2;
int mousex;
int mousey;
int gamex;
int gamey;

string selected_particle_type = "Stone";


void spawn_rect(int size) {
    int half_size = size / 2;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            spawn_particle(gamex + x - half_size / 2, gamey + y - half_size / 2, selected_particle_type);
        }
    }
}

void kill_rect(int size) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            kill_particle(gamex + x - size / 2, gamey + y - size / 2);
        }
    }
}

int main()
{
    sf::RectangleShape mouse_hologram;
    mouse_hologram.setSize(sf::Vector2f(particle_size, particle_size)); 
    mouse_hologram.setFillColor(sf::Color::Color(100, 200, 10, 0));
    mouse_hologram.setOutlineColor(sf::Color::Color(100,200,10));
    mouse_hologram.setOutlineThickness(mouse_hologram_border);

    sf::Text selected_text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font...";
    }
    selected_text.setPosition(50, 50);
    selected_text.setFont(font);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ParticleGame"); // , sf::Style::Fullscreen);
    window.setFramerateLimit(max_frame_rate);
    sf::RectangleShape shape;
    
    
    

    while (window.isOpen())
    {

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
            spawn_rect(10);
            
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            kill_rect(10);
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

        //Screen info print
        selected_text.setString(selected_particle_type);
        selected_text.setCharacterSize(24);
        selected_text.setFillColor(sf::Color::Red);

        
            
        // draw cycle
        window.clear();
        //draw mouse hologram

        mouse_hologram.setPosition(gamex * particle_size, gamey * particle_size);

        // draw all particles and update them
        for (auto i = particle_list.begin(); i != particle_list.end(); i++)
        {

            if (i->y > ARRAYY - 4) {
                //kill_particle(i->x, i->y);
                particle_list.erase(i);
                if (i->y > ARRAYY - 2 or i->x > ARRAYX - 2 or i->x < 2 or i->y < 2) {
                }
                else {
                    particle_pos[i->x][i->y] = 0;
                }
                
                
            }
            else {
                i->move();
            }

            



            sf::RectangleShape shape(sf::Vector2f(particle_size, particle_size));
            shape.setFillColor(i->color);

            shape.setPosition((i->x * particle_size), (i->y * particle_size));

            window.draw(shape);
        }
        window.draw(mouse_hologram);
        window.draw(selected_text);
        window.display();
            
            
        
        
        
        
        
    }
    return 0;
}
