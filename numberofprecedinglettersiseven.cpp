#include "numberofprecedinglettersiseven.h"

#include "datatypes/parsing.h"

#include <QXmlStreamReader>

NumberOfPrecedingLettersIsEven::NumberOfPrecedingLettersIsEven() : AbstractConstraint(AbstractConstraint::MatchCondition)
{

}

QString NumberOfPrecedingLettersIsEven::summary(const QString &suffix) const
{
    Q_UNUSED(suffix)
    return "NumberOfPrecedingLettersIsEven()";
}

QString NumberOfPrecedingLettersIsEven::elementName()
{
    return "preceding-letters-even";
}

AbstractConstraint *NumberOfPrecedingLettersIsEven::readFromXml(QXmlStreamReader &in, MorphologyXmlReader *morphologyReader)
{
    Q_UNUSED(in)
    Q_UNUSED(morphologyReader)
    return new NumberOfPrecedingLettersIsEven;
}

bool NumberOfPrecedingLettersIsEven::matchesElement(QXmlStreamReader &in)
{
    return in.name() == elementName();
}

bool NumberOfPrecedingLettersIsEven::matchesThisConstraint(const Parsing *parsing, const AbstractNode *node, const Allomorph &allomorph) const
{
    Q_UNUSED(node)
    Q_UNUSED(allomorph)
    return (parsing->parsedSoFar().length() % 2) == 0;
}
