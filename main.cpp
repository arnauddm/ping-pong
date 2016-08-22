//
//  main.cpp
//  ping-pong
//
//  Created by Arnaud DE MATTEIS on 22/07/2016.
//  Copyright © 2016 Arnaud DE MATTEIS. All rights reserved.
//
//  Developped with XCode on a
//  MacBookPro with 16Gb of RAM
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Ball.hpp"
#include "bar.hpp"
#include "collision_manager.hpp"

//déclaration des fonctions --- prototypage
void menu(sf::RenderWindow & app,
          const sf::Vector2i & WINDOW_SIZE,
          sf::Event & event,
          const sf::Font & font,
          const int BALL_SIZE_INIT,
          const int BALL_SPEED_INIT,
          const int SPEED_PADDLE_INIT,
          const int PADDLE_HEIGHT_INIT,
          const int PADDLE_WIDTH_INIT,
          const sf::Vector2i BALL_POS_INIT,
          const sf::Vector2f LEFT_PADDLE_POS_INIT,
          const sf::Vector2f RIGHT_PADDLE_POS_INIT,
          const bool state_bool_x,
          const bool state_bool_y);

void game(sf::RenderWindow& app,
          sf::Event event,
          sf::Font font,
          sf::Vector2i WINDOW_SIZE,
          sf::Vector2i BALL_POS_INIT,
          int BALL_SPEED,
          int BALL_SIZE,
          sf::Vector2f LEFT_PADDLE_POS_INIT,
          sf::Vector2f RIGHT_PADDLE_POS_INIT,
          int PADDLE_WIDTH,
          int PADDLE_HEIGHT,
          int SPEED_PADDLE_INIT,
          bool state_ball_x,
          bool state_ball_y,
          const int score_limit);

void parameter(sf::RenderWindow & app,
               sf::Event & event,
               const sf::Vector2i & WINDOW_SIZE,
               const sf::Font & font,
               int ballSpeed,
               int ballSize,
               int paddleHeight,
               int paddleWidth,
               int speedPaddle,
               const sf::Vector2i BALL_POS_INIT,
               const sf::Vector2f LEFT_PADDLE_POS_INIT,
               const sf::Vector2f RIGHT_PADDLE_POS_INIT,
               const bool state_ball_x,
               const bool state_ball_y);

sf::Text createText(const sf::String & content,
                    const sf::Vector2f & position,
                    const sf::Font & font,
                    int size);

sf::String toString(int value);

void setSuccess(sf::Text & text);

void setInactive(sf::Text & text);

void setDanger(sf::Text & text);

void setYellow(sf::Text & text);

void setWarning(sf::Text & text);

sf::String getTimer(unsigned long timeStart, unsigned long nowTime);

sf::String setTwoDigits(unsigned int number);

int getRand(int mini,
            int maxi);


/*  -------------------------------------------------
    *************************************************
 
                FONCTION MAIN
 
    *************************************************
    -------------------------------------------------
*/

