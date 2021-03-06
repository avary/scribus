/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          cpalette.cpp  -  description
                             -------------------
    begin                : Wed Apr 25 2001
    copyright            : (C) 2001 by Franz Schmid
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

#include "cpalette.h"

#include <QAbstractItemView>
#include <QEvent>
#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QRect>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStandardItem>
#include <QToolButton>
#include <QToolTip>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>

#include "colorlistbox.h"
#include "sccombobox.h"
#include "scribusdoc.h"
#include "scrspinbox.h"
#include "gradienteditor.h"
#include "units.h"
#include "page.h"
#include "pageitem.h"
#include "util_icon.h"
#include "commonstrings.h"
#include "sccolorengine.h"
#include "scpainter.h"
#include "scpattern.h"
#include "util.h"
#include "util_math.h"

Cpalette::Cpalette(QWidget* parent) : QWidget(parent)
{
	currentItem = NULL;
	patternList = NULL;
	CGradDia = NULL;
	CGradDia = new GradientVectorDialog(this->parentWidget());
	CGradDia->hide();
	setupUi(this);
	gradientTypeStroke->setCurrentIndex(0);
	editLineColorSelector->setIcon(QIcon(loadIcon("16/color-stroke.png")));
	editFillColorSelector->setIcon(QIcon(loadIcon("16/color-fill.png")));
	connect(editLineColorSelector, SIGNAL(clicked()), this, SLOT(editLineColorSelectorButton()));
	connect(editFillColorSelector, SIGNAL(clicked()), this, SLOT(editFillColorSelectorButton()));
	connect(patternBox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPattern(QListWidgetItem*)));
	connect(fillShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewBrushShade(int)));
	connect(strokeShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewPenShade(int)));
	connect(colorListStroke, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorS(QListWidgetItem*)));
	connect(colorListFill, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorF(QListWidgetItem*)));
	connect(gradEditButton, SIGNAL(clicked()), this, SLOT(editGradientVector()));
	connect(displayAllColors, SIGNAL(clicked()), this, SLOT(ToggleColorDisplay()));
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotGrad(int)));
	connect(CGradDia, SIGNAL(NewSpecial(double, double, double, double, double, double, double, double)), this, SIGNAL(NewSpecial(double, double, double, double, double, double, double, double)));
	connect(CGradDia, SIGNAL(paletteShown(bool)), this, SLOT(setActiveGradDia(bool)));
	connect(gradientType, SIGNAL(activated(int)), this, SLOT(slotGradType(int)));
	connect(gradEdit, SIGNAL(gradientChanged()), this, SIGNAL(gradientChanged()));
	connect(editPatternProps, SIGNAL(clicked()), this, SLOT(changePatternProps()));
	connect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
	connect(overPrintCombo, SIGNAL(activated(int)), this, SIGNAL(NewOverprint(int)));
	connect(patternBoxStroke, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPatternS(QListWidgetItem*)));
	connect(tabWidgetStroke, SIGNAL(currentChanged(int)), this, SLOT(slotGradStroke(int)));
	connect(editPatternPropsStroke, SIGNAL(clicked()), this, SLOT(changePatternPropsStroke()));
	connect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
	connect(gradientTypeStroke, SIGNAL(activated(int)), this, SLOT(slotGradTypeStroke(int)));
	connect(gradEditStroke, SIGNAL(gradientChanged()), this, SIGNAL(strokeGradientChanged()));
	connect(gradEditButtonStroke, SIGNAL(clicked()), this, SLOT(editGradientVectorStroke()));
	connect(followsPath, SIGNAL(clicked()), this, SLOT(toggleStrokePattern()));
	editFillColorSelector->setChecked(true);
	editFillColorSelectorButton();
}

void Cpalette::setCurrentItem(PageItem* item)
{
	currentItem = item;
}

void Cpalette::setDocument(ScribusDoc* doc)
{
	currentDoc = doc;
	if (doc == NULL)
	{
		colorListStroke->cList = NULL;
		colorListFill->cList = NULL;
	}
	else
	{
		colorListStroke->cList = &doc->PageColors;
		colorListFill->cList = &doc->PageColors;
		gradEdit->setColors(doc->PageColors);
		currentUnit = doc->unitIndex();
	}
}

