// prjVtkPointCloudRendering.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

// for generate random points
#include <cstdlib>
#include <ctime>

// vtk rendering
#include "vtkRendering.hpp"

int main()
{
	///* vtk test*/
	//CVtkRendering cVtk;

	//// random points generation
	//srand((unsigned int)time(NULL));
	//
	//double points[300];
	//const int numOfPoints = 100;

	//for (int i = 0; i < numOfPoints; ++i)
	//{
	//	for (int j = 0; j< 3; j++)
	//		points[i+j] = rand() % 100;;
	//}

	//// set input points
	//cVtk.Set3dPoints(points, numOfPoints);
	//cVtk.FilterRendering();
	//cVtk.Mapper();
	//cVtk.Actor(0.2, 0.3, 0.1);
	//cVtk.RenderInteractor(0.1, 0.5, 0.9, 512, 512);
	//cVtk.ControlView(120, 30, 1.25);
	//cVtk.Display();



	// Create the geometry of a point (the coordinate)
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	const float p[3] = { 1.0, 1.0, 1.0 };
	const float p1[3] = { 2.0, 2.0, 2.0 };
	const float p2[3] = { 3.0, 3.0, 3.0 };
	const float p3[3] = { 0.0, 0.0, 0.0 };

	// Create the topology of the point (a vertex)
	vtkSmartPointer<vtkCellArray> vertices =
		vtkSmartPointer<vtkCellArray>::New();
	vtkIdType pid[4];
	pid[0] = points->InsertNextPoint(p);
	pid[1] = points->InsertNextPoint(p1);
	pid[2] = points->InsertNextPoint(p2);
	pid[3] = points->InsertNextPoint(p3);


	// random points generation
	srand((unsigned int)time(NULL));

	double dpoints[300];
	const int numOfPoints = 100;

	for (int i = 0; i < numOfPoints; ++i)
	{
		for (int j = 0; j< 3; j++)
			dpoints[i + j] = rand() % 100;;
	}

	for (int i = 0; i < numOfPoints; i++)
	{
		double p[3];

		for (int j = 0; j < 3; j++)
			p[j] = dpoints[i * 3 + j];

		points->InsertNextPoint(p);
	}


	//vertices->InsertNextCell(1, pid);

	// Create a polydata object
	vtkSmartPointer<vtkPolyData> point =
		vtkSmartPointer<vtkPolyData>::New();

	// Set the points and vertices we created as the geometry and topology of the polydata
	point->SetPoints(points);
	//point->SetVerts(vertices);

	// point 들을 정육면체로 변환
	int dimension = 64;
	vtkSmartPointer<vtkPointOccupancyFilter> occupancy =
		vtkSmartPointer<vtkPointOccupancyFilter>::New();
	occupancy->SetInputData(point);
	occupancy->SetSampleDimensions(dimension, dimension, dimension);
	occupancy->SetOccupiedValue(1);
	occupancy->Update();
	// point 들을 정육면체로 변환


	vtkSmartPointer<vtkThreshold> threshold =
		vtkSmartPointer<vtkThreshold>::New();
	threshold->SetInputConnection(occupancy->GetOutputPort());
	threshold->ThresholdByUpper(1); // Criterion is cells whose scalars are greater or equal to threshold.
	threshold->AllScalarsOff();

	// Mapper
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(threshold->GetOutputPort());
	//mapper->SetInputData(point);
	mapper->ScalarVisibilityOff(); // 색깔나타남 없애면 검은색
								   // Mapper

								   // Actor
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// Actor

	// Set colors
	vtkSmartPointer<vtkNamedColors> nc =
		vtkSmartPointer<vtkNamedColors>::New();
	double flesh[3];
	nc->GetColorRGB("moccasin", flesh);
	actor->GetProperty()->SetColor(flesh);
	// Set colors

	// Render
	vtkSmartPointer<vtkRenderer> ren1 =
		vtkSmartPointer<vtkRenderer>::New();
	ren1->SetBackground(.3, .4, .6); // 배경색
									 // Render

									 // Render window
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	renWin->SetSize(512, 512);
	// Render window

	// Interactoer
	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	// Interactoer

	// Add the actors to the renderer
	ren1->AddActor(actor);
	// Add the actors to the renderer

	// Generate an interesting view
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Azimuth(120);
	ren1->GetActiveCamera()->Elevation(30);
	ren1->GetActiveCamera()->Dolly(1.25);
	ren1->ResetCameraClippingRange();
	// Generate an interesting view

	// Display
	iren->Initialize();
	iren->Start();
	// Display


    return 0;
}

