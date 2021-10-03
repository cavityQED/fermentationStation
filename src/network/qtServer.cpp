#include "qtServer.h"

qtServer::qtServer(QWidget* parent, uint16_t port) :	QWidget(parent),
														net::server<MSG_TYPE>(port)
{

}

qtServer::~qtServer() {}


void qtServer::update(size_t max_messages, bool wait)
{
	m_updateThread = std::thread([this]() {
		while(true) {
			net::server<MSG_TYPE>::update(-1, true);
		}
	});
}

void qtServer::onMessage(net_connection_ptr client, net::message<MSG_TYPE>& msg)
{
	qtControlUnit::params_t	p;
	msg >> p;
	auto u = qtControlUnit::getUnit(p.id);
	if(u) {
		//QApplication::postEvent(u, new msgEvent(client, msg));
	}
}									
