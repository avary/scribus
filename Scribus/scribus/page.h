/***************************************************************************
                          page.h  -  description
                             -------------------
    begin                : Sat Apr 7 2001
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

#ifndef PAGE_H
#define PAGE_H
#include <qobject.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qptrlist.h>
#include <qevent.h>
#include <qscrollview.h>
#include <qpopupmenu.h>
#include "fpoint.h"
#include "scribusdoc.h"
#include "pageitem.h"
/**
  *@author Franz Schmid
  */

class Page : public QWidget  {

Q_OBJECT

public:
	Page(QWidget *pa, int x, int y, int b, int h, ScribusDoc *doc, QScrollView *view);
	~Page() {};
  /** Zeichnet eine Ellipse */
  int PaintEllipse(float x, float y, float b, float h, float w, QString fill, QString outline);
  /** Zeichnet eine Bildbox */
  int PaintPict(float x, float y, float b, float h);
  /** Zeichnet ein Rechteck */
  int PaintRect(float x, float y, float b, float h, float w, QString fill, QString outline);
  /** Zeichnet eine Linie */
  int PaintLine(float x, float y, float b, float h, float w, QString outline);
  /** Zeichnet eine Textbox */
  int PaintText(float x, float y, float b, float h, float w, QString outline);
	/** Zeichnet ein Polygon */
	int PaintPoly(float x, float y, float b, float h, float w, QString fill, QString outline);
	int PaintPolyLine(float x, float y, float b, float h, float w, QString fill, QString outline);
  /** Laedt ein Bild */
  void LoadPict(QString fn, int ItNr);
  void insertColor(QString nam, float c, float m, float y, float k);
  void DrawPageMarks(QPaintEvent *e, ScPainter *p, QRect rd);
  void DrawPageItems(QPaintEvent *e, ScPainter *painter, QRect rd);
	void paintEvent(QPaintEvent *e);
	void setGroupRect();
	void getGroupRect(float *x, float *y, float *w, float *h);
	void getGroupRectScreen(float *x, float *y, float *w, float *h);
	void paintGroupRect(bool norm = true);
	void moveGroup(float x, float y, bool fromMP = false);
	FPoint transformPointI(FPoint in, float dx, float dy, float rot, float sx, float sy);
	FPoint transformPoint(FPoint in, float dx, float dy, float rot, float sx, float sy);
	void scaleGroup(float scx, float scy);
	void storeUndoInf(PageItem* b);
	void mouseDoubleClickEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *m);
	void mouseMoveEvent(QMouseEvent *m);
	void mousePressEvent(QMouseEvent *m);
	void HandleSizer(QPainter *p, PageItem *b, QRect mpo);
	void dragLeaveEvent(QDragLeaveEvent *e);
	void dragEnterEvent(QDragEnterEvent *e);
	void dragMoveEvent(QDragMoveEvent *e);
	void dropEvent(QDropEvent *e);
	bool SeleItem(QMouseEvent *m);
	bool SeleItemPos(QPoint m);
	void Deselect(bool prop = true);
	void SelectItemNr(int nr);
	void SetupDraw(int Nr);
	void MoveItemI(float newX, float newY, int ite);
	bool MoveItem(float newX, float newY, PageItem* ite, bool fromMP = false);
	void UpdateClip(PageItem* b);
	FPoint GetMaxClipF(FPointArray Clip);
	FPoint GetMinClipF(FPointArray Clip);
	QPoint GetMaxClip(QPointArray Clip);
	QPoint GetMinClip(QPointArray Clip);
	void SetPolyClip(PageItem *b, int up, int down);
	void UpdatePolyClip(PageItem *b);
	void ConvertClip(PageItem *b);
	void SetFrameRound(PageItem *b);
	void SetRectFrame(PageItem *b);
	void SetOvalFrame(PageItem *b);
	bool PointOnLine(QPoint Start, QPoint Ende, QRect MArea);
	void MirrorPolyH();
	void MirrorPolyV();
	void ShearPolyHR();
	void ShearPolyHL();
	void ShearPolyVU();
	void ShearPolyVD();
	void Reset1Control();
	void ResetControl();
	void AdjustItemSize(PageItem *b);
	bool GetItem(PageItem **b, int nr = -1);
	void MoveRotated(PageItem *b, FPoint npv);
	void AdjustPictScale(PageItem *b);
	bool SizeItem(float newX, float newY, int ite, bool fromMP = false, bool DoUpdateClip = true);
	bool MoveSizeItem(FPoint newX, FPoint newY, int ite);
	void RotateItem(float win, int ite);
	void MarkClip(PageItem *b);
	void Transform(PageItem *b, QPainter *p);
	void TransformM(PageItem *b, QPainter *p);
	void PaintSizeRect(QPainter *p, QRect alt, QRect neu);
	QPoint ApplyGrid(QPoint in);
	FPoint ApplyGridF(FPoint in);
	void RefreshItem(PageItem *b);
	void RepaintTextRegion(PageItem *b, QRegion alt);
	void EmitValues(PageItem *b);
	void AdjustPreview(PageItem *b);
	void FromHRuler(QMouseEvent *m);
	void FromVRuler(QMouseEvent *m);
	void SetYGuide(QMouseEvent *m);
	void SetXGuide(QMouseEvent *m);
	void SnapToGuides(PageItem* b);
	void ApplyGuides(float *x, float *y);
	void TextToPath();
	void UniteObj();
	void SplitObj();
	void PasteItem(struct CLBuf *Buffer, bool loading, bool drag = false);
	void ItemTextBrush(QString farbe);
	void ItemTextBrushS(int sha);
	void ItemTextPen(QString farbe);
	void ItemTextPenS(int sha);
	void ItemTextScale(int sha);
	QRegion ViewReg();
  /** Liste der Elemente */
  QPtrList<PageItem> Items;
  /** Dokument zu dem die Seite gehoert */
  ScribusDoc *doku;
  /** Nummer der Seite */
  uint PageNr;
  /** Name der Seite, wenn Musterseite */
  QString PageNam;
  QString MPageNam;
  QScrollView *Anz;
	QPopupMenu *pmen3;
  Margs Margins;
  int Mxp;
  int Myp;
  bool Mpressed;
  bool mCG;
  float oldW;
  QPtrList<PageItem> SelItem;
	QValueList<int> SelNode;
  int HowTo;
  int ClRe;
  int ClRe2;
	int SegP1;
	int SegP2;
  bool CursVis;
  int oldCp;
  int Dxp;
  int Dyp;
  bool Imoved;
  int SeRx;
  int SeRy;
  bool HaveSelRect;
  bool LeftPg;
  bool Magnify;
	bool FirstPoly;
	bool EdPoints;
	bool MoveSym;
	bool GroupSel;
	bool DraggedGroup;
	float GroupX;
	float GroupY;
	float GroupW;
	float GroupH;
	bool HanMove;
	int DrHY;
	int DrVX;
	QValueList<float> XGuides;
	QValueList<float> YGuides;
	uint GyM;
	bool MoveGY;
	uint GxM;
	bool MoveGX;
	FPoint RCenter;
	bool MidButt;

