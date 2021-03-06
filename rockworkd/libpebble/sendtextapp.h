#ifndef SENDTEXTAPP_H
#define SENDTEXTAPP_H

#include <QObject>
#include <QHash>
#include <QStringList>

/**
 * @brief The SendTextApp class
 */
class Pebble;
class WatchConnection;

class SendTextApp: public QObject
{
    Q_OBJECT
public:
    static const QUuid actionUUID;
    static const QUuid appUUID;
    static const char* appName;
    static const QSet<const QByteArray> appKeys;

    struct Contact {
        QString name;
        QStringList numbers;
    };

    SendTextApp(Pebble *pebble, WatchConnection *connection);

    QStringList getCannedMessages(const QByteArray &key) const;
    QList<Contact> getCannedContacts() const;

signals:
    void messageBlobSet(const QByteArray &key);
    void contactBlobSet();
    void sendTextMessage(const QString &account, const QString &contact, const QString &text) const;

public slots:
    void handleTextAction(const QString &contact, const QString &text) const;
    void setCannedMessages(const QHash<QString,QStringList> &cans);
    void wipeCannedMessages();
    void setCannedContacts(const QList<Contact> &favs, bool push=true);
    void wipeContacts();

private slots:
    void blobdbAckHandler(quint8 db, quint8 cmd, const QByteArray &key, quint8 ack);

private:
    QHash<QByteArray,QStringList> m_messages;
    QHash<QString,QString> m_revLookup;
    QList<Contact> m_contacts;

    Pebble *m_pebble;
    WatchConnection *m_connection;
};

#endif // SENDTEXTAPP_H
