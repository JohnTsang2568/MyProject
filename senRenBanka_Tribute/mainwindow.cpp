#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainLayout = new QVBoxLayout (ui->centralwidget);
    textLayout= new  QHBoxLayout ();
    EyeWidget =new QGraphicsPixmapItem(QPixmap(":/new/prefix1/Image/Character/Marasame/EyeWidget/Smaller/Mareasame_a_0_1963.png"));
    BodyWidget= new QGraphicsPixmapItem(QPixmap(":/new/prefix1/Image/Character/Marasame/BodyWidegt/Masame_a_0_1950.png"));
    textLabel= new QLabel();
    scene = new QGraphicsScene (this);
    view= new QGraphicsView(scene);

    expression_1 = new QPushButton (this);
    expression_2 = new QPushButton (this);

    bgLabel = new QLabel(this);
    bgLabel->setPixmap(QPixmap(":/new/bgimage/Image/Scenery/street_to_school_morningA.png"));
    bgLabel->setScaledContents(true);
    bgLabel->setGeometry(rect());
    bgLabel->lower();

    //allocation of memory for existed class members

    BodyWidget->setZValue(0);
    EyeWidget ->setZValue(1);

    EyeWidget -> setScale(0.9);
    EyeWidget->setParentItem(BodyWidget);
    EyeWidget->setPos(290,140);

    //set parameters for class members
    textLayout->addWidget(expression_1);
    textLayout->addWidget(expression_2);
    textLayout->addWidget(textLabel);


    mainLayout->addWidget(view,1);
    mainLayout->addLayout(textLayout);

    mainLayout->setAlignment(textLayout,Qt::AlignBottom | Qt::AlignHCenter);
    scene->addItem(EyeWidget);
    scene->addItem(BodyWidget);

    scene->setSceneRect(scene->itemsBoundingRect());

    view->setStyleSheet("background: transparent;");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    view->installEventFilter(this);
    //construct layout

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (bgLabel)
        bgLabel->setGeometry(rect());
    if(view&&scene)
    {
        view->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    }
}