void Cpalette::updateFromItem()
{
	if (currentItem == NULL)
		return;
	if (!currentDoc)
		return;
	disconnect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
	disconnect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
	disconnect(tabWidgetStroke, SIGNAL(currentChanged(int)), this, SLOT(slotGradStroke(int)));
	disconnect(gradientTypeStroke, SIGNAL(activated(int)), this, SLOT(slotGradTypeStroke(int)));
	disconnect(gradEdit, SIGNAL(gradientChanged()), this, SIGNAL(gradientChanged()));
	disconnect(gradEditStroke, SIGNAL(gradientChanged()), this, SIGNAL(strokeGradientChanged()));
	disconnect(gradientType, SIGNAL(activated(int)), this, SLOT(slotGradType(int)));
	updateCList();
	if (currentItem->doOverprint)
		setActOverprint(1);
	else
		setActOverprint(0);
	setActFarben(currentItem->lineColor(), currentItem->fillColor(), currentItem->lineShade(), currentItem->fillShade());
	ChooseGrad(currentItem->GrType);
	gradEdit->setGradient(currentItem->fill_gradient);
	gradEditStroke->setGradient(currentItem->stroke_gradient);
	if (!currentItem->gradient().isEmpty())
	{
		setCurrentComboItem(namedGradient, currentItem->gradient());
		gradEdit->setGradientEditable(false);
	}
	else
	{
		namedGradient->setCurrentIndex(0);
		gradEdit->setGradientEditable(true);
	}
	if (!currentItem->strokeGradient().isEmpty())
	{
		setCurrentComboItem(namedGradientStroke, currentItem->strokeGradient());
		gradEditStroke->setGradientEditable(false);
	}
	else
	{
		namedGradientStroke->setCurrentIndex(0);
		gradEditStroke->setGradientEditable(true);
	}
	if (currentItem->GrTypeStroke > 0)
	{
		if (currentItem->GrTypeStroke == 6)
			gradientTypeStroke->setCurrentIndex(0);
		else
			gradientTypeStroke->setCurrentIndex(1);
	}
	if (patternList->count() == 0)
	{
		tabWidgetStroke->setTabEnabled(2, false);
		tabWidget->setTabEnabled(2, false);
	}
	else
	{
		tabWidgetStroke->setTabEnabled(2, true);
		tabWidget->setTabEnabled(2, true);
	}
	if (!currentItem->strokePattern().isEmpty())
		tabWidgetStroke->setCurrentIndex(2);
	else if (currentItem->GrTypeStroke > 0)
		tabWidgetStroke->setCurrentIndex(1);
	else
		tabWidgetStroke->setCurrentIndex(0);
	connect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
	connect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
	connect(tabWidgetStroke, SIGNAL(currentChanged(int)), this, SLOT(slotGradStroke(int)));
	connect(gradientTypeStroke, SIGNAL(activated(int)), this, SLOT(slotGradTypeStroke(int)));
	connect(gradEdit, SIGNAL(gradientChanged()), this, SIGNAL(gradientChanged()));
	connect(gradEditStroke, SIGNAL(gradientChanged()), this, SIGNAL(strokeGradientChanged()));
	connect(gradientType, SIGNAL(activated(int)), this, SLOT(slotGradType(int)));
}

void Cpalette::updateCList()
{
	disconnect(colorListStroke, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorS(QListWidgetItem*)));
	disconnect(colorListFill, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorF(QListWidgetItem*)));
	colorListStroke->clear();
	colorListStroke->addItem(CommonStrings::tr_NoneColor);
	colorListFill->clear();
	colorListFill->addItem(CommonStrings::tr_NoneColor);
	if (displayAllColors->isChecked())
	{
		if (currentDoc != NULL)
			currentDoc->getUsedColors(colorList);
	}
	gradEditStroke->setColors(colorList);
	gradEdit->setColors(colorList);
	colorListFill->insertItems(colorList, ColorListBox::fancyPixmap);
	colorListStroke->insertItems(colorList, ColorListBox::fancyPixmap);
	if (colorListFill->currentItem())
		colorListFill->currentItem()->setSelected(false);
	if (colorListStroke->currentItem())
		colorListStroke->currentItem()->setSelected(false);
	connect(colorListStroke, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorS(QListWidgetItem*)));
	connect(colorListFill, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorF(QListWidgetItem*)));
}

