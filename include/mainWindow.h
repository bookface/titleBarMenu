//-*-c++-*-

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStatusBar>

#include "windowWithImage.h"

class MainWindow : public WindowWithImage
{
    Q_OBJECT

  public:
    MainWindow();
};

#endif //MAINWINDOW_H
