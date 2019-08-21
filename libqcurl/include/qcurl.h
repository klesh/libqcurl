#ifndef QCURL_H
#define QCURL_H

#include "qcurlbase.h"
#include "qcurlrequest.h"
#include "qcurlresponse.h"

//! The QCurl class represents a Network Session.
/*!
 *  A QCurl instance holds a session to a specific baseUrl, that mean
 *  you can perform multiple request on same connection.
 *
 *  QCurl also provides some \c static shortcut function in case you
 *  just need to grab something easily.
 */
class Q_DECL_EXPORT QCurl : public QObject
{
    Q_OBJECT
    QSharedDataPointer<QCurlData> d;

public:

    //! Constructs a Network Session
    /*!
     *
     * \param baseUrl all requests are relative to this baseUrl, if your url is meant
     *                for a directory, please make sure it has a / ending.
     */
    QCurl(const QUrl &baseUrl);
    QCurl(const QCurl &other);
    ~QCurl();

    //! Set default http headers for this session
    /*!
     * \param headers a QMap<QString, QString> contains all your customize header pairs
     */
    void setHeaders(const QCurlHeaders &headers);

    //! Set default http user-agent string for this session
    void setUserAgent(const QString &userAgent);

    //! Setup default proxy for this request
    /*!
     * \param proxyUrl i.e. socks5://localhost:1080
     */
    void setProxyUrl(const QUrl &proxyUrl);

    //! Set private key file path
    void setPrivateKeyPath(const QString &privateKeyPath);

    //! Set public key file path
    void setPublicKeyPath(const QString &publicKeyPath);

    //! Set private key password
    void setKeyPassword(const QString &keyPassword);

    //! Turn on/off curl's verbose mode
    void setVerbose(bool verbose);

    //! Whether flow redirection
    void setFlowLocation(bool flowLocation);

    //! Set CA path
    void setCaPath(const QString &path);

    //! Set timeout
    void setTimeout(long seconds);

    //! Return a QCurlRequest instance, so you can customize some setting before you actually perform it.
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlRequest
     */
    QCurlRequest request(const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a GET request
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse get(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a POST request
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse post(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse put(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a DELETE request
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse dele(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a HEAD request
    /*!
     * \param path relative to baseUrl
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse head(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Check if remote resource exists or not, support http/ftp/sftp
    /*!
     * \param result 1:  yes, 0: no, -1: error
     * \param path relative to baseUrl
     * \return bool
     */
    QCurlResponse exists(int &result, const QString &path = QString());

    //! Perform a POST request with a RAW request body
    /*!
     * \param path relative to baseUrl
     * \param bytes Raw bytes
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse post(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a POST request with a Regular Form (application/x-www-form-urlencoded)
    /*!
     * \param path relative to baseUrl
     * \param form name/value pairs as in QList<QPair<QString, QString>>
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse post(const QString &path, const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a POST request with a JSON body (application/json)
    /*!
     * \param path relative to baseUrl
     * \param json QJsonDocument
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse post(const QString &path, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a POST request with a Multipart body (multipart/form-data)
    /*!
     * \param path relative to baseUrl
     * \param parts a QList<QPair<QString, QVariant>> instance, which QVariant could be QString or QIODevice*
     *              you can pass in a QFile* or QFileDevice* which has fileName() property will be treated as
     *              File Field. However, if you pass a QBuffer*, it will be treated as raw value unless you
     *              give it a dynamic property "filename" by invoking `setProperty` method.
     *              note: you don't need to open QIODevice beforehand, but it will be closed after read
     * \param headers additional headers for this request only
     * \return QCurlResponse
     */
    QCurlResponse post(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a POST request with raw content from a QIODevice
    /*!
     * \brief post
     * \param path relative to baseUrl
     * \param stream for single file uploading scenario
     * \param headers additional headers for this request only
     * \return
     */
    QCurlResponse post(const QString &path, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request with a RAW body
    //!
    /*!
     * parameters are same as \link post(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty)
     */
    QCurlResponse put(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request with a Regular Form
    //!
    /*!
     * parameters same as \link post(const QString &path, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty)
     */
    QCurlResponse put(const QString &path, const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request with a JSON body
    //!
    /*!
     * parameters same as \link post(const QString &path, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty)
     */
    QCurlResponse put(const QString &path, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request with a Multipart body
    //!
    /*!
     * parameters same as \link post(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty)
     */
    QCurlResponse put(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);

    //! Perform a PUT request with raw content from a QIODevice
    //!
    /*!
     * parameters same as \link post(const QString &path, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty)
     */
    QCurlResponse put(const QString &path, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);


    //! Perform a GET request against baseUrl
    QCurlResponse get(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return get(QString(), headers); }
    //! Perform a POST request against baseUrl
    QCurlResponse post(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), headers); }
    //! Perform a PUT request against baseUrl
    QCurlResponse put(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), headers); }
    //! Perform a DELETE request against baseUrl
    QCurlResponse dele(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return dele(QString(), headers); }
    //! Perform a HEAD request against baseUrl
    QCurlResponse head(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return head(QString(), headers); }

    QCurlResponse post(const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), bytes, headers); }
    QCurlResponse post(const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), form, headers); }
    QCurlResponse post(const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), json, headers); }
    QCurlResponse post(QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), parts, headers); }
    QCurlResponse post(QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), stream, headers); }

    QCurlResponse put(const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), bytes, headers); }
    QCurlResponse put(const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), form, headers); }
    QCurlResponse put(const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), json, headers); }
    QCurlResponse put(QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), parts, headers); }
    QCurlResponse put(QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), stream, headers); }


    //! Perform a simple GET request without session
    static QCurlResponse get(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    //! Perform a simple POST request without session
    static QCurlResponse post(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    //! Perform a simple PUT request without session
    static QCurlResponse put(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    //! Perform a simple DELETE request without session
    static QCurlResponse dele(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    //! Perform a simple HEAD request without session
    static QCurlResponse head(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    //! Perform a simple existence checking without session
    static QCurlResponse exists(int &result, const QUrl &url);

    static QCurlResponse post(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    static QCurlResponse put(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, const QCurlForm &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

};

#endif // QCURL_H
