#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

/// HEADERS
#include "Global.h"

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <fstream>
#include <string>
#include <set>

namespace wmp {

    class Map;
    class Tile;
    class Material;

        /// map helper function
    bool mapSort (const Tile&, const Tile&);

        /// general helper function
            // index to point
    template <class V_TYPE>
    sf::Vector2<V_TYPE> resolvePoint (V_TYPE, V_TYPE);
            // point to index
    template <class V_TYPE>
    V_TYPE resolveIndex (sf::Vector2<V_TYPE>, sf::Vector2<V_TYPE>);

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

        void save (std::streambuf*, const std::string&) const;

        friend std::istream& operator>> (std::istream&, Tile&);
    };

    ///MAP
    //template <bool (* KEY_COMPARE) (const Tile&, const Tile&)>   //KEY_COMPARE -> strick weak ordering for the tiles std::set
    class Map : public sf::Drawable {
            // size of the grid: width and height
        sf::Vector2u size;
            // tiles held linearly and in order of drawing (FIFO)
        std::set<Tile, bool(*)(const Tile&, const Tile&)> tiles;

    protected:
            // SFML implementation
        void draw (sf::RenderTarget&, sf::RenderStates) const;

    public:
        Map();
        Map(const std::string&);

        /////////////////////////////////////////////////
        ///
        /// MANIPULATION of std::set tiles
        ///
        ////////////////////////////////////////////////

            ////////////
            /// INSERT
            //////////
                /// \@ add tile in its sorted position within tiles
        void addTile  (const Tile&);
                /// \@ std::move paramater to tiles
        void moveTileSet (std::set<Tile, bool(*)(const Tile&, const Tile&)>&&);

            //////////
            /// Find - return iterator to item equivilent to the parameter (with const variant)
            ////////
        std::set<Tile>::iterator find (const Tile&) const;
        std::set<Tile>::iterator find (const Tile&);

        /////////////////////////
        ///
        /// FILE MANIPULATION
        ///
        /////////////////////

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
