#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <fstream>
#include <string>
#include <list>

namespace wmp {

    class Map;
    class Tile;
    class Material;

    bool mapSort (const Tile&, const Tile&);

        //////////////////////////////
        ///
        /// Insertion & extraction
        ///
        //////////////////////////

        ////////////////
        /// \# material
    std::istream& operator>> (std::istream&, Material&);
    std::ostream& operator<< (std::ostream&, const Material&);

        ////////////////
        /// \# tile
    std::istream& operator>> (std::istream&, Tile&);

    struct Material {
        float hardness;
        float liquidity;
        float elasticity;

        sf::IntRect bounds;
    };

    ///TILE
    class Tile : public sf::Drawable {
    protected:
        void draw(sf::RenderTarget& renT, sf::RenderStates renS) const;

    public:
        Tile(const sf::Sprite&, const sf::Vector2i&);
        Tile();

        ~Tile();    //delete gbl texture (if possible)

        std::vector<Material> contents;

        sf::Vector2i pos;
        sf::Sprite spr;

        int texIndex;

        void save (std::streambuf*, const std::string&);

        friend std::istream& operator>> (std::istream&, Tile&);
    };

    ///MAP
    class Map : public sf::Drawable {
        mutable sf::Vector2u size;
        mutable std::list<Tile> tiles;
        mutable bool sorted;

        bool (*tile_sort) (const Tile&, const Tile&);

    protected:
        void draw (sf::RenderTarget&, sf::RenderStates) const;

    public:
        Map();
        Map(const std::string&);

        void pushTile (const Tile&);

        ///\//////////////////////////////////////
        /// \return true if succeed
        /// \param file - location of map to load
        bool loadMap (const std::string&);

        ///\//////////////////////////////////////
        /// \return true if succeed
        /// \param file - location of map to save (needs to be created)
        bool saveMap (const std::string&);
    };
}


/// DEFINITONS:
    ///HEADER
#include "WorldMapDef.h"

//  user:
//      moroga
//
//  pass:
//      blazer99

#endif // WORLDMAP_H_INCLUDED
