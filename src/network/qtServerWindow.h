#ifndef QTSERVERWINDOW_H
#define QTSERVERWINDOW_H

#include "common/qtCommon.h"
#include "qtServer.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QStackedWidget>

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

public slots:
	void changeCentralWidget() {
		std::cout << "Setting Widget\n";
		//Should check if sender is really an available station
		m_stack->setCurrentWidget(static_cast<QWidget*>(QWidget::sender()));
	}

protected:
	qtServer*						m_server;
	std::vector<qtControlStation*>	m_availableStations;
	QStackedWidget*					m_stack;
	QToolBar*						m_stationToolBar;
	QActionGroup*					m_toolBarActionGroup;

};

#endif