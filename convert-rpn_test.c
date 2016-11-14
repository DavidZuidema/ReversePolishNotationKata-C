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
    char actual[1];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a", actual, 1));
}
END_TEST

START_TEST(infixToReversePolish_withInvalidArgs_returnsError)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_INVALID_ARGS, infixToReversePolish(NULL, actual, MAX_EXPRESSION_LENGTH));
    ck_assert_int_eq(RPN_INVALID_ARGS, infixToReversePolish("a", NULL, MAX_EXPRESSION_LENGTH));
    ck_assert_int_eq(RPN_INVALID_ARGS, infixToReversePolish("a", actual, 0));
}
END_TEST

START_TEST(infixToReversePolish_withInvalidOperand_returnsError)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_PARSE_ERROR_INVALID_OPERAND, infixToReversePolish("A", actual, MAX_EXPRESSION_LENGTH));
}
END_TEST

START_TEST(infixToReversePolish_withSingleOperandExp_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "a");
}
END_TEST

START_TEST(infixToReversePolish_withTwoAdjacentOperands_returnsError)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_PARSE_ERROR_INVALID_OPERATOR, infixToReversePolish("aa", actual, MAX_EXPRESSION_LENGTH));
}
END_TEST

START_TEST(infixToReversePolish_withBinaryAddition_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a+b", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab+");
}
END_TEST

START_TEST(infixToReversePolish_withBinarySubtraction_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a-b", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab-");
}
END_TEST

START_TEST(infixToReversePolish_withBinaryMultiplication_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a*b", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab*");
}
END_TEST

START_TEST(infixToReversePolish_withBinaryDivision_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a/b", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab/");
}
END_TEST

START_TEST(infixToReversePolish_withBinaryExponentiation_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a^b", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab^");
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
    tcase_add_test(tc_core, infixToReversePolish_withInvalidArgs_returnsError);
    tcase_add_test(tc_core, infixToReversePolish_withInvalidOperand_returnsError);
    tcase_add_test(tc_core, infixToReversePolish_withSingleOperandExp_outputsCorrectly);
    tcase_add_test(tc_core, infixToReversePolish_withTwoAdjacentOperands_returnsError);
    tcase_add_test(tc_core, infixToReversePolish_withBinaryAddition_outputsCorrectly);
    tcase_add_test(tc_core, infixToReversePolish_withBinarySubtraction_outputsCorrectly);
    tcase_add_test(tc_core, infixToReversePolish_withBinaryMultiplication_outputsCorrectly);
    tcase_add_test(tc_core, infixToReversePolish_withBinaryDivision_outputsCorrectly);
    tcase_add_test(tc_core, infixToReversePolish_withBinaryExponentiation_outputsCorrectly);


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
