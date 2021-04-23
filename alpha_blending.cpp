#include "alpha_blending.h"

static const __m128i max = _mm_set1_epi8(255);  

static inline __m128i _mm_div255_epu16(__m128i x)
{
	// x = ((x + 1) + (x >> 8)) >> 8:
	return _mm_srli_epi16(_mm_adds_epu16(
		                  _mm_adds_epu16(x, _mm_set1_epi16(1)),
		                  _mm_srli_epi16(x, 8)), 8);
}

static __m128i _mm_scale_epu8 (__m128i x, __m128i y)
{
	// x = x * (y / 255)
	// Reorder: x = (x * y) / 255

	// Unpack x and y into 16-bit uints:
	__m128i xlo = _mm_unpacklo_epi8(x, _mm_setzero_si128());
	__m128i ylo = _mm_unpacklo_epi8(y, _mm_setzero_si128());
	__m128i xhi = _mm_unpackhi_epi8(x, _mm_setzero_si128());
	__m128i yhi = _mm_unpackhi_epi8(y, _mm_setzero_si128());

	// Multiply x with y, keeping the low 16 bits:
	xlo = _mm_mullo_epi16(xlo, ylo);
	xhi = _mm_mullo_epi16(xhi, yhi);

	// Divide by 255:
	xlo = _mm_div255_epu16(xlo);
	xhi = _mm_div255_epu16(xhi);

	// Repack the 16-bit uints to clamped 8-bit values:
	return _mm_packus_epi16(xlo, xhi);
}

void Alpha_blending(sf::Uint8* back, sf::Uint8* front, \
                    const sf::Vector2u size_back, const sf::Vector2u size_front, const sf::Vector2i shift)
{
    size_t begin_back_y  = (shift.y > 0) ? shift.y : 0;
    size_t begin_front_y = (shift.y > 0) ? 0 : -shift.y;
    size_t begin_back_x  = (shift.x > 0) ? shift.x : 0;
    size_t begin_front_x = (shift.x > 0) ? 0 : -shift.x;
    
    for (size_t back_y = begin_back_y, front_y = begin_front_y; \
                (back_y < size_back.y && front_y < size_front.y); ++back_y, ++front_y)
    {
        sf::Uint8* current_back  = back  + ((back_y  * size_back.x  + begin_back_x)  << 2);
        sf::Uint8* current_front = front + ((front_y * size_front.x + begin_front_x) << 2);

        for (size_t back_x = begin_back_x, front_x = begin_front_x; \
                    (back_x <= size_back.x - 4 && front_x <= size_front.x - 4); back_x +=4, front_x += 4)
        {
            __m128i alpha = _mm_set_epi8((unsigned char)current_front[15], (unsigned char)current_front[15], (unsigned char)current_front[15], (unsigned char)current_front[15], \
                                         (unsigned char)current_front[11], (unsigned char)current_front[11], (unsigned char)current_front[11], (unsigned char)current_front[11], \
                                         (unsigned char)current_front[7],  (unsigned char)current_front[7],  (unsigned char)current_front[7],  (unsigned char)current_front[7],  \
                                         (unsigned char)current_front[3],  (unsigned char)current_front[3],  (unsigned char)current_front[3],  (unsigned char)current_front[3]);

            __m128i not_alpha = _mm_subs_epu8(max, alpha);


            __m128i pixel_back  = _mm_set_epi8(current_back[15],  current_back[14],  current_back[13],  current_back[12],  \
                                               current_back[11],  current_back[10],  current_back[9],   current_back[8],   \
                                               current_back[7],   current_back[6],   current_back[5],   current_back[4],   \
                                               current_back[3],   current_back[2],   current_back[1],   current_back[0]);

            __m128i pixel_front = _mm_set_epi8(current_front[15], current_front[14], current_front[13], current_front[12], \
                                               current_front[11], current_front[10], current_front[9],  current_front[8],  \
                                               current_front[7],  current_front[6],  current_front[5],  current_front[4],  \
                                               current_front[3],  current_front[2],  current_front[1],  current_front[0]);

            pixel_back  = _mm_adds_epi8(_mm_scale_epu8(pixel_back, not_alpha), _mm_scale_epu8(pixel_front, alpha));

            _mm_maskmoveu_si128(pixel_back, max, reinterpret_cast<char*>(current_back));

            current_back  += 16;
            current_front += 16;
        }
    }
}