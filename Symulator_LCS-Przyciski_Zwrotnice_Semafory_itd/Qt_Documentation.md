Links:
https://wiki.qt.io/Qt_for_Beginners

Tips:

*QObject is the most basic class in Qt. Most of classes in Qt inherit from this class. QObject provides some very powerful capabilities like:

-object name : you can set a name, as a string, to an object and search for objects by names

-parenting system (described in the following section)

-signals and slots (described in the next chapter)

-event management

*QWidget contains most properties that are used to describe a window, or a widget, like position and size, mouse cursor, tooltips, etc.

*QAbstractButton provides basic properties that are shared by all buttons.

*Parenting system is a convenient way of dealing with objects in Qt, especially widgets. Any object that inherits from QObject can have a parent and children. This hierarchy tree makes many things convenient:

-When an object is destroyed, all of its children are destroyed as well. So, calling delete becomes optional in certain cases.

-All QObjects have findChild and findChildren methods that can be used to search for children of a given object.

-Child widgets in a QWidget automatically appear inside the parent widget.
