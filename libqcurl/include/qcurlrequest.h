#ifndef QCURLREQUEST_H
#define QCURLREQUEST_H

#include "qcurlbase.h"

//! QCurlRequest represents a Network Request
/*!
 * It's useful if you need to customize some request setting, like setting up
 * CURLOPT_QUOTE to perform some custom command on ftp/sftp server.
 *
 * Each QCurlRequest is meant to be perform only once.
 *
 * You can use QCurl::request method to obtain a new QCurlRequest instance
 */
class Q_DECL_EXPORT QCurlRequest : public QObject
{
    Q_OBJECT

    QSharedDataPointer<QCurlRequestData> d;

public:
    QCurlRequest(QCurlData &data);
    QCurlRequest(const QCurlRequest &other);

    //! Set additional header for this request
    void setHeader(const QString &name, const QString &value);

    //! Set additional headers for this request
    void setHeaders(const QCurlHeaders &headers);

    //! Set CURLOPT_QUOTE
    void setQuote(const QStringList quotes);

    //! Set USER AGENT string for http
    void setUserAgent(const QString &userAgent);

    //! Setup proxy
    void setProxyUrl(const QUrl &proxyUrl);

    //! Set private key file path
    void setPrivateKeyPath(const QString &privateKeyPath);

    //! Set public key file path
    void setPublicKeyPath(const QString &publicKeyPath);

    //! Set private key password
    void setKeyPassword(const QString &keyPassword);

    //! Turn on/off curl verbose mode
    void setVerbose(bool verbose);

    //! Set if response body is needed
    void setNoBody(bool nobody);

    //! Flow redirection
    void setFlowLocation(bool flow);

    //! Set RAW request body
    void setBody(const QCurlBytes &bytes);

    //! Set REGULAR FORM request body
    void setBody(const QCurlForm &form);

    //! Set JSON request body
    void setBody(const QCurlJson &json);

    //! Set MULTIPART request body
    /*!
     * \brief setBody
     * \param parts QCurl will open QIODevice* in ReadOnly mode if it's not opened, and will close it afterward
     */
    void setBody(QCurlMultipart &parts);

    //! Set request body to a QIODevice
    void setBody(QIODevice &stream);

    //! Set downloading range
    void setRange(QString range);

    //! Perform request
    /*!
     * \brief perform
     * \param method GET/PUT/POST/DELETE/HEAD/...
     * \param path relative to baseUrl set on QCurl
     * \param responseBody pass a QIODevice pointer if you want to save response into disk,
     *                     QCurl won't close or delete this resource
     * \return QCurlResponse
     */
    QCurlResponse perform(const QString &method, const QString &path = QString(), QIODevice *responseBody = nullptr);

    //! Check if remote resource exists or not, support http/ftp/sftp
    /*!
     * \param path relative to baseUrl
     * \return bool
     */
    int exists(const QString &path = QString());
};

#endif // QCURLREQUEST_H
