#include "renamedialog.h"
#include "ui_renamedialog.h"

#include <QPushButton>

RenameDialog::RenameDialog(const QString& oldName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RenameDialog)
{
    ui->setupUi(this);

    connect(ui->newNameEdit, &QLineEdit::textChanged, this, &RenameDialog::onNewNameEdited);

    ui->newNameEdit->setText(oldName);
    ui->newNameEdit->setSelection(0, ui->newNameEdit->text().size());
}

RenameDialog::~RenameDialog()
{
    delete ui;
}

QString RenameDialog::newName()
{
    return ui->newNameEdit->text();

}

void RenameDialog::onNewNameEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(text.size() != 0);
}
