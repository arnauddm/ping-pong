//
//  collision_manager.hpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#ifndef collision_manager_hpp
#define collision_manager_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Bar.hpp"

class CollisionManager {
public:
    CollisionManager(Ball & ball,
                     Bar & LeftPaddle,
                     Bar & RightPaddle,
                     sf::Vector2i appSize);
    
    bool ManagerCollisionX(int SizeBall,
                           int posXBall,
                           int posYBall,
                           int posYPaddle,
                           int HeightPaddle,
                           int WidthPaddle,
                           int HeightApp,
                           int WidthApp,
                           bool state_ball_x);
    
    void ManagerCollisionY(int SizeBall,
                           int posXBall,
                           int posYBall,
                           int posYPaddle,
                           int HeightPaddle,
                           int WidthPaddle,
                           int HeightApp,
                           int WidthApp);
    
private:
    Ball & myBall;
    Bar & myLeftPaddle, & myRightPaddle;
};

#endif /* collision_manager_hpp */
