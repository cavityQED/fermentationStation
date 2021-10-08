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

	void addStation(net::message<MSG_TYPE>& msg, net_connection_ptr client);

protected:
	virtual bool event(QEvent* e) {
		if(e->type() == connectEvent::type) {
			std::cout << "Connection Event\n";
			auto conn = static_cast<connectEvent*>(e);
			addStation(conn->msg, conn->client);
			return true;
		}
		else
			return QWidget::event(e);
	}

protected:
	qtServer*						m_server;
	qtControlStation*				m_centralStation;
	std::vector<qtControlStation*>	m_availableStations;
	QToolBar*						m_stationToolBar;

};

#endif