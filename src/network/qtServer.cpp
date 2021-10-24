#include "qtServer.h"

qtServer::qtServer(QWidget* parent, uint16_t port) :	QWidget(parent),
														net::server<MSG_TYPE>(port)
{	

}

qtServer::~qtServer() {
	if(m_updateThread.joinable())
		m_updateThread.join();
}


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
	std::cout << "RECIEVED Message:\n" << msg << '\n';
	qtControlUnit::params_t	p;

	switch(msg.header.id) {
		case CONNECT:
			msg >> p;
			std::cout << "Params: " << p << '\n';
			qtControlUnit::connect(p, client);
			break;
		case UPDATE:
			msg >> p;
			std::cout << "Params: " << p << '\n';
			qtControlUnit::update(p);
			break;
		case CLIENT_INFO:
			std::cout << "Recieved Client Info\n";
			QApplication::postEvent(parentWidget(), new connectEvent(client, msg));
			break;
		default:
			break;
	}
}									

bool qtServer::onClientConnect(net_connection_ptr client)
{
	return true;
}

bool qtServer::event(QEvent* e)
{
	if(e->type() == connectEvent::type) {
		std::cout << "Connection Event\n";
		auto conn = static_cast<connectEvent*>(e);

		return true;
	}

	else
		return QWidget::event(e);
}