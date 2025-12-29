#include "noteslistwidget.h"
#include "ui_noteslistwidget.h"
#include "notewidget.h"
#include "note.h"

NotesListWidget::NotesListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotesListWidget)
{
    ui->setupUi(this);

    connect(ui->noteList, &QListWidget::itemSelectionChanged, this, &NotesListWidget::itemSelectionChanged);
}

NotesListWidget::~NotesListWidget()
{
    delete ui;
}

void NotesListWidget::addNote(const Note &note)
{

    auto* item = new QListWidgetItem();
    ui->noteList->insertItem(0, item);

    setupNoteItem(note, item);
}

void NotesListWidget::removeCurrentNote() {

    auto* currentItem = ui->noteList->currentItem();
    if(currentItem != nullptr) {
        delete currentItem;
    }


}

void NotesListWidget::updateCurrentNote(const Note &note) {

    if(ui->noteList->currentRow() != 0) {
        moveCurrentItemtoTop(note);
    }
    else {

        auto widget = static_cast<NoteWidget*>(ui->noteList->itemWidget(ui->noteList->currentItem()));
        widget->updateContent(note);
    }

}

int NotesListWidget::currentNoteId() {

    auto* currentItem = ui->noteList->currentItem();
    int noteId = static_cast<NoteWidget*>(ui->noteList->itemWidget(currentItem))->noteId();
    return noteId;
}

void NotesListWidget::itemSelectionChanged() {

    auto* currentItem = ui->noteList->currentItem();
    if (currentItem) {

        int id = currentNoteId();

        emit selectedNoteChanged(id);
    }


}

void NotesListWidget::moveCurrentItemtoTop(const Note &note) {  // bc of the limitation of QListWidget, we can't move an item to top.
    // we basically remove the item and insert it back
    // the selection will change and will emit the signal back

    blockSignals(true);
    // we shouldn't return anything or throw exceptions between these two blockSignals

    auto* item = ui->noteList->takeItem(ui->noteList->currentRow());

    ui->noteList->insertItem(0, item);
    setupNoteItem(note, item);

    //
    blockSignals(false);

}

void NotesListWidget::setupNoteItem(const Note &note, QListWidgetItem *item) {

    NoteWidget* widget = new NoteWidget(note);
    connect(widget, &NoteWidget::removeNote, this, &NotesListWidget::removeNote);
    connect(widget, &NoteWidget::renameNote, this, &NotesListWidget::renameNote);

    item->setSizeHint(widget->sizeHint());
    ui->noteList->setItemWidget(item, widget);

    ui->noteList->setCurrentItem(item);
}
