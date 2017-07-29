#include "MQTTPacket.h"
namespace mqtter {

const char* MQTTPacket::packet_names[] =
{
   "RESERVED", "CONNECT", "CONNACK", "PUBLISH", "PUBACK", "PUBREC", "PUBREL",
   "PUBCOMP", "SUBSCRIBE", "SUBACK", "UNSUBSCRIBE", "UNSUBACK",
   "PINGREQ", "PINGRESP", "DISCONNECT"
};

MQTTPacket::MQTTPacket(int type,int dried, int dup,int qos):
    _ptype(type),_size(0),_step(0),_dried(dried)
{
    printf("Packet Type:%s\n", packet_names[type]);
    switch (_ptype)
    {
    case CONNECT:
#if DEBUG
        _packet = (pConnect)malloc(sizeof(Connect));
        memset(_packet,0,sizeof(Connect));
        pFMT(pConnect)->header.byte = 0;
        pFMT(pConnect)->header.bits.type = CONNECT;
#else
        ALLOC0(pConnect,Connect)
        initHeader0(pConnect,CONNECT)
#endif
        pFMT(pConnect)->Protocol = MQTT_NAME;
        //MQNEW(pConnect,Protocol,MQTT_NAME,4);
        pFMT(pConnect)->version = MQTT_VER;
        _step += 3;
        /* add CONNECT Variable header, size (2-byte)*/
        _size += 2 + 4 + 1;
        break;
    case CONNACK:
#if DEBUG
        _packet = (pConnAck)malloc(sizeof(ConnAck));
        memset(_packet,0,sizeof(ConnAck));
        pFMT(pConnAck)->header.byte = 0;
        pFMT(pConnAck)->header.bits.type = CONNACK;
#else
        ALLOC0(pConnAck,ConnAck)
        initHeader0(pConnAck,CONNACK)
#endif
        _step++;
        break;
    case PUBLISH:
#if DEBUG
        _packet = (pPublish)malloc(sizeof(Publish));
        memset(_packet,0,sizeof(Publish));
        pFMT(pPublish)->header.byte = 0;
        pFMT(pPublish)->header.bits.type = PUBLISH;
        pFMT(pPublish)->header.bits.dup = dup;
        pFMT(pPublish)->header.bits.qos = qos;
#else
        ALLOC0(pPublish,Publish)
        initHeader3(pPublish,PUBLISH,dup,qos)
#endif
        _step++;
        break;
    case PUBACK:
#if DEBUG
        _packet = (pPubAck)malloc(sizeof(PubAck));
        memset(_packet,0,sizeof(PubAck));
        pFMT(pPubAck)->header.byte = 0;
        pFMT(pPubAck)->header.bits.type = PUBACK;
#else
        ALLOC0(pPubAck,PubAck)
        initHeader0(pPubAck,PUBACK)
#endif
        _step++;
        break;
    case PUBREC:
#if DEBUG
        _packet = (pPubRec)malloc(sizeof(PubRec));
        memset(_packet,0,sizeof(PubRec));
        pFMT(pPubRec)->header.byte = 0;
        pFMT(pPubRec)->header.bits.type = PUBREC;
#else
        ALLOC0(pPubRec,PubRec)
        initHeader0(pPubRec,PUBREC)
#endif
        _step++;
        break;
    case PUBREL:
#if DEBUG
        _packet = (pPubRel)malloc(sizeof(PubRel));
        memset(_packet,0,sizeof(PubRel));
        pFMT(pPubRel)->header.byte = 0;
        pFMT(pPubRel)->header.bits.type = PUBREL;
        pFMT(pPubRel)->header.bits.qos = 1;//default value
#else
        ALLOC0(pPubRel,PubRel)
        initHeader1(pPubRel,PUBREL)
#endif
        _step++;
        break;
    case PUBCOMP:
#if DEBUG
        _packet = (pPubComp)malloc(sizeof(PubComp));
        memset(_packet,0,sizeof(PubComp));
        pFMT(pPubComp)->header.byte = 0;
        pFMT(pPubComp)->header.bits.type = PUBCOMP;
#else
        ALLOC0(pPubComp,PubComp)
        initHeader0(pPubComp,PUBCOMP)
#endif
        _step++;
        break;
    case SUBSCRIBE:
#if DEBUG
        _packet = (pSubscribe)malloc(sizeof(Subscribe));
        memset(_packet,0,sizeof(Subscribe));
        pFMT(pSubscribe)->header.byte = 0;
        pFMT(pSubscribe)->header.bits.type = SUBSCRIBE;
        pFMT(pSubscribe)->header.bits.qos = 1;//default value
#else
        ALLOC0(pSubscribe,Subscribe)
        initHeader1(pSubscribe,SUBSCRIBE)
#endif
        _step++;
        break;
    case SUBACK:
#if DEBUG
        _packet = (pSubAck)malloc(sizeof(SubAck));
        memset(_packet,0,sizeof(SubAck));
        pFMT(pSubAck)->header.byte = 0;
        pFMT(pSubAck)->header.bits.type = SUBACK;
#else
        ALLOC0(pSubAck,SubAck)
        initHeader0(pSubAck,SUBACK)
#endif
        _step++;
        break;
    case UNSUBSCRIBE:
#if DEBUG
        _packet = (pUnsubscribe)malloc(sizeof(Unsubscribe));
        memset(_packet,0,sizeof(Unsubscribe));
        pFMT(pUnsubscribe)->header.byte = 0;
        pFMT(pUnsubscribe)->header.bits.type = UNSUBSCRIBE;
#else
        ALLOC0(pUnsubscribe,Unsubscribe)
        initHeader1(pUnsubscribe,UNSUBSCRIBE)
#endif
        _step++;
        break;
    case UNSUBACK:
#if DEBUG
        _packet = (pUnsubAck)malloc(sizeof(UnsubAck));
        memset(_packet,0,sizeof(UnsubAck));
        pFMT(pUnsubAck)->header.byte = 0;
        pFMT(pUnsubAck)->header.bits.type = UNSUBACK;
#else
        ALLOC0(pUnsubAck,UnsubAck)
        initHeader0(pUnsubAck,UNSUBACK)
#endif
        _step++;
        break;
    case PINGREQ:
#if DEBUG
        _packet = (pPingReq)malloc(sizeof(PingReq));
        memset(_packet,0,sizeof(PingReq));
        pFMT(pPingReq)->header.byte = 0;
        pFMT(pPingReq)->header.bits.type = PINGREQ;
#else
        ALLOC0(pPingReq,PingReq)
        initHeader0(pPingReq,PINGREQ)
#endif
        _step++;
        break;
    case PINGRESP:
#if DEBUG
        _packet = (pPingResp)malloc(sizeof(PingResp));
        memset(_packet,0,sizeof(PingResp));
        pFMT(pPingResp)->header.byte = 0;
        pFMT(pPingResp)->header.bits.type = PINGRESP;
#else
        ALLOC0(pPingResp,PingResp)
        initHeader0(pPingResp,PINGRESP)
#endif
        _step++;
        break;
    case DISCONNECT:
#if DEBUG
        _packet = (pDisconnect)malloc(sizeof(Disconnect));
        memset(_packet,0,sizeof(Disconnect));
        pFMT(pDisconnect)->header.byte = 0;
        pFMT(pDisconnect)->header.bits.type = DISCONNECT;
#else
        ALLOC0(pDisconnect,Disconnect)
        initHeader0(pDisconnect,DISCONNECT)
#endif
        _step++;
        break;
    default:
        printf("error packet type\n");
        break;
    }
    pFMT(pHeader)->bits.retain = _dried; // dried flag
    if(0 == _dried && OnlyHeader){
        _size += 1;
    }
    _size += 1;
}

MQTTPacket::~MQTTPacket()
{
    if(_packet){
        switch (_ptype)
        {
        case CONNECT:
            //if(pFMT(pConnect)->Protocol){
            //    free(pFMT(pConnect)->Protocol);
            //}
            if(pFMT(pConnect)->clientID){
                free(pFMT(pConnect)->clientID);
            }
            if(pFMT(pConnect)->willTopic){
                free(pFMT(pConnect)->willTopic);
            }
            if(pFMT(pConnect)->willMsg){
                free(pFMT(pConnect)->willMsg);
            }
            if(pFMT(pConnect)->userName){
                free(pFMT(pConnect)->userName);
            }
            if(pFMT(pConnect)->passwd){
                free(pFMT(pConnect)->passwd);
            }
//            MQDEL(pConnect, Protocol);
//            MQDEL(pConnect, clientID);
//            MQDEL(pConnect, willTopic);
//            MQDEL(pConnect, willMsg);
//            MQDEL(pConnect, userName);
//            MQDEL(pConnect, passwd);
            break;
        case CONNACK:
            if(pFMT(pConnAck)->clientID){
                free(pFMT(pConnAck)->clientID);
            }
//            MQDEL(pConnAck, clientID);
            break;
        case PUBLISH:
            if(pFMT(pPublish)->topic){
                free(pFMT(pPublish)->topic);
            }
//            MQDEL(pPublish, topic);
            if(pFMT(pPublish)->payload){
                free(pFMT(pPublish)->payload);
            }
//            MQDEL(pPublish, payload);
            break;
        case SUBSCRIBE:
            if(pFMT(pSubscribe)->topics){
                delete pFMT(pSubscribe)->topics;
            }
            if(pFMT(pSubscribe)->qoss){
                delete pFMT(pSubscribe)->qoss;
            }
            break;
        case SUBACK:
            if(pFMT(pSubAck)->qoss){
                delete pFMT(pSubAck)->qoss;
            }
            break;
        case UNSUBSCRIBE:
            if(pFMT(pUnsubscribe)->topics){
                delete pFMT(pUnsubscribe)->topics;
            }
            break;
        case UNSUBACK:
        case PINGREQ:
        case PINGRESP:
        case DISCONNECT:
        case PUBACK:
        case PUBREC:
        case PUBREL:
        case PUBCOMP:
            break;
        default:
            printf("error packet type\n");
            break;
        }
        free(_packet);
        _packet = NULL;
    }
}

std::ostream & operator<<(std::ostream &out, const MQTTPacket &mp)
{
    msgTypes ptype = (msgTypes)mp._ptype;
    ListSub* sublist = NULL;
    Subitor  itlist;
    ListQos* subqoss = NULL;
    Qositor  itqoss;
    out << "Packet Type:\t" << mp.packet_names[mp._ptype]
        << "["<< mp._ptype << "]\nPacket Size:\t" << mp._size
        << "\nPacket Dried:\t" << mp._dried;
    switch (ptype)
    {
    case CONNECT:
        out << "\nProtocol:\t" << MQTT_NAME << "\nversion:\t" << MQTT_VER
            << "\nKATIMEOUT:\t" << mp.KAT() << "\nclientID:\t" << mp.clientId()
            << "\nwillTopic:\t" << mp.willTopic() << "\nwillMsg:\t"
            << mp.willMsg() << "\nuserName:\t" << mp.username()
            << "\npassword:\t" << mp.password() << std::endl;
        break;
    case CONNACK:
        out << "\nReturn Code:\t" << mp.RC() << "\nclientId:\t"
            << mp.AnewClientId() << std::endl;
        break;
    case PUBLISH:
        out << "\ntopic:\t"  << mp.topic() << "\npayload:\t"
               << mp.s_payload() << std::endl;
        break;
    case PUBACK:
    case PUBREC:
    case PUBREL:
    case PUBCOMP:
    case UNSUBACK:
        out << "\npacketId:\t" << mp.packetId() << std::endl;
        break;
    case SUBSCRIBE:
        sublist = ((pSubscribe)(mp._packet))->topics;
        subqoss = ((pSubscribe)(mp._packet))->qoss;
        itlist = sublist->begin();
        itqoss = subqoss->begin();
        for(; itlist != sublist->end() && itqoss != subqoss->end(); ++itlist,++itqoss)
        {
            out << "\nSubscribe:\t" << itlist->_content << "\tsize:" << itlist->_size
                << "\nSubQos:\t" << (int)*itqoss;
        }
        break;
    case SUBACK:
        subqoss = ((pSubAck)(mp._packet))->qoss;
        itqoss = subqoss->begin();
        for(; itqoss != subqoss->end(); ++itqoss)
        {
            out << "\nSubAckQos:\t" << (int)*itqoss;
        }
        break;
    case UNSUBSCRIBE:
        sublist = ((pUnsubscribe)(mp._packet))->topics;
        itlist = sublist->begin();
        for(; itlist != sublist->end(); ++itlist)
        {
            out << "\nUnsubscribe:\t" << itlist->_content << "\tsize:" << itlist->_size;
        }
        break;
    case PINGREQ:
    case PINGRESP:
    case DISCONNECT:
        break;
    default:
        out << "error packet type\n";
        break;
    }
    return out << std::endl;
}

void MQTTPacket::setKAT(Int kat)
{
    assert(_ptype == CONNECT);
    /* KAT size */
    _size += sizeof(int16_t);
    _step++;
    pFMT(pConnect)->KAT = kat;
}

void MQTTPacket::setClientId(char* clientId, size_t size)
{
    if(_ptype == CONNECT){
        if(_dried){
            // clientIDlen is always 16 byte,so needn't record
            _size += 16;
            pFMT(pConnect)->clientIDlen = 16;
            MQNEW(pConnect,clientID,clientId,16);
        }else{
            // clientIDlen(2 byte) length size
            _size += (size+2);
            MQNEW(pConnect,clientID,clientId,size);
        }
        if(finish()){
            _size += MQTTInt::encode_len(_size-1);
        }
        _step++;
    }else if(_ptype == CONNACK){
        if(signOk()){
            //_step++;
            _size += 16;
            MQNEW(pConnAck,clientID,clientId,16);
            /* clientIDlen is 16, so needn't add 1 Byte to measure clientID */
        }
    }else{
        return;
    }
}

void MQTTPacket::setWill(char* willtopic, char* willmsg, size_t sizet, size_t sizem)
{
    assert(_ptype == CONNECT);
    if(pFMT(pConnect)->flags.bits.will){
        if(_dried){
            if(sizet > 0xff || sizem > 0xff){
                printf("willtopic or willmsg too long must smaller 256!\n");
                return;
            }
            _size += 2; //willTopiclen(1 byte) & willMsglen(1 byte) length size
        }else{
            _size += 4; //willTopiclen(2 byte) & willMsglen(2 byte) length size
        }
        _size += sizet;
        _size += sizem;
        pFMT(pConnect)->willTopiclen = sizet;
        MQNEW(pConnect,willTopic,willtopic,sizet);
        pFMT(pConnect)->willMsglen = sizem;
        MQNEW(pConnect,willMsg,willmsg,sizem);
    }
    _step += 2;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setUserName(char* userName, size_t size)
{
    assert(_ptype == CONNECT);
    if(pFMT(pConnect)->flags.bits.username){
        if(_dried){
            if(size > 0xff){
                printf("user name too long must smaller 256!\n");
                return;
            }
            _size++;    //userNamelen(1 byte) length size
        }else{
            _size += 2; //userNamelen(2 byte) length size
        }
        _size += size;
        pFMT(pConnect)->userNamelen = size;
        MQNEW(pConnect,userName,userName,size);
    }
    _step++;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setPasswd(char* passwd, size_t size)
{
    assert(_ptype == CONNECT);
    if(pFMT(pConnect)->flags.bits.password){
        if(_dried){
            if(size > 0xff){
                printf("password too long must smaller 256!\n");
                return;
            }
            _size++;    //passwdlen(1 byte) length size
        }else{
            _size += 2; //passwdlen(2 byte) length size
        }
        _size += size;
        pFMT(pConnect)->passwdlen = size;
        MQNEW(pConnect,passwd,passwd,size);
    }
    _step++;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setSignUp()
{
    assert(_ptype == CONNECT);
    _step++;
    pFMT(pConnect)->clientIDlen = 16;
    pFMT(pConnect)->clientID = 0;
    pFMT(pConnect)->flags.bits.isregister = 1;
    _size += 16;  // default clientID 16 byte
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setSignDel(char* clientId, size_t size)
{
    if(_ptype != CONNECT){
        printf("%s no clientId!\n", packet_names[_ptype]);
        return;
    }
    _step++;
    pFMT(pConnect)->clientIDlen = size;
    pFMT(pConnect)->clientID = clientId;
    pFMT(pConnect)->flags.bits.isregister = 0;
    _size += size;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setRC(char rc)
{
    if(_ptype != CONNACK){
        printf("%s no RC!\n", packet_names[_ptype]);
        return;
    }
    _size += 1;
    _step++;
    pFMT(pConnAck)->rc = rc;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setFlags(MQ_byte flags)
{
    if(!HasFlags){
        printf("%s no flags!\n", packet_names[_ptype]);
        return;
    }
    _size++;
    _step++;
    switch (_ptype) {
    case CONNECT:
        pFMT(pConnect)->flags.all = flags;
        break;
    case CONNACK:
        pFMT(pConnAck)->flags.all = flags;
        break;
    default:
        break;
    }
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::addTopics(char qos, char* content, size_t size)
{
    switch (_ptype) {
    case PUBLISH:
        pFMT(pPublish)->topiclen = size;
        MQNEW(pPublish,topic,content,size);
        _size += size;
        break;
    case SUBSCRIBE:
        /* topics length's size */
        if(_dried){
            _size++;     // 1 byte
        }else{
            _size += 2;  // 2 byte
        }
        if(NULL == pFMT(pSubscribe)->topics){
            pFMT(pSubscribe)->topics = new ListSub();
        }
        if(NULL == pFMT(pSubscribe)->qoss){
            pFMT(pSubscribe)->qoss = new ListQos();
        }
        (pFMT(pSubscribe)->topics)->push_back(sub_t(size,content));
        _size += size;
        (pFMT(pSubscribe)->qoss)->push_back(qos);
        /* qos size 1 byte */
        _size++;
        break;
    case SUBACK:
        /* topics length's size */
        if(NULL == pFMT(pSubAck)->qoss){
            pFMT(pSubAck)->qoss = new ListQos();
        }
        (pFMT(pSubAck)->qoss)->push_back(qos);
        /* qos size 1 byte */
        _size++;
        break;
    case UNSUBSCRIBE:
        /* topics length's size */
        if(_dried){
            _size++;     // 1 byte
        }else{
            _size += 2;  // 2 byte
        }
        if(NULL == pFMT(pUnsubscribe)->topics){
            pFMT(pUnsubscribe)->topics = new ListSub();
        }
        (pFMT(pUnsubscribe)->topics)->push_back(sub_t(size,content));
        _size += size;
        break;
    default:
        printf("%s no topic!\n", packet_names[_ptype]);
        return;
        break;
    }
    _step++;
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setPayload(char* payload, size_t size)
{
    if(_ptype != PUBLISH){
        printf("%s no topic!\n", packet_names[_ptype]);
        return;
    }
    _size += size;
    _step++;
    pFMT(pPublish)->payloadlen = size;
    MQNEW(pPublish,payload,payload,size);
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

void MQTTPacket::setPacketId(int packetId)
{
    assert(HasPktId);
    _size += sizeof(int16_t); // packetId's size
    _step++;
    switch (_ptype) {
    case PUBLISH://QoS > 0
        pFMT(pPublish)->packetId = packetId;
        break;
    case PUBACK :
        pFMT(pPubAck)->packetId = packetId;
        break;
    case  PUBREC:
        pFMT(pPubRec)->packetId = packetId;
        break;
    case  PUBREL:
        pFMT(pPubRel)->packetId = packetId;
        break;
    case  PUBCOMP:
        pFMT(pPubComp)->packetId = packetId;
        break;
    case  SUBSCRIBE:
        pFMT(pSubscribe)->packetId = packetId;
        break;
    case  SUBACK:
        pFMT(pSubAck)->packetId = packetId;
        break;
    case  UNSUBSCRIBE:
        pFMT(pUnsubscribe)->packetId = packetId;
        break;
    case  UNSUBACK:
        pFMT(pUnsubAck)->packetId = packetId;
        break;
    default:
        break;
    }
    if(finish()){
        /* add space to save Remaining Length's size */
        _size += MQTTInt::encode_len(_size-1);
    }
}

bool MQTTPacket::encode(char* packet)
{
    if(NULL == packet){
        printf("packet is not a enough memory!\n");
        return false;
    }
    int     cursor = 0;            /* record byte stream current's position */
    int16_t packetId = 0;          /* use to save 2 byte length packet id */
    int16_t commonshort = 0;       /* use to save 2 byte length while _dried == 0 */
    char    commonchar = 0;        /* use to save 1 byte length while _dried == 1 */

    /* use at ptype = SUBSCRIBE SUBACK */
    ListSub* sublist;
    Subitor itlist;
    ListQos* subqoss;
    Qositor itqoss;

    /* part-1 fixed header */
    packet[cursor++] = pFMT(pHeader)->byte;

    /* part-2 Remaining Length: packet size cannot !!! */
    if(CannotDried){
        /* add packet's size after encode, size MQTTInt::encode's return */
        cursor += MQTTInt::encode(&packet[cursor], _size-1);
    }else{
        if(!_dried){
            if(OnlyHeader){
                /* Only Header, RL == 0 */
                packet[cursor++] = 0 + 1;
            }else{
                /* fix RL, RL == 2 */
                if(CONNACK == _ptype){
                    packet[cursor++] = 2 + 1 + pFMT(pConnAck)->clientIDlen;
                }else{
                    packet[cursor++] = 2 + 1;
                }
            }
        }else{
            //1. OnlyHeader: only fix header, delete 1-byte RL
            //2. FixRL:  fix 1-byte RL type, delete 1-byte RL
            if(OnlyHeader){
                /* Only Header, RL == 0 */
                packet[cursor++] = 0 + 1;
            }else{
                /* fix RL, RL == 2 */
                if(CONNACK == _ptype){
                    packet[cursor++] = 2 + 1 + pFMT(pConnAck)->clientIDlen;
                }else{
                    packet[cursor++] = 2 + 1;
                }
            }
        }
    }

    /* part-3 Variable header & payload */
    switch (_ptype)
    {
    case PUBLISH:// TODO
        /* Variable header */
        /* topic name */
        if(_dried){
            /* topic name's size 1 byte */
            commonchar = (char)pFMT(pPublish)->topiclen;
            memcpy(&packet[cursor++], &commonchar, 1);
            /* topic name's content */
            memcpy(&packet[cursor], pFMT(pPublish)->topic, commonchar);
            cursor += commonchar;
        }else{
            /* topic name's size 2 byte */
            commonshort = (int16_t)pFMT(pPublish)->topiclen;
            memcpy(&packet[cursor], &commonshort, 2);
            cursor += 2;
            /* topic name's content */
            memcpy(&packet[cursor], pFMT(pPublish)->topic, commonshort);
            cursor += commonshort;
        }
        /* packet ID qos not 0 */
        if(0 != pFMT(pHeader)->bits.qos){
            packetId = (int16_t)pFMT(pPublish)->packetId;
            memcpy(&packet[cursor++], &packetId, 2);
            // itoa((int16_t)pFMT(pPubAck)->packetId,&packet[cursor++],10);
        }
        /* payload qos, NOTE: payloadlen is not save at packet data, can use RL calculation while decode */
        commonshort = pFMT(pPublish)->payloadlen;
        memcpy(&packet[cursor], pFMT(pPublish)->payload , commonshort);
        cursor += commonshort;
        break;
    case SUBSCRIBE:// TODO
        /* Variable header */
        /* packet ID */
        packetId = (int16_t)pFMT(pSubscribe)->packetId;
        memcpy(&packet[cursor], (char*)&packetId, 2);
        cursor += 2;
        /* payload */
        /* List of topic and qos */
        sublist = pFMT(pSubscribe)->topics;
        subqoss = pFMT(pSubscribe)->qoss;
        itlist = sublist->begin();
        itqoss = subqoss->begin();
        if(_dried){
            for(; itlist != sublist->end() && itqoss != subqoss->end(); ++itlist,++itqoss)
            {
                /* each topic's size 1 byte */
                commonchar = (char)(itlist->_size);
                memcpy(&packet[cursor++], &commonchar, 1);
                /* each topic's content */
                memcpy(&packet[cursor], itlist->_content,commonchar);
                cursor += commonchar;
                /* each qos's */
                packet[cursor++] = *itqoss;
            }
        }else{
            for(; itlist != sublist->end() && itqoss != subqoss->end(); ++itlist,++itqoss)
            {
                /* each topic's size 2 byte */
                commonshort = (int16_t)(itlist->_size);
                memcpy(&packet[cursor], &commonshort, 2);
                cursor += 2;
                /* each topic's content */
                memcpy(&packet[cursor], itlist->_content,commonshort);
                cursor += commonshort;
                /* each qos's */
                packet[cursor++] = *itqoss;
            }
        }
        break;
    case SUBACK:// TODO
        /* Variable header */
        /* packet ID */
        packetId = (int16_t)pFMT(pSubAck)->packetId;
        memcpy(&packet[cursor], (char*)&packetId, 2);
        cursor += 2;
        /* payload */
        /* List of subscribe return qos */
        subqoss = pFMT(pSubAck)->qoss;
        itqoss = subqoss->begin();
        for(; itqoss != subqoss->end();++itqoss)
        {
            /* each qos's */
            packet[cursor++] = *itqoss;
        }
        break;
    case CONNECT:// TODO
        /* Variable header */
        /* add CONNECT Variable header, size (2-byte)*/
        packet[cursor++] = 0;
        packet[cursor++] = 4;
        /* add CONNECT MQTT Protocol, size(4-byte) */
        memcpy(&packet[cursor], pFMT(pConnect)->Protocol,4);
        cursor += 4;
        /* add CONNECT MQTT version, size(1-byte) */
        packet[cursor++] = pFMT(pConnect)->version;
        /* add CONNECT flags, size(1-byte) */
        packet[cursor++] = pFMT(pConnect)->flags.all;
        /* add CONNECT KAT, size(2-byte) */
        memcpy(&packet[cursor], &pFMT(pConnect)->KAT,2);
        cursor += 2;
        /* payload */        
        if (_dried){
            /* 1. client ID */
            memcpy(&packet[cursor], pFMT(pConnect)->clientID, pFMT(pConnect)->clientIDlen);
            // memcpy(&packet[cursor], &pFMT(pConnect)->clientID, 16);
            cursor += pFMT(pConnect)->clientIDlen;
            if(pFMT(pConnect)->flags.bits.will){
                /* 2. Will Topic */
                /* Will Topic's size 1 byte */
                commonchar = (char)pFMT(pConnect)->willTopiclen;
                memcpy(&packet[cursor++], &commonchar, 1);
                /* Will Topic's content */
                memcpy(&packet[cursor], pFMT(pConnect)->willTopic, commonchar);
                cursor += commonchar;
                /* 3. Will message */
                /* Will message's size 1 byte */
                commonchar = (char)pFMT(pConnect)->willMsglen;
                memcpy(&packet[cursor++], &commonchar, 1);
                /* Will message's content */
                memcpy(&packet[cursor], pFMT(pConnect)->willMsg, commonchar);
                cursor += commonchar;
            }
            if(pFMT(pConnect)->flags.bits.username){
                /* 4. User Name */
                /* UserName's size 1 byte */
                commonchar = (char)pFMT(pConnect)->userNamelen;
                memcpy(&packet[cursor++], &commonchar, 1);
                /* UserName's content */
                memcpy(&packet[cursor], pFMT(pConnect)->userName, commonchar);
                cursor += commonchar;
                if(pFMT(pConnect)->flags.bits.password){
                    /* 5. password */
                    /* password's size 1 byte */
                    commonchar = (char)pFMT(pConnect)->passwdlen;
                    memcpy(&packet[cursor++], &commonchar, 1);
                    /* password's content */
                    memcpy(&packet[cursor], pFMT(pConnect)->passwd, commonchar);
                    cursor += commonchar;
                }
            }
        }else{
            // TODO
            /* 1. client ID */
            /* clientIDlen size (2 byte) */
            commonshort = (int16_t)pFMT(pConnect)->clientIDlen;
            memcpy(&packet[cursor], &commonshort, 2);
            cursor += 2;
            /* clientID's content */
            memcpy(&packet[cursor], pFMT(pConnect)->clientID, commonshort);
            cursor += commonshort;
            if(pFMT(pConnect)->flags.bits.will){
                /* 2. Will Topic */
                commonshort = (int16_t)pFMT(pConnect)->willTopiclen;
                memcpy(&packet[cursor], &commonshort, 2);
                /* willTopiclen size (2 byte) */
                cursor += 2;
                /* Will Topic's content */
                memcpy(&packet[cursor], pFMT(pConnect)->willTopic, commonshort);
                cursor += commonshort;
                /* 3. Will message */
                commonshort = (int16_t)pFMT(pConnect)->willMsglen;
                memcpy(&packet[cursor], &commonshort, 2);
                /* willMsglen size (2 byte) */
                cursor += 2;
                /* Will message's content */
                memcpy(&packet[cursor], pFMT(pConnect)->willMsg,commonshort);
                cursor += commonshort;
            }
            if(pFMT(pConnect)->flags.bits.username){
                /* 4. User Name */
                commonshort = (int16_t)pFMT(pConnect)->userNamelen;
                memcpy(&packet[cursor], &commonshort, 2);
                /* userNamelen size (2 byte) */
                cursor += 2;
                /* UserName's content */
                memcpy(&packet[cursor], pFMT(pConnect)->userName,commonshort);
                cursor += commonshort;
                if(pFMT(pConnect)->flags.bits.password){
                    /* 5. password */
                    commonshort = (int16_t)pFMT(pConnect)->passwdlen;
                    memcpy(&packet[cursor], &commonshort, 2);
                    /* passwdlen size (2 byte) */
                    cursor += 2;
                    /* password's content */
                    memcpy(&packet[cursor], pFMT(pConnect)->passwd,commonshort);
                    cursor += commonshort;
                }
            }
        }
        break;
    case CONNACK:
        /* Variable header */
         packet[cursor++] = pFMT(pConnAck)->flags.all;
         packet[cursor++] = pFMT(pConnAck)->rc;
         /* payload */
         if(signOk()){
             /* 1. client ID */
             memcpy(&packet[cursor], pFMT(pConnAck)->clientID, pFMT(pConnAck)->clientIDlen);
             // memcpy(&packet[cursor], &pFMT(pConnAck)->clientID, 16);
             cursor += pFMT(pConnAck)->clientIDlen;
         }
        break;
    case PUBACK:
    case PUBREC:
    case PUBREL:
    case PUBCOMP:
    case UNSUBACK:
        /* Variable header */
        /* packet ID */
        packetId = (int16_t)pFMT(pAck)->packetId;
        memcpy(&packet[cursor], (char*)&packetId, 2);
        // itoa((int16_t)pFMT(pPubAck)->packetId,&packet[cursor++],10);
        cursor += 2;
        break;
    case UNSUBSCRIBE:// TODO
        /* Variable header */
        /* packet ID */
        packetId = (int16_t)pFMT(pUnsubscribe)->packetId;
        memcpy(&packet[cursor], (char*)&packetId, 2);
        cursor += 2;
        // itoa((int16_t)pFMT(pPubAck)->packetId,&packet[cursor++],10);
        /* payload */
        /* List of unsubscribe topic*/
        sublist = pFMT(pUnsubscribe)->topics;
        itlist = sublist->begin();
        if(_dried){
            for(; itlist != sublist->end(); ++itlist)
            {
                /* each topic's size 1 byte */
                commonchar = (char)(itlist->_size);
                memcpy(&packet[cursor++], &commonchar, 1);
                /* each topic's content */
                memcpy(&packet[cursor], itlist->_content,commonchar);
                cursor += commonchar;
            }
        }else{
            for(; itlist != sublist->end(); ++itlist)
            {
                /* each topic's size 2 byte */
                commonshort = (int16_t)(itlist->_size);
                memcpy(&packet[cursor], &commonshort, 2);
                cursor += 2;
                /* each topic's content */
                memcpy(&packet[cursor], itlist->_content,commonshort);
                cursor += commonshort;
            }
        }
        break;
    case PINGREQ:
    case PINGRESP:
    case DISCONNECT:
        printf("packet type don't have Variable header && payload!\n");
        break;
    default:
        printf("error packet type\n");
        break;
    }
    return true;
}

int   MQTTPacket::decode(char* packet)
{
    if(NULL == packet || NULL ==  _packet){
        return 0;
    }
    Header fixhead;
    int    cursor = 0;           /* record byte stream current's position */
    int    rlSize = 0;           /* Remaining Length + Remaining Length's size */
    int    payloadSize = 0;      /* payload size if payload is exist */
    int    commonshort = 0;      /* use to save 2 byte length while _dried == 0 */
    int    commonchar  = 0;

    /* use at ptype = SUBSCRIBE SUBACK */
    char*  content = NULL;

    /* part-1 fixed header */
    fixhead.byte = packet[cursor++];
    pFMT(pHeader)->byte = fixhead.byte;
    _dried = fixhead.bits.retain;
    _ptype = fixhead.bits.type;
    _step  = 1;

    /* part-2  Remaining Length: packet size */
    int  prefixByte = 0;         /* save a content size's byte */
    int16_t  packetID = 0;
    if(CannotDried){
        rlSize = MQTTInt::decode(&packet[cursor],prefixByte);
        _size = rlSize + 1; /* 1 is fix header's size */
        cursor += prefixByte;
    }else{
        if(!_dried){
            if(OnlyHeader){
                /* Only Header, RL == 0 + RL'size(1 byte) */
                _size = packet[cursor++];
            }else{
                /* fix RL, RL == 2 + RL'size(1 byte) */
                _size = packet[cursor++];
            }
            _size++; /* 1 is fix header's size */
        }
        else{
            //1. OnlyHeader: only fix header, delete 1-byte RL value = 0
            //2. FixRL:  fix 1-byte RL type, delete 1-byte RL value = 2
            _size = packet[cursor++] + 1;
        }
    }
    _step++;

    /* part-3 Variable header & payload */
    switch (_ptype)
    {
    case PUBLISH:
        /* Variable header */
        /* topic name */
        if(_dried){
            /* topic name  */
            pFMT(pPublish)->topiclen = packet[cursor++];
            MQNEW(pPublish,topic,&packet[cursor],pFMT(pPublish)->topiclen);
            cursor += pFMT(pPublish)->topiclen;
            _step++;
        }else{
            /* topic name's size(2 byte) */
            memcpy(&commonshort,&packet[cursor],2);
            pFMT(pPublish)->topiclen = commonshort;
            cursor += 2;
            /* topic name's content */
            MQNEW(pPublish,topic,&packet[cursor],pFMT(pPublish)->topiclen);
            cursor += commonshort;
            _step++;
        }
        /* packet ID qos not 0 */
        if(0 != pFMT(pHeader)->bits.qos){
            memcpy(&packetID,&packet[cursor],2);
            pFMT(pPublish)->packetId = packetID;
            cursor += 2;
            _step++;
        }
        /* payload qos */
        payloadSize = _size - cursor;
        pFMT(pPublish)->payloadlen = payloadSize;
        MQNEW(pPublish,payload,&packet[cursor],pFMT(pPublish)->payloadlen);
        cursor += payloadSize;
        _step++;
        break;
    case SUBSCRIBE:
        /* Variable header */
        /* packet ID */
        memcpy(&packetID,&packet[cursor],2);
        pFMT(pSubscribe)->packetId = packetID;
        cursor += 2;
        /* payload */
        /* List of topic and qos */
        payloadSize = rlSize - cursor;
        pFMT(pSubscribe)->topics = new ListSub();
        pFMT(pSubscribe)->qoss = new ListQos();
        if(_dried){
            while(cursor <= rlSize)
            {
                /* each topic's size */
                commonchar = packet[cursor++];
                content = (char*)malloc(commonchar);
                memcpy(content,&packet[cursor],commonchar);
                cursor += commonchar;
                (pFMT(pSubscribe)->topics)->push_back(sub_s(commonchar,content));
                free(content);
                /* each qos's */
                (pFMT(pSubscribe)->qoss)->push_back(packet[cursor++]);
            }
        }else{
            while(cursor <= rlSize)
            {
                /* each topic's size */
                memcpy(&commonshort,&packet[cursor],2);
                cursor += 2;
                content = (char*)malloc(commonshort);
                memcpy(content,&packet[cursor],commonshort);
                cursor += commonshort;
                (pFMT(pSubscribe)->topics)->push_back(sub_s(commonshort,content));
                free(content);
                /* each qos's */
                (pFMT(pSubscribe)->qoss)->push_back(packet[cursor++]);
            }
        }
        break;
    case SUBACK:
        /* Variable header */
        /* packet ID */
        memcpy(&packetID,&packet[cursor],2);
        pFMT(pSubAck)->packetId = packetID;
        cursor += 2;
        /* payload */
        /* List of subscribe return qos */
        pFMT(pSubAck)->qoss = new ListQos();
        payloadSize = rlSize - cursor;
        while(cursor <= rlSize)
        {
            /* each qos's */
            (pFMT(pSubAck)->qoss)->push_back(packet[cursor++]);
        }
        break;
    case CONNECT:
        /* Variable header */
        /* add CONNECT Variable header, size (2-byte)*/
        /* packet[cursor++] = 0;
           packet[cursor++] = 4; */
        cursor += 2;
        /* add CONNECT MQTT Protocol, size(4-byte) */
        pFMT(pConnect)->Protocol = MQTT_NAME;
        //MQNEW(pConnect,Protocol,&packet[cursor],4);
        cursor += 4;
        /* add CONNECT MQTT version, size(1-byte) */
        pFMT(pConnect)->version = packet[cursor++];
        /* add CONNECT flags, size(1-byte) */
        pFMT(pConnect)->flags.all = packet[cursor++];
        /* add CONNECT KAT, size(2-byte) */
        memcpy(&pFMT(pConnect)->KAT,&packet[cursor],2);
        cursor += 2;
        _step += 4;
        //pFMT(pConnect)->KAT = atoi(packetId);
        /* payload */
        if (_dried){
            /* 1. client ID */
            pFMT(pConnect)->clientIDlen = 16;
            MQNEW(pConnect,clientID,&packet[cursor],16);
            cursor += 16;
            _step++;
            if(pFMT(pConnect)->flags.bits.will){
                /* 2. Will Topic */
                pFMT(pConnect)->willTopiclen = packet[cursor++];
                MQNEW(pConnect,willTopic,&packet[cursor],pFMT(pConnect)->willTopiclen);
                cursor += pFMT(pConnect)->willTopiclen;
                _step++;
                /* 3. Will message */
                pFMT(pConnect)->willMsglen = packet[cursor++];
                MQNEW(pConnect,willMsg,&packet[cursor],pFMT(pConnect)->willMsglen);
                cursor += pFMT(pConnect)->willMsglen;
                _step += 2;
            }
            if(pFMT(pConnect)->flags.bits.username){
                /* 4. User Name */
                pFMT(pConnect)->userNamelen = packet[cursor++];
                MQNEW(pConnect,userName,&packet[cursor],pFMT(pConnect)->userNamelen);
                cursor += pFMT(pConnect)->userNamelen;
                _step++;
                if(pFMT(pConnect)->flags.bits.password){
                    /* 5. password */
                    pFMT(pConnect)->passwdlen = packet[cursor++];
                    MQNEW(pConnect,passwd,&packet[cursor],pFMT(pConnect)->passwdlen);
                    cursor += pFMT(pConnect)->passwdlen;
                    _step++;
                }
            }
        }else{
            // TODO
            /* 1. client ID */
            /* clientIdlen(2 byte) size */
            memcpy(&commonshort,&packet[cursor],2);
            pFMT(pConnect)->clientIDlen = commonshort;
            cursor += 2;
            MQNEW(pConnect, clientID,&packet[cursor],pFMT(pConnect)->clientIDlen);
            cursor += pFMT(pConnect)->clientIDlen;
            _step++;
            if(pFMT(pConnect)->flags.bits.will){
                /* 2. Will Topic */
                /* willTopiclen(2 byte) size */
                memcpy(&commonshort,&packet[cursor],2);
                pFMT(pConnect)->willTopiclen = commonshort;
                cursor += 2;
                MQNEW(pConnect,willTopic,&packet[cursor],pFMT(pConnect)->willTopiclen);
                cursor += pFMT(pConnect)->willTopiclen;
                _step++;
                /* 3. Will message */
                /* willMsglen(2 byte) size */
                memcpy(&commonshort,&packet[cursor],2);
                pFMT(pConnect)->willMsglen = commonshort;
                cursor += 2;
                MQNEW(pConnect,willMsg,&packet[cursor],pFMT(pConnect)->willMsglen);
                cursor += pFMT(pConnect)->willMsglen;
                _step++;
            }
            if(pFMT(pConnect)->flags.bits.username){
                /* 4. User Name */
                /* userNamelen(2 byte) size */
                memcpy(&commonshort,&packet[cursor],2);
                pFMT(pConnect)->userNamelen = commonshort;
                cursor += 2;
                MQNEW(pConnect,userName,&packet[cursor],pFMT(pConnect)->userNamelen);
                cursor += pFMT(pConnect)->userNamelen;
                _step++;
                if(pFMT(pConnect)->flags.bits.password){
                    /* 5. password */
                    /* userNamelen(2 byte) size */
                    memcpy(&commonshort,&packet[cursor],2);
                    pFMT(pConnect)->passwdlen = commonshort;
                    cursor += 2;
                    MQNEW(pConnect,passwd,&packet[cursor],pFMT(pConnect)->passwdlen);
                    cursor += pFMT(pConnect)->passwdlen;
                    _step++;
                }
            }
        }
        break;
    case CONNACK:
        /* Variable header */
        pFMT(pConnAck)->flags.all = packet[cursor++];
        pFMT(pConnAck)->rc = packet[cursor++];
        /* payload */
        if(signOk()){
            /* 1. client ID */
            pFMT(pConnAck)->clientIDlen = 16;
            MQNEW(pConnAck,clientID,&packet[cursor],16);
            cursor += 16;
        }
        break;
    case PUBACK:
    case PUBREC:
    case PUBREL:
    case PUBCOMP:
    case UNSUBACK:
        /* Variable header */
        /* packet ID */
        if (!_dried){
            cursor++;    // Remaining Length's size
        }
        memcpy(&packetID,&packet[cursor],2);
        pFMT(pAck)->packetId = packetID;
        cursor += 2; // packetId's size
        break;
    case UNSUBSCRIBE:
        /* Variable header */
        /* packet ID */
        memcpy(&packetID,&packet[cursor],2);
        pFMT(pUnsubscribe)->packetId = packetID;
        cursor += 2;
        /* payload */
        /* List of unsubscribe topic*/
        payloadSize = rlSize - cursor;
        pFMT(pUnsubscribe)->topics = new ListSub();
        if(_dried){
            while(cursor <= rlSize)
            {
                /* each topic's size */
                commonchar = packet[cursor++];
                content = (char*)malloc(commonchar);
                memcpy(content,&packet[cursor],commonchar);
                cursor += commonchar;
                (pFMT(pUnsubscribe)->topics)->push_back(sub_s(commonchar,content));
                free(content);
            }
        }else{
            while(cursor <= rlSize)
            {
                /* each topic's size */
                memcpy(&commonshort,&packet[cursor],2);
                cursor += 2;
                content = (char*)malloc(commonshort);
                memcpy(content,&packet[cursor],commonshort);
                cursor += commonshort;
                (pFMT(pUnsubscribe)->topics)->push_back(sub_s(commonshort,content));
                free(content);
            }
        }
        break;
    case PINGREQ:
    case PINGRESP:
    case DISCONNECT:
        printf("packet type don't have Variable header && payload!\n");
        break;
    default:
        printf("error packet type\n");
        break;
    }
    return _size;
}

}//namespace mqtter
