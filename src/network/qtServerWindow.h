#ifndef QTSERVERWINDOW_H
#define QTSERVERWINDOW_H

#include "common/qtCommon.h"
#include "qtServer.h"

#include <QMainWindow>

class qtServerWindow : public QMainWindow
{
	Q_OBJECT
public:
	qtServerWindow(QWidget* parent = nullptr);

protected:
	qtServer*		m_server;

};

#endif