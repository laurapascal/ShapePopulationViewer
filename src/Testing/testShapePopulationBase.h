#ifndef TESTSHAPEPOPULATIONBASE_H
#define TESTSHAPEPOPULATIONBASE_H


#include "../src/ShapePopulationBase.h"

class TestShapePopulationBase
{
public:
    TestShapePopulationBase();

    bool testCreationSphere(std::string filename);
    bool testChangeView();
    bool testOpacityMesh();
    bool testVectorScale(std::string filename);
};

#endif // TESTSHAPEPOPULATIONBASE_H
