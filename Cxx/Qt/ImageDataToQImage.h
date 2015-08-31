#ifndef ImageDataToQImage_H
#define ImageDataToQImage_H

#include "ui_ImageDataToQImage.h"

#include <QMainWindow>

class ImageDataToQImage : public QMainWindow, private Ui::ImageDataToQImage
{
  Q_OBJECT

public:
  ImageDataToQImage();
  
public slots:

  void on_btnDisplayImage_clicked();
};

#endif
