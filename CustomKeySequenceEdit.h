#ifndef CUSTOMKEYSEQUENCEEDIT_H
#define CUSTOMKEYSEQUENCEEDIT_H

#include <QKeySequenceEdit>

class QKeyEvent;

//потомок QKeySequenceEdit, ограничивающий размер последовательности хоткеев до одного
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
