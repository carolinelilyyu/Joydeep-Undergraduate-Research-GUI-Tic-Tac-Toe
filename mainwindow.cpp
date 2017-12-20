#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scribblearea.h"



MainWindow::MainWindow()
    :context(1),
     socket(context, ZMQ_REP)
{
    firstExecute = true;
    std::cout<<"initialized the socket"<<std::endl;
    socket.bind("tcp://127.0.0.1:5555");

    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);


    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    scribbleArea->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(500, 500);
}

//if saved, can exit. otherwise, won't do anything
void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::open(){
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if(!fileName.isEmpty()){
            qDebug()<<"reached open";
            qDebug()<<fileName;
            scribbleArea->openImage(fileName);
        }
    }
}
//runs when Save As button is chosen, and then choose an entry from the format menu. First thing we need to do is find out which action sent the signal using
//qobject sender, which returns the sender as an qobject pointer
void MainWindow::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFileInFolder("png");


    /*
        for some reason, the program hangs when I try to run the system execute through C++
    */

//    if(firstExecute == true){
//        system("/Users/carolineyu/anaconda/bin/python /Users/carolineyu/Documents/school/Undergraduate\\ Research/XO_Classifier/pytorch_predict.py --f /Users/carolineyu/Documents/school/Undergraduate\\ Research/XO_Classifier/board/");
//    }else{
//          std::cout << "hi"<<std::endl;
//    }
//    firstExecute = false;

    std::cout << "now i must wait for python"<<std::endl;


    zmq::message_t request;
    std::cout<<"got the request back"<<std::endl;
    //wait for next request from client/Python
    socket.recv(&request);
    std::string msg_str(static_cast<char*>(request.data()), request.size());
    std::cout<<"testing5"<<std::endl;

    std::cout << "Received message from Python" <<std::endl;
    std::cout<<"testing6"<<std::endl;
    QString str = QString::fromUtf8(msg_str.c_str());

    //std::cout<<str<<std::endl;
    qDebug()<<str;
    QString filename = ("game" + str);
    QString path = "/Users/carolineyu/Documents/school/Undergraduate Research/XO_Classifier";
    QString dir = path + "/board/" + filename + ".png";
    int num = str.toInt();
    qDebug()<<"this is the square it should be in";
    qDebug()<<num;
    scribbleArea->openOverlayImage(dir, num);

    //do some work/code to draw
    sleep(1);
    //draw
    //as soon as saveAct is activated
    //save current image after drawing it
    //send reply back to client/Python
    std::cout<<"sending reply back to Python"<<std::endl;
    zmq::message_t reply(5); //length of message
    memcpy(reply.data(), "Enter", 5);
    socket.send(reply);


}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

void MainWindow::penWidth(){
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width"), scribbleArea->penWidth(), 1, 50, 1, &ok);
    if(ok)
        scribbleArea->setPenWidth(newWidth);
}

//slot to create messagebox describing what example is showing
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
            tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
               "base widget for an application, and how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}

//actions representing menu entries and connect them to appropriate slots
void MainWindow::createActions(){

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    //connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);


    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}


//check if any unsaved edits, gives message to see if want to save or not
bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

//pop up file dialog with a file name suggestion. the static getsavefilename returns file name selected by user
bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {


        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}

bool MainWindow::saveFileInFolder(const QByteArray &fileFormat)
{
    QString path = "/Users/carolineyu/Documents/school/Undergraduate Research/XO_Classifier/board/";
    QString fileName = path + "game." + fileFormat;
    qDebug()<<"save file in folder";
//    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
//                               initialPath,
//                               tr("%1 Files (*.%2);;All Files (*)")
//                               .arg(QString::fromLatin1(fileFormat.toUpper()))
//                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {


        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}

