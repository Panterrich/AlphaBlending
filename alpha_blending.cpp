#include "alpha_blending.h"

void Alpha_blending(sf::Uint8* back, sf::Uint8* front, \
                    const sf::Vector2u size_back, const sf::Vector2u size_front, const sf::Vector2i shift)
{
    size_t begin_back_y  = (shift.y > 0) ? shift.y  : 0;
    size_t begin_front_y = (shift.y > 0) ? 0 : -shift.y;
    size_t begin_back_x  = (shift.x > 0) ? shift.x  : 0;
    size_t begin_front_x = (shift.x > 0) ? 0 : -shift.x;

    for (size_t back_y = begin_back_y, front_y = begin_front_y; \
                (back_y < size_back.y && front_y < size_front.y); ++back_y, ++front_y)
    {
        sf::Uint8* current_back  = back  + ((back_y  * size_back.x  + begin_back_x)  << 2);
        sf::Uint8* current_front = front + ((front_y * size_front.x + begin_front_x) << 2);


        for (size_t back_x = begin_back_x, front_x = begin_front_y; \
                    (back_x < size_back.x && front_x < size_front.x); ++back_x, ++front_x)
        {
            sf::Uint8 balpha = current_front[3];

            if (balpha != 0)
            {
                float alpha     = (float)((double)(balpha) * (1.0f / 255.f));
                float not_alpha = 1.0f - alpha;

                current_back[0] = lround(float(current_back[0] * not_alpha) + current_front[0] * alpha);
                current_back[1] = lround(float(current_back[1] * not_alpha) + current_front[1] * alpha);
                current_back[2] = lround(float(current_back[2] * not_alpha) + current_front[2] * alpha);
                current_back[3] = lround(float(current_back[3] * not_alpha) + current_front[3] * alpha);
            }

            current_back  += 4;
            current_front += 4;
        }
    }
}
