#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class NoteManager;
class FindReplaceDialog;
struct Note;
// main window take the NoteManager by reference, and store a reference to a NoteManager as a member, we'll take it by reference in a constructor

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(NoteManager& manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // handle signal from ui
    void onNewNoteButtonClicked();
    void onRemoveButtonClicked();

    // handle NoteManager signals
    void onNewNoteCreated(int id);
    void onNoteContentChanged(int id);

    // handle NotesListWidget signals
    void onSelectedNoteChanged(int id);
    void onRemoveNote(int id);
    void onRenameNote(int id, const QString& newTitle);

    //handle FindReplaceDialog signals
    void onFindReplaceDialog();


private:
    void addNoteToList(const Note& note);
    void removeNote(int id);

    void init();
    void makeConnections();
    void setupShortcuts();


    Ui::MainWindow *ui;
    NoteManager& noteManager;
    FindReplaceDialog* m_findDialog;



};
#endif // MAINWINDOW_H
