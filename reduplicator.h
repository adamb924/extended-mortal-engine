#ifndef REDUPLICATOR_H
#define REDUPLICATOR_H

#include "nodes/abstractnode.h"

/// this is a demo node class. If the <reduplicator> node is present, it simply reduplicates everything that has come before.

using namespace ME;

class Reduplicator : public AbstractNode
{
public:
    Reduplicator(const MorphologicalModel * model);

    static QString elementName();
    static AbstractNode *readFromXml(QXmlStreamReader &in, MorphologyXmlReader * morphologyReader, const MorphologicalModel * model);
    static bool matchesElement(QXmlStreamReader &in);

    AbstractNode * copy(MorphologyXmlReader *morphologyReader, const QString & idSuffix) const override;
    QList<const AbstractNode*> availableMorphemeNodes(QHash<const Jump*,int> &jumps) const override;

private:
    QList<Parsing> parsingsUsingThisNode( const Parsing & parsing, Parsing::Flags flags) const override;
    QList<Generation> generateFormsUsingThisNode( const Generation & generation ) const override;

};

#endif // REDUPLICATOR_H