void Cpalette::ToggleColorDisplay()
{
	if (currentDoc != NULL)
	{
		colorListStroke->cList = &currentDoc->PageColors;
		colorListFill->cList = &currentDoc->PageColors;
		colorList = currentDoc->PageColors;
		updateFromItem();
	}
}

void Cpalette::setActOverprint(int val)
{
	disconnect(overPrintCombo, SIGNAL(activated(int)), this, SIGNAL(NewOverprint(int)));
	overPrintCombo->setCurrentIndex(val);
	connect(overPrintCombo, SIGNAL(activated(int)), this, SIGNAL(NewOverprint(int)));
}

void Cpalette::setActFarben(QString p, QString b, int shp, int shb)
{
	disconnect(fillShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewBrushShade(int)));
	disconnect(strokeShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewPenShade(int)));
	disconnect(colorListStroke, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorS(QListWidgetItem*)));
	disconnect(colorListFill, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorF(QListWidgetItem*)));
	strokeShade->setValue(shp);
	fillShade->setValue(shp);
	if ((p != CommonStrings::None) && (!p.isEmpty()))
	{
		QList<QListWidgetItem *> cCol = colorListStroke->findItems(p, Qt::MatchExactly);
		if (cCol.count() != 0)
			colorListStroke->setCurrentItem(cCol[0]);
	}
	else
		colorListStroke->setCurrentRow(0);
	if ((b != CommonStrings::None) && (!b.isEmpty()))
	{
		QList<QListWidgetItem *> cCol = colorListFill->findItems(b, Qt::MatchExactly);
		if (cCol.count() != 0)
			colorListFill->setCurrentItem(cCol[0]);
	}
	else
		colorListFill->setCurrentRow(0);
	connect(fillShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewBrushShade(int)));
	connect(strokeShade, SIGNAL(valueChanged(int)), this, SIGNAL(NewPenShade(int)));
	connect(colorListStroke, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorS(QListWidgetItem*)));
	connect(colorListFill, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectColorF(QListWidgetItem*)));
}

void Cpalette::selectColorS(QListWidgetItem *item)
{
	ColorPixmapItem* c = dynamic_cast<ColorPixmapItem*>(item);
	if (c != NULL)	
		sFarbe = c->colorName();
	else if (! item->data(Qt::DisplayRole).toString().isEmpty()) 
		sFarbe = item->data(Qt::DisplayRole).toString();
	else
		return;
	emit NewPen(sFarbe);
}

void Cpalette::selectColorF(QListWidgetItem *item)
{
	ColorPixmapItem* c = dynamic_cast<ColorPixmapItem*>(item);
	if (c != NULL)	
		sFarbe = c->colorName();
	else if (! item->data(Qt::DisplayRole).toString().isEmpty()) 
		sFarbe = item->data(Qt::DisplayRole).toString();
	else
		return;
	emit NewBrush(sFarbe);
}

void Cpalette::SetColors(ColorList newColorList)
{
	colorList.clear();
	colorList = newColorList;
	updateCList();
}

void Cpalette::editLineColorSelectorButton()
{
	if (editLineColorSelector->isChecked())
	{
		stackedWidget->setCurrentIndex(0);
		editFillColorSelector->setChecked(false);
	}
	updateFromItem();
}

void Cpalette::editFillColorSelectorButton()
{
	if (editFillColorSelector->isChecked())
	{
		stackedWidget->setCurrentIndex(1);
		editLineColorSelector->setChecked(false);
	}
	updateFromItem();
}

void Cpalette::updateGradientList()
{
	disconnect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
	disconnect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
	namedGradient->clear();
	namedGradient->setIconSize(QSize(48, 12));
	namedGradient->addItem( tr("Custom"));
	namedGradientStroke->clear();
	namedGradientStroke->setIconSize(QSize(48, 12));
	namedGradientStroke->addItem( tr("Custom"));
	for (QMap<QString, VGradient>::Iterator it = gradientList->begin(); it != gradientList->end(); ++it)
	{
		QImage pixm(48, 12, QImage::Format_ARGB32_Premultiplied);
		QPainter pb;
		QBrush b(QColor(205,205,205), loadIcon("testfill.png"));
		pb.begin(&pixm);
		pb.fillRect(0, 0, 48, 12, b);
		pb.end();
		ScPainter *p = new ScPainter(&pixm, 48, 12);
		p->setPen(Qt::black);
		p->setLineWidth(1);
		p->setFillMode(2);
		p->fill_gradient = it.value();
		p->setGradient(VGradient::linear, FPoint(0,6), FPoint(48, 6), FPoint(0,0), 1, 0);
		p->drawRect(0, 0, 48, 12);
		p->end();
		delete p;
		QPixmap pm;
		pm = QPixmap::fromImage(pixm);
		namedGradient->addItem(pm, it.key());
		namedGradientStroke->addItem(pm, it.key());
	}
	connect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
	connect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
}

