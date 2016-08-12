//
//  Ball.cpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#include "Ball.hpp"

Ball::Ball(sf::Vector2i position,
           int size,
           int speed) : mySize(size), myDX(speed), myDY(speed), mySpeed(speed) {
    ball.setRadius(mySize);
    ball.setPosition(position.x, position.y);
}

void Ball::MoveX() {
    /*for (int i(0) ; i != myDX ; i++) {
        ball.move(1, 0);
    }*/
    ball.move(myDX, 0);
}

void Ball::MoveY() {
    /*for (int j(0) ; j != myDY ; j++) {
        ball.move(0, 1);
    }*/
    ball.move(0, myDY);
}

void Ball::ReverseX() {
    myDX *= -1;
}

void Ball::ReverseY() {
    myDY *= -1;
}

void Ball::restart(sf::Vector2i WindowSize) {
    ball.setPosition(WindowSize.x / 2, WindowSize.y / 2);
}

void Ball::setSpeed(unsigned int speed) {
    mySpeed = speed;
    myDX = mySpeed;
    myDY = mySpeed;
}