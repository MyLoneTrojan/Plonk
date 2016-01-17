#ifndef ZONE_H_INCLUDED
#define ZONE_H_INCLUDED

/// API
/*--- EMPTY ---*/

/// HEADERS
#include "WorldMap.h"

/// STD
#include <vector>


namespace zn {
    struct Zone;
    struct Pool;

    std::vector<wmp::Tile> generate (const Zone&);

    struct Pool {

        std::vector<float> prob;
    }

    struct Zone {
        Pool opt;

    }
}

#endif // ZONE_H_INCLUDED
