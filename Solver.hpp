#pragma once
#include "Cestica.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
class Solver
{
    public:

        Solver()
        {
            grid.resize(350, std::vector<std::vector<int>>(350));
        }
        
        Cestica& addObject(sf::Vector2f position, float radius)
        {
            int gridX = position.x / grid_size;
            int gridY = position.y / grid_size;
            Cestica newParticle = Cestica(position, radius, gridX, gridY, objects.size());
            grid[gridX][gridY].push_back(objects.size());
            return objects.emplace_back(newParticle);
        }

        void update()
        {
            float substep_dt = step_dt / substep;
            for(int i = 0; i < substep; i++)
            {
                applyGravity();  
                checkCollisions();
                applyBorders();
                updateObjects(substep_dt);  
            }
        }

        /*
        void mousePull(sf::Vector2f pos) {
            for (Cestica& obj : objects) {
                sf::Vector2f dir = pos - obj.getPosition();
                float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
                obj.accelerate(dir * std::max(0.0f, 10 * (120 - dist)));
            }
        }
    
        void mousePush(sf::Vector2f pos) {
            for (Cestica& obj : objects) {
                sf::Vector2f dir = pos - obj.getPosition();
                float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
                obj.accelerate(dir * std::min(0.0f, -10 * (120 - dist)));
            }
        }
            */

        std::vector<Cestica>& getObjects()
        {
            return objects;
        }

        void setBoundary(sf::Vector2f position, float radius)
        {
            boundary_center = position;
            boundary_radius = radius;
        }

        sf::Vector3f getBoundary()
        {
            return {boundary_center.x, boundary_center.y, boundary_radius};
        }

        void setObjectVelocity(Cestica& object, sf::Vector2f v)
        {
            object.setVelocity(v, step_dt / substep);
        }

    private:
        float window_size = 840.0f;
        std::vector<Cestica> objects;
        sf::Vector2f gravity = {0.0f, 1000.0f};
        const float dampening = 0.75f;


        sf::Vector2f boundary_center = {960.0f, 540.0f};
        float boundary_radius = 20.0f;


        float step_dt = 1.0f / 60;
        int substep = 8; //promenljiva koju uvodimo kako bismo obezbedili brze sprovodjenje update funkcija
        
        
        int grid_size = 10;
        std::vector<std::vector<std::vector<int>>> grid;

        void applyGravity()
        {
            for(auto &obj : objects)
                obj.accelerate(gravity);
        }

        void applyBorders()
        {
            for(auto& obj : objects)
            {
                const sf::Vector2f pos = obj.getPosition();
                sf::Vector2f npos = obj.getPosition();
                sf::Vector2f velocity = obj.getVelocity();
                sf::Vector2f dy = {velocity.x * dampening, -velocity.y}; //vektor koji predstavlja promenu brzine koja treba da se desi nakon sto cestica udari u gornju ili donju stranicu
                sf::Vector2f dx = {-velocity.x, dampening * velocity.y}; //isto samo za levu i desnu

                //provera za levu i za desnu ivicu
                if(pos.x < obj.getRadius() || pos.x + obj.getRadius() > window_size)
                {
                    if(pos.x < obj.getRadius()) npos.x = obj.getRadius();
                    if(pos.x + obj.getRadius() > window_size) npos.x = window_size - obj.getRadius();
                    obj.setPosition(npos);
                    obj.setVelocity(dx, 1.0f);
                }

                if(pos.y < obj.getRadius() || pos.y + obj.getRadius() > window_size)
                {
                    if(pos.y < obj.getRadius()) npos.y = obj.getRadius();
                    if(pos.y + obj.getRadius() > window_size) npos.y = window_size - obj.getRadius();
                    obj.setPosition(npos);
                    obj.setVelocity(dy, 1.0f);
                }
            }
        }

        //Funkcija koja je prvobitno ogranicavala cestice na krug. Sada to radi applyBorder
        /*
        void applyBoundary()
        {
            for(auto& obj : objects)
            {
                const sf::Vector2f r = boundary_center - obj.getPosition();
                const float distance = sqrt(r.x * r.x + r.y * r.y);
                if(distance > boundary_radius - obj.getRadius())
                {
                    const sf::Vector2f n = r / distance; //tangenta koja odgovara krugu, ujedno predstavlja i osu refleksije za kuglicu
                    const sf::Vector2f perp = {-n.y, n.x};
                    const sf::Vector2f velocity = obj.getVelocity();
                    obj.setPosition(boundary_center - n * (boundary_radius - obj.getRadius()));
                    obj.setVelocity(2.0f * (velocity.x * perp.x + velocity.y * perp.y) * perp - velocity, 1.0f);
                }
            }
        }*/

        void collideCells(int x1, int y1, int x2, int y2)
        {
            for(int id_1 : grid[x1][y1])
            {
                Cestica& obj1 = objects[id_1];
                for(int id_2 : grid[x2][y2])
                {
                    if(id_1 == id_2) continue;

                    Cestica& obj2 = objects[id_2];
                    sf::Vector2f v = obj1.getPosition() - obj2.getPosition();
                    float dist = sqrt(v.x * v.x + v.y * v.y);
                    float min_dist = obj1.getRadius() + obj2.getRadius();
                    if(dist < min_dist && dist != 0.0f)
                    {
                        sf::Vector2f n = v / dist;
                        float delta = 0.5f * (min_dist - dist);

                        obj1.setPosition(obj1.getPosition() + n * 0.5f * delta);
                        obj2.setPosition(obj2.getPosition() - n * 0.5f * delta);
                    }
                }
            }
        }

        void checkCollisions()
        {
            int num_cells = window_size / grid_size;
            int dx[] = {1, 1, 0, 0, -1};
            int dy[] = {0, 1, 0, 1, 1};
            for(int i = 0; i < num_cells; i++)
            {
                for(int j = 0; j < num_cells; j++)
                {
                    if(!grid[i][j].size()) continue;
                    for(int k = 0; k < 5; k++)
                    {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(nx < 0 || ny < 0 || nx >= num_cells || ny >= num_cells) continue;
                        collideCells(i, j, nx, ny);
                    }
                }
            }
        }

        void updateObjects(float dt)
        {
            
            for(auto& obj : objects)
            {
                int cur_gridX = obj.getGridX();
                int cur_gridY = obj.getGridY();

                obj.update(dt);
                obj.setGridX(obj.getPosition().x / grid_size);
                obj.setGridY(obj.getPosition().y / grid_size);

                if(cur_gridX != obj.getGridX() || cur_gridY != obj.getGridY())
                {
                    auto pos = find(grid[cur_gridX][cur_gridY].begin(), grid[cur_gridX][cur_gridY].end(), obj.getID());
                    grid[cur_gridX][cur_gridY].erase(pos);
                    grid[obj.getGridX()][obj.getGridY()].push_back(obj.getID());

                } 
            }
        }
    
};