/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-framework-profile/bin/profile.dart
 *
 * PURPOSE:
 *   Exercise the Framework native binding and report accepted or refused names without creating accounts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import 'dart:io';
import 'package:umicom_profile_name/umicom_profile_name.dart';
void main(List<String> args) {
  if (args.length != 1) {
    stderr.writeln('Usage: dart run bin/profile.dart NAME');
    exitCode = 2;
    return;
  }
  final result = normalizeProfileName(args.single);
  if (result.accepted) {
    stdout.writeln('canonical: ${result.canonicalName}');
  } else {
    stderr.writeln('name refused; status=${result.status}; no account created');
    exitCode = 1;
  }
}
