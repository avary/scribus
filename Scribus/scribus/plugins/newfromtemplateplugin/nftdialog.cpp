/***************************************************************************
 *   Riku Leino, tsoots@welho.com                                          *
 ***************************************************************************/
#include "nftdialog.h"
#include "nftdialog.moc"
#include "config.h"

extern QPixmap loadIcon(QString nam);

nftdialog::nftdialog(QWidget* parent) : QDialog(parent, "nftdialog", TRUE)
{
	settings = new nftsettings();
	
	setCaption( tr("New From Template"));
	setIcon(loadIcon("AppIcon.png"));
	
	QBoxLayout* blo = new QVBoxLayout(this,0,5,"blo");
	QWidget* top = new QWidget(this);
	top->setMaximumHeight(5);
	QWidget* middle = new QWidget(this);
	middle->setMinimumHeight(370);
	QWidget* bottom = new QWidget(this);
	bottom->setMinimumHeight(40);
	bottom->setMaximumHeight(40);
	blo->addWidget(top);
	blo->addWidget(middle);
	blo->addWidget(bottom);
	QBoxLayout* bottomlo = new QHBoxLayout(bottom,0,5,"bottomlo");
// 	settingsButton = new QPushButton(tr("Settings"),bottom,"settingsButton");
// 	bottomlo->insertSpacing(0,5);
// 	bottomlo->addWidget(settingsButton);
	bottomlo->addStretch(10);
	okButton = new QPushButton( tr("OK"),bottom,"okButton");
	okButton->setEnabled(false);
	bottomlo->addWidget(okButton);
	cancelButton = new QPushButton( tr("Cancel"),bottom,"cancelButton");
	bottomlo->addWidget(cancelButton);
	bottomlo->insertSpacing(-1,5);
	cancelButton->setDefault(true);
	
	mainlo = new QHBoxLayout(middle,0,5,"mainlo");
	QSplitter* splitter = new QSplitter(middle);
	mainlo->addWidget(splitter);
	
	categoryList = new QListBox(splitter,"categoryList",0);
	categoryList->setMinimumWidth(130);
	categoryList->setMaximumWidth(200);
	
	tnailGrid = new QIconView(splitter,"tnailGrid",0);
	tnailGrid->setMinimumWidth(300);
	tnailGrid->setSpacing(5);
	tnailGrid->setItemsMovable(false);
	
	QWidget* dtTmp = new QWidget(splitter, "dtTmp", 0);
	dtTmp->setMinimumWidth(235);
	mainlo->insertSpacing(0,5);
	mainlo->insertSpacing(-1,5);
	
	detaillo = new QVBoxLayout(dtTmp,0,5);
	detailBar = new QFrame(dtTmp,"detailBar",0);
	detailBar->setMaximumHeight(32);
	detailBar->setMinimumHeight(32);
	detailBar->setMargin(5);
	detaillo->addWidget(detailBar);
	
	infoLabel = new QTextBrowser(dtTmp,"infoLabel");
	infoLabel->setFrameShape(QFrame::Panel);
	infoLabel->setFrameShadow(QFrame::Sunken);
	detaillo->addWidget(infoLabel);

	tmpSpacer = new QWidget(dtTmp,"tmpSpacer",0);
	detaillo->addWidget(tmpSpacer);
	tmpSpacer->setHidden(true);
	
	imgLabel = new QIconView(dtTmp,"imgLabel",0);
	imgLabel->setFrameShape(QFrame::Panel);
	imgLabel->setFrameShadow(QFrame::Sunken);
	imgLabel->setSelectionMode(QIconView::NoSelection);
	detaillo->addWidget(imgLabel);
	imgLabel->setHidden(true);
	
	aboutLabel = new QTextBrowser(dtTmp,"aboutLabel");
	aboutLabel->setFrameShape(QFrame::Panel);
	aboutLabel->setFrameShadow(QFrame::Sunken);
	detaillo->addWidget(aboutLabel);
	aboutLabel->setHidden(true);
	setupAbout();
	
	dtbarlo = new QHBoxLayout(detailBar,0,5);
	imgButton = new QToolButton(detailBar,"imgButton");
	QIconSet imgSet(loadIcon("Bild.xpm"));
	imgButton->setIconSet(imgSet);
	imgButton->setToggleButton(true);
	imgButton->setMinimumWidth(30);
	imgButton->setMinimumHeight(30);
	imgButton->setMaximumWidth(30);
	imgButton->setMaximumHeight(30);
	dtbarlo->addWidget(imgButton);
	infoButton = new QToolButton(detailBar,"infoButton");
	QIconSet imgSet2(loadIcon("nftinfo.xpm"));
	infoButton->setIconSet(imgSet2);
	infoButton->setToggleButton(true);
	infoButton->setMinimumWidth(30);
	infoButton->setMinimumHeight(30);
	infoButton->setMaximumWidth(30);
	infoButton->setMaximumHeight(30);
	infoButton->toggle();
	dtbarlo->addWidget(infoButton);
	dtbarlo->addStretch(10);
	dtbarlo->insertSpacing(0,5);
	aboutButton = new QToolButton(detailBar,"aboutButton");
	QIconSet imgSet3(loadIcon("nftabout.xpm"));
	aboutButton->setIconSet(imgSet3);
	aboutButton->setToggleButton(true);
	aboutButton->setMinimumWidth(30);
	aboutButton->setMinimumHeight(30);
	aboutButton->setMaximumWidth(30);
	aboutButton->setMaximumHeight(30);
	dtbarlo->addWidget(aboutButton);
	
	// Signals and Slots Connections
	connect(categoryList, SIGNAL(selectionChanged()), this, SLOT(setTNails()));
	connect(infoButton, SIGNAL(toggled(bool)), this, SLOT(infoToggle()));
	connect(imgButton, SIGNAL(toggled(bool)), this, SLOT(imgToggle()));
	connect(aboutButton, SIGNAL(toggled(bool)), this, SLOT(aboutToggle()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(exitOK()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(exitCancel()));
	connect(tnailGrid, SIGNAL(selectionChanged(QIconViewItem*)),this,SLOT(setInfo(QIconViewItem*)));
	
	setupListItems();
	setupCategories();
}

void nftdialog::setupCategories() 
{
	QString categories("");
	for (uint i = 0; i < settings->templates.size(); i++)
	{
		if (categories.find(settings->templates[i]->templateCategory) == -1)
		{
			categoryList->insertItem(settings->templates[i]->templateCategory);
			categories += settings->templates[i]->templateCategory;
		}
	}
	categoryList->sort();
	categoryList->insertItem(QString( tr("All")), 0 );
	categoryList->setCurrentItem(0);
}

void nftdialog::setupListItems()
{
	for (uint i = 0; i < settings->templates.size(); ++i)
	{
		ListItem* tmp = new ListItem(settings->templates[i], NULL);
		iconItems.push_back(tmp);
	}
}

void nftdialog::setTNails()
{
	if (categoryList->currentItem() == 0)
	{
		tnailGrid->clear();
		for (uint i = 0; i < iconItems.size(); ++i) 
		{
			QIconViewItem* tmpQIVI = new QIconViewItem(tnailGrid,
			                                           iconItems[i]->first->name, 
			                                           QPixmap(iconItems[i]->first->tnail));
			iconItems[i]->second = tmpQIVI;
		}
		tnailGrid->sort();
		return;
	}
	QString curtype = categoryList->text(categoryList->currentItem());
	if (curtype != NULL)
	{
		tnailGrid->clear();
		for (uint i = 0; i < iconItems.size(); ++i)
		{
			if (curtype.find(iconItems[i]->first->templateCategory) != -1)
			{
				QIconViewItem* tmpQIVI = new QIconViewItem(tnailGrid,
			                                              iconItems[i]->first->name, 
			                                              QPixmap(iconItems[i]->first->tnail));
				iconItems[i]->second = tmpQIVI;
			} 
			else
				iconItems[i]->second = NULL;
		}
		tnailGrid->sort();
	}
}

void nftdialog::setInfo(QIconViewItem* item) 
{
	for (uint i = 0; i < iconItems.size(); ++i)
	{
		if (iconItems[i]->second == item)
		{
			currentTemplate = iconItems[i]->first;
			break;
		}
	}
	QString infoText = "<b>"+tr("Name")+"</b><br>";
	infoText += currentTemplate->name + "<br>";
	infoText += "<b>"+tr("Page Size")+"</b><br>";
	infoText += currentTemplate->psize + "<br>";
	infoText += "<b>"+tr("Colors")+"</b><br>";
	infoText += currentTemplate->color + "<br>";
	infoText += "<b>"+tr("Description")+"</b><br>";
	infoText += currentTemplate->descr + "<br>";
	infoText += "<b>"+tr("Usage")+"</b><br>";
	infoText += currentTemplate->usage + "<br>";
	infoText += "<b>"+tr("Created with")+"</b><br>";
	infoText += "Scribus " + currentTemplate->scribusVersion + "<br>";
	infoText += currentTemplate->date + "<br>";
	infoText += "<b>"+tr("Author")+"</b><br>";
	infoText += currentTemplate->author + "<br>";
	infoText += currentTemplate->email + "<br>";
	infoLabel->setText(infoText);
	imgLabel->clear();
	QPixmap tmplImg(currentTemplate->img);
	QIconViewItem* qvi = new QIconViewItem(imgLabel,currentTemplate->name,tmplImg);
	qvi->setRenameEnabled(false);
	qvi->setDragEnabled(false);
	qvi->setDropEnabled(false);
	
	if (!okButton->isEnabled())
	{
		okButton->setEnabled(true);
		okButton->setDefault(true);
	}
}

void nftdialog::infoToggle()
{
	if (infoButton->state() == QButton::On)
	{
		tmpSpacer->setHidden(true);
		infoLabel->setHidden(false);
		if (imgButton->state() == QButton::On)
			imgButton->toggle();
		if (aboutButton->state() == QButton::On)
			aboutButton->toggle();
	} 
	else
	{
		if (imgButton->state() == QButton::Off)
			tmpSpacer->setHidden(false);
		infoLabel->setHidden(true);
	}
	
}

void nftdialog::imgToggle() 
{	
	if (imgButton->state() == QButton::On)
	{
		tmpSpacer->setHidden(true);
		imgLabel->setHidden(false);
		if (infoButton->state() == QButton::On) 
			infoButton->toggle();
		if (aboutButton->state() == QButton::On) 
			aboutButton->toggle();
	}
	else
	{
		if (infoButton->state() == QButton::Off)
			tmpSpacer->setHidden(false);
		imgLabel->setHidden(true);
	}
}

void nftdialog::aboutToggle()
{
	if (aboutButton->state() == QButton::On)
	{
		tmpSpacer->setHidden(true);
		aboutLabel->setHidden(false);
		if (imgButton->state() == QButton::On) 
			imgButton->toggle();
		if (infoButton->state() == QButton::On)
			infoButton->toggle();
	}
	else
	{
		if (aboutButton->state() == QButton::Off)
			tmpSpacer->setHidden(false);
		aboutLabel->setHidden(true);
	}
}

void nftdialog::exitCancel() 
{
	reject();
}

void nftdialog::exitOK() 
{
	if (currentTemplate == NULL)
		reject();
	else
		accept();
}

void nftdialog::setupAbout() 
{
	QString text = "New From Template - 0.0.6<br><br>";
	text += "<b>Downloading Templates</b><br>";
	text += "Document templates can be found at<br>";
	text += "<i>http://insert/url/here</i><br><br>";
	text += "<b>Installing Templates</b><br>";
	text += "Extract the package to the template directory<br>";
	text += "<i>~/.scribus/templates</i><br>for the current user or<br>";
	text += "<i>PREFIX/share/scribus/templates</i><br>for all users ";
	text += "in the system.<br><br>";
	text += "<b>Preparing a template</b><br>";
	text += "Make sure images you use can be used anywhere. ";
	text += "Fonts must be checked for this as well. ";
	text += "If fonts cannot be shared remove them from the template directory ";
	text += "before packaging and distributing the template.<br><br>";
	aboutLabel->setText(text);
}

nftdialog::~nftdialog()
{
	// TODO Get the window size and position information and save with settings
	delete settings;
	for (uint i = 0; i < iconItems.size(); i++)
		delete iconItems[i];
}