public slots:
	void ChLineWidth(float w);
	void ChLineArt(PenStyle w);
	void ChLineJoin(PenJoinStyle w);
	void ChLineEnd(PenCapStyle w);
	void ChLocalXY(float x, float y);
	void ChLocalSc(float x, float y);
	void ToggleBookmark();
	void ToggleAnnotation();
	void ToggleLock();
	void TogglePic();
	void FlipImageH();
	void FlipImageV();
	void ItemFont(QString fon);
	void chFSize(int size);
	void ItemPen(QString farbe);
	void ItemBrush(QString farbe);
	void ItemPenShade(int sha);
	void ItemBrushShade(int sha);
	void ItemGradFill(int typ, QString col1, int sh1, QString col2, int sh2);
	void QueryFarben();
	void SetFrameRect();
	void SetFrameRounded();
	void SetFrameOval();
	void ToBack();
	void ToFront();
	void LowerItem();
	void RaiseItem();
	void DeleteItem();
	bool slotSetCurs(int x, int y);
	void slotDoCurs(bool draw);
	void BlinkCurs();
	void ChLineSpa(float w);
	void chKerning(float us);
	void chTyStyle(int s);
	void SetAbStyle(int s);
	void chAbStyle(PageItem *b, int s);
	void AlignObj(bool xa, bool ya, bool Vth, bool Vtv, float xdisp, float ydisp, int xart, int yart);
	void sentToScrap();
	void sentToLayer(int id);
	void ToTextFrame();
	void ToPicFrame();
	void ToPolyFrame();
	void ToBezierFrame();
	void MoveClipPoint(PageItem *b, FPoint np);
	void ToPathText();
	void Bezier2Poly();

signals: // Signals
  /** Mausposition X */
  void Hrule(int);
  /** Mausposition Y */
  void Vrule(int);
  /** Seite gewechselt */
  void PgCh(int);
  /** Element gezeichnet */
  void PaintingDone();
  /** Element ausgewaehlt */
  void HaveSel(int);
  /** Seite veraendert */
  void DocChanged();
  /** Position eines Elementes */
  void ItemPos(float, float);
  /** Breite und Hoehe eines Elementes */
  void ItemGeom(float, float);
  void ItemRadius(float);
  /** Setzt den Drehungswinkel des Elementes */
  void SetAngle(float);
  /** Zoomfunktionen */
  void ZoomIn();
  void ZoomOut();
  void ZoomAbs();
  void AbsPosi(int, int);
  void AbsPosi2(int, int);
  /** Sendet die Linienstaerke an die Masspalette */
  void SetSizeValue(float);
  /** Sendet die Linienart an die Masspalette */
  void SetLineArt(PenStyle, PenCapStyle, PenJoinStyle);
  /** Sendet die lokalen Bildeigenschaften an die Masspalette */
  void SetLocalValues(float, float, float, float);
  /** Sendet die Stiftfarbe an die Farbpalette */
  void ItemFarben(QString, QString, int, int);
  void ItemGradient(QString, QString, int, int, int);
  /** Sendet die Textattribute an die Masspalette */
  void ItemTextAttr(float);
  /** Sendet die Schriftart */
  void ItemTextFont(QString);
  /** Sendet die Schriftgroesse */
  void ItemTextSize(int);
  void ItemTextSca(int);
  void ItemTextUSval(float);
  void ItemTextAbs(int);
  void ItemTextFarben(QString, QString, int, int);
  /** Text in Textbox selektiert */
  void HasTextSel();
  void HasNoTextSel();
  void CutItem();
  void CopyItem();
  void ItemTextStil(int);
  void LoadPic();
  void LoadElem(QString, int, int, bool, bool, ScribusDoc *);
  void Amode(int);
	void AnnotProps();
	void ToScrap(QString);
  void MousePos(float, float);
	void ClipPo(float, float);
	void HavePoint(bool, bool);
	void PolyOpen();
	void PStatus(int, uint);
	void UndoAvail();
	void EditGuides();
	void ItemTrans(float, float);
	void AddBM(PageItem *);
	void DelBM(PageItem *);
	void NewBMNr(int, int);
	void ChBMText(PageItem *);
	void RotMode(int);
	void RasterPic(bool);
};

#endif
