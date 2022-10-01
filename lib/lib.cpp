#define EXPORT                                                                 \
  extern "C" __attribute__((visibility("default"))) __attribute__((used))

extern "C" {
#include "textmate.h"
}

// extern const char* GRAMMAR_CPP;
// extern const char* THEME_MONOKAI;

#define SKIP_PARSE_THRESHOLD 500
#define MAX_BUFFER_LENGTH (1024*512*2)

static char string_buffer[MAX_BUFFER_LENGTH];
static int string_buffer_idx = 0;

#include <string.h>
#include <stdio.h>

static TxSyntaxNode *syntax;
static TxThemeNode *theme;
static TxParserState stack;
static TxParseProcessor processor;

EXPORT void begin_string();

EXPORT void initialize()
{
  tx_initialize();
  tx_init_processor(&processor, TxProcessorTypeCollectAndRender);
}

EXPORT int highlight_buffer(bool start)
{
  if (start) {
    tx_init_parser_state(&stack, txn_syntax_value(syntax));
  }
  tx_parse_line((char_u*)string_buffer, (char_u*)string_buffer + string_buffer_idx, &stack, &processor);
  begin_string();
  // printf("\n");
  return 0;
}

EXPORT int load_theme_buffer()
{
  theme = txn_load_theme_data((char_u*)string_buffer);
  processor.theme = txn_theme_value(theme);
  begin_string();
  return 0;
}

EXPORT int load_language_buffer()
{
  syntax = txn_load_syntax_data((char_u*)string_buffer);
  tx_init_parser_state(&stack, txn_syntax_value(syntax));
  begin_string();
  return 0;
}

EXPORT void begin_string()
{
  string_buffer_idx = 0;
}

EXPORT void push_character(int c)
{
  if (string_buffer_idx >= MAX_BUFFER_LENGTH) {
    printf("buffer overflow %d\n", string_buffer_idx);
    string_buffer_idx = 0;
    return;
  }
  string_buffer[string_buffer_idx++] = c;
  string_buffer[string_buffer_idx] = 0;
}
