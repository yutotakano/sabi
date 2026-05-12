#include <iostream>

#include <QApplication>
#include <QWebEngineView>

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

    app.setStyle("windows11");
    QMainWindow widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    QWebEngineView view;
    view.setHtml("<html><head><style>@media (prefers-color-scheme: dark) { html { color: #ffffff; }}</style></head><body><h1>Hello, World! </h1><p>This is a simple web view.</p></body></html>");
    view.page()->setBackgroundColor(Qt::transparent);

    ui.webview->addWidget(&view);

    // Quit on button press
    ui.pushButton->connect(ui.pushButton, &QPushButton::clicked, &app, &QApplication::quit);

    // Only show main window when the web view is loaded
    QObject::connect(&view, &QWebEngineView::loadFinished, [&widget](bool ok)
    {
        if (ok)
        {
            widget.show();
        }
    });

    Epub epub(std::filesystem::path("test/romeo_and_juliet_pg1513.epub"));

    return app.exec();
}
