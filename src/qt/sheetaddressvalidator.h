// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Sheet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHEET_QT_SHEETADDRESSVALIDATOR_H
#define SHEET_QT_SHEETADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SheetAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SheetAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Sheet address widget validator, checks for a valid sheet address.
 */
class SheetAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SheetAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SHEET_QT_SHEETADDRESSVALIDATOR_H
