#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("[rational] - Rational ctor") {
	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(3) == Rational(3, 1));
	CHECK(Rational(-3) == Rational(-3, 1));
	CHECK(Rational(10, 6) == Rational(5, 3));
	CHECK(Rational(-10, 6) == Rational(-5, 3));
	CHECK(Rational(10, -6) == Rational(-5, 3));
	CHECK(Rational(-10, -6) == Rational(5, 3));
	CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - Unary minus operator") {
	CHECK(-Rational(3, 4) == Rational(-3, 4));
	CHECK(-Rational(-5, 6) == Rational(5, 6));
}

TEST_CASE("[rational] - Boolean conversion operator") {
	CHECK(bool(Rational(0)) == false);
	CHECK(bool(Rational(1, 2)) == true);
	CHECK(bool(Rational(-1, 2)) == true);
}

TEST_CASE("[rational] - Input operator") {
	std::istringstream input("3/4");
	Rational r;
	input >> r;
	CHECK(r == Rational(3, 4));
}

TEST_CASE("[rational] - Output operator") {
	std::ostringstream output;
	output << Rational(5, 6);
	CHECK(output.str() == "5/6");
}

TEST_CASE("[rational] - Arithmetic operators") {
	Rational r1(2, 3);
	Rational r2(3, 4);

	CHECK((r1 + r2) == Rational(17, 12));
	CHECK((r1 - r2) == Rational(-1, 12));
	CHECK((r1 * r2) == Rational(1, 2));
	CHECK((r1 / r2) == Rational(8, 9));

	Rational r3(-2, 3);
	Rational r4(4, 5);

	CHECK((r3 + r4) == Rational(-2, 15));
	CHECK((r3 - r4) == Rational(-22, 15));
	CHECK((r3 * r4) == Rational(-8, 15));
	CHECK((r3 / r4) == Rational(-5, 6));
}

TEST_CASE("[rational] - Arithmetic operators with assignment") {
	Rational r1(2, 3);
	Rational r2(3, 4);

	r1 += r2;
	CHECK(r1 == Rational(17, 12));

	r1 -= r2;
	CHECK(r1 == Rational(2, 3));

	r1 *= r2;
	CHECK(r1 == Rational(1, 2));

	r1 /= r2;
	CHECK(r1 == Rational(8, 9));

	Rational r3(-2, 3);
	Rational r4(4, 5);

	r3 += r4;
	CHECK(r3 == Rational(-2, 15));

	r3 -= r4;
	CHECK(r3 == Rational(-22, 15));

	r3 *= r4;
	CHECK(r3 == Rational(-8, 15));

	r3 /= r4;
	CHECK(r3 == Rational(-5, 6));
}
