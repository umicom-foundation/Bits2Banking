(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/coursebook_demo.pas
 *
 * PURPOSE:
 *   Display a small course list through the existing checked progress model.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

program CourseBookDemo;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
uses CourseBook;
var Book: TCourseBook; Number, Remaining, I: Integer;
begin
  InitialiseBook(Book);
  if not TryAddCourse(Book, 'Learning C', 4, Number) then Halt(1);
  if not TryAddCourse(Book, 'Introduction to RISC-V', 3, Number) then Halt(1);
  if not TryCompleteCourseLesson(Book, 1) then Halt(1);
  if not TryCompleteCourseLesson(Book, 1) then Halt(1);
  for I := 1 to Book.Count do
  begin
    if not TryReadRemaining(Book, I, Remaining) then Halt(1);
    WriteLn(I, '. ', Book.Entries[I - 1].Name, ': ', Remaining, ' remaining');
  end;
end.
