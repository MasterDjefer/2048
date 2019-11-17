#ifndef WIDGET_H
#define WIDGET_H
#include "field.h"
#include "block.h"
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <ctime>
#include <cstdlib>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    Field *mField;
    QVector<Block*> mBlocks;
    Block *mExampleBlock;

private:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void addBlock();
    bool needToAddBlock(QVector<Block *> temp);
    void deleteTempVector(QVector<Block *> temp);

private slots:
};

#endif // WIDGET_H
