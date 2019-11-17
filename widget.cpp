#include "widget.h"

Widget::Widget()
{
    srand(time(0));
    const int blockNumber = 4;
    const int blockSize = 180;
    const int penSize = 4;
    this->setFixedSize(blockNumber * blockSize + penSize * (blockNumber + 1),
                       blockNumber * blockSize + penSize * (blockNumber + 1));

    mField = new Field(blockNumber, blockSize, penSize);
    mExampleBlock = new Block(0, 0, blockSize, penSize);

    addBlock();
    addBlock();
}

Widget::~Widget()
{
    delete mField;
    delete mExampleBlock;

    while (mBlocks.size() > 0)
    {
        Block *b = mBlocks.back();
        delete b;
        mBlocks.pop_back();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(mField->pen());
    for (int i = 0; i < mField->lineNumber(); ++i)
    {
        painter.drawLine(mField->line(i));
    }

    painter.setBrush(mField->color());
    for (int i = 0; i < mField->blockNumber(); ++i)
    {
        painter.drawRect(mField->block(i));
    }

    painter.setPen(QPen(mBlocks.front()->color(), 1));
    painter.setFont(QFont("Times", 20));
    for (int i = 0; i < mBlocks.size(); ++i)
    {
        painter.setBrush(mBlocks.front()->color());
        painter.drawRect(mBlocks.at(i)->x(), mBlocks.at(i)->y(),
                         mBlocks.at(i)->blockSize(), mBlocks.at(i)->blockSize());
        painter.setPen(QPen(Qt::black));
        painter.drawText(mBlocks.at(i)->numberX(), mBlocks.at(i)->numberY(),
            mBlocks.at(i)->number());

    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_8)
    {
        QVector<Block*> temp;
        for (int i = 0; i < mBlocks.size(); ++i)
        {
            temp.push_back(new Block(mBlocks.at(i)->x(), mBlocks.at(i)->y(),
                                     mBlocks.at(i)->blockSize(), mBlocks.at(i)->penSize()));
        }

        for (int i = 0; i < mField->blockNumber(); ++i)
        {
            bool flag = false;
            int index = -1;
            for (int j = 0; j < mBlocks.size(); ++j)
            {
                if (mField->block(i).x() == mBlocks.at(j)->x() &&
                        mField->block(i).y() == mBlocks.at(j)->y())
                {
                    flag = true;
                    index = j;
                    break;
                }
            }

            if (flag)
            {
                int y = mField->block(i).y();
                while (flag)
                {
                    y = y - (mField->blockSize() + mField->pen().width());
                    if (y < 0)
                    {
                        flag = false;
                        break;
                    }
                    for (int j = 0; j < mBlocks.size(); ++j)
                    {
                        if (mBlocks.at(j)->y() == y &&
                                mBlocks.at(j)->x() == mField->block(i).x())
                        {
                            /////
                            int ind = -1;
                            for (int k = 0; k < mBlocks.size(); ++k)
                            {
                                if (mBlocks.at(k)->x() == mField->block(i).x() &&
                                        mBlocks.at(k)->y() == y)
                                {
                                    ind = k;
                                    break;
                                }
                            }

                            if (ind != -1)
                            {
                                if (mBlocks.at(index)->number() == mBlocks.at(ind)->number())
                                {
                                    mBlocks.at(index)->setNumber(mBlocks.at(index)->number().toInt() * 2);
                                    mBlocks.at(index)->setY(y);
                                    mBlocks.erase(mBlocks.begin() + ind);
                                }
                            }
                            /////
                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        mBlocks.at(index)->setY(y);
                    }
                }
            }
        }

        if (needToAddBlock(temp))
            addBlock();
    }
    else
    if (event->key() == Qt::Key_2)
    {
        QVector<Block*> temp;
        for (int i = 0; i < mBlocks.size(); ++i)
        {
            temp.push_back(new Block(mBlocks.at(i)->x(), mBlocks.at(i)->y(),
                                     mBlocks.at(i)->blockSize(), mBlocks.at(i)->penSize()));
        }

        for (int i = mField->blockNumber() - 1; i >= 0; --i)
        {
            bool flag = false;
            int index = -1;
            for (int j = 0; j < mBlocks.size(); ++j)
            {
                if (mField->block(i).x() == mBlocks.at(j)->x() &&
                        mField->block(i).y() == mBlocks.at(j)->y())
                {
                    flag = true;
                    index = j;
                    break;
                }
            }

            if (flag)
            {
                int y = mField->block(i).y();
                while (flag)
                {
                    y = y + mField->blockSize() + mField->pen().width();
                    if (y > mField->fieldSize() * mField->blockSize() +
                            mField->fieldSize() * mField->pen().width())
                    {
                        break;
                    }
                    for (int j = 0; j < mBlocks.size(); ++j)
                    {
                        if (mBlocks.at(j)->y() == y &&
                                mBlocks.at(j)->x() == mField->block(i).x())
                        {
                            int ind = -1;
                            for (int k = 0; k < mBlocks.size(); ++k)
                            {
                                if (mBlocks.at(k)->x() == mField->block(i).x() &&
                                        mBlocks.at(k)->y() == y)
                                {
                                    ind = k;
                                    break;
                                }
                            }

                            if (ind != -1)
                            {
                                if (mBlocks.at(index)->number() == mBlocks.at(ind)->number())
                                {
                                    mBlocks.at(index)->setNumber(mBlocks.at(index)->number().toInt() * 2);
                                    mBlocks.at(index)->setY(y);
                                    mBlocks.erase(mBlocks.begin() + ind);
                                }
                            }

                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        mBlocks.at(index)->setY(y);
                    }
                }
            }
        }

        if (needToAddBlock(temp))
            addBlock();
    }
    else
    if (event->key() == Qt::Key_6)
    {
        QVector<Block*> temp;
        for (int i = 0; i < mBlocks.size(); ++i)
        {
            temp.push_back(new Block(mBlocks.at(i)->x(), mBlocks.at(i)->y(),
                                     mBlocks.at(i)->blockSize(), mBlocks.at(i)->penSize()));
        }

        for (int i = mField->blockNumber() - 1; i >= 0; --i)
        {
            bool flag = false;
            int index = -1;
            for (int j = 0; j < mBlocks.size(); ++j)
            {
                if (mField->block(i).x() == mBlocks.at(j)->x() &&
                        mField->block(i).y() == mBlocks.at(j)->y())
                {
                    flag = true;
                    index = j;
                    break;
                }
            }

            if (flag)
            {
                int x = mField->block(i).x();
                while (flag)
                {
                    x = x + mField->blockSize() + mField->pen().width();
                    if (x > mField->fieldSize() * mField->blockSize() +
                            mField->fieldSize() * mField->pen().width())
                    {
                        break;
                    }
                    for (int j = 0; j < mBlocks.size(); ++j)
                    {
                        if (mBlocks.at(j)->x() == x &&
                                mBlocks.at(j)->y() == mField->block(i).y())
                        {                            
                            int ind = -1;
                            for (int k = 0; k < mBlocks.size(); ++k)
                            {
                                if (mBlocks.at(k)->x() == x &&
                                        mBlocks.at(k)->y() == mField->block(i).y())
                                {
                                    ind = k;
                                    break;
                                }
                            }

                            if (ind != -1)
                            {
                                if (mBlocks.at(index)->number() == mBlocks.at(ind)->number())
                                {
                                    mBlocks.at(index)->setNumber(mBlocks.at(index)->number().toInt() * 2);
                                    mBlocks.at(index)->setX(x);
                                    mBlocks.erase(mBlocks.begin() + ind);
                                }
                            }

                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        mBlocks.at(index)->setX(x);
                    }
                }
            }
        }

        if (needToAddBlock(temp))
            addBlock();
    }
    else
    if (event->key() == Qt::Key_4)
    {
        QVector<Block*> temp;
        for (int i = 0; i < mBlocks.size(); ++i)
        {
            temp.push_back(new Block(mBlocks.at(i)->x(), mBlocks.at(i)->y(),
                                     mBlocks.at(i)->blockSize(), mBlocks.at(i)->penSize()));
        }

        for (int i = 0; i < mField->blockNumber(); ++i)
        {
            bool flag = false;
            int index = -1;
            for (int j = 0; j < mBlocks.size(); ++j)
            {
                if (mField->block(i).x() == mBlocks.at(j)->x() &&
                        mField->block(i).y() == mBlocks.at(j)->y())
                {
                    flag = true;
                    index = j;
                    break;
                }
            }

            if (flag)
            {
                int x = mField->block(i).x();
                while (flag)
                {
                    x = x - (mField->blockSize() + mField->pen().width());
                    if (x < 0)
                    {
                        break;
                    }
                    for (int j = 0; j < mBlocks.size(); ++j)
                    {
                        if (mBlocks.at(j)->x() == x &&
                                mBlocks.at(j)->y() == mField->block(i).y())
                        {
                            int ind = -1;
                            for (int k = 0; k < mBlocks.size(); ++k)
                            {
                                if (mBlocks.at(k)->x() == x &&
                                        mBlocks.at(k)->y() == mField->block(i).y())
                                {
                                    ind = k;
                                    break;
                                }
                            }

                            if (ind != -1)
                            {
                                if (mBlocks.at(index)->number() == mBlocks.at(ind)->number())
                                {
                                    mBlocks.at(index)->setNumber(mBlocks.at(index)->number().toInt() * 2);
                                    mBlocks.at(index)->setX(x);
                                    mBlocks.erase(mBlocks.begin() + ind);
                                }
                            }

                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        mBlocks.at(index)->setX(x);
                    }
                }
            }
        }

        if (needToAddBlock(temp))
            addBlock();
    }
    else
    if (event->key() == Qt::Key_Space)
    {
        addBlock();
    }

    this->update();
}

void Widget::addBlock()
{
    if (mField->blockNumber() == mBlocks.size())
        this->close();

    while (true)
    {
        bool flag = true;
        int index = rand() % mField->blockNumber();
        for (int i = 0; i < mBlocks.size(); ++i)
        {
            if (mField->block(index).x() == mBlocks.at(i)->x() &&
                    mField->block(index).y() == mBlocks.at(i)->y())
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            mBlocks.push_back(new Block(mField->block(index).x(), mField->block(index).y(),
                              mExampleBlock->blockSize(), mExampleBlock->penSize()));
            return;
        }
    }
}

bool Widget::needToAddBlock(QVector<Block *> temp)
{
    if (mBlocks.size() != temp.size())
    {
        deleteTempVector(temp);
        return true;
    }

    for (int i = 0; i < temp.size(); ++i)
    {
        if (mBlocks.at(i)->x() == temp.at(i)->x() && mBlocks.at(i)->y() == temp.at(i)->y());
        else
        {
            deleteTempVector(temp);
            return true;
        }
    }

    deleteTempVector(temp);
    return false;
}

void Widget::deleteTempVector(QVector<Block *> temp)
{
    while (temp.size() > 0)
    {
        Block *b = temp.back();
        delete b;
        temp.pop_back();
    }
}
