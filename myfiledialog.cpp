#include "myfiledialog.h"

MyFileDialog::MyFileDialog(QWidget *parent) :
    QFileDialog(parent)
{
}

void MyFileDialog::accept()
{
    emit fileSelected(this->selectedFiles()[0]);
    QDialog::accept();
}
