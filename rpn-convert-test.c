#include <stdlib.h>
#include <stdbool.h>
#include <check.h>
#include "rpn-convert.h"

#define MAX_EXPRESSION_LENGTH 64
#define MINIMUM_VALID_LENGTH 1

START_TEST(infixToReversePolish_withValidArgs_returnsSuccess)
{
    char actual[MINIMUM_VALID_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a", actual, MINIMUM_VALID_LENGTH));
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

START_TEST(infixToReversePolish_withTwoOperatorExpression_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("a+b-c", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "abc-+");
}
END_TEST

START_TEST(infixToReversePolish_withMultipleOperatorExpression_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("l/m^n*o-p", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "lmn^/o*p-");
}
END_TEST

START_TEST(infixToReversePolish_withSimpleParensExpression_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("(a+b)-c", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "ab+c-");
}
END_TEST

START_TEST(infixToReversePolish_withMultipleParensExpression_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    char actual2[MAX_EXPRESSION_LENGTH];
    char actual3[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("((v/w)^x)*(y-z)", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "vw/x^yz-*");
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("((l/(m^n))*o)-p", actual2, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual2, "lmn^/o*p-");
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("(a+g)*(((b-a)+c)^(c+(e*(d^f))))", actual3, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual3, "ag+ba-c+cedf^*+^*");
}
END_TEST

START_TEST(infixToReversePolish_withAbsurdParensExpression_outputsCorrectly)
{
    char actual[MAX_EXPRESSION_LENGTH];
    ck_assert_int_eq(RPN_SUCCESS, infixToReversePolish("((((a+(b+(c+(d+(e+(f+(g+(h+(i+(j+(k+(l+(m+(n+o)))))))))))))))))", actual, MAX_EXPRESSION_LENGTH));
    ck_assert_str_eq(actual, "abcdefghijklmno++++++++++++++");
}
END_TEST

Suite * suite_convert_rpn_create(void)
{
    Suite *suite;
    TCase *tc_parse_basic;
    TCase *tc_parse_compound;

    suite = suite_create("Convert Infix to Reverse Polish Notation");
    tc_parse_basic = tcase_create("Parsing Expressions - Basic");
    tc_parse_compound = tcase_create("Parsing Expressions - Compound");

    tcase_add_test(tc_parse_basic, infixToReversePolish_withValidArgs_returnsSuccess);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withInvalidArgs_returnsError);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withInvalidOperand_returnsError);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withSingleOperandExp_outputsCorrectly);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withTwoAdjacentOperands_returnsError);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withBinaryAddition_outputsCorrectly);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withBinarySubtraction_outputsCorrectly);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withBinaryMultiplication_outputsCorrectly);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withBinaryDivision_outputsCorrectly);
    tcase_add_test(tc_parse_basic, infixToReversePolish_withBinaryExponentiation_outputsCorrectly);

    tcase_add_test(tc_parse_compound, infixToReversePolish_withTwoOperatorExpression_outputsCorrectly);
    tcase_add_test(tc_parse_compound, infixToReversePolish_withMultipleOperatorExpression_outputsCorrectly);
    tcase_add_test(tc_parse_compound, infixToReversePolish_withSimpleParensExpression_outputsCorrectly);
    tcase_add_test(tc_parse_compound, infixToReversePolish_withMultipleParensExpression_outputsCorrectly);
    tcase_add_test(tc_parse_compound, infixToReversePolish_withAbsurdParensExpression_outputsCorrectly);

    suite_add_tcase(suite, tc_parse_basic);
    suite_add_tcase(suite, tc_parse_compound);

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
