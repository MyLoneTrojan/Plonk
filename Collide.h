#ifndef COLLIDE_H_INCLUDED
#define COLLIDE_H_INCLUDED

/// API
#include <SFML/Graphics.hpp>

/// STD
#include <cmath>

/// HEADER
#include "Global.h"

namespace coll {

    inline float dot (const sf::Vector2f& a, const sf::Vector2f& b) {
        return (a.x*b.x) + (a.y*b.y);
    }

    template <class T>
    inline double length (const sf::Vector2<T>& a) {
        return (double)sqrt(a.x*a.x + a.y*a.y);
    }

    template <class T>
    inline double dist (const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return sqrt( pow(a.x-b.x, 2) + pow(a.y-b.y, 2) );
    }

    class Circle;       //Collidable circle
    class Object;       //Collidable object (VertexArray)
    class Rectangle;    //Collidable rectangle

    //Abstract class for object collision
    class Collidable {
    protected:
        struct MinMax {
            double min;
            double max;
        };

        /** \brief Project a vector onto another
         *
         * \param x - vector being projected
         * \param v - vector to be projected upon
         * \return x projected on v
         *
         */
        static sf::Vector2f proj (const sf::Vector2f& x, const sf::Vector2f& v) {
            const float c = dot(x,v) / dot(v,v);
            return sf::Vector2f(c*v.x,c*v.y);
        };

        /** \brief Check if two lines over lap (one dimensional plane)
         *
         * \param a - std::pair<double,double> with end points as doubles
         * \param b - std::pair<double,double> with end points as doubles
         * \return true if overlapping
         *
         */
        static bool isBetween (const MinMax& a, const MinMax& l) {
            return (a.min >= l.min && a.min <= l.max) || (a.max >= l.min && a.max <= l.min);
        }

        /** \brief Find minimum and maximum projections of object onto vector
         *
         * \param vector on which to project object
         * \return std::pair containing endpoints of projection (one dimensional plane)
         *
         */
        virtual Collidable::MinMax getMinMax (const sf::Vector2f& axis) const =0;


        /** \brief Find point on *this closet to given point
         *
         * \param p - point from which the distance is measured
         * \return closest point to p
         *
         **/
        virtual sf::Vector2f getMinFrom (const sf::Vector2f& p) const =0;

        /** \brief Find vector from vertex to consecutive vertex
         *
         * \param e - starting point
         * \return vector containing edge
         *
         */
        virtual sf::Vector2f getEdge (std::size_t e) const =0;

    public:
        std::size_t corners;

        friend bool Overlap (const Collidable&, const Collidable&, bool);
        friend bool Overlap (const Circle&, const Collidable&);
    };

    class Object : public Collidable, public sf::Drawable, public sf::Transformable {

        virtual sf::Vector2f getEdge (std::size_t i) const {
            const int o = i == 0 ? -1 : 1;
            sf::VertexArray current = getCurrent();
            return sf::Vector2f(current[i].position.x - current[i+o].position.x,
                                current[i].position.y - current[i+o].position.y);
        }

        virtual Collidable::MinMax getMinMax (const sf::Vector2f& axis) const {
            Collidable::MinMax minMax;
            for (unsigned int n(0); n < corners; ++n) {
                //for every vertex on this
                double projA  = length(proj( getCurrent()[n].position,axis ));
                minMax.min = (projA < minMax.min || n == 0) ? projA : minMax.min;
                minMax.max = (projA > minMax.max || n == 0) ? projA : minMax.max;
            }
            return minMax;
        }

        virtual sf::Vector2f getMinFrom (const sf::Vector2f& p) const {
            sf::VertexArray curr = getCurrent();
            sf::Vector2f    min  = curr[0].position;

            for (unsigned int i(0); i < corners; ++i)
                min = dist(curr[i].position,p) < dist(min,p) ? curr[i].position : min;
            return min;
        }

        sf::VertexArray corner;

    protected:

        virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(getCurrent(),states);
        }

