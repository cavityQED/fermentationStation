#ifndef QTCONTROLUNIT_H
#define QTCONTROLUNIT_H

#include "common/qtCommon.h"

class qtControlUnit : public QWidget
{
private:
	Q_OBJECT

public:
	//Struct to pass info 
	struct params_t {
		uint16_t		id;
		uint16_t		client_id;
		uint8_t			channel;
		UNIT_TYPE		type;
		QString			name;
		double			value;
	};

	/*
	*	Contructor
	*		
	*		Initializes property variables
	*		Creates Qt Widgets and initializes values
	*		Adds an entry to the tmpUnits map
	*/
	qtControlUnit(const params_t& p, QWidget* parent = nullptr);
	~qtControlUnit();

	/**
	*	Get Unit
	*		
	*/
	static qtControlUnit* getUnit(uint16_t id)			{return __allUnits.contains(id)? __allUnits[id] : nullptr;}
	static qtControlUnit* getUnit(const params_t& p)	{return getUnit(p.id);}

	/**
	*	Activate
	*		Connect unit to remote sensor on client device
	*
	*/
	static bool activate(const params_t& p, std::shared_ptr<net::connection<MSG_TYPE>> client);

	/**
	*	Deactivate
	*		Remove the unit from active units
	*		Give unit new temp id and add to temp units
	*
	*/
	static bool deactivate(uint16_t id);
	static bool deactivate(const params_t& p) {return deactivate(p.id);}

	/**
	*	Update
	*		Called on reciept of an update message from the client
	*		Updates the unit's value, emits the valueChanged signal
	*
	*/
	static void update(uint16_t id, double v);
	static void update(const params_t& p) {update(p.id, p.value);}


	//Setters
	void setClientID	(uint16_t id)			{m_params.client_id = id;}
	void setLabel(const QString name)			{m_label->setText(name);}
	void setName(const QString name)			{m_params.name = name; setLabel(name);}
	void setEdit(double v)						{m_valueEdit->setText(QString::number(v));}
	void setValue(double v)						{m_params.value = v; setEdit(v);}
	void setClient(net_connection_ptr client)	{m_client = client;}
	void setActive(bool active)					{m_active = active;}

	//Getters
	uint16_t	id()		const	{return m_params.id;}
	uint16_t	clientID()	const	{return m_params.client_id;}
	uint8_t		channel()	const	{return m_params.channel;}
	UNIT_TYPE	type()		const	{return m_params.type;}
	QString		name()		const	{return m_params.name;}
	params_t	params()	const	{return m_params;}
	bool		isActive()	const	{return m_active;}

protected:
	bool event(QEvent* e);

public slots:
	/**
	*	Read
	*		Sends a READ message to the client
	*
	**/
	void read() {
		if(!m_active)
			return;

		net::message<MSG_TYPE> msg;
		msg.header.id = READ;
		msg << m_params;
		if(m_client && m_client->isConnected()) {
			//get server pointer
			//send message through pointer
		}
	}

	/**
	*	Connect to Client
	*		Send an activate message to the client to connect the unit with the associated client object
	*
	*/
	void connectToClient() {
		if(m_client) {
			net::message<MSG_TYPE> msg;
			msg.header.id = ACTIVATE;
			msg << m_params;
			//get server pointer
			//send message through pointer
		}
	}

signals:
	void valueChange(double v);

protected:
	//Static members
	static std::map<uint16_t, qtControlUnit*>	__allUnits;	//All units that have been created across all clients
	static uint16_t								__id;		//Unique unit ID used by the server to keep track of units

	//Properties
	params_t	m_params;
	bool		m_active;

	//Qt Members
	QLineEdit*	m_valueEdit;		//Display the unit's value
	QLabel*		m_label;			//Display the unit's name

	//Client connection
	std::shared_ptr<net::connection<MSG_TYPE>>	m_client;
};

#endif