/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/flutter-lesson-counter/main.dart
 *
 * PURPOSE:
 *   Teach visible state and a bounded button action in a Flutter practice app.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import 'package:flutter/material.dart';

void main() => runApp(const LearningApp());

class LearningApp extends StatelessWidget {
  const LearningApp({super.key});
  @override
  Widget build(BuildContext context) => MaterialApp(
    title: 'Umicom learning practice',
    theme: ThemeData(colorSchemeSeed: const Color(0xff185ba4)),
    home: const LessonCounter(),
  );
}

class LessonCounter extends StatefulWidget {
  const LessonCounter({super.key});
  @override
  State<LessonCounter> createState() => _LessonCounterState();
}

class _LessonCounterState extends State<LessonCounter> {
  // Local state is intentionally temporary. Reusable progress services and
  // storage belong to Framework when integrating a real Umicom application.
  int completed = 0;
  @override
  Widget build(BuildContext context) => Scaffold(
    appBar: AppBar(title: const Text('Umicom learning practice')),
    body: Padding(
      padding: const EdgeInsets.all(24),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text('Completed: $completed of 3'),
          FilledButton(
            onPressed: completed < 3
                ? () => setState(() { if (completed < 3) completed += 1; })
                : null,
            child: const Text('Complete a practice lesson'),
          ),
          TextButton(
            onPressed: completed > 0 ? () => setState(() { completed = 0; }) : null,
            child: const Text('Reset practice'),
          ),
        ],
      ),
    ),
  );
}
