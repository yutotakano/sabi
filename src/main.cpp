#include <iostream>

#include <QApplication>
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

    app.setStyle("windows11");
    QMainWindow widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    Epub epub(std::filesystem::path("test/romeo_and_juliet_pg1513.epub"));

    QTextBrowser view;
    view.setHtml(QString::fromStdString(epub.readById("item3")));
    view.setStyleSheet("background: transparent");
    view.setFrameStyle(QFrame::NoFrame);

    ui.webview->addWidget(&view);

    // Quit on button press
    ui.pushButton->connect(ui.pushButton, &QPushButton::clicked, &app, &QApplication::quit);

    widget.show();
    return app.exec();
}
