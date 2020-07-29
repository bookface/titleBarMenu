//-*-c++-*-

#pragma once
#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <QDialog>
#include <QMouseEvent>

//
// This is a class that creates a Borderless Windows and
// allows the mouse to move
//
// This is a template class to allow parent class to be
// a QDialog or any child of QWidget.
//
// If template is a QDialog, you can call
// setSizeGripEnabled(true) if desired
//

template <typename T>
class BorderLessWindow : public T {
  public:

// you can use right mouse instead of left
    BorderLessWindow( QWidget *parent = nullptr
                      ,bool dragable = false
                      ,bool useRight = false):T(parent) {
        setWindowFlags(Qt::FramelessWindowHint);
        _useRight  = useRight;
        _dragable = dragable;
        _useEither = false;
        _leftButton = false;
        _rightButton = false;
        _closeOnEscape = true;
        _enabled = true;
    }

// if true, Escape key calls close(), default is on
    void setCloseOnEscape(bool b) {
        _closeOnEscape = b;
    }

// set dragAble - default true, but you might want to keep
// a window in one position
    void setDragable(bool b) {
        _dragable = b;
    }


// If dragable, you can enable/disable moving the window
// if required. Usually, if you're interacting with the
// Window other then moving it, you'll want to disable
// movement
    void setEnable(bool b) { _enabled = b; }

// if true, either mouse button will move the window
    void useEitherMouse(bool b = true) {
        _useEither = b;
    }
    
  protected:

    virtual void mousePressEvent(QMouseEvent *event) {
        _leftButton = event->button() == Qt::LeftButton;
        _rightButton = event->button() == Qt::RightButton;
        _mousedownx = event->x();
        _mousedowny = event->y();
    }
    
    virtual void mouseMoveEvent(QMouseEvent *event) {
        bool pressed = (_useRight ? _rightButton : _leftButton);
        if (_useEither) pressed = true;
        if (pressed && _enabled) {
            int dx = event->x() - _mousedownx;
            int dy = event->y() - _mousedowny;
            if (_dragable) {
                move(x() + dx, y() + dy);
            }
        }
    }

    virtual void mouseReleaseEvent(QEvent *event ) {
        _leftButton = false;
        _rightButton = false;
    }

    virtual void keyPressEvent (QKeyEvent *k ) {
        if (_closeOnEscape) 
            if (k->key() == Qt::Key_Escape) {
                close();
            }
    }

    bool _dragable;
    bool _useRight;
    bool _useEither;
    bool _leftButton;
    bool _rightButton;
    bool _closeOnEscape;
    bool _enabled;
    int  _mousedownx;
    int  _mousedowny;
};




#endif //BORDERLESS_H
