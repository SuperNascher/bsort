SUBDIRS += interface_sort \
 src \
 sort_bogo \
 sort_bubble \
 sort_shell \
 sort_quick
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread \
          ordered
