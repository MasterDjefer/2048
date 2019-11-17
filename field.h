#ifndef FIELD_H
#define FIELD_H
#include <QVector>
#include <QLine>
#include <QRect>
#include <QPen>
#include <QColor>

class Field
{
private:
    const int mFieldSize;
    const int mBlockSize;
    const int mPenSize;

    QPen mPen;
    QColor mColor;
    QVector<QLine> mLines;
    QVector<QRect> mBlocks;

public:
    Field(int fieldSize, int blockSize, int penSize);
    int lineNumber();
    QLine line(int index);
    int blockNumber();
    QRect block(int index);
    QPen pen();
    QColor color();
    int blockSize();
    int fieldSize();
};

#endif // FIELD_H
