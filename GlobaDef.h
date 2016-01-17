#ifndef GLOBADEF_INCLUDED
#define GLOBADEF_INCLUDED


///////////////////////////
///
/// ERROR       CLASS
///
/// \@ contain error for exceptions and the like
///
/////////////////////

    ///////////////////
    ///
    /// CONSTRUCTOR
    ///
    /// \@ optional file file and line set in constructor
    ///     \# default set line, prob, and warn to 0
    ///
    ///////////////

    gbl::Error::Error() (const std::string& str, int co = 0) : text(str), line(co), prob(true) {
        /*--- EMPTY ---*/
    };

    gbl::Error () : line(0), prob(false), warn(false) {
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

        ////////////////
        /// pass good()
    void gbl::Error::flush () {
        prob = false;
    }

    ///////////////////
    ///
    /// INFORMATION
    ///
    ///////////////

        ////////////
        /// Status
        //////////
    bool gbl::Error::good () const {
        return !prob || !warn;
    }

    bool gbl::Error::fail () const {
        return prob;
    }

    bool gbl::Error::bad  () const {
        return warn;
    }

        ///////////
        /// Print
        /////////
    virtual const char * gbl::Error::what    () const noexcept {
        return text.c_str();
    }

    virtual const int    gbl::Error::getLine () const noexcept {
        return line;
    }

    virtual const char * gbl::Error::getFile () const noexcept {
        return file.c_str();
    }


///////////////////////////
///
/// TexLoc      CLASS
///
/////////////////////

    gbl::TexLoc::TexLoc (const std::string& file_path) : /*std::pair<sf::Texture, std::string>()*/ {
        second = file_path;
        bad = !loadTex(file_path).good();
    }

    gbl::Error gbl::TexLoc::loadTex (const std::string& p) {
        gbl::Error param;
        if (!tex.loadFromFile(p))
            param.setLine(__LINE__).setFile(__FILE__).setText("Invalid File Name.");
        return param;
    }

////////////////////////////
///
/// HELPER      FUNCTIONS
///
/// \@ Manage Tex (remove or reduce redundant textures)
///
//////////////////////

        //////////////////////////////
        /// check if file is loaded
        /// \param file path
        /// \return position (-1 means not loaded)
    int gbl::isLoaded (const std::string& file) {
        for (std::size_t max = tex.size(), n(0); n < max; ++n)
            if (file == tex[n].path)
                return n;
        return -1;
    }

        //////////////////////////////
        /// \param position in tex
        /// \return texture of object in tex
    sf::Texture& getTex (std::size_t n) {
        return tex[n].tex;
    }

        //////////////////////////////
        /// \param file path of texutre to creat
        /// \param constructor args for the texture
        ///     \# if texture with the same source file is found, then its position is returned
        ///
        /// \return position of created object in tex
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

#endif // GLOBADEF_INCLUDED
