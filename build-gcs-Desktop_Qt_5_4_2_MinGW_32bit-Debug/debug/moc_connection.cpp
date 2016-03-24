/****************************************************************************
** Meta object code from reading C++ file 'connection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gcs/connection/include/connection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Connection_t {
    QByteArrayData data[16];
    char stringdata[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Connection_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Connection_t qt_meta_stringdata_Connection = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Connection"
QT_MOC_LITERAL(1, 11, 9), // "connected"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "disconnected"
QT_MOC_LITERAL(4, 35, 13), // "valueReceived"
QT_MOC_LITERAL(5, 49, 5), // "Value"
QT_MOC_LITERAL(6, 55, 19), // "valueVectorReceived"
QT_MOC_LITERAL(7, 75, 11), // "ValueVector"
QT_MOC_LITERAL(8, 87, 15), // "settingReceived"
QT_MOC_LITERAL(9, 103, 11), // "std::string"
QT_MOC_LITERAL(10, 115, 14), // "settingRemoved"
QT_MOC_LITERAL(11, 130, 25), // "userCodeRunStatusReceived"
QT_MOC_LITERAL(12, 156, 6), // "status"
QT_MOC_LITERAL(13, 163, 11), // "parseSerial"
QT_MOC_LITERAL(14, 175, 15), // "firmwareConnect"
QT_MOC_LITERAL(15, 191, 18) // "firmwareDisconnect"

    },
    "Connection\0connected\0\0disconnected\0"
    "valueReceived\0Value\0valueVectorReceived\0"
    "ValueVector\0settingReceived\0std::string\0"
    "settingRemoved\0userCodeRunStatusReceived\0"
    "status\0parseSerial\0firmwareConnect\0"
    "firmwareDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Connection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    2,   66,    2, 0x06 /* Public */,
       6,    4,   71,    2, 0x06 /* Public */,
       8,    2,   80,    2, 0x06 /* Public */,
      10,    1,   85,    2, 0x06 /* Public */,
      11,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   91,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Double,    2,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,    2,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::Bool,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Connection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Connection *_t = static_cast<Connection *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->valueReceived((*reinterpret_cast< Value(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->valueVectorReceived((*reinterpret_cast< ValueVector(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 4: _t->settingReceived((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 5: _t->settingRemoved((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->userCodeRunStatusReceived((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->parseSerial((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 8: _t->firmwareConnect(); break;
        case 9: _t->firmwareDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Connection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::connected)) {
                *result = 0;
            }
        }
        {
            typedef void (Connection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::disconnected)) {
                *result = 1;
            }
        }
        {
            typedef void (Connection::*_t)(Value , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::valueReceived)) {
                *result = 2;
            }
        }
        {
            typedef void (Connection::*_t)(ValueVector , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::valueVectorReceived)) {
                *result = 3;
            }
        }
        {
            typedef void (Connection::*_t)(std::string , std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::settingReceived)) {
                *result = 4;
            }
        }
        {
            typedef void (Connection::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::settingRemoved)) {
                *result = 5;
            }
        }
        {
            typedef void (Connection::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::userCodeRunStatusReceived)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject Connection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Connection.data,
      qt_meta_data_Connection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Connection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Connection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Connection.stringdata))
        return static_cast<void*>(const_cast< Connection*>(this));
    return QObject::qt_metacast(_clname);
}

int Connection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Connection::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Connection::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Connection::valueReceived(Value _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Connection::valueVectorReceived(ValueVector _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Connection::settingReceived(std::string _t1, std::string _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Connection::settingRemoved(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Connection::userCodeRunStatusReceived(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
