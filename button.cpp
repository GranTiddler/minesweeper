#include <SFML/Graphics.hpp>
#include "button.hpp"

//constructor
Button::Button(sf::RenderWindow &win) : window(win)
{
}

//get bounding box around button
void Button::updateBounds()
{
    bounds = getGlobalBounds();
}

//get if the mouse is above the button
bool Button::gethovered()
{
    mouse_position = sf::Mouse::getPosition(window);
    updateBounds();
    if (bounds.contains(mouse_position.x, mouse_position.y))
    {
        hovered = true;
        return true;
    }
    hovered = false;
    return false;
}

//get if the button is currently pressed down
bool Button::getclicked()
{
    if (gethovered())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicked = true;
            return true;
        }
    }
    clicked = false;
    return false;
}

// change to texture based on state of button
void Button::updatetexture()
{
    getclicked();
    if (clicked)
    {
        setTexture(clickedTexture);
    }
    else if (hovered)
    {
        setTexture(hoveredTexture);
    }
    else
    {
        setTexture(baseTexture);
    }
}

//set texture for button states
void Button::setBaseTexture(sf::Texture texture)
{
    baseTexture = texture;
}

void Button::setHoverTexture(sf::Texture texture)
{
    hoveredTexture = texture;
}

void Button::setClickedTexture(sf::Texture texture)
{
    clickedTexture = texture;
}