void Cpalette::SetGradients(QMap<QString, VGradient> *docGradients)
{
	gradientList = docGradients;
	updateGradientList();
}

void Cpalette::setNamedGradient(const QString &name)
{
	if (namedGradient->currentIndex() == 0)
	{
		gradEdit->setGradient(currentItem->fill_gradient);
		currentItem->setGradient("");
		gradEdit->setGradientEditable(true);
	}
	else
	{
		gradEdit->setGradient(gradientList->value(name));
		gradEdit->setGradientEditable(false);
		currentItem->setGradient(name);
	}
	if (gradientType->currentIndex() == 0)
		emit NewGradient(6);
	else
		emit NewGradient(7);
}

void Cpalette::setNamedGradientStroke(const QString &name)
{
	if (namedGradientStroke->currentIndex() == 0)
	{
		gradEditStroke->setGradient(currentItem->stroke_gradient);
		currentItem->setStrokeGradient("");
		gradEditStroke->setGradientEditable(true);
	}
	else
	{
		gradEditStroke->setGradient(gradientList->value(name));
		gradEditStroke->setGradientEditable(false);
		currentItem->setStrokeGradient(name);
	}
	if (gradientTypeStroke->currentIndex() == 0)
		emit NewGradientS(6);
	else
		emit NewGradientS(7);
}

void Cpalette::updatePatternList()
{
	disconnect(patternBox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPattern(QListWidgetItem*)));
	patternBox->clear();
	patternBox->setIconSize(QSize(48, 48));
	patternBoxStroke->clear();
	patternBoxStroke->setIconSize(QSize(48, 48));
	for (QMap<QString, ScPattern>::Iterator it = patternList->begin(); it != patternList->end(); ++it)
	{
		QPixmap pm;
		if (it.value().getPattern()->width() >= it.value().getPattern()->height())
			pm=QPixmap::fromImage(it.value().getPattern()->scaledToWidth(48, Qt::SmoothTransformation));
		else
			pm=QPixmap::fromImage(it.value().getPattern()->scaledToHeight(48, Qt::SmoothTransformation));
		QPixmap pm2(48, 48);
		pm2.fill(palette().color(QPalette::Base));
		QPainter p;
		p.begin(&pm2);
		p.drawPixmap(24 - pm.width() / 2, 24 - pm.height() / 2, pm);
		p.end();
		QListWidgetItem *item = new QListWidgetItem(pm2, it.key(), patternBox);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QListWidgetItem *itemS = new QListWidgetItem(pm2, it.key(), patternBoxStroke);
		itemS->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	patternBox->clearSelection();
	patternBoxStroke->clearSelection();
	connect(patternBox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPattern(QListWidgetItem*)));
}

void Cpalette::SetPatterns(QMap<QString, ScPattern> *docPatterns)
{
	patternList = docPatterns;
	updatePatternList();
}

void Cpalette::selectPattern(QListWidgetItem *c)
{
	if (c == NULL)
		return;
	emit NewPattern(c->text());
}

void Cpalette::selectPatternS(QListWidgetItem *c)
{
	if (c == NULL)
		return;
	emit NewPatternS(c->text());
}

