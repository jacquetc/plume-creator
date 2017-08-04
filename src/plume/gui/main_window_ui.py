# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/cyril/Devel/plume/plume-creator-py/src/plume/gui/main_window.ui'
#
# Created by: PyQt5 UI code generator 5.5.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1197, 766)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/pics/plume-creator.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setDockOptions(QtWidgets.QMainWindow.AnimatedDocks)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1197, 19))
        self.menubar.setObjectName("menubar")
        self.menuProject = QtWidgets.QMenu(self.menubar)
        self.menuProject.setObjectName("menuProject")
        self.menuView = QtWidgets.QMenu(self.menubar)
        self.menuView.setObjectName("menuView")
        self.menuHelp = QtWidgets.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.actionOpen_test_project = QtWidgets.QAction(MainWindow)
        self.actionOpen_test_project.setObjectName("actionOpen_test_project")
        self.actionWrite = QtWidgets.QAction(MainWindow)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/pics/48x48/scribus.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionWrite.setIcon(icon1)
        self.actionWrite.setObjectName("actionWrite")
        self.actionNote = QtWidgets.QAction(MainWindow)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/pics/48x48/accessories-text-editor.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionNote.setIcon(icon2)
        self.actionNote.setObjectName("actionNote")
        self.actionExit = QtWidgets.QAction(MainWindow)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/pics/16x16/application-exit.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionExit.setIcon(icon3)
        self.actionExit.setObjectName("actionExit")
        self.actionClose_project = QtWidgets.QAction(MainWindow)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/pics/16x16/window-close.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionClose_project.setIcon(icon4)
        self.actionClose_project.setObjectName("actionClose_project")
        self.actionImport = QtWidgets.QAction(MainWindow)
        icon5 = QtGui.QIcon()
        icon5.addPixmap(QtGui.QPixmap(":/pics/16x16/document-import.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionImport.setIcon(icon5)
        self.actionImport.setObjectName("actionImport")
        self.actionExport = QtWidgets.QAction(MainWindow)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(":/pics/16x16/document-export.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionExport.setIcon(icon6)
        self.actionExport.setObjectName("actionExport")
        self.actionSave = QtWidgets.QAction(MainWindow)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(":/pics/16x16/document-save.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionSave.setIcon(icon7)
        self.actionSave.setObjectName("actionSave")
        self.actionSave_as = QtWidgets.QAction(MainWindow)
        icon8 = QtGui.QIcon()
        icon8.addPixmap(QtGui.QPixmap(":/pics/16x16/document-save-as.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionSave_as.setIcon(icon8)
        self.actionSave_as.setObjectName("actionSave_as")
        self.actionOpen = QtWidgets.QAction(MainWindow)
        icon9 = QtGui.QIcon()
        icon9.addPixmap(QtGui.QPixmap(":/pics/16x16/document-open.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionOpen.setIcon(icon9)
        self.actionOpen.setObjectName("actionOpen")
        self.actionNew_project = QtWidgets.QAction(MainWindow)
        icon10 = QtGui.QIcon()
        icon10.addPixmap(QtGui.QPixmap(":/pics/16x16/tools-wizard.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionNew_project.setIcon(icon10)
        self.actionNew_project.setObjectName("actionNew_project")
        self.actionStart_window = QtWidgets.QAction(MainWindow)
        icon11 = QtGui.QIcon()
        icon11.addPixmap(QtGui.QPixmap(":/pics/16x16/go-home.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionStart_window.setIcon(icon11)
        self.actionStart_window.setObjectName("actionStart_window")
        self.actionAbout_Plume_Creator = QtWidgets.QAction(MainWindow)
        icon12 = QtGui.QIcon()
        icon12.addPixmap(QtGui.QPixmap(":/pics/16x16/help-about.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionAbout_Plume_Creator.setIcon(icon12)
        self.actionAbout_Plume_Creator.setObjectName("actionAbout_Plume_Creator")
        self.actionAbout_Qt = QtWidgets.QAction(MainWindow)
        self.actionAbout_Qt.setIcon(icon12)
        self.actionAbout_Qt.setObjectName("actionAbout_Qt")
        self.actionPrint = QtWidgets.QAction(MainWindow)
        icon13 = QtGui.QIcon()
        icon13.addPixmap(QtGui.QPixmap(":/pics/16x16/document-print.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionPrint.setIcon(icon13)
        self.actionPrint.setObjectName("actionPrint")
        self.actionPreferences = QtWidgets.QAction(MainWindow)
        icon14 = QtGui.QIcon()
        icon14.addPixmap(QtGui.QPixmap(":/pics/16x16/preferences-system.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionPreferences.setIcon(icon14)
        self.actionPreferences.setObjectName("actionPreferences")
        self.actionWelcome = QtWidgets.QAction(MainWindow)
        self.actionWelcome.setIcon(icon)
        self.actionWelcome.setObjectName("actionWelcome")
        self.menuProject.addAction(self.actionNew_project)
        self.menuProject.addAction(self.actionStart_window)
        self.menuProject.addAction(self.actionOpen_test_project)
        self.menuProject.addAction(self.actionOpen)
        self.menuProject.addSeparator()
        self.menuProject.addAction(self.actionSave)
        self.menuProject.addAction(self.actionSave_as)
        self.menuProject.addSeparator()
        self.menuProject.addAction(self.actionPreferences)
        self.menuProject.addSeparator()
        self.menuProject.addAction(self.actionPrint)
        self.menuProject.addSeparator()
        self.menuProject.addAction(self.actionExport)
        self.menuProject.addAction(self.actionImport)
        self.menuProject.addSeparator()
        self.menuProject.addAction(self.actionClose_project)
        self.menuProject.addAction(self.actionExit)
        self.menuView.addAction(self.actionWrite)
        self.menuView.addAction(self.actionNote)
        self.menuView.addSeparator()
        self.menuHelp.addAction(self.actionAbout_Plume_Creator)
        self.menuHelp.addAction(self.actionAbout_Qt)
        self.menubar.addAction(self.menuProject.menuAction())
        self.menubar.addAction(self.menuView.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())
        self.toolBar.addAction(self.actionPreferences)
        self.toolBar.addAction(self.actionStart_window)
        self.toolBar.addAction(self.actionOpen_test_project)
        self.toolBar.addAction(self.actionSave)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):

        MainWindow.setWindowTitle(_("Plume Creator"))
        self.menuProject.setTitle(_("&Project"))
        self.menuView.setTitle(_("&View"))
        self.menuHelp.setTitle(_("&Help"))
        self.toolBar.setWindowTitle(_("toolBar"))
        self.actionOpen_test_project.setText(_("&Open test project"))
        self.actionWrite.setText(_("&Write"))
        self.actionNote.setText(_("&Note"))
        self.actionNote.setToolTip(_("Note"))
        self.actionExit.setText(_("E&xit"))
        self.actionClose_project.setText(_("&Close project"))
        self.actionImport.setText(_("&Import"))
        self.actionExport.setText(_("&Export"))
        self.actionSave.setText(_("Sa&ve"))
        self.actionSave_as.setText(_("Save as"))
        self.actionOpen.setText(_("Open"))
        self.actionNew_project.setText(_("&New project"))
        self.actionStart_window.setText(_("&Start window"))
        self.actionAbout_Plume_Creator.setText(_("&About Plume Creator"))
        self.actionAbout_Qt.setText(_("About &Qt"))
        self.actionPrint.setText(_("P&rint"))
        self.actionPreferences.setText(_("&Preferences"))
        self.actionWelcome.setText(_("W&elcome"))

