#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPicture>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QTimer>

#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    void createButtons();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    bool saveFileInFolder(const QByteArray &fileFormat);
    ScribbleArea *scribbleArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *saveMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *saveAct;
    bool firstExecute;

    zmq::context_t context;
    zmq::socket_t socket;
};

#endif