int main(int argc, char const *argv[]) {
    //initialisation du random pour les nombres aléatoires
    srand(time(NULL));
    
    //déclaration des variables "constantes" de paramètres de jeu
    const int   BALL_SIZE_INIT(50),
    BALL_SPEED_INIT(1),
    SPEED_PADDLE_INIT(100),
    PADDLE_HEIGHT_INIT(500),
    PADDLE_WIDTH_INIT(20);
    
    const sf::Vector2i  WINDOW_SIZE(2500, 1500),
    BALL_POS_INIT(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
    
    const sf::Vector2f  LEFT_PADDLE_POS_INIT(0, WINDOW_SIZE.y / 2 - PADDLE_WIDTH_INIT),
    RIGHT_PADDLE_POS_INIT(WINDOW_SIZE.x - PADDLE_WIDTH_INIT, WINDOW_SIZE.y / 2 - PADDLE_HEIGHT_INIT / 2);
    
    bool state_ball_x(getRand(0, 1)), state_balle_y(getRand(0, 1));
    
    //variable concernant le réseau
    const unsigned short port(3600);
    const sf::IpAddress adress("127.0.0.1"); //no place lol
    
    
    //définition de la police
    sf::Font font;
    if(!font.loadFromFile("/Users/arnaud/Documents/dev/sfml/projet_tut/ping-pong/ping-pong/font.ttf")) {
        std::cout << "Erreur du chargement de la police...Fermeture du jeu !" << std::endl;
        return EXIT_FAILURE;
    }
    
    //paramètre de sélection du joueur :
    //  true : joueur 1 donc gère les calculs
    //  false
    const bool superPlayer(true);
    
    //création de la fenêtre
    sf::RenderWindow app(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Ping - Pong", sf::Style::Default);
    sf::Event event;
    
    //création des éléments réseaux
    if(superPlayer) {
        sf::TcpListener server;
        sf::TcpSocket socket;
        server.listen(port);
        server.accept(socket);
    }
    else {
        sf::TcpSocket socket;
        socket.connect(adress, port);
    }
    
    menu(app,
         WINDOW_SIZE,
         event,
         font,
         BALL_SIZE_INIT,
         BALL_SPEED_INIT,
         SPEED_PADDLE_INIT,
         PADDLE_HEIGHT_INIT,
         PADDLE_WIDTH_INIT,
         BALL_POS_INIT,
         LEFT_PADDLE_POS_INIT,
         RIGHT_PADDLE_POS_INIT,
         state_ball_x,
         state_balle_y);
    
    app.close();
    
    return 0;
}

/*  -------------------------------------------------
    *************************************************
 
                FONCTION TEXTE

    *************************************************
    -------------------------------------------------
*/

sf::Text createText(const sf::String & content,
                    const sf::Vector2f & position,
                    const sf::Font & font,
                    int size) {
    sf::Text text;
    text.setString(content);
    text.setPosition(position.x, position.y);
    text.setFont(font);
    text.setCharacterSize(size);
    return text;
}

/*  -------------------------------------------------
    *************************************************
 
                FONCTION COULEUR
 
    *************************************************
    -------------------------------------------------
*/

void setSuccess(sf::Text & text) {
    text.setColor(sf::Color(46, 204, 113));
}

void setInactive(sf::Text & text) {
    text.setColor(sf::Color(127, 140, 141));
}

void setDanger(sf::Text & text) {
    text.setColor(sf::Color::Red);
}

void setWarning(sf::Text & text) {
    text.setColor(sf::Color(211, 84, 0));
}

void setYellow(sf::Text & text) {
    text.setColor(sf::Color(243, 156, 18));
}


/*  -------------------------------------------------
    *************************************************
 
                    FONCTION MENU
 
    *************************************************
    -------------------------------------------------
*/


void menu(sf::RenderWindow & app,
          const sf::Vector2i & WINDOW_SIZE,
          sf::Event & event,
          const sf::Font & font,
          const int BALL_SIZE_INIT,
          const int BALL_SPEED_INIT,
          const int SPEED_PADDLE_INIT,
          const int PADDLE_HEIGHT_INIT,
          const int PADDLE_WIDTH_INIT,
          const sf::Vector2i BALL_POS_INIT,
          const sf::Vector2f LEFT_PADDLE_POS_INIT,
          const sf::Vector2f RIGHT_PADDLE_POS_INIT,
          const bool state_bool_x,
          const bool state_bool_y) {
    
    //variable de choix au niveau du menu
    int choice(1);
    
    sf::Text title = createText("Ping - Pong",
                                sf::Vector2f(WINDOW_SIZE.x / 3, WINDOW_SIZE.y / 30),
                                font,
                                200);
    setWarning(title);
    
    
    sf::Text subTitle = createText("Menu",
                                   sf::Vector2f(WINDOW_SIZE.x / 2.3, WINDOW_SIZE.y / 6),
                                   font,
                                   150);
    setYellow(subTitle);
    
    //afficher dans le menu
    sf::Text jouer = createText("Jouer",
                                sf::Vector2f(WINDOW_SIZE.x / 2.3, WINDOW_SIZE.y / 2.5),
                                font,
                                100);
    
    sf::Text quitter = createText("Quitter",
                                  sf::Vector2f(WINDOW_SIZE.x / 2.3, WINDOW_SIZE.y / 2),
                                  font,
                                  100);
    
    //message afficher lorque l'on quitte
    sf::Text soon = createText("A bientot",
                               sf::Vector2f(WINDOW_SIZE.x / 1.4, WINDOW_SIZE.y / 1.2),
                               font,
                               200);
    setDanger(soon);
    
    //variable de contrôle de la structure du jeu
    bool running(true);
    
    while(running) {
        while(app.pollEvent(event)) {
            
            /****************************
             APPUI SUR LES TOUCHES
             ***************************/
            //on vérifie tous les évènements émis par la fenêtre / éléments extérieurs
            //évènement concernant la navigation dans le menu
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                choice--;
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                choice++;
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                switch (choice) {
                    case 1:
                        parameter(app,
                                  event,
                                  WINDOW_SIZE,
                                  font,
                                  BALL_SPEED_INIT,
                                  BALL_SIZE_INIT,
                                  PADDLE_HEIGHT_INIT,
                                  PADDLE_WIDTH_INIT,
                                  SPEED_PADDLE_INIT,
                                  BALL_POS_INIT,
                                  LEFT_PADDLE_POS_INIT,
                                  RIGHT_PADDLE_POS_INIT,
                                  state_bool_x,
                                  state_bool_y);
                        break;
                        
                    case 2: //fermeture de la fermeture
                        app.clear();
                        app.draw(soon);
                        app.display();
                        sleep(2);
                        running = false;
                        break;
                    default:
                        break;
                }
            }
            
            //test concernant les choix...
            switch (choice) {
                case 0:
                    choice = 1;
                    break;
                    
                case 1:
                    setSuccess(jouer);
                    setInactive(quitter);
                    break;
                    
                case 2:
                    setInactive(jouer);
                    setDanger(quitter);
                    break;
                    
                case 3:
                    choice = 2;
                default:
                    break;
            }
            
            app.clear();
            app.draw(title);
            app.draw(subTitle);
            app.draw(jouer);
            app.draw(quitter);
            app.display();
        }
    }
}

/*  -------------------------------------------------
    *************************************************
 
                FONCTION PARAMÈTRES
 
    *************************************************
    -------------------------------------------------
*/

void parameter(sf::RenderWindow & app,
               sf::Event & event,
               const sf::Vector2i & WINDOW_SIZE,
               const sf::Font & font,
               int ballSpeed,
               int ballSize,
               int paddleHeight,
               int paddleWidth,
               int speedPaddle,
               const sf::Vector2i BALL_POS_INIT,
               const sf::Vector2f LEFT_PADDLE_POS_INIT,
               const sf::Vector2f RIGHT_PADDLE_POS_INIT,
               const bool state_ball_x,
               const bool state_ball_y) {
    
    //variable de contrôle de la structure
    bool running(true);
    
    int points(10);
    
    std::string valeur(std::to_string(ballSize));
    sf::Text tailleBalle = createText("Taille de la balle :    " + toString(ballSize),
                                      sf::Vector2f(WINDOW_SIZE.x / 4, WINDOW_SIZE.y / 3),
                                      font,
                                      100);
    
    sf::Text taillePaddle = createText("Taille des raquettes :    " + toString(paddleHeight),
                                       sf::Vector2f(WINDOW_SIZE.x / 5, WINDOW_SIZE.y / 2.5),
                                       font,
                                       100);
    
    sf::Text vitesseBalle = createText("Vitesse de la balle :     " + toString(ballSpeed),
                                       sf::Vector2f(WINDOW_SIZE.x / 5, WINDOW_SIZE.y / 2.1),
                                       font,
                                       100);
    
    sf::Text nombrePoints = createText("Nombres de points :    " + toString(points),
                                       sf::Vector2f(WINDOW_SIZE.x / 5, WINDOW_SIZE.y / 1.8),
                                       font,
                                       100);
    
    sf::Text jouer = createText("Jouer",
                                sf::Vector2f(WINDOW_SIZE.x / 2.3, WINDOW_SIZE.y / 1.5),
                                font,
                                100);
    
    sf::Text retour = createText("Retour",
                                 sf::Vector2f(WINDOW_SIZE.x / 2.3, WINDOW_SIZE.y / 1.2),
                                 font,
                                 100);
    
    //variable concernant les choix
    int choice(1);
    
    while (running) {
        while (app.pollEvent(event)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                choice--;
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                choice++;
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                switch (choice) {
                    case 1:
                        ballSize -= 5;
                        tailleBalle.setString("Taille de la balle :    " + toString(ballSize));
                        break;
                        
                    case 2:
                        paddleHeight -= 10;
                        taillePaddle.setString("Taille des raquettes :    " + toString(paddleHeight));
                        break;
                        
                    case 3:
                        ballSpeed--;
                        vitesseBalle.setString("Vitesse de la balle :     " + toString(ballSpeed));
                        break;
                        
                    case 4:
                        points--;
                        nombrePoints.setString("Nombres de points :    " + toString(points));
                        break;
                        
                    default:
                        break;
                }
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                switch (choice) {
                    case 1:
                        ballSize += 5;
                        tailleBalle.setString("Taille de la balle :    " + toString(ballSize));
                        break;
                        
                    case 2:
                        paddleHeight += 10;
                        taillePaddle.setString("Taille des raquettes :    " + toString(paddleHeight));
                        break;
                        
                    case 3:
                        ballSpeed++;
                        vitesseBalle.setString("Vitesse de la balle :     " + toString(ballSpeed));
                        break;
                        
                    case 4:
                        points++;
                        nombrePoints.setString("Nombres de points :    " + toString(points));
                        break;
                        
                    default:
                        break;
                }
                
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                switch (choice) {
                    case 5:
                        game(app,
                             event,
                             font,
                             WINDOW_SIZE,
                             BALL_POS_INIT,
                             ballSpeed,
                             ballSize,
                             LEFT_PADDLE_POS_INIT,
                             RIGHT_PADDLE_POS_INIT,
                             paddleWidth,
                             paddleHeight,
                             speedPaddle,
                             state_ball_x,
                             state_ball_y,
                             points);
                        break;
                        
                    case 6:
                        running = false;
                        break;
                        
                    default:
                        break;
                }
            }
            
            
            //test des différents choix
            switch (choice) {
                case 0:
                    choice = 1;
                    break;
                    
                case 1:
                    setSuccess(tailleBalle);
                    setInactive(taillePaddle);
                    setInactive(vitesseBalle);
                    setInactive(nombrePoints);
                    setInactive(jouer);
                    setInactive(retour);
                    break;
                    
                case 2:
                    setInactive(tailleBalle);
                    setSuccess(taillePaddle);
                    setInactive(vitesseBalle);
                    setInactive(nombrePoints);
                    setInactive(jouer);
                    setInactive(retour);
                    break;
                    
                case 3:
                    setInactive(tailleBalle);
                    setInactive(taillePaddle);
                    setSuccess(vitesseBalle);
                    setInactive(nombrePoints);
                    setInactive(jouer);
                    setInactive(retour);
                    break;
                    
                case 4:
                    setInactive(tailleBalle);
                    setInactive(taillePaddle);
                    setInactive(vitesseBalle);
                    setSuccess(nombrePoints);
                    setInactive(jouer);
                    setInactive(retour);
                    break;
                    
                case 5:
                    setInactive(tailleBalle);
                    setInactive(taillePaddle);
                    setInactive(vitesseBalle);
                    setInactive(nombrePoints);
                    setSuccess(jouer);
                    setInactive(retour);
                    break;
                    
                case 6:
                    setInactive(tailleBalle);
                    setInactive(taillePaddle);
                    setInactive(tailleBalle);
                    setInactive(vitesseBalle);
                    setInactive(nombrePoints);
                    setInactive(jouer);
                    setDanger(retour);
                    break;
                    
                case 7:
                    choice = 1;
                    break;
                    
                default:
                    break;
            }
            
        }
        
        app.clear();
        app.draw(tailleBalle);
        app.draw(taillePaddle);
        app.draw(vitesseBalle);
        app.draw(nombrePoints);
        app.draw(jouer);
        app.draw(retour);
        app.display();
    }
}

