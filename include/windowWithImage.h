//-*-c++-*-

#pragma once
#ifndef WINDOWWITHIMAGE_H
#define WINDOWWITHIMAGE_H

#include "titleBarWindow.h"

//
// Here's an example displaying an image.
// Normally toolbar is true, otherwise you will just get borderless
// Window. 
//
class WindowWithImage : public TitleBarWindow {

    Q_OBJECT

  public:
    WindowWithImage(const char *imageFile, bool createToolBar = true):TitleBarWindow(createToolBar) {
        _image = new Image(imageFile);
        if (createToolBar) {
            resize(_image->width(),_image->height() + toolBar()->height());
        } else {
            resize(_image->width(),_image->height());
        }
        createMenus();
    }

  protected:

    Image    *_image;

    void createMenus(void) {
        if (toolBar() == nullptr) return; // never created
        
    // File Menu
        QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
        menuBar()->addMenu(fileMenu);
        QString menuStyle("QMenu::item{color: rgb(0, 0, 0);}");
        fileMenu->setStyleSheet(menuStyle);
        QAction *exitAction = new QAction(tr("&Exit"));
        connect(exitAction,&QAction::triggered,this,
                [=](bool) {
                    QMainWindow::close();
                });
        fileMenu->addAction(exitAction);
        
    // Edit Menu
        QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
        editMenu->setStyleSheet(menuStyle);
        editMenu->addAction(new QAction(tr("Example")));
    }
    
    virtual void paintEvent(QPaintEvent *) {
        QPainter p(this);
        if (toolBar() != nullptr) {
            _image->imageLabel()->resize(width(),height()- toolBar()->height());
            _image->imageLabel()->render(&p,QPoint(0,toolBar()->height()));
        } else {
            _image->imageLabel()->resize(width(),height());
            _image->imageLabel()->render(&p);
        }
        p.end();
    }

};



#endif //WINDOWWITHIMAGE_H
