#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_A UINT64_C(4294967295)
#define MAX_MODULUS UINT64_C(4294967296)

/* Parse a non-negative integer. Base 0 permits decimal and 0x-prefixed hex. */
static int parse_u64(const char *text, uint64_t *value) {
  char *end = NULL;
  unsigned long long parsed;

  if (text == NULL || text[0] == '\0' || text[0] == '-') {
    return 0;
  }

  errno = 0;
  parsed = strtoull(text, &end, 0);

  if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
    return 0;
  }

  *value = (uint64_t)parsed;
  return 1;
}

/*
 * Extended Euclidean Algorithm.
 * Returns gcd(a, b), and writes x, y such that a*x + b*y = gcd(a, b).
 * Inputs are non-negative and bounded by 2^32 in this tool.
 */
static int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y) {
  int64_t old_r = a;
  int64_t r = b;
  int64_t old_x = 1;
  int64_t current_x = 0;
  int64_t old_y = 0;
  int64_t current_y = 1;

  while (r != 0) {
    const int64_t quotient = old_r / r;
    const int64_t next_r = old_r - quotient * r;
    const int64_t next_x = old_x - quotient * current_x;
    const int64_t next_y = old_y - quotient * current_y;

    old_r = r;
    r = next_r;
    old_x = current_x;
    current_x = next_x;
    old_y = current_y;
    current_y = next_y;
  }

  *x = old_x;
  *y = old_y;
  return old_r;
}

static void print_usage(const char *program) {
  fprintf(stderr, "Usage: %s <a> <modulus>\n", program);
  fprintf(stderr, "Accepts decimal or 0x-prefixed hexadecimal values.\n");
  fprintf(stderr, "Scope: 0 <= a <= 2^32-1 and 2 <= modulus <= 2^32.\n");
}

int main(int argc, char **argv) {
  uint64_t a_input;
  uint64_t modulus;
  uint64_t a;
  int64_t coefficient_a;
  int64_t coefficient_m;
  int64_t gcd;

  if (argc != 3 || !parse_u64(argv[1], &a_input) ||
      !parse_u64(argv[2], &modulus)) {
    print_usage(argv[0]);
    return 2;
  }

  if (a_input > MAX_A || modulus < 2 || modulus > MAX_MODULUS) {
    print_usage(argv[0]);
    return 2;
  }

  a = a_input % modulus;
  gcd = extended_gcd((int64_t)a, (int64_t)modulus, &coefficient_a,
                     &coefficient_m);

  printf("a (input) = %" PRIu64 " (0x%" PRIx64 ")\n", a_input, a_input);
  printf("a (mod m) = %" PRIu64 " (0x%" PRIx64 ")\n", a, a);
  printf("modulus   = %" PRIu64 " (0x%" PRIx64 ")\n", modulus, modulus);
  printf("gcd       = %" PRId64 "\n", gcd);
  printf("bezout    = (%" PRId64 ")*(%" PRIu64 ") + (%" PRId64 ")*(%" PRIu64
         ") = %" PRId64 "\n",
         coefficient_a, a, coefficient_m, modulus, gcd);

  if (gcd != 1) {
    puts("inverse   = does not exist because gcd(a, modulus) != 1");
    return 1;
  }

  {
    int64_t reduced = coefficient_a % (int64_t)modulus;
    uint64_t inverse;
    uint64_t check;

    if (reduced < 0) {
      reduced += (int64_t)modulus;
    }

    inverse = (uint64_t)reduced;
    check = (a * inverse) % modulus;

    printf("inverse   = %" PRIu64 "\n", inverse);
    printf("inverse_hex = 0x%08" PRIx64 "\n", inverse);
    printf("verify    = (a * inverse) mod modulus = %" PRIu64 "\n", check);

    if (check != 1) {
      fputs("internal verification failed\n", stderr);
      return 3;
    }
  }

  return 0;
}
