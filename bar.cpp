//
//  bar.cpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#include "bar.hpp"
#include <SFML/Graphics.hpp>

Bar::Bar(sf::Vector2f position,
         int height,
         int width) : myHeight(height), myWidth(width) {
    sf::Vector2f mySize(myHeight,
                        myWidth);
    rect.setSize(mySize);
    rect.setPosition(position);
}

void Bar::setPosition(int position) {
    rect.setPosition(0,
                     position);
}