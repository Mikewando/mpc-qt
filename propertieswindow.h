#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QDateTime>
#include <QDialog>
#include <QVariantList>
#include <QVariantMap>

namespace Ui {
class PropertiesWindow;
}

class PropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesWindow(QWidget *parent = 0);
    ~PropertiesWindow();

public slots:
    void setFileName(const QString &filename);
    void setFileFormat(const QString &format);
    void setFileSize(const int64_t &bytes);
    void setMediaLength(double time);
    void setVideoSize(const QSize &sz);
    void setFileCreationTime(const int64_t &secsSinceEpoch);
    void setTracks(const QVariantList &tracks);
    void setMediaTitle(const QString &title);
    void setFilePath(const QString &path);
    void setMetaData(QVariantMap data);

private:
    Ui::PropertiesWindow *ui;
};

#endif // PROPERTIESWINDOW_H
