#!/usr/bin/bash
###########################################################################
# This file is a reminder of how I built wxWidgets 3.1.0 on Windows.
#
# Use the script like:
#
#   bash
#   cd [wxwidgets_src_dir]
#   patch -p1 < [path_to_this_script]/wxwidgets-3.1.0.patch
#
#   cd [wxwidgets_bin_dir]/retail
#   [path_to_this_script]/configure-wxwidgets.sh [wxwidgets_src_dir]
#   make clean all
#
#   export DEBUG=1
#   cd [wxwidgets_bin_dir]/debug
#   [path_to_this_script]/configure-wxwidgets.sh [wxwidgets_src_dir]
#   make clean all
#
###########################################################################
if [ -z ${1+x} ];
then
  echo "Usage: configure-wxwidgets.sh <path to wxwidgets src>"
  exit 1
fi

CONFIGURE=$1/configure

if [ ! -f $CONFIGURE ];
then
  echo "The file $CONFIGURE does not exist"
  exit 1
fi

if [ -f configarg.cache ];
then
  rm configarg.cache
fi

if [ "$DEBUG" == "1" ];
then
  export ADDITIONAL_OPTIONS="--enable-debug --enable-debug_gdb --enable-debug_info --disable-optimise"
else
  export ADDITIONAL_OPTIONS="--disable-debug_flag --enable-optimise"

  # Enable link-time optimization so that the resulting fmslogo.exe isn't 8 MiB.
  # Without this, all of the uncalled member functions remain in the final executable.
  ## Unfortunately, there's a bug in the -flto in i686-w64-mingw32-g++ (GCC) 5.3.0
  ## So until this is fixed, wxWidgets cannot be compiled with this flag, which means
  ## that dead code cannot be removed.
  ##export CFLAGS=-flto
  ##export CXXFLAGS=-flto
  ##export LDFLAGS=-flto
fi

if [ "$PROFILE" == "1" ];
then
export ADDITIONAL_OPTIONS="$ADDITIONAL_OPTIONS --enable-profile"
fi

# Statically link to libc.  This has no impact on FMSLogo, as we only build a static
# library for for FMSLogo and the linker is not involved in that.  However, this makes
# it easier to run the wxWidgets sample applications.
export LDFLAGS="-static-libgcc -static-libstdc++" $LDFLAGS

export PATH=/usr/bin:$PATH

$CONFIGURE                        \
    $ADDITIONAL_OPTIONS           \
    --host=i686-w64-mingw32       \
    --disable-all-features        \
    --disable-metafile            \
    --disable-postscript          \
    --disable-largefile           \
    --disable-compat30            \
    --disable-gtktest             \
    --disable-sdltest             \
    --disable-dependency-tracking \
    --with-msw                    \
    --with-expat=builtin          \
    --with-regex=no               \
    --with-libpng=no              \
    --with-zlib=no                \
    --with-libjpeg=no             \
    --with-libtiff=no             \
    --with-opengl=no              \
    --with-libnotify=no           \
    --disable-unicode             \
    --enable-monolithic           \
    --disable-shared              \
    --enable-stc                  \
    --enable-stopwatch            \
    --enable-longlong             \
    --enable-menus                \
    --enable-notifmsg             \
    --enable-timer                \
    --enable-button               \
    --enable-stattext             \
    --enable-image                \
    --enable-bmpbutton            \
    --enable-statbmp              \
    --enable-textctrl             \
    --enable-scrollbar            \
    --enable-streams              \
    --enable-clipboard            \
    --enable-file                 \
    --enable-dataobj              \
    --enable-ole                  \
    --enable-variant              \
    --enable-listctrl             \
    --enable-listbox              \
    --enable-imaglist             \
    --enable-richtext             \
    --enable-html                 \
    --enable-filesystem           \
    --enable-printarch            \
    --enable-combobox             \
    --enable-choice               \
    --enable-msgdlg               \
    --enable-fontmap              \
    --enable-finddlg              \
    --enable-togglebtn            \
    --enable-mshtmlhelp           \
    --enable-help                 \
    --enable-textbuf              \
    --enable-textfile             \
    --enable-choicedlg            \
    --enable-dynamicloader        \
    --enable-dynlib               \
    --enable-fontdlg              \
    --enable-fontenum             \
    --enable-propgrid             \
    --enable-coldlg               \
    --enable-odcombobox           \
    --enable-comboctrl            \
    --enable-editablebox          \
    --enable-regkey               \
    --enable-filedlg              \
    --enable-dirdlg               \
    --enable-treectrl             \
    --enable-notebook             \
    --enable-caret                \
    --enable-accel                \
    --enable-spinbtn              \
    --enable-checkbox             \
    --enable-radiobtn             \
    --enable-statline             \
    --enable-spinctrl             \
    --enable-textdlg              \
    --enable-statbox              \
    --enable-stdpaths             \
    --enable-slider               \
    --enable-splitter             \
    --enable-uxtheme              \
    --enable-dccache              \
    --enable-wxdib                \
    --enable-mousewheel           \
    --enable-statusbar            \
    --enable-popupwin             \
