//the main ideia here is to try to optimize an iteration over particles, when
//they need to know some informations about the others;
//Space partitioning is going to be the first test
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

const int width = 1200;
const int height = 1200;
float ballSize = 10;
int side = 300;
int xGridSize = width/side;
int yGridSize = height/side;


void startBalls(
    std::vector<float>& xPositions,
    std::vector<float>& yPositions,
    std::vector<float>& xVelocities,
    std::vector<float>& yVelocities,
    std::vector<sf::CircleShape>& circles,
    std::vector<float>& radius,
    std::vector<sf::Color>& color,
    int numBalls
);
void startBalls(
    std::vector<float>& xPositions,
    std::vector<float>& yPositions,
    std::vector<float>& xVelocities,
    std::vector<float>& yVelocities,
    std::vector<sf::CircleShape>& circles,
    std::vector<float>& radius,
    std::vector<sf::Color>& color,
    int numBalls
){
    for(int k = 0; k <= sqrt(numBalls); k++){
        for(int i = 0; i <= sqrt(numBalls); i++){
            float x = 300 + (width - 2 * 300)/(sqrt(numBalls)) * i;
            float y = 300 + (height - 2 * 300)/sqrt(numBalls) * k;
            float xv = 0;
            float yv = 0;
            sf::CircleShape circle(ballSize);
            circle.setOrigin(ballSize, ballSize);
            circle.setFillColor(sf::Color(222, 184, 65));
            circle.setPosition(x, y);
            xPositions.push_back(x);
            yPositions.push_back(y);
            xVelocities.push_back(xv);
            yVelocities.push_back(yv);
            circles.push_back(circle);
            radius.push_back(ballSize);
            color.push_back(sf::Color(145,248,255));   
        }
    }
}


void drawGrid(sf::RenderWindow& window);
void drawGrid(sf::RenderWindow& window){
    std::vector<sf::RectangleShape> lines;
    for(int i = 0; i < yGridSize ; i++){
        sf::RectangleShape line(sf::Vector2f(width, 4));
        line.setPosition(0, height/yGridSize * i);
        line.setFillColor(sf::Color(109, 106, 117));
        lines.push_back(line);
    }
    for(int i = 0; i < xGridSize ; i++){
        sf::RectangleShape line(sf::Vector2f(4, height));
        line.setPosition(width/xGridSize*i, 0);
        line.setFillColor(sf::Color(109, 106, 117));
        lines.push_back(line);
    }
    for(auto line : lines){
        window.draw(line);
    }
}


void drawCircles(const std::vector<sf::CircleShape> circle,sf::RenderWindow& window);
void drawCircles(const std::vector<sf::CircleShape> circle,sf::RenderWindow& window){
    for(int i = 0; i < circle.size(); i++){
        window.draw(circle[i]);
    }
}


void spacialPartitioning(std::vector<sf::CircleShape> &circles,sf::RenderWindow& window);
void spacialPartitioning(std::vector<sf::CircleShape> &circles, sf::RenderWindow& window) {
    //drawGrid(window);
    
}


int main(){

    sf::RenderWindow window(sf::VideoMode(width, height), "PERFORMANCE");
    std::vector<float> xPositions;
    std::vector<float> yPositions;
    std::vector<float> xVelocities;
    std::vector<float> yVelocities;
    std::vector<sf::CircleShape> circles;
    std::vector<float> radius;
    std::vector<sf::Color> color;
    int numBalls = 100;
    startBalls(xPositions,yPositions,xVelocities, yVelocities, circles, radius, color, numBalls);


    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear(sf::Color(25, 30, 32));
        drawGrid(window);
        drawCircles(circles, window);
        spacialPartitioning(circles, window);
        window.display();
    }
}



