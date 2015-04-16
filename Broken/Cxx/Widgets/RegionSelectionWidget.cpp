#include "RegionSelectionWidget.h"

#include <vtkBorderRepresentation.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkWidgetCallbackMapper.h>
#include <vtkWidgetEvent.h>
#include <vtkViewport.h>
#include <vtkRenderer.h>

vtkStandardNewMacro(RegionSelectionWidget);

RegionSelectionWidget::RegionSelectionWidget()
{
  this->CallbackMapper->SetCallbackMethod(vtkCommand::MiddleButtonReleaseEvent,
                                        vtkWidgetEvent::EndSelect,
                                        this, RegionSelectionWidget::EndSelectAction);
}

int RegionSelectionWidget::SubclassEndSelectAction()
{
  
  
  // Ideal method - coordinates must have already been set to World
//   vtkCoordinate* lowerLeft = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPositionCoordinate();
//   double lowerLeftCoord[3];
//   lowerLeft->GetValue(lowerLeftCoord);
//   std::cout << "Lower left: " << lowerLeftCoord[0] << " " << lowerLeftCoord[1] << " " << lowerLeftCoord[2] << std::endl;
//   
//   vtkCoordinate* upperRight = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition2Coordinate();
//   double upperRightCoord[3];
//   upperRight->GetValue(upperRightCoord);
//   std::cout << "Upper right: " << upperRightCoord[0] << " " << upperRightCoord[1] << " " << upperRightCoord[2] << std::endl;
  
  
  // Get the bottom left corner
//   double* lowerLeft;
//   lowerLeft = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition();
//   std::cout << "Lower left: " << lowerLeft[0] << " " << lowerLeft[1] << std::endl;
// 
//   double* upperRight;
//   upperRight = static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->GetPosition2();
//   std::cout << "Upper right: " << upperRight[0] << " " << upperRight[1] << std::endl;

  double* lowerLeft = static_cast<vtkBorderRepresentation*>(this->GetRepresentation())->GetPositionCoordinate()->GetComputedWorldValue (this->Renderer);
  std::cout << "Lower left: " << lowerLeft[0] << " " << lowerLeft[1] << std::endl;

  double* upperRight = static_cast<vtkBorderRepresentation*>(this->GetRepresentation())->GetPosition2Coordinate()->GetComputedWorldValue (this->Renderer);
  std::cout << "Upper right: " << upperRight[0] << " " << upperRight[1] << std::endl;

  return vtkBorderWidget::SubclassSelectAction(); // works
}
