/****************************************************************************
** Meta object code from reading C++ file 'BackendInterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BackendInterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BackendInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackendInterface_t {
    QByteArrayData data[13];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackendInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackendInterface_t qt_meta_stringdata_BackendInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BackendInterface"
QT_MOC_LITERAL(1, 17, 16), // "responseReceived"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "response"
QT_MOC_LITERAL(4, 44, 23), // "connectionStatusChanged"
QT_MOC_LITERAL(5, 68, 9), // "connected"
QT_MOC_LITERAL(6, 78, 13), // "errorOccurred"
QT_MOC_LITERAL(7, 92, 5), // "error"
QT_MOC_LITERAL(8, 98, 11), // "onConnected"
QT_MOC_LITERAL(9, 110, 14), // "onDisconnected"
QT_MOC_LITERAL(10, 125, 11), // "onReadyRead"
QT_MOC_LITERAL(11, 137, 7), // "onError"
QT_MOC_LITERAL(12, 145, 30) // "QLocalSocket::LocalSocketError"

    },
    "BackendInterface\0responseReceived\0\0"
    "response\0connectionStatusChanged\0"
    "connected\0errorOccurred\0error\0onConnected\0"
    "onDisconnected\0onReadyRead\0onError\0"
    "QLocalSocket::LocalSocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackendInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,
      10,    0,   60,    2, 0x08 /* Private */,
      11,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    7,

       0        // eod
};

void BackendInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackendInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->responseReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 1: _t->connectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onConnected(); break;
        case 4: _t->onDisconnected(); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->onError((*reinterpret_cast< QLocalSocket::LocalSocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackendInterface::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackendInterface::responseReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackendInterface::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackendInterface::connectionStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackendInterface::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackendInterface::errorOccurred)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackendInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BackendInterface.data,
    qt_meta_data_BackendInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackendInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackendInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackendInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackendInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BackendInterface::responseReceived(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BackendInterface::connectionStatusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BackendInterface::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
