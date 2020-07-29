#include <QApplication>
#include "mainWindow.h"

#ifdef QT_STATIC
  #include <QtPlugin>
  Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    return app.exec();
}

