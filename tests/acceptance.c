/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests/acceptance.check" instead.
 */

#include <check.h>

#line 1 "tests/acceptance.check"
#include <stdlib.h>

#include "../src/interpreter/interpreter.h"

START_TEST(basic_maths)
{
#line 6
ck_assert_str_eq(interpret("+ 1 1"), "2");
ck_assert_str_eq(interpret("- 5 12"), "-7");
ck_assert_str_eq(interpret("/ 4 2"), "2");
ck_assert_str_eq(interpret("/ 5 2"), "2");
ck_assert_str_eq(interpret("* 20 10"), "200");
ck_assert_str_eq(interpret("* ( - 20 ) ( - 10 )"), "200");

}
END_TEST

START_TEST(nested_expressions)
{
#line 14
ck_assert_str_eq(interpret("+ 1 ( - 2 1 )"), "2");

}
END_TEST

START_TEST(erroneous_expressions)
{
#line 17
ck_assert(strstr(interpret("+ "), "error: expected whitespace, '-' or one or more of one or more of one of '0123456789' or '(' at end of input"));
ck_assert(strstr(interpret("1 "), "error: expected whitespace, '+', '-', '*', '/', '%', '^' or 'm' at '1'"));
ck_assert(strstr(interpret("()"), "error: expected whitespace, '+', '-', '*', '/', '%', '^' or 'm' at '('"));

}
END_TEST

START_TEST(div_by_zero_error_handling)
{
#line 22
ck_assert_str_eq(interpret("/ 10 0"), "Error: Division by zero!");
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, basic_maths);
    tcase_add_test(tc1_1, nested_expressions);
    tcase_add_test(tc1_1, erroneous_expressions);
    tcase_add_test(tc1_1, div_by_zero_error_handling);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
