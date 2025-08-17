/*
Desenvolvedor desta blasfêmia: Francisco Passos
Arrependimento em: 01/08/2025

Este programa foi desenvolvido para ver o quão longe um ser consegue chegar com a biblioteca SFML no C++
Para ver o quão distante Deus está da humanidade e o quanto a mesma se encontra perdida

Se seres humanos tivessem tal conhecimento, quais desgraças poderiam ser feitas? Quantas blasfêmias poderiam ser ditas?
Este projeto procura responder isso...
Nenhuma criatura merece perdão divino, principalmente quem desenvolveu esta escória. 

"O apocalípse deixou de ser um medo e se tornou uma esperança..."
~ Desconhecido

"Não tive filhos. Não passei a nenhuma criatura o legado de nossa miséria..."
~ Assis, Machado - 1800 e não sei o que


Tava dando erro, essa bosta de SFML:
 g++ -std=c++17 milos.cpp -o milos \
          -I/usr/local/include \
          -L/usr/local/lib \
          -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

*/


//bibliotecas utilizadas no projeto
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

//criação dos vetores
std::vector<sf::Texture> frames;
std::vector<sf::Sprite> sprites;

//declaração de variáveis
const int frame_count = 49;
int current_frame = 0;
float duration = 0.07f;

int main() {
    //algumas configurações de dimensão
    sf::RenderWindow window(
        sf::VideoMode(224, 224),
        "Ricardo Milos",
        sf::Style::Titlebar | sf::Style::Close     
    );
    window.setFramerateLimit(60);

    frames.reserve(frame_count); //evita realocação durante o push_back
    sprites.reserve(frame_count * 2); //o dobro para que o efeito ping-pong seja possível

    //Configuração dos sons do projeto
    sf::Sound sound;
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("sounds/milos.wav")){
        return -1; 
    }
    sound.setBuffer(buffer);
    sound.play();

    //Carregando o ícone da janela
    sf::Image icon;
    if (!icon.loadFromFile("icone/icon.png")) {
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //carrega as texturas direto nos vetores
    for (int i = 0; i < frame_count; i++) {
        frames.emplace_back(); 
        if (!frames.back().loadFromFile("image/frame_" + std::to_string(i) + ".png")) {
            return -1; //fechar o programa automaticamente caso não encontre o arquivo 
        }
        sprites.push_back(sf::Sprite(frames.back()));
    }
    
    //fazendo o processo inverso para causar o efeito ping-pong, carregando novamente as imagens, mas na ordem inversa (dobrando o valor de imagens)
    for (int i = frame_count - 1; i >= 0; i--) {
        sprites.push_back(sf::Sprite(frames[i]));
    }

    int num_frames = sprites.size();

    //configurações da interações com a janela e do clock
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= duration) {
            current_frame = (current_frame + 1) % num_frames;
            clock.restart();
        }

        window.clear();
        window.draw(sprites[current_frame]);
        window.display();
    }
    return 0;
}
