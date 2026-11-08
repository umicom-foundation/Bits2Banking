/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-framework-profile/device/profile_name_test.dart
 *
 * PURPOSE:
 *   Provide a headless Flutter device integration supplement for the native Framework binding.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:umicom_profile_name/umicom_profile_name.dart';
void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();
  testWidgets('target native asset normalizes a name', (tester) async {
    expect(normalizeProfileName('Device_User').canonicalName, 'device_user');
  });
  testWidgets('target native asset refuses embedded zero and Unicode', (tester) async {
    expect(normalizeProfileName('Ab\u0000c').accepted, isFalse);
    expect(normalizeProfileName('Useré').accepted, isFalse);
  });
  testWidgets('target result outlives native temporary buffers', (tester) async {
    final first = normalizeProfileName('FIRST');
    for (var i = 0; i < 50; ++i) normalizeProfileName('USER_$i');
    expect(first.canonicalName, 'first');
  });
}
