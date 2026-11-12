<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/17-c-linkage-and-the-installed-sdk.md

PURPOSE:
Use the C registry directly from a Qt adapter

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use the C registry directly from a Qt adapter

## Start from the shared contract

The first sixteen lessons built a profile form across target environments. This module adds a native, memory-only model exercise. A model supplies values to an interface; it does not have to draw a window. Open component_model.h and then the installed Framework header umicom/ui/components/registry.h. The registry owns component specifications as C records. Qt supplies the C++ model interface.

## Include the real SDK header

~~~cpp
#include "umicom/ui/components/registry.h"
#include <QAbstractListModel>

class ComponentModel final : public QAbstractListModel {
    // See the complete laboratory header for roles, signals and ownership.
};
~~~

Framework public headers declare their external functions with C linkage when included by C++. This keeps the language boundary explicit. Do not copy declarations into the lab or include Framework .c implementation files. The library and header must come from the same SDK installation. Linkage spelling alone does not reconcile different processors, compiler runtimes or structure layouts.

## Trace the dependency

CMake links the adapter against Umicom::ui_components and Qt6::Core. The imported Framework target carries the library dependencies. The adapter calls umi_ui_component_spec_default, the text setters and umi_ui_component_registry_add. C++ is required to implement the Qt class; admission policy stays in the shared C functions.

## Exercise and recovery

Before building, locate the selected SDK header and its matching library. Record their installation prefix and source identity. If the linker cannot resolve a component function, first determine whether the requested symbol has C or C++ linkage, then inspect the selected header and imported target. Do not paste an extern declaration into the application to hide a mismatched SDK. Reinstall a coherent SDK and qualify the consumer again.

## Reference

- [Qt list models](https://doc.qt.io/qt-6/qabstractlistmodel.html)

## Read the source

[labs/framework/qt-component-model/component_model.h](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/component_model.h). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Compare desktop, web and mobile release evidence](16-compare-desktop-web-and-mobile-evidence.md) · [Next: Map registry records to rows and roles](18-map-registry-records-to-qt-roles.md)
