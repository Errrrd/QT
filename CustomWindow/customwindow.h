#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
//#include <QDebug>

class CustomWindow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint pointCenter READ getPointCenter WRITE setPointCenter)
public:
    explicit CustomWindow(QWidget *parent = 0);
    ~CustomWindow();

private:
//--------events---------------------------------
    //virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *);
    //virtual void focusInEvent(QFocusEvent * event);
    //virtual void focusOutEvent(QFocusEvent *event);
    //virtual void showEvent(QShowEvent *event);
    //virtual bool eventFilter(QObject *object, QEvent *event);
//--------init------------------------------------
    void setCWFont();
    void createButtons();
    void createProperty();
    void createAnim();
    void initStdWindow();
    void initCustomWindow();
//-------draw-------------------------------------
    void drawWindow(QPainter *painter);
    void drawSlider(QPainter *painter);
//-------anim-------------------------------------
    void startCWAnim();
    QPoint getPointCenter();
    void setPointCenter(QPoint point);
//-------check------------------------------------
    void setRoundCentr();
    bool isMenuCW(QPoint *point);
    bool isCloseCW(QPoint *point);
    bool isRestoreCW(QPoint *point);
    bool isMinCW(QPoint *point);
    bool isMaxCW(QPoint *point);
    bool isDragCW(QPoint *point);
    bool isToResize(QPoint *point);
    bool isSlider(QPoint *point);


    QGraphicsDropShadowEffect *shadowEff;
    QFont *winFont;
    QMenu *fileMenu;
    QAction *aboutAct;
    QAction *exitAct;
    QPixmap closeCW;
    QPixmap custom_icon;
    QPixmap maximizeCW;
    QPixmap minimizeCW;
    QPixmap restoreCW;
    //QRect toRestore;
    QColor defaultBGColor;
    QColor customBGColor;
    QColor defaultSlBGColor;
    QColor customSlBGColor;
    QColor defaultHeadColor;
    QColor customHeadColor;
    QColor customLineColor;
    QPoint pointStart;
    QPoint pointFinish;
    QPoint pointGlobalPos;
    QPropertyAnimation *anim;
    //for anim
    QPoint pointCenter;
    QColor slBGColor;
    QColor bgColor;
    QColor headColor;
    QColor lineColor;
    qreal customOpacity;
    int defHead;
    int defMarg;
    int hHead;
    int margin;
    int menuSelect;
    bool isLBMPressed;
    bool custom;
    bool isSliderMove;
    bool isDraggable;
    bool isResizeCW;
    bool isOM;
    bool isDrawMSelect;

private slots:
    void changeStyle();
    void changeColors();

};

#endif // CUSTOMWINDOW_H
