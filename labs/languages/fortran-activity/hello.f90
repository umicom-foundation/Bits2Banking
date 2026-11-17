! Umicom Bits2Banking
! File: labs/languages/fortran-activity/hello.f90
! 
! PURPOSE:
! Introduce one value and observable output before crossing a language boundary.
! 
! AUTHOR AND ORGANISATION:
! Sammy Hegab
! Umicom Foundation
! 
! LICENCE:
! MIT
! 
program first_value
  implicit none
  integer :: completed
  completed = 41
  print '(A,I0)', 'Completed: ', completed
end program first_value
