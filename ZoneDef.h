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

    std::vector<wmp::Tile> zn::generate (const Zone& zone) {
        std::vector<wmp::Tile> tileGrid;
        tileGrid.reserve(zone.grid.x * zone.grid.y);

        srand(time(NULL)); //seed rand()

            /// add base layer of default resource
        for (std::size_t n(0); n < tileGrid.size(); ++n) {
            std::size_t resIndex = rand() % zone.znRs.size();
            std::size_t sprIndex = rand() % zone.znRs[resIndex].sprOpt.size();

            tileGrid.emplace_back(zone.znRs[resIndex].sprOpt[sprIndex], sf::Vector2i{n % zone.grid.x, (n-y) / zone.grid.x});
        }

        for (sf::Vector2i pos; pos.y < zone.grid.y; pos.y++) {
            bool north = pos.y <= zone.northFade;
            bool south = pos.y >= zone.grid.y - zone.southFade;

            int totalPool = 0;
            std::vector<int> pool;

            std::vector< std::vector<ZoneResource>* > options;

            if (north) {
                options.push_back(zone.nnRs);
                for (ZoneResource& zr : zone.nnRs) {
                    pool.push_back(zr.chance(pos.y) + totalPool);
                    totalPool += zr.chance(pos.y);
                }
            }
            if (south) {
                options.push_back(zone.snRs);
                for (ZoneResource& zr : zone.snRs) {
                    pool.push_back(zr.chance(pos.y) + totalPool);
                    totalPool += zr.chance(pos.y);
                }
            }

            for (; pos.x < zone.grid.x; pos.x++) {
                bool west  = pos.x <= zone.eastFade;
                bool east  = pos.x >= zone.westFade;
                short pops = 0;

                if (west) {
                    options.push_back(zone.wnRs);
                    pops++;

                    for (ZoneResource& zr : zone.wnRs) {
                        pool.push_back(zr.chance(pos.x) + totalPool);
                        totalPool += zr.chance(pos.x);
                    }
                }
                if (east) {
                    options.push_back(zone.enRs);
                    pops++;

                    for (ZoneResource& zr : zone.enRs) {
                        pool.push_back(zr.chance(pos.x) + totalPool);
                        totalPool += zr.chance(pos.x);
                    }
                }

                std::size_t res =  rand() % totalPool;

                for (const int& ch : pool) {
                    if (ch)
                }

                for (; pops > 0; --pops)
                    options.pop_back();
            }
        }

        return tileGrid;
    }

#endif // ZONEDEF_H_INCLUDED
