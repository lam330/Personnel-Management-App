/****************************************************************************
** Meta object code from reading C++ file 'rep_simpleswitch_source.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../rep_simpleswitch_source.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rep_simpleswitch_source.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Project_t {
    QByteArrayData data[4];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Project_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Project_t qt_meta_stringdata_Project = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Project"
QT_MOC_LITERAL(1, 8, 6), // "number"
QT_MOC_LITERAL(2, 15, 8), // "customer"
QT_MOC_LITERAL(3, 24, 4) // "role"

    },
    "Project\0number\0customer\0role"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Project[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095103,
       2, QMetaType::QString, 0x00095103,
       3, QMetaType::QString, 0x00095103,

       0        // eod
};

void Project::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = reinterpret_cast<Project *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->number(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->customer(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->role(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = reinterpret_cast<Project *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNumber(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setCustomer(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setRole(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Project::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_Project.data,
    qt_meta_data_Project,
    qt_static_metacall,
    nullptr,
    nullptr
} };

struct qt_meta_stringdata_Person_t {
    QByteArrayData data[6];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Person_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Person_t qt_meta_stringdata_Person = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Person"
QT_MOC_LITERAL(1, 7, 4), // "name"
QT_MOC_LITERAL(2, 12, 3), // "age"
QT_MOC_LITERAL(3, 16, 8), // "position"
QT_MOC_LITERAL(4, 25, 8), // "projects"
QT_MOC_LITERAL(5, 34, 16) // "QVector<Project>"

    },
    "Person\0name\0age\0position\0projects\0"
    "QVector<Project>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Person[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095103,
       2, QMetaType::Int, 0x00095103,
       3, QMetaType::QString, 0x00095103,
       4, 0x80000000 | 5, 0x0009510b,

       0        // eod
};

void Person::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = reinterpret_cast<Person *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->age(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->position(); break;
        case 3: *reinterpret_cast< QVector<Project>*>(_v) = _t->projects(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = reinterpret_cast<Person *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setAge(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setPosition(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setProjects(*reinterpret_cast< QVector<Project>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Person::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_Person.data,
    qt_meta_data_Person,
    qt_static_metacall,
    nullptr,
    nullptr
} };

struct qt_meta_stringdata_SimpleSwitchSource_t {
    QByteArrayData data[13];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleSwitchSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleSwitchSource_t qt_meta_stringdata_SimpleSwitchSource = {
    {
QT_MOC_LITERAL(0, 0, 18), // "SimpleSwitchSource"
QT_MOC_LITERAL(1, 19, 17), // "RemoteObject Type"
QT_MOC_LITERAL(2, 37, 12), // "SimpleSwitch"
QT_MOC_LITERAL(3, 50, 22), // "RemoteObject Signature"
QT_MOC_LITERAL(4, 73, 40), // "602dba037e13f860cf4adb5af7f8c..."
QT_MOC_LITERAL(5, 114, 13), // "personChanged"
QT_MOC_LITERAL(6, 128, 0), // ""
QT_MOC_LITERAL(7, 129, 6), // "Person"
QT_MOC_LITERAL(8, 136, 6), // "person"
QT_MOC_LITERAL(9, 143, 10), // "pushPerson"
QT_MOC_LITERAL(10, 154, 13), // "rep_to_source"
QT_MOC_LITERAL(11, 168, 12), // "clientPerson"
QT_MOC_LITERAL(12, 181, 13) // "source_to_rep"

    },
    "SimpleSwitchSource\0RemoteObject Type\0"
    "SimpleSwitch\0RemoteObject Signature\0"
    "602dba037e13f860cf4adb5af7f8c068ff37cf99\0"
    "personChanged\0\0Person\0person\0pushPerson\0"
    "rep_to_source\0clientPerson\0source_to_rep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleSwitchSource[] = {

 // content:
       8,       // revision
       0,       // classname
       2,   14, // classinfo
       4,   18, // methods
       1,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    1,   38,    6, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   41,    6, 0x0a /* Public */,
      10,    1,   44,    6, 0x0a /* Public */,
      12,    0,   47,    6, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   11,
    QMetaType::Void,

 // properties: name, type, flags
       8, 0x80000000 | 7, 0x0049510b,

 // properties: notify_signal_id
       0,

       0        // eod
};

void SimpleSwitchSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimpleSwitchSource *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->personChanged((*reinterpret_cast< Person(*)>(_a[1]))); break;
        case 1: _t->pushPerson((*reinterpret_cast< Person(*)>(_a[1]))); break;
        case 2: _t->rep_to_source((*reinterpret_cast< Person(*)>(_a[1]))); break;
        case 3: _t->source_to_rep(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimpleSwitchSource::*)(Person );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimpleSwitchSource::personChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SimpleSwitchSource *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Person*>(_v) = _t->person(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SimpleSwitchSource *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPerson(*reinterpret_cast< Person*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SimpleSwitchSource::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SimpleSwitchSource.data,
    qt_meta_data_SimpleSwitchSource,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimpleSwitchSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleSwitchSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleSwitchSource.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SimpleSwitchSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SimpleSwitchSource::personChanged(Person _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SimpleSwitchSimpleSource_t {
    QByteArrayData data[1];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleSwitchSimpleSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleSwitchSimpleSource_t qt_meta_stringdata_SimpleSwitchSimpleSource = {
    {
QT_MOC_LITERAL(0, 0, 24) // "SimpleSwitchSimpleSource"

    },
    "SimpleSwitchSimpleSource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleSwitchSimpleSource[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SimpleSwitchSimpleSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SimpleSwitchSimpleSource::staticMetaObject = { {
    QMetaObject::SuperData::link<SimpleSwitchSource::staticMetaObject>(),
    qt_meta_stringdata_SimpleSwitchSimpleSource.data,
    qt_meta_data_SimpleSwitchSimpleSource,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimpleSwitchSimpleSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleSwitchSimpleSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleSwitchSimpleSource.stringdata0))
        return static_cast<void*>(this);
    return SimpleSwitchSource::qt_metacast(_clname);
}

int SimpleSwitchSimpleSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SimpleSwitchSource::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
