#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <iostream>
#include <utility>
#include <list>

namespace gbl {
    std::list<sf::Drawable*> toDraw;

    int isLoaded (const std::string&);
    sf::Texture& getTex(std::size_t);
    template <class ... Args> int makeTex (const std::string&, Args...);

    // Variable
    struct TexLoc;
    std::vector< TexLoc > tex;

    // Classes
    class Error;

    ///\Classes
    class Error : public std::exception {
        std::string text;
        std::string file;
        int line;
        bool prob;
        bool warn;

    public:
        Error (const std::string& str, int co = 0) : text(str), line(co), prob(true) {};
        Error () : line(0), prob(false), warn(false) {};

        Error& setLine (int c) {
            prob = true;
            line = c;
            return *this;
        }
        Error& setText (const std::string& t) {
            prob = true;
            text = t;
            return *this;
        }
        Error& setFile (const std::string& f) {
            prob = true;
            file = f;
            return *this;
        }

        void flush () {
            prob = false;
        }

        bool good () const {
            return !prob || !warn;
        }
        bool fail () const {
            return prob;
        }
        bool bad () const {
            return warn;
        }

        virtual const char * what () const noexcept {
            return text.c_str();
        }
        virtual const int getLine () const noexcept {
            return line;
        }
        virtual const char * getFile () const noexcept {
            return file.c_str();
        }
    };

    struct TexLoc : std::pair<sf::Texture, std::string> {
        TexLoc(const std::string& p) : std::pair<sf::Texture, std::string>() {
            second = p;
            bad = !loadTex(p).good();
        }

        gbl::Error loadTex (const std::string& p) {
            gbl::Error param;
            if (!tex.loadFromFile(p))
                param.setLine(__LINE__).setFile(__FILE__).setText("Invalid File Name.");
            return param;
        }

        bool bad;

        sf::Texture& tex  = first;
        std::string& path = second;
    };

    // Functions
    int isLoaded (const std::string& file) {
        for (std::size_t max = tex.size(), n(0); n < max; ++n)
            if (file == tex[n].path)
                return n;
        return -1;
    }

    sf::Texture& getTex (std::size_t n) {
        return tex[n].tex;
    }

    int makeTex (const std::string& file) {
        int pos = isLoaded(file);

        if (pos != -1)
            return pos;

        tex.emplace_back(file);
        if (tex.back().bad) {
            tex.pop_back();
            return -1;
        }

        return tex.size() - 1;
    }
}

#endif // GLOBAL_H_INCLUDED

