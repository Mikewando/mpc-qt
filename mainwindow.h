#ifndef HOSTWINDOW_H
#define HOSTWINDOW_H

#include <QMainWindow>
#include <mpvwidget.h>
#include <QMenuBar>
#include <QTimer>
#include "helpers.h"
#include "qdrawnslider.h"
#include "qdrawnstatus.h"
#include "manager.h"
#include "playlistwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum DecorationState { AllDecorations, NoMenu, NoDecorations };
    enum ZoomMode { RegularZoom, Autofit, AutofitSmaller, AutofitLarger,
                    FitToWindow };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MpvWidget *mpvWidget();
    QMainWindow *mpvHost();
    PlaylistWindow *playlistWindow();
    QList<QAction *> editableActions();
    QVariantMap mouseMapDefaults();
    QVariantMap state();
    void setState(const QVariantMap &map);

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    bool mouseStateEvent(const MouseState &state);

    QMediaSlider *positionSlider();
    QVolumeSlider *volumeSlider();

    DecorationState decorationState();
    bool fullscreenMode();
    QSize noVideoSize();
    double sizeFactor();

    void setFullscreenMode(bool fullscreenMode);
    void setDiscState(bool playingADisc);

    void setupMenu();
    void setupPositionSlider();
    void setupVolumeSlider();
    void setupMpvWidget();
    void setupMpvHost();
    void setupPlaylist();
    void setupStatus();
    void setupSizing();
    void setupBottomArea();
    void setupHideTimer();
    void connectActionsToSlots();
    void connectButtonsToActions();
    void connectPlaylistWindowToActions();
    void globalizeAllActions();
    void setUiDecorationState(DecorationState state);
    void setUiEnabledState(bool enabled);
    void reparentBottomArea(bool overlay);
    void checkBottomArea(QPoint mousePosition);
    void updateBottomAreaGeometry();
    void updateTime();
    void updateFramedrops();
    void updateBitrate();
    void updatePlaybackStatus();
    void updateSize(bool first_run = false);
    void updateInfostats();
    void updateMouseHideTime();

signals:
    void applicationShouldQuit();
    void fileOpened(QUrl what, QUrl subs);
    void severalFilesOpened(QList<QUrl> what, bool important = false);
    void dvdbdOpened(QUrl what);
    void streamOpened(QUrl what);
    void recentOpened(TrackInfo info);
    void recentClear();
    void takeImage(bool subs);
    void takeImageAutomatically(bool subs);
    void optionsOpenRequested();
    void paused();
    void unpaused();
    void stopped();
    void stepBackward();
    void stepForward();
    void speedDown();
    void speedUp();
    void speedReset();
    void relativeSeek(bool forwards, bool isSmall);
    void audioTrackSelected(int64_t id);
    void subtitleTrackSelected(int64_t id);
    void videoTrackSelected(int64_t id);
    void volumeChanged(int64_t volume);
    void volumeMuteChanged(bool muted);
    void chapterPrevious();
    void chapterNext();
    void chapterSelected(int64_t id);
    void timeSelected(double time);
    void zoomPresetChanged(int which);

    void playCurrentItemRequested();
    void fireUpdateSize();

public slots:
    void setNoVideoSize(const QSize &sz);
    void setWindowedMouseMap(const MouseStateMap &map);
    void setFullscreenMouseMap(const MouseStateMap &map);
    void setRecentDocuments(QList<TrackInfo> tracks);
    void setTime(double time, double length);
    void setMediaTitle(QString title);
    void setChapterTitle(QString title);
    void setVideoSize(QSize size);
    void setSizeFactor(double factor);
    void setFitFactor(double fitFactor);
    void setZoomMode(ZoomMode mode);
    void setZoomPreset(int which, double fitFactor = -1.0);
    void setZoomCenter(bool yes);
    void setMouseHideTimeFullscreen(int msec);
    void setMouseHideTimeWindowed(int msec);
    void setBottomAreaBehavior(Helpers::ControlHiding method);
    void setBottomAreaHideTime(int milliseconds);
    void setTimeTooltip(bool show, bool above);
    void setFullscreenHidePanels(bool hidden);
    void setPlaybackState(PlaybackManager::PlaybackState state);
    void setPlaybackType(PlaybackManager::PlaybackType type);
    void setChapters(QList<QPair<double,QString>> chapters);
    void setAudioTracks(QList<QPair<int64_t,QString>> tracks);
    void setVideoTracks(QList<QPair<int64_t,QString>> tracks);
    void setSubtitleTracks(QList<QPair<int64_t,QString>> tracks);
    void setVolume(int level);
    void setFps(double fps);
    void setAvsync(double sync);
    void setDisplayFramedrops(int64_t count);
    void setDecoderFramedrops(int64_t count);
    void setPlaylistVisibleState(bool yes);
    void setPlaylistQuickQueueMode(bool yes);
    void setAudioBitrate(double bitrate);
    void setVideoBitrate(double bitrate);

