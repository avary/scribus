

#ifndef STYLESET_H
#define STYLESET_H

#include <assert.h>
#include <qvaluelist.h>
#include "style.h"

template<class STYLE>
class StyleSet : public StyleBase {
public:
	STYLE& operator[] (uint index) { assert(index < styles.count()); return * styles[index]; }
	const STYLE& operator[] (uint index) const { assert(index < styles.count()); return * styles[index]; }
	inline int find(QString name);
	inline const Style* resolve(QString name) const;
	uint count() const { return (uint) styles.count(); }
	void append(STYLE* style) { styles.append(style); }
	inline void remove(uint index, const STYLE* with = NULL);
	inline void redefine(QValueList<STYLE> defs, bool removeUnused=false);
	void create(const STYLE& proto) { styles.append(new STYLE(proto)); }
	StyleSet() : styles(), m_base(NULL), m_baseversion(-1) {}
	~StyleSet() { while(styles.count()>0) { delete styles.front(); styles.pop_front(); } }

	void setBase(StyleBase* base)    { m_base = base; m_baseversion = -1; }
	StyleBase* base()                { return m_base; }
	
private:
	StyleSet(const StyleSet&) {}
	StyleSet& operator= (const StyleSet&) { return *this; }
	QValueList<STYLE*> styles;
	StyleBase* m_base;
	int m_baseversion;
};

template<class STYLE>
inline void StyleSet<STYLE>::remove(uint index, const STYLE* with)
{
	assert(index < styles.count()); 
	typename QValueList<STYLE*>::Iterator it = styles.at(index);
	(*it)->erase();
	if (with)
		(*it)->setParent(with->name());
}

template<class STYLE>
inline int StyleSet<STYLE>::find(QString name)
{
	for (uint i=0; i < styles.count(); ++i)
		if (styles[i]->name() == name)
			return i;
	return -1;
}

template<class STYLE>
inline const Style* StyleSet<STYLE>::resolve(QString name) const
{
	for (uint i=0; i < styles.count(); ++i)
		if (styles[i]->name() == name)
			return styles[i];
	return m_base ? m_base->resolve(name) : NULL;
}

template<class STYLE>
inline void StyleSet<STYLE>::redefine(QValueList<STYLE> defs, bool removeUnused)
{
	for (int i=signed(styles.count())-1; i >=0; --i) {
		bool found = false;
		for (uint j=0; j < defs.count(); ++j) {
			if (styles[i]->name() == defs[j].name()) {
				found = true;
				(*styles[i]) = defs[j];
				break;
			}
		}
		if (!found && removeUnused) {
			remove(i);
		}
	}
	for (uint j=0; j < defs.count(); ++j) {
		if (find(defs[j].name()) < 0) {
			create(defs[j]);
		}
	}
// FIXME: replace temp parents with ones from this
}

#endif


