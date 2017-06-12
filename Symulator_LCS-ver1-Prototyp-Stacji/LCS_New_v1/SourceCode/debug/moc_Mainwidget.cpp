/****************************************************************************
** Meta object code from reading C++ file 'Mainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Mainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[24];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 5), // "Train"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 5), // "Trasa"
QT_MOC_LITERAL(4, 20, 1), // "j"
QT_MOC_LITERAL(5, 22, 5), // "kolor"
QT_MOC_LITERAL(6, 28, 3), // "flg"
QT_MOC_LITERAL(7, 32, 4), // "inUp"
QT_MOC_LITERAL(8, 37, 3), // "num"
QT_MOC_LITERAL(9, 41, 5), // "Stos*"
QT_MOC_LITERAL(10, 47, 3), // "tab"
QT_MOC_LITERAL(11, 51, 4), // "inDw"
QT_MOC_LITERAL(12, 56, 8), // "ZwChange"
QT_MOC_LITERAL(13, 65, 1), // "n"
QT_MOC_LITERAL(14, 67, 13), // "cleanAdjacent"
QT_MOC_LITERAL(15, 81, 5), // "stile"
QT_MOC_LITERAL(16, 87, 9), // "setZwStan"
QT_MOC_LITERAL(17, 97, 5), // "clean"
QT_MOC_LITERAL(18, 103, 11), // "setFromStan"
QT_MOC_LITERAL(19, 115, 3), // "tmp"
QT_MOC_LITERAL(20, 119, 4), // "stan"
QT_MOC_LITERAL(21, 124, 10), // "train_move"
QT_MOC_LITERAL(22, 135, 11), // "old_licznik"
QT_MOC_LITERAL(23, 147, 7) // "licznik"

    },
    "Widget\0Train\0\0Trasa\0j\0kolor\0flg\0inUp\0"
    "num\0Stos*\0tab\0inDw\0ZwChange\0n\0"
    "cleanAdjacent\0stile\0setZwStan\0clean\0"
    "setFromStan\0tmp\0stan\0train_move\0"
    "old_licznik\0licznik"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    3,   65,    2, 0x0a /* Public */,
       7,    2,   72,    2, 0x0a /* Public */,
      11,    2,   77,    2, 0x0a /* Public */,
      12,    1,   82,    2, 0x0a /* Public */,
      14,    2,   85,    2, 0x0a /* Public */,
      16,    1,   90,    2, 0x0a /* Public */,
      17,    2,   93,    2, 0x0a /* Public */,
      18,    2,   98,    2, 0x0a /* Public */,
      21,    2,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Char, QMetaType::Int,    4,    5,    6,
    QMetaType::Bool, QMetaType::Int, 0x80000000 | 9,    8,   10,
    QMetaType::Bool, QMetaType::Int, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   15,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,   23,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Train(); break;
        case 1: _t->Trasa((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: { bool _r = _t->inUp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Stos*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->inDw((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Stos*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->ZwChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->cleanAdjacent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->setZwStan((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->clean((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->setFromStan((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->train_move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
