#ifndef WORLDMAPDEF_H_INCLUDED
#define WORLDMAPDEF_H_INCLUDED

/// HEADER
#include "WorldMap.h"
#include "Global.h"

/// STD
#include <fstream>

///////////
///
/// Tile        CLASS
///
/// \@ smallest unit of a map
///     \# embeded with information on interaction w/ world
///
///////////

    ////////////////////////
    ///
    /// CONSTRUCTOR
    ///
    /// \@ set respective member to respective paramater
    ///     \# default all to default constructor
    ///
    /////////////////

    wmp::Tile::Tile() (const sf::Sprite& s, const sf::Vector2i& p) : spr(s), pos(p), texIndex(-1) {
        /*--- EMPTY --*/
    };
    wmp::Tile::Tile (), texIndex(-1) {
        /*--- EMPTY ---*/
    };

    /////////////////////
    ///
    /// DECONSTRUCTOR
    ///
    /// \@ delete global texutre (if possible)
    ///
    /////////////////

    wmp::Tile::~Tile () {
        if (texIndex >= 0)
            gbl::remove(texIndex);
    }

    /////////////////
    ///
    /// UTILITIES
    ///
    //////////////

        ////////////
        /// Draw
        //////////
    void wmp::Tile::draw(sf::RenderTarget& renT, sf::RenderStates renS) const {
        renT.draw(spr, renS);
    }

        //////////
        /// Save
        ////////
    void wmp::Tile::save (std::streambuf* outS, const std::string& texFile) {
        std::ostream outF (outS);
        const sf::Texture *    tex = spr.getTexture();
                  bool      smooth = tex->isSmooth();
                  bool    repeated = tex->isRepeated();
        const sf::IntRect& texRect = spr.getTextureRect();
        const sf::Vector2f& sprPos = spr.getPosition(),
                          sprScale = spr.getScale();

        outF << texFile.size() / sizeof(char) << texFile << smooth << repeated
             << texRect.left << texRect.top << texRect.width << texRect.height
             << sprPos.x << sprPos.y << spr.getRotation() << sprScale.x << sprScale.y
             << pos.x << pos.y << contents.size();

        for (unsigned n(0); n < contents.size(); ++n)
            outF << contents[n];
    }

//////////
///
/// Map         CLASS
///
/// \@ 2-d array of Tiles
///
///////////


    //////////////////
    ///
    /// CONSTUCTOR
    ///
    /// \@ defaults size      to 0
    /// \@ defaults sorted    to 0
    /// \@ defaults tile_sort to mapSort
    ///     \# string loads map at file
    ///
    ////////////////

    Map() : size(0,0), sorted(false), tile_sort(mapSort) {
        /*--- EMPTY ---*/
    };

    Map(const std::string& s) : Map() {
        loadMap(s);
    };


        ////////////
        /// Draw
        //////////
    void wmp::Map::draw (sf::RenderTarget& rT, sf::RenderStates rS) const {
        if (!sorted) {
            tiles.sort(tile_sort);
            sorted = true;
        }

        for (const auto& t : tiles)
            rT.draw(t);
    }

    //////////////////
    ///
    /// Load & setup
    ///
    ////////////////

        ////////////////////
        ///
        /// LOAD - from file
        ///
        //////////////////////
    bool wmp::Map::loadMap (const std::string& file_path) {
        std::ifstream file (file_path, std::ios::binary);

        if (!file.good())
            return false;

        file >> size.x
             >> size.y;

        for (unsigned n(0); n < size.x*size.y; ++n) {
            Tile buf;
            file >> buf;
            tiles.push_back(std::move(buf));
        }
        return true;
    }

        //////////////////////
        /// SETUP - add tile
        ////////////////////
    void wmp::Map::pushTile (const Tile& ti) {
        tiles.push_back(ti);
        sorted = false;
    }

    /////////////
    ///
    /// SAVE
    ///
    /// \@ save Map into file
    ///
    ////////////////
    bool wmp::Map::saveMap (const std::string& file_path) {
        std::ofstream file (file_path, std::ios::binary);

        if (!file.good())
            return false;

        file << size.x
             << size.y;

        for (auto& t : tiles)
            t.save(file.rdbuf(), "");
        return true;
    }

    ///////////////////////
    ///
    /// HELPER FUNCTIONS
    ///
    ////////////////////

        //////////////////////////
        /// \$ Map
        /// \# default sort tiles in Map
        ////////////////////////
    bool wmp::mapSort (const Tile& fr, const Tile& sc) {
        return (fr.pos.y > sc.pos.y) || (fr.pos.x > sc.pos.y) ? true : false;
    }

        ////////////////////////
        ///
        /// STREAM OPERATIONS
        ///
        /////////////////////

        ///material extraction & insertion
    std::istream& wmp::operator>> (std::istream& is, Material& m) {
        return is >> m.top >> m.bot >> m.elasticity >> m.hardness >> m.liquidity;
    }
    std::ostream& wmp::operator<< (std::ostream& os, const Material& m) {
        return os << m.top << m.bot << m.elasticity << m.hardness << m.liquidity;
    }

        ///tile extraction (insert w/ save)
    std::istream& wmp::operator>> (std::istream& is, Tile& tl) {
        sf::Texture * tex;
        {   ///Setup Texture for tile sprite
                //get file name
            std::size_t length;
            is >> length;
            char * file = new char [length];
            is.get(file, length);

                //get texture prop
            bool smooth, repeated;
            is >> smooth >> repeated;

                //create texture
            int texPos  = gbl::makeTex(file);
            tl.texIndex = texPos;
            tex = &gbl::getTex(texPos);
            delete[] file;

            tex->setRepeated(repeated);
            tex->setSmooth(smooth);
        }

        {   ///Setup Sprite for then in tile
               //get texture dimensions in sprite
            sf::IntRect texDimen;
            sf::Vector2f sprPos, scale;
            float rotation;
            is >> texDimen.left >> texDimen.top
               >> texDimen.width >> texDimen.height
               >> sprPos.x >> sprPos.y >> rotation >> scale.x >> scale.y;

                //set sprite
            tl.spr = sf::Sprite(*tex, texDimen);
            tl.spr.setPosition(sprPos);
            tl.spr.setRotation(rotation);
            tl.spr.setScale(scale);
        }

        std::size_t size = tl.contents.size();

        is >> tl.pos.x >> tl.pos.y
           >> size;

        for (unsigned n(0); n < size; ++n) {
            Material m;
            is >> m;
            tl.contents.push_back(std::move(m));
        }
        return is;
    }

#endif // WORLDMAPDEF_H_INCLUDED
