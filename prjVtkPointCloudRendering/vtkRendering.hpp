/*=========================================================================

	Author:			kyungpyo94@naver.com
	Description:	Point cloud rendering using vtk(Visualization ToolKit)
	
=========================================================================*/

/**
* @class   CVtkRendering
* @brief   Rendering 3D points
*/

#pragma once

#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>

#include <vtkPointOccupancyFilter.h>
#include <vtkThreshold.h>
#include <vtkDataSetMapper.h>
#include <vtkImageData.h>

#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtksys/SystemTools.hxx>

// for points
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>

class CVtkRendering
{
public:
	CVtkRendering() {};
	~CVtkRendering() {};
	
	/**
	* arg: double array, number of points
	* ex) {x0,y0,z0, x1, y1, z1, ...}
	*/
	bool Set3dPoints(double* pointCloud, int num);

	/**
	* filtering
	* render points as cube
	* thresholding
	*/
	bool FilterRendering();

	/** 
	* mapper
	*/
	bool Mapper();

	/**
	* actor
	* arg: r, g, b
	* Set points color
	*/
	bool Actor(double r, double g, double b);

	/**
	* render & interactor
	* arg: r, g, b, height, width
	* set background coler
	* set window size
	*/
	bool RenderInteractor(
		double r, double g, double b, 
		double h, double w);

	/**
	* view controller
	* arg:	azimuth: horizontal rotation, 
			elevation: vertical rotaion, 
			dolly: camera's distance from focal point
	*/
	bool ControlView(double a, double e, double d);

	/**
	* display
	*/
	void Display();

private:
	vtkSmartPointer<vtkPoints>					m_points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkPolyData>				m_polyData = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkThreshold>				m_threshold = vtkSmartPointer<vtkThreshold>::New();
	vtkSmartPointer<vtkDataSetMapper>			m_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	vtkSmartPointer<vtkActor>					m_actor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkRenderer>				m_renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindowInteractor>	m_renDisplay = vtkSmartPointer<vtkRenderWindowInteractor>::New();
};