void Cpalette::setActPatternStroke(QString pattern, double scaleX, double scaleY, double offsetX, double offsetY, double rotation, double skewX, double skewY, bool mirrorX, bool mirrorY, double space, bool pathF)
{
	disconnect(patternBoxStroke, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPatternS(QListWidgetItem*)));
	QList<QListWidgetItem*> itl = patternBoxStroke->findItems(pattern, Qt::MatchExactly);
	if (itl.count() != 0)
	{
		QListWidgetItem *it = itl[0];
		patternBoxStroke->setCurrentItem(it);
	}
	else
		patternBoxStroke->clearSelection();
	m_Pattern_scaleXS = scaleX;
	m_Pattern_scaleYS = scaleX;
	m_Pattern_offsetXS = offsetX;
	m_Pattern_offsetYS = offsetY;
	m_Pattern_rotationS = rotation;
	m_Pattern_skewXS = skewX;
	m_Pattern_skewYS = skewY;
	m_Pattern_mirrorXS = mirrorX;
	m_Pattern_mirrorYS = mirrorY;
	m_Pattern_spaceS = space;
	followsPath->setChecked(pathF);
	connect(patternBoxStroke, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPatternS(QListWidgetItem*)));
}

void Cpalette::setActPattern(QString pattern, double scaleX, double scaleY, double offsetX, double offsetY, double rotation, double skewX, double skewY, bool mirrorX, bool mirrorY)
{
	disconnect(patternBox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPattern(QListWidgetItem*)));
	QList<QListWidgetItem*> itl = patternBox->findItems(pattern, Qt::MatchExactly);
	if (itl.count() != 0)
	{
		QListWidgetItem *it = itl[0];
		patternBox->setCurrentItem(it);
	}
	else
		patternBox->clearSelection();
	m_Pattern_scaleX = scaleX;
	m_Pattern_scaleY = scaleX;
	m_Pattern_offsetX = offsetX;
	m_Pattern_offsetY = offsetY;
	m_Pattern_rotation = rotation;
	m_Pattern_skewX = skewX;
	m_Pattern_skewY = skewY;
	m_Pattern_mirrorX = mirrorX;
	m_Pattern_mirrorY = mirrorY;
	connect(patternBox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectPattern(QListWidgetItem*)));
}

void Cpalette::slotGradStroke(int number)
{
	if (number == 1)
	{
		disconnect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
		if (!currentItem->strokeGradient().isEmpty())
		{
			setCurrentComboItem(namedGradientStroke, currentItem->strokeGradient());
			gradEditStroke->setGradient(gradientList->value(currentItem->strokeGradient()));
			gradEditStroke->setGradientEditable(false);
		}
		else
		{
			namedGradientStroke->setCurrentIndex(0);
			gradEditStroke->setGradient(currentItem->stroke_gradient);
			gradEditStroke->setGradientEditable(true);
		}
		emit NewPatternS("");
		if (gradientTypeStroke->currentIndex() == 0)
			emit NewGradientS(6);
		else
			emit NewGradientS(7);
		connect(namedGradientStroke, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradientStroke(const QString &)));
	}
	else if (number == 2)
	{
		emit NewGradientS(8);
		if (patternBoxStroke->currentItem())
			emit NewPatternS(patternBoxStroke->currentItem()->text());
	}
	else
	{
		emit NewGradientS(0);
		emit NewPatternS("");
	}
}

void Cpalette::ChooseGrad(int number)
{
	disconnect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotGrad(int)));
	if (number==-1)
	{
		tabWidget->setCurrentIndex(0);
	}
	if (number == 0)
		tabWidget->setCurrentIndex(0);
	else if ((number > 0) && (number < 8))
	{
		if ((number == 5) || (number == 7))
			gradientType->setCurrentIndex(1);
		else
			gradientType->setCurrentIndex(0);
		tabWidget->setCurrentIndex(1);
	}
	else
	{
		if (patternList->count() == 0)
		{
			tabWidget->setCurrentIndex(0);
			emit NewGradient(0);
		}
		else
			tabWidget->setCurrentIndex(2);
	}
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotGrad(int)));
}

