/****************************************************************************
** Meta object code from reading C++ file 'btreewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qtest3/btreewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'btreewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BtreeWindow_t {
    QByteArrayData data[12];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BtreeWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BtreeWindow_t qt_meta_stringdata_BtreeWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BtreeWindow"
QT_MOC_LITERAL(1, 12, 10), // "returnMain"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "exitSlot"
QT_MOC_LITERAL(4, 33, 8), // "backSlot"
QT_MOC_LITERAL(5, 42, 13), // "PreOrdTraSlot"
QT_MOC_LITERAL(6, 56, 12), // "InOrdTraSlot"
QT_MOC_LITERAL(7, 69, 14), // "PostOrdTraSlot"
QT_MOC_LITERAL(8, 84, 17), // "CountLeafNodeSlot"
QT_MOC_LITERAL(9, 102, 12), // "InOrdThrSlot"
QT_MOC_LITERAL(10, 115, 14), // "PostOrdThrSlot"
QT_MOC_LITERAL(11, 130, 13) // "PreOrdThrSlot"

    },
    "BtreeWindow\0returnMain\0\0exitSlot\0"
    "backSlot\0PreOrdTraSlot\0InOrdTraSlot\0"
    "PostOrdTraSlot\0CountLeafNodeSlot\0"
    "InOrdThrSlot\0PostOrdThrSlot\0PreOrdThrSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BtreeWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BtreeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BtreeWindow *_t = static_cast<BtreeWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnMain(); break;
        case 1: _t->exitSlot(); break;
        case 2: _t->backSlot(); break;
        case 3: _t->PreOrdTraSlot(); break;
        case 4: _t->InOrdTraSlot(); break;
        case 5: _t->PostOrdTraSlot(); break;
        case 6: _t->CountLeafNodeSlot(); break;
        case 7: _t->InOrdThrSlot(); break;
        case 8: _t->PostOrdThrSlot(); break;
        case 9: _t->PreOrdThrSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BtreeWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BtreeWindow::returnMain)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject BtreeWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BtreeWindow.data,
      qt_meta_data_BtreeWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BtreeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BtreeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BtreeWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BtreeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void BtreeWindow::returnMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
