/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-framework-profile/test/profile_consumer_test.dart
 *
 * PURPOSE:
 *   Exercise the native package from an independent consumer rather than importing implementation files.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

@TestOn('vm')
library;
import 'package:test/test.dart';
import 'package:umicom_profile_name/umicom_profile_name.dart';
void main() {
  test('public consumer canonicalizes a valid name', () {
    expect(normalizeProfileName('Course_User').canonicalName, 'course_user');
  });
  test('invalid result has no stale text', () {
    expect(normalizeProfileName('Good').accepted, isTrue);
    final invalid = normalizeProfileName('no/slash');
    expect(invalid.status, 1); expect(invalid.canonicalName, isNull);
  });
  test('unicode input is not silently stripped', () {
    expect(normalizeProfileName('Useré').accepted, isFalse);
  });
  test('results remain independent after another call', () {
    final kept = normalizeProfileName('FIRST');
    expect(normalizeProfileName('SECOND').canonicalName, 'second');
    expect(kept.canonicalName, 'first');
  });
}
