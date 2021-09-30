/*	{CMAKE_SOURCE_DIR}/src/control/qtControlUnit.cpp	*/
#include "control/qtControlUnit.h"

std::map<uint16_t, qtControlUnit*>	__allUnits	= {};
uint16_t							__id		= 0;

qtControlUnit::qtControlUnit(const params_t& p, QWidget* parent) : 	QWidget(parent), 
																	m_params(std::move(p))
{
	m_params.id = __id++;

	__allUnits.insert(std::pair<uint16_t, qtControlUnit*>(m_params.id, this));

	//Main layout
	QVBoxLayout* layout = new QVBoxLayout();

	m_label	= new QLabel();
	m_label->setText(m_params.name);
	layout->addWidget(m_label);

	m_valueEdit = new QLineEdit();
	m_valueEdit->setReadOnly(true);
	layout->addWidget(m_valueEdit);

	setLayout(layout);
}

bool qtControlUnit::activate(const params_t& p, std::shared_ptr<net::connection<MSG_TYPE>> client)
{
	auto u = getUnit(p.id);
	if(u) {
		u->setClientID(p.client_id);
		u->setName(p.name);
		u->setClient(client);
		u->setActive(true);
		return true;
	}
	return false;	
}

bool qtControlUnit::deactivate(uint16_t id)
{
	auto u = getUnit(id);
	if(u) {
		u->setActive(false);
		return true;
	}
	return false;
}

void qtControlUnit::update(uint16_t id, double v)
{
	auto u = getUnit(id);
	if(u) {
		u->setValue(v);
		u->emit valueChanged(v);
	}
}