#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <list>
#include <iostream>
#include <iterator> 
using namespace std;

int particle_size = 3;
int kill_level = 1300 / particle_size;

static int ARRAYX = 800;
static int ARRAYY = 500;

int particle_pos[2000][2000];

/*

0 Empty
1 Particle
2 Water
3 Sand



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
        if (y > ARRAYY - 2 or x > ARRAYX - 2 or x < 2 or y < 2) {
        }
        else {
            particle_pos[x][y] = 1;
        }
        
        
    };

    void move() {
        if (type == "SOLID") {

        }
        else if (type == "LIQUID") {

            int x_neu = (rand() % 3) - 1;
            int y_neu = 1;

            for (int i = 0; i < (rand() % 15) * 2; i++) {
                if (y > ARRAYY - 2 or x > ARRAYX - 2 or x < 2 or y < 2) {
                }
                else {
                    particle_pos[x][y] = 0;
                }


                if (particle_pos[x][y + y_neu] == 0) {
                    y += y_neu;
                }
                else if (particle_pos[x + x_neu][y] == 0) {
                        x += x_neu;
                }
                else {
                    if (y > ARRAYY - 2 or x > ARRAYX - 2 or x < 0 or y < 0) {

                    }
                    else {
                        particle_pos[x][y] = 1;
                    }
                    break;
                }
                

                if (y > ARRAYY - 2 or x > ARRAYX - 2 or x < 2 or y < 2) {

                }
                else {
                    particle_pos[x][y] = 1;
                }
            }
            

            
            

        }
        else if (type == "POWDER") {

        }
 
    }
};

class Sand : public Particle
{
public:
    int x;
    int y;
    int id;
    int lastx, lasty;

    Sand(int x_start, int y_start) :Particle(x_start, y_start) {
        id = 3;
        type = "POWDER";
        name = "Sand";
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


int spawn_particle(int x, int y, std::string type)
{

    if (y > ARRAYY - 2 or x > ARRAYX - 2 or x < 2 or y < 2) {
        return 0;
    }
    else {
        
    }

    // check if a particle is already at the same position
    bool able_to_spawn = false;
   
    if (particle_pos[x][y] == 0){
        able_to_spawn = true;
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
            particle_pos[i->x][i->y] = 0;
            particle_list.erase(i); 
        }
    }
}


