cmake_minimum_required(VERSION 3.24)

if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(FMSLogoUnicode LANGUAGES C CXX ASM_MASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(LINUX 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET(WINDOWS 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    SET(FREEBSD 1)
ELSE ()
    SET(UNKNOW 1)
ENDIF()
if(WINDOWS)
set(wxWidgets_ROOT_DIR "C:/Program Files (x86)/wxWidgets")
elseif(LINUX)
set(wxWidgets_ROOT_DIR "/usr/local/lib/cmake/wxWidgets/")
endif()
set(wxWidgets_LIBRARIES "/usr/local/lib/libwx_baseu-3.3.so")
if(WINDOWS)
find_package(wxWidgets REQUIRED COMPONENTS core base stc richtext net scintilla)
elseif(LINUX)
find_package(wxWidgets REQUIRED COMPONENTS core base stc richtext net)
endif()
if(NOT wxWidgets_FOUND)
    message(FATAL_ERROR "wxWidgets not found")
endif()

include(${wxWidgets_USE_FILE})

set(SRC_FILES 
    3dsolid.cpp
    aboutfmslogo.cpp
    aboutmultiplesclerosis.cpp
    activearea.cpp
    appendablelist.cpp
    argumentutils.cpp
    avltree.cpp
    CConstStringTextReadonlyStream.cpp
    CEncodingConverter.cpp
    CEncodingFileTextStream.cpp
    CFileTextStream.cpp
    CLocalizedStringProvider.cpp
    CMbcsFileTextStream.cpp
    CNodePrinter.cpp
    commander.cpp
    commanderbutton.cpp
    commanderhistory.cpp
    commanderinput.cpp
    commandertogglebutton.cpp
    coms.cpp
    CStringTextStream.cpp
    CTextStream.cpp
    CUTF16FileTextStream.cpp
    cursor.cpp
    CUTF8FileTextStream.cpp
    devwind.cpp
    dynamicbuffer.cpp
    editproceduredialog.cpp
    eraseproceduredialog.cpp
    error.cpp
    eval.cpp
    files.cpp
    fileswnd.cpp
    FMSLogo.cpp
    fontutils.cpp
    gbm.cpp
    gbmbmp.cpp
    gbmgif.cpp
    gbmhelp.cpp
    gbmsize.cpp
    graphics.cpp
    graphwin.cpp
    guiutils.cpp
    helputils.cpp
    ibmterm.cpp
    init.cpp
    intern.cpp
    lists.cpp
    localizednode.cpp
    localizedstrings.cpp
    logocodectrl.cpp
    logodata.cpp
    logodialogboxes.cpp
    logoeventqueue.cpp
    logomath.cpp
    mainframe.cpp
    mainwind.cpp
    mem.cpp
    messagebox.cpp
    minieditor.cpp
    minieditortextctrl.cpp
    mmwind.cpp
    netwind.cpp
    paren.cpp
    parse.cpp
    print.cpp
    questionbox.cpp
    RtAudio.cpp
    savebeforeexitdialog.cpp
    LexFmsLogo.cxx
    LexFmsLogoRegisterer.cxx
    screen.cpp
    selectbox.cpp
    selectproceduredialog.cpp
    selectstartupinstruction.cpp
    setactivearea.cpp
    setcolor.cpp
    setpensize.cpp
    sort.cpp
    sound.cpp
    startup.cpp
    statusdialog.cpp
    stringprintednode.cpp
    term.cpp
    threed.cpp
    CCheckQueueEvent.cpp
    unix.cpp
    utils.cpp
    vector.cpp
    workspaceeditor.cpp
    wrksp.cpp
    FMSLogo.rc
)

#message(WARNING ${wxWidgets_LIBRARIES})
#message(WARNING ${wxWidgets_INCLUDE_DIRS})

if (WINDOWS)
    set(SRC_FILES ${SRC_FILES} dib.cpp dllwind.cpp stdafx.cpp)
if (CMAKE_CL_32)
    set(SRC_FILES ${SRC_FILES} helpers32.asm)
elseif (CMAKE_CL_64)
    set(SRC_FILES ${SRC_FILES} helpers64.asm)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
SET(wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES} "${wxWidgets_LIB_DIR}/wxlexilla.lib")
else()
SET(wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES} "${wxWidgets_LIB_DIR}/wxlexillad.lib")
endif()
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

if(WINDOWS)
target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_NON_CONFORMING_WCSTOK -D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS /FORCE:MULTIPLE)
elseif(LINUX)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DLINUX -DWX_PURE)	
endif()

