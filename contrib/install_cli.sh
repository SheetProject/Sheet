 #!/usr/bin/env bash

 # Execute this file to install the sheet cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Sheet-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Sheet-Qt.app/Contents/MacOS/sheetd /usr/local/bin/sheetd
 sudo ln -s ${LOCATION}/Sheet-Qt.app/Contents/MacOS/sheet-cli /usr/local/bin/sheet-cli
