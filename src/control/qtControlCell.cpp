#include "qtControlCell.h"

qtControlCell::qtControlCell(const std::vector<qtControlUnit::params_t>& units, QWidget* parent) : QGroupBox(parent)
{
	QVBoxLayout* layout = new QVBoxLayout();

	for(auto& u : units) {
		qtControlUnit* tmp = new qtControlUnit(u, this);
		layout->addWidget(tmp);
		m_units.push_back(tmp);
	}

	QPushButton* button = new QPushButton("Read", this);
	layout->addWidget(button);
	connect(button, &QPushButton::released, this, &qtControlCell::read);

	setLayout(layout);
	setCheckable(true);
	setChecked(false);
	connect(this, &QGroupBox::toggled, this, &qtControlCell::activate);
}

void qtControlCell::setClient(net_connection_ptr client)
{
	m_client = client;
	for(auto &u : m_units)
		u->setClient(client);
}