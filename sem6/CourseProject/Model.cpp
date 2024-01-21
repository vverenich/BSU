#include "Model.h"

#include "DecisionMaker.h"

Model::Model()
{

}

void Model::liveTheDay()
{
    DecisionMaker::analyzeState(*this);
}
