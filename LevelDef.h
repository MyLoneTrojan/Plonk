#ifndef LEVELDEF_H_INCLUDED
#define LEVELDEF_H_INCLUDED

///////////////////////////
///
/// \@ HELPER FUNCTIONS
///
///////////////////////

    ////////////////////
    /// \@ update Level* to point to new object determined by sec
    /// \return Errors collected (or warning of termination request)
    //////////////////
    gbl::Error lvl::imbue (Level*& lv, const Section& sec) {
        delete[] lv;

        gbl::Error err;

        switch (sec)
        {
        case Section::MainMenu:
            lv = new MainMenu;
            break;
        case Section::End: default:
            err.setText("Termination Called.");
            err.flush();
            return err;
        }

        return err;
    }

///////////////////////
///
/// \MainMenu     CLASS
///
/// \@ interface for game-portion selection
///
////////////////////////////

    /////////////////////
    ///
    /// CONSTRUCTOR
    ///
    /// \@ calls MainMenu::load; prints error if any
    ///
    //////////////
    lvl::MainMenu::MainMenu () {
        gbl::Error err = load();
        if (!err.good())
            std::cerr << "File: " << err.getFile()
                      << "\nLine: " << err.getLine()
                      << "What: " << err.what();
    }

    ////////////////////
    ///
    /// Setup / load
    ///
    ////////////////

        ///////////////////////
        /// \@ load necessary files and class for proper Menu interaction
        /// \return Error containing info on errors while loading
        /////////////////////
    gbl::Error lvl::MainMenu::load () {
        gbl::Error param;

        if (!verdana.loadFromFile("Font/verdana.ttf")) {
            param.setLine(__LINE__).setFile(__FILE__).setText("Font load error.");
            return param;
        }

        /*
        param = player.loadSpriteFromFile("Char/Main/dagger.png", sf::IntRect(0, 0, 64, 64));
        if (!param.good())
            return param;

        //Action plActs

        /*---- UNFINISHED ----*/

        return param;

    }

        //////////////////////
        /// \@ game loop
        /// \return request for next Section
        ///////////////////
    lvl::Section lvl::MainMenu::seq (sf::Window& window) {
        //Check events
            /* NOTE:
                Location allows events to be lost before time step use
             */
        for (sf::Event event; window.pollEvent(event); ) {
            switch (event.type)
            {
            case sf::Event::Closed:
                return Section::End;
            default:
                break;
            }
        }

            /* Manage time step */
        const  sf::Time frameCap  = sf::seconds(.25f);
        const  sf::Time frameTime = gmClock.restart();

        if (frameTime > frameCap)
            timePass += frameCap;
        else
            timePass += frameTime;

        for (const sf::Time dt = sf::seconds(0.05f); timePass > dt; timePass -= dt) {
            /* Update by time step */



            //Draw & process
            gbl::toDraw.clear();

            gbl::toDraw.push_back();
        }

            //No overflow errors :)
        if (timePass < sf::Time::Zero)
            timePass = sf::Time::Zero;

        return Section::Remain;
    }

    //////////////////
    ///
    /// INFO
    ///
    //////////////

    lvl::Section lvl::MainMenu::getSect () {
        return Section::MainMenu;
    }

#endif // LEVELDEF_H_INCLUDED
