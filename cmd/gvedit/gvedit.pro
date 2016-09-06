DEFINES += HAVE_CONFIG_H
LIBS += \
        -L..\..\Release\Graphviz\bin \
        -lgvc -lcgraph -lcdt

INCLUDEPATH += \
	$(SolutionDir) \
	$(SolutionDir)windows\include \
	$(SolutionDir)lib\gvc \
	$(SolutionDir)lib\common \
	$(SolutionDir)lib\pathplan \
	$(SolutionDir)lib\cgraph \
	$(SolutionDir)lib\cdt

QT += widgets printsupport
HEADERS = mainwindow.h mdichild.h csettings.h imageviewer.h ui_settings.h
SOURCES = main.cpp mainwindow.cpp mdichild.cpp csettings.cpp imageviewer.cpp
RESOURCES     = mdi.qrc

win32 {
	DESTDIR = $(SolutionDir)$(Configuration)\Graphviz\bin\
}