private slots:
    void on_actionFileOpenQuick_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileOpenDvdbd_triggered();
    void on_actionFileOpenDirectory_triggered();
    void on_actionFileOpenNetworkStream_triggered();
    void on_actionFileRecentClear_triggered();
    void on_actionFileSaveImage_triggered();
    void on_actionFileSaveImageAuto_triggered();
    void on_actionFileSavePlainImage_triggered();
    void on_actionFileSavePlainImageAuto_triggered();
    void on_actionFileClose_triggered();
    void on_actionFileExit_triggered();

    void on_actionViewHideMenu_triggered();
    void on_actionViewHideSeekbar_toggled(bool checked);
    void on_actionViewHideControls_toggled(bool checked);
    void on_actionViewHideInformation_toggled(bool checked);
    void on_actionViewHideStatistics_toggled(bool checked);
    void on_actionViewHideStatus_toggled(bool checked);
    void on_actionViewHideSubresync_toggled(bool checked);
    void on_actionViewHidePlaylist_toggled(bool checked);
    void on_actionViewHideCapture_toggled(bool checked);
    void on_actionViewHideNavigation_toggled(bool checked);

    void on_actionViewPresetsMinimal_triggered();
    void on_actionViewPresetsCompact_triggered();
    void on_actionViewPresetsNormal_triggered();

    void on_actionViewFullscreen_toggled(bool checked);

    void on_actionViewZoom025_triggered();
    void on_actionViewZoom050_triggered();
    void on_actionViewZoom075_triggered();
    void on_actionViewZoom100_triggered();
    void on_actionViewZoom150_triggered();
    void on_actionViewZoom200_triggered();
    void on_actionViewZoom300_triggered();
    void on_actionViewZoom400_triggered();
    void on_actionViewZoomAutofit_triggered();
    void on_actionViewZoomAutofitLarger_triggered();
    void on_actionViewZoomAutofitSmaller_triggered();
    void on_actionViewZoomDisable_triggered();

    void on_actionViewOptions_triggered();

    void on_actionPlayPause_triggered(bool checked);
    void on_actionPlayStop_triggered();
    void on_actionPlayFrameBackward_triggered();
    void on_actionPlayFrameForward_triggered();
    void on_actionPlayRateDecrease_triggered();
    void on_actionPlayRateIncrease_triggered();
    void on_actionPlayRateReset_triggered();
    void on_actionPlaySeekForwards_triggered();
    void on_actionPlaySeekBackwards_triggered();
    void on_actionPlaySeekForwardsFine_triggered();
    void on_actionPlaySeekBackwardsFine_triggered();

    void on_actionPlayLoopStart_triggered();
    void on_actionPlayLoopEnd_triggered();
    void on_actionPlayLoopUse_triggered(bool checked);
    void on_actionPlayLoopClear_triggered();

    void on_actionPlayVolumeUp_triggered();
    void on_actionPlayVolumeDown_triggered();
    void on_actionPlayVolumeMute_toggled(bool checked);

    void on_actionNavigateChaptersPrevious_triggered();
    void on_actionNavigateChaptersNext_triggered();

    void on_actionHelpHomepage_triggered();
    void on_actionHelpAbout_triggered();

    void on_actionPlaylistSearch_triggered();

    void position_sliderMoved(int position);
    void position_hoverValue(double value, QString text, double x);
    void on_play_clicked();
    void volume_sliderMoved(double position);
    void playlistWindow_windowDocked();
    void hideTimer_timeout();

    void sendUpdateSize();

private:
    Ui::MainWindow *ui;
    QMainWindow *mpvHost_;
    MpvWidget *mpvw;
    QMediaSlider *positionSlider_;
    QVolumeSlider *volumeSlider_;
    QStatusTime *timePosition;
    QStatusTime *timeDuration;
    PlaylistWindow *playlistWindow_;
    QTimer hideTimer;

    DecorationState decorationState_;
    bool fullscreenMaximized;
    bool fullscreenMode_;
    bool fullscreenHidePanels;
    Helpers::ControlHiding bottomAreaBehavior;
    int bottomAreaHeight;
    int bottomAreaHideTime;
    bool timeTooltipShown;
    bool timeTooltipAbove;

    QString previousOpenDir;
    QSize noVideoSize_;
    bool isPlaying;
    bool isPaused;
    double sizeFactor_;
    double fitFactor_;
    ZoomMode zoomMode;
    bool zoomCenter;
    int mouseHideTimeWindowed;
    int mouseHideTimeFullscreen;
    int64_t displayDrops;
    int64_t decoderDrops;
    double audioBitrate;
    double videoBitrate;

    MouseStateMap mouseMapWindowed;
    MouseStateMap mouseMapFullscreen;
};

#endif // HOSTWINDOW_H
