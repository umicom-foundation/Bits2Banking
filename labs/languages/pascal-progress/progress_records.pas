(*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/pascal-progress/progress_records.pas
 *
 * PURPOSE:
 *   Display independent progress records using the shared Pascal unit.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*)

program ProgressRecords;
{$mode objfpc}
{$H+}
{$R+}
{$Q+}
uses LessonProgress;

var
  Courses: array[0..1] of TLessonProgress;
  Item: Integer;
begin
  if not TryCreateProgress(3, 0, Courses[0]) then Halt(1);
  if not TryCreateProgress(5, 2, Courses[1]) then Halt(1);
  if not TryCompleteLesson(Courses[0]) then Halt(1);
  for Item := Low(Courses) to High(Courses) do
    WriteLn('Course ', Item + 1, ': ',
      RemainingLessons(Courses[Item].Total, Courses[Item].Completed),
      ' lessons remaining');
end.

