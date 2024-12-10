/****************************************************************************
** Meta object code from reading C++ file 'mainpage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/mainpage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainPage_t {
    uint offsetsAndSizes[14];
    char stringdata0[9];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[12];
    char stringdata5[16];
    char stringdata6[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainPage_t qt_meta_stringdata_MainPage = {
    {
        QT_MOC_LITERAL(0, 8),  // "MainPage"
        QT_MOC_LITERAL(9, 13),  // "toggleOptions"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 14),  // "toggleFavorite"
        QT_MOC_LITERAL(39, 11),  // "companyName"
        QT_MOC_LITERAL(51, 15),  // "showEncryptView"
        QT_MOC_LITERAL(67, 16)   // "showPasswordView"
    },
    "MainPage",
    "toggleOptions",
    "",
    "toggleFavorite",
    "companyName",
    "showEncryptView",
    "showPasswordView"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    1,   39,    2, 0x08,    2 /* Private */,
       5,    0,   42,    2, 0x08,    4 /* Private */,
       6,    0,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MainPage.offsetsAndSizes,
    qt_meta_data_MainPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainPage, std::true_type>,
        // method 'toggleOptions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleFavorite'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showEncryptView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPasswordView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleOptions(); break;
        case 1: _t->toggleFavorite((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->showEncryptView(); break;
        case 3: _t->showPasswordView(); break;
        default: ;
        }
    }
}

const QMetaObject *MainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
