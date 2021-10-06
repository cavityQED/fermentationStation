#include "qtServerWindow.h"

qtServerWindow::qtServerWindow(QWidget* parent) : QMainWindow(parent)
{
	m_server = new qtServer(this);
	m_server->start();
	m_server->update();

	setCentralWidget(m_server);
}