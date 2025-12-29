#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "note.h"
#include "notemanager.h"
#include "noteslistwidget.h"
#include "QMessageBox"
#include "algorithm"

MainWindow::MainWindow(NoteManager& manager, QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), noteManager(manager)

// whenever you have a member reference in argument, you can't initilize it in the constructor body
// because references refer something always that is constant, a constant pointer. they cannot change what they reference.

{
    ui->setupUi(this);

    makeConnections();
    init();  // take the notes from notes manager and do the things on ui
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onNewNoteButtonClicked()
{

    noteManager.createNewNote();
}

void MainWindow::onRemoveButtonClicked()
{

    removeNote(ui->notesListWidget->currentNoteId());
}


void MainWindow::onNewNoteCreated(int id)
{

    addNoteToList(noteManager.note(id));
}


void MainWindow::onNoteContentChanged(int id)
{
    ui->notesListWidget->updateCurrentNote(noteManager.note(id));
}


void MainWindow::onSelectedNoteChanged(int id)
{
    auto* document = noteManager.noteDocument(id);
    if(document) {

        ui->textEdit->setDocument(document);
        auto cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::onRemoveNote(int id)
{
    removeNote(id);

}

void MainWindow::onRenameNote(int id, const QString &newTitle)
{

    noteManager.renameNote(id, newTitle);
    ui->notesListWidget->updateCurrentNote(noteManager.note(id));
}

void MainWindow::addNoteToList(const Note &note)
{
    ui->notesListWidget->addNote(note);
}

void MainWindow::removeNote(int id)
{
    QString noteTitle = noteManager.note(id).title;

    // display in msg box
    auto pressedButton = QMessageBox::information(this, "Remove note?",
                                                  QString("Are you sure you want to remove  %0?").arg(noteTitle),
                                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (pressedButton == QMessageBox::Yes) {
        // remove the note from ui, then backend
        // next line is a safety net:
        if(noteManager.count() == 1)  // only weird piece of code, if there's one document left, textEdit shouldn't access a document that is deleted.
            ui->textEdit->setDocument(nullptr);

        ui->notesListWidget->removeCurrentNote();
        noteManager.removeNote(id);
    }

}

void MainWindow::init() {

    auto notesList = noteManager.noteCollection();  // unordered_map
    std::sort(notesList.begin(), notesList.end(),
              [](const Note& left, const Note& right) {  // lambda, basic comparison function

                return left.lastModified < right.lastModified;

                });

    for (auto& note : notesList) {

        addNoteToList(note);
    }
}


void MainWindow::makeConnections()
{
    connect(ui->newButton, &QPushButton::clicked, this, &MainWindow::onNewNoteButtonClicked);
    connect(ui->delButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);

    connect(&noteManager, &NoteManager::newNoteCreated, this, &MainWindow::onNewNoteCreated);
    connect(&noteManager, &NoteManager::noteContentChanged, this, &MainWindow::onNoteContentChanged);

    connect(ui->notesListWidget, &NotesListWidget::selectedNoteChanged, this, &MainWindow::onSelectedNoteChanged);
    connect(ui->notesListWidget, &NotesListWidget::removeNote, this, &MainWindow::onRemoveNote);
    connect(ui->notesListWidget, &NotesListWidget::renameNote, this, &MainWindow::onRenameNote);
}
