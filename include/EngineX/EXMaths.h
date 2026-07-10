#ifndef EXMATHS_H
#define EXMATHS_H

#include "types.h"

// EXMaths has to be reconstructued since its not included in dwarf ig

// We are ASSUMING that the regular x_base and so on structs are the same as the ones defined in EXMaths.
// We only have dwarf for the ones NOT defined in ExMaths. In fact, take everything here with multiple grains of salt
// as we have NO info on ExMaths.

struct EXMaths
{
    struct x_base
    {
        static unsigned int broadcast_field;
        static unsigned int valid_fields;
        /* 0x0 */ vec128_t vec128;
    };

    struct y_base
    {
        static unsigned int broadcast_field;
        static unsigned int valid_fields;
        /* 0x0 */ vec128_t vec128;
    };

    struct z_base
    {
        static unsigned int broadcast_field;
        static unsigned int valid_fields;
        /* 0x0 */ vec128_t vec128;
    };

    struct w_base
    {
        static unsigned int broadcast_field;
        static unsigned int valid_fields;
        /* 0x0 */ vec128_t vec128;
    };

    struct xyzw_base
    {
        static unsigned int broadcast_field;
        static unsigned int valid_fields;
        /* 0x0 */ vec128_t vec128;
    };
};

#endif // EXMATHS_H
