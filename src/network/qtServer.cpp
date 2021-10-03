#include "qtServer.h"

qtServer::qtServer(QWidget* parent, uint16_t port) :	QWidget(parent),
														net::server<MSG_TYPE>(port)
{	
	c = new QPushButton("CONNECT", this);
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
	std::cout << "NEW Message:\n" << msg << '\n';
	qtControlUnit::params_t	p;
	std::memcpy(&p, msg.body.data(), sizeof(qtControlUnit::params_t));
	PRINT_LINE;
	auto u = qtControlUnit::getUnit(p.id);
	if(u) {
		QApplication::postEvent(u, new msgEvent(client, msg));
	}
}									

bool qtServer::onClientConnect(net_connection_ptr client)
{
	auto u = qtControlUnit::getUnit(0);
	if(u) {
		u->setClient(client);
		connect(c, &QPushButton::released, u, &qtControlUnit::connectToClient);
	}
	return true;
}