void Cpalette::slotGrad(int number)
{
	if (number == 1)
	{
		disconnect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
		disconnect(gradientType, SIGNAL(activated(int)), this, SLOT(slotGradType(int)));
		disconnect(gradEdit, SIGNAL(gradientChanged()), this, SIGNAL(gradientChanged()));
		if (!currentItem->gradient().isEmpty())
		{
			setCurrentComboItem(namedGradient, currentItem->gradient());
			gradEdit->setGradient(gradientList->value(currentItem->gradient()));
			gradEdit->setGradientEditable(false);
		}
		else
		{
			namedGradient->setCurrentIndex(0);
			gradEdit->setGradient(currentItem->fill_gradient);
			gradEdit->setGradientEditable(true);
		}
		if (gradientType->currentIndex() == 0)
			emit NewGradient(6);
		else
			emit NewGradient(7);
		connect(namedGradient, SIGNAL(activated(const QString &)), this, SLOT(setNamedGradient(const QString &)));
		connect(gradientType, SIGNAL(activated(int)), this, SLOT(slotGradType(int)));
		connect(gradEdit, SIGNAL(gradientChanged()), this, SIGNAL(gradientChanged()));
	}
	else if (number == 2)
		emit NewGradient(8);
	else
		emit NewGradient(0);
}

void Cpalette::slotGradType(int type)
{
	if (type == 0)
		emit NewGradient(6);
	else
		emit NewGradient(7);
}

void Cpalette::slotGradTypeStroke(int type)
{
	if (type == 0)
		emit NewGradientS(6);
	else
		emit NewGradientS(7);
}

void Cpalette::setActGradient(int typ)
{
	ChooseGrad(typ);
}

void Cpalette::editGradientVector()
{
	if (gradEditButton->isChecked())
	{
		CGradDia->unitChange(currentDoc->unitIndex());
		CGradDia->setValues(currentItem->GrStartX, currentItem->GrStartY, currentItem->GrEndX, currentItem->GrEndY, currentItem->GrFocalX, currentItem->GrFocalY, currentItem->GrScale, currentItem->GrSkew);
		if (currentItem->GrType == 6)
			CGradDia->hideExtraWidgets();
		else
			CGradDia->showExtraWidgets();
		CGradDia->show();
	}
	else
	{
		CGradDia->hide();
	}
	editStrokeGradient = 0;
	emit editGradient(editStrokeGradient);
}

void Cpalette::editGradientVectorStroke()
{
	if (gradEditButtonStroke->isChecked())
	{
		CGradDia->unitChange(currentDoc->unitIndex());
		CGradDia->setValues(currentItem->GrStrokeStartX, currentItem->GrStrokeStartY, currentItem->GrStrokeEndX, currentItem->GrStrokeEndY, currentItem->GrStrokeFocalX, currentItem->GrStrokeFocalY, currentItem->GrStrokeScale, currentItem->GrStrokeSkew);
		if (currentItem->GrTypeStroke == 6)
			CGradDia->hideExtraWidgets();
		else
			CGradDia->showExtraWidgets();
		CGradDia->show();
	}
	else
	{
		CGradDia->hide();
	}
	editStrokeGradient = 1;
	emit editGradient(editStrokeGradient);
}

void Cpalette::setActiveGradDia(bool active)
{
	if (!active)
	{
		if (editStrokeGradient == 1)
			gradEditButtonStroke->setChecked(false);
		else
			gradEditButton->setChecked(false);
		emit editGradient(editStrokeGradient);
	}
}

void Cpalette::setSpecialGradient(double x1, double y1, double x2, double y2, double fx, double fy, double sg, double sk)
{
	if (CGradDia)
		CGradDia->setValues(x1, y1, x2, y2, fx, fy, sg, sk);
}

