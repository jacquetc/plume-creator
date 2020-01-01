/***************************************************************************
*   Copyright (C) 2019 by Cyril Jacquet                                 *
*   cyril.jacquet@skribisto.eu                                        *
*                                                                         *
*  Filename: plmnotelistproxymodel.cpp
*                                                  *
*  This file is part of Skribisto.                                    *
*                                                                         *
*  Skribisto is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by   *
*  the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                    *
*                                                                         *
*  Skribisto is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with Skribisto.  If not, see <http://www.gnu.org/licenses/>. *
***************************************************************************/
#include "plmnotelistproxymodel.h"
#include "plmmodels.h"

#include <QTimer>

PLMNoteListProxyModel::PLMNoteListProxyModel(QObject *parent) : QSortFilterProxyModel(parent),
    m_showDeletedFilter(false), m_projectIdFilter(0), m_parentIdFilter(-1)
{
    this->setSourceModel(plmmodels->noteListModel());
    this->setDeletedFilter(false);
    m_parentIdFilter = 0;
    m_projectIdFilter = 0;
}

Qt::ItemFlags PLMNoteListProxyModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = QSortFilterProxyModel::flags(index);

    if (!index.isValid()) return defaultFlags;

    return defaultFlags | Qt::ItemFlag::ItemIsEditable;
}

// -----------------------------------------------------------------------

QVariant PLMNoteListProxyModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    QModelIndex sourceIndex = this->mapToSource(index);
    int col                 = index.column();
    int row                 = index.row();

    if ((role == Qt::EditRole) && (col == 0)) {
        return this->sourceModel()->data(sourceIndex,
                                         PLMNoteItem::Roles::NameRole).toString();
    }

    return QSortFilterProxyModel::data(index, role);
}

// -----------------------------------------------------------------------

bool PLMNoteListProxyModel::setData(const QModelIndex& index, const QVariant& value,
                                     int role)
{
    QModelIndex sourceIndex = this->mapToSource(index);

    PLMNoteItem *item =
            static_cast<PLMNoteItem *>(sourceIndex.internalPointer());

    if ((role == Qt::EditRole) && (sourceIndex.column() == 0)) {
        if (item->isProjectItem()) {
            return this->sourceModel()->setData(sourceIndex,
                                                value,
                                                PLMNoteItem::Roles::ProjectNameRole);
        } else {
            return this->sourceModel()->setData(sourceIndex,
                                                value,
                                                PLMNoteItem::Roles::NameRole);
        }
    }
    return QSortFilterProxyModel::setData(index, value, role);
}

//--------------------------------------------------------------

void PLMNoteListProxyModel::setParentFilter(int projectId, int parentId)
{
    m_projectIdFilter = projectId;
    m_parentIdFilter = parentId;
    this->invalidate();
}
//--------------------------------------------------------------


void PLMNoteListProxyModel::setDeletedFilter(bool showDeleted)
{
    m_showDeletedFilter = showDeleted;
    this->invalidate();
}

//--------------------------------------------------------------


bool PLMNoteListProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    bool result = false;

    QModelIndex index = this->sourceModel()->index(sourceRow, 0, sourceParent);
    if (!index.isValid()){
        return false;
    }
    PLMNoteItem *item = static_cast<PLMNoteItem *>(index.internalPointer());
    PLMNoteListModel *model = static_cast<PLMNoteListModel *>(this->sourceModel());

    // displays project list :
    if(m_parentIdFilter == -2 && item->isProjectItem() && plmdata->projectHub()->getProjectIdList().count() > 1){
        return true;
    }

    // path / parent filtering :
    int indexProject = item->data(PLMNoteItem::Roles::ProjectIdRole).toInt();
    if (indexProject == m_projectIdFilter){
        return false;
    }
    PLMNoteItem *parentItem = model->getParentNoteItem(item);
    if(parentItem){
        if(parentItem->paperId() == m_parentIdFilter){
            result = true;
        }
    }
    else if(!parentItem && item->indent() == 0 ){
        result = true;
    }
    else {
        return false;
    }

    // deleted filtering :

    if(result && item->data(PLMNoteItem::Roles::DeletedRole).toBool() == m_showDeletedFilter){
        return true;
    }
    return false;
}