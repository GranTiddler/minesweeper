#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

/*
To run file:
-------------
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./sfml-app
*/

/*
TODO
-----------
-make a board class like you knew you should have done to begin with
    -methods:
        -generate board
        -uncover
            -uncover adjacent if tile value is zero
            -get if bomb
        -flag
        -get number of flags left

        -get if won

-better main loop (possibly just functions)
    -new game
        -get board where tile that was clicked has a value of zero
    -loop until win or loss condition met
        -remove and flag thingamajigs


*/

using namespace std;


 

int main()
{   
    srand(time(0));
    int scalar = 2;
    int height = 32;
    int width = 32;
    float bomb_prob = 0.1;

    sf::Vector2i mouse_position;


    sf::RenderWindow window(sf::VideoMode(scalar * 16 * width, scalar * 16 * height), "minesweeper");
    sf::Texture base;
    base.loadFromFile("sprites/base.png", sf::IntRect(0, 0, 16, 16));
    sf::Texture bomb;
    bomb.loadFromFile("sprites/bomb.png", sf::IntRect(0, 0, 16, 16));
    sf::Texture flagged;
    flagged.loadFromFile("sprites/flag.png", sf::IntRect(0, 0, 16, 16));

    sf::Texture number_textures[9];

    for(int i = 0; i < 9; i++){
        number_textures[i].loadFromFile("sprites/"+ to_string(i) + ".png", sf::IntRect(0, 0, 16, 16));
    }
    
    
    
    
    sf::Sprite grid[width][height];
    bool bombs[width][height];
    bool flags[width][height];
    int suround[width][height];
    int uncovered[width][height];

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            sf::Sprite sprite;
            sprite.setTexture(base);
            sprite.setOrigin(-i*16, -j*16);
            sprite.setScale(scalar, scalar);

            if (bomb_prob > (float) rand()/RAND_MAX){
                bombs[i][j] = true;
            }
            flags[i][j] = false;
            uncovered[i][j] = false;
            grid[i][j] = sprite;
            suround[i][j] = 0;

        }
    }
    
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            for(int k = -1; k <= 1; k++){
                for(int l = -1; l <= 1; l++){
                    if(i+k >= 0 and j+l >= 0){
                        if(i+k <= width and j+l <= width){
                            if(bombs[i+k][j+l]){
                                suround[i][j] ++;
                                //grid[i][j].setTexture(number_textures[suround[i][j]]);
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    sf::Image icon;
    icon.loadFromFile("sprites/bomb.png"); 
    


    
    int x_index;
    int y_index;
    bool unclicked = false;
    
 
    while (window.isOpen())
    {   
        //if close window button clicked close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mouse_position = sf::Mouse::getPosition(window);

        if(event.type == sf::Event::MouseButtonPressed){
            if(unclicked) 
            {   
                unclicked = false;
                x_index = (mouse_position.x - (mouse_position.x % (16 * scalar))) / (16 * scalar);
                y_index = (mouse_position.y - (mouse_position.y % (16 * scalar))) / (16 * scalar);
                    
                if (event.mouseButton.button == sf::Mouse::Left)
                {   
                    if(!flags[x_index][y_index]){
                        grid[x_index][y_index].setTexture(number_textures[suround[x_index][y_index]]);
                        uncovered[x_index][y_index] = true;
                        
                        if(bombs[x_index][y_index]){
                            grid[x_index][y_index].setTexture(bomb);
                            return 0;
                        }
                    }
                }
                else{
                    if(!uncovered[x_index][y_index]){
                        flags[x_index][y_index] = !flags[x_index][y_index];
                        if(flags[x_index][y_index]){
                            grid[x_index][y_index].setTexture(flagged);
                        }
                        else{
                            grid[x_index][y_index].setTexture(base);
                        }
                    }
                }
            }
        }
        else if(!unclicked)
        {   
            unclicked = true;
        }
        



        


        window.clear(sf::Color::White);

        

        


        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                window.draw(grid[i][j]);
            }
        }


        //show display
        window.display();
        
    }
 
    return EXIT_SUCCESS;
}