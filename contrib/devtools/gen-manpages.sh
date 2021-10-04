#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SHEETD=${SHEETD:-$SRCDIR/sheetd}
SHEETCLI=${SHEETCLI:-$SRCDIR/sheet-cli}
SHEETTX=${SHEETTX:-$SRCDIR/sheet-tx}
SHEETQT=${SHEETQT:-$SRCDIR/qt/sheet-qt}

[ ! -x $SHEETD ] && echo "$SHEETD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SHTXVER=($($SHEETCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for sheetd if --version-string is not set,
# but has different outcomes for sheet-qt and sheet-cli.
echo "[COPYRIGHT]" > footer.h2m
$SHEETD --version | sed -n '1!p' >> footer.h2m

for cmd in $SHEETD $SHEETCLI $SHEETTX $SHEETQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SHTXVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SHTXVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
