//Chaos Game by Ryan Campfield & Josh Adams

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;
int randPoint;
int pointAt;
int triforcePower;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    Font font;
    font.loadFromFile("zeldadxt.ttf");

    Text myText;
    myText.setCharacterSize(75);
    myText.setFillColor(Color::Green);
    myText.setFont(font);
    
    Text instruct;
    instruct.setCharacterSize(25);
    instruct.setFillColor(Color::Green);
    instruct.setFont(font);

    Texture link;
    link.loadFromFile("link.png");
    Sprite linkSprite;
    linkSprite.setTexture(link);
    linkSprite.setPosition(1300, 450);

	while (window.isOpen())
	{

       
       
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///fourth click
                        ///push back to points vector
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            randPoint = (rand() % 3);
            Vector2f mid;
            mid.x = ((vertices.at(randPoint).x + points.at(pointAt).x) / 2);
            mid.y = ((vertices.at(randPoint).y + points.at(pointAt).y) / 2);
            points.push_back(mid);
            pointAt++;
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }
        triforcePower = points.size();
        FloatRect instructRect = instruct.getLocalBounds();
        instruct.setOrigin(instructRect.left + instructRect.width/2.0f,
            instructRect.top + instructRect.height/2.0f);
        instruct.setPosition(600, 200);
        stringstream is;
        is << "Click 3 points to make triangle" << endl <<"Click inside triangle" << endl <<"(Press ESC to quit)" << endl << "Triforce Power : " << triforcePower << endl;
        instruct.setString(is.str());
        window.draw(instruct);

        window.draw(linkSprite);
        FloatRect textRect = myText.getLocalBounds();
        myText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        myText.setPosition(1920 / 2.0f, 300);
        stringstream ss;
        ss << "Triforce" << endl;
        myText.setString(ss.str());
        window.draw(myText);

        window.display();
    }
}
