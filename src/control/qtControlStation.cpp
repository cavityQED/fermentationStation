#include "qtControlStation.h"

qtControlStation::qtControlStation(const params_t& p, QWidget* parent) : QWidget(parent)
{
	m_client = p.client;

	QGridLayout* grid = new QGridLayout();

	for(int row = 0; row < p.rows; row++) {
		for(int col = 0; col < p.cols; col++) {
			qtControlCell* cell = new qtControlCell(p.cells[row*p.cols + col]);
			cell->setClient(p.client);
			m_cells.push_back(cell);
			grid->addWidget(cell, row, col);
		}
	}

	setLayout(grid);

	startTimer(std::chrono::seconds(5));
}