#ifndef GLOBALDEF_H_INCLUDED
#define GLOBALDEF_H_INCLUDED

/////////////////////////
///
/// TEXTURE  HELPERS
///
/// \# Texture management
///
/////////////////////////

    ////////////////
    ///
    /// FUNCTIONS
    ///
    /////////////

        //////////////////////////////
        /// check if file is loaded
        /// \param file path
        /// \return position (-1 means not loaded)
    int gbl::isLoaded (const std::string& file) {
        int n = 0;
        for (auto& p_texloc : tex) {
            if (file == p_texloc.path)
                return n;
            ++n;
        }
        return -1;
    }

        //////////////////////////////
        /// \param position in tex
        /// \return texture of object in tex
    sf::Texture& gbl::getTex (std::size_t n) {
        return tex.at(n).tex;
    }

        //////////////////////////////
        /// \param file path of texutre to creat
        /// \param constructor args for the texture
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
    int gbl::makeTex (const std::string& file) {
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

        //////////////////////////////
        /// \param index of element to be deleted from tex
    void gbl::remove (std::size_t index) {
        tex.erase( tex.begin()+index );
    }

    //////////////
    ///
    /// CLASS - TexLoc
    ///
    //////////////

    gbl::TexLoc::TexLoc(const std::string& p) : std::pair<sf::Texture, std::string>() {
        second = p;
        bad = !loadTex(p).good();
    }

    gbl::Error gbl::TexLoc::loadTex (const std::string& p) {
        gbl::Error param;
        if (!tex.loadFromFile(p))
            param.setLine(__LINE__).setFile(__FILE__).setText("Invalid File Name.");
        return param;
    }

///////////////////
///
/// ERROR   CLASS
///
/// \@ Exception and error management
///
/////////////////

    ////////////////////
    ///
    /// CONSTRUCTORS
    ///
    /// \param str - set file as str
    /// \param co  - set line as co
    ///     \# Default -- everything zeroed
    ///     \# Other wise -- prob set as true. everything else zeroed
    ///
    ////////////////

    gbl::Error::Error (const std::string& str, int co = 0) : text(str), line(co), prob(true) {
        /*--- EMPTY ---*/
    };
    gbl::Error::Error () : line(0), prob(false), warn(false) {
        /*--- EMPTY ---*/
    };

    /////////////
    ///
    /// SETUP
    ///
    /////////

    gbl::Error& gbl::Error::setLine (int c) {
        prob = true;
        line = c;
        return *this;
    }
    gbl::Error& gbl::Error::setText (const std::string& t) {
        prob = true;
        text = t;
        return *this;
    }
    gbl::Error& gbl::Error::setFile (const std::string& f) {
        prob = true;
        file = f;
        return *this;
    }

    void gbl::Error::flush () {
        prob = false;
    }

    ///////////
    ///
    ///INFO
    ///
    ///////

        //////////////
        /// Severity
    bool gbl::Error::good () const {
        return !prob || !warn;
    }
    bool gbl::Error::fail () const {
        return prob;
    }
    bool gbl::Error::bad () const {
        return warn;
    }

        ////////////////
        /// Specificts
    const char * gbl::Error::what    () const noexcept {
        return text.c_str();
    }
    const int    gbl::Error::getLine () const noexcept {
        return line;
    }
    const char * gbl::Error::getFile () const noexcept {
        return file.c_str();
    }


#endif // GLOBALDEF_H_INCLUDED
