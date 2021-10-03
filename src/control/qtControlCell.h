#ifndef QTCONTROLCELL_H
#define QTCONTROLCELL_H

#include "common/qtCommon.h"
#include "qtControlUnit.h"

class qtControlCell : public QWidget
{
	Q_OBJECT
public:
	qtControlCell(std::vector<qtControlUnit::params_t>& units, QWidget* parent = nullptr);
	virtual ~qtControlCell() {}

protected:
	std::map<uint16_t, qtControlUnit*>	m_units;
}