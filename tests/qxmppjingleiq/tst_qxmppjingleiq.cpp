/*
 * Copyright (C) 2008-2014 The QXmpp developers
 *
 * Author:
 *  Jeremy Lainé
 *
 * Source:
 *  https://github.com/qxmpp-project/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include <QObject>
#include "QXmppJingleIq.h"
#include "util.h"

class tst_QXmppJingleIq : public QObject
{
    Q_OBJECT

private slots:
    void testCandidate();
    void testRtpSession();
    void testSession();
    void testTerminate();
    void testAudioPayloadType();
    void testVideoPayloadType();
    void testRinging();
};

void tst_QXmppJingleIq::testCandidate()
{
    const QByteArray xml(
        "<candidate component=\"1\""
        " foundation=\"1\""
        " generation=\"0\""
        " id=\"el0747fg11\""
        " ip=\"10.0.1.1\""
        " network=\"1\""
        " port=\"8998\""
        " priority=\"2130706431\""
        " protocol=\"udp\""
        " type=\"host\"/>");

    QXmppJingleCandidate candidate;
    parsePacket(candidate, xml);
    QCOMPARE(candidate.foundation(), QLatin1String("1"));
    QCOMPARE(candidate.generation(), 0);
    QCOMPARE(candidate.id(), QLatin1String("el0747fg11"));
    QCOMPARE(candidate.host(), QHostAddress("10.0.1.1"));
    QCOMPARE(candidate.network(), 1);
    QCOMPARE(candidate.port(), quint16(8998));
    QCOMPARE(candidate.priority(), 2130706431);
    QCOMPARE(candidate.protocol(), QLatin1String("udp"));
    QCOMPARE(candidate.type(), QXmppJingleCandidate::HostType);
    serializePacket(candidate, xml);
};

void tst_QXmppJingleIq::testRtpSession()
{
    const QByteArray xml(
"<iq"
    " id=\"ih28sx61\""
    " to=\"juliet@capulet.lit/balcony\""
    " from=\"romeo@montague.lit/orchard\""
    " type=\"set\">"
  "<jingle xmlns=\"urn:xmpp:jingle:1\""
          " action=\"session-initiate\""
          " initiator=\"romeo@montague.lit/orchard\""
          " sid=\"a73sjjvkla37jfea\">"
    "<content creator=\"initiator\" name=\"voice\">"
      "<description xmlns=\"urn:xmpp:jingle:apps:rtp:1\" media=\"audio\">"
        "<payload-type id=\"96\" name=\"speex\" clockrate=\"16000\"/>"
        "<payload-type id=\"97\" name=\"speex\" clockrate=\"8000\"/>"
        "<payload-type id=\"18\" name=\"G729\"/>"
        "<payload-type id=\"0\" name=\"PCMU\"/>"
        "<payload-type id=\"103\" name=\"L16\" channels=\"2\" clockrate=\"16000\"/>"
        "<payload-type id=\"98\" name=\"x-ISAC\" clockrate=\"8000\"/>"
      "</description>"
      "<transport xmlns=\"urn:xmpp:jingle:transports:ice-udp:1\""
                 " ufrag=\"8hhy\""
                 " pwd=\"asd88fgpdd777uzjYhagZg\">"
        "<candidate component=\"1\""
                   " foundation=\"1\""
                   " generation=\"0\""
                   " id=\"el0747fg11\""
                   " ip=\"10.0.1.1\""
                   " network=\"1\""
                   " port=\"8998\""
                   " priority=\"2130706431\""
                   " protocol=\"udp\""
                   " type=\"host\"/>"
        "<candidate component=\"1\""
                   " foundation=\"2\""
                   " generation=\"0\""
                   " id=\"y3s2b30v3r\""
                   " ip=\"192.0.2.3\""
                   " network=\"1\""
                   " port=\"45664\""
                   " priority=\"1694498815\""
                   " protocol=\"udp\""
                   " type=\"srflx\"/>"
      "</transport>"
    "</content>"
  "</jingle>"
"</iq>");

    QXmppJingleIq session;
    parsePacket(session, xml);
    QCOMPARE(session.action(), QXmppJingleIq::SessionInitiate);
    QCOMPARE(session.initiator(), QLatin1String("romeo@montague.lit/orchard"));
    QCOMPARE(session.sid(), QLatin1String("a73sjjvkla37jfea"));
    QCOMPARE(session.content().creator(), QLatin1String("initiator"));
    QCOMPARE(session.content().name(), QLatin1String("voice"));
    QCOMPARE(session.reason().text(), QString());
    QCOMPARE(session.reason().type(), QXmppJingleIq::Reason::None);
    serializePacket(session, xml);
}

void tst_QXmppJingleIq::testSession()
{
    const QByteArray xml(
        "<iq"
        " id=\"zid615d9\""
        " to=\"juliet@capulet.lit/balcony\""
        " from=\"romeo@montague.lit/orchard\""
        " type=\"set\">"
        "<jingle xmlns=\"urn:xmpp:jingle:1\""
        " action=\"session-initiate\""
        " initiator=\"romeo@montague.lit/orchard\""
        " sid=\"a73sjjvkla37jfea\">"
        "<content creator=\"initiator\" name=\"this-is-a-stub\">"
        "<description xmlns=\"urn:xmpp:jingle:apps:stub:0\"/>"
        "<transport xmlns=\"urn:xmpp:jingle:transports:stub:0\"/>"
        "</content>"
        "</jingle>"
        "</iq>");

    QXmppJingleIq session;
    parsePacket(session, xml);
    QCOMPARE(session.action(), QXmppJingleIq::SessionInitiate);
    QCOMPARE(session.initiator(), QLatin1String("romeo@montague.lit/orchard"));
    QCOMPARE(session.sid(), QLatin1String("a73sjjvkla37jfea"));
    QCOMPARE(session.content().creator(), QLatin1String("initiator"));
    QCOMPARE(session.content().name(), QLatin1String("this-is-a-stub"));
    QCOMPARE(session.reason().text(), QString());
    QCOMPARE(session.reason().type(), QXmppJingleIq::Reason::None);
    serializePacket(session, xml);
}

void tst_QXmppJingleIq::testTerminate()
{
    const QByteArray xml(
        "<iq"
        " id=\"le71fa63\""
        " to=\"romeo@montague.lit/orchard\""
        " from=\"juliet@capulet.lit/balcony\""
        " type=\"set\">"
        "<jingle xmlns=\"urn:xmpp:jingle:1\""
        " action=\"session-terminate\""
        " sid=\"a73sjjvkla37jfea\">"
        "<reason>"
        "<success/>"
        "</reason>"
        "</jingle>"
        "</iq>");

    QXmppJingleIq session;
    parsePacket(session, xml);
    QCOMPARE(session.action(), QXmppJingleIq::SessionTerminate);
    QCOMPARE(session.initiator(), QString());
    QCOMPARE(session.sid(), QLatin1String("a73sjjvkla37jfea"));
    QCOMPARE(session.reason().text(), QString());
    QCOMPARE(session.reason().type(), QXmppJingleIq::Reason::Success);
    serializePacket(session, xml);
}

void tst_QXmppJingleIq::testAudioPayloadType()
{
    const QByteArray xml("<payload-type id=\"103\" name=\"L16\" channels=\"2\" clockrate=\"16000\"/>");
    QXmppJinglePayloadType payload;
    parsePacket(payload, xml);
    QCOMPARE(payload.id(), static_cast<unsigned char>(103));
    QCOMPARE(payload.name(), QLatin1String("L16"));
    QCOMPARE(payload.channels(), static_cast<unsigned char>(2));
    QCOMPARE(payload.clockrate(), 16000u);
    serializePacket(payload, xml);
}

void tst_QXmppJingleIq::testVideoPayloadType()
{
    const QByteArray xml(
        "<payload-type id=\"98\" name=\"theora\" clockrate=\"90000\">"
            "<parameter name=\"height\" value=\"768\"/>"
            "<parameter name=\"width\" value=\"1024\"/>"
        "</payload-type>");
    QXmppJinglePayloadType payload;
    parsePacket(payload, xml);
    QCOMPARE(payload.id(), static_cast<unsigned char>(98));
    QCOMPARE(payload.name(), QLatin1String("theora"));
    QCOMPARE(payload.clockrate(), 90000u);
    QCOMPARE(payload.parameters().size(), 2);
    QCOMPARE(payload.parameters().value("height"), QLatin1String("768"));
    QCOMPARE(payload.parameters().value("width"), QLatin1String("1024"));
    serializePacket(payload, xml);
}

void tst_QXmppJingleIq::testRinging()
{
    const QByteArray xml(
        "<iq"
        " id=\"tgr515bt\""
        " to=\"romeo@montague.lit/orchard\""
        " from=\"juliet@capulet.lit/balcony\""
        " type=\"set\">"
        "<jingle xmlns=\"urn:xmpp:jingle:1\""
        " action=\"session-info\""
        " initiator=\"romeo@montague.lit/orchard\""
        " sid=\"a73sjjvkla37jfea\">"
        "<ringing xmlns=\"urn:xmpp:jingle:apps:rtp:info:1\"/>"
        "</jingle>"
        "</iq>");

    QXmppJingleIq iq;
    parsePacket(iq, xml);
    QCOMPARE(iq.ringing(), true);
    serializePacket(iq, xml);
}

QTEST_MAIN(tst_QXmppJingleIq)
#include "tst_qxmppjingleiq.moc"
