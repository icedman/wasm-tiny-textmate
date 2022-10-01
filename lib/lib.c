#define EXPORT                                                                 \
  extern __attribute__((visibility("default"))) __attribute__((used))

#include "textmate.h"

#define SKIP_PARSE_THRESHOLD 500
#define MAX_BUFFER_LENGTH (1024*512)

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
  tx_init_processor(&processor, TxProcessorTypeCollectAndStyle);
}

EXPORT int highlight_buffer(bool start)
{
  if (start) {
    tx_init_parser_state(&stack, txn_syntax_value(syntax));
  }
  string_buffer[string_buffer_idx] = '\n';
  tx_parse_line((char_u*)string_buffer, (char_u*)string_buffer + string_buffer_idx + 1, &stack, &processor);
  begin_string();
  // printf("\n");
  return processor.line_styles_size;
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

EXPORT int get_style_span(int index)
{
  if (index > processor.line_styles_size - 1) {
    return 0;
  }

  int res = 0;

  TxStyleSpan s = processor.line_styles[index];

  // start
  res |= (s.start);
  // length
  res |= ((s.end - s.start) << 8);

  // printf("%d-%d rgb(%d, %d, %d) %d\n", s.start, s.length, s.r, s.g, s.b, res);
  return res;
}

EXPORT int get_style_color(int index)
{
  if (index > processor.line_styles_size - 1) {
    return 0;
  }

  int res = 0;

  TxStyleSpan s = processor.line_styles[index];

  int rgb[] = {250, 250, 250};
  txt_color_to_rgb(s.fg, rgb);

  // rgb
  res |= (rgb[0]);
  res |= (rgb[1] << 8);
  res |= (rgb[2] << 16);
  res |= ((s.italic ? 1 : 0) << 24);

  // printf("%d-%d rgb(%d, %d, %d)\n", s.start, s.length, s.r, s.g, s.b);
  return res;
}

EXPORT int get_theme_foreground()
{
  // theme_ptr t
  int res = 0;

  int rgb[] = {250, 250, 250};

  TxStyleSpan s;
  if (tx_style_from_scope("foreground", theme, &s)) {
    txt_color_to_rgb(s.fg, rgb);
  } else if (tx_style_from_scope("editor.foreground", theme, &s)) {
    txt_color_to_rgb(s.fg, rgb);
  }

  // rgb
  res |= (rgb[0]);
  res |= (rgb[1] << 8);
  res |= (rgb[2] << 16);

  return res;
}

EXPORT int get_theme_background()
{
  // theme_ptr t
  int res = 0;

  int rgb[] = {50, 50, 50};

  TxStyleSpan s;
  if (tx_style_from_scope("background", theme, &s)) {
    txt_color_to_rgb(s.fg, rgb);
  } else if (tx_style_from_scope("editor.background", theme, &s)) {
    txt_color_to_rgb(s.fg, rgb);
  }

  // rgb
  res |= (rgb[0]);
  res |= (rgb[1] << 8);
  res |= (rgb[2] << 16);

  return res;
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
