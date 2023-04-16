#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "CelestialBody.h"
#include <vector>
#include <math.h>
using namespace std;

const double GRAV = 0.0000000000667;

class Universe {
public:

 void create(double time, double deltime)
 {
  int particles;
  double unir;

  //Create Celestial Bodies:
  //First input the particles and the radius
  cin >> particles;
  cin >> unir;

  //Create the pointers for the vector
 for (int i = 0; i < particles; i++)
  {
   CelestialBody* C = new CelestialBody(0, 0, 0, 0, 0, unir, "");
   cin >> *C;
   Bodies.push_back(C);
  }

  //Create Background
  sf::Image i;
  i.loadFromFile("starfield.jpg");
  sf::Texture t;
  t.loadFromImage(i);
  sf::Sprite s;
  s.setTexture(t);
  s.scale(1.2f, 1.2f);

  //Time to make a counter! (make the fonts and text)
  sf::Font font;
  if (!font.loadFromFile("arial.ttf"))
  {
  cout << "There is no arial font file to display the text" << endl;
  }

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(24);
  text.setPosition(0,0);

  //Find the endtime
  const double ctime = time;

  //Time to play some sound!
  sf::Music music;
  if(!music.openFromFile("2001.wav"))
  cout << "The music file is not in the same file as the program! Please name it \"2001.wav\"" << endl;


  //Window creation
sf::RenderWindow window(sf::VideoMode(DISPLAY, DISPLAY), "The Universe");
while (window.isOpen())
    {
	music.play();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	window.clear();

	//Counter is always off by 40,000, this is due to the step function
	int counter = 40000;
	while (time >= deltime)
	{

	step(deltime);
	time -= deltime;
	window.draw(s);

	for (int i = 0; i < particles; i++)
	window.draw(*Bodies.at(i));

	text.setString("Timer: " + to_string(counter) + "/" + to_string((int)(ctime)));

	counter += deltime;

	window.draw(text);
	window.display();
	}

    }

  //Output (which looks just like the input file...)
  cout << Bodies.size() << endl;
  cout << Bodies.at(0)->getUNIR() << endl;
  for (int i = 0; i < (int)Bodies.size(); i++)
  {
   cout << scientific << Bodies.at(i)->getXPos() << "   ";
   cout << scientific << Bodies.at(i)->getYPos()*-1 << "   ";
   cout << scientific << Bodies.at(i)->getXVel() << "   ";
   cout << scientific << Bodies.at(i)->getYVel() << "   ";
   cout << scientific << Bodies.at(i)->getMass() << "   ";
   cout << scientific << Bodies.at(i)->getFileName() << endl;
  }
 }

void step(double del)
{
  for (int i = 0; i < (int)Bodies.size(); i++)
  {
  //Calculate the acceleration (Force)...
  double ForceX = 0, ForceY = 0, Force = 0, r = 0, delx = 0, dely = 0;
  for (int j = 0; j < (int)Bodies.size(); j++)
  {
   //If the bodies are the same, do not do any calculations
   if(i != j)
   {
   //Calculate the Del X and Del Y
   delx = Bodies.at(j)->getXPos() - Bodies.at(i)->getXPos();
   dely = Bodies.at(j)->getYPos() - Bodies.at(i)->getYPos();

   //Calculate r
   r = sqrt((delx*delx) + (dely*dely));

   //Calculate Force
   Force = (GRAV * Bodies.at(i)->getMass() * Bodies.at(j)->getMass()) / (r*r);

   //Calculate ForceX (Depending on directions, the force is neg)
   ForceX += Force * (delx/r);
   ForceY += Force * (dely/r);
   }
  }
  //Now, use the force to calculate the acceleration for x and y
  double AcX, AcY;
  AcX = ForceX / Bodies.at(i)->getMass();
  AcY = ForceY / Bodies.at(i)->getMass();

  //Calculate the velocity....
  Bodies.at(i)->setXVel(Bodies.at(i)->getXVel() + (del * AcX));
  Bodies.at(i)->setYVel(Bodies.at(i)->getYVel() + (del * AcY));

  //Calculate the position...
  Bodies.at(i)->setXPos(Bodies.at(i)->getXPos() + (Bodies.at(i)->getXVel() * del));
  Bodies.at(i)->setYPos(Bodies.at(i)->getYPos() + (Bodies.at(i)->getYVel() * del));
 }
}

private:

vector<CelestialBody*> Bodies;

};

#endif
