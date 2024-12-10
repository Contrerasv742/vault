/****************************************************************************
** Meta object code from reading C++ file 'encryptpage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/encryptpage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'encryptpage.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_EncryptPage_t {
    uint offsetsAndSizes[14];
    char stringdata0[12];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[17];
    char stringdata5[12];
    char stringdata6[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_EncryptPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_EncryptPage_t qt_meta_stringdata_EncryptPage = {
    {
        QT_MOC_LITERAL(0, 11),  // "EncryptPage"
        QT_MOC_LITERAL(12, 20),  // "updatePasswordLength"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 5),  // "value"
        QT_MOC_LITERAL(40, 16),  // "generatePassword"
        QT_MOC_LITERAL(57, 11),  // "encryptText"
        QT_MOC_LITERAL(69, 23)   // "updateStrengthIndicator"
    },
    "EncryptPage",
    "updatePasswordLength",
    "",
    "value",
    "generatePassword",
    "encryptText",
    "updateStrengthIndicator"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_EncryptPage[] = {

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
       1,    1,   38,    2, 0x08,    1 /* Private */,
       4,    0,   41,    2, 0x08,    3 /* Private */,
       5,    0,   42,    2, 0x08,    4 /* Private */,
       6,    0,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject EncryptPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EncryptPage.offsetsAndSizes,
    qt_meta_data_EncryptPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_EncryptPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EncryptPage, std::true_type>,
        // method 'updatePasswordLength'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'generatePassword'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'encryptText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateStrengthIndicator'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void EncryptPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EncryptPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatePasswordLength((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->generatePassword(); break;
        case 2: _t->encryptText(); break;
        case 3: _t->updateStrengthIndicator(); break;
        default: ;
        }
    }
}

const QMetaObject *EncryptPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EncryptPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EncryptPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EncryptPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
