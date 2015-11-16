
#include "TestShapePopulationBase.h"
#include "QSharedPointer.h"
#include "ShapePopulationQT.h"

TestShapePopulationBase::TestShapePopulationBase()
{

}

bool TestShapePopulationBase::testCreationSphere(std::string filename)
{
    // Creation of sphere with color by direction as map
    QSharedPointer<ShapePopulationBase> shapePopulationBase = QSharedPointer<ShapePopulationBase>( new ShapePopulationBase );

    // Call of the function that must be test
    vtkSmartPointer<vtkActor> actorSphere;
    actorSphere.TakeReference(shapePopulationBase->creationSphereActor());

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData = (vtkPolyData* )actorSphere->GetMapper()->GetInput();
    vtkIdType numPts1 = polyData->GetNumberOfPoints();
    polyData->GetPointData()->SetActiveScalars("ColorByDirection");
    int nb1 = polyData->GetPointData()->GetNumberOfComponents();

    // Recover of data to make a comparison
    vtkSmartPointer<vtkPolyDataReader> meshReader = vtkSmartPointer<vtkPolyDataReader>::New();
    meshReader->SetFileName(filename.c_str());
    meshReader->Update();
    vtkSmartPointer<vtkPolyData> SpherePolyData = vtkSmartPointer<vtkPolyData>::New();
    SpherePolyData = meshReader->GetOutput();
    vtkIdType numPts2 = SpherePolyData->GetNumberOfPoints();
    SpherePolyData->GetPointData()->SetActiveScalars("ColorByDirection");
    int nb2 = SpherePolyData->GetPointData()->GetNumberOfComponents();

    // test if the result obtained is correct
    if(numPts1 != numPts2) return 1;
    if(nb1 != nb2) return 1;

    double p[3];
    double s[3];

    for( vtkIdType i = 0; i < numPts1; ++i )
    {
        polyData->GetPoint(i,p);
        SpherePolyData->GetPoint(i,s);

        for(int j = 0; j< 3; j++)
        {
            if(fabs(p[j] - s[j]) > 0.00001)
            {
                return 1;
            }
        }
    }

    return 0;
}

bool TestShapePopulationBase::testChangeView()
{
    QSharedPointer<ShapePopulationBase> shapePopulationBase = QSharedPointer<ShapePopulationBase>( new ShapePopulationBase );

    //SPHERE
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);
    sphereSource->SetThetaResolution(40);
    sphereSource->SetPhiResolution(40);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyData> polyData = sphereSource->GetOutput();

    //mapper & actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if (VTK_MAJOR_VERSION < 6)
    mapper->SetInputConnection(polyData->GetProducerPort());
#else
    mapper->SetInputData(polyData);
#endif
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    //renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    //window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    shapePopulationBase->m_windowsList.push_back(renderWindow);

    //interactor
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    shapePopulationBase->m_selectedIndex.clear();
    shapePopulationBase->m_selectedIndex.push_back(0);

    // Call of the function that must be test
        // View P
    shapePopulationBase->ChangeView(0,-1,0,0,0,1);

    vtkSmartPointer<vtkRenderer> firstRenderer = vtkSmartPointer<vtkRenderer>::New();
    firstRenderer = shapePopulationBase->m_windowsList[0]->GetRenderers()->GetFirstRenderer();
    double* coords = firstRenderer->GetActiveCamera()->GetFocalPoint();
    double distance = firstRenderer->GetActiveCamera()->GetDistance();
    double* viewUp = firstRenderer->GetActiveCamera()->GetViewUp();
    double* position = firstRenderer->GetActiveCamera()->GetPosition();

    if(!(viewUp[0] == 0 && viewUp[1] == 0 && viewUp[2] == 1 && position[0] == coords[0] && position[1] == (coords[1] - distance) && position[2] == coords[2]))
    {
        return 1;
    }

    // Call of the function that must be test
        // View I
    shapePopulationBase->ChangeView(0,0,-1,0,1,0);
    coords = firstRenderer->GetActiveCamera()->GetFocalPoint();
    distance = firstRenderer->GetActiveCamera()->GetDistance();
    viewUp = firstRenderer->GetActiveCamera()->GetViewUp();
    position = firstRenderer->GetActiveCamera()->GetPosition();
    if(!(viewUp[0] == 0 && viewUp[1] == 1 && viewUp[2] == 0 && position[0] == coords[0] && position[1] == coords[1] && position[2] == (coords[2] - distance) ))
    {
        return 1;
    }

    return 0;
}

bool TestShapePopulationBase::testOpacityMesh()
{
    QSharedPointer<ShapePopulationBase> shapePopulationBase = QSharedPointer<ShapePopulationBase>( new ShapePopulationBase );

    //SPHERE
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);
    sphereSource->SetThetaResolution(40);
    sphereSource->SetPhiResolution(40);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyData> polyData = sphereSource->GetOutput();

    //mapper & actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if (VTK_MAJOR_VERSION < 6)
    mapper->SetInputConnection(polyData->GetProducerPort());
#else
    mapper->SetInputData(polyData);
#endif
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    //renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    //window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    shapePopulationBase->m_windowsList.push_back(renderWindow);

    //interactor
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    shapePopulationBase->m_selectedIndex.clear();
    shapePopulationBase->m_selectedIndex.push_back(0);
    shapePopulationBase->m_meshOpacity.push_back(0);

    // Call of the function that must be test
    shapePopulationBase->setMeshOpacity(0.5);

    vtkActorCollection * actors = shapePopulationBase->m_windowsList[0]->GetRenderers()->GetFirstRenderer()->GetActors();
    actors->InitTraversal();
    double meshOpacity = actors->GetNextActor()->GetProperty()->GetOpacity();

    if(meshOpacity == 0.5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

bool TestShapePopulationBase::testVectorScale(std::string filename)
{
    QSharedPointer<ShapePopulationBase> shapePopulationBase = QSharedPointer<ShapePopulationBase>( new ShapePopulationBase );

    shapePopulationBase->m_selectedIndex.clear();
    shapePopulationBase->m_selectedIndex.push_back(0);
    shapePopulationBase->m_vectorScale.push_back(0);
    shapePopulationBase->m_displayVectorsByDirection.push_back(false);
    shapePopulationBase->m_displayVectorsByAbsoluteDirection.push_back(false);
    shapePopulationBase->CreateNewWindow(filename);

    // Call of the function that must be test
    shapePopulationBase->setVectorScale(50);


    int vectorScale = shapePopulationBase->m_glyphList[0]->GetScaleFactor();

    if(vectorScale == 50)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



