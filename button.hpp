#pragma once
#include <SFML/Graphics.hpp>
class Button : public sf::Sprite{
    private:
        

        sf::Vector2i mouse_position;

        sf::FloatRect bounds;

        sf::Texture hoveredTexture;
        sf::Texture baseTexture;
        sf::Texture clickedTexture;
        sf::RenderWindow& window;

    
    public:
        bool clicked = false;
        bool hovered = false;
        
        Button(sf::RenderWindow &win);

        void updateBounds();

        bool gethovered(); 

        bool getclicked();

        bool getrising();
        
        bool getfalling();

        void updatetexture();

        void setBaseTexture(sf::Texture texture);
        
        void setHoverTexture(sf::Texture texture);
        
        void setClickedTexture(sf::Texture texture);

};