#---------------------------------------------------------------------------
# QT Static needs a lot more stuff.  The Qt folks also change some of the file names
# with each version.  These work with Version 5.9.1.
#
if (QT_STATIC)
    add_definitions(-DQT_STATIC)
    if (${Qt5Widgets_VERSION} VERSION_GREATER 5.9.0)

        find_library(platformSupport Qt5PlatformCompositorSupport
            HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${platformSupport})

        find_library(harfbuzz qtharfbuzz HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${harfbuzz})

        find_library(qtfreetype qtfreetype HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${qtfreetype})

        find_library(qtpcre2 qtpcre2 HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${qtpcre2})

        find_library(accessible Qt5AccessibilitySupport HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${accessible})

        find_library(fontengine Qt5FontDatabaseSupport HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${fontengine})

        find_library(png qtlibpng HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${png})

        find_library(eventdispatcher Qt5EventDispatcherSupport
            HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${eventdispatcher})

        find_library(themeSupport Qt5ThemeSupport HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${themeSupport})

        find_library(qtmain qtmain HINTS ${_qt5Core_install_prefix}/lib)
        set(QT_LIBRARIES ${QT_LIBRARIES} ${qtmain})

        set(QT_LIBRARIES ${QT_LIBRARIES} UxTheme Dwmapi Mincore)

    endif()

    if(WIN32)
        find_library(qwindows qwindows HINTS ${_qt5Core_install_prefix}/plugins/platforms)
        set (QT_LIBRARIES ${QT_LIBRARIES} ${qwindows})
    endif()
endif()
