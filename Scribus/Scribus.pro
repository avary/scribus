######################################################################
# Automatically generated by qmake (1.07a) Thu Feb 10 19:54:31 2005
######################################################################

TEMPLATE = app
DEPENDPATH += scribus \
              scribus/libabout \
              scribus/libpdf \
              scribus/libpostscript \
              scribus/libprefs \
              scribus/po \
              scribus/plugins/fontpreview \
              scribus/plugins/newfromtemplateplugin \
              scribus/plugins/pixmapexport \
              scribus/plugins/printpreview \
              scribus/plugins/psimport \
              scribus/plugins/saveastemplateplugin \
              scribus/plugins/scriptplugin \
              scribus/plugins/short-words \
              scribus/plugins/svgexplugin \
              scribus/plugins/svgimplugin \
              scribus/plugins/fileloader/oodraw \
              scribus/plugins/gettext/csvim \
              scribus/plugins/gettext/htmlim \
              scribus/plugins/gettext/sxwim \
              scribus/plugins/gettext/textfilter \
              scribus/plugins/gettext/txtim
INCLUDEPATH += . \
               scribus \
               scribus/libprefs \
               scribus/libabout \
               scribus/libpostscript \
               scribus/libpdf \
               scribus/plugins/fontpreview \
               scribus/plugins/newfromtemplateplugin \
               scribus/plugins/pixmapexport \
               scribus/plugins/printpreview \
               scribus/plugins/psimport \
               scribus/plugins/saveastemplateplugin \
               scribus/plugins/scriptplugin \
               scribus/plugins/short-words \
               scribus/plugins/svgexplugin \
               scribus/plugins/svgimplugin \
               scribus/plugins/fileloader/oodraw \
               scribus/plugins/gettext/csvim \
               scribus/plugins/gettext/htmlim \
               scribus/plugins/gettext/sxwim \
               scribus/plugins/gettext/textfilter \
               scribus/plugins/gettext/txtim

