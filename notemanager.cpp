#include "notemanager.h"
#include "note.h"

#include <QTextDocument>
#include <QSignalMapper>

int nextNodeId();

NoteManager::NoteManager(QObject *parent) : QObject(parent) // we are gonna allocate this on the stack
{
    mapChangedSignaltoNoteId = new QSignalMapper(this);
    connect(mapChangedSignaltoNoteId, &QSignalMapper::mappedInt, this, &NoteManager::NoteContentChanged);

    readNotes();

    if(notes.size() == 0)
        createNewNote();
}

NoteManager::~NoteManager()
{

    writeNotes();
}

void NoteManager::createNewNote()
{
    int id = nextNodeId();

    //     std::unordered_map<int, std::pair<Note, std::unique_ptr<QTextDocument>>> notes;

    auto& [note, textDocument] = notes[id]; // structured bindings, returns textDocument
    note.id = id;
    note.title = "New Note";
    note.lastModified = QDateTime::currentDateTime();
    textDocument = createNewTextDocument(note);

    emit newNoteCreated(id);



}

void NoteManager::removeNote(int id)
{

    notes.erase(id);

    if (notes.empty())
        createNewNote();
}

void NoteManager::renameNote(int id, const QString &newTitle)
{

    auto found = notes.find(id);
    if (found != notes.end()) {

        auto& [note, textDocument] = found->second;
        note.title = newTitle;
        note.lastModified = QDateTime::currentDateTime();

    }
}

const Note& NoteManager::note(int id) const
{
    // return notes[id].first;  // it will create a new item with same id
    return notes.at(id).first;

}

QTextDocument *NoteManager::noteDocument(int id) const
{

    auto found = notes.find(id);
    if (found != notes.end())  // notes.end() is an invalid element
    {
        return found->second.second.get();
        // found is an iterator to a pair, first element is an id (int), the second element is a pair<Note, std::unique_ptr<QTextDocument>>
        // get() for accessing the raw pointer, stored in the unique_ptr


    }
    return nullptr;
}

std::vector<std::reference_wrapper<Note> > NoteManager::noteCollection()
{
    std::vector<std::reference_wrapper<Note>> out;
    for (auto& i : notes) {
        auto& [note, textDocument] = i.second;
        note.content = textDocument->toPlainText();  // toHtml for adding richtext or coloring
        out.push_back(note);
    }
    return out;

}

size_t NoteManager::count() const
{
    return notes.size();
}

void NoteManager::NoteContentChanged(int id)
{

    notes.at(id).first.lastModified = QDateTime::currentDateTime();

    emit noteContentChanged(id);

}


void NoteManager::readNotes()
{
    //TODO
}

void NoteManager::writeNotes()
{
    //TODO
}

std::unique_ptr<QTextDocument> NoteManager::createNewTextDocument(const Note &note) {

    auto textDocument = std::make_unique<QTextDocument>(note.content);
    connect(textDocument.get(), &QTextDocument::contentsChanged, mapChangedSignaltoNoteId, qOverload<>(&QSignalMapper::map));
    mapChangedSignaltoNoteId->setMapping(textDocument.get(), note.id);
    return textDocument;

}

int nextNodeId() {

    static int id = 0;
    return ++id;

}
