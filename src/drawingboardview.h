#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include "drawingboardscene.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>

class DrawingBoardView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DrawingBoardView(QWidget *parent = nullptr);
    ~DrawingBoardView();

public:
    void setShapeType(DrawingBoardScene::ShapeType type)
    {
        // m_scene->setShapeType(type);
    }

    void loadSvgFile(const QString &file_name);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void zoomBy(qreal factor);
    qreal zoomFactor() const;

private:
    QGraphicsScene *m_scene;
};

#endif  // DRAWINGBOARD_H
