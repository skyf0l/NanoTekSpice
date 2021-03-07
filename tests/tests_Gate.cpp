/*
** EPITECH PROJECT, 2021
** TESTS_GATE
** File description:
** Test Gate
*/

#include <criterion/criterion.h>
#include <Tristate.hpp>

namespace nts
{
    Test(computeAND, basic)
    {
        cr_assert_eq(U && U, U);
        cr_assert_eq(F && U, F);
        cr_assert_eq(T && U, U);
        cr_assert_eq(U && F, F);
        cr_assert_eq(U && T, U);
        cr_assert_eq(F && F, F);
        cr_assert_eq(F && T, F);
        cr_assert_eq(T && F, F);
        cr_assert_eq(T && T, T);
    }

    Test(computeOR, basic)
    {
        cr_assert_eq(U || U, U);
        cr_assert_eq(F || U, U);
        cr_assert_eq(T || U, T);
        cr_assert_eq(U || F, U);
        cr_assert_eq(U || T, T);
        cr_assert_eq(F || F, F);
        cr_assert_eq(F || T, T);
        cr_assert_eq(T || F, T);
        cr_assert_eq(T || T, T);
    }

    Test(computeXOR, basic)
    {
        cr_assert_eq(U ^ U, U);
        cr_assert_eq(F ^ U, U);
        cr_assert_eq(T ^ U, U);
        cr_assert_eq(U ^ F, U);
        cr_assert_eq(U ^ T, U);
        cr_assert_eq(F ^ F, F);
        cr_assert_eq(F ^ T, T);
        cr_assert_eq(T ^ F, T);
        cr_assert_eq(T ^ T, F);
    }

    Test(computeNOT, basic)
    {
        cr_assert_eq(!U, U);
        cr_assert_eq(!F, T);
        cr_assert_eq(!T, F);
    }

    Test(computeNAND, basic)
    {
        cr_assert_eq(!(U && U), U);
        cr_assert_eq(!(F && U), T);
        cr_assert_eq(!(T && U), U);
        cr_assert_eq(!(U && F), T);
        cr_assert_eq(!(U && T), U);
        cr_assert_eq(!(F && F), T);
        cr_assert_eq(!(F && T), T);
        cr_assert_eq(!(T && F), T);
        cr_assert_eq(!(T && T), F);
    }

    Test(computeNOR, basic)
    {
        cr_assert_eq(!(U || U), U);
        cr_assert_eq(!(F || U), U);
        cr_assert_eq(!(T || U), F);
        cr_assert_eq(!(U || F), U);
        cr_assert_eq(!(U || T), F);
        cr_assert_eq(!(F || F), T);
        cr_assert_eq(!(F || T), F);
        cr_assert_eq(!(T || F), F);
        cr_assert_eq(!(T || T), F);
    }

    Test(computeNXOR, basic)
    {
        cr_assert_eq(!(U ^ U), U);
        cr_assert_eq(!(F ^ U), U);
        cr_assert_eq(!(T ^ U), U);
        cr_assert_eq(!(U ^ F), U);
        cr_assert_eq(!(U ^ T), U);
        cr_assert_eq(!(F ^ F), T);
        cr_assert_eq(!(F ^ T), F);
        cr_assert_eq(!(T ^ F), F);
        cr_assert_eq(!(T ^ T), T);
    }

} // namespace nts