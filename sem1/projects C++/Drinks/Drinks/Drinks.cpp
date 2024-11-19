#include <iostream>
#include"Beer.h"
#include"Cognac.h"
#include"Wine.h"
#include"Milk.h"
#include"Lemonade.h"
#include"MineralWater.h"

int main()
{
    Beer newBeer("Baltika", 200, 10, Raw::wheat);
    Cognac newCognac("Armenian", 2, 20, Grape::Montil);
    Wine newWine("Dow's", 23, 30, 30);

    Lemonade newLemonade("Buratino", 3, Type::Baikal);
    MineralWater newMineralWater("Minsk", 4, Kind::Calcium);
    Milk newMilk("Horki", 2, 40);

    std::cout << newBeer.GetName() << " " << newBeer.GetVolume() << " " << newBeer.GetStrength() << " " << newBeer.GetTypeRaw()<<"\n";
    std::cout << newCognac.GetName() << " " << newCognac.GetVolume() << " " << newCognac.GetStrength() << " " << newCognac.GetGrape() << "\n";
    std::cout << newWine.GetName() << " " << newWine.GetVolume() << " " << newWine.GetStrength() << " " << newWine.GetHoldingTime() << "\n";

    std::cout << newLemonade.GetName() << " " << newLemonade.GetVolume() << " " << newLemonade.GetType() << "\n";
    std::cout << newMilk.GetName() << " " << newMilk.GetVolume() << " " << newMilk.GetFatContent() << "\n";
    std::cout << newMineralWater.GetName() << " " << newMineralWater.GetVolume() << " " << newMineralWater.GetKind() << "\n";

    newMilk.SetFatContent(15);
    std::cout << newMilk.GetName() << " " << newMilk.GetVolume() << " " << newMilk.GetFatContent() << "\n";
   
    return 0;
}

 