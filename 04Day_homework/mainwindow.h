#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>

#include <QMainWindow>
#include <gamadata.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendClicked();

private:
    Ui::MainWindow *ui;
    QPushButton * buttons[ROWS][COLS];

};

#endif // MAINWINDOW_H
