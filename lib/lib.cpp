#define EXPORT                                                                 \
  extern "C" __attribute__((visibility("default"))) __attribute__((used))

extern "C" {
#include "textmate.h"
}

#include <string.h>

EXPORT void initialize()
{
  tx_initialize();
  // tx_read_package_dir("./");

  TxSyntaxNode *root = tx_syntax_from_scope((char_u*)"source.c");
  TxParserState stack;
  tx_init_parser_state(&stack, txn_syntax_value(root));

  TxParseProcessor processor;
  tx_init_processor(&processor, TxProcessorTypeCollectAndDump);

  TxThemeNode *theme = txn_load_theme((char_u*)"dracula.json");

  char_u temp[TX_MAX_LINE_LENGTH];
  strcpy((char*)temp, "int main(int argc, char** argv)");
  int len = strlen((char*)temp);
  tx_parse_line(temp, temp + len, &stack, &processor);

  txn_free((TxNode*)theme);
  tx_shutdown();
}
