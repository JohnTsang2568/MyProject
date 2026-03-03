#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    QVBoxLayout *mainLayout;
    QHBoxLayout *textLayout;
    QGraphicsItem* EyeWidget;
    QGraphicsItem *BodyWidget;
    QLabel *textLabel;
    QLabel * bgLabel;
    QGraphicsScene* scene;
    QGraphicsView *view;
    QPushButton *expression_1;
    QPushButton *expression_2;


protected:
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
