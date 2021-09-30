#ifndef QTCONTROLUNIT_H
#define QTCONTROLUNIT_H

#include "common/qtCommon.h"

class qtControlUnit
{
	Q_OBJECT
public:
	//Struct to pass info 
	struct prop_t {
		uint16_t		id;
		uint8_t			channel;
		UNIT_TYPE		type;
		QString			name;
		double			value;
	};

	qtControlUnit(const properties& p, QWidget* parent = nullptr);
	~qtControlUnit() {}

	//Setters
	void setID	(uint16_t id)				{m_id = id;}
	void setName(const std::string name)	{m_name = name;}

	//Getters
	uint16_t	id()		 const	{return m_id;}
	uint8_t		channel()	 const	{return m_channel;}
	UNIT_TYPE	type()		 const	{return m_type;}
	QString		name()		 const	{return m_name;}
	prop_t		properties() const	{return m_properties;}

protected:
	//Static members
	static std::map<uint16_t, qtControlUnit*>		__tmpUnits;		//Units that have been created but not activated
	static std::map<uint16_t, qtControlUnit*>		__activeUnits;	//Active units
	static uint16_t									__tmp_id;		//Temporary id for inactive units - real id obtained from client

	//Basic Unit Info
	uint16_t	m_id;
	uint8_t		m_channel;
	UNIT_TYPE	m_type;
	QString		m_name;
	double		m_value;
	prop_t		m_properties;

	//Qt Members
	QLineEdit*	m_valueEdit		//Display the unit's value
	QLabel*		m_label			//Display the unit's name
};

#endif