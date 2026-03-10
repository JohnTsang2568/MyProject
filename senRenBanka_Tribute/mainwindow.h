#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include<QBrush>
#include<QFile>
#include<QString>
#include<QTextStream>
#include <QFont>
#include <QKeyEvent>
#include<QEvent>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

    Ui::MainWindow *ui;
    QGraphicsItem* EyeWidget;
    QGraphicsItem *BodyWidget;
    QLabel *textLabel;
    QLabel * bgLabel;
    QGraphicsScene* scene;
    QPushButton *expression_1;
    QPushButton *expression_2;
    QTimer * timer;
    QStringList allText;
    QString line;
    int line_idx;
    int char_idx;
    QMediaPlayer* player;
    QAudioOutput* output;


private slots:
    void appendNextChar();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void loadText();
    void startCurrentLine();
    void keyPressEvent(QKeyEvent * event);
    void showEvent (QShowEvent * event);
    void handleUI ();
};
#endif // MAINWINDOW_H
