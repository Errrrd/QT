#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QDesktopServices>


 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 private:
     void createActions();
     void createMenus();
     void createStatusBar();
     bool maybeSave();
     void loadFile(const QString &fileName);
     bool saveFile(const QString &fileName);
     void setCurrentFile(const QString &fileName);
     QString strippedName(const QString &fullFileName);

     QVBoxLayout *layout;
     QPlainTextEdit *textEdit;
     QString currentFile;

     QMenu *fileMenu;
     QAction *newAct;
     QAction *openAct;
     QAction *saveAct;
     QAction *saveAsAct;
     QAction *exitAct;

 private slots:
     void newFile();
     void open();
     bool save();
     bool saveAs();
     void documentWasModified();

 public:
     MainWindow();

     ~MainWindow();
 };

 #endif
