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

//asio network files
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
	ACTIVATE,
	ADD,
	REMOVE,
	READ,
	SET
};

enum UNIT_TYPE {
	THERMISTOR,
	DS18B20,
	DHT,
	FAN,
	HEATER
};

#endif