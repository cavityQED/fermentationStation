#ifndef QTCONTROLCELL_H
#define QTCONTROLCELL_H

#include "common/qtCommon.h"
#include "qtControlUnit.h"

class qtControlCell : public QGroupBox
{
	Q_OBJECT
public:
	qtControlCell(const std::vector<qtControlUnit::params_t>& units, QWidget* parent = nullptr);
	virtual ~qtControlCell() {}

	void setClient(net_connection_ptr client);

public slots:
	void connectToClient() {
		for(auto &u : m_units)
			u->connectToClient();
	}

	void activate(bool a) {
		for(auto &u : m_units) {
			u->setActive(a);
			if(a && !(u->isConnected()))
				u->connectToClient();	
		}
	}

	void read() {
		for(auto &u : m_units) {
			if(u->isActive())
				u->read();
		}
	}

protected:
	std::vector<qtControlUnit*>		m_units;
	net_connection_ptr				m_client;
};

#endif