/*  -------------------------------------------------
    *************************************************
 
            FONCTION CONVERSION
 
    *************************************************
    -------------------------------------------------
*/

sf::String toString(int value) {
    std::string valeur(std::to_string(value));
    return sf::String(valeur);
}

/*  -------------------------------------------------
    *************************************************
 
                FONCTION GAME
 
    *************************************************
    -------------------------------------------------
*/

//fonction concernant la partie (gère et affiche)
void game(sf::RenderWindow& app,
          sf::Event event,
          sf::Font font,
          sf::Vector2i WINDOW_SIZE,
          sf::Vector2i BALL_POS_INIT,
          int BALL_SPEED,
          int BALL_SIZE,
          sf::Vector2f LEFT_PADDLE_POS_INIT,
          sf::Vector2f RIGHT_PADDLE_POS_INIT,
          int PADDLE_WIDTH,
          int PADDLE_HEIGHT,
          int SPEED_PADDLE_INIT,
          bool state_ball_x,
          bool state_ball_y,
          const int score_limit) {
    
    //déclaration des différentes variables
    int posXBall(BALL_POS_INIT.x), posYBall(BALL_POS_INIT.y);
    int posXLeftPaddle(LEFT_PADDLE_POS_INIT.x), posYLeftPaddle(LEFT_PADDLE_POS_INIT.y);
    int posXRightPaddle(RIGHT_PADDLE_POS_INIT.x), posYRightPaddle(RIGHT_PADDLE_POS_INIT.y);
    
    //variable de score
    int score1(0), score2(0);
    
    //création des différents objets
    Ball ball(BALL_POS_INIT, BALL_SIZE, BALL_SPEED);
    Bar LeftPaddle(LEFT_PADDLE_POS_INIT, PADDLE_WIDTH, PADDLE_HEIGHT);
    Bar RightPaddle(RIGHT_PADDLE_POS_INIT, PADDLE_WIDTH, PADDLE_HEIGHT);
    
    //variable concernant le nombre de bounce
    int counterBounce(0);
    
    
    //creation de la musique
    sf::Music musique;
    if(!musique.openFromFile("/Users/arnaud/Documents/dev/sfml/projet_tut/ping-pong/ping-pong/Sandstorm.ogg")) {
        std::cout << "Le chargement de la musique a échoué." << std::endl;
        return EXIT_FAILURE;
    }
    musique.setVolume(100);
    musique.setRelativeToListener(true);
    musique.setLoop(true);
    musique.play();
    
    sf::Text title = createText("Ping - Pong",
                                sf::Vector2f(WINDOW_SIZE.x / 3, WINDOW_SIZE.y / 6),
                                font,
                                200);
    
    sf::Text timer = createText("",
                               sf::Vector2f(WINDOW_SIZE.x / 3, WINDOW_SIZE.y / 1.3),
                               font,
                               75);
    
    sf::Text scorePlayer1 = createText("",
                                       sf::Vector2f(100, 100),
                                       font,
                                       75);
    
    sf::Text scorePlayer2 = createText("",
                                       sf::Vector2f(WINDOW_SIZE.x - 100, 100),
                                       font,
                                       75);
    
    //variable de contrôle de la structure du jeu
    bool running(true);
    int score_player_1,
        score_player_2;
    
    //variable de temps de départ pour le comptage du temps de jeu
    unsigned long timeStart(time(NULL));
    
    
    while(running || score_player_1 != score_limit || score_player_2 != score_limit) {
        while(app.pollEvent(event)) {
            //on vérifie tous les évènements émis par la fenêtre / éléments extérieurs
            
            //évènement de fermeture
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                running = false;
            }
            
            //évènements de déplacements des paddles
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                posYLeftPaddle -= SPEED_PADDLE_INIT;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                posYLeftPaddle += SPEED_PADDLE_INIT;
            }
            if(posYLeftPaddle <= 0) {
                posYLeftPaddle = 0;
            }
            else if(posYLeftPaddle > WINDOW_SIZE.y - PADDLE_HEIGHT) {
                posYLeftPaddle = WINDOW_SIZE.y - PADDLE_HEIGHT;
            }
        }
        
        LeftPaddle.setPosition(posYLeftPaddle);
        //différents test pour détecter une collision
        if ((posXBall <= 0 && (posYBall < posYLeftPaddle || posYBall > posYLeftPaddle + PADDLE_HEIGHT))) {
            sleep(1);
            ball.restart(WINDOW_SIZE);
            posXBall = WINDOW_SIZE.x / 2;
            posYBall = WINDOW_SIZE.y / 2;
            score2++;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            ball.restart(WINDOW_SIZE);
            posXBall = WINDOW_SIZE.x / 2;
            posYBall = WINDOW_SIZE.y / 2;
            timeStart = time(NULL);
            score1 = 0;
            score2 = 0;
            sleep(1);
        }
        
        if(posXBall >= WINDOW_SIZE.x - 2 * BALL_SIZE || (posXBall + PADDLE_WIDTH <= 0 && (posYBall > posYLeftPaddle || posYBall + BALL_SIZE / 2 > posYLeftPaddle) && (posYBall < posYLeftPaddle + PADDLE_HEIGHT || posYBall + BALL_SIZE / 2 < posYLeftPaddle + PADDLE_HEIGHT))) {
            ball.ReverseX();
            ball.MoveX();
            if (state_ball_x == true) {
                state_ball_x = false;
            }
            else {
                state_ball_x = true;
            }
            counterBounce++;
        }
        else {
            ball.MoveX();
        }
        
        if (state_ball_x == false) {
            posXBall += BALL_SPEED;
        }
        else {
            posXBall -= BALL_SPEED;
        }
        
        std::cout << posXBall << "   " << posYBall << std::endl;
        sleep(0.5);
        //ColliManager.ManagerCollisionY(BALL_SIZE, posXBall, posYBall, posYLeftPaddle, PADDLE_HEIGHT, PADDLE_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH);
        //ColliManager.ManagerCollisionY(BALL_SIZE, posXBall, posYBall, posYRightPaddle, PADDLE_HEIGHT, PADDLE_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH);
        
        if (posYBall >= WINDOW_SIZE.y - 2*BALL_SIZE || posYBall < 1) {
            ball.ReverseY();
            ball.MoveY();
            if (state_ball_y == true) {
                state_ball_y = false;
            }
            else {
                state_ball_y = true;
            }
        }
        else {
            ball.MoveY();
        }
        
        if (state_ball_y == false) {
            posYBall += BALL_SPEED;
        }
        else {
            posYBall -= BALL_SPEED;
        }
        
        /*if(counterBounce == 2 * BALL_SPEED) {
            BALL_SPEED++;
            ball.setSpeed(BALL_SPEED);
            counterBounce = 0;
        }*/
        
        timer.setString(getTimer(timeStart, time(NULL)));
        scorePlayer1.setString(toString(score1));
        scorePlayer2.setString(toString(score2));
        
        app.clear();
        app.draw(ball);
        app.draw(LeftPaddle);
        app.draw(RightPaddle);
        app.draw(title);
        app.draw(timer);
        app.draw(scorePlayer1);
        app.draw(scorePlayer2);
        app.display();
    }
}

sf::String getTimer(unsigned long timeStart, unsigned long nowTime) {
    unsigned int secondes(nowTime - timeStart);
    unsigned int minutes(0);
    unsigned int hours(0);
    
    //test des secondes
    if(secondes > 60) {
        //ajout des minutes
        while (secondes >= 60) {
            minutes++;
            secondes -= 60;
        }
    }
    
    //test des minutes
    if(minutes > 60) {
        //ajout des heures
        while (minutes >= 60) {
            hours++;
            minutes -= 60;
        }
    }
    
    
    return sf::String(setTwoDigits(hours) + ":" + setTwoDigits(minutes) + ":" + setTwoDigits(secondes));
}

sf::String setTwoDigits(unsigned int number) {
    sf::String value;
    if(number < 10) {
        value = "0" + toString(number);
    }
    else {
        value = toString(number);
    }
    return value;
}


/*  -------------------------------------------------
    *************************************************
 
            FONCTION GAME
 
    *************************************************
    -------------------------------------------------
*/

int getRand(int mini,
            int maxi) {
    return rand() % (maxi - mini) + mini;
}