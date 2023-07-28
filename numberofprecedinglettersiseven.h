#ifndef NUMBEROFPRECEDINGLETTERSISEVEN_H
#define NUMBEROFPRECEDINGLETTERSISEVEN_H

#include "constraints/abstractconstraint.h"

/// this is a demo class. If the <reduplicator> node is present, it simply reduplicates everything that has come before.

class NumberOfPrecedingLettersIsEven : public AbstractConstraint
{
public:
    NumberOfPrecedingLettersIsEven();

    QString summary(const QString & suffix = QString()) const override;

    static QString elementName();
    static AbstractConstraint *readFromXml(QXmlStreamReader &in, MorphologyXmlReader * morphologyReader);
    static bool matchesElement(QXmlStreamReader &in);

private:
    bool matchesThisConstraint( const Parsing * parsing, const AbstractNode *node, const Allomorph &allomorph ) const override;

};

#endif // NUMBEROFPRECEDINGLETTERSISEVEN_H
