/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
 
#ifndef SCCOLORTRANSFORMPOOL_H
#define SCCOLORTRANSFORMPOOL_H

#include <QSet>
#include "sccolormngtstructs.h"
#include "sccolortransform.h"

class ScColorTransformPool
{
public:
	ScColorTransformPool (int engineID);

	void clear(void);
	void addTransform(const ScColorTransform& transform);
	void removeTransform(const ScColorTransform& transform);
	void removeTransform(const ScColorTransformInfo& info);

	ScColorTransform findTransform(const ScColorTransformInfo& info) const;

protected:
	int m_engineID;
	QSet<ScColorTransform> m_pool;
};

#endif
