#include <iostream>
#include <string>
#include <QApplication>
#include <QFileInfo>

//#include "ShapePopulationQT.h"
//#include "ShapePopulationViewerCLP.h"
//#include "ShapePopulationBase.h"



#include "TestShapePopulationBase.h"

int main(int argc, char *argv[])
{
    TestShapePopulationBase testShapePopulationBase;
    bool test1 = testShapePopulationBase.testCreationSphere( (std::string)argv[1] );
    bool test2 = testShapePopulationBase.testChangeView();
    bool test3 = testShapePopulationBase.testOpacityMesh();
    bool test4 = testShapePopulationBase.testVectorScale( (std::string)argv[1] );



    bool test = (test1 || test2 || test3 || test4);
    if(!test)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
