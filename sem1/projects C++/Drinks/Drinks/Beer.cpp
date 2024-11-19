#include "Beer.h"

Beer::Beer(std::string nam, double volum, double streng, Raw r)
{
	name = nam;
	SetVolume(volum);
	SetStrength(streng);
	typeOfRaw = r;
}

std::string Beer::GetTypeRaw() const
{
	if (typeOfRaw == Raw::wheat) {
		return "wheat";
	}
	if (typeOfRaw == Raw::ginger) {
		return "ginger";
	}
	if (typeOfRaw == Raw::barley) {
		return "barley";
	}
}

void Beer::SetTypeRaw(Raw r)
{
	typeOfRaw = r;
}
 