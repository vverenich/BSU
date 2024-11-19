#include "MineralWater.h"

MineralWater::MineralWater(std::string nam, double volum, Kind k)
{
	name = nam;
	SetVolume(volum);
	SetKind(k);
}

std::string MineralWater::GetKind() const
{
	if (kind == Kind::Bicarbonate) {
		return "Bicarbonate";
	}
	if (kind == Kind::Sulfate) {
		return "Sulfate";
	}
	if (kind == Kind::Chloride) {
		return "Chloride";
	}
	if (kind == Kind::Calcium) {
		return "Calcium";
	}
	if (kind == Kind::Magnesium) {
		return "Magnesium";
	}
	if (kind == Kind::Sodium) {
		return "Sodium";
	}
	if (kind == Kind::Sour) {
		return "Sour";
	}
	if (kind == Kind::Glandular) {
		return "Glandular,";
	}
	if (kind == Kind::Fluorine) {
		return "Fluorine";
	}
}

void MineralWater::SetKind(Kind k)
{
	kind = k;
}
