#include "CelestialBody.h"

CelestialBody::CelestialBody(double ixpos, double ixvel, double iypos, double iyvel, double imass, double iunir, string ifilename)
{
 xvel = ixvel*-1;
 yvel = iyvel*-1;
 mass = imass;
 unir = iunir;

 filename = ifilename;

 //This function converts the pos given to the pos on the screen
 PosXConv(ixpos, iunir);
 PosYConv(iypos, iunir);

 if (ifilename != "")
{
 sf::Image imagefile;
 imagefile.loadFromFile(ifilename);

 if(!texturefile.loadFromImage(imagefile))
 cout <<"ERROR" << endl;

 //Sprite Manipulation
 spritefile.setTexture(texturefile);

 //Moving the sprite to the correct position
 spritefile.move(xpos, ypos);

 //Setting the origin of the sprite correctly
 sf::FloatRect gb = spritefile.getGlobalBounds();
 spritefile.setOrigin((gb.width/2), (gb.height/2));
}
}

void CelestialBody::PosXConv(double ixpos, double iunir)
{
 xpos = (ixpos * (DISPLAY/(iunir*2))) + 300;
}

void CelestialBody::PosYConv(double iypos, double iunir)
{
 ypos = (iypos * (DISPLAY/(iunir*2))) + 300;
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
 target.draw(spritefile, states);
}


