#include "qtServerWindow.h"

qtServerWindow::qtServerWindow(QWidget* parent) : QMainWindow(parent)
{
	m_server = new qtServer(this);
	m_server->start();
	m_server->update();

	setGeometry(100, 100, 1024, 480);

	m_stationToolBar = new QToolBar("Stations");
	addToolBar(Qt::LeftToolBarArea, m_stationToolBar);
	m_stationToolBar->setOrientation(Qt::Vertical);

	m_toolBarActionGroup = new QActionGroup(this);

	m_stack = new QStackedWidget(this);
	setCentralWidget(m_stack);
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

	uint8_t extra_units;
	msg >> extra_units;
	std::cout << "\tExtra Units: " << (int)extra_units << '\n';

	for(int c = 0; c < (int)num_cells; c++) {
		cell_params.clear();
		for(int u = 0; u < (int)units_per_cell; u++) {
			msg >> unit_params;
			cell_params.push_back(unit_params);
		}
		station_params.cells.push_back(cell_params);
	}

	for(int e = 0; e < (int)extra_units; e++) {
		msg >> unit_params;
		station_params.extraCell.push_back(unit_params);
	}
	station_params.cols = 4;
	station_params.rows = 1;
	station_params.client = client;
	station_params.name = QString::number(m_availableStations.size()+1);

	qtControlStation* tmp = new qtControlStation(station_params, this);
	m_stack->addWidget(tmp);
	connect(tmp, &qtControlStation::centralWidgetRequest, this, &qtServerWindow::changeCentralWidget);

	m_stationToolBar->addAction(tmp->selectAction());
	m_toolBarActionGroup->addAction(tmp->selectAction());
}

void qtServerWindow::addStation(qtControlStation::params_t& params)
{
	qtControlStation* tmp = new qtControlStation(params, this);

	m_stack->addWidget(tmp);
	connect(tmp, &qtControlStation::centralWidgetRequest, this, &qtServerWindow::changeCentralWidget);

	m_stationToolBar->addAction(tmp->selectAction());
	m_toolBarActionGroup->addAction(tmp->selectAction());
}

bool qtServerWindow::event(QEvent* e)
{
	if(e->type() == connectEvent::type)
	{
		connectEvent* cEvent = static_cast<connectEvent*>(e);
		addStation(cEvent->msg, cEvent->client);
		return true;
	}
	else
		return QWidget::event(e);
}