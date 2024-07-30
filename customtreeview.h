#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QTreeView>

class CustomTreeView : public QTreeView
{
    Q_OBJECT

public:
    CustomTreeView(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void onAdd();
    void onEdit();
    void onDelete();

private:
    QMenu *contextMenu;
    QAction *addAction;
    QAction *editAction;
    QAction *deleteAction;
};

#endif // CUSTOMTREEVIEW_H
