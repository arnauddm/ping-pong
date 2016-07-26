//
//  collision_manager.cpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 28/01/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//

#include "collision_manager.hpp"

CollisionManager::CollisionManager(Ball & ball,
                                   Bar & LeftPaddle,
                                   Bar & RightPaddle,
                                   sf::Vector2i appSize) : myBall(ball), myLeftPaddle(LeftPaddle), myRightPaddle(RightPaddle) {
    
}

/*void CollisionManager::ManagerCollisionX(int SizeBall, int posXBall, int posYBall, int posYPaddle, int HeightPaddle, int WidthPaddle, int HeightApp, int WidthApp) {
 if ((posXBall + SizeBall) >= (WidthPaddle - WidthPaddle) && (posYBall + (SizeBall / 2)) > posYPaddle && (posYBall + (SizeBall / 2)) < (posYPaddle + HeightPaddle)) {
 if(posXBall == 0 || posXBall == 2000) {
 myBall.ReverseX();
 myBall.MoveX();
 }
 
 }
 
 void CollisionManager::ManagerCollisionY(int SizeBall, int posXBall, int posYBall, int posYPaddle, int HeightPaddle, int WidthPaddle, int HeightApp, int WidthApp) {
 //if (posYBall <= 0 || posYBall >= HeightPaddle) {
 if (posYBall == 0 || posYBall == 1500) {
 myBall.ReverseY();
 myBall.MoveY();
 }
 }*/