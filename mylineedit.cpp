#include <QMimeData>

#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void MyLineEdit::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->text().startsWith("file:///")) {
        e->accept();
    }
    else {
        e->ignore();
    }
}

void MyLineEdit::dropEvent(QDropEvent *e)
{
    this->setText(e->mimeData()->text().mid(QString("file:///").size()).replace("/","\\"));
}

