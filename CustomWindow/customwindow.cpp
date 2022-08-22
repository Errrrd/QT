#include "customwindow.h"
#include <QFontDatabase>

CustomWindow::CustomWindow(QWidget *parent) :
    QWidget(parent),
    customOpacity(0),
    hHead(40),
    margin(10), //граница под "тень"
    isLBMPressed(false),
    custom(false),
    isSliderMove(false),
    isDraggable(false),
    isResizeCW(false),
    isDrawMSelect(false),
    isOM(false),
    menuSelect(0)
{
    setCWFont();
    createButtons();
    createProperty();
    createAnim();
    initStdWindow();

    //толщина бордюра виндового окна
    defMarg = this->geometry().x()-this->pos().x();
    //толщина "шапки" без бордюров и границы активного окна
    defHead = this->geometry().y()-this->pos().y()-defMarg-1;

    startTimer(100);

    //qDebug()<<"created";
}

CustomWindow::~CustomWindow()
{

    anim->deleteLater();
    aboutAct->deleteLater();
    exitAct->deleteLater();
    fileMenu->deleteLater();
    delete winFont;
}
//-------END OF CONSTRUCTOR/DESTRUCTOR------------------------------------------

//-------INITIAL FUNCTIONS------------------------------------------------------
void CustomWindow::setCWFont()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/AlternateGotNo3D.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    winFont = new QFont(family, 13, QFont::Normal);
}

