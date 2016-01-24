#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

/// HEADER
#include "Entity.h"

////////////////////////////////////////
///
/// \Action CLASS
///
/// \@ Describes array of Effects for frames
///
//////////////////////////////////////////////

    //////////////////
    ///
    /// CONSTRUCTORS
    ///
    /// \@ defaults pointer to null or calls loadFromFile
    ///
    ////////////////

    mob::Action::Action () {
        eff = nullptr;
    }

    mob::Action::Action (const std::string& file) {
        gbl::Error ex;
        ex = loadFromFile(file);

        if (!ex.good())
            throw (ex);
    }

    /////////////////////
    ///
    /// DECONSTRUCTOR
    ///
    /// \@ deletes eff array
    ///
    /////////////////
    mob::Action::~Action () {
        for (unsigned cell(0); cell < frameGrid.x * frameGrid.y; ++cell)
            delete[] eff[cell];
        delete[] eff;
        delete[] cellLen;
    }

    ////////////////////
    ///
    /// LOAD & SETUP
    ///
    ////////////////

        /////////
        /// Load
        ///////
    gbl::Error mob::Action::loadFromFile (const std::string& file) {
        gbl::Error err;

            /*---- Pares file here ----*/
        err.setText("Unfinished function {Mob.h}").setLine(__LINE__);

        return err;
    }

        ///////////
        /// Setup
        /////////
    void mob::Action::setEffect (const Effect ** newEff, const std::size_t * newLen, const sf::Vector2u& grid) {
        for (unsigned n(0); n < frameGrid.x*frameGrid.y; ++n)
            delete[] eff[n];
        delete[] eff;
        delete[] cellLen;

        std::size_t len = grid.x * grid.y;
        frameGrid = grid;
        eff = new Effect * [len];
        cellLen = new std::size_t [len];

        for (unsigned cell(0); cell < len; ++cell) {
            cellLen[cell] = newLen[cell];
            eff[cell] = new Effect [newLen[cell]];

            for (unsigned cellEf(0); cellEf < newLen[cell]; cellEf++)
                eff[cell][cellEf] = newEff[cell][cellEf];
        }
    }
    void mob::Action::moveEffect (Effect ** newEff, std::size_t * newLen, const sf::Vector2u& grid) {
        frameGrid = grid;

        delete[] eff;
        delete[] cellLen;
        eff = newEff;
        cellLen = newLen;
    }

        //////////
        /// Info
        ////////
    const mob::Effect * mob::Action::getEffect (const sf::Vector2u& frame) const {
        std::size_t index = frameGrid.x*frame.x + frame.y;

        if (index > frameGrid.x*frameGrid.y) {
            gbl::Error ex;
            ex.setText("Out of range.").setLine(__LINE__).setFile(__FILE__);
            throw (ex);
        }

        return eff[index];
    }

/////////////////////////////////
///
/// \Action helper function
///
/// \@ Create easier interaction w/ private members
///
///////////////////////////

    mob::Action mob::deepCopy (const Action& actOG) {
        Action actNew = actOG;

        std::size_t gridSize = actOG.frameGrid.x * actOG.frameGrid.y;

        actNew.eff = new Effect* [gridSize];
        actNew.cellLen = new std::size_t [gridSize];

        for (unsigned cell(0); cell < gridSize; ++cell) {
            actNew.eff[cell] = new Effect [actOG.cellLen[cell]];
            actNew.cellLen[cell] = actOG.cellLen[cell];

            for (unsigned cellEf(0); cellEf < actOG.cellLen[cell]; ++cellEf)
                actNew.eff[cell][cellEf] = actOG.eff[cell][cellEf];
        }

        return actNew;
    }

