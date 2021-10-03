#include "qtControlCell.h"

qtControlCell::qtControlCell(std::vector<qtControlUnit::params_t>& units, QWidget* parent) : QWidget(parent)
{
	for(auto& u : units) {
		qtControlUnit* tmp = new qtControlUnit(u, this);
		m_units.push_back(tmp);
	}
}