void CustomWindow::createButtons()
{
    //QString strColor = "background-color: "+ bgColor.name();

    closeCW = QPixmap(":/images/close.png");
    custom_icon = QPixmap(":/images/custom_icon.png");
    maximizeCW = QPixmap(":/images/maximize.png");
    minimizeCW = QPixmap(":/images/minimize.png");
    restoreCW = QPixmap(":/images/restore.png");

    aboutAct = new QAction(tr("About"), this);
    //aboutAct->setStatusTip(tr("About"));
    //connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutCW()));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void CustomWindow::createProperty()
{
    QString strColor = "background-color: ";

    resize(800,600);

    shadowEff = new QGraphicsDropShadowEffect;
    shadowEff->setBlurRadius(10.0);
    shadowEff->setColor(QColor(0, 0, 0, 160));
    shadowEff->setOffset(0.0);
    shadowEff->setEnabled(false);
    setGraphicsEffect(shadowEff);

    setMinimumWidth(512+2*margin);
    setMinimumHeight(400+hHead+2*margin);
    setWindowFlags(Qt :: FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    customBGColor = QColor(255,255,255);
    defaultBGColor = this->palette().background().color();
    bgColor = defaultBGColor;
    slBGColor = QColor(230,222,211,255);
    headColor = QColor(252, 250, 240, 0);
    lineColor = QColor(204,204,204,0);

    strColor += QColor(252, 250, 240, 255).name();

    fileMenu = new QMenu(this);
    fileMenu->setStyleSheet(strColor);
    fileMenu->addAction(aboutAct);
    fileMenu->addAction(exitAct);
    fileMenu->setFont(*winFont);
}

void CustomWindow::createAnim()
{
    anim = new QPropertyAnimation;
    connect(anim, SIGNAL(finished()), this, SLOT(changeStyle()));
    connect(anim, SIGNAL(valueChanged(QVariant)), this, SLOT(repaint()));
    connect(anim, SIGNAL(valueChanged(QVariant)), this, SLOT(changeColors()));
    anim->setTargetObject(this);
    anim->setPropertyName("pointCenter");
    anim->setDuration(1000);
    //anim->setEasingCurve(QEasingCurve::InOutExpo);
}

void CustomWindow::initStdWindow()
{
    int x = pos().x()+margin-defMarg;
    int y = pos().y()+hHead+margin-defHead-defMarg;

    setWindowFlags(Qt :: Window);
    if(x<0)
        x=0;
    if(y<0)
        y=0;
    if(custom) {
        resize(width()-2*margin, height()-hHead-2*margin);
        if(!isFullScreen()){
            move(x, y);
            show();
        } else {
            showFullScreen();
        }
    } else {
        show();
    }
    custom = false;
    this->setWindowTitle("Standart Window");
    pointGlobalPos = pos();
}

void CustomWindow::initCustomWindow()
{
    int x = pos().x()-margin;
    int y = pos().y()-hHead-margin-1;

    setWindowFlags(Qt :: FramelessWindowHint
                |  Qt :: WindowSystemMenuHint
                |  Qt :: WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
    if(x<0)
        x=0;
    if(y<0)
        y=0;
    resize(width()+2*margin, height()+hHead+2*margin);
    custom = true;
    if(isFullScreen())
    {
        showFullScreen();
    } else {
        move(x, y);
        show();
    }
}
//-------END OF INITIAL FUNCTIONS-----------------------------------------------

//-------SLOTS------------------------------------------------------------------
void CustomWindow::changeStyle()
{
    isSliderMove = false;
    if(custom) {
        shadowEff->setEnabled(false);
        initStdWindow();
        custom = false;
    } else {
        shadowEff->setEnabled(true);
        initCustomWindow();
        custom = true;
    }
    //custom = !custom;

    //qDebug()<<"work2";
}

void CustomWindow::changeColors()
{
    int dx = pointCenter.x() - pointStart.x();
    int r = defaultBGColor.red();
    int g = defaultBGColor.green();
    int b = defaultBGColor.blue();


    slBGColor.setRgb(230 - 84*dx/200, 222, 211 - 12*dx/20,255);
    bgColor.setRgb(r + (255-r)*dx/200,
                   g + (255-g)*dx/200,
                   b + (255-b)*dx/200, 255);
    //qDebug()<< " bg col ="<<bgColor;
    headColor.setRgb(252, 250, 240, 255*dx/200);
    lineColor.setRgb(204,204,204, 255*dx/200);
    customOpacity = float(dx)/200.0;
}
//------- END OF SLOTS ------------------------------------------------------------

//------- FUNCTIONS FOR ANIMATION -------------------------------------------------
QPoint CustomWindow::getPointCenter()
{
    return pointCenter;
}

void CustomWindow::setPointCenter(QPoint point)
{
    pointCenter = point;
}

void CustomWindow::startCWAnim()
{
    isSliderMove = true;
    anim->setStartValue(pointStart);
    anim->setEndValue(pointFinish);
    anim->setDirection(custom ? QPropertyAnimation::Backward : QPropertyAnimation::Forward);
    anim->start();

    //qDebug()<<"work";
}
//------- END FUNCTIONS FOR ANIMATION ---------------------------------------------

//------- EVENTS ------------------------------------------------------------------
/*
void CustomWindow::resizeEvent(QResizeEvent *event)
{
    //qDebug()<<"Resize Event"<<this->pos()<<this->geometry();
}
*/
void CustomWindow::timerEvent(QTimerEvent *event)
{
    if(isOM&&!isSliderMove) {
        menuSelect +=1;
        if(menuSelect > 50) {
            menuSelect = 0;
            isOM = false;
            fileMenu->hide();
        }
    }
}

void CustomWindow::mousePressEvent(QMouseEvent *event)
{
    if( (event->button()== Qt::LeftButton) ) {
        QPoint pPress = event->pos();

        isLBMPressed = true;
        if(custom) {
            pointGlobalPos = event->globalPos();
            if(isMenuCW(&pPress)) {
                isOM = true;
                fileMenu->setGeometry(pos().x()+margin+8, pos().y()+margin+hHead, fileMenu->width(),60);
                fileMenu->show();
                //qDebug()<<"menu Open";
            }

            if(isCloseCW(&pPress)) {
                close();
            }

            if(isMinCW(&pPress)) {
                showMinimized();
            }

            if(isMaxCW(&pPress)) {
                //toRestore = this->geometry();
                this->showFullScreen();
            }

            if(isRestoreCW(&pPress)) {
                //toRestore = this->geometry();
                showNormal();
            }

            isDraggable = isDragCW(&pPress);
            isResizeCW = isToResize(&pPress);
        }
        if(isSlider(&pPress)) {
            startCWAnim();
        }

        event->accept();
        //qDebug() << "mousePressEvent"<<pPress<<pos()<<"isOM = "<< isOM;
    }
}

void CustomWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button()==Qt::LeftButton ) {
        isLBMPressed = false;
        isDraggable = false;
        isResizeCW = false;

        event->accept();
        //qDebug() << "mouseReleaseEvent";
    }
}

void CustomWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isLBMPressed)
    {
        QPoint vShift = event->globalPos() - pointGlobalPos;

        if(isDraggable) {
            this->move(pos().x()+vShift.x(), pos().y()+vShift.y());
        }

        if(isResizeCW) {
            this->resize(width()+vShift.x(), height()+vShift.y());
        }
        pointGlobalPos = event->globalPos();
    }
    //qDebug() << "mouseMoveEvent";
    return;
}

void CustomWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(isFullScreen()) {
        margin = 0;
    } else {
        margin = 10;
    }
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(bgColor);
    painter.setBrush(bgColor);
    if(custom) {
        shadowEff->setEnabled(!isSliderMove); //не отрисовывает при включенной тени.Почему - не выяснил.
        drawWindow(&painter);
    } else {
        painter.drawRect(0, 0, width(), height());
    }
    drawSlider(&painter);

    //qDebug()<<"Paint Event";
}
//------- EVENTS ------------------------------------------------------------------

//-------------- DRAW FUNCTIONS ---------------------------------------------------
void CustomWindow::drawWindow(QPainter *painter)
{
    int dH = margin+(hHead-20)/2;

    //background
    painter->drawRect(margin, margin, width()-2*margin, height()-2*margin);

    //header
    painter->setOpacity(customOpacity);
    painter->setBrush(headColor);
    painter->setPen(headColor);
    painter->drawRect(margin, margin, width()-2*margin, hHead);
    painter->setPen(QPen(lineColor,1));
    painter->drawLine(margin, hHead+margin+1, width()-margin, hHead+margin+1);

    //buttons
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPoint(width()-25-margin, dH), closeCW);
    if(isFullScreen()) {
        painter->drawPixmap(QPoint(width()-45-margin, dH), restoreCW);
    } else {
        painter->drawPixmap(QPoint(width()-45-margin, dH), maximizeCW);
    }
    painter->drawPixmap(QPoint(width()-65-margin, dH), minimizeCW);
    //menu
    painter->drawPixmap(QPoint(margin+8, dH), custom_icon);

    //title
    painter->setPen  (Qt::black);
    painter->setFont(QFont("Times", 11, QFont::Normal));
    painter->drawText(QPoint(margin+35, margin+hHead/2+5), tr("Custom Window") );
    painter->setOpacity(1);
}

