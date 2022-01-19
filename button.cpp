#include <SFML/Graphics.hpp>
#include "button.hpp"
        
        Button::Button(sf::RenderWindow &win) : window(win){
            
        }

        void Button::updateBounds(){
            bounds = getGlobalBounds();
        }

        

        bool Button::gethovered(){
            mouse_position = sf::Mouse::getPosition(window);
            updateBounds();
            if(bounds.contains(mouse_position.x, mouse_position.y)){
                hovered = true;
                return true;

            }
            hovered = false;
            return false;
        }   

        bool Button::getclicked(){
            if(gethovered()){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    clicked = true;
                    return true;
                }
            }
            clicked = false;
            return false;
        }

        void Button::updatetexture(){
            getclicked();
            if(clicked){
                setTexture(clickedTexture);
            }
            else if(hovered){
                setTexture(hoveredTexture);
            }
            else {
                setTexture(baseTexture);
            }
        }

        void Button::setBaseTexture(sf::Texture texture){
            baseTexture = texture;
        }
        
        void Button::setHoverTexture(sf::Texture texture){
            hoveredTexture = texture;
        }
        
        void Button::setClickedTexture(sf::Texture texture){
            clickedTexture = texture;
        }
