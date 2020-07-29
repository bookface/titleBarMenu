//-*-c++-*-

#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>

class Image {
    
  public:
    Image(const QString &name, QLabel *label = nullptr) {
        _imageLabel = label == nullptr ? new QLabel : label;
        _imageLabel->setScaledContents(true);
        _imageLabel->setFrameShape(QFrame::NoFrame);
        loadImage(name);
    }
    QLabel *imageLabel(void) { return _imageLabel; }
    int width(void) { return _image->width();}
    int height(void) { return _image->height();}

  protected:

    void loadImage (const QString &fileName) {
        _image = new QImage(fileName);
        _imageLabel->setPixmap(QPixmap::fromImage(*_image));
    }

  private:
    QImage *_image;
    QLabel *_imageLabel;
};
    


#endif //IMAGE_H
