#include "block.h"

Block::Block(int x, int y, int size, int penSize) : QPoint(x, y), mSize(size), mPenSize(penSize)
{
    if ((rand() % 100 + 1) <= 75)
    {
        mNumber = 2;
    }
    else
    {
        mNumber = 4;
    }

    mColor = QColor(220, 220, 220);
}


QColor Block::color()
{
    return mColor;
}

int Block::blockSize()
{
    return mSize;
}

int Block::penSize()
{
    return mPenSize;
}

int Block::numberX()
{
    return x() + mSize / 2;
}

int Block::numberY()
{
    return y() + mSize / 2;
}

QString Block::number()
{
    return QString::number(mNumber);
}

void Block::setNumber(int n)
{
    mNumber = n;
}
