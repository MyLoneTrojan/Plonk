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
        std::vector<wmp::Tile> tileGrid;
        tileGrid.reserve(zone.grid.x * zone.grid.y);

        srand(time(NULL));

        for (std::size_t n(0); n < tileGrid.size(); ++n) {
            tileGrid.push_back( zone.znRs[rand() % zone.znRs.size()] );
        }



        return tileGrid;
    }

#endif // ZONEDEF_H_INCLUDED
