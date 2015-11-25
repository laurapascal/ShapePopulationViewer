#ifndef REVERSEAXISCOLORDIALOGQT_H
#define REVERSEAXISCOLORDIALOGQT_H

#include <QDialog>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointData.h>
#include <vtkMath.h>
#include <vtkArrowSource.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextActor.h>
#include <iostream>
#include <QVTKWidget.h>
#include "ShapePopulationBase.h"


namespace Ui {
class reverseAxisColorDialogQT;
}

class reverseAxisColorDialogQT : public QDialog, public ShapePopulationBase
{
    Q_OBJECT

public:
    explicit reverseAxisColorDialogQT(QWidget *parent = 0);
    ~reverseAxisColorDialogQT();
    void AxisColor();

protected:
    std::vector< vtkSmartPointer<vtkActor> > m_arrowActors;
    std::vector< vtkSmartPointer<vtkTextActor> > m_labelActors;
    QVTKWidget * widget;

protected slots:
    void on_checkbox_reverseXAxisColor_toggled(bool checked);
    void on_checkbox_reverseYAxisColor_toggled(bool checked);
    void on_checkbox_reverseZAxisColor_toggled(bool checked);

signals:
    void sig_reverseXAxisColor_valueChanged(bool checked);
    void sig_reverseYAxisColor_valueChanged(bool checked);
    void sig_reverseZAxisColor_valueChanged(bool checked);

private:
    Ui::reverseAxisColorDialogQT *ui;
};

#endif // REVERSEAXISCOLORDIALOGQT_H
