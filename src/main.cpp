#include "ui_mainwindow.h"
#include <QApplication>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle("windowsvista");
    QMainWindow widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    QWebEngineView view;
    view.setHtml("<html><body><h1>Hello, World! </h1><p>This is a simple web view.</p></body></html>");

    ui.verticalLayout->addWidget(&view);

    // Quit on button press
    ui.pushButton->connect(ui.pushButton, &QPushButton::clicked, &app, &QApplication::quit);

    // Only show main window when the web view is loaded
    QObject::connect(&view, &QWebEngineView::loadFinished, [&widget](bool ok)
                     {
        if (ok) {
            widget.show();
        } });

    return app.exec();
}
