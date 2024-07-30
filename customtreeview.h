#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStandardItemModel>
#include <QTreeView>

class CustomTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit CustomTreeView(QWidget *parent = nullptr);

signals:
    void contextMenuRequested(const QPoint &pos, const QModelIndex &index);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QMenu *contextMenu;
    QAction *actionEdit;
    QAction *actionDelete;

private slots:
    void onEdit();
    void onDelete();
};

#endif // CUSTOMTREEVIEW_H
