#pragma once
#include <QObject>

#include <unordered_map>
#include <utility>
#include <memory>
#include <vector>

struct Note;

class QTextDocument;
class QSignalMapper;


class NoteManager : public QObject
{
    Q_OBJECT
public:
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager();

    void createNewNote();
    void removeNote(int id);
    void renameNote(int id, const QString& newTitle);

    const Note& note(int id) const;
    QTextDocument* noteDocument(int id) const;
    std::vector<std::reference_wrapper<Note>> noteCollection(); // returns all notes so no parameters here
    size_t count() const;


signals:
    void newNoteCreated(int id);
    void noteContentChanged(int id);

private:
    void NoteContentChanged(int id);
    void readNotes();
    void writeNotes();
    // notes to be implemented on a XML file

    std::unique_ptr<QTextDocument> createNewTextDocument(const Note& note);

private:
    std::unordered_map<int, std::pair<Note, std::unique_ptr<QTextDocument>>> notes;

    QSignalMapper* mapChangedSignaltoNoteId = nullptr;

};
