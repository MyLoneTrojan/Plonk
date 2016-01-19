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

//////////////////
///
/// FUNCTIONS
///
//////////////

        /// Use Zone to generate corresponding vector of Tile
    std::vector<wmp::Tile> generate (const Zone&);

////////////////
///
/// CLASSES
///
////////////

    struct ZoneResource {
        std::vector<int> texBlock;
        std::vector<wmp::Material> matBlock;
        float chance;
    }

    struct Zone {
        std::vector<ZoneResource> znRs;

        sf::Vector2i grid;

        int northFade;
        std::vector<ZoneResource> nnRs;

        int southFade;
        std::vector<ZoneResource> snRs;

        int eastFade;
        std::vector<ZoneResource> enRs;

        int westFade;
        std::vector<ZoneResource> wnRs;
    }
}

/// Definitions
#define "ZoneDef"

#endif // ZONE_H_INCLUDED
