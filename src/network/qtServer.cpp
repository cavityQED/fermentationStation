#include "network/qtServer.h"

qtServer::qtServer(uint16_t port, QWidget* parent) :	QWidget(parent),
														net::server<MSG_TYPE>(port)
{

}										