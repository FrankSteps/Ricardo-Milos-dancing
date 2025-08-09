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
*/


//bibliotecas utilizadas no projeto
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

//declaração dos namespaces utilizadas por algumas das bibliotecas
using namespace std;
using namespace sf;

//criação dos vetores
vector<Texture> frames;
vector<Sprite> sprites;

//declaração de variáveis
const int frame_count = 49;
int current_frame = 0;
float duration = 0.07f;


int main() {
    //algumas configurações de dimensão
    RenderWindow window(VideoMode(224, 224), "Ricardo Milos");
    window.setFramerateLimit(60);

    frames.reserve(frame_count); //evita realocação durante o push_back
    sprites.reserve(frame_count * 2); //o dobro para que o efeito ping-pong seja possível

    //Configuração dos sons do projeto
    Sound sound;
    SoundBuffer buffer;
    if(!buffer.loadFromFile("sounds/milos.wav")){
        return -1; 
    }
    sound.setBuffer(buffer);
    sound.play();

    //Carregando o ícone da janela
    Image icon;
    if(!icon.loadFromFile("icone/icon.png")){
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //carrega as texturas direto nos vetores
    for (int i = 0; i < frame_count; i++) {
        frames.emplace_back(); 
        if (!frames.back().loadFromFile("image/frame_" + to_string(i) + ".png")) {
            return -1; //fechar o programa automaticamente caso não encontre o arquivo 
        }
        sprites.push_back(Sprite(frames.back()));
    }
    
    //fazendo o processo inverso para causar o efeito ping-pong, carregando novamente as imagens, mas na ordem inversa (dobrando o valor de imagens)
    for (int i = frame_count - 1; i >= 0; i--) {
        sprites.push_back(Sprite(frames[i]));
    }

    int num_frames = sprites.size();

    //configurações da interações com a janela e do clock
    Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
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
