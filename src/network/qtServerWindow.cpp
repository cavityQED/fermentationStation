#include "qtServerWindow.h"

qtServerWindow::qtServerWindow(QWidget* parent) : QMainWindow(parent)
{
	m_server = new qtServer(this);
	m_server->start();
	m_server->update();

	//setCentralWidget(m_server);
}

void qtServerWindow::addStation(net::message<MSG_TYPE>& msg, net_connection_ptr client)
{
	std::cout << "Adding Station\n";
	qtControlStation::params_t				station_params = {};
	std::vector<qtControlUnit::params_t>	cell_params = {};
	qtControlUnit::params_t					unit_params = {};

	uint8_t num_cells;
	msg >> num_cells;
	std::cout << "\tCells: " << (int)num_cells << '\n';

	uint8_t units_per_cell;
	msg >> units_per_cell;
	std::cout << "\tUnits per Cell: " << (int)units_per_cell << '\n';


	for(int c = 0; c < (int)num_cells; c++) {
		cell_params.clear();
		for(int u = 0; u < (int)units_per_cell; u++) {
			msg >> unit_params;
			cell_params.push_back(unit_params);
		}
		station_params.cells.push_back(cell_params);
	}

	station_params.rows = 1;
	station_params.cols = 4;
	station_params.client = client;

	qtControlStation* m_station = new qtControlStation(station_params, this);
	setCentralWidget(m_station);
	m_station->show();
}