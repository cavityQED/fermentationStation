#ifndef QTSERVER_H
#define QTSERVER_H

#include "common/qtCommon.h"

class qtServer : public QWidget, public net::server<MSG_TYPE>
{
	Q_OBJECT
public:
	/**
	*	Constructor
	*
	*/
	qtServer(uint16_t port = 22, QWidget* parent = nullptr);
	
};

#endif