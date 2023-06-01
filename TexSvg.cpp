#include "TexSvg.h"
#include "MJaxAdaptor.h"

TexSVG::TexSVG(QObject* parent)
    : QObject(parent)
{
    mb_isLoaded = false;
    m_adaptor = new MJaxAdaptor(this);

    connect(m_adaptor, &MJaxAdaptor::loadFinished,
        this, &TexSVG::setIsLoaded);
    connect(m_adaptor, &MJaxAdaptor::loadFinished,
        this, &TexSVG::loadFinished);
    connect(m_adaptor, &MJaxAdaptor::rendered,
        this, &TexSVG::rendered);
}

bool TexSVG::isLoaded() const
{
    return mb_isLoaded;
}

void TexSVG::render(const QString& latex)
{
    if (mb_isLoaded) {
        m_adaptor->render(latex);
    } else {
        m_queue.push_back(latex);
    }
}

void TexSVG::load()
{
    m_adaptor->load();
}

void TexSVG::setIsLoaded(bool new_isLoaded)
{
    mb_isLoaded = new_isLoaded;

    while (!m_queue.empty()) {
        render(m_queue.front());
        m_queue.pop_front();
    }
}
