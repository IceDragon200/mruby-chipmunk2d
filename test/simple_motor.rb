assert('Chipmunk2d::SimpleMotor#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  rate = 0.5
  motor = Chipmunk2d::SimpleMotor.new(a, b, rate)
  assert_kind_of(Chipmunk2d::Constraint, motor)
  assert_kind_of(Chipmunk2d::SimpleMotor, motor)
  assert_equal(a, motor.body_a)
  assert_equal(b, motor.body_b)
  assert_equal(rate, motor.rate)
end
