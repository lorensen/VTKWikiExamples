#include <vtkMultiBlockDataSet.h>
#include <vtkSphereSource.h>
#include <vtkNew.h>
#include <vtkCompositePolyDataMapper2.h>
#include <vtkMultiBlockDataGroupFilter.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main( int argc, char *argv[] )
{
  vtkNew<vtkMultiBlockDataGroupFilter> groupFilter;
  // The vtkMultiBlockDataGroupFilter allows multiple inputs and adds
  // each input as a block in its output multiblock dataset.
  for (int i = 0; i < 5; ++i)
  {
    for (int j = 0; j < 5; ++j)
    {
      vtkNew<vtkSphereSource> sphere;
      sphere->SetCenter(2 * i, 2 * j,0);
      sphere->SetRadius((50 - (i * i) - (j * j)) / 52.4);
      groupFilter->AddInputConnection(sphere->GetOutputPort());
    }
  }

  vtkNew<vtkCompositePolyDataMapper2> mapper;
  mapper->SetInputConnection(groupFilter->GetOutputPort());
  
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper.Get());

  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer.Get());
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow.Get());

  renderer->AddActor(actor.Get());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
