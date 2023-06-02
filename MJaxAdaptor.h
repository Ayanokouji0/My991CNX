#ifndef MJAXADAPTOR_H
#define MJAXADAPTOR_H

#include <QCache>
#include <QObject>
#include <QWebEnginePage>
#include <QWebEngineView>

class MJaxAdaptor : public QObject {
    Q_OBJECT
public:
    explicit MJaxAdaptor(QObject* parent = nullptr);
    ~MJaxAdaptor();
    Q_INVOKABLE void MJaxSend(QString latex,QString svg1, QString svg2);
    Q_INVOKABLE void MJaxError(QString errorMessage);
    Q_INVOKABLE void MJaxLoaded();

public slots:
    void render(const QString& latex);
    void load();

signals:
    void rendered(QString latex,QByteArray svg);
    void loadFinished(bool result);

private slots:
    void onPageLoaded(bool);

private:
    QWebEngineView *m_view;
    QWebEnginePage *m_page;
    QCache<QString, QByteArray> m_cache;
};

#endif // MJAXADAPTOR_H
