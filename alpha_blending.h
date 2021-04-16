#ifndef ALPHA_BLENDING
#define ALPHA_BLENDING

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <x86intrin.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


void Alpha_blending(sf::Uint8* back, sf::Uint8* front, \
                    const sf::Vector2u size_back, const sf::Vector2u size_front, const sf::Vector2i shift);

#endif
