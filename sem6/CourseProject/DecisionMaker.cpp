#include "DecisionMaker.h"

#include "Model.h"

DecisionMaker::DecisionMaker()
{

}

void DecisionMaker::analyzeState(Model& model)
{
    for (auto& city : model.m_Objects) {
        for (auto& obj : city) {
            if (obj.m_State == LargeObjectState::DAMAGED ||
                obj.m_State == LargeObjectState::DESTROYED) {
                obj.m_State = LargeObjectState::UNDER_REPAIR;
            } else if (obj.m_State == LargeObjectState::UNDER_REPAIR) {
                obj.m_State = LargeObjectState::GOOD;
            } else if (obj.m_State == LargeObjectState::GOOD) {
                obj.m_State = ((rand() % 100) > 75) ?
                                  (((rand() % 100) > 75) ? LargeObjectState::DESTROYED :
                                                           LargeObjectState::DAMAGED) :
                                  LargeObjectState::GOOD;
            }
        }
    }
}
