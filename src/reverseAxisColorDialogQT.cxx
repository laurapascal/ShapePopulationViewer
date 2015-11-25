#include "reverseAxisColorDialogQT.h"
#include "ui_reverseAxisColorDialogQT.h"


reverseAxisColorDialogQT::reverseAxisColorDialogQT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reverseAxisColorDialogQT)
{
    ui->setupUi(this);
}

reverseAxisColorDialogQT::~reverseAxisColorDialogQT()
{
    delete ui;
}

void reverseAxisColorDialogQT::AxisColor()
{

    double arrowTranslate[6][3] = {{0.2,0.0,0.0},
                                   {0.15,0.15,0.0},
                                   {0.0,0.2,0.0},
                                   {-0.2,0.0,0.0},
                                   {-0.15,-0.15,0.0},
                                   {0.0,-0.2,0.0}};
    double labelTranslate[6][2] = {{265,127},
                                   {245,200},
                                   {135.0,235.0},
                                   {10,130},
                                   {55.0,55.0},
                                   {130.0,20.0}};
    const char* label[6] = {"Z Superior","X Right","Y Anterior","-Z Inferior","-X Left","-Y Posterior"};

    for(int i = 0; i < 6; i++)
    {

        /// Create an arrows
        vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();
        arrow->Update();

        //translate the sphere
        vtkSmartPointer<vtkTransform> translation = vtkSmartPointer<vtkTransform>::New();

        translation->Translate(arrowTranslate[i]);
        if(i < 3) translation->RotateZ(i*45);
        else translation->RotateZ(i*45 + 45);
        translation->Scale(0.35, 0.35, 0.35);

        vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
#if (VTK_MAJOR_VERSION < 6)
        transformFilter->SetInputConnection(arrow->GetProducerPort());
#else
        transformFilter->SetInputData(arrow->GetOutput());
#endif
        transformFilter->SetTransform(translation);
        transformFilter->Update();

        //mapper of the sphere
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if (VTK_MAJOR_VERSION < 6)
        mapper->SetInputConnection(transformFilter->GetOutputPort());
#else
        mapper->SetInputData(transformFilter->GetOutput());
#endif


        // Create a actor
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(m_colorAxis[i]);
        m_arrowActors.push_back(actor);

        // label
        vtkSmartPointer<vtkTextActor> labelActor = vtkSmartPointer<vtkTextActor>::New();
        labelActor->GetTextProperty()->SetFontSize ( 14 );
        labelActor->GetTextProperty()->BoldOn();
        labelActor->SetInput ( label[i] );
        labelActor->GetTextProperty()->SetColor ( m_colorAxis[i] );
        labelActor->SetPosition(labelTranslate[i]);
        m_labelActors.push_back(labelActor);


    }

    ///****************************************************************************///
    ///****************************************************************************///
    ///****************************************************************************///


    /// VISUALIZATION
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renderWindow = vtkRenderWindow::New();
    renderWindow->AddRenderer(renderer);
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    interactor->SetRenderWindow(renderWindow);
    vtkInteractorStyleTrackballCamera * interactorStyle = vtkInteractorStyleTrackballCamera::New();
    interactor->SetInteractorStyle(interactorStyle);

    // Add the actors to the renderer
    for(int i = 0 ; i < 6; i++)
    {
        renderer->AddActor(m_arrowActors[i]);
        renderer->AddActor2D(m_labelActors[i]);
    }

    // Set the background and size
    renderer->SetBackground(1, 1, 1); // background : gray
    renderer->ResetCamera();


    widget = new QVTKWidget(ui->widget_AxisColor);
    widget->resize(346,272);
    widget->SetRenderWindow(renderWindow);
//    interactor->EnableRenderOff();

    widget->show();
    interactor->Start();

}

void reverseAxisColorDialogQT::on_checkbox_reverseXAxisColor_toggled(bool checked)
{
    double colorTemp[3];
    for(int j = 0; j < 3; j++)
    {
        colorTemp[j] = m_colorAxis[1][j];
        m_colorAxis[1][j] = m_colorAxis[4][j];
        m_colorAxis[4][j] = colorTemp[j];
    }

    m_arrowActors[1]->GetProperty()->SetColor(m_colorAxis[1]);
    m_arrowActors[4]->GetProperty()->SetColor(m_colorAxis[4]);
    m_labelActors[1]->GetTextProperty()->SetColor ( m_colorAxis[1] );
    m_labelActors[4]->GetTextProperty()->SetColor ( m_colorAxis[4] );

    widget->GetRenderWindow()->Render();

    emit sig_reverseXAxisColor_valueChanged(checked);

}

void reverseAxisColorDialogQT::on_checkbox_reverseYAxisColor_toggled(bool checked)
{
    double colorTemp[3];
    for(int j = 0; j < 3; j++)
    {
        colorTemp[j] = m_colorAxis[2][j];
        m_colorAxis[2][j] = m_colorAxis[5][j];
        m_colorAxis[5][j] = colorTemp[j];
    }


    m_arrowActors[2]->GetProperty()->SetColor(m_colorAxis[2]);
    m_arrowActors[5]->GetProperty()->SetColor(m_colorAxis[5]);
    m_labelActors[2]->GetTextProperty()->SetColor ( m_colorAxis[2] );
    m_labelActors[5]->GetTextProperty()->SetColor ( m_colorAxis[5] );

    widget->GetRenderWindow()->Render();

    emit sig_reverseYAxisColor_valueChanged(checked);
}

void reverseAxisColorDialogQT::on_checkbox_reverseZAxisColor_toggled(bool checked)
{
    double colorTemp[3];
    for(int j = 0; j < 3; j++)
    {
        colorTemp[j] = m_colorAxis[0][j];
        m_colorAxis[0][j] = m_colorAxis[3][j];
        m_colorAxis[3][j] = colorTemp[j];
    }

    m_arrowActors[0]->GetProperty()->SetColor(m_colorAxis[0]);
    m_arrowActors[3]->GetProperty()->SetColor(m_colorAxis[3]);
    m_labelActors[0]->GetTextProperty()->SetColor ( m_colorAxis[0] );
    m_labelActors[3]->GetTextProperty()->SetColor ( m_colorAxis[3] );

    widget->GetRenderWindow()->Render();

    emit sig_reverseZAxisColor_valueChanged(checked);
}

