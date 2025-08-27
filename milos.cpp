/*
[PT-BR]
Desenvolvedor desta blasfêmia: Francisco Passos
Arrependimento em: 27/08/2025

Este programa foi desenvolvido para ver o quão longe um ser consegue chegar com a biblioteca Raylib no C++
Para ver o quão distante Deus está da humanidade e o quanto a mesma se encontra perdida

Se seres humanos tivessem tal conhecimento, quais desgraças poderiam ser feitas? Quantas blasfêmias poderiam ser ditas?
Este projeto procura responder isso...
Nenhuma criatura merece perdão divino, principalmente quem desenvolveu esta escória. 

Me perdoe, raysan5; me perdoe, Bjarne Stroustrup; me perdoe, Santo Deus pois eu não mereço seu perdão. 
Não sou digno de ser teu filho, oh meu pai! Não sou digno de tua herança

"O apocalípse deixou de ser um medo e se tornou uma esperança..."
~ Desconhecido

"Não tive filhos. Não passei a nenhuma criatura o legado de nossa miséria..."
~ Assis, Machado - 1800 e não sei o que


[EN-US]
Developer of this blasphemy: Francisco Passos
Repentance on: 08/27/2025

This program was developed to see how far a being can go with the Raylib library in C++.
To see how far God is from humanity and how lost it is.

If human beings had such knowledge, what misfortunes could be done? How many blasphemies could be uttered?
This project seeks to answer that...
No creature deserves divine forgiveness, especially those who developed this scum. 

Forgive me, raysan5; forgive me, Bjarne Stroustrup; forgive me, Holy God, for I am not worthy of your forgiveness. 
I am not worthy to be your son, oh my father! I am not worthy of your inheritance.

“The apocalypse ceased to be a fear and became a hope...”
~ Unknown

“I had no children. I did not pass on the legacy of our misery to any creature...”
~Assis, ax - 1800 or 1900 (i don't know and i don´t care)
*/
#include <iostream>
#include <string>
#include <vector>

namespace ray {
    #include <raylib.h>
}

int main() {
    ray::InitWindow(224, 224, "Ricardo Milos"); 

    ray::Image icon = ray::LoadImage("icone/icon.png"); 
    ray::SetWindowIcon(icon);
    
    // Responsável por tocar a música
    ray::InitAudioDevice();
    ray::Sound sound = ray::LoadSound("sounds/milos.wav");
    ray::PlaySound(sound);

    // Responsável pelas imagens (frames da animação)
    const int frame_count = 48;
    std::vector<ray::Texture> frames(frame_count);

    for (int i = 0; i < frame_count; i++) {
        frames[i] = ray::LoadTexture(("image/frame_" + std::to_string(i) + ".png").c_str());
    }

    int current_frame = 0;
    int direction = 1; 
    float frame_timer = 0.0f;
    const float frame_duration = 0.07f;

    while (!ray::WindowShouldClose()) {
        // Atualiza animação
        frame_timer += ray::GetFrameTime();
        if (frame_timer >= frame_duration) {
            current_frame += direction;

            // inverte a direção ao chegar no fim ou no começo
            if (current_frame >= frame_count - 1 || current_frame <= 0) {
                direction *= -1;
            }
            frame_timer = 0.0f;
        }
        ray::BeginDrawing();
        ray::ClearBackground(ray::RAYWHITE);
        ray::DrawTexture(frames[current_frame], 0, 0, ray::WHITE);
        ray::EndDrawing();
    }
    // Libera memória para evitar vazamento
    for (auto &t : frames) ray::UnloadTexture(t);
    ray::UnloadSound(sound);
    ray::UnloadImage(icon);
    ray::CloseAudioDevice();
    ray::CloseWindow();
    return EXIT_SUCCESS;    
}
