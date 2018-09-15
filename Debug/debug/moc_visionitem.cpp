/****************************************************************************
** Meta object code from reading C++ file 'visionitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../visionitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionItem_t {
    QByteArrayData data[12];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionItem_t qt_meta_stringdata_VisionItem = {
    {
QT_MOC_LITERAL(0, 0, 10), // "VisionItem"
QT_MOC_LITERAL(1, 11, 14), // "signal_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "VisionItem*"
QT_MOC_LITERAL(4, 39, 4), // "item"
QT_MOC_LITERAL(5, 44, 8), // "selected"
QT_MOC_LITERAL(6, 53, 3), // "bIn"
QT_MOC_LITERAL(7, 57, 1), // "x"
QT_MOC_LITERAL(8, 59, 1), // "y"
QT_MOC_LITERAL(9, 61, 11), // "signal_ctrl"
QT_MOC_LITERAL(10, 73, 10), // "eventStyle"
QT_MOC_LITERAL(11, 84, 12) // "signal_press"

    },
    "VisionItem\0signal_clicked\0\0VisionItem*\0"
    "item\0selected\0bIn\0x\0y\0signal_ctrl\0"
    "eventStyle\0signal_press"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   44,    2, 0x06 /* Public */,
       1,    4,   55,    2, 0x26 /* Public | MethodCloned */,
       1,    3,   64,    2, 0x26 /* Public | MethodCloned */,
       1,    2,   71,    2, 0x26 /* Public | MethodCloned */,
       9,    1,   76,    2, 0x06 /* Public */,
      11,    0,   79,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal, QMetaType::QReal,    4,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void VisionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionItem *_t = static_cast<VisionItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 1: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 2: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->signal_ctrl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signal_press(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionItem::*_t)(VisionItem * , bool , bool , qreal , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_ctrl)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_press)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject VisionItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisionItem.data,
      qt_meta_data_VisionItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionItem.stringdata0))
        return static_cast<void*>(const_cast< VisionItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< VisionItem*>(this));
    return QObject::qt_metacast(_clname);
}

int VisionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VisionItem::signal_clicked(VisionItem * _t1, bool _t2, bool _t3, qreal _t4, qreal _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 4
void VisionItem::signal_ctrl(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VisionItem::signal_press()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
