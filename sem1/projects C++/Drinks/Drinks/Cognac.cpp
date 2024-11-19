#include "Cognac.h"

Cognac::Cognac(std::string nam, double volum, double streng, Grape g)
{
	name = nam;
	SetVolume(volum);
	SetStrength(streng);
	SetGrape(g);
}

std::string Cognac::GetGrape() const
{
	if (grape == Grape::Colombard) {
		return "Colombard";
	}
	if (grape == Grape::FoilBlanche) {
		return "FoilBlanche";
	}
	if (grape == Grape::UnyBlanc) {
		return "UnyBlanc";
	}
	if (grape == Grape::Montil) {
		return "Montil";
	}
	if (grape == Grape::JurensonBlanc) {
		return "JurensonBlanc";
	}
	if (grape == Grape::Semillon) {
		return "Semillon";
	}
}

void Cognac::SetGrape(Grape g)
{
	grape = g;
}
