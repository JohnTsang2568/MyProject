#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), line_idx(0), char_idx(0)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    output = new QAudioOutput (this);
    player->setAudioOutput(output);
    player->setSource(QUrl("qrc:/new/music/SenRenBanka/Audio/BGM/BGM61.wav"));
    player->setLoops(QMediaPlayer::Infinite);
    output->setVolume(0.6);
    player->play();

    textLabel= ui->label;
    scene=new QGraphicsScene();
    EyeWidget =new QGraphicsPixmapItem(QPixmap(":/new/prefix1/Image/Character/Marasame/EyeWidget/Smaller/Mareasame_a_0_1963.png"));
    BodyWidget= new QGraphicsPixmapItem(QPixmap(":/new/prefix1/Image/Character/Marasame/BodyWidegt/Masame_a_0_1950.png"));
     //allocation of memory for existed class members

    timer = new QTimer(this);
    timer->setInterval(50);
    connect(timer,&QTimer::timeout,this,&MainWindow::appendNextChar);

    bgLabel = new QLabel(this);
    bgLabel->setPixmap(QPixmap(":/new/bgimage/Image/Scenery/street_to_school_morningA.png"));
    bgLabel->setScaledContents(true);
    bgLabel->lower();

    //load bgLabel

    BodyWidget->setZValue(0);
    // BodyWidget->setScale(0.3);
    BodyWidget->setPos(500, 200);
    EyeWidget->setParentItem(BodyWidget);
    EyeWidget->setPos(785, 335);

    EyeWidget ->setZValue(1);

    EyeWidget -> setScale(0.9);
    EyeWidget->setParentItem(BodyWidget);

    scene->addItem(EyeWidget);
    scene->addItem(BodyWidget);

    //set widgets and add them to scene

    scene->setSceneRect(scene->itemsBoundingRect());

    //make sure items may not exceed sceneRect

    ui->view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->view->setScene(scene);
    ui->view->setStyleSheet("background: transparent;");
    ui->view->setInteractive(false);
    ui->view->setFocusPolicy(Qt::NoFocus);
    //construct view
    // qDebug() << ui -> view->viewport()->size();
    // qDebug() << scene->sceneRect().size();

    loadText();
    //load text
    if(!this->allText.empty())
    {
        this->line_idx=0;this->char_idx=0;
        startCurrentLine();
    }
    //print the first line of the text

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    handleUI();
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    if (this->line_idx>=this->allText.size()) {
        return;
    }
    timer->stop();
    ++this->line_idx;
    startCurrentLine();
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->key()==Qt::Key_Space)
    {
    if (this->line_idx>=this->allText.size()) {
        return;
    }
    timer->stop(); //stop timer for the last line
    ++this->line_idx; //get ready for the new line!
    startCurrentLine();
    }

    else
    {
       QMainWindow::keyPressEvent(event);
    }
}

//press space or click mouse to play next line
void MainWindow::loadText()
{
    QFile textFile(":/new/text/SenRenBanka/dialogue_only.txt");
    if(!textFile.open(QIODeviceBase::ReadOnly))
    {
        qDebug() << "Fail to load the text";
        return;
    }

    QString line; QTextStream text(&textFile);
    while(!text.atEnd())
    {
    line=text.readLine();

        if(!line.isEmpty())
    {
        this->allText.append(line);
    }
    }
    textFile.close();
}

//load class member allText with the textfile

void MainWindow::appendNextChar()
{
    if(this->line_idx>=allText.size())
    {
        timer->stop();
        return;
    }
    //stop timer and return if EOF

    QString currentLine= this->allText.at(line_idx);
    if(this->char_idx<currentLine.size())
    {
        QChar now=currentLine.at(char_idx);
        textLabel->setText(textLabel->text()+now);
        ++char_idx;
    }
    //append next char to the current text shown in the textLabel

    else timer->stop();
}

void MainWindow::startCurrentLine()
{
    if(this->line_idx>=this->allText.size())
    {
        timer->stop();
        return;
    }
     //stop timer and return if EOF

    this->char_idx=0;
    textLabel->clear();
    timer->start();
    //get ready for new line
}

void MainWindow::showEvent (QShowEvent * event)
{
    Q_UNUSED(event);
    handleUI();
}

void MainWindow::handleUI ()
{
    const int reservedHeight=156;
    const double ratio=reservedHeight*0.00166666;

    int w= ui->centralwidget->width();
    int h= ui->centralwidget->height();

    double h_now=h*ratio;
    double viewHeight=h-h_now;

    ui->view->setGeometry(0,0,w,h);
    this->textLabel->setGeometry(0,viewHeight,w,h_now);

    ui->view->viewport()->resize(ui->view->size());

    if(bgLabel)
    {
        bgLabel->setGeometry(rect());
    }

    if(ui->view && scene)
    {
        ui->view->fitInView(ui->view->scene()->sceneRect(),Qt::KeepAspectRatio);
    }

}
