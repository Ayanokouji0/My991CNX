#include "MJaxAdaptor.h"

#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QRegularExpression>
#include <QTimer>
#include <QWebChannel>

MJaxAdaptor::MJaxAdaptor(QObject* parent)
    : QObject(parent)
{
    m_view = new QWebEngineView();
    m_page = nullptr;

    connect(m_view, &QWebEngineView::loadFinished,
        this, &MJaxAdaptor::onPageLoaded);
}

MJaxAdaptor::~MJaxAdaptor()
{
    delete m_page;
    delete m_view;
}

void MJaxAdaptor::MJaxSend(QString latex, QString svg1, QString svg2)
{

    QRegularExpression s1("<.?svg>");
    QRegularExpression s2("(<svg .+?>)");

    svg1 = svg1.replace(s1, " ");
    emit rendered(latex, svg2.replace(s2, "\\1" + svg1).toUtf8());
}

void MJaxAdaptor::MJaxError(QString errorMessage)
{
    qDebug() << "ERROR:" << errorMessage;
}

void MJaxAdaptor::MJaxLoaded()
{
    emit loadFinished(true);
}

void MJaxAdaptor::render(const QString& latex)
{
    QString tex = latex;
    tex = tex.replace("\\", "\\\\")
              .replace("'", "\\'")
              .replace("\n", "\\\n");

    QString toRun = QString("var TeX2SVG_result = null;"
                            "try {"
                            "    TeX2SVG_result = UpdateOutput( '%1' );"
                            "} catch ( e ) {"
                            "    cpp.MJaxError(e.toString());"
                            "}"
                            "TeX2SVG_result")
                        .arg(tex);

    m_page->runJavaScript(toRun);
}

void MJaxAdaptor::load()
{
    QString toLoad
        = "qrc:/main.html";
    m_view->load(QUrl(toLoad));
}

void MJaxAdaptor::onPageLoaded(bool result)
{
    if (result) {
        if (m_page != nullptr) delete m_page;
        m_page = m_view->page();
        QFile apiFile(":/qtwebchannel/qwebchannel.js"); //load the API from the resources
        if (!apiFile.open(QIODevice::ReadOnly))
            qDebug() << "Couldn't load Qt QWebChannel API!";
        QString apiScript = QString::fromLatin1(apiFile.readAll());
        apiFile.close();

        m_page->runJavaScript(apiScript);
        QWebChannel* ch = new QWebChannel(m_page);
        m_page->setWebChannel(ch);
        QString code = QStringLiteral(
            R"DELIM(
        window.webChannel = new QWebChannel(qt.webChannelTransport, function( channel)
        {
            cpp = channel.objects.cpp;
            if(MathJaxIsLoaded){
            cpp.MJaxLoaded();
            }
        });

        )DELIM");

        ch->registerObject(QStringLiteral("cpp"), this);
        m_page->runJavaScript(code);
    } else {
        emit loadFinished(false);
    }
}
