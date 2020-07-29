#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QColor>
#include <QFontDatabase>
#include <QLineEdit>
#include <iostream>
#include "mainWindow.h"

MainWindow::MainWindow():WindowWithImage(":/images/enterprise.png"
                                         ,true /*display toolbar*/)
{
//
// If you want to drag the whole window with the mouse
//
//    setDragable(true);
    show();
}

