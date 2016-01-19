#ifndef ZONEDEF_H_INCLUDED
#define ZONEDEF_H_INCLUDED

/// Declarations
#include "Zone.h"

/////////////////////////
///
/// HELPER FUNCTIONS - Zone
///
/// \@ generate vector of Tile based on Zone's description
///
/////////////////////

    std::vector<wmp::Tile> zn::generate (const zn::Zone& zone) {
        std::vector<wmp::Tile> tileGrid (zone.grid.x * zone.grid.y);


    }

#endif // ZONEDEF_H_INCLUDED
