/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../JDPost/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[14];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "onTabCurrentChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "index"
QT_MOC_LITERAL(4, 38, 15), // "onCmdsTreeClick"
QT_MOC_LITERAL(5, 54, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 71, 4), // "item"
QT_MOC_LITERAL(7, 76, 6), // "column"
QT_MOC_LITERAL(8, 83, 14), // "onAddParameter"
QT_MOC_LITERAL(9, 98, 9), // "onAddText"
QT_MOC_LITERAL(10, 108, 5), // "onDel"
QT_MOC_LITERAL(11, 114, 12), // "onAddNewLine"
QT_MOC_LITERAL(12, 127, 25), // "onSaveMenuActionTriggered"
QT_MOC_LITERAL(13, 153, 19) // "onOpenFileTriggered"

    },
    "MainWindow\0onTabCurrentChanged\0\0index\0"
    "onCmdsTreeClick\0QTreeWidgetItem*\0item\0"
    "column\0onAddParameter\0onAddText\0onDel\0"
    "onAddNewLine\0onSaveMenuActionTriggered\0"
    "onOpenFileTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x09 /* Protected */,
       4,    2,   57,    2, 0x09 /* Protected */,
       8,    0,   62,    2, 0x09 /* Protected */,
       9,    0,   63,    2, 0x09 /* Protected */,
      10,    0,   64,    2, 0x09 /* Protected */,
      11,    0,   65,    2, 0x09 /* Protected */,
      12,    0,   66,    2, 0x09 /* Protected */,
      13,    0,   67,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTabCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onCmdsTreeClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->onAddParameter(); break;
        case 3: _t->onAddText(); break;
        case 4: _t->onDel(); break;
        case 5: _t->onAddNewLine(); break;
        case 6: _t->onSaveMenuActionTriggered(); break;
        case 7: _t->onOpenFileTriggered(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
