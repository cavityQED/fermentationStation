#include "qtLogger.h"

qtLogger::qtLogger(const std::string& filename, QWidget* parent) : QWidget(parent)
{
	m_filename = filename;

}

void qtLogger::addUnit(qtControlUnit* u)
{
	m_monitoredUnits.push_back(u);
	m_file.open(m_filename);
	if(m_file.is_open()) {
		m_file.seekg(0, std::ios_base::end);
		m_file << "Time,";
		for(auto& unit : m_monitoredUnits) {
			m_file << unit->name().toStdString() << ',';
		}
		m_file << '\n';
		m_file.close();
	}	
}