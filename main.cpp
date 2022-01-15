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
        -get number of flags left
        -get if won
        -loop until win or loss condition met
        


*/

using namespace std;

class Board{
    private:
        int scalar;
        int height;
        int width;
        float bomb_prob;

        sf::Texture base;
        sf::Texture bomb;
        sf::Texture flagged;

        sf::Texture number_textures[9];

        sf::RenderWindow& window;

        sf::Sprite grid[32][32];

        bool bombs[32][32];
        bool flags[32][32];
        int suround[32][32];
        int uncovered[32][32];

        float ran;

    public:
        bool hasBoard = false;
        Board(int s, int w, int h, float p, sf::RenderWindow &win) : window(win){
            scalar = s;
            height = h;
            width = w;
            bomb_prob = p;

            
            base.loadFromFile("sprites/base.png", sf::IntRect(0, 0, 16, 16));
            bomb.loadFromFile("sprites/bomb.png", sf::IntRect(0, 0, 16, 16));
            flagged.loadFromFile("sprites/flag.png", sf::IntRect(0, 0, 16, 16));
            

            for(int i = 0; i < 9; i++){
                number_textures[i].loadFromFile("sprites/"+ to_string(i) + ".png", sf::IntRect(0, 0, 16, 16));
            }
        }
        
        void generateBoard() {

            for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                    sf::Sprite sprite;
                    sprite.setTexture(base);
                    sprite.setOrigin(-i*16, -j*16);
                    sprite.setScale(scalar, scalar);
                    
                    bombs[i][j] = false;

                    if (bomb_prob > ((float)rand())/RAND_MAX){
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
                                if(i+k < width and j+l < width){
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
        }

        void draw() {
            for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                    window.draw(grid[i][j]);
                }
            }
        }

        void drawExposed() {
            
            for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                    grid[i][j].setTexture(number_textures[suround[i][j]]);
                    window.draw(grid[i][j]);
                }
            }
        }
        

        int uncover(int x, int y){
            if(uncovered[x][y]){
                return -1; 
            }
            if(!flags[x][y] && !uncovered[x][y]){
                uncovered[x][y] = true;
                grid[x][y].setTexture(number_textures[suround[x][y]]);
                
                        
                if(bombs[x][y]){
                    grid[x][y].setTexture(bomb);
                    return 1;
                }

                if(suround[x][y] == 0){
                    for(int i = -1; i <= 1; i ++){
                        for(int j = -1; j <= 1; j ++){
                            if(x+i < width && x+i >= 0){
                                if(y+j < height && y+j >= 0){
                                    uncover(x + i, y+j);
                                }
                            }
                        }
                    }
                }
                return 0;
            }
            return -1;
        }

        int flag(int x, int y){
            if(!uncovered[x][y]){
                flags[x][y] = !flags[x][y];
                if (flags[x][y]){
                    grid[x][y].setTexture(flagged);
                }
                else{
                    grid[x][y].setTexture(base);
                }
                return 0;
            }
            return -1;
        }

        void generateZeroed(int x, int y){
            generateBoard();
            //drawExposed();
            if(suround[x][y] != 0){
                generateZeroed(x, y);
            }
            else{
                hasBoard = true;
            }
            
            return;
        }

        bool checkwin(){
            for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                    if(bombs[i][j] != flags[i][j]){
                        return false;
                    }
                }
            }
            return true;
        }
};
 

int main()
{  
    sf::Texture base;
    base.loadFromFile("sprites/base.png", sf::IntRect(0, 0, 16, 16));

    srand(time(0));
    int scalar = 2;
    int height = 32; // can't change this for now I need to figure out how to initialize lists in classes
    int width = 32; //
    float bomb_prob = 0.15;

    sf::Vector2i mouse_position;


    sf::RenderWindow window(sf::VideoMode(scalar * 16 * width, scalar * 16 * height), "minesweeper", sf::Style::Close);
    
    
    sf::Image icon;
    icon.loadFromFile("sprites/bomb.png"); 
    


    Board board = Board(scalar, width, height, bomb_prob, window);
    board.generateBoard();
    



    int x_index;
    int y_index;
    bool unclicked = false;
    bool haslost;

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


        if(!(board.checkwin() || haslost)){
            if(event.type == sf::Event::MouseButtonPressed){
                if(unclicked) 
                {   
                    unclicked = false;
                    x_index = (mouse_position.x - (mouse_position.x % (16 * scalar))) / (16 * scalar);
                    y_index = (mouse_position.y - (mouse_position.y % (16 * scalar))) / (16 * scalar);

                    
                    if(!board.hasBoard){
                        board.generateZeroed(x_index, y_index);
                    }
                        
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {   
                        if(board.uncover(x_index, y_index) == 1){
                            haslost = true;
                        }
                    }
                    else{
                        board.flag(x_index, y_index);
                    }
                }
            }
            else if(!unclicked)
            {   
                unclicked = true;
            }
        }


        window.clear(sf::Color::White);
        

        board.draw();

        

        //show display
        window.display();
        
    }
 
    return EXIT_SUCCESS;
}