#include <iostream>

#include <QApplication>
#include <QCommandLineParser>
#include <QTextBrowser>

#include "ui_mainwindow.h"

#include "epub.h"

int main(int argc, char *argv[])
{
    std::set_terminate([]()
    {
        try
        {
            throw;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Unhandled exception: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unhandled unknown exception" << std::endl;
        };
        if (qApp)
        {
            qApp->exit(1);
        }
        exit(1);
    });

    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("epub", "Path to the EPUB file to open");
    parser.process(app);

    app.setStyle("windows11");
    QMainWindow widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    std::filesystem::path epubPath = (parser.positionalArguments().value(0, "test/romeo_and_juliet_pg1513.epub")).toStdString();
    Epub epub(epubPath);

    class EpubTextBrowser : public QTextBrowser
    {
    public:
        using QTextBrowser::QTextBrowser;
        void setEpub(Epub *e) { epub_ = e; }

    protected:
        QVariant loadResource(int type, const QUrl &name) override
        {
            if (!epub_)
                return QTextBrowser::loadResource(type, name);
            std::string href = name.toString().toStdString();
            // Strip parts after '#' if present, as QUrl::toString() includes the fragment, but the manifest hrefs don't
            size_t fragmentPos = href.find('#');
            if (fragmentPos != std::string::npos)
            {
                href = href.substr(0, fragmentPos);
            }
            std::string content = epub_->readByHref(href);
            if (content.empty())
            {
                std::cerr << "Failed to read content for href: " << href << std::endl;
                return QVariant();
            }
            return QString::fromStdString(content);
        }

    private:
        Epub *epub_ = nullptr;
    };

    EpubTextBrowser view;
    view.setEpub(&epub);
    view.setSource(QUrl(epub.package()->manifest()->entryById("item3")->href().c_str()));
    view.setStyleSheet("background: transparent");
    view.setFrameStyle(QFrame::NoFrame);

    ui.webview->addWidget(&view);

    // Quit on button press
    ui.pushButton->connect(ui.pushButton, &QPushButton::clicked, &app, &QApplication::quit);

    widget.show();
    return app.exec();
}
