#include "control/qtControlUnit.h"
#include "network/qtServer.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	qtServer* s = new qtServer();
	s->show();
	s->start();

	qtControlUnit::params_t p = {0,0,0,THERMISTOR,"TEST",0};
	qtControlUnit* u = new qtControlUnit(p, s);

	return app.exec();
}