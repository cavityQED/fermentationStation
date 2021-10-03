#include "qtControlUnit.h"

std::map<uint16_t, qtControlUnit*>	qtControlUnit::__allUnits	= {};
uint16_t							qtControlUnit::__id			= 0;

qtControlUnit::qtControlUnit(const params_t& p, QWidget* parent) : 	QWidget(parent)
{
	m_params = p;
	m_params.id = __id++;

	__allUnits.insert(std::pair<uint16_t, qtControlUnit*>(m_params.id, this));

	//Main layout
	QVBoxLayout* layout = new QVBoxLayout();

	m_label	= new QLabel();
	layout->addWidget(m_label);

	m_valueEdit = new QLineEdit();
	m_valueEdit->setReadOnly(true);
	layout->addWidget(m_valueEdit);

	setLayout(layout);
}

qtControlUnit::~qtControlUnit() 
{

}

uint16_t qtControlUnit::addUnit(const params_t& p, QWidget* parent)
{
	qtControlUnit* tmp = new qtControlUnit(p, parent);

	return tmp->id();
}

bool qtControlUnit::activate(const params_t& p, net_connection_ptr client)
{
	auto u = getUnit(p.id);
	if(u) {
		u->setClientID(p.client_id);
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
		u->emit valueChange(v);
	}
}

bool qtControlUnit::event(QEvent* e)
{
	if(e->type() == msgEvent::type) {
		auto m = static_cast<msgEvent*>(e);
		std::cout << "[" << m_params.id << "] Recieved Message:\n" << m->msg << '\n';
		return true;
	}

	else
		return QWidget::event(e);
}