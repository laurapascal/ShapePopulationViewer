#ifndef SHAPEPOPULATIONBASE_H
#define SHAPEPOPULATIONBASE_H

#include "ShapePopulationData.h"
#include "colorBarStruct.h"
#include "cameraConfigStruct.h"

#include <vtkCamera.h>                  //Camera
#include <vtkPolyDataMapper.h>          //Mapper
#include <vtkActor.h>                   //Actor
#include <vtkProperty.h>                //Actor Opacity
#include <vtkRenderer.h>                //Renderer
#include <vtkRenderWindow.h>            //RenderWindow
#include <vtkRenderWindowInteractor.h>  //Interactor
#include <vtkCornerAnnotation.h>        //Window Annotations
#include <vtkTextProperty.h>            //Annotations Text
#include <vtkScalarBarActor.h>          //ScalarBar
#include <vtkColorTransferFunction.h>   //LookUpTable
#include <vtkCommand.h>                 //Event
#include <vtkRendererCollection.h>      //GetRenderers
#include <vtkActor2DCollection.h>       //GetActors2D

#include "vtkGlyph3D.h"
#include "vtkArrowSource.h"
#include "vtkMaskPoints.h"


#include <set>

class ShapePopulationBase
{
  public :

    ShapePopulationBase();
    ~ShapePopulationBase(){} //delete the pointers in the lists


    void KeyPressEventVTK(vtkObject* a_selectedObject, unsigned long, void*);
    void CameraChangedEventVTK(vtkObject*, unsigned long, void*);
    void StartEventVTK(vtkObject*, unsigned long, void*);
    void EndEventVTK(vtkObject*, unsigned long, void*);

  protected :

    std::vector<ShapePopulationData *> m_meshList;
    std::vector< vtkSmartPointer<vtkGlyph3D> > m_glyphList;
    std::vector< vtkSmartPointer<vtkRenderWindow> > m_windowsList;
    std::vector< unsigned int > m_selectedIndex;
    vtkSmartPointer<vtkCamera> m_headcam;
    cameraConfigStruct m_headcamConfig;
    std::vector<std::string> m_commonAttributes;
    colorBarStruct * m_usedColorBar;
    std::vector< colorBarStruct *> m_colorBarList;
    bool m_renderAllSelection;
    bool m_displayVectors;
    bool m_displayColorbar;

    void CreateNewWindow(std::string a_filePath);

    //SELECTION
    virtual void ClickEvent(vtkObject* a_selectedObject, unsigned long, void*);
    virtual void SelectAll();
    virtual void UnselectAll();
    unsigned int getSelectedIndex(vtkSmartPointer<vtkRenderWindow> a_selectedWindow);
    
    //RENDERING
    void RenderSelection();
    void RealTimeRenderSynchro(bool realtime);

    //COLORMAP
    void computeCommonAttributes();
    double* computeCommonRange(const char * a_cmap, std::vector<unsigned int> a_windowIndex);
    void UpdateAttribute(const char *a_cmap, std::vector<unsigned int> a_windowIndex);
    void UpdateColorMap(std::vector<unsigned int> a_windowIndex);
    double m_commonRange[2];

    //VECTORS
    void setMeshOpacity(double value);
    void setVectorScale(double value);
    void setVectorDensity(double value);
    void displayVectors(bool display);
    void displayColorbar(bool display);

    //CAMERA
    void ChangeView(int x, int y, int z);
    void ResetHeadcam();
    virtual void UpdateCameraConfig();

    //CENTER
    void PositionToCentered();
    void PositionToOriginal();

    //BACKGROUND
    double m_selectedColor[3];
    double m_unselectedColor[3];
    double m_labelColor[3];
    void setBackgroundSelectedColor(double a_selectedColor[]);
    void setBackgroundUnselectedColor(double a_unselectedColor[]);
    void setLabelColor(double a_labelColor[]);

};


#endif