# Input
HEADERS += config.h \
           scribus/align.h \
           scribus/alignselect.h \
           scribus/annot.h \
           scribus/annota.h \
           scribus/applytemplate.h \
           scribus/arrowchooser.h \
           scribus/art_kmisc.h \
           scribus/art_render_misc.h \
           scribus/art_render_pattern.h \
           scribus/art_rgb.h \
           scribus/art_rgb_affine_private.h \
           scribus/art_rgb_svp.h \
           scribus/art_rgba_affine.h \
           scribus/autoform.h \
           scribus/bookmwin.h \
           scribus/bookpalette.h \
           scribus/buttonicon.h \
           scribus/charselect.h \
           scribus/checkDocument.h \
           scribus/cmsprefs.h \
           scribus/cmykcolor.h \
           scribus/cmykfw.h \
           scribus/color.h \
           scribus/colorchart.h \
           scribus/colorm.h \
           scribus/cpalette.h \
           scribus/cupsoptions.h \
           scribus/customfdialog.h \
           scribus/dcolor.h \
           scribus/delpages.h \
           scribus/docinfo.h \
           scribus/druck.h \
           scribus/edit1format.h \
           scribus/editformats.h \
           scribus/editor.h \
           scribus/fileloader.h \
           scribus/filewatcher.h \
           scribus/fmitem.h \
           scribus/fontcombo.h \
           scribus/fontprefs.h \
           scribus/fontreplacedialog.h \
           scribus/fparser.h \
           scribus/fpoint.h \
           scribus/fpointarray.h \
           scribus/frameedit.h \
           scribus/gdk-pixbuf-xlib-private.h \
           scribus/gdk-pixbuf-xlib.h \
           scribus/gdk-pixbuf-xlibrgb.h \
           scribus/gradienteditor.h \
           scribus/gtaction.h \
           scribus/gtdialogs.h \
           scribus/gtfont.h \
           scribus/gtframestyle.h \
           scribus/gtgettext.h \
           scribus/gtmeasure.h \
           scribus/gtparagraphstyle.h \
           scribus/gtstyle.h \
           scribus/gtwriter.h \
           scribus/guidemanager.h \
           scribus/helpbrowser.h \
           scribus/hnjalloc.h \
           scribus/hruler.h \
           scribus/hyask.h \
           scribus/hyphen.h \
           scribus/hyphenator.h \
           scribus/hysettings.h \
           scribus/icons5.h \
           scribus/icons6.h \
           scribus/insertTable.h \
           scribus/inspage.h \
           scribus/javadocs.h \
           scribus/keymanager.h \
           scribus/langmgr.h \
           scribus/layers.h \
           scribus/linecombo.h \
           scribus/lineformats.h \
           scribus/linkbutton.h \
           scribus/md5.h \
           scribus/mdup.h \
           scribus/measurements.h \
           scribus/menumanager.h \
           scribus/mergedoc.h \
           scribus/missing.h \
           scribus/movepage.h \
           scribus/mpalette.h \
           scribus/mspinbox.h \
           scribus/multiline.h \
           scribus/muster.h \
           scribus/navigator.h \
           scribus/newfile.h \
           scribus/newtemp.h \
           scribus/page.h \
           scribus/pageitem.h \
           scribus/pageselector.h \
           scribus/pdfopts.h \
           scribus/picsearch.h \
           scribus/picstatus.h \
           scribus/polygonwidget.h \
           scribus/polyprops.h \
           scribus/prefscontext.h \
           scribus/prefsdialogbase.h \
           scribus/prefsfile.h \
           scribus/prefsreader.h \
           scribus/prefstable.h \
           scribus/query.h \
           scribus/rc4.h \
           scribus/reformdoc.h \
           scribus/scfonts.h \
           scribus/scfonts_ttf.h \
           scribus/scmenu.h \
           scribus/scpainter.h \
           scribus/scpreview.h \
           scribus/scraction.h \
           scribus/scrap.h \
           scribus/scribus.h \
           scribus/scribusdoc.h \
           scribus/scribusstructs.h \
           scribus/scribusview.h \
           scribus/scribuswin.h \
           scribus/scribusXml.h \
           scribus/search.h \
           scribus/seiten.h \
           scribus/selfield.h \
           scribus/serializer.h \
           scribus/shadebutton.h \
           scribus/spalette.h \
           scribus/splash.h \
           scribus/story.h \
           scribus/styleselect.h \
           scribus/tabcheckdoc.h \
           scribus/tabguides.h \
           scribus/tabmanager.h \
           scribus/tabpdfoptions.h \
           scribus/tabruler.h \
           scribus/tabtools.h \
           scribus/tabtypography.h \
           scribus/tree.h \
           scribus/undogui.h \
           scribus/undomanager.h \
           scribus/undoobject.h \
           scribus/undostate.h \
           scribus/units.h \
           scribus/vgradient.h \
           scribus/vruler.h \
           scribus/werktoolb.h \
           scribus/libabout/about.h \
           scribus/libpdf/pdflib.h \
           scribus/libpostscript/pslib.h \
           scribus/libprefs/prefs.h \
           scribus/plugins/fontpreview/fontpreview.h \
           scribus/plugins/fontpreview/ui.h \
           scribus/plugins/newfromtemplateplugin/nftdialog.h \
           scribus/plugins/newfromtemplateplugin/nftemplate.h \
           scribus/plugins/newfromtemplateplugin/nftrcreader.h \
           scribus/plugins/newfromtemplateplugin/nftsettings.h \
           scribus/plugins/newfromtemplateplugin/nfttemplate.h \
           scribus/plugins/pixmapexport/dialog.h \
           scribus/plugins/pixmapexport/export.h \
           scribus/plugins/printpreview/preview.h \
           scribus/plugins/psimport/importps.h \
           scribus/plugins/saveastemplateplugin/satdialog.h \
           scribus/plugins/saveastemplateplugin/satemplate.h \
           scribus/plugins/scriptplugin/cmdcolor.h \
           scribus/plugins/scriptplugin/cmddialog.h \
           scribus/plugins/scriptplugin/cmddoc.h \
           scribus/plugins/scriptplugin/cmdgetprop.h \
           scribus/plugins/scriptplugin/cmdgetsetprop.h \
           scribus/plugins/scriptplugin/cmdmani.h \
           scribus/plugins/scriptplugin/cmdmisc.h \
           scribus/plugins/scriptplugin/cmdobj.h \
           scribus/plugins/scriptplugin/cmdpage.h \
           scribus/plugins/scriptplugin/cmdsetprop.h \
           scribus/plugins/scriptplugin/cmdtext.h \
           scribus/plugins/scriptplugin/cmdutil.h \
           scribus/plugins/scriptplugin/cmdvar.h \
           scribus/plugins/scriptplugin/conswin.h \
           scribus/plugins/scriptplugin/guiapp.h \
           scribus/plugins/scriptplugin/objimageexport.h \
           scribus/plugins/scriptplugin/objpdffile.h \
           scribus/plugins/scriptplugin/objprinter.h \
           scribus/plugins/scriptplugin/pconsole.h \
           scribus/plugins/scriptplugin/scriptplugin.h \
           scribus/plugins/scriptplugin/valuedialog.h \
           scribus/plugins/short-words/configuration.h \
           scribus/plugins/short-words/parse.h \
           scribus/plugins/short-words/shortwords.h \
           scribus/plugins/short-words/version.h \
           scribus/plugins/short-words/vlnadialog.h \
           scribus/plugins/svgexplugin/svgexplugin.h \
           scribus/plugins/svgimplugin/color.h \
           scribus/plugins/svgimplugin/svgplugin.h \
           scribus/plugins/fileloader/oodraw/color.h \
           scribus/plugins/fileloader/oodraw/crypt.h \
           scribus/plugins/fileloader/oodraw/ioapi.h \
           scribus/plugins/fileloader/oodraw/oodrawimp.h \
           scribus/plugins/fileloader/oodraw/stylestack.h \
           scribus/plugins/fileloader/oodraw/sxwunzip.h \
           scribus/plugins/fileloader/oodraw/unzip.h \
           scribus/plugins/gettext/csvim/csvdia.h \
           scribus/plugins/gettext/csvim/csvim.h \
           scribus/plugins/gettext/htmlim/htmlim.h \
           scribus/plugins/gettext/htmlim/htmlreader.h \
           scribus/plugins/gettext/sxwim/contentreader.h \
           scribus/plugins/gettext/sxwim/crypt.h \
           scribus/plugins/gettext/sxwim/ioapi.h \
           scribus/plugins/gettext/sxwim/stylereader.h \
           scribus/plugins/gettext/sxwim/sxwdia.h \
           scribus/plugins/gettext/sxwim/sxwim.h \
           scribus/plugins/gettext/sxwim/sxwunzip.h \
           scribus/plugins/gettext/sxwim/unzip.h \
           scribus/plugins/gettext/textfilter/textfilter.h \
           scribus/plugins/gettext/textfilter/tfdia.h \
           scribus/plugins/gettext/textfilter/tffilter.h \
           scribus/plugins/gettext/txtim/txtim.h
