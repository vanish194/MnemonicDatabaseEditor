#include "customtreeview.h"
#include <QDebug>
#include <QMessageBox>

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView(parent)
{
    contextMenu = new QMenu(this);

    actionEdit = new QAction(tr("Edit"), this);
    actionDelete = new QAction(tr("Delete"), this);

    contextMenu->addAction(actionEdit);
    contextMenu->addAction(actionDelete);

    connect(actionEdit, &QAction::triggered, this, &CustomTreeView::onEdit);
    connect(actionDelete, &QAction::triggered, this, &CustomTreeView::onDelete);
}

void CustomTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        emit contextMenuRequested(event->pos(), index);
        contextMenu->exec(event->globalPos());
    }
}

void CustomTreeView::onEdit()
{
    QModelIndex index = currentIndex();
    if (index.isValid()) {
        QString itemText = model()->data(index).toString();
        QMessageBox::information(this, tr("Edit"), tr("Edit item: %1").arg(itemText));
    }
}

void CustomTreeView::onDelete()
{
    QModelIndex index = currentIndex();
    if (index.isValid()) {
        QString itemText = model()->data(index).toString();
        QMessageBox::information(this, tr("Delete"), tr("Delete item: %1").arg(itemText));
        model()->removeRow(index.row(), index.parent());
    }
}
