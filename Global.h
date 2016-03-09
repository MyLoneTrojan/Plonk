#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <iostream>
#include <vector>
#include <utility>
#include <list>

namespace gbl {

class  Error;
struct TexLoc;
struct TexPos;

struct texPos {
    std::list<TexLoc>::iterator list_iter;

};


/////////////
///
/// DRAW
///
/////////

    std::vector<sf::Drawable*> toDraw;

///////////////
///
/// TEXTURE
///
/// \@ remove reuse of textures
///
/////////////////

    ////////////////
    ///
    /// OBJECTS
    ///
    ////////////

    std::list< TexLoc > tex;
    typedef std::list<TexLoc>::iterator list_iter;

    /////////////////
    ///
    /// FUCNTIONS
    ///
    //////////////

        //////////////////////////////
        /// check if file is loaded
        /// \param file path
        /// \return position (-1 means not loaded)
    list_iter isLoaded (const std::string&);

        //////////////////////////////
        /// \param position in tex
        /// \return texture of object in tex
    sf::Texture& getTex(list_iter);

        //////////////////////////////
        /// \param file path of texutre to creat
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
    list_iter makeTex (const std::string&);

        //////////////////////////////
        /// \param index of element to be deleted from tex
    void remove (list_iter);

    ////////////////
    ///
    /// CLASSES
    ///
    ////////////

        //////////////////////////////////
        ///Pair of texture and source file
    struct TexLoc : std::pair<sf::Texture, std::string> {   //Remove std::pair inheritence?
        TexLoc(const std::string&);

        gbl::Error loadTex (const std::string&);

        bool bad;

        sf::Texture& tex  = first;
        std::string& path = second;
    };

////////////
///
/// ERROR
///
/// \@ exception and error management
///
/////////////

    class Error : public std::exception {
        std::string text;
        std::string file;
        int line;
        bool prob;
        bool warn;

    public:
        Error (const std::string&, int);
        Error ();

        Error& setLine (int c);
        Error& setText (const std::string& t);
        Error& setFile (const std::string& f);

        void flush ();

        bool good () const;
        bool fail () const;
        bool bad () const;

        virtual const char * what () const noexcept;
        virtual const int getLine () const noexcept;
        virtual const char * getFile () const noexcept;
    };
}

/// Definitions
#include "GlobalDef.h"

#endif // GLOBAL_H_INCLUDED

