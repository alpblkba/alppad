#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QRegularExpression>

namespace Ui {
class FindReplaceDialog;
}

class FindReplaceDialog : public QDialog {
    Q_OBJECT

public:
    explicit FindReplaceDialog(QTextEdit* editor, QWidget* parent = nullptr);
    ~FindReplaceDialog();

private slots:
    void onFindNext();
    void onFindPrevious();
    void onReplace();
    void onReplaceAll();

private:
    Ui::FindReplaceDialog* ui;
    QTextEdit* m_editor;

    QTextDocument::FindFlags findFlags() const;
    bool findNextInternal(bool backward = false);


};

