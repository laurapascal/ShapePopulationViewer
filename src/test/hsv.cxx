///****************************************************************************///
///                                    HSL COLORS                              ///
///****************************************************************************///

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkUnsignedCharArray.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointData.h>
#include <vtkMath.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "vtkDoubleArray.h"
#include "vtkMath.h"

//-----------------------------------------------------
int main()
{

    
    /// Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);

    double radius = 1.0;

    sphereSource->SetRadius(radius);

    sphereSource->SetThetaResolution(360);
    sphereSource->SetPhiResolution(360);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyData> polyData = sphereSource->GetOutput();

    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();

    normalGenerator->SetInputData(polyData);
    normalGenerator->Update();
    
    polyData = normalGenerator->GetOutput();

    vtkDoubleArray* normalDataDouble = (vtkDoubleArray*)polyData->GetPointData()->GetArray("Normals");

    cout<<normalDataDouble<<endl;

    double magnitud = -1;
    vtkIdType numPts = polyData->GetNumberOfPoints();

    for(int i = 0; i  < numPts; i++){
        double normal[3];
        normalDataDouble->GetTuple(i, normal);
        magnitud = std::max(magnitud, std::sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]));
    }

    /// Color map by direction with hsv color        
    vtkSmartPointer<vtkUnsignedCharArray> scalars = vtkSmartPointer<vtkUnsignedCharArray>::New();
    scalars->SetNumberOfComponents(3);
    scalars->SetNumberOfTuples(numPts);
    scalars->SetName("ColorByDirection");

    for(int i = 0; i  < numPts; i++){
        double normal[3];
        normalDataDouble->GetTuple(i, normal);

        float HSV[3];
        //MAGNITUD OF THE CURRENT VECTOR
        double mag = std::sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);            
        
        //NORMALIZE THE VECTOR
        vtkMath::Normalize(normal);
        //HUE IS THE ANGLE OF THE VECTOR PROJECTED ONTO THE XY PLANE, 
        HSV[0] =  (vtkMath::Pi() + std::atan2(normal[1],normal[0]))/(2.0*vtkMath::Pi());
        //SATURATION IS THE VALUE OF THE ELEVATION ANGLE !! THE NORMAL OF THIS VECTOR IS = 1, RESCALE THE VALUE BETWEEN 0-1
        //INVERT THE SATURATION SO WE HAVE WHITE AT THE POLES
        HSV[1] = 1 - fabs((std::asin(normal[2]))/(vtkMath::Pi()/2.0));
        //VALUE IS THE VALUE OF THE MAGNITUD AND IT HAS TO BE NORMALIZED WITH THE LARGEST VALUE OF THE VECTORS
        HSV[2] = mag/magnitud;


        float RGB[3];
        vtkMath::HSVToRGB(HSV, RGB);
        vtkMath::MultiplyScalar(RGB, 255);

        scalars->InsertTuple3 (i, (unsigned char)RGB[0], (unsigned char)RGB[1], (unsigned char)RGB[2]);
        
        // vtkMath::MultiplyScalar(normal, 1.0/magnitud);
        // unsigned char r = abs(255*normal[0]);
        // unsigned char g = abs(255*normal[1]);
        // unsigned char b = abs(255*normal[2]);
        // scalars->InsertTuple3 (i, r, g, b);

    }
    
    
    polyData->GetPointData()->AddArray(scalars);
    polyData->GetPointData()->SetActiveScalars("ColorByDirection");
    


    /// VISUALIZATION
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renderWindow = vtkRenderWindow::New();
    renderWindow->AddRenderer(renderer);
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    interactor->SetRenderWindow(renderWindow);

    vtkInteractorStyleTrackballCamera * interactorStyle = vtkInteractorStyleTrackballCamera::New();
    interactor->SetInteractorStyle(interactorStyle);

    // Add the actors to the renderer
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    vtkSmartPointer<vtkActor> m_actor = vtkSmartPointer<vtkActor>::New();
    m_actor->SetMapper(mapper);

    renderer->AddActor(m_actor);

    // Set the background and size
    renderer->SetBackground(1, 1, 1); // background : gray
    renderWindow->SetSize(500, 500); // resize of the window

    renderer->ResetCamera();
    renderWindow->Render();

    interactor->Start();


    return EXIT_SUCCESS;
}
