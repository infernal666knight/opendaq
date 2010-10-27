#include <QApplication>
#include "mwindow.h"

int main (int argc, char *argv[]){
	QApplication app (argc, argv);
		MWindow *mainWin = new MWindow;
		mainWin -> show();
	return app.exec();
}
