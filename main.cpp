#include "alpha_blending.h"

int main()
{
    sf::Image file_background;
    sf::Image file_neko;
    sf::Image file_jotaro;

    file_neko.loadFromFile("Images/neko.png");
    file_jotaro.loadFromFile("Images/jotaro1.png");
    file_background.loadFromFile("Images/back3.png");

    const sf::Vector2u size_neko    = file_neko.getSize();
    const sf::Vector2u size_jotaro  = file_jotaro.getSize();
    const sf::Vector2u size_back    = file_background.getSize();

    const sf::Vector2i shift_neko   = {930, 110};
    const sf::Vector2i shift_jotaro = {100, 250};

    const sf::Uint8* neko   = file_neko.getPixelsPtr();
    const sf::Uint8* jotaro = file_jotaro.getPixelsPtr();
    const sf::Uint8* back   = file_background.getPixelsPtr();

    sf::Uint8* result = new sf::Uint8[size_back.x * size_back.y * 4];
    memcpy(result, back, size_back.x * size_back.y * 4);

    for (size_t i = 0; i < 100; ++i)
    {
        Alpha_blending(result, const_cast<sf::Uint8*>(neko), size_back, size_neko, shift_neko);
        Alpha_blending(result, const_cast<sf::Uint8*>(jotaro), size_back, size_jotaro, shift_jotaro);
    }

    sf::Texture result_image;
    result_image.update(result);
    sf::Image rsl;
    rsl.create(size_back.x, size_back.y, result);    
    rsl.saveToFile("Images/output.png");

    delete [] result;

    return 0;
}