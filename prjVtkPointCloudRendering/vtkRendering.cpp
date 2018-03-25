#include "vtkRendering.hpp"

bool CVtkRendering::Set3dPoints(double* pointCloud, int num)
{

	for (int i = 0; i < num; i++)
	{
		double p[3];
		
		for (int j = 0; j < 3; j++)
			p[j] = pointCloud[i * 3 + j];

		m_points->InsertNextPoint(p);
	}

	m_polyData->SetPoints(m_points);

	return true;
}

bool CVtkRendering::FilterRendering()
{
	// render point as cube
	int dimension = 128;
	vtkSmartPointer<vtkPointOccupancyFilter> occupancy =
		vtkSmartPointer<vtkPointOccupancyFilter>::New();
	occupancy->SetInputData(m_polyData);
	occupancy->SetSampleDimensions(dimension, dimension, dimension);
	occupancy->SetOccupiedValue(1);
	occupancy->Update();
	// render point as cube

	// threshold
	m_threshold->SetInputConnection(occupancy->GetOutputPort());
	m_threshold->ThresholdByUpper(1); // Criterion is cells whose scalars are greater or equal to threshold.
	m_threshold->AllScalarsOff();
	// threshold

	return true;
}

bool CVtkRendering::Mapper()
{
	//m_mapper->SetInputConnection(m_threshold->GetOutputPort());
	m_mapper->SetInputData(m_polyData);
	m_mapper->ScalarVisibilityOff(); // 색깔나타남 없애면 검은색
	
	return true;
}

bool CVtkRendering::Actor(double r, double g, double b)
{
	m_actor->SetMapper(m_mapper);

	// Set colors
	/*vtkSmartPointer<vtkNamedColors> nc =
		vtkSmartPointer<vtkNamedColors>::New();
	nc->GetColorRGB("moccasin", rgb);
	actor->GetProperty()->SetColor(flesh);*/

	m_actor->GetProperty()->SetColor(r, g, b);
	// Set colors

	return true;
}

bool CVtkRendering::RenderInteractor(
	double r, double g, double b,
	double h, double w) 
{
	// Render
	m_renderer->SetBackground(r, g, b);
	// Render
	
	// set window size
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(m_renderer);
	renWin->SetSize(h, w);
	// set window size
	
	// Interactoer
	m_renDisplay->SetRenderWindow(renWin);
	// Interactoer

	// Add the actors to the renderer
	m_renderer->AddActor(m_actor);
	// Add the actors to the renderer

	return true;
}

bool CVtkRendering::ControlView(double a, double e, double d)
{
	// Generate an interesting view
	m_renderer->ResetCamera();
	m_renderer->GetActiveCamera()->Azimuth(a);
	m_renderer->GetActiveCamera()->Elevation(e);
	m_renderer->GetActiveCamera()->Dolly(d);
	m_renderer->ResetCameraClippingRange();
	// Generate an interesting view

	return true;
}

void CVtkRendering::Display()
{
	m_renDisplay->Initialize();
	m_renDisplay->Start();
}
