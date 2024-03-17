#include <math.h>
#include "Hitbox.h"

namespace std {
    template <typename T>
    const T& clamp(const T& value, const T& min, const T& max) 
    {
        return (value < min) ? min : (value > max) ? max : value;
    }
}

bool HitboxBoxCircle(const Pos& _pos1, const Pos& _pos2, const Pos& _circlepos, int _radius)
{
    int closestX = std::clamp(_circlepos.x_, _pos1.x_, _pos2.x_);
    int closestY = std::clamp(_circlepos.y_, _pos1.y_, _pos2.y_);

    int deltaX = _circlepos.x_ - closestX;
    int deltaY = _circlepos.y_ - closestY;

    return (deltaX * deltaX + deltaY * deltaY) <= (_radius * _radius);
}

	//return !(thisBottom < otherTop || thisTop > otherBottom || thisRight < otherLeft || thisLeft > otherRight)