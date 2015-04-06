#pragma once

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
public:
    MyLineEdit(QWidget *parent = 0);
    ~MyLineEdit()
    {}

protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
};