void Cpalette::changePatternProps()
{
	PatternPropsDialog *dia = new PatternPropsDialog(this, currentUnit, false);
	dia->spinXscaling->setValue(m_Pattern_scaleX);
	dia->spinYscaling->setValue(m_Pattern_scaleY);
	dia->spinXoffset->setValue(m_Pattern_offsetX);
	dia->spinYoffset->setValue(m_Pattern_offsetY);
	dia->spinAngle->setValue(m_Pattern_rotation);
	double asina = atan(m_Pattern_skewX);
	dia->spinXSkew->setValue(asina / (M_PI / 180.0));
	double asinb = atan(m_Pattern_skewY);
	dia->spinYSkew->setValue(asinb / (M_PI / 180.0));
	dia->FlipH->setChecked(m_Pattern_mirrorX);
	dia->FlipV->setChecked(m_Pattern_mirrorY);
	connect(dia, SIGNAL(NewPatternProps(double, double, double, double, double, double, double, bool, bool)), this, SIGNAL(NewPatternProps(double, double, double, double, double, double, double, bool, bool)));
	dia->exec();
	m_Pattern_scaleX = dia->spinXscaling->value();
	m_Pattern_scaleY = dia->spinYscaling->value();
	m_Pattern_offsetX = dia->spinXoffset->value();
	m_Pattern_offsetY = dia->spinYoffset->value();
	m_Pattern_rotation = dia->spinAngle->value();
	double skewX = dia->spinXSkew->value();
	double a;
	if (skewX == 90)
		a = 1;
	else if (skewX == 180)
		a = 0;
	else if (skewX == 270)
		a = -1;
	else if (skewX == 360)
		a = 0;
	else
		a = tan(M_PI / 180.0 * skewX);
	m_Pattern_skewX = tan(a);
	skewX = dia->spinYSkew->value();
	if (skewX == 90)
		a = 1;
	else if (skewX == 180)
		a = 0;
	else if (skewX == 270)
		a = -1;
	else if (skewX == 360)
		a = 0;
	else
		a = tan(M_PI / 180.0 * skewX);
	m_Pattern_skewY = tan(a);
	m_Pattern_mirrorX = dia->FlipH->isChecked();
	m_Pattern_mirrorY = dia->FlipV->isChecked();
	delete dia;
	tabWidget->setCurrentIndex(2);
	emit NewGradient(8);
}

void Cpalette::changePatternPropsStroke()
{
	PatternPropsDialog *dia = new PatternPropsDialog(this, currentUnit, true);
	dia->spinXscaling->setValue(m_Pattern_scaleXS);
	dia->spinYscaling->setValue(m_Pattern_scaleYS);
	dia->spinXoffset->setValue(m_Pattern_offsetXS);
	dia->spinYoffset->setValue(m_Pattern_offsetYS);
	dia->spinAngle->setValue(m_Pattern_rotationS);
	dia->spinSpacing->setValue(m_Pattern_spaceS * 100.0);
	double asina = atan(m_Pattern_skewXS);
	dia->spinXSkew->setValue(asina / (M_PI / 180.0));
	double asinb = atan(m_Pattern_skewYS);
	dia->spinYSkew->setValue(asinb / (M_PI / 180.0));
	dia->FlipH->setChecked(m_Pattern_mirrorXS);
	dia->FlipV->setChecked(m_Pattern_mirrorYS);
	connect(dia, SIGNAL(NewPatternPropsS(double, double, double, double, double, double, double, double, bool, bool)), this, SIGNAL(NewPatternPropsS(double, double, double, double, double, double, double, double, bool, bool)));
	dia->exec();
	m_Pattern_scaleXS = dia->spinXscaling->value();
	m_Pattern_scaleYS = dia->spinYscaling->value();
	m_Pattern_offsetXS = dia->spinXoffset->value();
	m_Pattern_offsetYS = dia->spinYoffset->value();
	m_Pattern_rotationS = dia->spinAngle->value();
	double skewX = dia->spinXSkew->value();
	double a;
	if (skewX == 90)
		a = 1;
	else if (skewX == 180)
		a = 0;
	else if (skewX == 270)
		a = -1;
	else if (skewX == 360)
		a = 0;
	else
		a = tan(M_PI / 180.0 * skewX);
	m_Pattern_skewXS = tan(a);
	skewX = dia->spinYSkew->value();
	if (skewX == 90)
		a = 1;
	else if (skewX == 180)
		a = 0;
	else if (skewX == 270)
		a = -1;
	else if (skewX == 360)
		a = 0;
	else
		a = tan(M_PI / 180.0 * skewX);
	m_Pattern_skewYS = tan(a);
	m_Pattern_spaceS = dia->spinSpacing->value() / 100.0;
	m_Pattern_mirrorXS = dia->FlipH->isChecked();
	m_Pattern_mirrorYS = dia->FlipV->isChecked();
	delete dia;
}

void Cpalette::toggleStrokePattern()
{
	emit NewPatternTypeS(followsPath->isChecked());
}

void Cpalette::unitChange(double, double, int unitIndex)
{
	if (CGradDia)
		CGradDia->unitChange(unitIndex);
	currentUnit = unitIndex;
}

void Cpalette::changeEvent(QEvent *e)
{
	if (e->type() == QEvent::LanguageChange)
	{
		languageChange();
	}
	else
		QWidget::changeEvent(e);
}
