#ifndef CUSTOMKEYSEQUENCEEDIT_H
#define CUSTOMKEYSEQUENCEEDIT_H

#include <QKeySequenceEdit>

class QKeyEvent;

class CustomKeySequenceEdit : public QKeySequenceEdit
{
    Q_OBJECT

public:
    explicit CustomKeySequenceEdit(QWidget *parent = nullptr);
    ~CustomKeySequenceEdit();

protected:
    void keyPressEvent(QKeyEvent *pEvent);
};

#endif // CUSTOMKEYSEQUENCEEDIT_H
