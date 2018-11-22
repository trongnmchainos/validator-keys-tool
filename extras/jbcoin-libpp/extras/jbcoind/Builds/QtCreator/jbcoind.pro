
# Jbcoin protocol buffers

PROTOS = ../../src/jbcoin_data/protocol/jbcoin.proto
PROTOS_DIR = ../../build/proto

# Google Protocol Buffers support

protobuf_h.name = protobuf header
protobuf_h.input = PROTOS
protobuf_h.output = $${PROTOS_DIR}/${QMAKE_FILE_BASE}.pb.h
protobuf_h.depends = ${QMAKE_FILE_NAME}
protobuf_h.commands = protoc --cpp_out=$${PROTOS_DIR} --proto_path=${QMAKE_FILE_PATH} ${QMAKE_FILE_NAME}
protobuf_h.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_h

protobuf_cc.name = protobuf implementation
protobuf_cc.input = PROTOS
protobuf_cc.output = $${PROTOS_DIR}/${QMAKE_FILE_BASE}.pb.cc
protobuf_cc.depends = $${PROTOS_DIR}/${QMAKE_FILE_BASE}.pb.h
protobuf_cc.commands = $$escape_expand(\\n)
#protobuf_cc.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_cc

# Jbcoin compilation

DESTDIR = ../../build/QtCreator
OBJECTS_DIR = ../../build/QtCreator/obj

TEMPLATE = app
CONFIG += console thread warn_off
CONFIG -= qt gui

DEFINES += _DEBUG

linux-g++:QMAKE_CXXFLAGS += \
    -Wall \
    -Wno-sign-compare \
    -Wno-char-subscripts \
    -Wno-invalid-offsetof \
    -Wno-unused-parameter \
    -Wformat \
    -O0 \
    -std=c++11 \
    -pthread

INCLUDEPATH += \
    "../../src/leveldb/" \
    "../../src/leveldb/port" \
    "../../src/leveldb/include" \
    $${PROTOS_DIR}

OTHER_FILES += \
#   $$files(../../src/*, true) \
#   $$files(../../src/beast/*) \
#   $$files(../../src/beast/modules/beast_basics/diagnostic/*)
#   $$files(../../src/beast/modules/beast_core/, true)

UI_HEADERS_DIR += ../../src/jbcoin_basics

# ---------
# New style
#
SOURCES += \
    ../../src/jbcoin/beast/jbcoin_beast.unity.cpp \
    ../../src/jbcoin/beast/jbcoin_beastc.c \
    ../../src/jbcoin/common/jbcoin_common.unity.cpp \
    ../../src/jbcoin/http/jbcoin_http.unity.cpp \
    ../../src/jbcoin/json/jbcoin_json.unity.cpp \
    ../../src/jbcoin/peerfinder/jbcoin_peerfinder.unity.cpp \
    ../../src/jbcoin/radmap/jbcoin_radmap.unity.cpp \
    ../../src/jbcoin/resource/jbcoin_resource.unity.cpp \
    ../../src/jbcoin/sitefiles/jbcoin_sitefiles.unity.cpp \
    ../../src/jbcoin/sslutil/jbcoin_sslutil.unity.cpp \
    ../../src/jbcoin/testoverlay/jbcoin_testoverlay.unity.cpp \
    ../../src/jbcoin/types/jbcoin_types.unity.cpp \
    ../../src/jbcoin/validators/jbcoin_validators.unity.cpp

# ---------
# Old style
#
SOURCES += \
    ../../src/jbcoin_app/jbcoin_app.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt1.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt2.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt3.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt4.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt5.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt6.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt7.unity.cpp \
    ../../src/jbcoin_app/jbcoin_app_pt8.unity.cpp \
    ../../src/jbcoin_basics/jbcoin_basics.unity.cpp \
    ../../src/jbcoin_core/jbcoin_core.unity.cpp \
    ../../src/jbcoin_data/jbcoin_data.unity.cpp \
    ../../src/jbcoin_hyperleveldb/jbcoin_hyperleveldb.unity.cpp \
    ../../src/jbcoin_leveldb/jbcoin_leveldb.unity.cpp \
    ../../src/jbcoin_net/jbcoin_net.unity.cpp \
    ../../src/jbcoin_overlay/jbcoin_overlay.unity.cpp \
    ../../src/jbcoin_rpc/jbcoin_rpc.unity.cpp \
    ../../src/jbcoin_websocket/jbcoin_websocket.unity.cpp

LIBS += \
    -lboost_date_time-mt\
    -lboost_filesystem-mt \
    -lboost_program_options-mt \
    -lboost_regex-mt \
    -lboost_system-mt \
    -lboost_thread-mt \
    -lboost_random-mt \
    -lprotobuf \
    -lssl \
    -lrt
