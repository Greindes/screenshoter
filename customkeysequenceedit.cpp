#include "customkeysequenceedit.h"
#include <QKeyEvent>

CustomKeySequenceEdit::CustomKeySequenceEdit(QWidget *parent)
    : QKeySequenceEdit(parent)
{

}

CustomKeySequenceEdit::~CustomKeySequenceEdit()
{

}

void CustomKeySequenceEdit::keyPressEvent(QKeyEvent *pEvent)
{
    //QKeySequence seq();
    setKeySequence(keySequence()[0]);
    QKeySequenceEdit::keyPressEvent(pEvent);
}
