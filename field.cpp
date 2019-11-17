#include "field.h"

Field::Field(int fieldSize, int blockSize, int penSize) :
    mFieldSize(fieldSize), mBlockSize(blockSize), mPenSize(penSize)
{
    for (int i = 0; i < mFieldSize + 1; ++i)
    {
        mLines.push_back(QLine(0, mPenSize / 2 + (mBlockSize + mPenSize)* i,
                mFieldSize* mPenSize + mPenSize / 2 + mFieldSize * mBlockSize,
                            mPenSize / 2 + (mBlockSize + mPenSize)* i));

        mLines.push_back(QLine(mPenSize / 2 + (mBlockSize + mPenSize)* i, 0,
                        mPenSize / 2 + (mBlockSize + mPenSize)* i,
                            mFieldSize* mPenSize + mPenSize / 2 + mFieldSize * mBlockSize));
    }

    for (int i = 0; i < fieldSize; ++i)
    {
        for (int j = 0; j < fieldSize; ++j)
        {
            mBlocks.push_back(QRect(penSize + i * (penSize + blockSize),
                                    penSize + j * (penSize + blockSize), blockSize, blockSize));
        }
    }

    mPen.setWidth(mPenSize);
    mPen.setColor(Qt::gray);
    mColor = QColor(200, 200, 200);
}

int Field::lineNumber()
{
    return mLines.size();
}

QLine Field::line(int index)
{
    return mLines.at(index);
}

int Field::blockNumber()
{
    return mBlocks.size();
}

QRect Field::block(int index)
{
    return mBlocks.at(index);
}

QPen Field::pen()
{
    return mPen;
}

QColor Field::color()
{
    return mColor;
}

int Field::blockSize()
{
    return mBlockSize;
}

int Field::fieldSize()
{
    return mFieldSize;
}
