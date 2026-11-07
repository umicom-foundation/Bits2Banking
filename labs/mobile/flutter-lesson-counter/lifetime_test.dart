/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-lesson-counter/lifetime_test.dart
 *
 * PURPOSE:
 *   Check that rebuilds retain a mounted counter and disposal releases its temporary state.
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
  testWidgets('theme rebuild retains the mounted count', (tester) async {
    await tester.pumpWidget(MaterialApp(
      theme: ThemeData.light(),
      home: const LessonCounter(key: ValueKey('practice')),
    ));
    await tester.tap(find.text('Complete a practice lesson'));
    await tester.pump();
    expect(find.text('Completed: 1 of 3'), findsOneWidget);
    await tester.pumpWidget(MaterialApp(
      theme: ThemeData.dark(),
      home: const LessonCounter(key: ValueKey('practice')),
    ));
    expect(find.text('Completed: 1 of 3'), findsOneWidget);
    await tester.tap(find.text('Reset practice'));
    await tester.pump();
    expect(find.text('Completed: 0 of 3'), findsOneWidget);
  });

  testWidgets('a disposed practice has no persisted count', (tester) async {
    await tester.pumpWidget(const LearningApp());
    await tester.tap(find.text('Complete a practice lesson'));
    await tester.pump();
    expect(find.text('Completed: 1 of 3'), findsOneWidget);
    await tester.pumpWidget(const SizedBox.shrink());
    await tester.pumpWidget(const LearningApp());
    expect(find.text('Completed: 0 of 3'), findsOneWidget);
    expect(tester.takeException(), isNull);
  });
}
