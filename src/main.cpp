#include "ui_mainwindow.h"
#include <QApplication>
#include <QtWebView>

int main(int argc, char *argv[])
{
    QtWebView::initialize();
    QApplication app(argc, argv);

    app.setStyle("windowsvista");
    QMainWindow widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    QWebView view;
    view.loadHtml("<html><body><h1>Hello, World!</h1><p>This is a simple web view.</p></body></html>");

    QWidget *webViewContainer = QWidget::createWindowContainer(&view); 
    ui.verticalLayout->addWidget(webViewContainer);

    widget.show();
    return app.exec();
}
