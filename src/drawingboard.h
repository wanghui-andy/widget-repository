#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>

class DrawingBoard : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DrawingBoard(QWidget *parent = nullptr);
    ~DrawingBoard();

protected:
    // Event handlers
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QPoint m_start_pos;
    QPoint m_end_pos;
    bool m_prepare_paint = false;
    bool m_need_paint = false;

    enum ShapeType
    {
        typeRectangle,
        typePloygon,
    };
    ShapeType m_shape_type = typePloygon;

    struct Line
    {
        Line() {}
        Line(QPoint begin, QPoint end) : begin_point(begin), end_point(end) {}
        QPoint begin_point;
        QPoint end_point;
    };
    std::vector<Line> m_lines;
};

#endif  // DRAWINGBOARD_H
