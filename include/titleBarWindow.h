//-*-c++-*-

#pragma once
#ifndef TITLEBARWINDOW_H
#define TITLEBARWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStatusBar>
#include <QPainter>
#include <QToolBar>
#include <QMenuBar>
#include <QDebug>
#include <QApplication>
#include <QStyle>

#include "image.h"
#include "borderLess.h"

//
// We're going to add a QMenuBar to the top of our Window.  Normally,
// mouse move events do not affect a QMenubar, so we need to create our
// own, which will move the parent Window with the mouse.
//
class DragableMenu : public QMenuBar {

    Q_OBJECT

    QWidget *_parent;
    QPoint   _mouse;
    bool     _pressed = false;
    
  public:

    DragableMenu(QWidget *parent):QMenuBar(parent) {_parent = parent;}

  protected:

    virtual void mousePressEvent(QMouseEvent *event) override {
    //
    // Check if there's a QAction at the mouse position.  If
    // so, we don't want to move the Window, we want to
    // trigger the QAction
    //
        auto action = actionAt(QPoint(event->x(),event->y()));
        if (action == nullptr) {
            _pressed = true;
            _mouse.setX(event->x());
            _mouse.setY(event->y());
        }
        QMenuBar::mousePressEvent(event);
    }
    
//
// Move the parent window with the moveEvent
//
    virtual void mouseMoveEvent(QMouseEvent *event) override {
        if (_pressed) {
            int dx = event->x() - _mouse.x();
            int dy = event->y() - _mouse.y();
            _parent->move(_parent->x() + dx
                          ,_parent->y() + dy);
        }
    }

    virtual void mouseReleaseEvent(QMouseEvent *event ) override {
        _pressed = false;
        QMenuBar::mouseReleaseEvent(event);
    }
};

//
// Window with our own Title bar + Menu + Minimize + Maximize + Close
// The toolbar is optional, default is enabled. Nothing is
// added to the Menu, the child class must add
// whatever menu options it wants.
//
// If using a QMenuBar with Designer:
//   1. promote your QMenuBar to DragableMenu
//   2. call TitleBarWindow(false) to disable addTools()
//   3. call addTools(DragableMenu *) with your MenuBar from Designer
//
class TitleBarWindow : public BorderLessWindow<QMainWindow> {

    Q_OBJECT

  public:

    TitleBarWindow(bool toolBar = true) 
        :BorderLessWindow<QMainWindow>() {
        statusBar()->setSizeGripEnabled(true);
    // if no toolbar, it's just a borderless Window
        if (toolBar) {
            addTools();
        }
    }

    DragableMenu *menuBar(void) { return _menuBar; }
    QToolBar     *toolBar(void) { return _toolBar; }

  protected:

//
// if you want to change the styleSheet, both the toolbar
// and menubar need to be changed
//
    void setStyleSheet(const QString &sheet) {
        _toolBar->setStyleSheet(sheet);
        _menuBar->setStyleSheet(sheet);
    }

//
// Create the Toolbar with your own
// (probably Designer built) menubar
//
    void addTools(DragableMenu *menuBar) {
        _menuBar = menuBar;
        addTools();
    }

    void addTools(void) {
        _toolBar = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,_toolBar);
        _toolBar->setMouseTracking(true);
        _toolBar->setFloatable(false);
        _toolBar->setMovable(false);

    // Menu bar that moves this Window
        if (_menuBar == nullptr)
            _menuBar = new DragableMenu(this);
        _toolBar->addWidget(_menuBar);

    // minimize button
        QIcon icon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
        QAction *minimizeAction = _toolBar->addAction(icon,"");
        connect(minimizeAction,&QAction::triggered,this,
                [=](bool) {
                    showMinimized();
                });

    // maximize button
        QIcon icon2(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
        QAction *maximizeAction = _toolBar->addAction(icon2,"");
        connect(maximizeAction,&QAction::triggered,this,
                [=](bool) {
                    if (isMaximized()) showNormal();
                    else showMaximized();
                });

    // close button
        QIcon icon3(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
        QAction *closeAction = _toolBar->addAction(icon3,"");
        connect(closeAction,&QAction::triggered,this,
                [=](bool) {
                    QMainWindow::close();
                });

    }

    QToolBar     *_toolBar = nullptr;
    DragableMenu *_menuBar = nullptr;

};

#endif //TITLEBARWINDOW_H
