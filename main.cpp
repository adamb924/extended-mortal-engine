/// This should be run with the working directory as the "working-directory" (included in the repository)
/// It should be run with the single argument extended-model.xml (which is the model file)

#include <QCoreApplication>
#include <QCommandLineParser>

#include "morphology.h"
#include "morphologyxmlreader.h"
#include "numberofprecedinglettersiseven.h"
#include "reduplicator.h"

using namespace ME;

/// convenience function to check the grammaticality of a string
void process(const Morphology * m, const QString & str)
{
    const Form f(WritingSystem("wk-LA"), str);
    qInfo() << str << m->isWellFormed( f );
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /// this just processes the input file
    QCommandLineParser parser;
    parser.setApplicationDescription("Program to demonstrate Mortal Engine extensions.");
    parser.addHelpOption();
    parser.addPositionalArgument("input", QCoreApplication::translate("main", "Input file."));
    parser.process(a);
    const QStringList args = parser.positionalArguments();
    if( args.count() != 1 )
    {
        parser.showHelp();
    }
    const QString modelFile = args.at(0);

    /// first create a Morphology object
    Morphology *m = new Morphology;

    /// instead of using Morphology::readXmlFile, create your own MorphologyXmlReader object, passing it the Morphology object as an argument
    MorphologyXmlReader reader(m);
    /// these functions register the new contraints or nodes
    reader.registerConstraintMatcher<NumberOfPrecedingLettersIsEven>();
    reader.registerNodeMatcher<Reduplicator>();

    /// now use the reader object to read the model's XML
    try {
        reader.readXmlFile(modelFile);
    }  catch (const std::runtime_error& e) {
        qCritical() << e.what() << "(" << modelFile << ")";
    }

    if( !m->isOk() )
    {
        qCritical() << "Error reading model file";
        return 1;
    }

    /// these are just demonstrations that the model works as intended

    /// Should return true because aý has an even number of letters
    process(m, "aýSteven");

    /// Should return false because ata has an odd number of letters
    process(m, "ataSteven");

    /// Reduplicated and non-reduplicated forms are accepted
    process(m, "bil");
    process(m, "bilbil");
    process(m, "aýStevenaýSteven");

    /// Incorrectly reduplicated forms are rejected
    process(m, "bilbi");

    delete m;
    return 0;
}