        virtual sf::VertexArray getCurrent () const {
            //Declare & setup current
            sf::VertexArray current(corner);

            sf::Transform t = getTransform();

            for (unsigned int i(0); i < corners; ++i)
                current[i].position = t.transformPoint(current[i].position);
            return current;
        }

    public:
        Object (std::size_t c, sf::Color co = sf::Color::White) : corner(sf::PrimitiveType::Quads, c) {
            corners = c;
            for (unsigned int i(0); i < c; ++i)
                corner[i].color = co;
        }

        sf::Vertex& operator[] (std::size_t i) {
            return corner[i];
        }
    };

    class Rectangle : public Collidable, public sf::RectangleShape {

        virtual sf::Vector2f getEdge (std::size_t i) const {
            const int o = i == 0 ? -1 : 1;
            return sf::Vector2f(getPoint(i).x - getPoint(i+o).x,
                                getPoint(i).y - getPoint(i+o).y);
        }

        virtual Collidable::MinMax getMinMax (const sf::Vector2f& axis) const {
            Collidable::MinMax minMax;
            for (unsigned int n(0); n < getPointCount(); ++n) {
                //for every vertex on this
                double projA  = length(proj( getPoint(n),axis ));
                minMax.min = (projA < minMax.min || n == 0) ? projA : minMax.min;
                minMax.max = (projA > minMax.max || n == 0) ? projA : minMax.max;
            }
            return minMax;
        }

    protected:
        virtual sf::Vector2f getMinFrom (const sf::Vector2f& p) const {
            sf::Vector2f min = getPoint(0);

            for (unsigned int i(0); i < getPointCount(); ++i)
                min = dist(min,p) < dist(getPoint(i),p) ? min : p;
            return min;
        }
    public:
        Rectangle (const sf::Vector2f &size=sf::Vector2f(0, 0)) : sf::RectangleShape(size) {};
    };

    class Circle : public Collidable, public sf::CircleShape {
        sf::Vector2f getCenter () const {
            sf::Vector2f OG;
            OG.y = OG.x = 0;
            return getTransform().transformPoint(OG);
        }

        virtual sf::Vector2f getMinFrom (const sf::Vector2f& p) {
            const sf::Vector2f c = getCenter();
            return sf::Vector2f(c.x - p.x, c.y - p.y);
        }

    public:
        Circle(float radius=0, std::size_t pointCount=30) : sf::CircleShape(radius,pointCount) {};

        friend bool Overlap (const Circle& a, const Circle& b);
        friend bool Overlap (const Circle& a, const Collidable& b);
    };

    //FUNCTIONS
    bool Overlap (const Circle& a, const Circle& b) {
        if (dist(a.getCenter(),b.getCenter()) > a.getRadius()+b.getRadius())
            return false;
        return true;
    }

    bool Overlap (const Circle& a, const Collidable& b) {
        sf::Vector2f center = a.getCenter();
        sf::Vector2f min    = b.getMinFrom(center);
        const sf::Vector2f axis(center.x - min.x, center.y - min.y);

        Collidable::MinMax minMax [2];
        minMax[0] = a.getMinMax(axis);
        minMax[1] = b.getMinMax(axis);

        return !( !Collidable::isBetween(minMax[0],minMax[1]) &&
                  !Collidable::isBetween(minMax[1],minMax[0]) );
    }

    bool Overlap (const Collidable& a, const Circle& b) {
        return Overlap(b,a);
    }

    bool Overlap (const Collidable& a, const Collidable& b, bool repeat = true) {
        Collidable::MinMax minMax [2];

        for (unsigned int i(1); i < a.corners; ++i) {
            //Find edge
            sf::Vector2f axis = a.getEdge(i);
            //Find normal
            std::swap(axis.x,axis.y);
            axis.y *= -1;

            minMax[0] = a.getMinMax(axis);
            minMax[1] = b.getMinMax(axis);

            if ( !Collidable::isBetween(minMax[0],minMax[1]) &&
                 !Collidable::isBetween(minMax[1],minMax[0]) )
                return false;
        }

        return repeat ? Overlap(b,a,false) : true;
    }
}

#endif // COLLIDE_H_INCLUDED
