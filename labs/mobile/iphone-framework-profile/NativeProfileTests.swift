// -----------------------------------------------------------------------------
// Umicom Bits2Banking
// File: labs/mobile/iphone-framework-profile/NativeProfileTests.swift
//
// PURPOSE:
//   Exercise the compiled Swift-to-C path in an Xcode unit-test target.
//
// AUTHOR AND ORGANISATION:
// Sammy Hegab
// Umicom Foundation
//
// LICENCE:
// MIT
// -----------------------------------------------------------------------------

import XCTest
@testable import ProfilePolicyLab

final class NativeProfileTests: XCTestCase {
    func testCanonicalAscii() {
        XCTAssertEqual(NativeProfile.canonical("Sam_007"), "sam_007")
    }
    func testMinimumLength() {
        XCTAssertEqual(NativeProfile.canonical("ABC"), "abc")
    }
    func testMaximumLength() {
        XCTAssertEqual(NativeProfile.canonical(String(repeating: "A", count: 48)),
                       String(repeating: "a", count: 48))
    }
    func testShortValues() {
        for value in ["", "a", "ab"] { XCTAssertNil(NativeProfile.canonical(value)) }
    }
    func testLongInputIsNotTruncatedIntoAValidName() {
        XCTAssertNil(NativeProfile.canonical(String(repeating: "a", count: 49)))
        XCTAssertNil(NativeProfile.canonical(String(repeating: "a", count: 4096)))
    }
    func testInvalidAscii() {
        for value in ["1abc", "_abc", "-abc", "ab c", "a.b", "<b>"] {
            XCTAssertNil(NativeProfile.canonical(value))
        }
    }
    func testUnicodeDoesNotBecomeAscii() {
        for value in ["caf\u{00e9}", "cafe\u{0301}", "ab\u{1f600}"] {
            XCTAssertNil(NativeProfile.canonical(value))
        }
    }
    func testEmbeddedNulPreservesTheWholeValue() {
        XCTAssertNil(NativeProfile.canonical("abc\u{0000}tail"))
    }
    func testPermittedSeparatorsAndDigits() {
        XCTAssertEqual(NativeProfile.canonical("A-1_B"), "a-1_b")
    }
    func testRefusalDoesNotChangeOtherCalls() {
        let first = NativeProfile.canonical("FIRST")
        XCTAssertNil(NativeProfile.canonical("not allowed"))
        XCTAssertEqual(NativeProfile.canonical("SECOND"), "second")
        XCTAssertEqual(first, "first")
    }
}
