(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/coursebook_checks.pas
 *
 * PURPOSE:
 *   Check course capacity, name boundaries, index translation and refusal preservation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

program CourseBookChecks;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
uses CourseBook;
procedure Check(Condition: Boolean; const MessageText: String);
begin
  if not Condition then
  begin WriteLn(StdErr, 'FAIL: ', MessageText); Halt(1); end;
end;
var Book: TCourseBook; Number, Remaining, I: Integer; Name: String;
begin
  InitialiseBook(Book);
  Number := 77;
  Check(not TryAddCourse(Book, '', 2, Number), 'empty name');
  Check(not TryAddCourse(Book, '   ', 2, Number), 'blank name');
  Check(not TryAddCourse(Book, 'C' + #10, 2, Number), 'control character');
  Name := ''; for I := 1 to 41 do Name := Name + 'X';
  Check(not TryAddCourse(Book, Name, 2, Number), 'name length');
  Check(not TryAddCourse(Book, 'Invalid total', -1, Number), 'negative total');
  Check((Book.Count = 0) and (Number = 77), 'refused addition changed outputs');
  Check(TryAddCourse(Book, 'C', 2, Number) and (Number = 1), 'first addition');
  Check(not TryAddCourse(Book, 'C', 2, Number), 'duplicate name');
  Check((Book.Count = 1) and (Number = 1), 'duplicate changed state');
  Check(not TryCompleteCourseLesson(Book, 0), 'zero is not a course number');
  Check(not TryCompleteCourseLesson(Book, 2), 'unoccupied course number');
  Check(TryCompleteCourseLesson(Book, 1), 'first completion');
  Check(TryCompleteCourseLesson(Book, 1), 'second completion');
  Check(not TryCompleteCourseLesson(Book, 1), 'completed course overflow');
  Remaining := 99;
  Check(TryReadRemaining(Book, 1, Remaining) and (Remaining = 0), 'remaining count');
  Remaining := 99;
  Check(not TryReadRemaining(Book, 0, Remaining), 'invalid read');
  Check(Remaining = 99, 'invalid read changed result');
  for I := 2 to CourseCapacity do
  begin
    Str(I, Name); Name := 'Course ' + Name;
    Check(TryAddCourse(Book, Name, I, Number), 'fill list');
    Check(Number = I, 'course number');
  end;
  Number := 77;
  Check(not TryAddCourse(Book, 'Overflow', 1, Number), 'capacity');
  Check((Book.Count = CourseCapacity) and (Number = 77), 'capacity preservation');
  Check(TryReadRemaining(Book, 2, Remaining) and (Remaining = 2), 'independent progress');
  InitialiseBook(Book);
  Name := ''; for I := 1 to CourseNameLimit do Name := Name + 'A';
  Check(TryAddCourse(Book, Name, 0, Number), 'exact name limit and empty course');
  Check(not TryCompleteCourseLesson(Book, Number), 'empty course cannot advance');
  WriteLn('Course book checks passed');
end.