void CustomWindow::drawSlider(QPainter *painter)
{
    int rectY;
    QRect rect;

    if(custom) {
        rectY = (height()-hHead-2*margin)/5 + hHead + margin;
    } else {
        rectY = height()/5;
    }
    setRoundCentr();
    rect = QRect((width() - 460)/2, rectY, 460, 256);
    painter->setPen(slBGColor);
    painter->setBrush(QBrush(slBGColor, Qt::SolidPattern));
    painter->drawRoundRect(rect, 55,128);

    painter->setFont(*winFont);
    painter->setPen(Qt::white);
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawText(width()/2 + 100, rectY + 128, "OFF");
    painter->drawText(width()/2 - 100, rectY + 128, "ON");
    //Draw round of "slider":
    painter->drawEllipse(pointCenter, 120,120);

    painter->setOpacity(1);
    painter->setPen(qRgb(204,204,204));
    //painter->setBrush(QBrush(qRgb(204,204,204), Qt::SolidPattern));
    painter->drawText(width()/2 - 110, height()*3/5+132, tr("USE SLIDER TO SWITCH WINDOW STATES"));
    painter->setOpacity(customOpacity);
}
//-------------- END DRAW FUNCTIONS -----------------------------------------------

//-------------- CUSTOM CONTROL FUNCTIONS -----------------------------------------
void CustomWindow::setRoundCentr()
{
    if(custom) {
        pointStart = QPoint(width()/2 -100, (height()-hHead-2*margin)/5 + 128 + hHead+margin);
        pointFinish = QPoint(width()/2 +100, (height()-hHead-2*margin)/5 + 128 + hHead+margin);
        if(!isSliderMove)
            pointCenter = pointFinish;
    } else {
        pointStart = QPoint(width()/2 -100, height()/5 + 128);
        pointFinish = QPoint(width()/2 +100, height()/5 + 128);
        if(!isSliderMove)
            pointCenter = pointStart;
    }
}

bool CustomWindow::isMenuCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();
    int dW = margin+8;
    int dH = margin+(hHead-20)/2;

    return (x > dW)&&(x < dW+20)&&(y > dH)&&(y < dH+20);
}

bool CustomWindow::isCloseCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();
    int dH = margin+(hHead-20)/2;

    return (x > width()-25-margin)&&(x < width()-5-margin)&&(y > dH)&&(y < dH+20);
}

bool CustomWindow::isRestoreCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();
    int dH = margin+(hHead-20)/2;

    return (x > width()-45-margin)&&(x < width()-25-margin)&&(y > dH)&&(y < dH+20)&&isFullScreen();
}

bool CustomWindow::isMinCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();
    int dH = margin+(hHead-20)/2;

    return (x > width()-65-margin)&&(x < width()-45-margin)&&(y > dH)&&(y < dH+20);
}

bool CustomWindow::isMaxCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();
    int dH = margin+(hHead-20)/2;

    return (x > width()-45-margin)&&(x < width()-25-margin)&&(y > dH)&&(y < dH+20)&&(!isFullScreen());
}

bool CustomWindow::isDragCW(QPoint *point)
{
    int x = point->x();
    int y = point->y();

    //qDebug()<<"drag";
    return (x > margin+30)&&(x < width()-70-margin)&&(y > margin)&&(y < margin+hHead)&&(!isFullScreen());
}

bool CustomWindow::isToResize(QPoint *point)
{
    int x = point->x();
    int y = point->y();

    return (y > height()-25)&&(y <= height())&&(x > width()-25)&&(x <= width());
}

bool CustomWindow::isSlider(QPoint *point)
{
    int dx;
    int dy;

    dx = point->x() - pointCenter.x();
    dy = point->y() - pointCenter.y();

    return ((dx*dx + dy*dy) < 14000)&&!isSliderMove;
}

//-------------- END CUSTOM CONTROL FUNCTIONS -------------------------------------

//-------------- other -----------------------------------------
/*
void CustomWindow::focusInEvent(QFocusEvent *event)
{
    qDebug() << "focusInEvent";
}

void CustomWindow::focusOutEvent(QFocusEvent * event)
{
    qDebug() << "focusOutEvent";
}
/*
bool CustomWindow::eventFilter(QObject *object, QEvent *event)
{
    qDebug() << "Event ftr";
}
/*
void CustomWindow::showEvent(QShowEvent *event)
{
  Q_UNUSED(event);
    qDebug()<<"showEvent";
}


*/
