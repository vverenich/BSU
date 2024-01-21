#ifndef DECISIONMAKER_H
#define DECISIONMAKER_H

class Model;

class DecisionMaker {
  public:
    DecisionMaker();

    void static analyzeState(Model& model);
};

#endif // DECISIONMAKER_H
