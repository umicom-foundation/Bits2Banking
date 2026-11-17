! Umicom Bits2Banking
! File: labs/languages/fortran-activity/main.f90
! 
! PURPOSE:
! Call the existing checked C activity bridge using interoperable integer values.
! 
! AUTHOR AND ORGANISATION:
! Sammy Hegab
! Umicom Foundation
! 
! LICENCE:
! MIT
! 
program activity_client
  use iso_c_binding, only: c_int
  implicit none
  interface
    function activity_next(current) bind(C, name="BtbActivityNext") result(next)
      import c_int
      integer(c_int), value :: current
      integer(c_int) :: next
    end function activity_next
  end interface
  integer(c_int), parameter :: inputs(5) = [-1_c_int, 0_c_int, 41_c_int, 999_c_int, 1000_c_int]
  integer(c_int), parameter :: expected(5) = [-1_c_int, 1_c_int, 42_c_int, 1000_c_int, -1_c_int]
  integer :: i
  integer(c_int) :: next
  do i = 1, size(inputs)
    next = activity_next(inputs(i))
    ! VALUE passes a C int rather than the address of the Fortran variable.
    if (next /= expected(i)) error stop 1
    print '(I0,A,I0)', inputs(i), ' -> ', next
  end do
end program activity_client
