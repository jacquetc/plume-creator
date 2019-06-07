/***************************************************************************
*   Copyright (C) 2019 by Cyril Jacquet                                 *
*   cyril.jacquet@plume-creator.eu                                        *
*                                                                         *
*  Filename: plmbasesubwindow.cpp
*                                                  *
*  This file is part of Plume Creator.                                    *
*                                                                         *
*  Plume Creator is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by   *
*  the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                    *
*                                                                         *
*  Plume Creator is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with Plume Creator.  If not, see <http://www.gnu.org/licenses/>. *
***************************************************************************/
#include "plmsubwindow.h"
#include "ui_plmbasesubwindow.h"

PLMSubWindow::PLMSubWindow(int id, QWidget *parent) : QMainWindow(parent),
    m_id(id), ui(
        new Ui::PLMBaseSubWindow) {
    ui->setupUi(this);

    this->setupActions();
}

PLMSubWindow::~PLMSubWindow()
{
    delete ui;
}

void PLMSubWindow::mousePressEvent(QMouseEvent *event) {
    // qDebug() << "pressed";
    emit subWindowFocusActived(m_id);

    event->ignore();
}

void PLMSubWindow::addDocument(PLMBaseDocument *document) {
    ui->stackedWidget->addWidget(document);
    ui->stackedWidget->setCurrentWidget(document);

    m_documentList.append(document);

    // focus update :


    connect(document, &PLMBaseDocument::documentFocusActived,
            [ = ](int id) {
        Q_UNUSED(id)
        emit subWindowFocusActived(m_id);
    });

    emit documentAdded(document->getProjectId(), document->getDocumentId());
}

bool PLMSubWindow::setCurrentDocument(int projectId, int documentId)
{
    bool success = false;

    for (PLMBaseDocument *document : m_documentList) {
        if ((document->getProjectId() == projectId) &&
            (document->getDocumentId() == documentId)) {
            ui->stackedWidget->setCurrentWidget(document);
            document->setFocus();
            success = true;
        }
    }

    return success;
}

void PLMSubWindow::clearProject(int projectId)
{
    QMutableListIterator<PLMBaseDocument *> i(m_documentList);

    while (i.hasNext()) {
        if (i.next()->getProjectId() == projectId) {
            i.next()->deleteLater();
            i.remove();
        }
    }
}

void PLMSubWindow::setupActions()
{
    ui->closeWindowButton->setDefaultAction(ui->actionClose);

    connect(ui->actionClose,
            &QAction::triggered,
            [ = ]() {
        emit subWindowClosed(this->id());
    });

    ui->splitButton->addAction(ui->actionSplitVertically);

    connect(ui->actionSplitVertically,
            &QAction::triggered,
            [ = ]() {
        emit splitCalled(Qt::Vertical, this->id());
    });

    ui->splitButton->addAction(ui->actionSplitHorizontally);

    connect(ui->actionSplitHorizontally,
            &QAction::triggered,
            [ = ]() {
        emit splitCalled(Qt::Horizontal, this->id());
    });
}