#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QTextEdit* editor, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::FindReplaceDialog),
    m_editor(editor)
{
    ui->setupUi(this);
    ui->findEdit->setFocus();


    connect(ui->findNextBtn, &QPushButton::clicked,
            this, &FindReplaceDialog::onFindNext);

    connect(ui->findPrevBtn, &QPushButton::clicked,
            this, &FindReplaceDialog::onFindPrevious);

    connect(ui->replaceBtn, &QPushButton::clicked,
            this, &FindReplaceDialog::onReplace);

    connect(ui->replaceAllBtn, &QPushButton::clicked,
            this, &FindReplaceDialog::onReplaceAll);

    ui->findEdit->selectAll();


}

QTextDocument::FindFlags FindReplaceDialog::findFlags() const {
    QTextDocument::FindFlags flags;

    if (ui->caseSensitiveChk->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    return flags;
}

bool FindReplaceDialog::findNextInternal(bool backward) {
    QTextDocument::FindFlags flags = findFlags();
    if (backward)
        flags |= QTextDocument::FindBackward;

    const QString pattern = ui->findEdit->text();

    if (pattern.isEmpty())
        return false;

    bool found = false;

    if (ui->regexChk->isChecked()) {
        QRegularExpression regex(pattern);

        if (!regex.isValid())
            return false;

        found = m_editor->find(regex, flags);
    } else {
        found = m_editor->find(pattern, flags);
    }

    // wrap-around behavior
    if (!found) {
        m_editor->moveCursor(backward ? QTextCursor::End
                                      : QTextCursor::Start);

        if (ui->regexChk->isChecked()) {
            QRegularExpression regex(pattern);
            if (!regex.isValid())
                return false;

            found = m_editor->find(regex, flags);
        } else {
            found = m_editor->find(pattern, flags);
        }
    }

    return found;
}

void FindReplaceDialog::onFindNext() {
    findNextInternal(false);
}

void FindReplaceDialog::onFindPrevious() {
    findNextInternal(true);
}

// qt does NOT auto-expand regex capture groups ($1, $2) in replace. this matches notepad behaviour
void FindReplaceDialog::onReplace() {
    QTextCursor cursor = m_editor->textCursor();

    if (!cursor.hasSelection())
        return;

    cursor.insertText(ui->replaceEdit->text());
    m_editor->setTextCursor(cursor);

    onFindNext();
}

void FindReplaceDialog::onReplaceAll() {
    const QString pattern = ui->findEdit->text();
    if (pattern.isEmpty())
        return;

    QTextCursor cursor(m_editor->document());
    cursor.beginEditBlock();

    cursor.movePosition(QTextCursor::Start);
    m_editor->setTextCursor(cursor);

    QTextDocument::FindFlags flags = findFlags();

    while (true) {
        bool found = false;

        if (ui->regexChk->isChecked()) {
            QRegularExpression regex(pattern);
            if (!regex.isValid())
                break;

            found = m_editor->find(regex, flags);
        } else {
            found = m_editor->find(pattern, flags);
        }

        if (!found)
            break;

        QTextCursor c = m_editor->textCursor();
        c.insertText(ui->replaceEdit->text());
    }

    cursor.endEditBlock();
}




FindReplaceDialog::~FindReplaceDialog() {
    delete ui;
}
