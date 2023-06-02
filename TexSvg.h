#ifndef TEXSVG_H
#define TEXSVG_H

#include <QtCore/QObject>
#include <QQueue>

class MJaxAdaptor;

class TexSVG : public QObject {
    Q_OBJECT
public:
    explicit TexSVG(QObject* parent = nullptr);

    bool isLoaded() const;

public slots:
    void render(const QString& latex);
    void load();
signals:
    void rendered(QString latex, QByteArray svg);
    void loadFinished(bool result);

private slots:
    void setIsLoaded(bool new_isLoaded);

private:
    QQueue<QString> m_queue;
    bool mb_isLoaded;
    MJaxAdaptor *m_adaptor;
};

#endif
