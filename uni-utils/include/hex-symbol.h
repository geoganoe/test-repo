//
// Use this declaration to create a function returning the string with
//   the symbol representing the dots pattern for the byte value passed
//   as argument to the function.

//
// The declaration was created by the sho-hex-dots program after it
//   computed the information needed from the the braille pattern dots
//   in the ducet and the two arrays created to represent hex digit
//   bits to be shown
//
// The first 32 characters have been changed manually to display the
//   Unicode Control Pictures set which is a set of graphic pictures
//   for control codes that show the short form name for the control
//   character.  Thes are easier to read than the braille dot patterns
//   especially those in the first 16 characters including the 0x00
//   character which is likely the most common, and just looks like an
//   extra wide space when displayed on the screen.

#ifndef HEX_SYMBOL_H
#define HEX_SYMBOL_H

#include <cstdint>
#include <string>

const uint16_t control_pics[ 32 ] {
    0x2400, 0x2401, 0x2402, 0x2403, 0x2404, 0x2405, 0x2406, 0x2407,
    0x2408, 0x2409, 0x240a, 0x240b, 0x240c, 0x240d, 0x240e, 0x240f,
    0x2410, 0x2411, 0x2412, 0x2313, 0x2414, 0x2415, 0x2416, 0x2417,
    0x2418, 0x2419, 0x241a, 0x241b, 0x241c, 0x241d, 0x241e, 0x241f };

const uint16_t hex_byte_dots[ 256 ] {
    0x2800, 0x2880, 0x2820, 0x28a0, 0x2810, 0x2890, 0x2830, 0x28b0,
    0x2808, 0x2888, 0x2828, 0x28a8, 0x2818, 0x2898, 0x2838, 0x28b8,
    0x2840, 0x28c0, 0x2860, 0x28e0, 0x2850, 0x28d0, 0x2870, 0x28f0,
    0x2848, 0x28c8, 0x2868, 0x28e8, 0x2858, 0x28d8, 0x2878, 0x28f8,
    0x2804, 0x2884, 0x2824, 0x28a4, 0x2814, 0x2894, 0x2834, 0x28b4,
    0x280c, 0x288c, 0x282c, 0x28ac, 0x281c, 0x289c, 0x283c, 0x28bc,
    0x2844, 0x28c4, 0x2864, 0x28e4, 0x2854, 0x28d4, 0x2874, 0x28f4,
    0x284c, 0x28cc, 0x286c, 0x28ec, 0x285c, 0x28dc, 0x287c, 0x28fc,
    0x2802, 0x2882, 0x2822, 0x28a2, 0x2812, 0x2892, 0x2832, 0x28b2,
    0x280a, 0x288a, 0x282a, 0x28aa, 0x281a, 0x289a, 0x283a, 0x28ba,
    0x2842, 0x28c2, 0x2862, 0x28e2, 0x2852, 0x28d2, 0x2872, 0x28f2,
    0x284a, 0x28ca, 0x286a, 0x28ea, 0x285a, 0x28da, 0x287a, 0x28fa,
    0x2806, 0x2886, 0x2826, 0x28a6, 0x2816, 0x2896, 0x2836, 0x28b6,
    0x280e, 0x288e, 0x282e, 0x28ae, 0x281e, 0x289e, 0x283e, 0x28be,
    0x2846, 0x28c6, 0x2866, 0x28e6, 0x2856, 0x28d6, 0x2876, 0x28f6,
    0x284e, 0x28ce, 0x286e, 0x28ee, 0x285e, 0x28de, 0x287e, 0x28fe,
    0x2801, 0x2881, 0x2821, 0x28a1, 0x2811, 0x2891, 0x2831, 0x28b1,
    0x2809, 0x2889, 0x2829, 0x28a9, 0x2819, 0x2899, 0x2839, 0x28b9,
    0x2841, 0x28c1, 0x2861, 0x28e1, 0x2851, 0x28d1, 0x2871, 0x28f1,
    0x2849, 0x28c9, 0x2869, 0x28e9, 0x2859, 0x28d9, 0x2879, 0x28f9,
    0x2805, 0x2885, 0x2825, 0x28a5, 0x2815, 0x2895, 0x2835, 0x28b5,
    0x280d, 0x288d, 0x282d, 0x28ad, 0x281d, 0x289d, 0x283d, 0x28bd,
    0x2845, 0x28c5, 0x2865, 0x28e5, 0x2855, 0x28d5, 0x2875, 0x28f5,
    0x284d, 0x28cd, 0x286d, 0x28ed, 0x285d, 0x28dd, 0x287d, 0x28fd,
    0x2803, 0x2883, 0x2823, 0x28a3, 0x2813, 0x2893, 0x2833, 0x28b3,
    0x280b, 0x288b, 0x282b, 0x28ab, 0x281b, 0x289b, 0x283b, 0x28bb,
    0x2843, 0x28c3, 0x2863, 0x28e3, 0x2853, 0x28d3, 0x2873, 0x28f3,
    0x284b, 0x28cb, 0x286b, 0x28eb, 0x285b, 0x28db, 0x287b, 0x28fb,
    0x2807, 0x2887, 0x2827, 0x28a7, 0x2817, 0x2897, 0x2837, 0x28b7,
    0x280f, 0x288f, 0x282f, 0x28af, 0x281f, 0x289f, 0x283f, 0x28bf,
    0x2847, 0x28c7, 0x2867, 0x28e7, 0x2857, 0x28d7, 0x2877, 0x28f7,
    0x284f, 0x28cf, 0x286f, 0x28ef, 0x285f, 0x28df, 0x287f, 0x28ff };

std::string hex_symbol( uint16_t ch, bool use_ctl_pics = false );

#endif //HEX_SYMBOL_H
