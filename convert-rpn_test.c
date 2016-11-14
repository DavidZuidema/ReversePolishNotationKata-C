#include <stdlib.h>
#include <check.h>
#include "convert-rpn.h"

#define MAX_EXPRESSION_LENGTH 64

START_TEST(isValidOperator_withValidOperators_returnsTrue)
{
    ck_assert_int_eq(1, isValidOperator('+'));
    ck_assert_int_eq(1, isValidOperator('-'));
    ck_assert_int_eq(1, isValidOperator('*'));
    ck_assert_int_eq(1, isValidOperator('/'));
    ck_assert_int_eq(1, isValidOperator('^'));
}
END_TEST

START_TEST(isValidOperator_withInvalidOperators_returnsFalse)
{
    ck_assert_int_eq(0, isValidOperator('%'));
}
END_TEST

START_TEST(isValidOperand_withValidOperands_returnsTrue)
{
    ck_assert_int_eq(1, isValidOperand('a'));
    ck_assert_int_eq(1, isValidOperand('b'));
    ck_assert_int_eq(1, isValidOperand('c'));
    ck_assert_int_eq(1, isValidOperand('z'));
}
END_TEST

START_TEST(isValidOperand_withInvalidOperands_returnsFalse)
{
    ck_assert_int_eq(0, isValidOperand('`'));
    ck_assert_int_eq(0, isValidOperand('{'));
}
END_TEST

START_TEST(infixToReversePolish_withValidArgs_returnsSuccess)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a", actual, MAX_EXPRESSION_LENGTH));
}
END_TEST

Suite * suite_convert_rpn_create(void)
{
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Convert Infix to Reverse Polish Notation");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, isValidOperator_withValidOperators_returnsTrue);
    tcase_add_test(tc_core, isValidOperator_withInvalidOperators_returnsFalse);
    tcase_add_test(tc_core, isValidOperand_withValidOperands_returnsTrue);
    tcase_add_test(tc_core, isValidOperator_withInvalidOperators_returnsFalse);
    tcase_add_test(tc_core, infixToReversePolish_withValidArgs_returnsSuccess);

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
