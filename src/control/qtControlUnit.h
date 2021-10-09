#ifndef QTCONTROLUNIT_H
#define QTCONTROLUNIT_H

#include "common/qtCommon.h"

#include <QContextMenuEvent>
#include <QLCDNumber>

class qtControlUnit : public QGroupBox
{
private:
	Q_OBJECT

public:
	//Struct to pass info 
	struct params_t {
		uint16_t		id			= 0;
		uint16_t		client_id	= 0;
		uint8_t			channel		= 0;
		double			value		= 0;
		UNIT_TYPE		type		= THERMISTOR;
		char			name[32];

		friend std::ostream& operator<<(std::ostream& out, const params_t& p) {
			out << "\n\tName:\t"		<< p.name; 
			out << "\n\tID:\t"		 	<< (int)p.id;
			out << "\n\tClient ID:\t"	<< (int)p.client_id;
			out << "\n\tChannel:\t"		<< (int)p.channel;
			out << "\n\ttype:\t"		<< p.type;
			out << '\n';
			return out;
		}
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
	*	Add Unit
	*		Add a unit and return the id
	*
	**/
	static uint16_t addUnit(const params_t& p, QWidget* parent = nullptr);

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
	static bool connect(const params_t& p, net_connection_ptr client);

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
	void setLabel(const QString name)			{m_labelName->setText(name);}
	void setName(const QString name)			{m_name = name; std::strcpy(m_params.name, name.toStdString().c_str()), setLabel(name);}
	void setEdit(double v)						{m_labelValue->display(std::round(v*100)/100);}
	void setValue(double v)						{m_params.value = v; setEdit(v);}
	void setClient(net_connection_ptr client)	{m_client = client;}
	void setActive(bool a)						{m_active = a;}
	void setConnected(bool c)					{m_connected = c;}

	//Getters
	uint16_t	id()			const	{return m_params.id;}
	uint16_t	clientID()		const	{return m_params.client_id;}
	uint8_t		channel()		const	{return m_params.channel;}
	double		value()			const	{return m_params.value;}
	UNIT_TYPE	type()			const	{return m_params.type;}
	QString		name()			const	{return m_name;}
	params_t	params()		const	{return m_params;}
	bool		isActive()		const	{return m_active;}
	bool		isConnected()	const	{return (m_client == nullptr)? false : m_connected && m_client->isConnected();}

protected:
	virtual bool event(QEvent* e) override;

	virtual void contextMenuEvent(QContextMenuEvent* e) override;

public slots:
	/**
	*	Read
	*		Sends a READ message to the client
	*
	**/
	void read() {
		if(!m_active)
			return;

		if(m_client && m_client->isConnected()) {
			net::message<MSG_TYPE> msg;
			msg.header.id = READ;
			msg << m_params;
			//get server pointer
			//send message through pointer
			//but for now just send through client
			m_client->send(msg);
		}
	}

	void set(double v) {
		if(!m_active)
			return;

		if(m_client && m_client->isConnected()) {
			net::message<MSG_TYPE> msg;
			msg.header.id = SET;
			m_params.value = v;
			msg << m_params;
			m_client->send(msg);
		}
	}

	void increase() {
		set(std::min((m_params.value + 5), 100.0));
	}

	void decrease() {
		set(std::max((m_params.value - 5), 0.0));
	}

	/**
	*	Connect to Client
	*		Send an activate message to the client to connect the unit with the associated client object
	*
	*/
	void connectToClient() {
		std::cout << "Attempting connection\n";
		if(m_client) {
			net::message<MSG_TYPE> msg;
			msg.header.id = CONNECT;
			msg << m_params;
			//get server pointer
			//send message through pointer
			//but for now just send through client
			m_client->send(msg);
		}
	}

	void editName() {
		std::string name;
		std::getline(std::cin, name);
		QString qName(name.c_str());
		setName(qName);
	}

signals:
	void valueChange(double v);

protected:
	//Static members
	static std::map<uint16_t, qtControlUnit*>	__allUnits;	//All units that have been created across all clients
	static uint16_t								__id;		//Unique unit ID used by the server to keep track of units

	//Properties
	QString		m_name 		= "";
	params_t	m_params	= {};
	bool		m_active	= false;
	bool		m_connected = false;

	//Qt Members
	QLCDNumber*	m_labelValue;		//Display the unit's value
	QLabel*		m_labelName;		//Display the unit's name
	QLabel*		m_labelChannel;		//Display the unit's channel
	QLabel*		m_labelType;		//Display the unit's type

	QPushButton* m_incButton;
	QPushButton* m_decButton;

	//Client connection
	std::shared_ptr<net::connection<MSG_TYPE>>	m_client;

	//Actions
	QAction*	editNameAct;
};

#endif