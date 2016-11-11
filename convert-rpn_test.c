#include <stdlib.h>
#include <check.h>
#include "convert-rpn.h"

START_TEST(isValidOperator_withPlus_returnsTrue)
{
    ck_assert_int_eq(1, isValidOperator('+'));
}
END_TEST

START_TEST(isValidOperator_withModulo_returnsFalse)
{
    ck_assert_int_eq(0, isValidOperator('%'));
}
END_TEST

Suite * suite_convert_rpn_create(void)
{
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Convert Infix to Reverse Polish Notation");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, isValidOperator_withPlus_returnsTrue);
    tcase_add_test(tc_core, isValidOperator_withModulo_returnsFalse);

    suite_add_tcase(suite, tc_core);

    return suite;
}

int main(void) {
    int number_failed;

    Suite *suite;
    SRunner *suiteRunner;

    suite = suite_convert_rpn_create();
    suiteRunner = srunner_create(suite);

    srunner_run_all(suiteRunner, CK_NORMAL);
    number_failed = srunner_ntests_failed(suiteRunner);
    srunner_free(suiteRunner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
