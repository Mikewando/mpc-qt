#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QDockWidget>
#include <QHash>
#include <QUuid>

namespace Ui {
class PlaylistWindow;
}

class QDrawnPlaylist;

class PlaylistWindow : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlaylistWindow(QWidget *parent = 0);
    ~PlaylistWindow();

    QPair<QUuid, QUuid> addToCurrentPlaylist(QList<QUrl> what);
    QPair<QUuid, QUuid> urlToQuickPlaylist(QUrl what);
    bool isCurrentPlaylistEmpty();
    QUuid getItemAfter(QUuid list, QUuid item);
    QUrl getUrlOf(QUuid list, QUuid item);

private:
    void addNewTab(QUuid playlist, QString title);

signals:
    void itemDesired(QUuid playlistUuid, QUuid itemUuid);

public slots:
    void changePlaylistSelection(QUuid playlistUuid, QUuid itemUuid);

private slots:
    void on_newTab_clicked();

    void on_closeTab_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_duplicateTab_clicked();

private:
    Ui::PlaylistWindow *ui;

    QHash<QUuid, QDrawnPlaylist*> widgets;
};

#endif // PLAYLISTWINDOW_H