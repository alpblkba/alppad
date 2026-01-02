#include "xmlstorage.h"
#include "note.h"

#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>



XmlStorage::XmlStorage() {

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;

    if(!dir.exists(path)) {

        dir.mkdir(path);
    }

    fullFilePath = QString("%0/%1").arg(path, fileName);
}

std::vector<Note> XmlStorage::read()
{

    std::vector<Note> notes;

    QFile inputFile(fullFilePath);

    if(inputFile.open(QIODevice::ReadOnly)) {

        QXmlStreamReader reader(&inputFile);
        if(reader.readNextStartElement()) {

            if(reader.name() == xmlRootToken) {

                while (reader.readNextStartElement()) {
                    readNote(reader, notes);
                }
            }
            else {
                reader.skipCurrentElement();
            }
        }
    }
    return notes;
}

void XmlStorage::readNote(QXmlStreamReader &stream, std::vector<Note> &notes)
{
    if(stream.name() == noteToken) {

        Note note;
        auto attributes = stream.attributes(); // attributes retrieved from stream
        note.title = attributes.value(titleToken).toString(); // value returns string ref
        note.lastModified = QDateTime::fromString(attributes.value(lastModifiedToken).toString(), dateTimeFormat);

        stream.readNextStartElement();
        if(stream.name() == contentToken) {  // making sure that we are reading an actual XML element

            note.content = stream.readElementText();
        }
        notes.push_back(note);


    }
    stream.skipCurrentElement();
}

bool XmlStorage::write(const std::vector<std::reference_wrapper<Note> > &notes)
{

    QFile outputFile(fullFilePath);

    if(!outputFile.open(QIODevice::WriteOnly)) {

        return false;
    }

    QXmlStreamWriter writer(&outputFile);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();

    // iterate over each note and inside that loop we will call writeNote
    // after loop, stream right end element and stream right end document
    writer.writeStartDocument(xmlRootToken);

    for (auto& note : notes) {

        writeNote(writer, note);
    }

    writer.writeEndElement();
    writer.writeEndDocument();


}

void XmlStorage::writeNote(QXmlStreamWriter &stream, const Note &note)
{
    // title and lastModified are the attributes of the main Note element (from readNote)
    // text element of the Note, will be the content

    stream.writeStartElement(noteToken);

    stream.writeAttribute(titleToken, note.title);

    stream.writeAttribute(lastModifiedToken, note.lastModified.toString(dateTimeFormat));

    stream.writeTextElement(contentToken, note.content);

    stream.writeEndElement();
}


