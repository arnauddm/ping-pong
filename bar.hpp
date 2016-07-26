//
//  bar.hpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#ifndef bar_hpp
#define bar_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Bar : public sf::Drawable {
public:
    Bar(sf::Vector2f position,
        int height,
        int width);
    
    void setPosition(int position);
    
private:
    int myHeight, myWidth;
    
    sf::RectangleShape rect;
    
    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override
    {
        target.draw(rect,
                    states);
    }
};

#endif /* bar_hpp */
