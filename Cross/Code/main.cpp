#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main()
{
    float x1, y1, x2, y2;
    bool on_ground = true;
    bool platformrange = true;
    
    RenderWindow window(sf::VideoMode(1280, 1280), "EASY GAME 228");
    
    Texture herotexture;
    herotexture.loadFromFile("Resources/hero.png");
    
    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 192, 96, 96));
    herosprite.setPosition(592, 1280-96-64);
    
    Texture platformtexture;
    platformtexture.loadFromFile("Resources/platform.jpg");
    
    Sprite platformsprite;
    platformsprite.setTexture(platformtexture);
    platformsprite.setTextureRect(IntRect(0, 0, 256, 64));
    platformsprite.setPosition(512, 1280-64);
    
    float CurrentFrame = 0;  //хранит текущий кадр
    Clock clock;
    
    while (window.isOpen())
    {
        
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 400;
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
        
        
        
        if ((Keyboard::isKeyPressed(Keyboard::Left))) { //если нажата клавиша стрелка влево
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
            herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
            herosprite.move(-0.1*time, 0);//происходит само движение персонажа влево
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Right))) {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
            herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
            
            herosprite.move(0.1*time, 0);//происходит само движение персонажа вправо

        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Space)) && (on_ground)) {
            
            herosprite.move(0, -0.3*time);
            on_ground = false;
        }
        
        
        
        // ОБРАБОТКА ВЗАИМОДЕЙСТВИЯ ПЕРСОНАЖА С ПЛАТФОРМОЙ
        x1 = herosprite.getPosition().x;        // координата х персонажа
        y1 = herosprite.getPosition().y;        // координата у персонажа
        x2 = platformsprite.getPosition().x;    // координата х платформы
        y2 = platformsprite.getPosition().y;    // координата у платформы
        
        if (((x2-48 < x1) && (x1 < x2+192)))
            on_ground = true;
        else
            on_ground = false;
        
        if (!on_ground && !(Keyboard::isKeyPressed(Keyboard::Space))){
            herosprite.move(0, 0.1*time);
        }

//        if (y2-96 == y1)
//            platformrange = true;
//        else platformrange = false;
//
//        if (platformrange == false)
//            herosprite.move(0, 0.2*time);
        
        window.clear();
        window.draw(herosprite);
        window.draw(platformsprite);
        window.display();
    }
    
    return 0;
}
