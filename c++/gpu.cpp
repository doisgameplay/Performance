#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random> 
#include <vector>
#include <thread>
#include <future>

float dt = 0.1f;
int numParticles = 1000;

class particle{
public:
    sf::Vector2f position;
    sf::Vector2f velocities;
    sf::Vertex pixel;

    sf::Vector2f acceleration;

    particle(sf::Vector2f position_, sf::Vector2f velocities_)
        : position(position_), velocities(velocities_), pixel(position,sf::Color::White){
    };
    void update(sf::RenderWindow& window){
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        acceleration = sf::Vector2f(mousePos) - position;
        float length = std::sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y);
        acceleration /= length;
        velocities = velocities + acceleration*(dt * 10);
        position += velocities * dt;
        pixel.position = position;
    }
};

void update(int initial, int final, std::vector<particle>& particles, sf::VertexArray& vertices, sf::RenderWindow& window){
    for(int i  = initial; i < final; i++){
        particles[i].update(window);
        vertices[i].position = particles[i].position;
    }
}


int main(){
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "particles", sf::Style::Fullscreen);
    sf::Clock clock;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> value(0,desktop.height);
    std::vector<particle> particles;
    particles.reserve(numParticles);
    sf::VertexArray vertices(sf::Points, numParticles);
    for(int i = 0; i < numParticles;i++){
        particle p(sf::Vector2f(value(gen),value(gen)),sf::Vector2f(0,0));
        particles.emplace_back(p);
        vertices[i].position = p.position;
        vertices[i].color = sf::Color::White;
    }
    while(window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        const int numThreads = std::thread::hardware_concurrency();
        std::vector<std::future<void>> futures;
        int chunkSize = numParticles/numThreads;

        for(int t = 0; t < numThreads; ++t){
            int start = t * chunkSize;
            int end = (t == numThreads - 1) ? numParticles : start + chunkSize;
            futures.emplace_back(std::async(std::launch::async,update, start, end, std::ref(particles),std::ref(vertices), std::ref(window)));
        }

        for(auto& future : futures){
            future.get();
        }
       
        sf::Time elapsedTime = clock.restart();
        float fps =  1.0f/elapsedTime.asSeconds();
        std::cout<<"FPS : "<<fps<<std::endl;
        window.draw(vertices);    
        window.display();
    }

}