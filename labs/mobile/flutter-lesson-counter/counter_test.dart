/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-lesson-counter/counter_test.dart
 *
 * PURPOSE:
 *   Exercise visible counter state, completion limits and reset through buttons.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:lesson_counter/main.dart';

void main() {
  testWidgets('complete three lessons and reset', (tester) async {
    await tester.pumpWidget(const LearningApp());
    expect(find.text('Completed: 0 of 3'), findsOneWidget);
    expect(tester.widget<TextButton>(find.byType(TextButton)).onPressed, isNull);
    for (var count = 1; count <= 3; count += 1) {
      await tester.tap(find.text('Complete a practice lesson'));
      await tester.pump();
      expect(find.text('Completed: $count of 3'), findsOneWidget);
    }
    expect(tester.widget<FilledButton>(find.byType(FilledButton)).onPressed, isNull);
    await tester.tap(find.text('Reset practice'));
    await tester.pump();
    expect(find.text('Completed: 0 of 3'), findsOneWidget);
    expect(tester.widget<FilledButton>(find.byType(FilledButton)).onPressed, isNotNull);
  });
}
