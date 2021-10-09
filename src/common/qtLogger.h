#ifndef QTLOGGER_H
#define QTLOGGER_H

#include "qtCommon.h"

#include "control/qtControlUnit.h"

class qtLogger : public QWidget
{
	Q_OBJECT
public:
	qtLogger(const std::string& filename, QWidget* parent = nullptr);
	virtual ~qtLogger() {}

	void addUnit(qtControlUnit* u);

public slots:
	void start(int s) {
		m_timerID = startTimer(std::chrono::seconds(s));
	}

	void stop() {
		killTimer(m_timerID);
	}

protected:
	virtual void timerEvent(QTimerEvent* e) override {
		m_file.open(m_filename);
		m_file.seekg(0, std::ios_base::end);
		if(!m_file.is_open())
			return;

		std::cout << "Writing to file...\n";

		m_file << "time,";
		for(auto& u : m_monitoredUnits) {
			if(u->isActive())
				m_file << std::to_string(u->value()) << ',';
			else
				m_file << ",";
		}
		m_file << '\n';
		m_file.close();
	}

protected:
	std::string		m_filename;
	std::fstream	m_file;

	std::vector<qtControlUnit*>		m_monitoredUnits;

	int 			m_timerID;
};

#endif