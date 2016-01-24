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
    struct ZoneResource;

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
            // gbl::tex index options
        std::vector<sf::Sprite> sprOpt;
            // resource from which the fade forms
        std::vector<wmp::Material> matBlock;
            // probability of being a matBlock
        float (*chanceFunc)(std::size_t);
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
