#ifndef BLOCK_H
#define BLOCK_H
#include <QPoint>
#include <QRect>
#include <QColor>
#include <ctime>
#include <cstdlib>


class Block : public QPoint
{
private:
    const int mSize;
    int mNumber;
    const int mPenSize;
    QColor mColor;

public:
    Block(int x, int y, int size, int penSize);
    QColor color();
    int blockSize();
    int penSize();
    int numberX();
    int numberY();
    QString number();
    void setNumber(int n);
};

#endif // BLOCK_H
