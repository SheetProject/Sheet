// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Sheet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHEET_SHEETCONSENSUS_H
#define SHEET_SHEETCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_SHEET_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/sheet-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBSHEETCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SHEETCONSENSUS_API_VER 1

typedef enum sheetconsensus_error_t
{
    sheetconsensus_ERR_OK = 0,
    sheetconsensus_ERR_TX_INDEX,
    sheetconsensus_ERR_TX_SIZE_MISMATCH,
    sheetconsensus_ERR_TX_DESERIALIZE,
    sheetconsensus_ERR_AMOUNT_REQUIRED,
    sheetconsensus_ERR_INVALID_FLAGS,
} sheetconsensus_error;

/** Script verification flags */
enum
{
    sheetconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    sheetconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    sheetconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    sheetconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    sheetconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    sheetconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    sheetconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    sheetconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = sheetconsensus_SCRIPT_FLAGS_VERIFY_P2SH | sheetconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               sheetconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | sheetconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               sheetconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | sheetconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int sheetconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, sheetconsensus_error* err);

EXPORT_SYMBOL int sheetconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, sheetconsensus_error* err);

EXPORT_SYMBOL unsigned int sheetconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // SHEET_SHEETCONSENSUS_H
