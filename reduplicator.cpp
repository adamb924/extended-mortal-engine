#include "reduplicator.h"

#include "datatypes/generation.h"

#include <QXmlStreamReader>

Reduplicator::Reduplicator(const MorphologicalModel *model) : AbstractNode(model, AbstractNode::MorphemeNodeType)
{

}

QString Reduplicator::elementName()
{
    return "reduplicator";

}

AbstractNode *Reduplicator::readFromXml(QXmlStreamReader &in, MorphologyXmlReader *morphologyReader, const MorphologicalModel *model)
{
    Q_ASSERT( in.isStartElement() );
    Reduplicator* r = new Reduplicator(model);
    r->readInitialNodeAttributes(in, morphologyReader);

    if( in.attributes().value("optional").toString() == "true" )
        r->setOptional(true);

    /// skip to closing element
    in.readNext();

    Q_ASSERT( in.isEndElement() && in.name() == elementName() );
    return r;
}

bool Reduplicator::matchesElement(QXmlStreamReader &in)
{
    return in.isStartElement() && in.name() == elementName();
}

AbstractNode *Reduplicator::copy(MorphologyXmlReader *morphologyReader, const QString &idSuffix) const
{
    Q_UNUSED(morphologyReader)

    Reduplicator * r = new Reduplicator( model() );

    /// copy AbstractNode properties
    r->setLabel( label() );
    /// mType will be set by the constructor
    /// mNext will be set by the constructor
    r->setOptional( optional() );
    if( !id().isEmpty() )
    {
        r->setId( id() + idSuffix );
    }

    return r;
}

QList<const AbstractNode *> Reduplicator::availableMorphemeNodes(QHash<const Jump *, int> &jumps) const
{
    QList<const AbstractNode *> list;
    list << this;

    /// move on to the next node if this one is optional
    if( optional() && AbstractNode::next() != nullptr )
    {
        list.append( AbstractNode::next()->availableMorphemeNodes(jumps) );
    }

    return list;
}

QList<Parsing> Reduplicator::parsingsUsingThisNode(const Parsing &parsing, Parsing::Flags flags) const
{
    Q_UNUSED(flags)
    QList<Parsing> list;
    Parsing reduplicated(parsing);
    Allomorph a( parsing.parsedSoFar(),  Allomorph::Original);
    reduplicated.append(this, a);
    appendIfComplete(list, reduplicated);
    return list;
}

QList<Generation> Reduplicator::generateFormsUsingThisNode(const Generation &generation) const
{
    Q_UNUSED(generation)
    qCritical() << "Apologies. I did not implement Reduplicator::generateFormsUsingThisNode.";
    return QList<Generation>();
}
