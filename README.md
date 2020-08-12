Title Bar Window

Many programs today have moved the drop-down menus from a separate toolbar
to the title bar of the program (which is basically a waste of space
otherwise).

This code implements a title bar window, with drop down menus on the
title bar of the program. It creates a QMainWindow without the
built-in title bar and a title bar to replace it.

It will not work if your QMainWindow has a QToolBar.  Qt insists
on placing the ToolBar at the top of the Window with no option
to move it, so it will conflict with the MenuBar created here.
Still looking for a solution.

The classes are:

BorderLessWindow
   Create a plain Window with no decorations.  The Window can be
   set as dragable with left mouse, or with both the left
   and right mouse buttons.  The default is not draggable and
   left mouse only.

DragableMenu
   QMenuBar's are not normally moved with the mouse.  This class
   creates a QMenuBar that will drag it's parent window using
   the mouse.
   
TitleBarWindow
   This is a Window with a QMenuBar and min,max, and close
   buttons on the title bar.  No items are added to the
   QMenuBar.  They should be added by a child class.

   If using Designer:
      1. promote your QMenuBar to DragableMenu
      2. call TitleBarWindow(false) to disable addTools()
      3. call addTools(DragableMenu *) with your MenuBar created
         in Designer

WindowWithImage
   An example program.
   
   