#pragma once

#include <QWidget>

class QLabel;
class QPoint;

struct Note;

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(const Note& note, QWidget *parent = nullptr);

    int noteId();
    void updateContent(const Note& note);

signals:
    void removeNote(int id);
    void renameNote(int id, const QString& newTitle);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;


private:
    void setupGui();
    void updateLabels();

    void setElidedText(QLabel* label, const QString& pos);
    void showContextMenu(const QPoint& pos);
    void onRemoveActionTriggered();
    void onRenameActionTriggered();

private:
    QLabel* titleLabel;
    QLabel* lastModifiedLabel;

    int id;
    QString title;
    QString lastModified;

    const QString dateTimeFormat = "dd/mm/yyyy - hh:mm:ss";
};


