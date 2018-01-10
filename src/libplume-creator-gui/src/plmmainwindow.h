#ifndef PLMMAINWINDOW_H
#define PLMMAINWINDOW_H

#include "plmdata.h"
#include <QCloseEvent>
#include <QtWidgets/QMainWindow>

namespace Ui
{
class PLMMainWindow;
}

class PLMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PLMMainWindow(PLMData *data);
    void init();
    ~PLMMainWindow();

public slots:
    void clearFromAllProjects();
    void activate();
    void raiseWindow(const QString &windowName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void attachWindow(const QString &windowName);
    void detachWindow(const QString &windowName);
private:
    Ui::PLMMainWindow *ui;
    PLMData *m_data;
    void loadPlugins();
    QHash<QString, QMainWindow *> hash_nameAndWindow;
};

#endif // MAINWINDOW_H