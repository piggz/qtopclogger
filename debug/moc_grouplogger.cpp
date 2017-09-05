/****************************************************************************
** Meta object code from reading C++ file 'grouplogger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../grouplogger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grouplogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GroupLogger_t {
    QByteArrayData data[15];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GroupLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GroupLogger_t qt_meta_stringdata_GroupLogger = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GroupLogger"
QT_MOC_LITERAL(1, 12, 14), // "loggingChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 1), // "l"
QT_MOC_LITERAL(4, 30, 14), // "logPathChanged"
QT_MOC_LITERAL(5, 45, 1), // "p"
QT_MOC_LITERAL(6, 47, 7), // "newData"
QT_MOC_LITERAL(7, 55, 4), // "data"
QT_MOC_LITERAL(8, 60, 13), // "fileWriteTime"
QT_MOC_LITERAL(9, 74, 8), // "addGroup"
QT_MOC_LITERAL(10, 83, 9), // "groupName"
QT_MOC_LITERAL(11, 93, 10), // "expression"
QT_MOC_LITERAL(12, 104, 4), // "tags"
QT_MOC_LITERAL(13, 109, 7), // "logging"
QT_MOC_LITERAL(14, 117, 7) // "logPath"

    },
    "GroupLogger\0loggingChanged\0\0l\0"
    "logPathChanged\0p\0newData\0data\0"
    "fileWriteTime\0addGroup\0groupName\0"
    "expression\0tags\0logging\0logPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GroupLogger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x0a /* Public */,
       8,    0,   48,    2, 0x0a /* Public */,
       9,    3,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariantMap,    7,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QStringList,   10,   11,   12,

 // properties: name, type, flags
      13, QMetaType::Bool, 0x00495103,
      14, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void GroupLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GroupLogger *_t = static_cast<GroupLogger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loggingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->logPathChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->newData((*reinterpret_cast< QMap<QString,QVariant>(*)>(_a[1]))); break;
        case 3: { int _r = _t->fileWriteTime();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->addGroup((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GroupLogger::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupLogger::loggingChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GroupLogger::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupLogger::logPathChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        GroupLogger *_t = static_cast<GroupLogger *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->logging(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->logPath(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        GroupLogger *_t = static_cast<GroupLogger *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLogging(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setLogPath(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject GroupLogger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GroupLogger.data,
      qt_meta_data_GroupLogger,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GroupLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GroupLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GroupLogger.stringdata0))
        return static_cast<void*>(const_cast< GroupLogger*>(this));
    if (!strcmp(_clname, "OPCDataReceiver"))
        return static_cast< OPCDataReceiver*>(const_cast< GroupLogger*>(this));
    return QObject::qt_metacast(_clname);
}

int GroupLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GroupLogger::loggingChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GroupLogger::logPathChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
