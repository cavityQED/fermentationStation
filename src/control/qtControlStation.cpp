#include "qtControlStation.h"

qtControlStation::qtControlStation(const params_t& p, QWidget* parent) : QWidget(parent)
{
	m_client = p.client;

	QGridLayout* grid = new QGridLayout();
	m_log = new qtLogger("testLog.txt", this);
	for(int row = 0; row < p.rows; row++) {
		for(int col = 0; col < p.cols; col++) {
			qtControlCell* cell = new qtControlCell(p.cells[row*p.cols + col]);
			cell->setClient(p.client);
			m_cells.push_back(cell);
			grid->addWidget(cell, row, col);

			for(auto& u : cell->getUnits())
				m_log->addUnit(u);
		}
	}

	qtControlCell* extra = new qtControlCell(p.extraCell, this);
	for(auto& u : extra->getUnits())
		m_log->addUnit(u);
	extra->setClient(p.client);
	grid->addWidget(extra, 0, p.cols, p.rows, 1);

	setLayout(grid);

	m_selectAct = new QAction(p.name);
	m_selectAct->setCheckable(true);
	connect(m_selectAct, &QAction::triggered, this, &qtControlStation::centralWidgetRequest);


	startTimer(std::chrono::seconds(10));
	m_log->start(10);
}