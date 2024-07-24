//the main ideia here is to try to optimize an iteration over particles, when
//they need to know some informations about the others;
//Space partitioning is going to be the first test
#include <SFML/Graphics.hpp>

int main(){

    sf::RenderWindow window(sf::VideoMode(500,500), "PERFORMANCE");

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.display();
    }
}



