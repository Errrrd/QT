#include "mainwindow.h"

 MainWindow::MainWindow()
    :
      textEdit(new QPlainTextEdit(this))

 {
     QWidget *widget = new QWidget;
     setCentralWidget(widget);

     //newFile();

     layout = new QVBoxLayout;
     //layout->setMargin(5);
     //layout->addWidget(topFiller);
     layout->addWidget(textEdit);
     //layout->addWidget(bottomFiller);
     widget->setLayout(layout);

     createActions();
     createMenus();

     connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

     setCurrentFile("");

     QString message = tr("Text Edit");
     statusBar()->showMessage(message);
 }

 MainWindow::~MainWindow() {}

 void MainWindow::newFile()
 {
     if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
     }
 }

 void MainWindow::open()
 {
     if (maybeSave()) {
          QString fileName = QFileDialog::getOpenFileName(this);
          if (!fileName.isEmpty()) {
              loadFile(fileName);
          }
     }
 }

 bool MainWindow::save()
 {
     if (currentFile.isEmpty()) {
        return saveAs();
     }
     return saveFile(currentFile);
 }

 bool MainWindow::saveAs()
 {
     QString fileName = QFileDialog::getSaveFileName(this);

     if (fileName.isEmpty()) {
          return false;
     }
     return saveFile(fileName);
 }


 void MainWindow::createActions()
 {
     newAct = new QAction(tr("&New"), this);
     newAct->setShortcuts(QKeySequence::New);
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     openAct = new QAction(tr("&Open..."), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     saveAct = new QAction(tr("&Save"), this);
     saveAct->setShortcuts(QKeySequence::Save);
     saveAct->setStatusTip(tr("Save the document to disk"));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

     saveAsAct = new QAction(tr("&Save as..."), this);
     saveAsAct->setShortcuts(QKeySequence::Print);
     saveAsAct->setStatusTip(tr("Save the document to disk as..."));
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAct = new QAction(tr("E&xit"), this);
     exitAct->setShortcuts(QKeySequence::Quit);
     exitAct->setStatusTip(tr("Exit the application"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newAct);
     fileMenu->addAction(openAct);
     fileMenu->addAction(saveAct);
     fileMenu->addAction(saveAsAct);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAct);
 }

 void MainWindow::documentWasModified()
 {
     setWindowModified(textEdit->document()->isModified());
 }

bool MainWindow::maybeSave()
 {
     if (textEdit->document()->isModified()) {
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Application"),
                      tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         if (ret == QMessageBox::Save)
             return save();
         else if (ret == QMessageBox::Cancel)
             return false;
     }
     return true;
 }

 void MainWindow::loadFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"), tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     textEdit->setPlainText(in.readAll());
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 }

 bool MainWindow::saveFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     out << textEdit->toPlainText();
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File saved"), 2000);
     return true;
 }

 void MainWindow::setCurrentFile(const QString &fileName)
 {
     currentFile = fileName;
     textEdit->document()->setModified(false);
     setWindowModified(false);

     QString shownName = currentFile;
     if (currentFile.isEmpty())
         shownName = "untitled.txt";
     setWindowFilePath(shownName);
 }

 QString MainWindow::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }
