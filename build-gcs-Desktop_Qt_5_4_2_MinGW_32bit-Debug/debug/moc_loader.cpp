/****************************************************************************
** Meta object code from reading C++ file 'loader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gcs/board/include/loader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Loader_t {
    QByteArrayData data[11];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Loader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Loader_t qt_meta_stringdata_Loader = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Loader"
QT_MOC_LITERAL(1, 7, 7), // "success"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 5), // "error"
QT_MOC_LITERAL(4, 22, 5), // "start"
QT_MOC_LITERAL(5, 28, 10), // "selectFile"
QT_MOC_LITERAL(6, 39, 7), // "process"
QT_MOC_LITERAL(7, 47, 3), // "end"
QT_MOC_LITERAL(8, 51, 7), // "receive"
QT_MOC_LITERAL(9, 59, 4), // "data"
QT_MOC_LITERAL(10, 64, 4) // "test"

    },
    "Loader\0success\0\0error\0start\0selectFile\0"
    "process\0end\0receive\0data\0test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Loader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void,

       0        // eod
};

void Loader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Loader *_t = static_cast<Loader *>(_o);
        switch (_id) {
        case 0: _t->success(); break;
        case 1: _t->error(); break;
        case 2: _t->start(); break;
        case 3: _t->selectFile(); break;
        case 4: _t->process(); break;
        case 5: _t->end(); break;
        case 6: _t->receive((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->test(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::success)) {
                *result = 0;
            }
        }
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Loader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Loader.data,
      qt_meta_data_Loader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Loader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Loader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Loader.stringdata))
        return static_cast<void*>(const_cast< Loader*>(this));
    return QObject::qt_metacast(_clname);
}

int Loader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Loader::success()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Loader::error()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
