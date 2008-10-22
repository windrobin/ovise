#ifndef dotSceneColour_h_
#define dotSceneColour_h_
#include "dotSceneColour.h"
#endif

void dotSceneObjects::dotSceneColour::set_r(double value) { _r = value; }
void dotSceneObjects::dotSceneColour::set_g(double value) { _g = value; }
void dotSceneObjects::dotSceneColour::set_b(double value) { _b = value; }

double dotSceneObjects::dotSceneColour::get_r() const { return _r; }
double dotSceneObjects::dotSceneColour::get_g() const { return _g; }
double dotSceneObjects::dotSceneColour::get_b() const { return _b; }

///region constructors & destructors
dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneElementTags incomingTag) : dotSceneObject(incomingTag) { }
dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneElementTags incomingTag, std::string str_r, std::string str_g, std::string str_b) : dotSceneObject(incomingTag)
{
	double tmpr, tmpg, tmpb;
	sscanf(str_r.c_str(), "%lf", &tmpr);
	sscanf(str_g.c_str(), "%lf", &tmpg);
	sscanf(str_b.c_str(), "%lf", &tmpb);
    this->set_r(tmpr);
    this->set_g(tmpg);
	this->set_b(tmpb);
}

dotSceneObjects::dotSceneColour::dotSceneColour(dotSceneElementTags incomingTag, double double_r, double double_g, double double_b) : dotSceneObject(incomingTag)
{
	this->set_r(double_r);
    this->set_g(double_g);
	this->set_b(double_b);
}
