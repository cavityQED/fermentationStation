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
			qtControlUnit::connect(p, client);
			break;
		case UPDATE:
			msg >> p;
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
	//QApplication::postEvent(this, new connectEvent(client));
	return true;
}

bool qtServer::event(QEvent* e)
{
	if(e->type() == connectEvent::type) {
		std::cout << "Connection Event\n";
		auto conn = static_cast<connectEvent*>(e);
	/*
		qtControlStation::params_t				station_params;
		std::vector<qtControlUnit::params_t>	cell_params;

		qtControlUnit::params_t					htr_unit_params;
			htr_unit_params.type = THERMISTOR;
			std::strcpy(htr_unit_params.name, "Heater Temp");
		
		qtControlUnit::params_t					liq_unit_params;
			liq_unit_params.type = DS18B20;;
			std::strcpy(liq_unit_params.name, "Liquid Temp");

		qtControlUnit::params_t					out_unit_params;
			out_unit_params.type = THERMISTOR;
			std::strcpy(out_unit_params.name, "Jar Temp");

		station_params.client = conn->client;
		station_params.rows = 1;
		station_params.cols = 4;

		htr_unit_params.channel = 0;
		liq_unit_params.channel = 0;
		out_unit_params.channel = 1;
		cell_params.push_back(htr_unit_params);
		cell_params.push_back(liq_unit_params);
		cell_params.push_back(out_unit_params);
		station_params.cells.push_back(cell_params);

		cell_params.clear();
		htr_unit_params.channel = 2;
		liq_unit_params.channel = 1;
		out_unit_params.channel = 3;
		cell_params.push_back(htr_unit_params);
		cell_params.push_back(liq_unit_params);
		cell_params.push_back(out_unit_params);
		station_params.cells.push_back(cell_params);
		
		cell_params.clear();
		htr_unit_params.channel = 4;
		liq_unit_params.channel = 2;
		out_unit_params.channel = 5;
		cell_params.push_back(htr_unit_params);
		cell_params.push_back(liq_unit_params);
		cell_params.push_back(out_unit_params);
		station_params.cells.push_back(cell_params);

		cell_params.clear();
		htr_unit_params.channel = 6;
		liq_unit_params.channel = 3;
		out_unit_params.channel = 7;
		cell_params.push_back(htr_unit_params);
		cell_params.push_back(liq_unit_params);
		cell_params.push_back(out_unit_params);
		station_params.cells.push_back(cell_params);
		m_station = new qtControlStation(station_params, this);
		m_station->show();
	*/

		return true;
	}

	else
		return QWidget::event(e);
}