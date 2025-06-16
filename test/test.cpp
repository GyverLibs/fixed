#include <AUnit.h>
// #define FIXED_USE_64
#include <fixed.h>

using namespace aunit;
using fixt = fixedT<12>;

test(ComplexExpression1) {
    fixt a = (fixt(123) + 3.14f) / fixt(0.5f);  // (123 + 3.14) / 0.5 = 126.14 / 0.5 = 252.28
    assertNear(a.toFloat(), 252.28f, 0.05f);
}

test(ComplexExpression2) {
    fixt a(2.0f);
    a *= (fixt(5) - 1) + 3.5f;  // a = 2 * (4 + 3.5) = 2 * 7.5 = 15
    assertNear(a.toFloat(), 15.0f, 0.01f);
}

test(ComplexExpression3) {
    fixt a(10.0f);
    a /= (fixt(2) + fixt(3)) * 0.5f;  // a = 10 / ((2 + 3) * 0.5) = 10 / 2.5 = 4
    assertNear(a.toFloat(), 4.0f, 0.01f);
}

test(ComplexExpression4) {
    fixt a = fixt(1.5f);
    a += fixt(2.5f) * 3 - 1;  // a = 1.5 + (2.5*3) - 1 = 1.5 + 7.5 - 1 = 8
    assertNear(a.toFloat(), 8.0f, 0.01f);
}

test(ComplexExpression5) {
    fixt a(5.0f);
    a -= (fixt(1.2f) + 2) * fixt(2);  // a = 5 - (3.2)*2 = 5 - 6.4 = -1.4
    assertNear(a.toFloat(), -1.4f, 0.02f);
}

test(AdditionAssignmentfixt) {
    fixt a(1.5f);
    fixt b(2.25f);
    a += b;
    assertNear(a.toFloat(), 3.75f, 0.01f);
}

test(SubtractionAssignmentfixt) {
    fixt a(5.0f);
    fixt b(1.75f);
    a -= b;
    assertNear(a.toFloat(), 3.25f, 0.01f);
}

test(MultiplicationAssignmentfixt) {
    fixt a(1.5f);
    fixt b(2.0f);
    a *= b;
    assertNear(a.toFloat(), 3.0f, 0.01f);
}

test(DivisionAssignmentfixt) {
    fixt a(3.0f);
    fixt b(1.5f);
    a /= b;
    assertNear(a.toFloat(), 2.0f, 0.01f);
}

test(AdditionAssignmentInt) {
    fixt a(2.5f);
    a += 3;  // int
    assertNear(a.toFloat(), 5.5f, 0.01f);
}

test(SubtractionAssignmentFloat) {
    fixt a(6.0f);
    a -= 2.5f;  // float
    assertNear(a.toFloat(), 3.5f, 0.01f);
}

test(MultiplicationAssignmentInt) {
    fixt a(1.5f);
    a *= 4;  // int
    assertNear(a.toFloat(), 6.0f, 0.01f);
}

test(DivisionAssignmentFloat) {
    fixt a(9.0f);
    a /= 3.0f;  // float
    assertNear(a.toFloat(), 3.0f, 0.01f);
}

test(NegativeValues) {
    fixt a(-2);
    fixt b(-1.5f);
    assertNear(a.toFloat(), -2.0f, 0.01f);
    assertNear(b.toFloat(), -1.5f, 0.01f);
}

test(NegativeAddition) {
    fixt a(-2.0f), b(3.5f);
    fixt c = a + b;
    assertNear(c.toFloat(), 1.5f, 0.01f);
}

test(MultipleAdditions) {
    fixt a(1.0f), b(2.0f), c(3.0f);
    fixt sum = a + b + c;
    assertNear(sum.toFloat(), 6.0f, 0.01f);
}

test(MultiplyByZero) {
    fixt a(2.75f), b(0.0f);
    fixt c = a * b;
    assertNear(c.toFloat(), 0.0f, 0.01f);
}

test(MultiplyByFraction) {
    fixt a(2.0f), b(0.5f);
    fixt c = a * b;
    assertNear(c.toFloat(), 1.0f, 0.01f);
}

test(DivideByOne) {
    fixt a(7.5f), b(1.0f);
    fixt c = a / b;
    assertNear(c.toFloat(), 7.5f, 0.01f);
}

test(DivideByFraction) {
    fixt a(1.0f), b(0.25f);
    fixt c = a / b;
    assertNear(c.toFloat(), 4.0f, 0.01f);
}

test(PrecisionCheck) {
    fixt a(0.1f);
    assertNear(a.toFloat(), 0.1f, 0.01f);  // с учётом округления
}

test(OverflowCheck_Multiply) {
    fixt a(32767.0f);  // ближе к максимуму для int32_t с 8 дробными битами
    fixt b(32767.0f);
    fixt c = a * b;
    float val = c.toFloat();
    assertTrue(!isnan(val));
}

test(Constructor_Int) {
    fixt a(5);
    assertNear(a.toFloat(), 5.0f, 0.01f);
}

test(Constructor_Float) {
    fixt a(3.75f);
    assertNear(a.toFloat(), 3.75f, 0.01f);
}

test(Addition) {
    fixt a(1.5f), b(2.25f);
    fixt c = a + b;
    assertNear(c.toFloat(), 3.75f, 0.01f);
}

test(Subtraction) {
    fixt a(5.0f), b(2.5f);
    fixt c = a - b;
    assertNear(c.toFloat(), 2.5f, 0.01f);
}

test(Multiplication) {
    fixt a(2.0f), b(3.0f);
    fixt c = a * b;
    assertNear(c.toFloat(), 6.0f, 0.01f);
}

test(Division) {
    fixt a(6.0f), b(2.0f);
    fixt c = a / b;
    assertNear(c.toFloat(), 3.0f, 0.01f);
}

test(Comparison_Equal) {
    fixt a(1.25f), b(1.25f);
    assertTrue(a == b);
}

test(Comparison_NotEqual) {
    fixt a(1.0f), b(2.0f);
    assertTrue(a != b);
}

test(Comparison_LessThan) {
    fixt a(1.0f), b(2.0f);
    assertTrue(a < b);
}

test(Comparison_GreaterThan) {
    fixt a(3.0f), b(2.0f);
    assertTrue(a > b);
}

test(Comparison_LessEqual) {
    fixt a(2.0f), b(2.0f);
    assertTrue(a <= b);
    assertTrue(fixt(1.0f) <= b);
}

test(Comparison_GreaterEqual) {
    fixt a(2.0f), b(2.0f);
    assertTrue(a >= b);
    assertTrue(fixt(3.0f) >= b);
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    aunit::TestRunner::run();
}