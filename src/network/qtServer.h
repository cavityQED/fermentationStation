#ifndef QTSERVER_H
#define QTSERVER_H

#include "common/qtCommon.h"
#include "control/qtControlUnit.h"

class qtServer : public QWidget, public net::server<MSG_TYPE>
{
private:
	Q_OBJECT
public:
	/**
	*	Constructor
	*
	*/
	qtServer(QWidget* parent = nullptr, uint16_t port = 22);

	/**
	*	Destructor
	*		Joins the updateThread if joinable
	*
	*/
	virtual ~qtServer();

	virtual void update(size_t max_messages = -1, bool wait = false) override;

	/**
	*	onMessage
	*		Called when a message is recieved from a client
	*
	*/
	virtual void onMessage(net_connection_ptr client, net::message<MSG_TYPE>& msg) override;

	virtual bool onClientConnect(net_connection_ptr client) override {
		return true;
	}	

protected:
	//Thread for the server to read messages
	std::thread		m_updateThread;
};

#endif