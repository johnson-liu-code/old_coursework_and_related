! Duffing Oscillator

program duffing
    implicit none
! real kind with decimal precision() >= 14 and exponent range() >= 300
    integer, parameter :: dp = selected_real_kind(14, 300)
! constants
    real(dp), parameter :: zero = 0._dp, one = 1._dp, two = 2._dp
    real(dp), parameter :: half = one / two, six = (one + two) * two
! physics parameters
    real(dp) :: omega = 2.4_dp, gamma = 0.1_dp
    real(dp) :: a = 0.5_dp, b = 0.25_dp
    real(dp) :: F0 = 2.0_dp
! variables
    real(dp), dimension(2) :: xv, dxvdt
    real(dp) :: t, t_max, dt
    real(dp), dimension(2) :: k1, k2, k3, k4, xv_step
    character(len=50) :: file_name
! get input from user and initialize
    print *, 'Duffing Oscillator Simulation'
    print *, '============================='
    print *, 'Enter initial x and v: '
    read *, xv(1), xv(2)
    print *, 'Enter time step dt'
    read *, dt
    print *, 'Enter integration time: '
    read *, t_max
    print *, 'Enter output file name: '
    read *, file_name
    open(unit=2, file=file_name)
    t = zero
    write(2, *) t, xv(1), xv(2)
! main integration loop
    do
        if (t >= t_max) exit
!    4th order Runge-Kutta step
        call find_dxvdt(t, xv, dxvdt)
        k1 = dt * dxvdt
        xv_step = xv + k1 / two
        call find_dxvdt(t + half * dt, xv_step, dxvdt)
        k2 = dt * dxvdt
        xv_step = xv + k2 / two
        call find_dxvdt(t + half * dt, xv_step, dxvdt)
        k3 = dt * dxvdt
        xv_step = xv + k3
        call find_dxvdt(t + dt, xv_step, dxvdt)
        k4 = dt * dxvdt
        xv = xv + (k1 + two * k2 + two * k3 + k4) / six
        t = t + dt
        write(2, *) t, xv(1), xv(2)
    end do
    print *, 'Output in file: ', file_name
    close(2)

! Duffing equation
contains
    subroutine find_dxvdt(t, xv, dxvdt)
        implicit none
        real(dp), intent(in) :: t
        real(dp), dimension(2), intent(in) :: xv
        real(dp), dimension(2), intent(out) :: dxvdt
        dxvdt(1) = xv(2)
        dxvdt(2) = - gamma * xv(2) + 2 * a * xv(1) - 4 * b * xv(1)**3
        dxvdt(2) = dxvdt(2) + F0 * cos(omega * t)
    end subroutine find_dxvdt
end program duffing
