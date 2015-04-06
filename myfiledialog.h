#pragma once

#include <QFileDialog>

class MyFileDialog : public QFileDialog
{
public:
    MyFileDialog(QWidget *parent = 0);
    ~MyFileDialog()
    {}
protected:
    virtual void accept();
};
