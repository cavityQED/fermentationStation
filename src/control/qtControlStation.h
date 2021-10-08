#ifndef QTCONTROLSTATION_H
#define QTCONTROLSTATION_H

#include "common/qtCommon.h"
#include "control/qtControlCell.h"

class qtControlStation : public QWidget
{
	Q_OBJECT
public:
	struct params_t {
		net_connection_ptr									client;
		std::vector<std::vector<qtControlUnit::params_t>>	cells;
		int													rows;
		int													cols;
	};

	qtControlStation(const params_t& p, QWidget* parent = nullptr);
	~qtControlStation() {}
	
protected:
	virtual void timerEvent(QTimerEvent* e) override {
		for(auto &c : m_cells)
			c->read();
	}

protected:
	std::vector<qtControlCell*>		m_cells;
	net_connection_ptr				m_client;
};

#endif