#include <check.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_tokenize) {
  // char *testStr = "Hei på deg";
  // char **output;

  ck_assert_int_eq(4, 2);
}
END_TEST

Suite *tokenizeSuite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tokenize");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_tokenize);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = tokenizeSuite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
