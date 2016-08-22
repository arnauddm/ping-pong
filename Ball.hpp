//
//  Ball.hpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
public:
    Ball(sf::Vector2i position,
         int size,
         int speed);
    ~Ball(void);
    
    void MoveX();
    void MoveY();
    void ReverseX();
    void ReverseY();
    void restart(sf::Vector2i WindowSize);
    void setSpeed(unsigned int speed);
    int mySize,
    myDX,
    myDY,
    mySpeed;
private:
    
    sf::CircleShape ball;
    
    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override
    {
        target.draw(ball,
                    states);
    }
};
#endif /* Ball_hpp */
