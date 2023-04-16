#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const double DISPLAY = 600;

using namespace std;

class CelestialBody : public sf::Drawable{
public:

CelestialBody(double ixpos, double ixvel, double iypos, double iyvel, double imass, double iunir, string ifilename);

void draw(sf::RenderTarget& target, sf::RenderStates states) const;

friend istream& operator>>(istream& in, CelestialBody& c)
{
 if (c.unir == 0)
 cout << "You must intialize unir before using the insertion operator" << endl;

 in >> c.xpos;
 in >> c.ypos;
 in >> c.xvel;

 //Multiply by -1 due to the window (right is positive, left is negative)
 c.xvel = c.xvel*-1;
 in >> c.yvel;

 //Multiply by -1 due to the window (up is negative, down is positive)
 c.yvel = c.yvel*-1;
 in >> c.mass;

 string ifilename;
 in >> ifilename;

 c.filename = ifilename;

 //Convert from real number to display coordinate numbers
 c.PosXConv(c.xpos, c.unir);
 c.PosYConv(c.ypos, c.unir);

 sf::Image imagefile;
 imagefile.loadFromFile(ifilename);

 if(!c.texturefile.loadFromImage(imagefile))
 cout <<"ERROR" << endl;

 //Sprite Manipulation
 c.spritefile.setTexture(c.texturefile);

 //Moving the sprite to the correct position
 c.spritefile.move(c.xpos, c.ypos);

 //Setting the origin of the sprite correctly
 sf::FloatRect gb = c.spritefile.getGlobalBounds();
 c.spritefile.setOrigin((gb.width/2), (gb.height/2));

 return in;

}

void setXVel(double in) { xvel = in; }
void setYVel(double in) { yvel = in; }

//When setting the postions, make sure to convert them to pixels...
void setXPos(double in)
{
	xpos = in;
	PosXConv(xpos, unir);
	spritefile.setPosition(xpos, ypos);
}
void setYPos(double in)
{
	ypos = in;
	PosYConv(ypos, unir);
	spritefile.setPosition(xpos, ypos);
}

//Same thing here
double getUNIR(){ return unir; }
double getMass(){ return mass; }
double getXVel(){ return xvel; }
double getYVel(){ return yvel; }

double getXPos()
{
 	double x;
 	x = ((xpos-300) * ((unir*2)/DISPLAY));
 	return x;
}

double getYPos()
{
 	double y;
 	y = ((ypos-300) * ((unir*2)/DISPLAY));
 	return y;
}

string getFileName(){ return filename; }


private:

 double unir;
 double xpos, xvel, ypos, yvel, mass;
 string filename;
 sf::Sprite spritefile;
 sf::Texture texturefile;

 void PosXConv(double ixpos, double iunir);
 void PosYConv(double iypos, double iunir);

};

#endif
