/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#ifndef PREFS_USERINTERFACE_H
#define PREFS_USERINTERFACE_H

#include "ui_prefs_userinterfacebase.h"
#include "scribusapi.h"

class SCRIBUS_API Prefs_UserInterface : public QWidget, Ui::Prefs_UserInterface
{
	Q_OBJECT

	public:
		Prefs_UserInterface(QWidget* parent=0);
		~Prefs_UserInterface();

//		setValues();

};

#endif // PREFS_USERINTERFACE_H
