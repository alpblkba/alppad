#include "notewidget.h"
#include "note.h"
#include "renamedialog.h"


#include <QLabel>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QMenu>

NoteWidget::NoteWidget(const Note &note, QWidget *parent) : QWidget(parent)
{
    setupGui();

    id = note.id;
    title = note.title;
    lastModified = note.lastModified.toString(dateTimeFormat);

    updateLabels();
    setToolTip(QString("0\n%1").arg(title, lastModified));

}

int NoteWidget::noteId()
{
    return id;
}

void NoteWidget::updateContent(const Note &note)
{
    title = note.title;
    lastModified = note.lastModified.toString(dateTimeFormat);

    updateLabels();
    setToolTip(QString("0\n%1").arg(title, lastModified));
}

void NoteWidget::resizeEvent(QResizeEvent *event)
{

    updateLabels();
    QWidget::resizeEvent(event);
}

void NoteWidget::contextMenuEvent(QContextMenuEvent *event)
{

    showContextMenu(event->globalPos());
}

void NoteWidget::setupGui()
{

    titleLabel = new QLabel();
    lastModifiedLabel = new QLabel();

    auto layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(lastModifiedLabel);
}

void NoteWidget::updateLabels()
{

    setElidedText(titleLabel, title);
    setElidedText(lastModifiedLabel, lastModified);
}


void NoteWidget::setElidedText(QLabel *label, const QString &text)
{
    auto parentObj = parent();
    if (parentObj) {

        auto parentWidget = qobject_cast<QWidget*>(parentObj);  // similar to dynamic cast, returns a nullptr if parentobj is not QWidget
        if (parentWidget) {

            QFontMetrics fm(label->font());  // class for how much place is needed for font to render
            QString elidedText = fm.elidedText(text, Qt::ElideRight, parentWidget->width() - 20);
            label->setText(elidedText);
        }
    }
}

void NoteWidget::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(this);


    QAction* renameAction = contextMenu.addAction("Rename Note");

    renameAction->setIcon(QIcon(":/icons/rename.svg"));
    connect(renameAction, &QAction::triggered, this, &NoteWidget::onRenameActionTriggered);

    QAction* removeAction = contextMenu.addAction("Remove Note");
    removeAction->setIcon(QIcon(":/icons/delete.svg"));
    connect(removeAction, &QAction::triggered, this, &NoteWidget::onRemoveActionTriggered);

    contextMenu.exec(pos);
}


void NoteWidget::onRemoveActionTriggered()
{

    emit removeNote(id);
}

void NoteWidget::onRenameActionTriggered()
{
    RenameDialog renameDialog(title, this);
    if(renameDialog.exec() == QDialog::Accepted) { // exec is the functon that starts the main loop of the dialog and returns the state of dialog

        emit renameNote(id, renameDialog.newName());
    }

}