SOURCES += scribus/align.cpp \
           scribus/alignselect.cpp \
           scribus/annot.cpp \
           scribus/annota.cpp \
           scribus/applytemplate.cpp \
           scribus/arrowchooser.cpp \
           scribus/art_kmisc.c \
           scribus/art_render_misc.c \
           scribus/art_render_pattern.c \
           scribus/art_rgb.c \
           scribus/art_rgb_affine_private.c \
           scribus/art_rgb_svp.c \
           scribus/art_rgba_affine.c \
           scribus/autoform.cpp \
           scribus/bookmwin.cpp \
           scribus/bookpalette.cpp \
           scribus/buttonicon.cpp \
           scribus/charselect.cpp \
           scribus/checkDocument.cpp \
           scribus/cmsprefs.cpp \
           scribus/cmykcolor.cpp \
           scribus/cmykfw.cpp \
           scribus/colorchart.cpp \
           scribus/colorm.cpp \
           scribus/cpalette.cpp \
           scribus/cupsoptions.cpp \
           scribus/customfdialog.cpp \
           scribus/dcolor.cpp \
           scribus/delpages.cpp \
           scribus/docinfo.cpp \
           scribus/druck.cpp \
           scribus/edit1format.cpp \
           scribus/editformats.cpp \
           scribus/editor.cpp \
           scribus/fileloader.cpp \
           scribus/filewatcher.cpp \
           scribus/fmitem.cpp \
           scribus/fontcombo.cpp \
           scribus/fontprefs.cpp \
           scribus/fontreplacedialog.cpp \
           scribus/fparser.cpp \
           scribus/fpoint.cpp \
           scribus/fpointarray.cpp \
           scribus/frameedit.cpp \
           scribus/gdk-pixbuf-xlib-drawable.c \
           scribus/gdk-pixbuf-xlib-render.c \
           scribus/gdk-pixbuf-xlib.c \
           scribus/gdk-pixbuf-xlibrgb.c \
           scribus/gradienteditor.cpp \
           scribus/gtaction.cpp \
           scribus/gtdialogs.cpp \
           scribus/gtfont.cpp \
           scribus/gtframestyle.cpp \
           scribus/gtgettext.cpp \
           scribus/gtmeasure.cpp \
           scribus/gtparagraphstyle.cpp \
           scribus/gtstyle.cpp \
           scribus/gtwriter.cpp \
           scribus/guidemanager.cpp \
           scribus/helpbrowser.cpp \
           scribus/hnjalloc.c \
           scribus/hruler.cpp \
           scribus/hyask.cpp \
           scribus/hyphen.c \
           scribus/hyphenator.cpp \
           scribus/hysettings.cpp \
           scribus/insertTable.cpp \
           scribus/inspage.cpp \
           scribus/javadocs.cpp \
           scribus/keymanager.cpp \
           scribus/langmgr.cpp \
           scribus/layers.cpp \
           scribus/linecombo.cpp \
           scribus/lineformats.cpp \
           scribus/linkbutton.cpp \
           scribus/main.cpp \
           scribus/md5.c \
           scribus/mdup.cpp \
           scribus/measurements.cpp \
           scribus/menumanager.cpp \
           scribus/mergedoc.cpp \
           scribus/missing.cpp \
           scribus/movepage.cpp \
           scribus/mpalette.cpp \
           scribus/mspinbox.cpp \
           scribus/multiline.cpp \
           scribus/muster.cpp \
           scribus/navigator.cpp \
           scribus/newfile.cpp \
           scribus/newtemp.cpp \
           scribus/page.cpp \
           scribus/pageitem.cpp \
           scribus/pageselector.cpp \
           scribus/pdfopts.cpp \
           scribus/picsearch.cpp \
           scribus/picstatus.cpp \
           scribus/polygonwidget.cpp \
           scribus/polyprops.cpp \
           scribus/prefscontext.cpp \
           scribus/prefsdialogbase.cpp \
           scribus/prefsfile.cpp \
           scribus/prefsreader.cpp \
           scribus/prefstable.cpp \
           scribus/query.cpp \
           scribus/rc4.c \
           scribus/reformdoc.cpp \
           scribus/scfonts.cpp \
           scribus/scfonts_ttf.cpp \
           scribus/scmenu.cpp \
           scribus/scpainter.cpp \
           scribus/scpreview.cpp \
           scribus/scraction.cpp \
           scribus/scrap.cpp \
           scribus/scribus.cpp \
           scribus/scribusdoc.cpp \
           scribus/scribusview.cpp \
           scribus/scribuswin.cpp \
           scribus/scribusXml.cpp \
           scribus/search.cpp \
           scribus/seiten.cpp \
           scribus/selfield.cpp \
           scribus/serializer.cpp \
           scribus/shadebutton.cpp \
           scribus/spalette.cpp \
           scribus/splash.cpp \
           scribus/story.cpp \
           scribus/styleselect.cpp \
           scribus/tabcheckdoc.cpp \
           scribus/tabguides.cpp \
           scribus/tabmanager.cpp \
           scribus/tabpdfoptions.cpp \
           scribus/tabruler.cpp \
           scribus/tabtools.cpp \
           scribus/tabtypography.cpp \
           scribus/translationdummy.cpp \
           scribus/tree.cpp \
           scribus/undogui.cpp \
           scribus/undomanager.cpp \
           scribus/undoobject.cpp \
           scribus/undostate.cpp \
           scribus/units.cpp \
           scribus/util.cpp \
           scribus/vgradient.cpp \
           scribus/vruler.cpp \
           scribus/werktoolb.cpp \
           scribus/libabout/about.cpp \
           scribus/libpdf/pdflib.cpp \
           scribus/libpostscript/pslib.cpp \
           scribus/libprefs/prefs.cpp \
           scribus/plugins/fontpreview/fontpreview.cpp \
           scribus/plugins/fontpreview/ui.cpp \
           scribus/plugins/newfromtemplateplugin/nftdialog.cpp \
           scribus/plugins/newfromtemplateplugin/nftemplate.cpp \
           scribus/plugins/newfromtemplateplugin/nftrcreader.cpp \
           scribus/plugins/newfromtemplateplugin/nftsettings.cpp \
           scribus/plugins/newfromtemplateplugin/nfttemplate.cpp \
           scribus/plugins/pixmapexport/dialog.cpp \
           scribus/plugins/pixmapexport/export.cpp \
           scribus/plugins/printpreview/preview.cpp \
           scribus/plugins/psimport/importps.cpp \
           scribus/plugins/saveastemplateplugin/satdialog.cpp \
           scribus/plugins/saveastemplateplugin/satemplate.cpp \
           scribus/plugins/scriptplugin/cmdcolor.cpp \
           scribus/plugins/scriptplugin/cmddialog.cpp \
           scribus/plugins/scriptplugin/cmddoc.cpp \
           scribus/plugins/scriptplugin/cmdgetprop.cpp \
           scribus/plugins/scriptplugin/cmdgetsetprop.cpp \
           scribus/plugins/scriptplugin/cmdmani.cpp \
           scribus/plugins/scriptplugin/cmdmisc.cpp \
           scribus/plugins/scriptplugin/cmdobj.cpp \
           scribus/plugins/scriptplugin/cmdpage.cpp \
           scribus/plugins/scriptplugin/cmdsetprop.cpp \
           scribus/plugins/scriptplugin/cmdtext.cpp \
           scribus/plugins/scriptplugin/cmdutil.cpp \
           scribus/plugins/scriptplugin/conswin.cpp \
           scribus/plugins/scriptplugin/guiapp.cpp \
           scribus/plugins/scriptplugin/objimageexport.cpp \
           scribus/plugins/scriptplugin/objpdffile.cpp \
           scribus/plugins/scriptplugin/objprinter.cpp \
           scribus/plugins/scriptplugin/pconsole.cpp \
           scribus/plugins/scriptplugin/scriptplugin.cpp \
           scribus/plugins/scriptplugin/valuedialog.cpp \
           scribus/plugins/short-words/configuration.cpp \
           scribus/plugins/short-words/parse.cpp \
           scribus/plugins/short-words/shortwords.cpp \
           scribus/plugins/short-words/vlnadialog.cpp \
           scribus/plugins/svgexplugin/svgexplugin.cpp \
           scribus/plugins/svgimplugin/svgplugin.cpp \
           scribus/plugins/fileloader/oodraw/ioapi.c \
           scribus/plugins/fileloader/oodraw/oodrawimp.cpp \
           scribus/plugins/fileloader/oodraw/stylestack.cpp \
           scribus/plugins/fileloader/oodraw/sxwunzip.cpp \
           scribus/plugins/fileloader/oodraw/unzip.c \
           scribus/plugins/gettext/csvim/csvdia.cpp \
           scribus/plugins/gettext/csvim/csvim.cpp \
           scribus/plugins/gettext/htmlim/htmlim.cpp \
           scribus/plugins/gettext/htmlim/htmlreader.cpp \
           scribus/plugins/gettext/sxwim/contentreader.cpp \
           scribus/plugins/gettext/sxwim/ioapi.c \
           scribus/plugins/gettext/sxwim/stylereader.cpp \
           scribus/plugins/gettext/sxwim/sxwdia.cpp \
           scribus/plugins/gettext/sxwim/sxwim.cpp \
           scribus/plugins/gettext/sxwim/sxwunzip.cpp \
           scribus/plugins/gettext/sxwim/unzip.c \
           scribus/plugins/gettext/textfilter/textfilter.cpp \
           scribus/plugins/gettext/textfilter/tfdia.cpp \
           scribus/plugins/gettext/textfilter/tffilter.cpp \
           scribus/plugins/gettext/txtim/txtim.cpp
