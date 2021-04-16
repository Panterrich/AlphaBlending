#include "alpha_blending.h"

void Alpha_blending(sf::Uint8* back, sf::Uint8* front, \
                    const sf::Vector2u size_back, const sf::Vector2u size_front, const sf::Vector2i shift)
{
    for (size_t back_y = (shift.y > 0) ? shift.y : 0, front_y = (shift.y > 0) ? 0 : -shift.y; \
                (back_y < size_back.y && front_y < size_front.y); ++back_y, ++front_y)
    {
        for (size_t back_x = (shift.x > 0) ? shift.x : 0, front_x = (shift.x > 0) ? 0 : -shift.x ; \
                    (back_x < size_back.x && front_x < size_front.x); ++back_x, ++front_x)
        {
            sf::Uint8* current_back  = back  + ((back_y  * size_back.x  + back_x)  << 2);
            sf::Uint8* current_front = front + ((front_y * size_front.x + front_x) << 2);

            sf::Uint8 balpha = current_front[3];

            if (balpha != 0)
            {
                float not_alpha = 1.0f - (float)((double)(balpha) * (1.0f / 255.f));

                current_back[0] = lround(float(current_back[0] * not_alpha) + current_front[0]);
                current_back[1] = lround(float(current_back[1] * not_alpha) + current_front[1]);
                current_back[2] = lround(float(current_back[2] * not_alpha) + current_front[2]);
                current_back[3] = lround(float(current_back[3] * not_alpha) + current_front[3]);
            }
        }
    }
}
