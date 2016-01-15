#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

/// STD
#include <memory>
#include <string>
#include <bitset>

// HEADER
#include "Global.h"

namespace mob {

    class  Mob;
    class  Action;
    struct Effect;

    Action deepCopy (const Action&);

        ///////////////////////
        /// \Effect     CLASS
        ///
        /// \@ class to describe action's external effects
        ///
        ///////////////////////
    struct Effect {
        Effect () {};

        enum class Type : bool {
            Physical, Mystical
        };

        bool circular;

        union {
            struct {
                sf::Vector2f origin;
                float radius;
            } hitCirlce;
            sf::IntRect hitBox;
        };

        float power;

        sf::Time duration;
    };

        //////////////////////////////////////
        ///
        /// \Action    CLASS
        ///
        /// \@ grid of dynamic array Effect
        ///
        ///////////////////////////////

    class Action {
        Effect ** eff;
        std::size_t * cellLen;
        sf::Vector2u frameGrid;

        //void clear();
    public:
        Action ();
        Action (const std::string&);
       ~Action ();

        gbl::Error loadFromFile (const std::string&);

        const Effect *       getEffect (const sf::Vector2u&) const;

        void                 setEffect  (const Effect**, const std::size_t *, const sf::Vector2u&);
        void                 moveEffect (      Effect**,       std::size_t *, const sf::Vector2u&);

        friend Action deepCopy (const Action&);
    };

        //////////////////////////////////////
        ///
        /// \Mob    CLASS
        ///
        /// \@ sprite wrapper with easier animation
        ///     \# automatic animation is limited to square sprites
        ///
        ///////////////////////////////

    class Mob : public sf::Drawable, public sf::Transformable {
        //////////////////////////
        /// Back-end Members
        mutable sf::Sprite   mobSpr;
                sf::Texture* mobTex;
        bool delTex;

        sf::Vector2u frameDimen;

        Action       moveSet;

    protected:
        //////////////////////////
        /// Helper function
        virtual bool validFrame (const sf::Vector2u&);

        //////////////////////////
        /// Ease drawing
        virtual void draw (sf::RenderTarget&, sf::RenderStates) const;

    public:
        //////////////////////////
        /// Constructor
        Mob ();
        Mob (const std::string&, const sf::IntRect, const std::string&);
        ~Mob ();

        //////////////////////////
        /// Load sprite
        gbl::Error   loadSpriteFromFile    (const std::string&, sf::IntRect);
        gbl::Error   loadSpriteFromTexture (sf::Texture*, sf::IntRect);

        //////////////////////////
        /// Actions of sprite
        gbl::Error   loadActionFromFile    (const std::string&);
        gbl::Error   setActionViaCopy      (const Action&);
        void         setActionViaMove      (Action&&) noexcept;

        //////////////////////////
        /// Animation (automatic)
        virtual void animateRowF           (std::size_t) const;           /// \Force
        virtual void animateRowL           (std::size_t) const;           /// \Loose

        //////////////////////////
        /// Animation (manual)
        sf::Vector2u getFrame              () const;
        gbl::Error   setFrame              (const sf::Vector2u&) const;

        //////////////////////////
        /// Output effects
        const Effect * getEffect           (const sf::Vector2u&) const;
        const Effect * getActiveEffect     () const;

        //////////////////////////
        /// Input effects
        virtual void grok                  (const Effect&);
    };
}

#endif // ENTITY_H_INCLUDED
