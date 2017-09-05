/****************************************************************************
** Meta object code from reading C++ file 'plotdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plotdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlotDialog_t {
    QByteArrayData data[25];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotDialog_t qt_meta_stringdata_PlotDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlotDialog"
QT_MOC_LITERAL(1, 11, 21), // "on_btnSavePDF_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "on_btnSavePNG_clicked"
QT_MOC_LITERAL(4, 56, 11), // "axisClicked"
QT_MOC_LITERAL(5, 68, 8), // "QCPAxis*"
QT_MOC_LITERAL(6, 77, 4), // "axis"
QT_MOC_LITERAL(7, 82, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(8, 106, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 119, 5), // "event"
QT_MOC_LITERAL(10, 125, 14), // "plotMousePress"
QT_MOC_LITERAL(11, 140, 16), // "plotMouseRelease"
QT_MOC_LITERAL(12, 157, 13), // "plotMouseMove"
QT_MOC_LITERAL(13, 171, 22), // "on_btnLoadFile_clicked"
QT_MOC_LITERAL(14, 194, 21), // "on_btnAddFile_clicked"
QT_MOC_LITERAL(15, 216, 20), // "on_chkTracer_clicked"
QT_MOC_LITERAL(16, 237, 7), // "checked"
QT_MOC_LITERAL(17, 245, 8), // "setTitle"
QT_MOC_LITERAL(18, 254, 3), // "tag"
QT_MOC_LITERAL(19, 258, 7), // "setData"
QT_MOC_LITERAL(20, 266, 15), // "QVector<double>"
QT_MOC_LITERAL(21, 282, 3), // "key"
QT_MOC_LITERAL(22, 286, 5), // "value"
QT_MOC_LITERAL(23, 292, 7), // "addData"
QT_MOC_LITERAL(24, 300, 11) // "addBoolData"

    },
    "PlotDialog\0on_btnSavePDF_clicked\0\0"
    "on_btnSavePNG_clicked\0axisClicked\0"
    "QCPAxis*\0axis\0QCPAxis::SelectablePart\0"
    "QMouseEvent*\0event\0plotMousePress\0"
    "plotMouseRelease\0plotMouseMove\0"
    "on_btnLoadFile_clicked\0on_btnAddFile_clicked\0"
    "on_chkTracer_clicked\0checked\0setTitle\0"
    "tag\0setData\0QVector<double>\0key\0value\0"
    "addData\0addBoolData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    3,   81,    2, 0x08 /* Private */,
      10,    1,   88,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      12,    1,   94,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    1,   99,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      17,    1,  102,    2, 0x02 /* Public */,
      19,    3,  105,    2, 0x02 /* Public */,
      23,    3,  112,    2, 0x02 /* Public */,
      24,    3,  119,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 8,    6,    2,    9,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 20, 0x80000000 | 20,   18,   21,   22,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 20, 0x80000000 | 20,   18,   21,   22,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 20, 0x80000000 | 20,   18,   21,   22,

       0        // eod
};

void PlotDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotDialog *_t = static_cast<PlotDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnSavePDF_clicked(); break;
        case 1: _t->on_btnSavePNG_clicked(); break;
        case 2: _t->axisClicked((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 3: _t->plotMousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->plotMouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->plotMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->on_btnLoadFile_clicked(); break;
        case 7: _t->on_btnAddFile_clicked(); break;
        case 8: _t->on_chkTracer_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->setData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2])),(*reinterpret_cast< const QVector<double>(*)>(_a[3]))); break;
        case 11: _t->addData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2])),(*reinterpret_cast< const QVector<double>(*)>(_a[3]))); break;
        case 12: _t->addBoolData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2])),(*reinterpret_cast< const QVector<double>(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject PlotDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PlotDialog.data,
      qt_meta_data_PlotDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlotDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlotDialog.stringdata0))
        return static_cast<void*>(const_cast< PlotDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PlotDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
