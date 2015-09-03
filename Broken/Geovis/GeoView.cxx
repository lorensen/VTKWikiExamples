#include <vtkGeoFileTerrainSource.h>
#include <vtkGeoView.h>
#include <vtkGeoTerrain.h>
#include <vtkGeoGlobeSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int argc, char* argv[])
{

  // Create the geo view.
  vtkSmartPointer<vtkGeoView> view = vtkSmartPointer<vtkGeoView>::New();
  view->DisplayHoverTextOff();
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->SetSize(400,400);

  vtkSmartPointer<vtkGeoTerrain> terrain =
      vtkSmartPointer<vtkGeoTerrain>::New();
  vtkSmartPointer<vtkGeoSource> terrainSource;
  vtkGeoGlobeSource* globeSource = vtkGeoGlobeSource::New();
  terrainSource.TakeReference(globeSource);
  terrainSource->Initialize();
  terrain->SetSource(terrainSource);
  view->SetTerrain(terrain);

  //int retVal = vtkRegressionTestImage(win);
  view->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  // Shut down sources
  terrainSource->ShutDown();
  return EXIT_SUCCESS;
}
