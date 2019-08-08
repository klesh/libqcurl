#include <qcurl>

int main() {
    QCurlResponse res = QCurl::get(QUrl("http://example.com"));
    qDebug() << "status" << res.statusCode() << res.responseText();
    return 0;
}