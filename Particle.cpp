#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <list>
#include <iostream>
#include <iterator> 
using namespace std;

int particle_size = 10;
int kill_level = 1300 / particle_size;

static int ARRAYX = 200;
static int ARRAYY = 200;

int particle_pos[200][200];

/*

0 Empty
1 Particle
2 Water



*/



class Particle {
public:
    int x;
    int y;
    int lastx, lasty;
    string name;
    string type;
    sf::Color color;


    Particle(int x_start, int y_start) {
        type = "SOLID";
        color = sf::Color::White;
        x = x_start;
        y = y_start;
        lastx = x;
        lasty = y;
        particle_pos[x][y] = 1;
        
    };

    void move(int x_neu, int y_neu) {
        if (type == "SOLID") {

        }
        else if (type == "LIQUID" or type == "POWDER") {
            particle_pos[x][y] = 0;
            x += x_neu;
            y += y_neu;
            if (y > ARRAYY - 2) {

            }
            else {
                particle_pos[x][y] = 1;
            }
            

        }
 
    }
};

class Sand : public Particle
{
public:
    int x;
    int y;

    Sand(int x_start, int y_start) :Particle(x_start, y_start) {
        type = "POWDER";
        color = sf::Color::Color(255, 248, 199);
    };
};

class Water : public Particle
{
public:
    int x;
    int y;

    Water(int x_start, int y_start) :Particle(x_start, y_start) {
        type = "LIQUID";
        color = sf::Color::Blue;
    };
};

class Stone : public Particle
{
public:
    int x;
    int y;

    Stone(int x_start, int y_start):Particle(x_start, y_start) {
        type = "SOLID";
        color = sf::Color::Color(143, 143, 143);
    };
};


list<Particle> particle_list;


void spawn_particle(int x, int y, std::string type)
{

    // check if a particle is already at the same position
    bool able_to_spawn = true;
    for (auto i = particle_list.begin(); i != particle_list.end(); i++)
    {
        if (i->x == x && i->y == y) {
            able_to_spawn = false;
        }
    }

    // spawn particle if there is no particle at this x, y
    if (able_to_spawn)
    {
        if (type == "TEST") {
            Particle a(x, y);
            particle_list.push_back(a);
        }
        else if (type == "Stone") {
            Stone a(x, y);
            particle_list.push_back(a);
        }
        else if (type == "Water") {
            Water a(x, y);
            particle_list.push_back(a);
        }
        else if (type == "Sand") {
            Sand a(x, y);
            particle_list.push_back(a);

        }
        else{
            cout << "Unknown Element type " << type << "\n";
        }
    }
    
}


void kill_particle(int x, int y)
{
    for (auto i = particle_list.begin(); i != particle_list.end(); i++)
    {
        
        if (i->x == x && i->y == y)
        {
            particle_list.erase(i); 
        }
    }
}


