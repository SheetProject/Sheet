// Copyright (c) 2011-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Sheet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHEET_QT_GUICONSTANTS_H
#define SHEET_QT_GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 250;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

/* SheetGUI -- Size of icons in status bar */
static const int STATUSBAR_ICONSIZE = 16;

static const bool DEFAULT_SPLASHSCREEN = true;

/* Invalid field background style */
#define STYLE_INVALID "background:#FF8080; border: 1px solid lightgray; padding: 0px;"
#define STYLE_VALID "border: 1px solid lightgray; padding: 0px;"

/* Transaction list -- unconfirmed transaction */
#define COLOR_UNCONFIRMED QColor(128, 128, 128)
/* Transaction list -- negative amount */
#define COLOR_NEGATIVE QColor(255, 0, 0)
/* Transaction list -- bare address (without label) */
#define COLOR_BAREADDRESS QColor(140, 140, 140)
/* Transaction list -- TX status decoration - open until date */
#define COLOR_TX_STATUS_OPENUNTILDATE QColor(64, 64, 255)
/* Transaction list -- TX status decoration - offline */
#define COLOR_TX_STATUS_OFFLINE QColor(192, 192, 192)
/* Transaction list -- TX status decoration - danger, tx needs attention */
#define COLOR_TX_STATUS_DANGER QColor(200, 100, 100)
/* Transaction list -- TX status decoration - default color */
#define COLOR_BLACK QColor(0, 0, 0)
/* Widget Background color - default color */
#define COLOR_WHITE QColor(255, 255, 255)

#define COLOR_WALLETFRAME_SHADOW QColor(0,0,0,71)

/* Color of labels */
#define COLOR_LABELS QColor("#0059b3")

/** LIGHT MODE */
/* Background color, very light gray */
#define COLOR_BACKGROUND_LIGHT QColor("#ffffff")
/* Sheet dark orange */
#define COLOR_DARK_ORANGE QColor("#004d99")
/* Sheet light orange */
#define COLOR_LIGHT_ORANGE QColor("#0066cc")
/* Sheet dark blue */
#define COLOR_DARK_BLUE QColor("#004d99")
/* Sheet light blue */
#define COLOR_LIGHT_BLUE QColor("#0066cc")
/* Sheet asset text */
#define COLOR_ASSET_TEXT QColor(255, 255, 255)
/* Sheet shadow color - light mode */
#define COLOR_SHADOW_LIGHT QColor("#cce6ff")
/* Toolbar not selected text color */
#define COLOR_TOOLBAR_NOT_SELECTED_TEXT QColor("#ffffff")
/* Toolbar selected text color */
#define COLOR_TOOLBAR_SELECTED_TEXT QColor("#ffffff")

/** DARK MODE */
/* Background color, dark mode */
#define COLOR_BACKGROUND_DARK QColor("#262626")
/* Widget background color, dark mode */
#define COLOR_WIDGET_BACKGROUND_DARK QColor("#4d4d4d")
/* Sheet shadow color - dark mode */
#define COLOR_SHADOW_DARK QColor("#999999")
/* Sheet Light blue - dark mode - dark mode */
#define COLOR_LIGHT_BLUE_DARK QColor("#262626")
/* Sheet Dark blue - dark mode - dark mode */
#define COLOR_DARK_BLUE_DARK QColor("#4d4d4d")
/* Pricing widget background color */
#define COLOR_PRICING_WIDGET QColor("#4d4d4d")
/* Sheet dark mode administrator background color */
#define COLOR_ADMIN_CARD_DARK QColor("#262626")
/* Sheet dark mode regular asset background color */
#define COLOR_REGULAR_CARD_DARK_BLUE_DARK_MODE QColor("#262626")
/* Sheet dark mode regular asset background color */
#define COLOR_REGULAR_CARD_LIGHT_BLUE_DARK_MODE QColor("#262626")
/* Toolbar not selected text color */
#define COLOR_TOOLBAR_NOT_SELECTED_TEXT_DARK_MODE QColor("#ffffff")
/* Toolbar selected text color */
#define COLOR_TOOLBAR_SELECTED_TEXT_DARK_MODE QColor("#ffffff")


/* Sheet label color as a string */
#define STRING_LABEL_COLOR "color: #0059b3"
#define STRING_LABEL_COLOR_DARK "color: #ffffff"
#define STRING_LABEL_COLOR_WARNING "color: #FF8080"


/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define QR_IMAGE_SIZE 300

/* Number of frames in spinner animation */
#define SPINNER_FRAMES 36

#define QAPP_ORG_NAME "Sheet"
#define QAPP_ORG_DOMAIN "sheetproject.org"
#define QAPP_APP_NAME_DEFAULT "Sheet-Qt"
#define QAPP_APP_NAME_TESTNET "Sheet-Qt-testnet"

#endif // SHEET_QT_GUICONSTANTS_H