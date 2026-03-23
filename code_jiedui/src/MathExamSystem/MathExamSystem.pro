QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _CRT_SECURE_NO_WARNINGS

# 使用 UTF-8 编码
#QMAKE_CXXFLAGS += /utf-8
#QMAKE_CFLAGS += /utf-8

# 或者指定源代码编码
#CODECFORSRC = UTF-8

# 应用程序信息
TARGET = MathExamSystem
TEMPLATE = app

# 源文件
SOURCES += \
    MainWindow.cpp \
    BackendInterface.cpp \
    main.cpp

HEADERS += \
    backendinterface.h \
    mainwindow.h

FORMS += \
    MainWindow.ui

# 发布版本配置
release: DESTDIR = $$PWD/release
debug: DESTDIR = $$PWD/debug

# 添加后端包含路径
INCLUDEPATH += ../backend \
               ../backend/Core \
               ../backend/Services \
               ../backend/Models \
               ../backend/Utils \
               ../ipc

# 添加后端源文件
SOURCES += \
    ../backend/Core/BackendCore.cpp \
    ../backend/Services/UserManager.cpp \
    ../backend/Services/ExamManager.cpp \
    ../backend/Services/QuestionService.cpp \
    ../backend/Services/QuestionGenerator.cpp \
    ../backend/Utils/StringHelper.cpp \
    ../backend/Utils/FileHelper.cpp \
    ../ipc/IPCServer.cpp

HEADERS += \
    ../backend/Core/BackendCore.h \
    ../backend/Services/UserManager.h \
    ../backend/Services/ExamManager.h \
    ../backend/Services/QuestionService.h \
    ../backend/Services/QuestionGenerator.h \
    ../backend/Models/UserInfo.h \
    ../backend/Models/Question.h \
    ../backend/Models/ExamResult.h \
    ../backend/Utils/StringHelper.h \
    ../backend/Utils/FileHelper.h \
    ../ipc/IPCServer.h

# 编译输出目录
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

# 编译器设置
QMAKE_CXXFLAGS += -std=c++17

# 平台特定设置
win32 {
    # Windows 特定设置
    LIBS += -lws2_32  # 如果需要网络功能

    # 根据架构选择包含路径
    contains(QT_ARCH, arm64) {
        # ARM架构
        INCLUDEPATH += "$$PWD/arm/include/curl"
        DEPENDPATH += "$$PWD/arm/include/curl"
        LIBS += -L$$PWD/arm/lib -lcurl
    } else {
        # Intel架构（包括x86和x64）
        INCLUDEPATH += "$$PWD/intel/include/curl"
        DEPENDPATH += "$$PWD/intel/include/curl"
        LIBS += -L$$PWD/intel/lib -lcurl
    }
}

unix {
    # Linux 特定设置
}
