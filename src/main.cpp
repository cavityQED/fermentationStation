#include "control/qtControlUnit.h"
#include "network/qtServerWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);


	qtServerWindow* s = new qtServerWindow();
	s->show();

	return app.exec();
}