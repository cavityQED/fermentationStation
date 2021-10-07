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

	//Print message bytes
	void msgBytePrint(net::message<MSG_TYPE>& msg) {
		uint8_t byte;

		int max = msg.header.size;

		for(int b = 0; b < max; b++){
			msg >> byte;
			std::cout << "[" << std::bitset<8>(byte) << "---\'" << /*(char)(byte) << */"\']";
			if((b+1) % 8)
				std::cout << ",\t";
			else
				std::cout << '\n';
		}
		std::cout << '\n';
	}

protected:
	virtual bool event(QEvent* e) {
		if(e->type() == connectEvent::type) {
			std::cout << "Connection Event\n";
			auto conn = static_cast<connectEvent*>(e);
			//msgBytePrint(conn->msg);
			addStation(conn->msg, conn->client);
			return true;
		}
		else
			return QWidget::event(e);
	}

protected:
	qtServer*		m_server;

	qtControlStation* m_station;

};

#endif