TRANSLATIONS += scribus/po/scribus.af.ts \
                scribus/po/scribus.bg.ts \
                scribus/po/scribus.br.ts \
                scribus/po/scribus.ca.ts \
                scribus/po/scribus.cs_CZ.ts \
                scribus/po/scribus.cy.ts \
                scribus/po/scribus.da_DK.ts \
                scribus/po/scribus.de.ts \
                scribus/po/scribus.en_GB.ts \
                scribus/po/scribus.es_ES.ts \
                scribus/po/scribus.eu.ts \
                scribus/po/scribus.fi.ts \
                scribus/po/scribus.gl.ts \
                scribus/po/scribus.hu.ts \
                scribus/po/scribus.id.ts \
                scribus/po/scribus.lt_LT.ts \
                scribus/po/scribus.nb_NO.ts \
                scribus/po/scribus.nl.ts \
                scribus/po/scribus.pl_PL.ts \
                scribus/po/scribus.pt_BR.ts \
                scribus/po/scribus.ru.ts \
                scribus/po/scribus.se.ts \
                scribus/po/scribus.sl.ts \
                scribus/po/scribus.sq.ts \
                scribus/po/scribus.sr.ts \
                scribus/po/scribus.tr.ts \
                scribus/po/scribus.uk.ts \
                scribus/po/scribus.zh_CN.ts