//////////
///
/// \Mob CLASS
///
/// \@ Animates sprite & pair Action to the sprite
///
/////////////////

    ////////////////////
    ///
    /// CONSTRUCTORS
    ///
    /// \@ Defaults delTex = true
    /// \@ OPTIONAL: calls Mob::loadFromFile
    ///
    ////////////////

    mob::Mob::Mob () : delTex(true), texIndex(-1) {
        /*--- EMPTY ---*/
    };

    mob::Mob::Mob (const std::string& fileSpr, const sf::IntRect fDimen, const std::string& fileAct) : Mob() {
        if (!fileSpr.empty())
            loadSpriteFromFile(fileSpr, fDimen);
        if (!fileAct.empty())
            loadActionFromFile(fileAct);
    }

    ///////////////////////
    ///
    /// DECONSTRUCTOR
    ///
    /// \@ Delete texture pointed to by mobTex if delTex == true
    ///
    /////////////////
    mob::Mob::~Mob () {
        if (texIndex >= 0)
            gbl::remove(texIndex);
    }

    //////////////
    ///
    /// HELPER
    ///
    //////////

    bool mob::Mob::validFrame (const sf::Vector2u& frame) {
        sf::Vector2u grid = mobTex->getSize();
        if (frame.x > grid.x)
            return false;
        if (frame.y > grid.y)
            return false;
        return true;
    }

    ////////////////////
    ///
    /// LOAD & SETUP
    ///
    ////////////////

        //////////
        /// LOAD - sprite
        ////////
    gbl::Error mob::Mob::loadSpriteFromFile (const std::string& file, const sf::IntRect fDimen) {
        gbl::Error param;

        if (file.empty()) {
            param.setText("Directory empty.").setLine(__LINE__).setFile(__FILE__);
            return param;
        }

        int texI = gbl::makeTex(file);
        if (texI == -1) {
            param.setText("Failure allocating texture or creating texture.").setLine(__LINE__).setFile(__FILE__);
            return param;
        }

        mobTex = &gbl::getTex(texI);
        delTex = true;
        texIndex = mobTex;

        mobTex->setSmooth(true);
        mobSpr.setTexture(*mobTex);
        mobSpr.setTextureRect(fDimen);

        frameDimen.x = fDimen.width;
        frameDimen.y = fDimen.height;

        return param;
    }

    gbl::Error mob::Mob::loadSpriteFromTexture (sf::Texture* texp, sf::IntRect fDimen) {
        gbl::Error param;

        if (texp == nullptr) {
            param.setText("Null Pointer").setLine(__LINE__).setFile(__FILE__);
            return param;
        }

        mobTex = texp;
        mobSpr.setTexture(*mobTex);
        mobSpr.setTextureRect(fDimen);

        frameDimen.x = fDimen.width;
        frameDimen.y = fDimen.height;

        return param;
    }

        ///////////////////
        /// LOAD - Action
        /////////////////
    gbl::Error mob::Mob::loadActionFromFile (const std::string& file) {
        gbl::Error param;

            /*--- INCOMPLETE --*/
        param.setText("Unfinished function definition.").setLine(__LINE__).setFile(__FILE__);

        return param;
    }

    gbl::Error mob::Mob::setActionViaCopy (const Action& actOG) {
        gbl::Error param;

        try {
            moveSet = deepCopy(actOG);
        } catch (const gbl::Error& ex) {
            param = ex;
        } catch (const std::exception& ex) {
            param.setText(ex.what()).setFile(__FILE__).setLine(0);
        }

        return param;
    }

    void mob::Mob::setActionViaMove (Action&& actOG) noexcept {
        moveSet = std::move(actOG);
    }

    ////////////////
    ///
    /// Animation
    ///
    /////////////

        /////////////////////
        /// Auto-management
        ///////////////////
    void mob::Mob::animateRowF (std::size_t row) const {
        sf::IntRect frameRect = mobSpr.getTextureRect();
        sf::Vector2u gridDimen = mobTex->getSize();

        if (frameRect.top != row*frameDimen.y){
            frameRect.left = 0;
            frameRect.top = row*frameDimen.y;
        } else {
            frameRect.left = (frameRect.left+frameDimen.x) % gridDimen.x;
        }

        mobSpr.setTextureRect(frameRect);
    }

    void mob::Mob::animateRowL (std::size_t row) const {
        sf::IntRect frameRect = mobSpr.getTextureRect();
        sf::Vector2u gridDimen = mobTex->getSize();

        if (frameRect.left != 0 || frameRect.top == row*frameRect.height) {
            frameRect.left = (frameRect.left+frameDimen.x) % gridDimen.x;
        } else {
            frameRect.top = row*frameRect.height;
        }

        mobSpr.setTextureRect(frameRect);
    }

        /////////////////////////////
        /// Manual frame management
        ///////////////////////////
    sf::Vector2u mob::Mob::getFrame () const {
        sf::IntRect frameRect = mobSpr.getTextureRect();
        return sf::Vector2u( frameRect.left/frameRect.width, frameRect.top/frameRect.height );
    }

    gbl::Error mob::Mob::setFrame (const sf::Vector2u& frame) const {
        gbl::Error param;
        sf::IntRect frameRect = mobSpr.getTextureRect();
        sf::Vector2u gridDimen = mobTex->getSize();

        frameRect.top  = frame.y*frameRect.height;
        frameRect.left = frame.x*frameRect.width;

        if (frameRect.top >= int(gridDimen.y) || frameRect.top < 0 ||
                frameRect.left <= int(gridDimen.x) || frameRect.left < 0) {
            param.setText("Requested frame out of range.").setLine(__LINE__).setFile(__FILE__);
            return param;
        }

        mobSpr.setTextureRect(frameRect);
        return param;
    }

        //////////
        /// Draw
        ////////
    void mob::Mob::draw (sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(mobSpr, states);
    }

    ///////////////////////////
    ///
    /// Interaction in-game
    ///
    ///////////////////////

        ////////////
        /// Output
        //////////
    const mob::Effect* mob::Mob::getEffect (const sf::Vector2u& frame) const {
        return moveSet.getEffect(frame);
    }

    const mob::Effect* mob::Mob::getActiveEffect () const {
        sf::Vector2u frame = getFrame();
        return moveSet.getEffect(frame);
    }

        ///////////
        /// Input
        /////////
    void mob::Mob::grok (const mob::Effect& act) {
        return;
    }

#endif // MOB_H_INCLUDED
