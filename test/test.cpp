#include <AUnit.h>
#include <fixed.h>

using namespace aunit;

test(ComplexExpression1) {
    fixed8 a = (fixed8(123) + 3.14f) / fixed8(0.5f);  // (123 + 3.14) / 0.5 = 126.14 / 0.5 = 252.28
    assertNear(a.toFloat(), 252.28f, 0.05f);
}

test(ComplexExpression2) {
    fixed8 a(2.0f);
    a *= (fixed8(5) - 1) + 3.5f;  // a = 2 * (4 + 3.5) = 2 * 7.5 = 15
    assertNear(a.toFloat(), 15.0f, 0.01f);
}

test(ComplexExpression3) {
    fixed8 a(10.0f);
    a /= (fixed8(2) + fixed8(3)) * 0.5f;  // a = 10 / ((2 + 3) * 0.5) = 10 / 2.5 = 4
    assertNear(a.toFloat(), 4.0f, 0.01f);
}

test(ComplexExpression4) {
    fixed8 a = fixed8(1.5f);
    a += fixed8(2.5f) * 3 - 1;  // a = 1.5 + (2.5*3) - 1 = 1.5 + 7.5 - 1 = 8
    assertNear(a.toFloat(), 8.0f, 0.01f);
}

test(ComplexExpression5) {
    fixed8 a(5.0f);
    a -= (fixed8(1.2f) + 2) * fixed8(2);  // a = 5 - (3.2)*2 = 5 - 6.4 = -1.4
    assertNear(a.toFloat(), -1.4f, 0.02f);
}

test(AdditionAssignmentFixed8) {
    fixed8 a(1.5f);
    fixed8 b(2.25f);
    a += b;
    assertNear(a.toFloat(), 3.75f, 0.01f);
}

test(SubtractionAssignmentFixed8) {
    fixed8 a(5.0f);
    fixed8 b(1.75f);
    a -= b;
    assertNear(a.toFloat(), 3.25f, 0.01f);
}

test(MultiplicationAssignmentFixed8) {
    fixed8 a(1.5f);
    fixed8 b(2.0f);
    a *= b;
    assertNear(a.toFloat(), 3.0f, 0.01f);
}

test(DivisionAssignmentFixed8) {
    fixed8 a(3.0f);
    fixed8 b(1.5f);
    a /= b;
    assertNear(a.toFloat(), 2.0f, 0.01f);
}

test(AdditionAssignmentInt) {
    fixed8 a(2.5f);
    a += 3;  // int
    assertNear(a.toFloat(), 5.5f, 0.01f);
}

test(SubtractionAssignmentFloat) {
    fixed8 a(6.0f);
    a -= 2.5f;  // float
    assertNear(a.toFloat(), 3.5f, 0.01f);
}

test(MultiplicationAssignmentInt) {
    fixed8 a(1.5f);
    a *= 4;  // int
    assertNear(a.toFloat(), 6.0f, 0.01f);
}

test(DivisionAssignmentFloat) {
    fixed8 a(9.0f);
    a /= 3.0f;  // float
    assertNear(a.toFloat(), 3.0f, 0.01f);
}

test(NegativeValues) {
    fixed8 a(-2);
    fixed8 b(-1.5f);
    assertNear(a.toFloat(), -2.0f, 0.01f);
    assertNear(b.toFloat(), -1.5f, 0.01f);
}

test(NegativeAddition) {
    fixed8 a(-2.0f), b(3.5f);
    fixed8 c = a + b;
    assertNear(c.toFloat(), 1.5f, 0.01f);
}

test(MultipleAdditions) {
    fixed8 a(1.0f), b(2.0f), c(3.0f);
    fixed8 sum = a + b + c;
    assertNear(sum.toFloat(), 6.0f, 0.01f);
}

test(MultiplyByZero) {
    fixed8 a(2.75f), b(0.0f);
    fixed8 c = a * b;
    assertNear(c.toFloat(), 0.0f, 0.01f);
}

test(MultiplyByFraction) {
    fixed8 a(2.0f), b(0.5f);
    fixed8 c = a * b;
    assertNear(c.toFloat(), 1.0f, 0.01f);
}

test(DivideByOne) {
    fixed8 a(7.5f), b(1.0f);
    fixed8 c = a / b;
    assertNear(c.toFloat(), 7.5f, 0.01f);
}

test(DivideByFraction) {
    fixed8 a(1.0f), b(0.25f);
    fixed8 c = a / b;
    assertNear(c.toFloat(), 4.0f, 0.01f);
}

test(PrecisionCheck) {
    fixed8 a(0.1f);
    assertNear(a.toFloat(), 0.1f, 0.01f);  // с учётом округления
}

test(OverflowCheck_Multiply) {
    fixed8 a(32767.0f);  // ближе к максимуму для int32_t с 8 дробными битами
    fixed8 b(32767.0f);
    fixed8 c = a * b;
    float val = c.toFloat();
    assertTrue(!isnan(val));
}

test(Constructor_Int) {
    fixed8 a(5);
    assertNear(a.toFloat(), 5.0f, 0.01f);
}

test(Constructor_Float) {
    fixed8 a(3.75f);
    assertNear(a.toFloat(), 3.75f, 0.01f);
}

test(Addition) {
    fixed8 a(1.5f), b(2.25f);
    fixed8 c = a + b;
    assertNear(c.toFloat(), 3.75f, 0.01f);
}

test(Subtraction) {
    fixed8 a(5.0f), b(2.5f);
    fixed8 c = a - b;
    assertNear(c.toFloat(), 2.5f, 0.01f);
}

test(Multiplication) {
    fixed8 a(2.0f), b(3.0f);
    fixed8 c = a * b;
    assertNear(c.toFloat(), 6.0f, 0.01f);
}

test(Division) {
    fixed8 a(6.0f), b(2.0f);
    fixed8 c = a / b;
    assertNear(c.toFloat(), 3.0f, 0.01f);
}

test(Comparison_Equal) {
    fixed8 a(1.25f), b(1.25f);
    assertTrue(a == b);
}

test(Comparison_NotEqual) {
    fixed8 a(1.0f), b(2.0f);
    assertTrue(a != b);
}

test(Comparison_LessThan) {
    fixed8 a(1.0f), b(2.0f);
    assertTrue(a < b);
}

test(Comparison_GreaterThan) {
    fixed8 a(3.0f), b(2.0f);
    assertTrue(a > b);
}

test(Comparison_LessEqual) {
    fixed8 a(2.0f), b(2.0f);
    assertTrue(a <= b);
    assertTrue(fixed8(1.0f) <= b);
}

test(Comparison_GreaterEqual) {
    fixed8 a(2.0f), b(2.0f);
    assertTrue(a >= b);
    assertTrue(fixed8(3.0f) >= b);
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    aunit::TestRunner::run();
}