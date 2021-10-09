#include "qtControlUnit.h"

std::map<uint16_t, qtControlUnit*>	qtControlUnit::__allUnits	= {};
uint16_t							qtControlUnit::__id			= 0;

qtControlUnit::qtControlUnit(const params_t& p, QWidget* parent) : 	QGroupBox(parent)
{
	m_params = p;
	m_params.id = __id++;
	m_name.append(p.name);

	__allUnits.insert(std::pair<uint16_t, qtControlUnit*>(m_params.id, this));

	m_labelName 	= new QLabel();
	m_labelName->setText(p.name);
	
	m_labelChannel	= new QLabel();
	m_labelChannel->setText("Channel " + QString::number(m_params.channel));
	
	m_labelType		= new QLabel();
	m_labelType->setText(unitTypeQString(m_params.type));

	m_labelValue	= new QLCDNumber();
	m_labelValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	m_labelValue->setFixedSize(50,30);
	m_labelValue->setDigitCount(4);
	m_labelValue->setSegmentStyle(QLCDNumber::Filled);


	QGridLayout* grid = new QGridLayout();
	grid->addWidget(m_labelName, 0, 0);
	grid->addWidget(m_labelType, 3, 0);
	grid->addWidget(m_labelChannel, 4, 0);
	grid->addWidget(m_labelValue, 2, 2, 3, 1);
	if(m_params.type == FAN || m_params.type == HEATER) {
		m_incButton = new QPushButton(QChar(0x25B2));
		m_decButton = new QPushButton(QChar(0x25BC));

		grid->addWidget(m_incButton, 1, 1);
		grid->addWidget(m_decButton, 3, 1);

		QWidget::connect(m_incButton, &QPushButton::released, this, &qtControlUnit::increase);
		QWidget::connect(m_decButton, &QPushButton::released, this, &qtControlUnit::decrease);
	}
	else
		grid->setColumnMinimumWidth(1, 40);
	
	setLayout(grid);

	editNameAct = new QAction(tr("Edit Name"), this);
	QObject::connect(editNameAct, &QAction::triggered, this, &qtControlUnit::editName);
}

qtControlUnit::~qtControlUnit() 
{

}

uint16_t qtControlUnit::addUnit(const params_t& p, QWidget* parent)
{
	qtControlUnit* tmp = new qtControlUnit(p, parent);

	return tmp->id();
}

bool qtControlUnit::connect(const params_t& p, net_connection_ptr client)
{
	auto u = getUnit(p.id);
	if(u) {
		u->setClientID(p.client_id);
		u->setClient(client);
		u->setConnected(true);
		return true;
	}
	else {
		std::cout << "Error Connecting\n";
		return false;	
	}
}

void qtControlUnit::update(uint16_t id, double v)
{
	auto u = getUnit(id);
	if(u && u->isActive()) {
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

void qtControlUnit::contextMenuEvent(QContextMenuEvent* e)
{
	QMenu menu(this);
	menu.addAction(editNameAct);
	menu.exec(e->globalPos());
}