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

            tileGrid.emplace_back(zone.znRs[resIndex].sprOpt[sprIndex].first,     //sprite in question
                                  wmp::resolvePoint<int>(n, zone.grid.x));  //position in tileGrid(graphicly);
        }

            /// add alternate tiles to replace default
        for (sf::Vector2i pos; pos.y < zone.grid.y; pos.y++) {      //bottom to top by row
            bool north = pos.y <= zone.northFade;
            bool south = pos.y >= zone.grid.y - zone.southFade;

            int totalPool = 0;      // sum of pool's elements
            std::vector< std::pair<int, const ZoneResource*> > pool;

            std::vector< const std::vector<ZoneResource>* > options;

                // Append zone resource vector*-s to options
                    // then append (probability + totalPool) to pool (so the appended item's distance from prev is equal it's probablity. equal distance means probablity is maintained)
                    // then increase totalPool
            if (north) {
                options.push_back(&zone.nnRs);
                for (const ZoneResource& zr : zone.nnRs) {
                    pool.emplace_back(zr.chance(pos.y) + totalPool, &zr);
                    totalPool += zr.chance(pos.y);
                }
            }
            if (south) {
                options.push_back(&zone.snRs);
                for (const ZoneResource& zr : zone.snRs) {
                    pool.emplace_back(zr.chance(pos.y) + totalPool, &zr);
                    totalPool += zr.chance(pos.y);
                }
            }

            for (; pos.x < zone.grid.x; pos.x++) {                  //left to right by collumn
                bool west  = pos.x <= zone.eastFade;
                bool east  = pos.x >= zone.westFade;
                short pops = 0;

                    // Append zone resource vector*-s to options
                        // then append probability (+ total pool (for some reason)) to pool & increase totalPool
                if (west) {
                    options.push_back(&zone.wnRs);
                    pops++;

                    for (const ZoneResource& zr : zone.wnRs) {
                        pool.emplace_back(zr.chance(pos.x) + totalPool, &zr);
                        totalPool += zr.chance(pos.x);
                    }
                }
                if (east) {
                    options.push_back(&zone.enRs);
                    pops++;

                    for (const ZoneResource& zr : zone.enRs) {
                        pool.emplace_back(zr.chance(pos.x) + totalPool, &zr);
                        totalPool += zr.chance(pos.x);
                    }
                }

                std::size_t res =  rand() % totalPool;

                for (const auto& ch : pool) {
                    if (res <= ch.first){
                        //change with ch.second
                        wmp::Tile alt_tile;

                        std::size_t sprIndex = rand() % ch.second->sprOpt.size();
                        alt_tile.spr = ch.second->sprOpt[sprIndex].first;
                        alt_tile.texIndex = ch.second->sprOpt[sprIndex].second;

                        alt_tile.contents = ch.second->matBlock;

                        tileGrid[wmp::resolveIndex(pos, zone.grid)] = alt_tile;
                        break;
                    }
                }

                for (; pops > 0; --pops)
                    options.pop_back();
            }
        }

        return tileGrid;
    }

#endif // ZONEDEF_H_INCLUDED
