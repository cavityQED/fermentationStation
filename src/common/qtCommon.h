#ifndef QTCOMMON_H
#define QTCOMMON_H

//std libraries
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <map>
#include <chrono>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <cmath>
#include <iostream>

//Qt libraries
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QEvent>
#include <QApplication>

//asio network files
#include "net_common.h"
#include "net_server.h"
#include "net_client.h"
#include "net_connection.h"
#include "net_message.h"

//Macro to print the line and file
#define PRINT_LINE {std::cout << "Line: " << __LINE__ << " in file:\n\t" << __FILE__ << "\n\n";}

//Assert macro
#define ASSERT(condition) { if(!(condition)) {std::cout << "\nAssert Failed: " << #condition << " @ " << __FILE__ << ", line " << __LINE__ << '\n'; break;}}

//Redefinitions
#define net_connection_ptr	std::shared_ptr<net::connection<MSG_TYPE>>

enum MSG_TYPE {
	ERROR,
	CONNECT,
	ADD,
	REMOVE,
	READ,
	SET,
	UPDATE,
};

enum UNIT_TYPE {
	THERMISTOR,
	DS18B20,
	DHT,
	FAN,
	HEATER
};

class msgEvent : public QEvent
{
public:
	static const QEvent::Type type = static_cast<QEvent::Type>(1231);

	msgEvent(net_connection_ptr ptr, const net::message<MSG_TYPE>& m);

	net_connection_ptr		client;
	net::message<MSG_TYPE>	msg;
};

class connectEvent : public QEvent
{
public:
	static const QEvent::Type type = static_cast<QEvent::Type>(1232);

	connectEvent(net_connection_ptr ptr, const net::message<MSG_TYPE>& m = {}) :
		QEvent(type), client(ptr), msg(std::move(m)) {}

	net_connection_ptr		client;
	net::message<MSG_TYPE>	msg;
};

#endif