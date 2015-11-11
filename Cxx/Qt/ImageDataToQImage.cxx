#include "ImageDataToQImage.h"

#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

// Constructor
ImageDataToQImage::ImageDataToQImage()
{
  this->setupUi(this);
}

QImage vtkImageDataToQImage(vtkImageData* imageData);

void ImageDataToQImage::on_btnDisplayImage_clicked()
{
  // Create an image data
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  image->SetDimensions(50,50,1);
#if VTK_MAJOR_VERSION <= 5
  #pragma message(VTK_MAJOR_VERSION)
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif

  int width = image->GetDimensions()[0];
  int height = image->GetDimensions()[1];

  for (int y = 0; y < height; y++)
    {
    for (int x = 0; x < width; x++)
      {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 0;
      pixel[1] = 255;
      pixel[2] = 0;
      }
    }

  QGraphicsScene* scene = new QGraphicsScene();

  this->graphicsView->setScene(scene);

  QImage qImage = vtkImageDataToQImage(image);
  scene->addPixmap(QPixmap::fromImage(qImage));

}

QImage vtkImageDataToQImage(vtkImageData* imageData)
{
  if (!imageData)
    {
    return QImage();
    }

  /// \todo retrieve just the UpdateExtent
  int width = imageData->GetDimensions()[0];
  int height = imageData->GetDimensions()[1];
  QImage image(width, height, QImage::Format_RGB32);
  QRgb* rgbPtr = reinterpret_cast<QRgb*>(image.bits()) +
    width * (height-1);
  unsigned char* colorsPtr = reinterpret_cast<unsigned char*>(
    imageData->GetScalarPointer());
  // mirror vertically
  for(int row = 0; row < height; ++row)
    {
    for (int col = 0; col < width; ++col)
      {
      // Swap rgb
      *(rgbPtr++) = QColor(colorsPtr[0], colorsPtr[1], colorsPtr[2]).rgb();
      colorsPtr +=  3;
      }
    rgbPtr -= width * 2;
    }
  return image;
}
