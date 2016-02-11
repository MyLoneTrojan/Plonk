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

        /// Helps fade-in inside generate
    //void addFade (const Zone&, std::vector<wmp::Tile>&);

////////////////
///
/// CLASSES
///
////////////

        /// Contain options and probability of options for certain tiles
    struct ZoneResource {
            // gbl::tex index options with sprite
        std::vector< std::pair<sf::Sprite, std::size_t> > sprOpt; // sprite not autoset
            // resource from which the fade forms
        std::vector<wmp::Material> matBlock;
            // probability of being a this
        int (*chance)(std::size_t);
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
