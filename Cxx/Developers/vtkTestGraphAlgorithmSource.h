#ifndef __vtkTestGraphAlgorithmSource_h
#define __vtkTestGraphAlgorithmSource_h

#include "vtkGraphAlgorithm.h"

class vtkTestGraphAlgorithmSource : public vtkGraphAlgorithm 
{
public:
  vtkTypeRevisionMacro(vtkTestGraphAlgorithmSource,vtkGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestGraphAlgorithmSource *New();
	
protected:
  vtkTestGraphAlgorithmSource();
  ~vtkTestGraphAlgorithmSource();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  
  int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestGraphAlgorithmSource(const vtkTestGraphAlgorithmSource&);  // Not implemented.
  void operator=(const vtkTestGraphAlgorithmSource&);  // Not implemented.

};

#endif
