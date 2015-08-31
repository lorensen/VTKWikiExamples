#include <vtkImageData.h>
#include <vtkSmartPointer.h>

#include <QColor>
#include <QImage>
#include <QApplication>

#include "ImageDataToQImage.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  ImageDataToQImage imageDataToQImage;
  imageDataToQImage.show();

  return app.exec();
}
