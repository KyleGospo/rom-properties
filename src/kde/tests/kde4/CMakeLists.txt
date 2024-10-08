# KDE UI frontend test suite (KDE4)
PROJECT(kde4-tests LANGUAGES CXX)

# Top-level src directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../..)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/../../..)

# KDE source directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../..)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/../..)

INCLUDE(RP_FindQt4andKDE4)
FIND_QT4_AND_KDE4()

IF(BUILD_KDE4)

### ListDataSortProxyModel tests

STRING(REGEX REPLACE "([^;]+)" "../\\1" ListDataSortProxyModelTest_kde4_SRCS "${ListDataSortProxyModelTest_SRCS}")
STRING(REGEX REPLACE "([^;]+)" "../\\1" ListDataSortProxyModelTest_kde4_H    "${ListDataSortProxyModelTest_H}")

ADD_EXECUTABLE(ListDataSortProxyModelTest_kde4
	${ListDataSortProxyModelTest_kde4_SRCS}
	${ListDataSortProxyModelTest_kde4_H}
	)
TARGET_LINK_LIBRARIES(ListDataSortProxyModelTest_kde4 PRIVATE rptest romdata)
TARGET_LINK_LIBRARIES(ListDataSortProxyModelTest_kde4 PUBLIC Qt4::QtGui Qt4::QtCore)
LIST(APPEND KDE4_TESTS ListDataSortProxyModelTest_kde4)

### RomDataFormat tests

STRING(REGEX REPLACE "([^;]+)" "../\\1" RomDataFormatTest_kde4_SRCS "${RomDataFormatTest_SRCS}")
STRING(REGEX REPLACE "([^;]+)" "../\\1" RomDataFormatTest_kde4_H    "${RomDataFormatTest_H}")

ADD_EXECUTABLE(RomDataFormatTest_kde4
	${RomDataFormatTest_kde4_SRCS}
	${RomDataFormatTest_kde4_H}
	)
TARGET_LINK_LIBRARIES(RomDataFormatTest_kde4 PRIVATE rptest romdata)
# NOTE: QSortFilterProxyModel is in QtGui in Qt4. (In Qt5, it was moved to QtCore.)
TARGET_LINK_LIBRARIES(RomDataFormatTest_kde4 PUBLIC Qt4::QtGui Qt4::QtCore)
# Include directories required for stdafx.h.
TARGET_INCLUDE_DIRECTORIES(RomDataFormatTest_kde4
	PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/../../../librptext"
	)
LIST(APPEND KF5_TESTS RomDataFormatTest_kde4)

###### Add tests to CTest ######

FOREACH(_target ${KDE4_TESTS})
	DO_SPLIT_DEBUG(${_target})
	SET_WINDOWS_SUBSYSTEM(${_target} CONSOLE)
	SET_WINDOWS_ENTRYPOINT(${_target} wmain OFF)
	ADD_TEST(NAME ${_target} COMMAND ${_target} --gtest_brief)
ENDFOREACH(_target)

ENDIF(BUILD_KDE4)
