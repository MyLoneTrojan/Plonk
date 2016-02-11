#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

///STD
#include <exception>

///API
#include "Global.h"     //gbl
#include "WorldMap.h"   //wmp
#include "Zone.h"       //zn
#include "Mob.h"        //mob

namespace lvl {

    enum class Section : char {
        End, Remain, MainMenu
    };

    class Level;
    class MainMenu; //derivative of Level

    void next (Level*&);
    gbl::Error imbue (Level*&, const Section&);

        ///////////////////
        ///
        /// \Level CLASS
        ///
        ///////////////
    class Level {
    public:
        virtual Section seq (sf::Window&) =0;

        virtual Section getSect () =0;
    };

        ////////////////////////
        ///
        /// \Level DERIVITIVES
        ///
        ////////////////////
    class MainMenu : public Level {
        sf::Font verdana;

        //mob::Mob player;

        sf::Clock gmClock;
        sf::Time timePass;

        //std::vector<sf::Text>

        gbl::Error load ();

    public:
        MainMenu ();

        ////////////////////
        ///continue game
        virtual Section seq (sf::Window&);

        virtual Section getSect ();
    };
    ///\End////////////////////////////////
}

#include "LevelDef.h"

#endif // LEVEL_H_INCLUDED
