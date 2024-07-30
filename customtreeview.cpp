#include "customtreeview.h"

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView(parent)
{
    contextMenu = new QMenu(this);

    addAction = new QAction("Add", this);
    editAction = new QAction("Edit", this);
    deleteAction = new QAction("Delete", this);

    contextMenu->addAction(addAction);
    contextMenu->addAction(editAction);
    contextMenu->addAction(deleteAction);

    connect(addAction, &QAction::triggered, this, &CustomTreeView::onAdd);
    connect(editAction, &QAction::triggered, this, &CustomTreeView::onEdit);
    connect(deleteAction, &QAction::triggered, this, &CustomTreeView::onDelete);
}

void CustomTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    contextMenu->exec(event->globalPos());
}

void CustomTreeView::onAdd()
{
    // Handle add action
}

void CustomTreeView::onEdit()
{
    // Handle edit action
}

void CustomTreeView::onDelete()
{
    // Handle delete action
}
