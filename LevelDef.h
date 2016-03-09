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

        {   /// LOAD ZONE

            zn::Zone stzn;              // used to generate parts of tiles
            zn::ZoneResource buffZR;    // peice of stzn
            const sf::Vector2i tileSize (5,5);


                /* push sprite */
            sf::Sprite buffSpr;         // sub-peice of buffZR
            buffSpr.setTextureRect(sf::IntRect(tileSize.x, tileSize.y, 0, 0)); //may be invalid .*. may need texture
            buffSpr.setColor(sf::Color::Cyan);

            buffZR.sprOpt.emplace_back(buffSpr, -1);

                /* Push materials */
            wmp::Material buffM;        // sub-peice of buffZR
            buffM.hardness   = 0;
            buffM.elasticity = 0;
            buffM.liquidity  = 0;
            buffM.bounds = sf::IntRect(5,5,0,0);

            buffZR.matBlock.push_back(buffM);

                /* set function pointer */
            buffZR.chance = [](std::size_t) { return 100; };

                /* add to stzn (zn::Zone) */
            stzn.znRs.push_back(buffZR);

            buffZR.sprOpt[0].first.setColor(sf::Color::Magenta);

            stzn.nnRs.push_back(buffZR);
            stzn.northFade = 5;

            auto tileZone = zn::generate(stzn);

            for (auto& tz : tileZone)
                worldMap.addTile(tz);
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
