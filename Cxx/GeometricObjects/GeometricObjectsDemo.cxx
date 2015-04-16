#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextMapper.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 
#include <vtkArrowSource.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkRegularPolygonSource.h>
#include <vtkSphereSource.h>
 
#include <vector>
 
int main(int, char *[])
{
  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm> > geometricObjectSources;
 
  geometricObjectSources.push_back(vtkSmartPointer<vtkArrowSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkConeSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkCubeSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkCylinderSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkDiskSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkLineSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkRegularPolygonSource>::New());
  geometricObjectSources.push_back(vtkSmartPointer<vtkSphereSource>::New());
  
  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;
  std::vector<vtkSmartPointer<vtkTextMapper> > textmappers;
  std::vector<vtkSmartPointer<vtkActor2D> > textactors;

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(12);
  textProperty->SetJustificationToCentered();

  // Create a source, renderer, mapper, and actor
  // for each object 
  for(unsigned int i = 0; i < geometricObjectSources.size(); i++)
    {
    geometricObjectSources[i]->Update();
 
    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(geometricObjectSources[i]->GetOutputPort());  
 
    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
 
    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textmappers[i]->SetInput(geometricObjectSources[i]->GetClassName());
    textmappers[i]->SetTextProperty(textProperty);

    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textactors[i]->SetMapper(textmappers[i]);
    textactors[i]->SetPosition(150, 16);

    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    }
 
  int gridDimensions = 3;
 
  // Need a renderer even if there is no actor
  for(size_t i = geometricObjectSources.size();
      i < static_cast<size_t>(gridDimensions * gridDimensions);
      i++)
    {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    } 

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 200;
  renderWindow->SetSize(rendererSize*gridDimensions, rendererSize*gridDimensions);
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
 
  for(int row = 0; row < gridDimensions; row++)
    {
    for(int col = 0; col < gridDimensions; col++)
      {
      int index = row*gridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {static_cast<double>(col) * rendererSize / (gridDimensions * rendererSize), 
			    static_cast<double>(gridDimensions - (row+1)) * rendererSize / (gridDimensions * rendererSize), 
			    static_cast<double>(col+1)*rendererSize / (gridDimensions * rendererSize), 
			    static_cast<double>(gridDimensions - row) * rendererSize / (gridDimensions * rendererSize)};
 
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(viewport);
      if(index > static_cast<int>(geometricObjectSources.size() - 1))
	{
	continue;
	}

      renderers[index]->AddActor(actors[index]);
      renderers[index]->AddActor(textactors[index]);
      renderers[index]->SetBackground(.4, .3, .2);
      }
    }
 
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderWindow->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
