/***************************************************************************
                          scribuswin.cpp  -  description
                             -------------------
    begin                : Mit Nov 6 2002
    copyright            : (C) 2002 by Franz Schmid
    email                : Franz.Schmid@altmuehlnet.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <qfileinfo.h>
#include <qdir.h>
#include "scribuswin.h"
#include "pageselector.h"
#include "scribuswin.moc"
#include "scribusXml.h"
#include "scribus.h"
#include "story.h"
#include "util.h"
#include "commonstrings.h"

extern ScribusApp* ScApp;

ScribusWin::ScribusWin(QWidget* parent, ScribusDoc* ddoc) : QMainWindow(parent, "", WDestructiveClose)
{
	setIcon(loadIcon("AppIcon2.png"));
	doc = ddoc;
	muster = NULL;
}

void ScribusWin::setView(ScribusView* dview)
{
	view = dview;
	doc->viewCount++;
	doc->viewID++;
	winIndex = doc->viewID;
	QPoint point = QPoint(0,0);
	statusFrame = new QFrame(this, "newDocFrame");
	statusFrameLayout = new QHBoxLayout( statusFrame, 0, 0, "statusFrame");
	view->unitSwitcher->reparent(statusFrame, point);
	view->LE->reparent(statusFrame, point);
	view->zoomOutToolbarButton->reparent(statusFrame, point);
	view->zoomInToolbarButton->reparent(statusFrame, point);
	view->PGS->reparent(statusFrame, point);
	view->LY->reparent(statusFrame, point);
	statusFrameLayout->addWidget(view->unitSwitcher);
	statusFrameLayout->addWidget(view->LE);
	statusFrameLayout->addWidget(view->zoomOutToolbarButton);
	statusFrameLayout->addWidget(view->zoomInToolbarButton);
	statusFrameLayout->addWidget(view->PGS);
	statusFrameLayout->addWidget(view->LY);
	QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	statusFrameLayout->addItem( spacer );
	statusBar()->addWidget(statusFrame, 4, true);
}

void ScribusWin::slotAutoSave()
{
	if ((doc->hasName) && (doc->isModified()))
	{
		moveFile(doc->DocName, doc->DocName+".bak");
		QString fn = doc->DocName;
		QFileInfo fi(fn);
		QDir::setCurrent(fi.dirPath(true));
		ScriXmlDoc *ss = new ScriXmlDoc();
		if (ss->WriteDoc(fn, doc, 0))
		{
			doc->setModified(false);
			setCaption(doc->DocName);
			qApp->processEvents();
			emit AutoSaved();
		}
		delete ss;
	}
}

void ScribusWin::closeEvent(QCloseEvent *ce)
{
	if (doc->isModified() && (doc->viewCount == 1))
	{
		QString CloseTxt;
		if (ScApp->singleClose)
			CloseTxt = tr("&Leave Anyway");
		else
			CloseTxt = tr("C&lose Anyway");
		int exit=QMessageBox::information(this,
		                                  tr("Warning"),
		                                  tr("Document:")+" "+doc->DocName+"\n"+ tr("has been changed since the last save."),
		                                  tr("&Save Now"),
		                                  CommonStrings::tr_Cancel,
		                                  CloseTxt,
		                                  0, 1);
		switch (exit)
		{
		case 0:
			if (ScApp->DoSaveClose())
			{
				if (doc==ScApp->storyEditor->currentDocument())
					ScApp->storyEditor->close();
				ce->accept();
			}
			else
				return;
			break;
		case 1:
			break;
		case 2:
			emit Schliessen();
			ce->accept();
			break;
		}
	}
	else
	{
		emit Schliessen();
		ce->accept();
	}
}
